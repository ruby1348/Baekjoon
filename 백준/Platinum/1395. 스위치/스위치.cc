#include <iostream>
#include <vector>
#define MAX 131072

std::vector<long long> segtree(MAX * 2, 0);
std::vector<long long> lazy(MAX * 2, 0);

long long sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);
void insert_lazy(int left, int right, int point);
void insert_range(int start, int end, int left, int right, int point, long long num);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;

		if (temp == 0) {
			int start, end;
			std::cin >> start >> end;
			insert_range(start, end, 0, MAX - 1, 1, 1);
		}
		if (temp == 1) {
			int start, end;
			std::cin >> start >> end;
			std::cout << sum_tree(start, end, 0, MAX - 1, 1) << "\n";
		}
	}
}

void insert(int index, long long num) {
	int point = index + MAX;

	segtree[point] = num;
	while (point > 0) {
		point /= 2;
		segtree[point] = segtree[point * 2] ^ segtree[point * 2 + 1];
	}
}

void insert_lazy(int left, int right, int point) {
	if (lazy[point] != 0) {
		segtree[point] = std::abs(segtree[point] - (right - left + 1));
		if (left != right) {
			lazy[point * 2] ^= 1;
			lazy[point * 2 + 1] ^= 1;
		}
		lazy[point] = 0;
	}
}

void insert_range(int start, int end, int left, int right, int point, long long num) {
	insert_lazy(left, right, point);

	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point] = std::abs(segtree[point] - (right - left + 1));
		if (left != right) {
			lazy[point * 2] ^= 1;
			lazy[point * 2 + 1] ^= 1;
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