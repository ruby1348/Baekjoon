#include <iostream>
#include <vector>
#include <stack>
#define MAX 2000

std::vector<std::vector<int>> graph;
std::vector<int> is_scc;
std::vector<int> parent;
std::vector<int> visited;
std::vector<std::vector<int>> scc;
std::vector<std::vector<int>> scc_graph;
std::vector<int> scc_degree;
std::stack<int> stack;
int scc_index = 0;

int dfs(int n);
void scc_dfs(int n);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, m;
	std::cin >> n >> m;
	graph.resize(MAX * 2 + 1);
	visited.assign(MAX * 2 + 1, 0);
	is_scc.assign(MAX * 2 + 1, -1);
	parent.assign(MAX * 2 + 1, -1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char temp;
			std::cin >> temp;

			if (temp == '*') {
				//보석
				graph[i].push_back(j + n + MAX);
				graph[i + MAX].push_back(j + n);
				graph[j + n].push_back(i + MAX);
				graph[j + n + MAX].push_back(i);
			}
			if (temp == '#') {
				//위치추적기
				graph[i].push_back(j + n);
				graph[j + n].push_back(i);
				graph[i + MAX].push_back(j + n + MAX);
				graph[j + n + MAX].push_back(i + MAX);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (is_scc[i] == -1) dfs(i);
	}

	std::vector<int> counting(MAX + 1, 0);
	bool result = true;
	int check = 0;
	for (int i = 0; i < scc.size(); i++) {
		check++;
		for (int j = 0; j < scc[i].size(); j++) {
			int v = scc[i][j];
			if (v <= MAX) {
				if (counting[v] == check) {
					result = false;
					break;
				}
				counting[v] = check * -1;
			}
			else {
				if (counting[v - MAX] == check * -1) {
					result = false;
					break;
				}
				counting[v - MAX] = check;
			}
		}

		if (result == false) break;
	}

	if (result) std::cout << "1";
	else std::cout << "0";

}

int dfs(int n) {
	parent[n] = scc_index++;
	stack.push(n);

	int low = parent[n];
	for (int i = 0; i < graph[n].size(); i++) {
		int v = graph[n][i];
		if (parent[v] == -1) {
			int temp = dfs(v);
			if (temp < low) low = temp;
		}
		else if (is_scc[v] == -1 && parent[v] < low) low = parent[v];
	}

	if (low == parent[n]) {
		std::vector<int> temp;
		while (1) {
			int top = stack.top();
			temp.push_back(top);
			stack.pop();
			is_scc[top] = scc.size();
			if (top == n) break;
		}

		scc.push_back(temp);
	}

	return low;
}