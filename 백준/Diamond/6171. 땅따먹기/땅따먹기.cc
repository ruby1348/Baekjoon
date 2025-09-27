#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Land {
public:
	long long w, h;
	Land(long long w, long long h) {
		this->w = w;
		this->h = h;
	}
};

class Line {
public:
	long long m, y;
	Line(long double m, long double y) {
		this->m = m;
		this->y = y;
	}
};

//교차점 구하기
//ax + b = cx + d -> x = (d - b) / (a - c)
long double cross(Line a, Line b) {
	return (long double)(b.y - a.y) / (long double)(a.m - b.m);
}

inline bool compare(Land a, Land b) { 
	if (a.w == b.w) return a.h > b.h;
	return a.w > b.w;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	long long n;
	std::cin >> n;

	std::vector<Land> temp_vec;
	std::vector<Land> temp_vec2;
	std::vector<Land> vec;
	std::vector<long long> dp(n + 1, 0);
	std::vector<Line> line_vec;

	for (int i = 0; i < n; i++) {
		int w, h;
		std::cin >> w >> h;
		temp_vec.push_back(Land(w, h));
	}

	// 정렬
	std::sort(temp_vec.begin(), temp_vec.end(), compare);

	//w가 같은 땅 합치기
	int temp_w = temp_vec[0].w;
	int temp_h = temp_vec[0].h;
	temp_vec2.push_back(Land(temp_w, temp_h));
	for (int i = 1; i < n; i++) {
		if (temp_vec[i].w != temp_w) {
			temp_w = temp_vec[i].w;
			temp_h = temp_vec[i].h;
			temp_vec2.push_back(Land(temp_w, temp_h));
		}
	}

	//h가 작은 땅 합치기
	temp_w = temp_vec2[0].w;
	temp_h = temp_vec2[0].h;
	vec.push_back(Land(temp_w, temp_h));
	for (int i = 1; i < temp_vec2.size(); i++) {
		if (temp_vec2[i].h > temp_h) {
			temp_w = temp_vec2[i].w;
			temp_h = temp_vec2[i].h;
			vec.push_back(Land(temp_w, temp_h));
		}
	}
	


	// 점화식 dp[i] = min(w[i] * h[j] + do[j]) / m = w[i] * h[j] + dp[j]
	// 컨백스 홀 트릭
	line_vec.push_back(Line(vec[0].w, 0));
	for (int i = 0; i < vec.size(); i++) {
		int left = 0;
		int right = line_vec.size() - 1;
		int index = 0;

		// 이분 탐색
		while (left <= right) {
			int mid = (left + right) / 2;

			if (mid + 1 < line_vec.size() && line_vec[mid].m * vec[i].h + line_vec[mid].y > line_vec[mid + 1].m * vec[i].h + line_vec[mid + 1].y) {
				left = mid + 1;
			}
			else {
				index = mid;
				right = mid - 1;
			}
		}

		dp[i] = line_vec[index].m * vec[i].h + line_vec[index].y;
		if (i != vec.size() - 1) {
			Line line = Line(vec[i + 1].w, dp[i]);


			while (line_vec.size() > 1) {
				Line l1 = line_vec.back();
				Line l2 = line_vec[line_vec.size() - 2];

				// 새로운 선이 교차점이 뒤에 있을 때까지 뒤에서 꺼내기
				if (cross(l2, l1) < cross(l2, line)) break;

				line_vec.pop_back();
			}

			line_vec.push_back(line);
		}
	}

	
	std::cout << dp[vec.size() - 1];
}