#include <iostream>

int main(){
    int T;
    std::cin >> T;
    for(int t = 0; t < T; t++){
        unsigned long long n;
        std::cin >> n;
        
        unsigned long long luck = 8;
        while(luck < 9e18 && luck * 10 + 8 <= n){
            luck *= 10;
            luck += 8;
        }
        
        for(int i = 0; i < 8; i++){
            n -= luck;
            while(luck > n) {
                luck /= 10;
            }
        }
        
        if(n == 0) std::cout << "Yes\n";
        else std::cout << "No\n";
    }
}