#include <iostream>

int main(){
    int n;
    std::cin >> n;
    
    std::cout << n << "\n";
    for(int i = 1; i <= n - 1; i++){
        std::cout << i << " ";
    }
    std::cout << 59;
}