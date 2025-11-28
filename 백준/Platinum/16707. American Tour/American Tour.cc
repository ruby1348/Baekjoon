#include <iostream>
#include <vector>
#include <queue>
#define MAX 1e9

class Line {
public:
	int flow;
	int capacity;
	int cost;
};


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;
	// 1 ~ n : 시작 정점, n ~ n + 1 : 나가는 정점
	int start = 1;
	int end = n;
	std::vector<std::vector<std::vector<Line>>> line(n * 2 + 1, std::vector<std::vector<Line>>(n * 2 + 1));
	std::vector<std::vector<int>> graph(n * 2 + 1);

	// 정점 분리
	for (int i = 1; i <= n; i++) {
		line[i][n + i].resize(1);
		line[i][n + i][0].flow = 0;
		line[i][n + i][0].capacity = 2;
		line[i][n + i][0].cost = 0;
		line[n + i][i].resize(1);
		line[n + i][i][0].flow = 0;
		line[n + i][i][0].capacity = 0;
		line[n + i][i][0].cost = 0;
		graph[i].push_back(n + i);
		graph[n + i].push_back(i);
	}

	for (int i = 0; i < m; i++) {
		int temp1, temp2, cost;
		std::cin >> temp1 >> temp2 >> cost;
		Line l1, l2;
		l1.flow = 0;
		l1.capacity = 1;
		l1.cost = cost;
		l2.flow = 0;
		l2.capacity = 0;
		l2.cost = -cost;

		line[n + temp1][temp2].push_back(l1);
		line[n + temp2][temp1].push_back(l1);
		line[temp2][n + temp1].push_back(l2);
		line[temp1][n + temp2].push_back(l2);

		graph[n + temp1].push_back(temp2);
		graph[n + temp2].push_back(temp1);
		graph[temp2].push_back(n + temp1);
		graph[temp1].push_back(n + temp2);
	}

	int count = 0;
	for (int k = 0; k < 2; k++) {
		if (k == 0) {
			start = 2;
			end = 1;
		}
		if (k == 1) {
			start = 2;
			end = n;
		}
		std::vector<std::pair<int, int>> path(n * 2 + 1, std::pair<int, int>(-1, 0));
		std::vector<int> dist(n * 2 + 1, MAX);
		std::vector<bool> is_queue(n * 2 + 1);
		std::queue<std::pair<int, int>> queue;

		queue.push(std::pair<int, int>(start, 0));
		is_queue[start] = true;
		path[start] = std::pair<int, int>(start, 0);
		dist[start] = 0;

		// SPFA 알고리즘
		while (queue.size() > 0) {
			int node = queue.front().first;
			queue.pop();
			is_queue[node] = false;

			for (int i = 0; i < graph[node].size(); i++) {
				int target = graph[node][i];

				//증가 경로 확인
				for (int j = 0; j < line[node][target].size(); j++) {
					if (dist[target] > dist[node] + line[node][target][j].cost && line[node][target][j].flow < line[node][target][j].capacity) {
						dist[target] = dist[node] + line[node][target][j].cost;
						path[target] = std::pair<int, int>(node, j);
						if (!is_queue[target]) {
							queue.push(std::pair<int, int>(target, j));
							is_queue[target] = true;
						}
					}
				}
			}
		}
		// 경로 없음
		if (path[end].first == -1) break;

		int f = MAX;
		int cost = 0;

		// 역추적으로 찾은 경로에 최대로 흘려보낼 수 있는 유량 찾기
		int point = end;
		while (point != start) {
			std::pair<int,int> back = path[point];
			int minf = MAX;
			f = std::min(f, line[back.first][point][back.second].capacity - line[back.first][point][back.second].flow);
			point = back.first;
		}

		// 거꾸로 유량 흘려보내기
		point = end;
		while (point != start) {
			std::pair<int, int> back = path[point];
			line[back.first][point][back.second].flow += f;
			line[point][back.first][back.second].flow -= f;
			cost += line[back.first][point][back.second].cost;
			point = back.first;
		}
		count += cost;
	}

	std::cout << count << "\n";

}