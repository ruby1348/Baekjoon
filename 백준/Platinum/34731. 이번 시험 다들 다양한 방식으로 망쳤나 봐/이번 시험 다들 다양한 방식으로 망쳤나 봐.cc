#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
//SCC 템플릿
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> scc_graph;
std::vector<std::vector<int>> reverse_graph;
std::vector<int> is_scc;
std::vector<int> parent;
std::vector<int> visited;
std::vector<std::vector<int>> scc;
std::vector<int> scc_degree;
std::stack<int> stack;
int index = 0;

int dfs(int n);
void scc_dfs(int scc_num, int n);
int scc_dfs2(int n);

bool compare(const std::vector<int>& a, const std::vector<int>& b) {
	return a[0] < b[0];
}

int main() {
	int n, m, x;
	index = 0;
	std::cin >> n >> m >> x;

	graph.clear();
	graph.resize(n + 1);
	is_scc.assign(n + 1, -1);
	parent.assign(n + 1, -1);
	visited.assign(n + 1, 0);
	stack = std::stack<int>();
	scc.clear();
	scc_degree.clear();
	scc_graph.clear();
	reverse_graph.clear();

	for (int i = 0; i < m; i++) {
		int start, end;
		std::cin >> start >> end;
		graph[end].push_back(start);
	}

	for (int i = 1; i <= n; i++) {
		if (is_scc[i] == -1) dfs(i);
	}

	scc_graph.resize(scc.size());
	scc_degree.assign(scc.size(), 0);
	reverse_graph.resize(scc.size());
	for (int i = 0; i < scc.size(); i++) {
		scc_dfs(i, scc[i][0]);
	}

	visited.assign(n + 1, 0);
	int count = scc_dfs2(is_scc[x]);
	
	std::cout << scc.size() - count << "\n";
}

int dfs(int n) {
	parent[n] = index++;
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

		std::sort(temp.begin(), temp.end());

		scc.push_back(temp);
	}

	return low;
}

void scc_dfs(int scc_num, int n) {
	for (int i = 0; i < graph[n].size(); i++) {
		int v = graph[n][i];
		if (visited[v] == 0 && is_scc[v] == scc_num) {
			visited[v] = 1;
			scc_dfs(scc_num, v);
		}
		else if (is_scc[v] != is_scc[n]) {
			scc_graph[is_scc[n]].push_back(is_scc[v]);
			reverse_graph[is_scc[v]].push_back(is_scc[n]);
			scc_degree[is_scc[v]]++;
		}
	}
}

int scc_dfs2(int n) {
	if (visited[n]) return 0;
	visited[n] = 1;
	int count = 1;

	for (int i = 0; i < reverse_graph[n].size(); i++) {
		count += scc_dfs2(reverse_graph[n][i]);
	}
	return count;
}