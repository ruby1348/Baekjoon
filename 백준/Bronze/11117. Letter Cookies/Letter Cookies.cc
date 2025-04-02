#include <iostream>
#include <string>

int main(){
    int T;
    std::cin >> T;
    for(int t = 0; t < T; t++){
        std::string str;
        int n;
        
        int alp[26];
        for(int i = 0; i < 26; i++) alp[i] = 0;
        
        std::cin >> str >> n;
        
        for(int i = 0; i < str.length(); i++){
           alp[str[i] - 'A']++; 
        }
        
        for(int i = 0; i < n; i++){
            std::string q;
            std::cin >> q;
            
            int word[26];
            for(int i = 0; i < 26; i++) word[i] = 0;
            
            bool result = true;
            
            for(int j = 0; j < q.length(); j++){
                word[q[j] - 'A']++;
                //쿠키 상자보다 알파벳의 개수가 많은 경우
                if(word[q[j] - 'A'] > alp[q[j] - 'A']) result = false;
            }
            
            if(result) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
    }
}