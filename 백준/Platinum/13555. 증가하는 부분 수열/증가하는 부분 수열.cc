#include <iostream>
#include <vector>
#define MAX 131072
#define MOD 5000000

std::vector<std::vector<int>> segtree;

int sum_tree(int start, int end, int left, int right, int point, int ord);
void insert(int point, int num, int ord);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, k;
	int total = 0;
	std::cin >> n >> k;
    
    segtree.resize(k, std::vector<int>(MAX * 2, 0));

	for (int i = 0; i < n; i++) {
		int temp;
		std::cin >> temp;

		// 원소 개수만큼 만들 수 있는 쌍의 개수 구하고 세그먼트 트리에 넣기
		int sum = 1;
		for (int j = 0; j < k - 1; j++) {
			insert(temp, sum, j);
			sum = sum_tree(0, temp - 1, 0, MAX - 1, 1, j);
		}
		total = (total + sum) % MOD;
	}

	std::cout << total;
}

void insert(int index, int num, int ord) {
	int point = index + MAX;

	segtree[ord][point] = (segtree[ord][point] + num) % MOD;
	while (point > 0) {
		point /= 2;
		segtree[ord][point] = (segtree[ord][point] + num) % MOD;
	}
}

int sum_tree(int start, int end, int left, int right, int point, int ord) {
	if (left > end || right < start) return 0;
	if (start <= left && end >= right) return segtree[ord][point];

	int mid = (left + right) / 2;
	return (sum_tree(start, end, left, mid, point * 2, ord) + sum_tree(start, end, mid + 1, right, point * 2 + 1, ord)) % MOD;
}