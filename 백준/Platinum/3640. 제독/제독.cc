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
	while (std::cin >> n >> m) {
		// 1 ~ n : 시작 정점, n ~ n + 1 : 나가는 정점
		int start = n + 1;
		int end = n;
		std::vector<std::vector<Line>> line(n * 2 + 1, std::vector<Line>(n * 2 + 1));
		std::vector<std::vector<int>> graph(n * 2 + 1);

		// 정점 분리
		for (int i = 1; i <= n; i++) {
			line[i][n + i].capacity = 1;
			graph[i].push_back(n + i);
			graph[n + i].push_back(i);
		}

		for (int i = 0; i < m; i++) {
			int temp1, temp2, cost;
			std::cin >> temp1 >> temp2 >> cost;
			line[n + temp1][temp2].capacity = 1;
			line[n + temp1][temp2].cost = cost;
			line[temp2][n + temp1].cost = -cost;
			graph[n + temp1].push_back(temp2);
			graph[temp2].push_back(n + temp1);
		}

		int count = 0;
		for(int k = 0; k < 2; k++){
			std::vector<int> path(n * 2 + 1, -1);
			std::vector<int> dist(n * 2 + 1, MAX);
			std::vector<bool> is_queue(n * 2 + 1);
			std::queue<int> queue;
			queue.push(start);
			is_queue[start] = true;
			path[start] = start;
			dist[start] = 0;

			// SPFA 알고리즘
			while (queue.size() > 0) {
				int node = queue.front();
				queue.pop();
				is_queue[node] = false;

				for (int i = 0; i < graph[node].size(); i++) {
					int target = graph[node][i];

					//증가 경로 확인
					if (dist[target] > dist[node] + line[node][target].cost && line[node][target].flow < line[node][target].capacity) {
						dist[target] = dist[node] + line[node][target].cost;
						path[target] = node;
						if (!is_queue[target]) {
							queue.push(target);
							is_queue[target] = true;
						}
					}
				}
			}

			// 경로 없음
			if (path[end] == -1) break;

			int f = MAX;
			int cost = 0;

			// 역추적으로 찾은 경로에 최대로 흘려보낼 수 있는 유량 찾기
			int point = end;
			while (point != start) {
				int back = path[point];
				f = std::min(f, line[back][point].capacity - line[back][point].flow);
				point = back;
			}

			// 거꾸로 유량 흘려보내기
			point = end;
			while (point != start) {
				int back = path[point];
				line[back][point].flow += f;
				line[point][back].flow -= f;
				cost += line[back][point].cost;
				point = back;
			}

			count += cost;

		}

		std::cout << count << "\n";
	}
}