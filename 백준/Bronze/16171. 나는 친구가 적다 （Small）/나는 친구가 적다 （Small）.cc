#include <iostream>
#include <string>

int main(){
    std::string line, que, str = "";
    std::cin >> line;
    for(int i = 0; i < line.length(); i++){
        if(line[i] >= 'A' && line[i] <= 'z'){
            str.push_back(line[i]);
        }
    }
    std::cin >> que;
    bool result = false;
    if(str.find(que) != std::string::npos) result = true;
    
    if(result) std::cout << "1";
    else std::cout << "0";
}