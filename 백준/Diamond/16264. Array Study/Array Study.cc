#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#define MAX 1000001

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

	int t;
	std::cin >> t;
	for (int T = 0; T < t; T++) {
		long long sum = 0;
		int n, m, k, sqrt_n;
		int left, right;

		std::cin >> n;
		std::vector<int> vec(n + 2);
		std::vector<std::deque<int>> counting(n * 2 + 1);

		sqrt_n = std::sqrt(n * 2);
		std::vector<int> original((sqrt_n + 1) * (sqrt_n + 1) + 1);
		std::vector<int> sqrt_vec(sqrt_n + 1);
		max = n;

		vec[0] = n;
		for (int i = 1; i <= n; i++) {
			int temp;
			std::cin >> temp;
			vec[i] += vec[i - 1] + temp;
		}

		std::cin >> m;

		std::vector<query> q_vec(m);

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

			bool is_result = false;
			for (int j = sqrt_n; j >= 0; j--) {
				if (is_result) break;
				if (sqrt_vec[j] == 0) continue;
				for (int u = (j + 1) * (j + 1); u >= j * j; u--) {
					if (original[u]) {
						sum += u;
						is_result = true;
						break;
					}
				}
			}
		}

		std::cout << sum << "\n";
	}
}