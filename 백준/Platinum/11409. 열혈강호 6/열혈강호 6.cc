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

	// 0: 시작, 1 ~ n: 사람, n + 1 ~ n + m 일, m + n + 1: 끝
	int start = 0;
	int end = n + m + 1;
	std::vector<std::vector<Line>> line(end + 1, std::vector<Line>(end + 1));
	std::vector<std::vector<int>> graph(end + 1);

	// 일->끝
	for (int i = 1; i <= m; i++) {
		line[n + i][end].capacity = 1;
		graph[n + i].push_back(end);
		graph[end].push_back(n + i);
	}

	// 시작->사람
	for (int i = 1; i <= n; i++) {
		line[start][i].capacity = 1;
		graph[start].push_back(i);
		graph[i].push_back(start);
	}

	// 사람->일
	for (int i = 1; i <= n; i++) {
		int temp;
		std::cin >> temp;
		for (int j = 1; j <= temp; j++) {
			int job;
			std::cin >> job;
			std::cin >> line[i][n + job].cost;
			line[n + job][i].cost = -line[i][n + job].cost;
			line[i][n + job].capacity = 1;
			graph[i].push_back(n + job);
			graph[n + job].push_back(i);
		}
	}

	int count = 0;
	int total = 0;
	while (1) {
		std::vector<int> path(end + 1, -1);
		std::vector<int> dist(end + 1, MAX);
		std::vector<bool> is_queue(end + 1);
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
				if (dist[target] > dist[node] - line[node][target].cost && line[node][target].flow < line[node][target].capacity) {
					dist[target] = dist[node] - line[node][target].cost;
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

		count += f;
		total += f * cost;
	}

	std::cout << count << "\n" << total;
}