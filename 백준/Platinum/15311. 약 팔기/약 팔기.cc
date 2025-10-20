#include <iostream>

int main(){
    int n;
    std::cin >> n;
    std::cout << 2000 << "\n";
    for(int i = 1; i <= 1000; i++){
        std::cout << 999 << " ";
    }
    for(int i = 1000; i > 0; i--){
        std::cout << 1 << " ";
    }
}