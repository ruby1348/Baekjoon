#include <iostream>
#include <string>
#include <vector>

int main(){
    int n;
    int result = 0;
    std::vector<std::string> vec;
    std::cin >> n;
    
    for(int i = 0; i < n; i++){
        std::string str;
        std::cin >> str;
        
        for(int j = 0; j < vec.size(); j++){
            int size = std::min(str.length(), vec[j].length());
            
            for(int k = 1; k <= size; k++){
                if(str.substr(0, k) == vec[j].substr(vec[j].length() - k)
                   || str.substr(str.length() - k) == vec[j].substr(0, k)){
                    result++;
                    break;
                }
            }
        }
        vec.push_back(str);
    }
    std::cout << result;
}