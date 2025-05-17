#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n;
    std::vector<int> vec;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        int nn, sum = 0;
        std::cin >> nn;
        for(int j  = 0; j < nn; j++){
            int temp;
            std::cin >> temp;
            sum += temp;
        }
        vec.push_back(sum);
    }
    std::sort(vec.begin(), vec.end());
    
    long long sum = 0, res = 0;
    for(int i = 0; i < n; i++){
        res += sum + vec[i];
        sum += vec[i];
    }
    std::cout << res;
}