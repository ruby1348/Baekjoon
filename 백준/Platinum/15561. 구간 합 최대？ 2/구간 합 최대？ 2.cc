#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 131072
#define MIN -1000000000

class node {
public:
	long long left = MIN;
	long long left_num = 0;
	long long right = MIN;
	long long right_num = 0;
	long long max = MIN;
	long long max_num = 0;
	long long sum = 0;
	long long sum_num = 0;
};

std::vector<node> segtree(MAX * 2);

long long u, v;

node sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m >> u >> v;

	for (int i = 1; i <= n; i++) {
		int temp;
		std::cin >> temp;
		insert(i, temp);
	}

	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;

		if (temp == 0) {
			int start, end;
			std::cin >> start >> end;
			node result = sum_tree(start, end, 0, MAX - 1, 1);
			std::cout << result.max * u + (result.max_num - 1) * v << "\n";
		}
		if (temp == 1) {
			int index, num;
			std::cin >> index >> num;
			insert(index, num);
		}
	}
}

void insert(int index, long long num) {
	int point = index + MAX;

	segtree[point].left = num;
	segtree[point].left_num = 1;
	segtree[point].right = num;
	segtree[point].right_num = 1;
	segtree[point].max = num;
	segtree[point].max_num = 1;
	segtree[point].sum = num;
	segtree[point].sum_num = 1;
	while (point > 1) {
		point /= 2;

		node left_node = segtree[point * 2];
		node right_node = segtree[point * 2 + 1];
		segtree[point].sum = left_node.sum + right_node.sum;
		segtree[point].sum_num = left_node.sum_num + right_node.sum_num;

		//왼쪽
		if (left_node.left * u + (left_node.left_num - 1) * v > (left_node.sum + right_node.left) * u + (left_node.sum_num + right_node.left_num - 1) * v) {
			segtree[point].left = left_node.left;
			segtree[point].left_num = left_node.left_num;
		}
		else {
			segtree[point].left = left_node.sum + right_node.left;
			segtree[point].left_num = left_node.sum_num + right_node.left_num;
		}

		//오른쪽
		if (right_node.right * u + (right_node.right_num - 1) * v > (left_node.right + right_node.sum) * u + (left_node.right_num + right_node.sum_num - 1) * v) {
			segtree[point].right = right_node.right;
			segtree[point].right_num = right_node.right_num;
		}
		else {
			segtree[point].right = left_node.right + right_node.sum;
			segtree[point].right_num = left_node.right_num + right_node.sum_num;
		}

		//최종
		if (left_node.max * u + (left_node.max_num - 1) * v > right_node.max * u + (right_node.max_num - 1) * v) {
			segtree[point].max = left_node.max;
			segtree[point].max_num = left_node.max_num;
		}
		else {
			segtree[point].max = right_node.max;
			segtree[point].max_num = right_node.max_num;
		}

		if ((left_node.right + right_node.left) * u + (left_node.right_num + right_node.left_num - 1) * v > segtree[point].max * u + (segtree[point].max_num - 1) * v) {
			segtree[point].max = left_node.right + right_node.left;
			segtree[point].max_num = left_node.right_num + right_node.left_num;
		}
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

	if (left_node.sum_num == 0) return right_node;
	if (right_node.sum_num == 0) return left_node;

	temp.sum = left_node.sum + right_node.sum;
	temp.sum_num = left_node.sum_num + right_node.sum_num;

	//왼쪽
	if (left_node.left * u + (left_node.left_num - 1) * v > (left_node.sum + right_node.left) * u + (left_node.sum_num + right_node.left_num - 1) * v) {
		temp.left = left_node.left;
		temp.left_num = left_node.left_num;
	}
	else {
		temp.left = left_node.sum + right_node.left;
		temp.left_num = left_node.sum_num + right_node.left_num;
	}

	//오른쪽
	if (right_node.right * u + (right_node.right_num - 1) * v > (left_node.right + right_node.sum) * u + (left_node.right_num + right_node.sum_num - 1) * v) {
		temp.right = right_node.right;
		temp.right_num = right_node.right_num;
	}
	else {
		temp.right = left_node.right + right_node.sum;
		temp.right_num = left_node.right_num + right_node.sum_num;
	}

	//최종
	if (left_node.max * u + (left_node.max_num - 1) * v > right_node.max * u + (right_node.max_num - 1) * v) {
		temp.max = left_node.max;
		temp.max_num = left_node.max_num;
	}
	else {
		temp.max = right_node.max;
		temp.max_num = right_node.max_num;
	}

	if ((left_node.right + right_node.left) * u + (left_node.right_num + right_node.left_num - 1) * v > temp.max * u + (temp.max_num - 1) * v) {
		temp.max = left_node.right + right_node.left;
		temp.max_num = left_node.right_num + right_node.left_num;
	}
	return temp;
}