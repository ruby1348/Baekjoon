#include <iostream>
#include <string>

int main(){
    std::string line;
    int n;
    std::cin >> n;
    std::getline(std::cin, line); //엔터 파싱
    for(int t = 0; t < n; t++){
        std::string result = "";
        std::getline(std::cin, line);
        bool is_number = true;
        bool is_null = true;
        //시작지점 찾기
        int start = 0;
        for( ; start < line.length(); start++){
            if(line[start] >= '0' && line[start] <= '9'){
                is_null = false; //숫자가 하나라도 있으면 false
                break;
            }
            if(line[start] != ' '){
                is_number = false;
                break;
            }
        }
        
        //0 파싱
        for( ; start < line.length(); start++){
            if(line[start] >= '1' && line[start] <= '9')
                break;
            if(line[start] != '0')
                break;
        }
        
        //숫자 시작지점부터 숫자 확인
        for( ; start < line.length(); start++){
            if(line[start] >= '0' && line[start] <= '9'){
                result.push_back(line[start]);
            }
            else{
                break;
            }
        }
        
        for( ; start < line.length(); start++){
            if(line[start] != ' '){
                is_number = false;
                break;
            }
        }
        
       //예외 처리
        if(is_number && is_null == false && result == "") std::cout << "0\n";
        else if(is_number && !is_null) std::cout << result << "\n";
        else std::cout << "invalid input\n";
    }
}