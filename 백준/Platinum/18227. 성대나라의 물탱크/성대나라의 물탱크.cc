#include <iostream>
#include <vector>
#define MAX 262144

std::vector<long long> segtree(MAX * 2, 0);
std::vector<std::vector<int>> graph;
std::vector<std::pair<int, int>> vec;
std::vector<int> vec_depth;


long long sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);
int dfs(int n, int start, int depth);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m, start_point;
	std::cin >> n >> start_point;

	graph.resize(n + 1);
	vec.resize(n + 1);
    vec_depth.resize(n + 1);
    
	for (int i = 1; i < n; i++) {
		int temp1, temp2;
        std::cin >> temp1 >> temp2;
        graph[temp1].push_back(temp2);
        graph[temp2].push_back(temp1);
	}
	//탐색 시작
	dfs(start_point, 1, 1);

    std::cin >> m;
    
	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;

		if (temp == 1) {
			int point;
			std::cin >> point;
			insert(vec[point].first, 1);
		}
		if (temp == 2) {
			int point;
			std::cin >> point;
			std::cout << sum_tree(vec[point].first, vec[point].second, 0, MAX - 1, 1) * vec_depth[point] << "\n";
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

long long sum_tree(int start, int end, int left, int right, int point) {
	if (left > end || right < start) return 0;
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
	return sum_tree(start, end, left, mid, point * 2) + sum_tree(start, end, mid + 1, right, point * 2 + 1);
}

int dfs(int n, int start, int depth) {
	int temp = start;
	vec[n].first = temp;
    vec_depth[n] = depth;
	for (int i = 0; i < graph[n].size(); i++) {
		if(vec[graph[n][i]].first == 0) temp = dfs(graph[n][i], temp + 1, depth + 1);
	}

	vec[n].second = temp;
	return temp;
}