#include <iostream>
#include <vector>

int r, c, t;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
std::vector<std::vector<int>> map;

int top = -1;
int bottom = -1;

void simulate();
void circulate(bool is_up, int i, int j, int n);

int main() {
    std::cin >> r >> c >> t;

    map.resize(r);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int temp;
            std::cin >> temp;
            map[i].push_back(temp);

            if (temp == -1) {
                if (top == -1) top = i;
                else bottom = i;
            }
        }
    }

    //시뮬레이션
    for (int i = 0; i < t; i++) {
        simulate();
    }

    // 결과
    int count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) if(map[i][j] != -1) count += map[i][j];
    }

    std::cout << count;
}

void simulate() {
    std::vector<std::vector<int>> change(r, std::vector<int>(c, 0));

    // 미세먼지 확산
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (map[i][j] == -1 && map[i][j] < 5) continue;
            for (int k = 0; k < 4; k++) {
                int tempy = i + dy[k];
                int tempx = j + dx[k];

                //범위 검사
                if (tempy < 0 || tempy >= r ||
                    tempx < 0 || tempx >= c) continue;

                //공기 청정기가 있는지 검사
                if (map[tempy][tempx] == -1) continue;

                change[tempy][tempx] += map[i][j] / 5;
                change[i][j] -= map[i][j] / 5;
            }
        }
    }

    // 미세먼지 확산 반영
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            map[i][j] += change[i][j];
        }
    }

    // 위쪽 공기청정기
    circulate(true, top, 1, 0);
    // 아래쪽 공기청정기
    circulate(false, bottom, 1, 0);
}

void circulate(bool is_up, int i, int j, int n) {
    if (map[i][j] == -1) return;

    // 1열에 있는 경우
    if (j == 0) {
        if (is_up) circulate(is_up, i + 1, j, map[i][j]);
        else circulate(is_up, i - 1, j, map[i][j]);
    }
    // 1행 또는 마지막행에 있는 경우
    else if (i == 0 || i == r - 1) circulate(is_up, i, j - 1, map[i][j]);
    // 마지막열에 있는 경우
    else if (j == c - 1) {
        if (is_up) circulate(is_up, i - 1, j, map[i][j]);
        else circulate(is_up, i + 1, j, map[i][j]);
    }
    else circulate(is_up, i, j + 1, map[i][j]);

    // 마지막 맵에 반영
    map[i][j] = n;
}