#include <iostream>
#include <vector>
#include <string>

int main(){
    int T;
    std::cin >> T;
    for(int t = 0; t < T; t++){
        int p;
        bool invert = false, error = false;
        std::string str, arr;
        std::vector<int> vec;
        std::cin >> str >> p >> arr;
        
        //파싱
        if(p != 0){
            int index = 1; //첫글자 제외
            for(int i = 2; i < arr.length(); i++){
                if(arr[i] == ',' || arr[i] == ']'){
                    vec.push_back(std::stoi(arr.substr(index, i - index)));
                    index = i + 1;
                }
            }
        }
        
        int start = 0;
        int end = vec.size() - 1;
        for(int i = 0; i < str.length(); i++){
            if(error) break;
            
            if(str[i] == 'R') invert = !invert;
            else{
                //뒤에서 제거
                if(invert){
                    if(end < start) error = true;
                    end--;
                }
                //앞에서 제거
                else{
                    if(start > end) error = true;
                    start++;
                }
            }
        }
        
        if(error) std::cout << "error\n";
        else{
            std::cout << "[";
            //뒤에서 출력
            if(invert){
                for(int i = end; i >= start; i--) {
                    std::cout << vec[i];
                    if(i != start) std::cout << ",";
                }
            }
            //앞에서 출력
            else{
                for(int i = start; i <= end; i++) {
                    std::cout << vec[i];
                    if(i != end) std::cout << ",";
                }
            }
            std::cout << "]\n";
        }
    }
}