#include <iostream>
#include <vector>
#include <queue>
#define MAX 1e9


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;

	//n + m + 1: start, 1 ~ n, n + 1 ~ n + m, n + m + 2: end
	int start = n + m + 1, end = n + m + 2;
	int total = 0;

	//first : 유량, second : 용량
	std::vector<std::vector<std::pair<int, int>>> flow(end + 1, std::vector<std::pair<int, int>>(end + 1));
	std::vector<std::vector<int>> graph(end + 1);

	// n -> m
	for (int i = 1; i <= n; i++) {
		for (int j = n + 1; j <= n + m; j++) {
			flow[i][j].second = 1;
			graph[i].push_back(j);
			graph[j].push_back(i);
		}
	}

	// start -> n
	for (int i = 1; i <= n; i++) {
		std::cin >> flow[start][i].second;
		graph[start].push_back(i);
		graph[i].push_back(start);
	}

	// m -> end
	for (int i = n + 1; i <= n + m; i++) {
		std::cin >> flow[i][end].second;
		total += flow[i][end].second;
		graph[i].push_back(end);
		graph[end].push_back(i);
	}

	int count = 0;
	while (1) {
		std::vector<int> path(end + 1, -1);
		std::queue<int> queue;
		queue.push(start);
		path[start] = start;

		// BFS 경로 찾기
		while (queue.size() > 0) {
			int node = queue.front();
			queue.pop();

			if (node == end) break;

			for (int i = 0; i < graph[node].size(); i++) {
				int target = graph[node][i];

				//증가 경로 확인
				if (path[target] == -1 && flow[node][target].first < flow[node][target].second) {
					path[target] = node;
					queue.push(target);
					if (target == end) break;
				}
			}
		}

		// 경로 없음
		if (path[end] == -1) break;

		int f = MAX;

		// 역추적으로 찾은 경로에 최대로 흘려보낼 수 있는 유량 찾기
		int point = end;
		while (point != start) {
			int back = path[point];
			f = std::min(f, flow[back][point].second - flow[back][point].first);
			point = back;
		}

		// 거꾸로 유량 흘려보내기
		point = end;
		while (point != start) {
			int back = path[point];
			flow[back][point].first += f;
			flow[point][back].first -= f;
			point = back;
		}

		count += f;
	}

	// 가능한 대진표 없음
	if (total != count) {
		std::cout << -1;
		return 0;
	}

	// 대진표 바꾸기
	if (count != 0) {
		int last_n, last_m;
		for (int i = 1; i <= n; i++) {
			for (int j = n + 1; j <= n + m; j++) {
				if (flow[i][j].first == 1) {
					last_n = i;
					last_m = j;

					std::vector<int> path(end + 1, -1);
					std::queue<int> queue;
					queue.push(last_n);
					path[last_n] = last_n;

					// BFS 경로 찾기
					while (queue.size() > 0) {
						int node = queue.front();
						queue.pop();
						if (node == last_m) break;
						if (node < last_n) continue;
						for (int i = 0; i < graph[node].size(); i++) {
							int target = graph[node][i];
							if (node == last_n && target < last_m) continue;
							//증가 경로 확인
							if (path[target] == -1 && flow[node][target].first < flow[node][target].second) {
								path[target] = node;
								queue.push(target);
								if (target == last_m) break;
							}
						}
					}

					// 경로 없음
					if (path[last_m] == -1) continue;;

					int f = MAX;

					// 역추적으로 찾은 경로에 최대로 흘려보낼 수 있는 유량 찾기
					int point = last_m;
					while (point != last_n) {
						int back = path[point];
						f = std::min(f, flow[back][point].second - flow[back][point].first);
						point = back;
					}

					// 거꾸로 유량 흘려보내기
					point = last_m;
					while (point != last_n) {
						int back = path[point];
						flow[back][point].first += f;
						flow[point][back].first -= f;
						point = back;
					}

					flow[last_n][last_m].first = 0;
					flow[last_m][last_n].first = 0;

				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = n + 1; j <= n + m; j++) {
			if (flow[i][j].first == 1) std::cout << 1;
			else std::cout << 0;
		}
		std::cout << "\n";
	}
}