#include <iostream>
#include <vector>

int main(){
    int n, m;
    std::cin >> n >> m;
    
    bool result = true;
    
    for(int i = 0; i < m; i++){
        int num;
        std::cin >> num;
        
        int current = 200001;
        for(int j = num; j > 0; j--){
            int temp;
            std::cin >> temp;
            if(current < temp) result = false;
            current = temp;
        }
    }
    
    if(result) std::cout << "Yes";
    else std::cout << "No";
}