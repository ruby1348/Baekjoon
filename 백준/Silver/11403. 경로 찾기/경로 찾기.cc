#include <iostream>
#include <vector>

void search(int n, std::vector<std::vector<bool>> graph, std::vector<bool> &visited){
    for(int i = 0; i < graph[n].size(); i++) {
        if(graph[n][i] && !visited[i]) {
            visited[i] = true;
            search(i, graph, visited);
        }
    }
}

int main(){
    int n;
    std::cin >> n;
    std::vector<std::vector<bool>> graph(n);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            bool temp;
            std::cin >> temp;
            graph[i].push_back(temp);
        }
    }
    
    for(int i = 0; i < n; i++){
        std::vector<bool> visited(n);
        search(i, graph, visited);
        for(int j = 0; j < n; j++) std::cout << visited[j] << " ";
        std::cout << "\n";
    }
}