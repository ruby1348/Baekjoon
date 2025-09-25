#include <iostream>
#include <vector>
#define MAX 1048576

std::vector<long long> segtree(MAX * 2, 0);

long long sum_tree(int start, int end, int left, int right, int point);
void insert(int point, int num);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;

        if(temp == 0){
            int left, right;
            std::cin >> left >> right;
            if(left > right) std::swap(left, right);
            std::cout << sum_tree(left, right, 0, MAX - 1, 1) << "\n";
        }
        if(temp == 1){
            int index, val;
            std::cin >> index >> val;
            insert(index, val - segtree[index + MAX]);
        }
	}
}

void insert(int index, int num) {
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