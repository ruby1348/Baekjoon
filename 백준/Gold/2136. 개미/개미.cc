#include <iostream>
#include <vector>
#include <algorithm>

class ant{
public:
    int pos;
    int num;
    bool invert;
};

int main(){
    int n, l, count = 0, max = 0;
    bool total_invert = false;
    std::cin >> n >> l;
    std::vector<ant> vec;
    for(int i = 1; i <= n; i++){
        ant temp;
        temp.num = i;
        std::cin >> temp.pos;
        if(temp.pos < 0){
            temp.pos *= -1;
            temp.invert = true;
            count++;
            if(max < temp.pos){
                max = temp.pos;
                total_invert = true;
            }
        }
        else{
            temp.invert = false;
            if(max < l - temp.pos){
                max = l - temp.pos;
                total_invert = false;
            }
        }
        vec.push_back(temp);
    }
    
    std::sort(vec.begin(), vec.end(), [](const ant& a, const ant& b){
        return a.pos < b.pos;
    });

    if(total_invert) std::cout << vec[count - 1].num << " " << max;
    else std::cout << vec[count].num << " " << max;
}