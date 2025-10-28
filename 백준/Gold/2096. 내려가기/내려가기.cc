#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int max[2][3];
int min[2][3];

int main() {
    int n, a, b, c;
    int maxv, minv;
    int tmax, tmin;
    scanf("%d", &n);

    scanf("%d %d %d", &a, &b, &c);
    max[0][0] = a;
    max[0][1] = b;
    max[0][2] = c;
    min[0][0] = max[0][0];
    min[0][1] = max[0][1];
    min[0][2] = max[0][2];

    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        min[1][0] = (min[0][0] < min[0][1]) ? min[0][0] + a : min[0][1] + a;
        max[1][0] = (max[0][0] > max[0][1]) ? max[0][0] + a : max[0][1] + a;

        min[1][2] = (min[0][2] < min[0][1]) ? min[0][2] + c : min[0][1] + c;
        max[1][2] = (max[0][2] > max[0][1]) ? max[0][2] + c : max[0][1] + c;

        tmin = min[0][0];
        tmax = max[0][0];
        for (int i = 1; i < 3; i++) {
            tmin = (tmin < min[0][i]) ? tmin : min[0][i];
            tmax = (tmax > max[0][i]) ? tmax : max[0][i];
        }

        min[1][1] = tmin + b;
        max[1][1] = tmax + b;

        min[0][0] = min[1][0];
        min[0][1] = min[1][1];
        min[0][2] = min[1][2];

        max[0][0] = max[1][0];
        max[0][1] = max[1][1];
        max[0][2] = max[1][2];
          
    }

    maxv = (max[0][0] > max[0][1]) ? max[0][0] : max[0][1];
    maxv = (max[0][2] > maxv) ? max[0][2] : maxv;
    minv = (min[0][0] < min[0][1]) ? min[0][0] : min[0][1];
    minv = (min[0][2] < minv) ? min[0][2] : minv;

    printf("%d %d", maxv, minv);
}