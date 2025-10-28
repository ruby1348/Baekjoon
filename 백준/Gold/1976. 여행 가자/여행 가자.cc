#include <iostream>
#include <vector>

int main(){
    int n, m;
    std::cin >> n >> m;
    
    int group_count = 1;
    std::vector<int> group(n + 1);
    std::vector<std::vector<int>> group_member(n + 1);
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int temp;
            std::cin >> temp;
            
            if(temp){
                if(group[i] == 0 && group[j] == 0){
                    // 새로운 그룹 생성
                    group[i] = group_count;
                    group[j] = group_count;
                    group_member[group_count].push_back(i);
                    group_member[group_count].push_back(j);
                    group_count++;
                    continue;
                }
                
                if(group[i] == 0 || group[j] == 0){
                    // 그룹 편입
                    int target = group[i] == 0 ? i : j;
                    int non_target = group[i] == 0 ? j : i;
                    group[target] = group[non_target];
                    group_member[group[non_target]].push_back(target);
                    continue;
                }
                
                if(group[i] != group[j]){
                    // 그룹 합치기, 그룹 넘버가 작은 것으로 합치기
                    int target = group[i] > group[j] ? group[i] : group[j];
                    int non_target = group[i] > group[j] ? group[j] : group[i];
                    for(int k = 0; k < group_member[target].size(); k++){
                        group[group_member[target][k]] = non_target;
                        group_member[non_target].push_back(group_member[target][k]);
                    }
                }
            }
        }
    }
    // 모든 여행 계획이 같은 그룹 내 있으면 성공
    int plan;
    bool res = true;
    std::cin >> plan;
    plan = group[plan];
    for(int i = 0; i < m; i++){
        int temp;
        std::cin >> temp;
        if(group[temp] != plan || group[temp] == 0 || plan == 0){
            res = false;
        }
    }
    
    if(res || n == 1) std::cout << "YES";
    else std::cout << "NO";
}