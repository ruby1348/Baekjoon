#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 131072
#define MIN -9000000000000000000

class node {
public:
	long long left = MIN;
	long long right = MIN;
	long long max = MIN;
	long long sum = 0;
};

std::vector<node> segtree(MAX * 2);

node sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);

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
		int start, end;
		std::cin >> start >> end;
		node result = sum_tree(start, end, 0, MAX - 1, 1);
		std::cout << result.max << "\n";
	}
}

void insert(int index, long long num) {
	int point = index + MAX;

	segtree[point].left = num;
	segtree[point].right = num;
	segtree[point].max = num;
	segtree[point].sum = num;
	while (point > 1) {
		point /= 2;
		segtree[point].sum = segtree[point * 2].sum + segtree[point * 2 + 1].sum;
		segtree[point].left = std::max(segtree[point * 2].left, segtree[point * 2].sum + segtree[point * 2 + 1].left);
		segtree[point].right = std::max(segtree[point * 2 + 1].right, segtree[point * 2 + 1].sum + segtree[point * 2].right);
		segtree[point].max = std::max({ segtree[point * 2].max, segtree[point * 2 + 1].max, segtree[point * 2].right + segtree[point * 2 + 1].left });
	}
}

node sum_tree(int start, int end, int left, int right, int point) {
	if (left > end || right < start) {
		node temp;
		return temp;
	}
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
	node left_node = sum_tree(start, end, left, mid, point * 2);
	node right_node = sum_tree(start, end, mid + 1, right, point * 2 + 1);
	node temp;

	temp.sum = left_node.sum + right_node.sum;
	temp.left = std::max(left_node.left, left_node.sum + right_node.left);
	temp.right = std::max(right_node.right, right_node.sum + left_node.right);
	temp.max = std::max({ left_node.max, right_node.max, left_node.right + right_node.left });
	return temp;
}