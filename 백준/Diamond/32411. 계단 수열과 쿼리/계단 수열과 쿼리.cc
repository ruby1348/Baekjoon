#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 131072
#define MIN 1

class node {
public:
	long long left = MIN;
	long long right = MIN;
	long long max = MIN;
};

class Node {
public:
	std::vector<node> vec;
	int left = MAX;
	int right = -MAX;
	int sum = 0;

	Node() {
		vec.resize(11);
	}
};

std::vector<Node> segtree(MAX * 2);
std::vector<int> lazy(MAX * 2);

void insert(int index, int num);
void insert_range(int start, int end, int left, int right, int point, long long num);
void insert_lazy(int left, int right, int point);
Node sum_tree(int start, int end, int left, int right, int point);

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
		int temp, start, end, k;
		std::cin >> temp >> start >> end >> k;
		if (temp == 1) {
			insert_range(start, end, 0, MAX - 1, 1, k);
		}
		if (temp == 2) {
			Node temp = sum_tree(start, end, 0, MAX - 1, 1);
			std::cout << temp.vec[k].max << "\n";
		}
	}
}

void insert(int index, int num) {
	int point = index + MAX;

	for (int i = 1; i <= 10; i++) {
		segtree[point].vec[i].left = 1;
		segtree[point].vec[i].right = 1;
		segtree[point].vec[i].max = 1;
	}
	segtree[point].left = num;
	segtree[point].right = num;
	segtree[point].sum = 1;

	while (point > 1) {
		point /= 2;
		segtree[point].left = segtree[point * 2].left;
		segtree[point].right = segtree[point * 2 + 1].right;
		segtree[point].sum = segtree[point * 2].sum + segtree[point * 2 + 1].sum;

		for (int i = 1; i <= 10; i++) {
			segtree[point].vec[i].left = segtree[point * 2].vec[i].left;
			segtree[point].vec[i].right = segtree[point * 2 + 1].vec[i].right;
			if (std::abs(segtree[point * 2].right - segtree[point * 2 + 1].left) == i) {
				if (segtree[point * 2].vec[i].left == segtree[point * 2].sum) segtree[point].vec[i].left = segtree[point * 2].vec[i].left + segtree[point * 2 + 1].vec[i].left;
				if (segtree[point * 2 + 1].vec[i].right == segtree[point * 2 + 1].sum) segtree[point].vec[i].right = segtree[point * 2].vec[i].right + segtree[point * 2 + 1].vec[i].right;
				segtree[point].vec[i].max = segtree[point * 2].vec[i].right + segtree[point * 2 + 1].vec[i].left;
			}
			segtree[point].vec[i].max = std::max({ segtree[point * 2].vec[i].max, segtree[point * 2 + 1].vec[i].max, segtree[point].vec[i].max });
		}
	}
}

void insert_range(int start, int end, int left, int right, int point, long long num) {
	insert_lazy(left, right, point);

	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point].left += num;
		segtree[point].right += num;
		if (left != right) {
			lazy[point * 2] += num;
			lazy[point * 2 + 1] += num;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point].left = segtree[point * 2].left;
	segtree[point].right = segtree[point * 2 + 1].right;

	for (int i = 1; i <= 10; i++) {
		segtree[point].vec[i].left = segtree[point * 2].vec[i].left;
		segtree[point].vec[i].right = segtree[point * 2 + 1].vec[i].right;
		segtree[point].vec[i].max = MIN;
		if (std::abs(segtree[point * 2].right - segtree[point * 2 + 1].left) == i) {
			if (segtree[point * 2].vec[i].left == segtree[point * 2].sum) segtree[point].vec[i].left = segtree[point * 2].vec[i].left + segtree[point * 2 + 1].vec[i].left;
			if (segtree[point * 2 + 1].sum == segtree[point * 2 + 1].vec[i].right) segtree[point].vec[i].right = segtree[point * 2].vec[i].right + segtree[point * 2 + 1].vec[i].right;
			segtree[point].vec[i].max = std::max({ segtree[point * 2].vec[i].max, segtree[point * 2 + 1].vec[i].max, segtree[point * 2].vec[i].right + segtree[point * 2 + 1].vec[i].left });
		}
		segtree[point].vec[i].max = std::max({ segtree[point * 2].vec[i].max, segtree[point * 2 + 1].vec[i].max, segtree[point].vec[i].max });
	}
}

void insert_lazy(int left, int right, int point) {
	if (lazy[point] != 0) {
		segtree[point].left += lazy[point];
		segtree[point].right += lazy[point];
		if (left != right) {
			lazy[point * 2] += lazy[point];
			lazy[point * 2 + 1] += lazy[point];
		}
		lazy[point] = 0;
	}
}

Node sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) {
		Node temp;
		return temp;
	}
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
	Node left_node = sum_tree(start, end, left, mid, point * 2);
	Node right_node = sum_tree(start, end, mid + 1, right, point * 2 + 1);

	if (left_node.sum == 0) return right_node;
	if (right_node.sum == 0) return left_node;
	Node temp;

	temp.left = left_node.left;
	temp.right = right_node.right;
	temp.sum = left_node.sum + right_node.sum;

	for (int i = 1; i <= 10; i++) {
		temp.vec[i].left = left_node.vec[i].left;
		temp.vec[i].right = right_node.vec[i].right;
		if (std::abs(left_node.right - right_node.left) == i) {
			if (left_node.vec[i].left == left_node.sum) temp.vec[i].left = left_node.vec[i].left + right_node.vec[i].left;
			if (right_node.vec[i].right == right_node.sum) temp.vec[i].right = left_node.vec[i].right + right_node.vec[i].right;
			temp.vec[i].max = left_node.vec[i].right + right_node.vec[i].left;
		}
		temp.vec[i].max = std::max({ left_node.vec[i].max, right_node.vec[i].max, temp.vec[i].max });
	}
	return temp;
}