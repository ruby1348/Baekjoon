#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX 1000001

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

	std::cin >> n >> m;

	std::vector<long long> counting(MAX);
	std::vector<int> vec(n + 1);

	for (int i = 1; i <= n; i++) {
		std::cin >> vec[i];
	}

	std::vector<query> q_vec(m);
	std::vector<long long> res(m);

	for (int i = 0; i < m; i++) {
		std::cin >> q_vec[i].start >> q_vec[i].end;
		q_vec[i].index = i;
	}

	std::sort(q_vec.begin(), q_vec.end());

	long long current = 0;
	left = 1;
	right = 1;
	counting[vec[1]]++;
	current += vec[1];

	for (int i = 0; i < m; i++) {

		while (left < q_vec[i].start) {
			int target = vec[left];
			current -= counting[target] * counting[target] * target;
			counting[target]--;
			current += counting[target] * counting[target] * target;
			left++;
		}

		while (right > q_vec[i].end) {
			int target = vec[right];
			current -= counting[target] * counting[target] * target;
			counting[target]--;
			current += counting[target] * counting[target] * target;
			right--;
		}

		while (left > q_vec[i].start) {
			left--;
			int target = vec[left];
			current -= counting[target] * counting[target] * target;
			counting[target]++;
			current += counting[target] * counting[target] * target;
		}

		while (right < q_vec[i].end) {
			right++;
			int target = vec[right];
			current -= counting[target] * counting[target] * target;
			counting[target]++;
			current += counting[target] * counting[target] * target;
		}

		res[q_vec[i].index] = current;
	}

	for (int i = 0; i < m; i++) std::cout << res[i] << "\n";
}