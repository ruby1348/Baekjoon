#include <iostream>
#include <string>
#include <vector>

class log
{
public:
    bool is_right;
    int time;
    
    log()
    {
        is_right = false;
        time = 0;
    }
};

int main(){
    std::vector<log> vec(26);
    int count = 0, score = 0;
    int t;
    while(std::cin >> t){
        if(t == -1) break;
        std::string num, ans;
        std::cin >> num >> ans;
        int index = num[0] - 'A';
        
        if(ans == "right"){
            vec[index].time += t;
            vec[index].is_right = true;
        }
        else vec[index].time += 20;
    }
    
    for(int i = 0; i < 26; i++){
        if(vec[i].is_right) { 
            score += vec[i].time;
            count++;
        }
    }
    std::cout << count << " " << score;
}