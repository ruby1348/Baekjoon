#include <iostream>
#include <vector>
#define MAX 131072
#define MOD 1000000007

std::vector<long long> segtree(MAX * 2, 0);
std::vector<long long> lazy(MAX * 2, 0);
std::vector<long long> lazy2(MAX * 2, 1);

void insert(int index, int num);
void insert_range(int start, int end, int left, int right, int point, int num);
void insert_range2(int start, int end, int left, int right, int point, int num);
void insert_range3(int start, int end, int left, int right, int point, int num);
void insert_lazy(int left, int right, int point);
long long sum_tree(int start, int end, int left, int right, int point);

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
		int temp, left, right, var;
		std::cin >> temp >> left >> right;

		if (temp == 1 || temp == 2 || temp == 3) std::cin >> var;

		if (temp == 1) {
			insert_range(left, right, 0, MAX - 1, 1, var);
		}
		if (temp == 2) {
			insert_range2(left, right, 0, MAX - 1, 1, var);
		}
		if (temp == 3) {
			insert_range3(left, right, 0, MAX - 1, 1, var);
		}
		if (temp == 4) {
			std::cout << sum_tree(left, right, 0, MAX - 1, 1) << "\n";
		}
		/*
		for (int i = 1; i <= n; i++) std::cout << sum_tree(i, i, 0, MAX - 1, 1) << " ";
		std::cout << "\n";
		*/
	}
}

void insert(int index, int num) {
	int point = MAX + index;
	segtree[point] = num;

	while (point > 0) {
		point /= 2;
		segtree[point] = (segtree[point] + num) % MOD;
	}
}

void insert_range(int start, int end, int left, int right, int point, int num) {
	insert_lazy(left, right, point);

	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point] = (segtree[point] + (long long)(right - left + 1) * num) % MOD;
		if (left != right) {
			lazy[point * 2] = (lazy[point * 2] + num) % MOD;
			lazy[point * 2 + 1] = (lazy[point * 2 + 1] + num) % MOD;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point] = (segtree[point * 2] + segtree[point * 2 + 1]) % MOD;
}

void insert_range2(int start, int end, int left, int right, int point, int num) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point] = (segtree[point] * num) % MOD;
		if (left != right) {
			lazy2[point * 2] = (lazy2[point * 2] * num) % MOD;
			lazy2[point * 2 + 1] = (lazy2[point * 2 + 1] * num) % MOD;
			lazy[point * 2] = (lazy[point * 2] * num) % MOD;
			lazy[point * 2 + 1] = (lazy[point * 2 + 1] * num) % MOD;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range2(start, end, left, mid, point * 2, num);
	insert_range2(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point] = (segtree[point * 2] + segtree[point * 2 + 1]) % MOD;
}

void insert_range3(int start, int end, int left, int right, int point, int num) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point] = ((long long)num * (right - left + 1)) % MOD;
		if (left != right) {
			lazy2[point * 2] = 0;
			lazy2[point * 2 + 1] = 0;
			lazy[point * 2] = num;
			lazy[point * 2 + 1] = num;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range3(start, end, left, mid, point * 2, num);
	insert_range3(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point] = (segtree[point * 2] + segtree[point * 2 + 1]) % MOD;
}


void insert_lazy(int left, int right, int point) {
	segtree[point] = (segtree[point] * lazy2[point]) % MOD;
	segtree[point] = (segtree[point] + lazy[point] * (right - left + 1)) % MOD;
	if (left != right) {
		lazy2[point * 2] = (lazy2[point * 2] * lazy2[point]) % MOD;
		lazy2[point * 2 + 1] = (lazy2[point * 2 + 1] * lazy2[point]) % MOD;
		lazy[point * 2] = (lazy[point * 2] * lazy2[point]) % MOD;
		lazy[point * 2 + 1] = (lazy[point * 2 + 1] * lazy2[point]) % MOD;
		lazy[point * 2] = (lazy[point * 2] + lazy[point]) % MOD;
		lazy[point * 2 + 1] = (lazy[point * 2 + 1] + lazy[point]) % MOD;
	}

	lazy2[point] = 1;
	lazy[point] = 0;
}

long long sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return 0;
	if (left >= start && right <= end) return segtree[point];

	int mid = (left + right) / 2;
	return (sum_tree(start, end, left, mid, point * 2) + sum_tree(start, end, mid + 1, right, point * 2 + 1)) % MOD;
}