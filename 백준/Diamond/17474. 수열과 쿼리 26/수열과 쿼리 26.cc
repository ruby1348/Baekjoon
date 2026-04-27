#include <iostream>
#include <vector>
#define MAX 1048576

class node {
public:
	long long sum;
	int max1, max2, count;

	node() {
		sum = 0; max1 = -1; max2 = -1; count = 0;
	};
};

std::vector<node> segtree(MAX * 2);

int max_tree(int start, int end, int left, int right, int point);
long long sum_tree(int start, int end, int left, int right, int point);
void update_node(int point);
void insert(int index, long long num);
void insert_lazy(int point);
void insert_range(int start, int end, int left, int right, int point, long long num);

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
			std::cout << max_tree(start, end, 0, MAX - 1, 1) << "\n";
		}
		if (temp == 3) {
			int start, end;
			std::cin >> start >> end;
			std::cout << sum_tree(start, end, 0, MAX - 1, 1) << "\n";
		}
	}
}

void insert(int index, long long num) {
	int point = index + MAX;

	segtree[point].max1 = num;
	segtree[point].max2 = -1;
	segtree[point].sum = num;
	segtree[point].count = 1;
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
	
	if (left.max1 == right.max1) {
		segtree[point].max1 = left.max1;
		segtree[point].max2 = std::max(left.max2, right.max2);
		segtree[point].count = left.count + right.count;
	}
	else if (left.max1 > right.max1) {
		segtree[point].max1 = left.max1;
		segtree[point].max2 = std::max(left.max2, right.max1);
		segtree[point].count = left.count;
	}
	else {
		segtree[point].max1 = right.max1;
		segtree[point].max2 = std::max(left.max1, right.max2);
		segtree[point].count = right.count;
	}
}

void insert_lazy(int point) {
	if (point >= MAX) return;
	node& left = segtree[point * 2];
    node& right = segtree[point * 2 + 1];
	if (left.max1 > segtree[point].max1) {
		left.sum -= (long long)left.count * (left.max1 - segtree[point].max1);
		left.max1 = segtree[point].max1;
	}
	if (right.max1 > segtree[point].max1) {
		right.sum -= (long long)right.count * (right.max1 - segtree[point].max1);
		right.max1 = segtree[point].max1;
	}
}

void insert_range(int start, int end, int left, int right, int point, long long num) {
	if (left > end || right < start || segtree[point].max1 <= num) return;
	if (start <= left && end >= right && segtree[point].max2 < num) {
		segtree[point].sum -= (long long)segtree[point].count * (segtree[point].max1 - num);
		segtree[point].max1 = num;
		return;
	}

	int mid = (left + right) / 2;
	insert_lazy(point);
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	update_node(point);
}

int max_tree(int start, int end, int left, int right, int point) {
	insert_lazy(point);
	if (left > end || right < start) return 0;
	if (start <= left && end >= right) return segtree[point].max1;

	int mid = (left + right) / 2;
	return std::max(max_tree(start, end, left, mid, point * 2), max_tree(start, end, mid + 1, right, point * 2 + 1));
}

long long sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(point);
	if (left > end || right < start) return 0;
	if (start <= left && end >= right) return segtree[point].sum;

	int mid = (left + right) / 2;
	return sum_tree(start, end, left, mid, point * 2) + sum_tree(start, end, mid + 1, right, point * 2 + 1);
}