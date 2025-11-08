#include <iostream>
#include <vector>
#include <queue>


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;

	//first : 유량, second : 용량
	std::vector<std::vector<std::pair<int, int>>> flow(n * 2 + 1, std::vector<std::pair<int, int>>(n * 2 + 1));
	std::vector<std::vector<int>> graph(n * 2+ 1);

	for (int i = 0; i < m; i++) {
		int start, end;
		std::cin >> start >> end;
		flow[n + start][end].second++;
		flow[n + end][start].second++;
		graph[n + start].push_back(end);
		graph[end].push_back(n + start);
		graph[n + end].push_back(start);
		graph[start].push_back(n + end);
	}

	for (int i = 1; i <= n; i++) {
		flow[i][n + i].second = 1;
		graph[i].push_back(n + i);
		graph[n + i].push_back(i);
	}

	int count = 0;
	while (1) {
		std::vector<int> path(n * 2 + 1, -1);
		std::queue<int> queue;
		queue.push(n + 1);
		path[n + 1] = n + 1;

		// BFS 경로 찾기
		while (queue.size() > 0) {
			int node = queue.front();
			queue.pop();

			if (node == 2) break;

			for (int i = 0; i < graph[node].size(); i++) {
				int target = graph[node][i];

				//증가 경로 확인
				if (path[target] == -1 && flow[node][target].first < flow[node][target].second) {
					path[target] = node;
					queue.push(target);
					if (target == 2) break;
				}
			}
		}

		// 경로 없음
		if (path[2] == -1) break;

		int f = 1e9;

		// 역추적으로 찾은 경로에 최대로 흘려보낼 수 있는 유량 찾기
		int point = 2;
		while (point != n + 1) {
			int back = path[point];
			f = std::min(f, flow[back][point].second - flow[back][point].first);
			point = back;
		}

		// 거꾸로 유량 흘려보내기
		point = 2;
		while (point != n + 1) {
			int back = path[point];
			flow[back][point].first += f;
			flow[point][back].first -= f;
			point = back;
		}

		count += f;
	}

	std::cout << count;
}