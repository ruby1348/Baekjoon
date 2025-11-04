#include <iostream>
#include <vector>
#include <algorithm>

class Node{
public:
    int full = 0;
    int half = 0;
    int not_eat = 0;
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL), std::cout.tie(NULL);
    
    int n;
    std::cin >> n;
    std::vector<Node> vec(n + 1);
    for(int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;

        if(i == 0) vec[i].full = temp;
        if(i > 0) {
            vec[i].full = vec[i - 1].not_eat + temp;
            vec[i].half = vec[i - 1].full + temp / 2;
            vec[i].not_eat = std::max({vec[i - 1].full, vec[i - 1].half, vec[i - 1].not_eat});
        }
    }

    std::cout << std::max({vec[n - 1].full, vec[n - 1].half, vec[n - 1].not_eat});
}