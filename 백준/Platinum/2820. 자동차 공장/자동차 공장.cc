#include <iostream>
#include <vector>
#define MAX 524288

std::vector<long long> segtree(MAX * 2, 0);
std::vector<long long> lazy(MAX * 2, 0);
std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> ett;


long long sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);
void insert_lazy(int left, int right, int point);
void insert_range(int start, int end, int left, int right, int point, long long num);
int dfs(int n, int start);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;

	graph.resize(n + 1);
	ett.resize(n + 1);
	std::vector<int> vec(n + 1);

	int temp;
	std::cin >> temp;
	vec[1] = temp;

	for (int i = 2; i <= n; i++) {
		int temp1, temp2;
		std::cin >> temp1 >> temp2;

		graph[temp2].push_back(i);

		vec[i] = temp1;
	}

	//탐색 시작
	dfs(1, 1);

	for (int i = 1; i <= n; i++) {
		insert(ett[i].first, vec[i]);
	}

	for (int i = 0; i < m; i++) {
		std::string temp;
		std::cin >> temp;

		if (temp == "p") {
			int point;
			long long num;
			std::cin >> point >> num;
			if(ett[point].first != ett[point].second) insert_range(ett[point].first + 1, ett[point].second, 0, MAX - 1, 1, num);
		}
		if (temp == "u") {
			int point;
			std::cin >> point;
			std::cout << sum_tree(ett[point].first, ett[point].first, 0, MAX - 1, 1) << "\n";
		}
	}
}

void insert(int index, long long num) {
	int point = index + MAX;

	segtree[point] += num;
	while (point > 0) {
		point /= 2;
		segtree[point] += num;
	}
}

void insert_lazy(int left, int right, int point) {
	if (lazy[point] != 0) {
		segtree[point] += (right - left + 1) * lazy[point];
		if (left != right) {
			lazy[point * 2] += lazy[point];
			lazy[point * 2 + 1] += lazy[point];
		}

		lazy[point] = 0;
	}
}

void insert_range(int start, int end, int left, int right, int point, long long num) {
	insert_lazy(left, right, point);

	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point] += (right - left + 1) * num;
		if (left != right) {
			lazy[point * 2] += num;
			lazy[point * 2 + 1] += num;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point] = segtree[point * 2] + segtree[point * 2 + 1];
}

long long sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return 0;
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
	return sum_tree(start, end, left, mid, point * 2) + sum_tree(start, end, mid + 1, right, point * 2 + 1);
}

int dfs(int n, int start) {
	int temp = start;
	ett[n].first = temp;
	for (int i = 0; i < graph[n].size(); i++) {
		temp = dfs(graph[n][i], temp + 1);
	}

	ett[n].second = temp;
	return temp;
}