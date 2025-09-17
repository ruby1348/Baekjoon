#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#define MAX_SIZE 1000000

int compare(const void* a, const void* b);

int main() {
	int num;
	int array[MAX_SIZE];
	int sum = 0;

	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		scanf("%d", &array[i]);
	}

	qsort(array, num, sizeof(array[0]), compare);

	//절사
	int min = (num * 0.15 + 0.5);
	int max = num - min;

	for (int i = min; i < max; i++) {
		sum += array[i];
	}

	if (num != 0) {
		double total = (double)sum / (max - min) + 0.5;
		sum = (int)total;
	}

	if (num != 0) printf("%d", sum);
	else printf("0");
}

int compare(const void* a, const void* b) {
	if (*(int*)a < *(int*)b) return -1;
	else if (*(int*)a > *(int*)b) return 1;
	else return 0;
}