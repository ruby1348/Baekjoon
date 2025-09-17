#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<bool> visited;

void dfs(int n);

int main() {
    int n, m, k;
    std::vector<std::vector<int>> party;
    std::vector<int> known_people;

    std::cin >> n >> m >> k;
    visited.resize(n + 1);
    graph.resize(n + 1);
    party.resize(m);
    
    for(int i = 0; i < k; i++){
        int temp;
        std::cin >> temp;
        known_people.push_back(temp);
    }

    // 파티 입력 처리
    for(int i = 0; i < m; i++){
        int num;
        std::cin >> num;
        for(int j = 0; j < num; j++){
            int temp;
            std::cin >> temp;
            party[i].push_back(temp);

            // 그래프 간선 추가
            for(int p = j - 1; p >= 0; p--){
                graph[temp].push_back(party[i][p]);
                graph[party[i][p]].push_back(temp);
            }
        }
    }

    // 알려진 사람 DFS
    for(int i = 0; i < k; i++){
        dfs(known_people[i]);
    }

    // 파티 카운트
    int count = 0;
    for(int i = 0; i < m; i++){
        if(!visited[party[i][0]]) count++;
    }

    std::cout << count;
}

void dfs(int n){
    visited[n] = true;
    
    for(int i = 0; i < graph[n].size(); i++){
        if(!visited[graph[n][i]]) dfs(graph[n][i]);
    }
}