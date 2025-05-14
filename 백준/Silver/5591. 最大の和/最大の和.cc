#include <iostream>
#include <queue>

int main(){
    std::ios_base :: sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n, k, sum = 0, max = -99999999;
    std::queue<int> queue;
    std::cin >> n >> k;
    for(int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        if(queue.size() == k){
            sum -= queue.front();
            queue.pop();
        }
        queue.push(temp);
        sum += temp;
        if(queue.size() == k) max = max > sum ? max : sum;
    }
    std::cout << max;
}