#include <iostream>
#include <vector>
#include <stack>
#define MAX 1000

std::vector<std::vector<int>> graph;
std::vector<int> is_scc;
std::vector<int> parent;
std::vector<int> visited;
std::vector<int> scc_visited;
std::vector<std::vector<int>> scc;
std::vector<std::vector<int>> scc_graph;
std::vector<int> scc_degree;
std::stack<int> stack;
int scc_index = 0;

int dfs(int n);
void scc_dfs(int n);
int scc_dfs2(int n);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n, k;
	std::cin >> n >> k;
	graph.resize(MAX + 1);
	visited.assign(MAX + 1, 0);
	is_scc.assign(MAX + 1, -1);
	parent.assign(MAX + 1, -1);

	for (int i = 1; i <= n; i++) {
		int target;
		std::cin >> target;
		graph[target].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		if (is_scc[i] == -1) dfs(i);
	}

	std::vector<std::pair<int, int>> group;
	scc_graph.resize(scc.size());
	scc_degree.resize(scc.size());
	scc_visited.resize(scc.size());

	for (int i = 0; i < scc.size(); i++) {
		scc_dfs(scc[i][0]);
	}

	for (int i = 0; i < scc.size(); i++) {
		if (scc_degree[i] == 0) {
			int size = scc_dfs2(i) - 1 + scc[i].size();
			group.push_back(std::pair<int, int>(scc[i].size(), size)); //first : 최소 사이즈, second : 최대 사이즈
		}
	}
	
	std::vector<std::pair<bool, int>> result(k + 1, { false, 0 });
	for (int i = 0; i < group.size(); i++) {
		int size = group[i].first;
		for (int j = k - size; j >= 0; j--) {
			if (result[j].first == true || j == 0) {
				result[j + size].first = true;
				result[j + size].second = std::max(result[j + size].second, result[j].second + group[i].second);
			}
		}
	}

	int max = 0;
	for (int i = 1; i <= k; i++) {
		if(result[i].first == true) max = max > result[i].second ? max : result[i].second;
	}
	if (max > k) max = k;

	std::cout << max;
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

void scc_dfs(int n) {
	for (int i = 0; i < graph[n].size(); i++) {
		int v = graph[n][i];
		if (v == n) continue;
		if (visited[v] == 0 && is_scc[v] == is_scc[n]) {
			visited[v] = 1;
			scc_dfs(v);
		}
		else if (is_scc[v] != is_scc[n]) {
			scc_graph[is_scc[n]].push_back(is_scc[v]);
			scc_degree[is_scc[v]]++;
		}
	}
}

int scc_dfs2(int n) {
	int count = 1;
	for (int i = 0; i < scc_graph[n].size(); i++) {
		int v = scc_graph[n][i];
		if (scc_visited[v] == 0) {
			scc_visited[v] = 1;
			count += scc_dfs2(v);
		}
	}
	return count;
}