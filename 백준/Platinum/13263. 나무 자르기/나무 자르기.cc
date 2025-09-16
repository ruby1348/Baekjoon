#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

class Line {
public:
	long double m, y;
	Line(long double m, long double y) {
		this->m = m;
		this->y = y;
	}
};

//교차점 구하기
//ax + b = cx + d -> x = (d - b) / (a - c)
long double cross(Line a, Line b) {
	return (b.y - a.y) / (a.m - b.m);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n;
	std::vector<long double> height;
	std::vector<long double> cost;
	std::vector<long double> dp; // 나무를 자르기위한 최소 비용
	std::vector<Line> line_vec;

	std::cin >> n;
	height.resize(n);
	cost.resize(n);
	dp.resize(n);

	for (int i = 0; i < n; i++) std::cin >> height[i];
	for (int i = 0; i < n; i++) std::cin >> cost[i];	

	// n ^ 2 풀이, 정답 확인하기 위한 코드
	/*
	dp.resize(n, 9999999);
	dp[0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = i - 1; j >= 0; j--) {
			dp[i] = std::min(height[i] * cost[j] + dp[j], dp[i]);
		}
	}

	for (int i = 0; i < n; i++) std::cout << dp[i] << " ";
	*/

	// 컨백스 홀 트릭
	line_vec.push_back(Line(cost[0], 0));
	for (int i = 1; i < n; i++) {
		int left = 0;
		int right = line_vec.size() - 1;
		int index = 0;
		while (left <= right) {
			int mid = (left + right) / 2;

			if (mid + 1 < line_vec.size() && line_vec[mid].m * height[i] + line_vec[mid].y > line_vec[mid + 1].m * height[i] + line_vec[mid + 1].y) {
				left = mid + 1;
			}
			else {
				index = mid;
				right = mid - 1;
			}
		}

		dp[i] = line_vec[index].m * height[i] + line_vec[index].y;

		Line line = Line(cost[i], dp[i]);

		while (line_vec.size() > 1) {
			Line l1 = line_vec.back();
			Line l2 = line_vec[line_vec.size() - 2];

			// 새로운 선이 교차점이 뒤에 있을 때까지 뒤에서 꺼내기
			if (cross(l2, l1) <= cross(l2, line)) break;

			line_vec.pop_back();
		}

		line_vec.push_back(line);
	}

	std::cout << std::fixed << std::setprecision(0) << dp[n - 1];
}