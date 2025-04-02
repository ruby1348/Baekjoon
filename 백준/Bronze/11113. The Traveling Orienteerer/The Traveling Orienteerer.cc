#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

int main(){
    int n;
    std::cin >> n;
    std::vector<std::pair<double, double>> vec;
    for(int i = 0; i < n; i++){
        std::pair<double, double> temp;
        std::cin >> temp.first >> temp.second;
        vec.push_back(temp);
    }
    int t;
    std::cin >> t;
    for(int i = 0; i < t; i++){
        int k, start;
        double sum = 0;
        std::cin >> k;
        std::cin >> start;
        std::pair<double, double> point = vec[start];
        for(int j = 1; j < k; j++){
            int temp;
            std::cin >> temp;
            double x = point.first - vec[temp].first;
            double y = point.second - vec[temp].second;
            sum += std::sqrt(x * x + y * y);
            point = vec[temp];
        }
        std::cout << int(sum + 0.5) << "\n";
    }
}