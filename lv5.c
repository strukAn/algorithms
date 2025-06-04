#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 100000

void swap(int* a, int* b) {
	*a += *b;
	*b = *a - *b;
	*a -= *b;
}

void printArr(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

void merge(int arr[], int left, int right, int n, int temp[]) {
	int i = left, j = right;

	for (int k = left; k < n; k++) {
		if (i < right && (j >= n || arr[i] <= arr[j])) {
			temp[k] = arr[i];
			i++;
		} else {
			temp[k] = arr[j];
			j++;
		}
	}
}

void mergeSort(int arr[], int n) {
	int* temp = (int*)malloc(sizeof(int) * n);
	if (!temp) {
		printf("MALLOC FAILED");
		return;
	}

	for (int i = 1; i < n; i *= 2) {
		for (int j = 0; j < n; j += i * 2) {
			merge(arr, j, j + i < n ? j + i : n, j + 2 * i < n ? j + 2 * i : n, temp);
		}

		for (int i = 0; i < n; i++) {
			arr[i] = temp[i];
		}
	}
}

void heapify(int arr[], int n, int index) {
	int max = index;

	int l = (2 * index) + 1;
	int r = (2 * index) + 2;

	if (l < n && arr[l] > arr[index]) {
		max = l;
	}
	else {
		max = index;
	}

	if (r < n && arr[r] > arr[max]) {
		max = r;
	}

	if (max != index) {
		swap(arr + index, arr + max);
		heapify(arr, n, max);
	}
}

void heapSort(int arr[], int n) {
	for (int i = (n - 1) / 2; i >= 0; i--) {
		heapify(arr, n, i);
	}

	for (int i = n; i > 1; i--) {
		swap(&arr[0], &arr[--n]);
		heapify(arr, n, 0);
	}
}

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[i]) {
				swap(arr + i, arr + j);
			}
		}
	}
}

int main() {
	srand(time(NULL));

	int* arr = (int*)malloc(sizeof(int) * N);
	int* bubble = (int*)malloc(sizeof(int) * N);
	int* heap = (int*)malloc(sizeof(int) * N);
	int* merge = (int*)malloc(sizeof(int) * N);

	if (!arr || !bubble || !heap) {
		printf("MALLOC FAILED");
		return -1;
	}


	for (int i = 0; i < N; i++) {
		heap[i] = bubble[i] = merge[i] = arr[i] = rand() % 1000;
	}

	clock_t t0 = 0, t1 = 1;

	//printf("ARR:\t");
	//printArr(arr, N);

	t0 = clock();
	heapSort(heap, N);
	t1 = clock();

	printf("HEAP:\t");
	//printArr(heap, N);
	printf("\tTime: %ld\n", t1 - t0);



	t0 = clock();
	bubbleSort(bubble, N);
	t1 = clock();

	printf("Bubble:\t");
	//printArr(bubble, N);
	printf("\tTime: %ld\n", t1 - t0);



	t0 = clock();
	mergeSort(merge, N);
	t1 = clock();

	printf("Merge:\t");
	//printArr(merge, N);
	printf("\tTime: %ld\n", t1 - t0);
}
