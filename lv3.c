#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STACK_SIZE 100000

typedef struct LinkedListNode {
	unsigned int x;
	struct LinkedListNode* next;
} NODE;

typedef struct LinkedList {
	NODE* head;
} LIST;

unsigned int stackPopLL(LIST* list) {
	unsigned int x = list->head->x;
	NODE* temp = list->head;
	list->head = list->head->next;
	free(temp);

	return x;
}

int stackIsEmptyLL(LIST* list) {
	if (!list->head) {
		return 1;
	}

	return 0;
}

void stackClearLL(LIST* list) {
	while (!stackIsEmptyLL(list)) {
		stackPopLL(list);
	}
}

void stackPushLL(LIST* list, unsigned int x) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (!newNode) {
		printf("Stack overflow");
		exit(1);
		return;
	}

	newNode->x = x;
	newNode->next = list->head;
	list->head = newNode;
}

void stackClear(unsigned int* Sp) {
	*Sp = 0;
}

int stackIsEmpty(unsigned int Sp) {
	if (!Sp) {
		return 1;
	}

	return 0;
}

void stackPush(unsigned int* stack, unsigned int* Sp, unsigned int x) {
	if (*Sp == STACK_SIZE) {
		printf("Stack overflow");
		exit(1);
		return;
	}

	stack[*Sp] = x;
	(*Sp)++;
}

unsigned int stackPop(unsigned int* stack, unsigned int* Sp) {
	if (!*Sp) {
		printf("Failed to pop: empty stack");
		return -1;
	}

	(*Sp)--;
	return stack[*Sp];
}

unsigned int factorial(unsigned int x) {
	if (x <= 1) {
		return x;
	}

	return x * factorial(x - 1);
}

unsigned int binCoef(unsigned int n, unsigned int k) {
	if (k > n) return 0;
	if (k == 0 || k == n) return 1;

	return binCoef(n - 1, k - 1) + binCoef(n - 1, k);
}

unsigned int binCoefStack(unsigned int n, unsigned int k) {
	unsigned int sp1 = 0, sp2 = 0, a, b, res = 0;
	unsigned int stack1[STACK_SIZE] = { 0 };
	unsigned int stack2[STACK_SIZE] = { 0 };

	stackPush(stack1, &sp1, n);
	stackPush(stack2, &sp2, k);


	while (!stackIsEmpty(sp1)) {
		a = stackPop(stack1, &sp1);
		b = stackPop(stack2, &sp2);

		if (a == b || b == 0) {
			res++;
		} else {
			stackPush(stack1, &sp1, a - 1);
			stackPush(stack2, &sp2, b - 1);
			stackPush(stack1, &sp1, a - 1);
			stackPush(stack2, &sp2, b);
		}
	}

	return res;
}

unsigned int binCoefStackLL(unsigned int n, unsigned int k) {
	unsigned int a, b, res = 0;
	LIST list1 = { 0 };
	LIST list2 = { 0 };

	stackPushLL(&list1, n);
	stackPushLL(&list2, k);


	while (!stackIsEmptyLL(&list1)) {
		a = stackPopLL(&list1);
		b = stackPopLL(&list2);

		if (a == b || b == 0) {
			res++;
		}
		else {
			stackPushLL(&list1, a - 1);
			stackPushLL(&list2, b - 1);
			stackPushLL(&list1, a - 1);
			stackPushLL(&list2, b);
		}
	}

	return res;
}

int main() {
	unsigned long long t0 = 0, t1 = 0;

	t0 = clock();
	printf("Recursive:\t%u\n", binCoef(25, 12));
	t1 = clock();
	printf("Time:\t\t%llums\n\n", t1 - t0);

	t0 = clock();
	printf("Stack:\t\t%u\n", binCoefStack(25, 12));
	t1 = clock();
	printf("Time:\t\t%llums\n\n", t1 - t0);

	t0 = clock();
	printf("LLStack:\t%u\n", binCoefStackLL(25, 12));
	t1 = clock();
	printf("Time:\t\t%llums\n", t1 - t0);
}