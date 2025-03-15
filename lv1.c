#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define N 10

int sekv_pret(float V[], int n, float x) {
	for (int i = 0; i < n; i++) {
		if (V[i] == x) {
			return i;
		}
	}

	return -1;
}

void swap(float* a, float* b) {
	float t = *a;
	*a = *b;
	*b = t;
}

int partition(float arr[], int low, int high) {
	float pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}


void quickSort(float arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void sort(float V[], int n) {
	quickSort(V, 0, n - 1);
}

int bin_pret(float V[], int n, float x) {
	int low = 0, high = n, s;

	while (low <= high) {
		s = low + (high - low) / 2;
		if (x == V[s]) {
			return s;
		} else if (x < V[s]) {
			high = s - 1;
		} else {
			low = s + 1;
		}
	}

	return -1;
} 

int main(char argc, char** argv) {
	srand(time(NULL));
	float V[N] = { 0 };

	for (int i = 0; i < N; i++) {
		V[i] = (float)rand() / RAND_MAX;
	}


	for (int i = 0; i < N; i++) {
		if (i == N - 1) {
			printf("%f\n", V[i]);
		}
		else {
			printf("%f, ", V[i]);
		}
	}
}