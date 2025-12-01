#include <iostream>
#include <vector>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> vec;

    for (int i = 0; i < n; i++) {
        std::string str;
        std::cin >> str;
        vec.push_back(std::vector<int>());
        for (int j = 0; j < m; j++) {
            vec[i].push_back(str[j] - '0');
        }
    }
    bool result = true;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (vec[i][j] && vec[i + 1][j] && vec[i + 1][j + 1] && vec[i][j + 1]) result = false;
        }
    }

    if (result) std::cout << 0;
    else std::cout << 1;
}