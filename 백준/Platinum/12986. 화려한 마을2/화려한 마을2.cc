#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 200001

typedef struct query {
	int start, end, index;
} query;

int counting[MAX_SIZE];
int counting_size[MAX_SIZE];
int compare(const void* a, const void* b);

int main() {
	int n, t;
	int left, right;
	query q_arr[MAX_SIZE];
	int arr[MAX_SIZE];
	int result[MAX_SIZE];
	int max;
	scanf("%d %d", &n, &t);

	for (int i = 0; i < MAX_SIZE; i++) {
		counting[i] = 0;
		counting_size[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		arr[i] += 100000;
	}

	for (int i = 0; i < t; i++) {
		scanf("%d %d", &q_arr[i].start, &q_arr[i].end);
		q_arr[i].start--;
		q_arr[i].end--;
		q_arr[i].index = i;
	}

	qsort(q_arr, t, sizeof(query), compare);

	left = 0;
	right = 0;
	counting[arr[0]]++;
	counting_size[1] = 1;
	max = 1;
	for (int i = 0; i < t; i++) {

		while (left < q_arr[i].start) {
			counting_size[counting[arr[left]]]--;
			counting[arr[left]]--;
			counting_size[counting[arr[left]]]++;
			if (counting_size[max] == 0) max--;
			left++;
		}
		while (left > q_arr[i].start) {
			left--;
			counting_size[counting[arr[left]]]--;
			counting[arr[left]]++;
			counting_size[counting[arr[left]]]++;
			if (counting[arr[left]] > max) max = counting[arr[left]];
		}

		while (right < q_arr[i].end) {
			right++;
			counting_size[counting[arr[right]]]--;
			counting[arr[right]]++;
			counting_size[counting[arr[right]]]++;
			if (counting[arr[right]] > max) max = counting[arr[right]];
		}
		while (right > q_arr[i].end) {
			counting_size[counting[arr[right]]]--;
			counting[arr[right]]--;
			counting_size[counting[arr[right]]]++;
			if (counting_size[max] == 0) max--;
			right--;
		}

		result[q_arr[i].index] = max;
	}

	for (int i = 0; i < t; i++) {
		printf("%d\n", result[i]);
	}

}

int compare(const void* a, const void* b) {
	query qa = *(query*)a;
	query qb = *(query*)b;

	int sqrt_n = sqrt(MAX_SIZE);
	int a_start = qa.start / sqrt_n;
	int b_start = qb.start / sqrt_n;

	if (a_start == b_start) return qa.end - qb.end;
	else return a_start - b_start;
}