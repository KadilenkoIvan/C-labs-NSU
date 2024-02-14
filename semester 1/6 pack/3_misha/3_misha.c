#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include < string.h >

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int type;
	char stroka[10001];
	char a;
	int n, count = 0;
	int len;
	int index; // индекс
	int j = 0;
	scanf("%d", &n);
	char** arr = malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		scanf("%d", &type);
		if (type == 0) {
			scanf("%d", &len);
			len++;
			scanf("%s", &stroka);
			char* str = (char*)malloc(len * sizeof(char));
			strcpy(str, stroka);// srr-куда , stroka-откуда
			arr[j] = str;
			j++;
		}
		if (type == 1) {
			scanf("%d", &index);
			free(arr[index]);
		}
		if (type == 2) {
			scanf("%d", &index);
			printf("%s\n", arr[index]);
		}
		if (type == 3) {
			scanf("%d", &index);
			scanf(" %c", &a);
			for (int l = 0; arr[index][l] != NULL; l++) {
				if (arr[index][l] == a)
				{
					count++;
				}
			}
			printf("%d\n", count);
			count = 0;
		}
	}
	free(arr);

}