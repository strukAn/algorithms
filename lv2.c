#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _NODE {
	int x;
	struct _NODE* next;
} NODE;

NODE* prvi = NULL;

#define N 1000000

NODE* arrToList(int* arr, int n) {
	NODE* head = NULL;
	NODE* curr = NULL;

	long long t0 = 0, t1 = 0;

	t0 = clock();
	for (int i = 0; i < N; i++) {
		if (!curr) {
			curr = (NODE*)malloc(sizeof(NODE));
			head = curr;
		}

		curr->x = arr[i];

		if (N - 1 != i) {
			curr->next = (NODE*)malloc(sizeof(NODE));
		} else {
			curr->next = NULL;
		}

		curr = curr->next;
	}

	t1 = clock();

	printf("List: %ld\n", t1 - t0);

	return head;
}

void printList(NODE* head) {
	while (head) {
		printf("%d ", head->x);
		head = head->next;
	}
}

int seqList(NODE* head, int x) {
	int found = 0;
	long long t0 = 0, t1 = 0;

	t0 = clock();
	while (head) {
		if (x == head->x) {
			found = 1;
		}
		head = head->next;
	}

	t1 = clock();
	printf("List seq search: %ld\n", t1 - t0);
	return found;
}

int seqArr(int* arr, int n, int x) {
	int found = 0;
	long t0 = 0, t1 = 0;

	t0 = clock();
	for (int i = 0; i < n; i++) {
		if (x == arr[i]) {
			found = 1;
		}
	}

	t1 = clock();

	printf("Dyn arr seq search: %ld\n", t1 - t0);

	return found;
}

long maxListLen() {
	long count = 1;
	NODE* curr = (NODE*)malloc(sizeof(NODE));

	while (1) {
		curr->next = (NODE*)malloc(sizeof(NODE));
		if (curr->next == NULL) {
			break;
		}

		count++;
		curr = curr->next;
	}

	return count;
}

#define UL 32068000000
void maxArrLen() {

	for (long long i = 32067000000; i < UL; i++) {
		int* c = (int*)malloc(sizeof(int) * i);
		if (c == NULL) {
			printf("Arr len: %llu\n", i);
			break;
		}

		free(c);
	}
}

int main() {
	long long t0 = 0, t1 = 0;

	int* darr = NULL;
	darr = (int*)malloc(sizeof(int) * N);

	t0 = clock();
	for (int i = 0; i < N; i++) {
		darr[i] = rand() % 10 + 1;
	}
	t1 = clock();

	printf("Dyn arr: %ld\n" , t1 - t0);


	NODE* head = arrToList(darr, N);

	seqArr(darr, N, -1);
	seqList(head, -1);

	//printf("MAX list: %ld", maxListLen());

	//maxArrLen();

	/*int* c = (int*)malloc(sizeof(int) * 32067000000);
	if (c == NULL) {
		printf("malloc failed");
	}*/
}