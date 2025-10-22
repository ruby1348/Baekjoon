#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
    int k, m, n;
    int score = 0;
    std::cin >> k >> m >> n;
    
    std::vector<std::pair<std::string, int>> vec;
    
    for(int i = 0; i < k; i++){
        std::string str;
        int num;
        std::cin >> str >> num;
        
        vec.push_back(std::pair<std::string, int>(str, num));
    }
    
    std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        });
    
    for(int i = 0; i < n; i++){
        std::string str;
        std::cin >> str;
        
        auto index = std::find_if(vec.begin(), vec.end(), 
        [=](const std::pair<std::string, int>& temp) {
            return str == temp.first;
        });
                     
        score += index->second;
        vec.erase(index);
    }                      
    
    int max = score;
    int min = score;
    
    for(int i = 0; i < m - n; i++){
        min += vec[i].second;
        max += vec[vec.size() - i - 1].second;
    }
    
    std::cout << min << " " << max;
}