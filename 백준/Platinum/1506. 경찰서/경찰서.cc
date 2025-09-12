#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

std::vector<std::vector<int>> graph;
std::vector<int> is_scc;
std::vector<int> parent;
std::vector<std::vector<int>> scc;
std::stack<int> stack;
int scc_index = 0;

int dfs(int n);

bool compare(const std::vector<int>& a, const std::vector<int>& b) {
	return a[0] < b[0];
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> cost;
    
    cost.resize(n + 1);
	graph.resize(n + 1);
	is_scc.resize(n + 1, -1);
	parent.resize(n + 1, -1);

    for(int i = 0; i < n; i++){
        std::cin >> cost[i + 1];
    }

	for(int i = 0; i < n; i++){
        std::string str;
        std::cin >> str;
        for(int j = 0; j < str.length(); j++){
            if(str[j] == '0') continue;

            graph[i + 1].push_back(j + 1);
        }
	}

	for (int i = 1; i <= n; i++) {
		if (is_scc[i] == -1) dfs(i);
	}

    int sum = 0;
    std::vector<int> scc_cost;
    scc_cost.resize(scc.size(), 99999999);
    
    for(int i = 0; i < scc.size(); i++){
        for(int j = 0; j < scc[i].size(); j++){
            scc_cost[i] = scc_cost[i] < cost[scc[i][j]] ? scc_cost[i] : cost[scc[i][j]];
        }
        sum += scc_cost[i];
    }
    std::cout << sum;
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

		std::sort(temp.begin(), temp.end());

		scc.push_back(temp);
	}

	return low;
}