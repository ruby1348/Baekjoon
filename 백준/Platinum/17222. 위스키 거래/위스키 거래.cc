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

	std::vector<int> vec(n + m + 1);

	//first : 유량, second : 용량
	std::vector<std::vector<std::pair<int, int>>> flow(end + 1, std::vector<std::pair<int, int>>(end + 1));
	std::vector<std::vector<int>> graph(end + 1);

	for (int i = 1; i <= n; i++) {
		std::cin >> vec[i];
	}

	for (int i = n + 1; i <= n + m; i++) {
		std::cin >> vec[i];
	}

	// start -> m
	for (int i = n + 1; i <= n + m; i++) {
		flow[start][i].second = vec[i];
		graph[start].push_back(i);
		graph[i].push_back(start);
	}

	// n -> end
	for (int i = 1; i <= n; i++) {
		flow[i][end].second = MAX;
		graph[i].push_back(end);
		graph[end].push_back(i);
	}

	// m -> n
	for (int i = n + 1; i <= n + m; i++) {
		int temp;
		std::cin >> temp;
		for (int j = 1; j <= temp; j++) {
			int num;
			std::cin >> num;
			flow[i][num].second = vec[num];
			graph[i].push_back(num);
			graph[num].push_back(i);
		}
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

	std::cout << count;

}