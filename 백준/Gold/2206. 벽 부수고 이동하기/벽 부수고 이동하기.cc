#include <iostream>
#include <string>
#include <vector>
#include <queue>

class node {
public:
    int x, y, num, b;
};

int n, m;
int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

int result = -1;
std::vector<std::vector<int>> map;
std::vector<std::vector<bool>> visited;
std::vector<std::vector<bool>> visited2;
std::queue<node> queue;
void bfs(int y, int x, int num, int b);

int main() {
    std::cin >> n >> m;
    map.resize(n);
    visited.resize(n);
    visited2.resize(n);

    for (int i = 0; i < n; i++) {
        visited[i].resize(m);
        visited2[i].resize(m);

        std::string str;
        std::cin >> str;
        for (int j = 0; j < m; j++) {
            map[i].push_back(str[j] - '0');
        }
    }

    bfs(0, 0, 1, 1);
    while (queue.size() > 0) {
        node temp = queue.front();
        queue.pop();
        bfs(temp.y, temp.x, temp.num, temp.b);
    }
    std::cout << result;
}

void bfs(int y, int x, int num, int b) {
    // 정답 찾으면 바로 리턴
    if (result != -1) return;

    // 목적지
    if (y == n - 1 && x == m - 1) {
        result = num;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int tempy = y + dy[i];
        int tempx = x + dx[i];
        if (tempy >= 0 && tempy < n && tempx >= 0 && tempx < m) {
            // 벽이 아닌 경우
            if (map[tempy][tempx] == 0) {
                // b==1, b==0인 경우 방문 처리 다르게 하기
                if (b == 1) {
                    if (visited[tempy][tempx]) continue;
                    visited[tempy][tempx] = true;
                }
                if (b == 0) {
                    if (visited2[tempy][tempx]) continue;
                    visited2[tempy][tempx] = true;
                }
                node temp;
                temp.y = tempy;
                temp.x = tempx;
                temp.num = num + 1;
                temp.b = b;
                queue.push(temp);
            }

            // 벽인 경우
            if (map[tempy][tempx] == 1 && b == 1 && visited2[tempy][tempx] == false) {
                visited2[tempy][tempx] = true;
                node temp;
                temp.y = tempy;
                temp.x = tempx;
                temp.num = num + 1;
                temp.b = 0;
                queue.push(temp);
            }
        }
    }
}