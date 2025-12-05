#include <iostream>

int main(){
    int t;
    std::cin >> t;
    for(int T = 0; T < t; T++){
        long long n, m;
        std::cin >> n >> m;
        
        long long count = 0;
        while(n >= 1){
            n /= 2;
            count++;
        }
        
        count += m;
        
        std::cout << count << "\n";
    }
}