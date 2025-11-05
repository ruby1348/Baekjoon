#include <iostream>
#include <vector>
#define MAX 2097152
#define MIN 0
std::vector<std::pair<int, int>> lazy(MAX * 2, std::pair<int, int>(MAX, MIN));
//first : uppper, second : lower
void insert_range(int start, int end, int left, int right, int point, int num);
void insert_range2(int start, int end, int left, int right, int point, int num);
void insert_lazy(int left, int right, int point);
void update_tree(int start, int end, int left, int right, int point);
int main() {
	std::ios_base::sync_with_stdio(false);	std::cin.tie(NULL), std::cout.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int temp, start, end, num;
		std::cin >> temp >> start >> end >> num;
		if (temp == 1) insert_range(start, end, 0, MAX - 1, 1, num);
		if (temp == 2) insert_range2(start, end, 0, MAX - 1, 1, num);
	}
	for (int i = 0; i < n; i++) {
		update_tree(i, i, 0, MAX - 1, 1);
		std::cout << lazy[MAX + i].second << "\n";
	}
}
//lower bound
void insert_range(int start, int end, int left, int right, int point, int num) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return;
	if (start <= left && end >= right) {
        lazy[point].second = std::max(lazy[point].second, num);
        lazy[point].first = std::max(lazy[point].first, lazy[point].second);
		if (left != right) {
			lazy[point * 2].second = std::max(lazy[point * 2].second, lazy[point].second);
            lazy[point * 2].first  = std::max(lazy[point * 2].first,  lazy[point].second);
            lazy[point * 2].second = std::min(lazy[point * 2].second, lazy[point].first);
            lazy[point * 2].first  = std::min(lazy[point * 2].first,  lazy[point].first);
			lazy[point * 2 + 1].second = std::max(lazy[point * 2 + 1].second, lazy[point].second);
            lazy[point * 2 + 1].first  = std::max(lazy[point * 2 + 1].first,  lazy[point].second);
            lazy[point * 2 + 1].second = std::min(lazy[point * 2 + 1].second, lazy[point].first);
            lazy[point * 2 + 1].first  = std::min(lazy[point * 2 + 1].first,  lazy[point].first);
            lazy[point].first = MAX;
            lazy[point].second = MIN;
		}
		return;
	}
	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
}
//upper bound
void insert_range2(int start, int end, int left, int right, int point, int num) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		lazy[point].first = std::min(lazy[point].first, num);
		lazy[point].second = std::min(lazy[point].first, lazy[point].second);
		if (left != right) {
            lazy[point * 2].second = std::max(lazy[point * 2].second, lazy[point].second);
            lazy[point * 2].first  = std::max(lazy[point * 2].first,  lazy[point].second);
            lazy[point * 2].second = std::min(lazy[point * 2].second, lazy[point].first);
            lazy[point * 2].first  = std::min(lazy[point * 2].first,  lazy[point].first);
			lazy[point * 2 + 1].second = std::max(lazy[point * 2 + 1].second, lazy[point].second);
            lazy[point * 2 + 1].first  = std::max(lazy[point * 2 + 1].first,  lazy[point].second);
            lazy[point * 2 + 1].second = std::min(lazy[point * 2 + 1].second, lazy[point].first);
            lazy[point * 2 + 1].first  = std::min(lazy[point * 2 + 1].first,  lazy[point].first);
            lazy[point].first = MAX;
            lazy[point].second = MIN;
		}
		return;
	}
	int mid = (left + right) / 2;
	insert_range2(start, end, left, mid, point * 2, num);
	insert_range2(start, end, mid + 1, right, point * 2 + 1, num);
}

void insert_lazy(int left, int right, int point) {
	if (lazy[point].first != MAX || lazy[point].second != MIN) {
		if (left != right) {
			lazy[point * 2].second = std::max(lazy[point * 2].second, lazy[point].second);
            lazy[point * 2].first  = std::max(lazy[point * 2].first,  lazy[point].second);
            lazy[point * 2].second = std::min(lazy[point * 2].second, lazy[point].first);
            lazy[point * 2].first  = std::min(lazy[point * 2].first,  lazy[point].first);
			lazy[point * 2 + 1].second = std::max(lazy[point * 2 + 1].second, lazy[point].second);
            lazy[point * 2 + 1].first  = std::max(lazy[point * 2 + 1].first,  lazy[point].second);
            lazy[point * 2 + 1].second = std::min(lazy[point * 2 + 1].second, lazy[point].first);
            lazy[point * 2 + 1].first  = std::min(lazy[point * 2 + 1].first,  lazy[point].first);
		    lazy[point].first = MAX;
		    lazy[point].second = MIN;
        }
	}
}

void update_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return;
	if (left >= start && right <= end) return;
	int mid = (left + right) / 2;
	update_tree(start, end, left, mid, point * 2);
	update_tree(start, end, mid + 1, right, point * 2 + 1);
}