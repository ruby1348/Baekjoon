#include <iostream>
#include <vector>
#include <iomanip>

class Line {
public:
	long long m, y;
	Line(long long m, long long y) {
		this->m = m;
		this->y = y;
	}
};

//교차점 구하기
//ax + b = cx + d -> x = (d - b) / (a - c)
long double cross(Line a, Line b) {
	return (long double)(b.y - a.y) / (long double)(a.m - b.m);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, a, b, c;
	std::cin >> n >> a >> b >> c;

	std::vector<long long> sum(n + 1, 0);
	std::vector<long long> dp(n + 1, 0);
	std::vector<Line> line_vec;

	for (int i = 1; i <= n; i++) {
		long long temp;
		std::cin >> temp;
		sum[i] = temp + sum[i - 1];
	}

	// 점화식 dp[i] = max(-2asum[j]sum[i] + asum[j] ^ 2 -bsum[j] + dp[j]) + asum[i] ^ 2 + bsum[i] + c
	// 선에 넣는 일차함수 : sum[i]을 x라 하면 -2asum[j]x + asum[j] ^ 2 - bsum[j] + dp[j]
	// m = -2asum[j], y = asum[j] ^ 2 - bsum[j] + dp[j]
	// 컨백스 홀 트릭
	dp[0] = 0;
	line_vec.push_back(Line(0, 0));
	for (int i = 1; i <= n; i++) {
		int left = 0;
		int right = line_vec.size() - 1;
		int index = 0;

		// 이분 탐색
		while (left <= right) {
			int mid = (left + right) / 2;

			if (mid + 1 < line_vec.size() && line_vec[mid].m * sum[i] + line_vec[mid].y < line_vec[mid + 1].m * sum[i] + line_vec[mid + 1].y) {
				left = mid + 1;
			}
			else {
				index = mid;
				right = mid - 1;
			}
		}

		dp[i] = line_vec[index].m * sum[i] + line_vec[index].y + a * sum[i] * sum[i] + b * sum[i] + c;

		Line line = Line(-2 * a * sum[i], a * sum[i] * sum[i] - b * sum[i] + dp[i]);

		while (line_vec.size() > 1) {
			Line l1 = line_vec.back();
			Line l2 = line_vec[line_vec.size() - 2];

			// 새로운 선이 교차점이 뒤에 있을 때까지 뒤에서 꺼내기
			if (cross(l2, l1) < cross(l2, line)) break;

			line_vec.pop_back();
		}

		line_vec.push_back(line);
	}
	
	std::cout << dp[n];
}