#include <iostream>
#include <string>

int main(){
    int n;
    std::string line;
    std::cin >> n;
    
    std::getline(std::cin, line); // 엔터 파싱
    for(int t = 0; t < n; t++){
        bool result[26];
        bool pan = true;
        for(int i = 0; i < 26; i++) result[i] = false;
        std::getline(std::cin, line);
        for(int i = 0; i < line.length(); i++){
            if(line[i] >= 'A' && line[i] <= 'Z')
                line[i] = line[i] - 'A' + 'a'; //소문자로 변경
            if(line[i] >= 'a' && line[i] <= 'z')
                result[line[i] - 'a'] = true;
        }
        for(int i = 0; i < 26; i++)
            if(!result[i]) pan = false;
        if(pan) std::cout << "pangram";
        else{
            std::cout << "missing ";
            for(int i = 0; i < 26; i++){
                if(!result[i]) std::cout << char(i +'a');
            }
        }
        std::cout << "\n";
    }
}