#include <iostream>

int main(){
    int n, m, q;
    std::cin >> n >> m >> q;
    
    int minx = 1;
    int maxx = n;
    int miny = 1;
    int maxy = n;
    
    for(int i = 0; i < q; i++){
        int x, y, mod;
        std::cin >> x >> y >> mod;
        switch(mod){
            case 1:
                minx = std::max(minx, x + 1);
                miny = y;
                maxy = y;
                break;
            case 2:
                maxx = std::min(maxx, x - 1);
                miny = y;
                maxy = y;
                break;
            case 3:
                minx = x;
                maxx = x;
                maxy = std::min(maxy, y - 1);
                break;
            case 4:
                minx = x;
                maxx = x;
                miny = std::max(miny, y + 1);
                break;
            case 5:
                minx = std::max(minx, x + 1);
                miny = std::max(miny, y + 1);
                break;
            case 6:
                maxx = std::min(maxx, x - 1);
                miny = std::max(miny, y + 1);
                break;
            case 7:
                minx = std::max(minx, x + 1);
                maxy = std::min(maxy, y - 1);
                break;
            case 8:
                maxx = std::min(maxx, x - 1);
                maxy = std::min(maxy, y - 1);
                break;
            case 9:
                minx = x;
                maxx = x;
                miny = y;
                maxy = y;
                break;
        }
    }
    
    std::cout << (long long)(maxx - minx + 1) * (long long)(maxy - miny + 1);
}