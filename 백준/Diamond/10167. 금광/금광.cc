#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 4096
#define MIN -4000000000000000000

class node {
public:
	long long left = MIN;
	long long right = MIN;
	long long max = MIN;
	long long sum = 0;
};

class Mine {
public:
	int x;
	int y;
	long long w;
};

std::vector<node> segtree(MAX * 2);

node sum_tree(int start, int end, int left, int right, int point);
void insert(int index, long long num);
void insert_init(int index);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n;
	std::cin >> n;

	std::vector<Mine> vec;

	for (int i = 0; i < n; i++) {
		Mine temp;
		std::cin >> temp.x >> temp.y >> temp.w;
		vec.push_back(temp);
	}

	std::sort(vec.begin(), vec.end(), [](const Mine& a, const Mine& b) { return a.x < b.x; });

	//x 좌표 정렬
	int current_x = -1000000001;
	int count_x = -1;
	for (int i = 0; i < n; i++) {
		if (vec[i].x == current_x) {
			vec[i].x = count_x;
			continue;
		}
		current_x = vec[i].x;
		vec[i].x = ++count_x;
	}

	std::sort(vec.begin(), vec.end(), [](const Mine& a, const Mine& b) { return a.y < b.y; });

	//y 좌표 정렬
	int current_y = -1000000001;
	int count_y = -1;
	for (int i = 0; i < n; i++) {
		if (vec[i].y == current_y) {
			vec[i].y = count_y;
			continue;
		}
		current_y = vec[i].y;
		vec[i].y = ++count_y;
	}

	long long max = 0;
	for (int i = 0; i < n; i++) {
		int current_y = -1000000001;

		// 이전 y 좌표가 같은 경우 최댓값 갱신 X
		if (i > 0 && vec[i].y == vec[i - 1].y) continue;

		for (int j = i; j < n; j++) {
			insert(vec[j].x, vec[j].w);
			// 다음 y 좌표가 같은 경우 최댓값 갱신 X 
			if (j + 1 < n && vec[j].y == vec[j + 1].y) continue;
			max = std::max(sum_tree(0, MAX - 1, 0, MAX - 1, 1).max, max);
		}

		// 세그트리 초기화
		for (int j = i; j < n; j++) {
			insert_init(vec[j].x);
		}
	}

	std::cout << max;
}

void insert(int index, long long num) {
	int point = index + MAX;

	if (segtree[point].left == MIN) segtree[point].left = 0;
	if (segtree[point].right == MIN) segtree[point].right = 0;
	if (segtree[point].max == MIN) segtree[point].max = 0;
	segtree[point].left += num;
	segtree[point].right += num;
	segtree[point].max += num;
	segtree[point].sum += num;
	while (point > 1) {
		point /= 2;
		segtree[point].sum = segtree[point * 2].sum + segtree[point * 2 + 1].sum;
		segtree[point].left = std::max(segtree[point * 2].left, segtree[point * 2].sum + segtree[point * 2 + 1].left);
		segtree[point].right = std::max(segtree[point * 2 + 1].right, segtree[point * 2 + 1].sum + segtree[point * 2].right);
		segtree[point].max = std::max({ segtree[point * 2].max, segtree[point * 2 + 1].max, segtree[point * 2].right + segtree[point * 2 + 1].left });
	}
}

void insert_init(int index) {
	int point = index + MAX;

	segtree[point].left = MIN;
	segtree[point].right = MIN;
	segtree[point].max = MIN;
	segtree[point].sum = 0;
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