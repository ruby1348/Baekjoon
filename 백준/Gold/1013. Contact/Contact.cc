#include <iostream>
#include <regex>
#include <string>

int main(){
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        std::string str;
        std::cin >> str;
        std::regex regex("(100+1+|01)+");
        
        bool result = std::regex_match(str, regex);
        if(result) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}