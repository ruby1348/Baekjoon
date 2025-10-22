#include <iostream>
#include <vector>

int main(){
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> vec(n + 2);
    
    long long total = 0;
    long long max = 0;
    
    for(int i = 0; i < q; i++){
        int temp;
        std::cin >> temp;
        
        if(temp == 1){
            int x, p;
            std::cin >> x >> p;
            vec[p] += x;
            if(p != n + 1) {
                total += x;
                max = std::max(max, vec[p]);
            }
        }
        if(temp == 2){
            int x, y;
            std::cin >> x >> y;
            
            if(vec[n + 1] + x > max &&
               vec[n + 1] + x - 1 > (total + y - 1) / n) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
    }
}