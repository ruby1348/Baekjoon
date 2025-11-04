#include <iostream>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL), std::cout.tie(NULL);
    int t;
    std::cin >> t;
    for(int T = 0; T < t; T++){
        long long n, m;
        std::cin >> n >> m;
        
        if((n + m) % 2 == 1 || n == 1 || m == 1) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}