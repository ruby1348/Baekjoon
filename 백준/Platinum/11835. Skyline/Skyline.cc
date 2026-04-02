#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n;
	std::cin >> n;
	std::vector<int> vec(n);
	std::vector<std::vector<int>> dp(n, std::vector<int>(3));
	// 0 : 3개
	// 1 : 2개
	// 2 : 1개
	for (int i = 0; i < n; i++) std::cin >> vec[i];

	for (int i = 0; i < n - 2; i++) {
		// 2개 -> 3개 -> 1개
		if (vec[i + 1] > vec[i + 2] && vec[i + 1] > vec[i]) {
			dp[i + 1][1] = std::min(vec[i + 1] - vec[i + 2], vec[i]);
			vec[i] -= dp[i + 1][1];
			vec[i + 1] -= dp[i + 1][1];
			dp[i + 2][0] = std::min(vec[i], std::min(vec[i + 1], vec[i + 2]));
			vec[i] -= dp[i + 2][0];
			vec[i + 1] -= dp[i + 2][0];
			vec[i + 2] -= dp[i + 2][0];
			dp[i][2] = vec[i];
		}
		// 3개 -> 2개 -> 1개
		else {
			dp[i + 2][0] = std::min(vec[i], std::min(vec[i + 1], vec[i + 2]));
			vec[i] -= dp[i + 2][0];
			vec[i + 1] -= dp[i + 2][0];
			vec[i + 2] -= dp[i + 2][0];
			dp[i + 1][1] = std::min(vec[i], vec[i + 1]);
			vec[i] -= dp[i + 1][1];
			vec[i + 1] -= dp[i + 1][1];
			dp[i][2] = vec[i];
		}
	}

	if (n > 1) {
		dp[n - 1][1] = std::min(vec[n - 1], vec[n - 2]);
		vec[n - 1] -= dp[n - 1][1];
		vec[n - 2] -= dp[n - 1][1];
		dp[n - 2][2] = vec[n - 2];
	}
	dp[n - 1][2] = vec[n - 1];

	int result = 0;
	for (int i = 0; i < n; i++) {
		result += dp[i][0] * 7 + dp[i][1] * 5 + dp[i][2] * 3;
		//std::cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << "\n";
	}
	std::cout << result;
}