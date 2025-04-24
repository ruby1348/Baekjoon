#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 101

typedef struct point {
	long long x, y;
} point;

int CCW(point a, point b, point c);
point start;

int compare1(const void* a, const void* b);
int compare2(const void* a, const void* b);
double calculate(point a, point b);

int main() {
	int T, n;
	double sum;
	point arr[MAX_SIZE];
	point stack[MAX_SIZE];
	int top;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		sum = 0;
		top = -1;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &arr[i].x, &arr[i].y);
		}

		//좌표 순 정렬
		qsort(arr, n, sizeof(point), compare1);

		start = arr[0];

		//반시계 순서 정렬
		qsort(arr + 1, n - 1, sizeof(point), compare2);


		stack[++top] = arr[0];
		stack[++top] = arr[1];
		for (int i = 2; i < n; i++) {
			while (top > 0 && CCW(stack[top - 1], stack[top], arr[i]) <= 0) top--;
			stack[++top] = arr[i];
		}
	

		for (int i = 1; i <= top; i++) {
			sum += calculate(stack[i - 1], stack[i]);
		}
		sum += calculate(stack[top], stack[0]);

		printf("%.2lf\n", sum);
	}
}

int CCW(point a, point b, point c) {
	long long result;

	result = (b.x - a.x) * (c.y - a.y)
		- (b.y - a.y) * (c.x - a.x);

	if (result == 0) return 0;
	else if (result < 0) return -1;
	else return 1;
}

int compare1(const void* a, const void* b) {
	if (((point*)a)->y == ((point*)b)->y) return ((point*)a)->x - ((point*)b)->x;
	else return ((point*)a)->y - ((point*)b)->y;
}

int compare2(const void* a, const void* b) {
	int ccw = CCW(start, *(point*)a, *(point*)b);

	if (ccw == 0) {
		if (((point*)a)->y == ((point*)b)->y) return ((point*)a)->x - ((point*)b)->x;
		else return ((point*)a)->y - ((point*)b)->y;
	}
	else return ccw * -1;
}

double calculate(point a, point b) {
	double cal;
	cal = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
	cal = sqrt(cal);
	return cal;
}