#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#define MAX 131072

int max;

class query {
public:
	int start, end, index;

	bool operator<(const query& other) {
		int sqrt_n = sqrt(max);
		int a_start = this->start / sqrt_n;
		int b_start = other.start / sqrt_n;

		if (a_start != b_start) {
			return a_start < b_start;
		}
		else {
			if (a_start % 2 == 0) {
				return this->end < other.end;
			}
			else {
				return this->end > other.end;
			}
		}
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m, k, sqrt_n;
	int left, right;

	std::cin >> n >> k;
	std::vector<std::pair<int, int>> ori_vec(n + 1);
	std::vector<int> vec(n + 1);

	sqrt_n = std::sqrt(n);
	std::vector<int> original((sqrt_n + 1) * (sqrt_n + 1) + 1);
	std::vector<int> sqrt_vec(sqrt_n + 1);
	max = n;

	int count = 0;
	for (int i = 1; i <= n; i++) {
		int temp;
		std::cin >> temp;
		ori_vec[i].first = (ori_vec[i - 1].first + temp) % k;
		ori_vec[i].second = i;
	}

	// 좌표 압축
	std::sort(ori_vec.begin(), ori_vec.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.first < b.first;
		});

	int current = ori_vec[0].first;
	int point = 0;
	for (int i = 1; i <= n; i++) {
		if (ori_vec[i].first != current) point++;
		current = ori_vec[i].first;
		ori_vec[i].first = point;
	}

	std::sort(ori_vec.begin(), ori_vec.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.second < b.second;
		});

	for (int i = 1; i <= n; i++) {
		vec[i] = ori_vec[i].first;
	}


	std::vector<std::deque<int>> counting(n + 1);

	std::cin >> m;

	std::vector<query> q_vec(m);
	std::vector<int> res(m);

	for (int i = 0; i < m; i++) {
		std::cin >> q_vec[i].start >> q_vec[i].end;
		q_vec[i].start--;
		q_vec[i].index = i;
	}

	std::sort(q_vec.begin(), q_vec.end());

	left = 1;
	right = 0;

	for (int i = 0; i < m; i++) {
		while (left > q_vec[i].start) {
			left--;
			std::deque<int>& target = counting[vec[left]];
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]--;
				sqrt_vec[sqrt_num]--;
			}
			target.push_front(left);
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]++;
				sqrt_vec[sqrt_num]++;
			}
		}

		while (right < q_vec[i].end) {
			right++;
			std::deque<int>& target = counting[vec[right]];
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]--;
				sqrt_vec[sqrt_num]--;
			}
			target.push_back(right);
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]++;
				sqrt_vec[sqrt_num]++;
			}
		}

		while (left < q_vec[i].start) {
			std::deque<int>& target = counting[vec[left]];
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]--;
				sqrt_vec[sqrt_num]--;
			}
			target.pop_front();
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]++;
				sqrt_vec[sqrt_num]++;
			}
			left++;
		}

		while (right > q_vec[i].end) {
			std::deque<int>& target = counting[vec[right]];
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]--;
				sqrt_vec[sqrt_num]--;
			}
			target.pop_back();
			if (target.size() >= 2) {
				int num = target.back() - target.front();
				int sqrt_num = std::sqrt(num);
				original[num]++;
				sqrt_vec[sqrt_num]++;
			}
			right--;
		}

		for (int j = sqrt_n; j >= 0; j--) {
			if (res[q_vec[i].index] != 0) break;
			if (sqrt_vec[j] == 0) continue;
			for (int u = (j + 1) * (j + 1); u >= j * j; u--) {
				if (original[u]) {
					res[q_vec[i].index] = u;
					break;
				}
			}
		}
	}

	for (int i = 0; i < m; i++) {
		std::cout << res[i] << "\n";
	}
}