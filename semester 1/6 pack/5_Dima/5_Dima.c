#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Node_s {
	char str[8];
	struct Node_s* next;
} node;
typedef struct list_s {
	struct Node_s* first;
	struct Node_s* last;
} list;
list headarr[1000000];
void main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, maxk = 0, mink = 1000001;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d ", &k);
		if (maxk < k) maxk = k;
		if (mink > k) mink = k;
		node* nn = (node*)malloc(sizeof(node));
		nn->next = NULL;
		scanf("%s", nn->str);
		if (headarr[k].first == 0) {
			headarr[k].first = nn;
			headarr[k].last = nn;
		}
		else {
			headarr[k].last->next = nn;
			headarr[k].last = nn;
		}
	}
	for (int k = mink; k <= maxk; k++) {
		for (node* p = headarr[k].first; p; p = p->next)
			printf("%d %s\n", k, p->str);
		node* current = headarr[k].first;
		while (current != NULL) {
			node* nodeToDelete = current;
			current = current->next;
			free(nodeToDelete);
		}
		headarr[k].first = NULL;
		headarr[k].last = NULL;
	}

}