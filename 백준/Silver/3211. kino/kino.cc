#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n, result = 1;
    std::vector<int> vec;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end());
    for(int i = 0; i < result; i++){
        if(vec[i] >= result) result = vec[i] + 1;
    }
    std::cout << result;
}