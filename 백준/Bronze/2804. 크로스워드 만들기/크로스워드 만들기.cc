#include <iostream>
#include <string>

int main(){
    std::string str1, str2;
    std::cin >> str1 >> str2;
    
    //같은 문자 찾기
    int s1 = -1, s2 = -1;
    for(int i = 0; i < str1.length(); i++){
        for(int j = 0; j < str2.length(); j++){
            if(str1[i] == str2[j]){
                s1 = i;
                s2 = j;
                break;
            }
        }
        if(s1 != -1) break;
    }
    for(int i = 0; i < str2.length(); i++){
        for(int j = 0; j < str1.length(); j++){
            if(j == s1) std::cout << str2[i];
            else if(i == s2) std::cout << str1[j];
            else std::cout << ".";
        }
        std::cout << std::endl;
    }
}