#include <iostream>

int main(){
    int r, c, k;
    std::cin >> r >> c >> k;
    
    if((r * c) % 2 == 1 && k > 1) std::cout << "0";
    else std::cout << "1";
}