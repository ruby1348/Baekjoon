#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX 10001

class query {
public:
	int start, end, index;

	bool operator<(const query& other) {
		int sqrt_n = sqrt(MAX);
		int a_start = this->start / sqrt_n;
		int b_start = other.start / sqrt_n;

		if (a_start == b_start) {
			return this->end < other.end;
		}
		else return a_start < b_start;
	}
};

int compare(const void* a, const void* b);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m, c;
	int left, right;

	std::cin >> n >> c;

	std::vector<int> counting(MAX);
	std::vector<int> vec(n + 1);

	for (int i = 1; i <= n; i++) {
		std::cin >> vec[i];
	}

	std::cin >> m;
	std::vector<query> q_vec(m);
	std::vector<int> res(m);

	for (int i = 0; i < m; i++) {
		std::cin >> q_vec[i].start >> q_vec[i].end;
		q_vec[i].index = i;
	}

	std::sort(q_vec.begin(), q_vec.end());

	left = 1;
	right = 1;
	counting[vec[1]]++;

	for (int i = 0; i < m; i++) {

		while (left < q_vec[i].start) {
			counting[vec[left]]--;
			left++;
		}

		while (right > q_vec[i].end) {
			counting[vec[right]]--;
			right--;
		}

		while (left > q_vec[i].start) {
			left--;
			counting[vec[left]]++;
		}

		while (right < q_vec[i].end) {
			right++;
			counting[vec[right]]++;
		}

		int max_index = 0;
		for (int j = 1; j <= c; j++) {
			if (counting[j] > counting[max_index]) max_index = j;
		}

		if (counting[max_index] > (right - left + 1) / 2) res[q_vec[i].index] = max_index;
	}

	for (int i = 0; i < m; i++) {
		if (res[i]) std::cout << "yes " << res[i] << "\n";
		else std::cout << "no\n";
	}
}