#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 200000

//푸는 방법: 우선순위 큐 만들어서 종료시간 끝날 때마다 제거, 시작 시간 하나 시작할때마다 삽입하는 형식, 우선순위 큐가 가장 큰 사이즈일때
//당연히 시뮬레이션은 시작시간 기준 qsort, 우선순위 큐는 종료 시간 기준 최소힙, 시작 시간 < 종료 시간일 경우 우선순위 큐에 삽입

typedef struct lecture {
    int start, end;
} lecture;

int compare(const void* a, const void* b);
void pop();
void push(lecture item);

int max = 0;

lecture queue[MAX_SIZE];
int queue_size = 0;

int main() {
    int n;
    int te;
    lecture list[MAX_SIZE];


    lecture temp;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &list[i].start, &list[i].end);
    }

    qsort(list, n, sizeof(lecture), compare);

    

    for (int i = 0; i < n; i++) {
        temp = list[i];

        while (queue_size > 0 && temp.start >= queue[1].end) {
            pop();
        }

        push(temp);
    }

    printf("%d", max);
}

int compare(const void* a, const void* b) {
    if (((lecture*)a)->start > ((lecture*)b)->start) return 1;
    else if (((lecture*)a)->start == ((lecture*)b)->start) {
        if (((lecture*)a)->end > ((lecture*)b)->end) {
            return 1;
        }
        else if (((lecture*)a)->end == ((lecture*)b)->end) return 0;
        else return -1;
    }
    else return -1;
}

void pop() {
    int point = 1;
    int child;
    lecture temp;

    queue[1] = queue[queue_size--];

    while (point * 2 <= queue_size) {
        child = point * 2;
        if (child < queue_size && queue[child].end > queue[child + 1].end) {
            child++;
        }

        if (queue[point].end > queue[child].end) {
            temp = queue[point];
            queue[point] = queue[child];
            queue[child] = temp;
            point = child;
        }
        else {
            break;
        }
    }

}

void push(lecture item) {
    int point;
    lecture temp;

    queue[++queue_size] = item;
    point = queue_size;

    while (point > 1) {
        if (queue[point].end < queue[point/ 2].end) {
            temp = queue[point];
            queue[point] = queue[point / 2];
            queue[point / 2] = temp;
            point = point / 2;
        }
        else break;
    }

    max = (max > queue_size) ? max : queue_size;
}