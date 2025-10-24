#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

std::set<std::string> visited;

class State {
public:
	int map[3][3];
	int n; // 이동 횟수 
	int h; // 휴리스틱
	int x, y; // 0의 좌표

	bool operator<(const State& other) const {
		return this->n + this->h > other.n + other.h;
	}

	State() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				map[i][j] = 0;
		n = 0;
		h = 0;
		x = 0;
		y = 0;
	}

	State(int map[3][3], int n, int h, int x, int y) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->map[i][j] = map[i][j];
			}
		}
		this->n = n;
		this->h = h;
		this->x = x;
		this->y = y;
	}
};

std::string mapToString(int map[3][3]) {
	std::string str = "";
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			str += std::to_string(map[i][j]);
	return str;
}

std::priority_queue<State> queue;

int main() {
	int map[3][3];

	int h = 0;
	int x = 0;
	int y = 0;
	int result = -1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			std::cin >> map[i][j];

			if (map[i][j] == 0) {
				y = i;
				x = j;
				continue;
			}

			// x좌표
			h += std::abs((map[i][j] - 1) % 3 - j);
			// y좌표
			h += std::abs((map[i][j] - 1) / 3 - i);
		}

	State state = State(map, 0, h, x, y);

	queue.push(state);

	while (queue.size() > 0) {
		State state = queue.top();
		queue.pop();

		if (state.h == 0) {
			result = state.n;
			break;
		}

		std::string mapString = mapToString(state.map);
		if (visited.find(mapString) != visited.end()) continue;
		visited.insert(mapString);

		// tempx, tempy를 x,y 좌표로 옮겨가면서 평가값 비교
		for (int i = 0; i < 4; i++) {
			int tempx = state.x + dx[i];
			int tempy = state.y + dy[i];
			int temph = 0;
			if (tempx >= 0 && tempx < 3 && tempy >= 0 && tempy < 3) {
				temph += std::abs((state.map[tempy][tempx] - 1) / 3 - tempy) - std::abs((state.map[tempy][tempx] - 1) / 3 - state.y);
				temph += std::abs((state.map[tempy][tempx] - 1) % 3 - tempx) - std::abs((state.map[tempy][tempx] - 1) % 3 - state.x);

				State new_state = state;
				new_state.n++;
				new_state.h = state.h - temph;
				std::swap(new_state.map[state.y + dy[i]][state.x + dx[i]], new_state.map[state.y][state.x]);
				new_state.x += dx[i];
				new_state.y += dy[i];
				queue.push(new_state);
			}
		}
	}

	std::cout << result;
}