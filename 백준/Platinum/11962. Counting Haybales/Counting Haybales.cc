#include <iostream>
#include <vector>
#define MAX 262144
#define MAX2 9000000000000000000

std::vector<std::pair<long long, long long>> segtree(MAX * 2, std::pair<long long, long long>(MAX2, 0)); // 구간 최소, 구간 총 개수
std::vector<long long> lazy(MAX * 2, 0);

std::pair<long long, long long> sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);
void insert_lazy(int left, int right, int point);
void insert_range(int start, int end, int left, int right, int point, long long num);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		int temp;
		std::cin >> temp;
		insert(i, temp);
	}

	for (int i = 0; i < m; i++) {
		std::string temp;
		std::cin >> temp;

		if (temp == "P") {
			int start, end;
			long long num;
			std::cin >> start >> end >> num;
			insert_range(start, end, 0, MAX - 1, 1, num);
		}
		if (temp == "M") {
			int start, end;
			std::cin >> start >> end;
			std::cout << sum_tree(start, end, 0, MAX - 1, 1).first << "\n";
		}
		if (temp == "S") {
			int start, end;
			std::cin >> start >> end;
			std::cout << sum_tree(start, end, 0, MAX - 1, 1).second << "\n";
		}
	}
}

void insert(int index, long long num) {
	int point = MAX + index;
	segtree[point].first = num;
	segtree[point].second = num;

	while (point > 0) {
		point /= 2;
		segtree[point].first = std::min(segtree[point * 2].first, segtree[point * 2 + 1].first);
		segtree[point].second += num;
	}
}

void insert_lazy(int left, int right, int point) {
	if (lazy[point] != 0) {
		segtree[point].first += lazy[point];
		segtree[point].second += lazy[point] * (right - left + 1);
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
		segtree[point].first += num;
		segtree[point].second += num * (right - left + 1);
		if (left != right) {
			lazy[point * 2] += num;
			lazy[point * 2 + 1] += num;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point].first = std::min(segtree[point * 2].first, segtree[point * 2 + 1].first);
	segtree[point].second = segtree[point * 2].second + segtree[point * 2 + 1].second;
}

std::pair<long long, long long> sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) {
		return std::pair<long long, long long>(MAX2, 0);
	}
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
	std::pair<long long, long long> left_node = sum_tree(start, end, left, mid, point * 2);
	std::pair<long long, long long> right_node = sum_tree(start, end, mid + 1, right, point * 2 + 1);
	return std::pair<long long, long long>(std::min(left_node.first, right_node.first), left_node.second + right_node.second);
}