#include <iostream>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++) {
		int total_result = 99999999;
		int n, k;
		std::cin >> n >> k;
		std::vector<std::vector<int>> map(2, std::vector<int>(n));
		//0번 -- 1번 -- 2번 -- 3번 -- 4번
		//X 1    X 1    1 1    X 1    1 1
		//X 1    X 2    X 2    2 2    2 2

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				std::cin >> map[i][j];
			}
		}

		// 예외처리
		if (n == 1) {
			if (map[0][0] + map[1][0] <= k) std::cout << "1\n";
			else std::cout << "2\n";
			continue;
		}

		// 유형 0번과 1번일 때, DP
		std::vector<std::vector<int>> dp(n, std::vector<int>(5, 99999999));
		if (map[0][0] + map[1][0] <= k) dp[0][0] = 1;
		dp[0][1] = 2;

		//dp 시작
		for (int i = 1; i < n; i++) {
			//유형 0번
			if (map[0][i] + map[1][i] <= k) {
				int min = 999999999;
				for (int j = 0; j < 5; j++) {
					min = std::min(min, dp[i - 1][j]);
				}
				dp[i][0] = min + 1;
			}

			//유형 1번
			int min = 999999999;
			for (int j = 0; j < 5; j++) {
				min = std::min(min, dp[i - 1][j]);
			}
			dp[i][1] = min + 2;

			//유형 2번
			if (map[0][i - 1] + map[0][i] <= k) {
				dp[i][2] = std::min(dp[i - 1][1] + 1, dp[i - 1][3] + 1);
			}

			//유형 3번
			if (map[1][i - 1] + map[1][i] <= k) {
				dp[i][3] = std::min(dp[i - 1][1] + 1, dp[i - 1][2] + 1);
			}

			//유형 4번
			if (map[0][i - 1] + map[0][i] <= k && map[1][i - 1] + map[1][i] <= k) {
				dp[i][4] = dp[i - 1][1];
			}
		}

		int result = 99999999;
		for (int i = 0; i < 5; i++) result = std::min(result, dp[n - 1][i]);
		total_result = std::min(total_result, result);

		//유형 2번 DP
		if (map[0][0] + map[0][n - 1] <= k) {
			std::vector<std::vector<int>> dp(n, std::vector<int>(5, 99999999));
			dp[0][2] = 2;

			//dp 시작
			for (int i = 1; i < n - 1; i++) {
				//유형 0번
				if (map[0][i] + map[1][i] <= k) {
					int min = 999999999;
					for (int j = 0; j < 5; j++) {
						min = std::min(min, dp[i - 1][j]);
					}
					dp[i][0] = min + 1;
				}

				//유형 1번
				int min = 999999999;
				for (int j = 0; j < 5; j++) {
					min = std::min(min, dp[i - 1][j]);
				}
				dp[i][1] = min + 2;

				//유형 2번
				if (map[0][i - 1] + map[0][i] <= k) {
					dp[i][2] = std::min(dp[i - 1][1] + 1, dp[i - 1][3] + 1);
				}

				//유형 3번
				if (map[1][i - 1] + map[1][i] <= k) {
					dp[i][3] = std::min(dp[i - 1][1] + 1, dp[i - 1][2] + 1);
				}

				//유형 4번
				if (map[0][i - 1] + map[0][i] <= k && map[1][i - 1] + map[1][i] <= k) {
					dp[i][4] = dp[i - 1][1];
				}
			}
			//마지막칸 처리
			if (map[1][n - 2] + map[1][n - 1] <= k) {
				//n - 2 유형이 1번과 2번의 경우 묶을 수 있음
				dp[n - 2][1]--;
				dp[n - 2][2]--;
			}

			int result = 99999999;
			for (int i = 0; i < 5; i++) result = std::min(result, dp[n - 2][i] + 1);
			total_result = std::min(total_result, result);
		}

		//유형 3번 DP
		if (map[1][0] + map[1][n - 1] <= k) {
			std::vector<std::vector<int>> dp(n, std::vector<int>(5, 99999999));
			dp[0][3] = 2;

			//dp 시작
			for (int i = 1; i < n - 1; i++) {
				//유형 0번
				if (map[0][i] + map[1][i] <= k) {
					int min = 999999999;
					for (int j = 0; j < 5; j++) {
						min = std::min(min, dp[i - 1][j]);
					}
					dp[i][0] = min + 1;
				}

				//유형 1번
				int min = 999999999;
				for (int j = 0; j < 5; j++) {
					min = std::min(min, dp[i - 1][j]);
				}
				dp[i][1] = min + 2;

				//유형 2번
				if (map[0][i - 1] + map[0][i] <= k) {
					dp[i][2] = std::min(dp[i - 1][1] + 1, dp[i - 1][3] + 1);
				}

				//유형 3번
				if (map[1][i - 1] + map[1][i] <= k) {
					dp[i][3] = std::min(dp[i - 1][1] + 1, dp[i - 1][2] + 1);
				}

				//유형 4번
				if (map[0][i - 1] + map[0][i] <= k && map[1][i - 1] + map[1][i] <= k) {
					dp[i][4] = dp[i - 1][1];
				}
			}
			//마지막칸 처리
			if (map[0][n - 2] + map[0][n - 1] <= k) {
				//n - 2 유형이 1번과 3번의 경우 묶을 수 있음
				dp[n - 2][1]--;
				dp[n - 2][3]--;
			}

			int result = 99999999;
			for (int i = 0; i < 5; i++) result = std::min(result, dp[n - 2][i] + 1);
			total_result = std::min(total_result, result);
		}

		//유형 4번 DP
		if (map[0][0] + map[0][n - 1] <= k && map[1][0] + map[1][n - 1] <= k) {
			std::vector<std::vector<int>> dp(n, std::vector<int>(5, 99999999));
			dp[0][4] = 2;

			//dp 시작
			for (int i = 1; i < n - 1; i++) {
				//유형 0번
				if (map[0][i] + map[1][i] <= k) {
					int min = 999999999;
					for (int j = 0; j < 5; j++) {
						min = std::min(min, dp[i - 1][j]);
					}
					dp[i][0] = min + 1;
				}

				//유형 1번
				int min = 999999999;
				for (int j = 0; j < 5; j++) {
					min = std::min(min, dp[i - 1][j]);
				}
				dp[i][1] = min + 2;

				//유형 2번
				if (map[0][i - 1] + map[0][i] <= k) {
					dp[i][2] = std::min(dp[i - 1][1] + 1, dp[i - 1][3] + 1);
				}

				//유형 3번
				if (map[1][i - 1] + map[1][i] <= k) {
					dp[i][3] = std::min(dp[i - 1][1] + 1, dp[i - 1][2] + 1);
				}

				//유형 4번
				if (map[0][i - 1] + map[0][i] <= k && map[1][i - 1] + map[1][i] <= k) {
					dp[i][4] = dp[i - 1][1];
				}
			}

			int result = 99999999;
			for (int i = 0; i < 5; i++) result = std::min(result, dp[n - 2][i]);
			total_result = std::min(total_result, result);
		}

		std::cout << total_result <<"\n";
	}
}