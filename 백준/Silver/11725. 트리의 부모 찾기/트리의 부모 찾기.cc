#include <iostream>
#include <vector>

std::vector<int> parent;
std::vector<std::vector<int>> graph;

void dfs(int n, int p);

int main() {
    int n;
    std::cin >> n;

    parent.resize(n + 1);
    graph.resize(n + 1);

    for(int i = 0; i < n; i++){
        int a, b;
        std::cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(graph[1][0], 1);

    for(int i = 2; i <= n; i++) std::cout << parent[i] << "\n";
}

void dfs(int n, int p){
    parent[n] = p;

    for(int i = 0; i < graph[n].size(); i ++){
        int target = graph[n][i];

        // 부모가 정해지지 않은 노드의 경우에만 탐색을 계속
        if(parent[target] == 0) dfs(target, n);
    }
}