#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct binaryTreeNode {
	char x;
	struct binaryTreeNode* left;
	struct binaryTreeNode* right;
};
typedef struct binaryTreeNode BTNODE;

int treeFind(BTNODE* root, char x) {
	if (root == NULL) {
		return -1;
	}
	int found = 0;
	BTNODE* curr = root;

	while (true) {
		if (curr->x == x) {
			found = 1;
		} else {
			if (x < curr->x) {
				if (curr->left != NULL) {
					curr = curr->left;
				} else {
					found = -1;
				}
			}
			if (x > curr->x) {
				if (curr->right != NULL) {
					curr = curr->right;
				} else {
					found = -1;
				}
			}
		}

		if (found) {
			return found;
		}
	}
}

int treeFindRec(BTNODE* root, char x) {
	int found = -1;
	BTNODE *curr = root, *parent = NULL;

	if (curr == NULL || curr->x == x) {
		found = 1;
		return found;
	}

	parent = curr;

	if (curr->x > x) {
		found = treeFindRec(curr->left, x);
	} else {
		found = treeFindRec(curr->right, x);
	}

	return found;
}

void treeAdd(BTNODE** root, char x) {
	if (treeFind(*root, x) == 1) {
		return;
	}

	BTNODE *curr = *root, *parent = *root, *newNode = NULL;

	while (curr) {
		parent = curr;
		if (x < curr->x && curr->left != NULL) {
			curr = curr->left;
		} else if (x > curr->x && curr->right != NULL) {
			curr = curr->right;
		} else {
			break;
		}
	}

	newNode = (BTNODE*)malloc(sizeof(BTNODE));
	if (!newNode) {
		printf("MALLOC FAILED");
		return;
	}


	newNode->x = x;
	newNode->left = NULL;
	newNode->right = NULL;

	if (parent == NULL) {
		*root = newNode;
	} else {
		if (x < parent->x) {
			parent->left = newNode;
		} else {
			parent->right = newNode;
		}
	}
}

void printTreePre(BTNODE* root) {
	if (root == NULL) {
		return;
	}

	BTNODE* curr = root;

	printf("%c ", curr->x);

	printTreePre(curr->left);
	printTreePre(curr->right);
}

void printTreePost(BTNODE* root) {
	if (root == NULL) {
		return;
	}

	BTNODE* curr = root;

	printTreePost(curr->left);
	printTreePost(curr->right);
	printf("%c ", curr->x);
}

void printTreeIn(BTNODE* root) {
	if (root == NULL) {
		return;
	}

	BTNODE* curr = root;

	printTreeIn(curr->left);
	printf("%c ", curr->x);
	printTreeIn(curr->right);
}

int main() {
	BTNODE* tree = NULL;
	char ime[16] = "antoniostruklec";
	
	for (int i = 0; i < 15; i++) {
		treeAdd(&tree, ime[i]);
	}

	printf("PRE: ");
	printTreePre(tree);
	printf("\nIN: ");
	printTreeIn(tree);
	printf("\nPOST: ");
	printTreePost(tree);
}