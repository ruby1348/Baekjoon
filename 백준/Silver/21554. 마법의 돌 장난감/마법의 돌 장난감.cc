#include <iostream>
#include <vector>

int main(){
    int n;
    std::cin >> n;
    std::vector<int> vec(n + 1);
    std::vector<std::pair<int, int>> res;
    for(int i = 1; i <= n; i++){
        std::cin >> vec[i];
    }
    
    int count = 0;
    for(int i = 1; i <= n; i++){
        if(vec[i] != i){
            count++;
            int point;
            for(int j = i + 1; j <= n; j++){
                if(vec[j] == i){
                    point = j;
                    break;
                }
            }
            
            res.push_back(std::pair<int, int>(i, point));
            int left = i;
            while(left < point){
                std::swap(vec[left++], vec[point--]);
            }
        }
    }
    
    std::cout << count << "\n";
    for(int i = 0; i < res.size(); i++) std::cout << res[i].first << " " << res[i].second << "\n";
}