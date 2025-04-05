#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;

void search(int n, std::vector<bool> &visit){
    visit[n]= true;
    for(int i = 0; i < graph[n].size(); i++){
        int temp = graph[n][i];
        if(!visit[temp]) search(temp, visit);
    }
}

int main(){
    int n;
    std::cin >> n;
    graph.resize(n);
    
    for(int i = 0; i < n - 1; i++){
        int a, b;
        std::cin >> a >> b;
        graph[b - 1].push_back(a - 1);
    }
    
    bool is_result = false;
    for(int i = 0; i < n; i++){
        std::vector<bool> visit(n);
        visit[i] = true;
        for(int j = 0; j < graph[i].size(); j++) search(graph[i][j], visit);
        
        bool result = true;
        for(int j = 0; j < n; j++){
            if(!visit[j]){
                result = false;
                break;
            }
        }
        
        if(result){
            std::cout << i + 1;
            is_result = true;
            break;
        }
    }
    
    if(!is_result) std::cout << -1;
}