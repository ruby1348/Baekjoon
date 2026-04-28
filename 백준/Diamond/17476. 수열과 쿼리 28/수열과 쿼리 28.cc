#include <iostream>
#include <vector>
#include <cmath>
#define MAX 131072

class node {
public:
	long long sum, lazy;
	long long max = -1e9;
	long long min = 1e9;

	node() {
		sum = 0; lazy = 0; max = 0; min = 0;
	};
};

std::vector<node> segtree(MAX * 2);

long long sum_tree(int start, int end, int left, int right, int point);
void update_node(int point);
void insert(int index, long long num);
void insert_lazy(int point, int left, int right);
void insert_range(int start, int end, int left, int right, int point, long long num);
void insert_range2(int start, int end, int left, int right, int point);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n;

	for (int i = 1; i <= n; i++) {
		int temp;
		std::cin >> temp;
		insert(i, temp);
	}

	std::cin >> m;

	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;

		if (temp == 1) {
			int start, end;
			long long num;
			std::cin >> start >> end >> num;
			insert_range(start, end, 0, MAX - 1, 1, num);
		}
		if (temp == 2) {
			int start, end;
			std::cin >> start >> end;
			insert_range2(start, end, 0, MAX - 1, 1);
		}
		if (temp == 3) {
			int start, end;
			std::cin >> start >> end;
			std::cout << sum_tree(start, end, 0, MAX - 1, 1) << "\n";
			/*
			for (int i = start; i <= end; i++) {
				std::cout << sum_tree(i, i, 0, MAX - 1, 1) << " ";
			} std::cout << "\n";
			*/
		}
	}
}

void insert(int index, long long num) {
	int point = index + MAX;

	segtree[point].max = num;
	segtree[point].min = num;
	segtree[point].sum = num;
	while (point > 0) {
		point /= 2;
		update_node(point);
	}
}

void update_node(int point) {
	if (point >= MAX) return;
	node& left = segtree[point * 2];
	node& right = segtree[point * 2 + 1];
	segtree[point].sum = left.sum + right.sum;

	segtree[point].max = std::max(left.max, right.max);
	segtree[point].min = std::min(left.min, right.min);
}

void insert_lazy(int point, int left, int right) {
	if (segtree[point].lazy == 0) return;
	long long lazy = segtree[point].lazy;
	int mid = (left + right) / 2;
	if (point < MAX) {
		segtree[point * 2].lazy += lazy;
		segtree[point * 2].sum += lazy * (mid - left + 1);
		segtree[point * 2].max += lazy;;
		segtree[point * 2].min += lazy;
		segtree[point * 2 + 1].lazy += lazy;
		segtree[point * 2 + 1].sum += lazy * (right - mid);
		segtree[point * 2 + 1].max += lazy;
		segtree[point * 2 + 1].min += lazy;
	}

	segtree[point].lazy = 0;
}

void insert_range(int start, int end, int left, int right, int point, long long num) {
	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point].lazy += num;
		segtree[point].sum += num * (right - left + 1);
		segtree[point].max += num;
		segtree[point].min += num;
		return;
	}

	int mid = (left + right) / 2;
	insert_lazy(point, left, right);
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	update_node(point);
}

void insert_range2(int start, int end, int left, int right, int point) {
	if (left > end || right < start) return;
	insert_lazy(point, left, right);
	if (start <= left && end >= right) {
		if(segtree[point].max - (long long)std::sqrt(segtree[point].max) == segtree[point].min - (long long)std::sqrt(segtree[point].min)){
			long long lazy = (long long)std::sqrt(segtree[point].max) - segtree[point].max;
			segtree[point].lazy += lazy;
			segtree[point].sum += lazy * (right - left + 1);
			segtree[point].max += lazy;
			segtree[point].min += lazy;
			return;
		}
	}

	int mid = (left + right) / 2;
	insert_range2(start, end, left, mid, point * 2);
	insert_range2(start, end, mid + 1, right, point * 2 + 1);
	update_node(point);
}

long long sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(point, left, right);
	update_node(point);
	if (left > end || right < start) return 0;
	if (start <= left && end >= right) return segtree[point].sum;

	int mid = (left + right) / 2;
	return sum_tree(start, end, left, mid, point * 2) + sum_tree(start, end, mid + 1, right, point * 2 + 1);
}