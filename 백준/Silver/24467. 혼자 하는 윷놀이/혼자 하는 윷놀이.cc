#include <iostream>
#include <string>

int main(){
    int point = 0;
    std::string line;
    while(std::getline(std::cin, line)){
        int count = 0;
        for(int i = 0; i < 4; i++){
            if(line[i] == '0') count++;
        }
        if(count == 0) count = 5;
        
        if(point > 20 && point < 30) continue;
        point += count;
        
        if(point == 5) point = 30;
        if(point == 10) point = 50;
        if(point == 33) point = 53;
        
        if(point >= 36 && point < 50) point -= 21;
        if(point >= 56) point -= 36;
    }
    
    if(point > 20 && point < 30) std::cout << "WIN";
    else std::cout << "LOSE";
}