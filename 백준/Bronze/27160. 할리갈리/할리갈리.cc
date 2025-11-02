#include <iostream>
#include <string>

int main(){
    int n;
    std::cin >> n;
    
    int s = 0;
    int b = 0;
    int l = 0;
    int p = 0;
    
    for(int i = 0; i < n; i++){
        std::string str;
        int temp;
        std::cin >> str >> temp;
        
        if(str == "STRAWBERRY") s += temp;
        if(str == "BANANA") b += temp;
        if(str == "LIME") l += temp;
        if(str == "PLUM") p += temp;
    }
    
    if(s == 5 || b == 5 || l == 5 || p == 5) std::cout << "YES";
    else std::cout << "NO";
}