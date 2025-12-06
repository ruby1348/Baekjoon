#include <iostream>
#include <vector>
#define MAX 1e9 + 1

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> vec(n);

    long long max1 = -MAX, max2 = -MAX;
    long long min1 = MAX, min2 = MAX;

    long long sum = 0;
    for(int i = 0; i < n; i++){
        std::cin >> vec[i];
        sum += vec[i];
        if(vec[i] > max1) {
            max2 = max1;
            max1 = vec[i];
        }
        else if(vec[i] > max2) max2 = vec[i];

        if(vec[i] < min1) {
            min2 = min1;
            min1 = vec[i];
        }
        else if(vec[i] < min2) min2 = vec[i];
    }

    long long sum2 = sum;
    sum -= max1;
    sum -= max2;
    sum += max1 * max2 * 2;

    long long sum3 = sum2;
    sum3 -= min1;
    sum3 -= min2;
    sum3 += min1 * min2 * 2;
    
    if(sum2 > sum) sum = sum2;
    if(sum3 > sum) sum = sum3;
    std::cout << sum;
}