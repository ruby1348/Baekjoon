#include <iostream>

int main(){
    while(true){
        int d, m, y;
        int count = 0;
        std::cin >> d >> m >> y;
        if(d == 0) break;
        
        int mon[13] {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for(int i = 1; i <= 12; i++){
            if(m == i) break;
            count += mon[i];
        }
        
        count += d;
        if(y % 4 == 0 && m > 2) {
            if(y % 100 == 0 && y % 400 != 0) count--;
            count++;
        }
        std::cout << count << "\n";
    }
}