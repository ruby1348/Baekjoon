#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int k;
    std::cin >> k;
    for(int i = 0; i < k; i++){
        int n, gap = -1e9;
        std::cin >> n;
        std::vector<int> vec(n);
        for(int j = 0; j < n; j++){
            std::cin >> vec[j];
        }
        
        std::sort(vec.begin(), vec.end());
        
        for(int j = 1; j < n; j++){
            if(vec[j] - vec[j - 1] > gap) gap = vec[j] - vec[j - 1];
        }
        
        std::cout << "Class " << i + 1 << "\n";
        std::cout << "Max " << vec[n - 1] << ", Min " << vec[0] << ", Largest gap " << gap << "\n";
    }
}