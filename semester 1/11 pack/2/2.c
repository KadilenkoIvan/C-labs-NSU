#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct list_s
{
	int value;
	struct list_s* next;
}list;

typedef void (*callback)(void* ctx, int* value);

void callback_f(void* cnt, int* value)
{
	if (*value % 2 == 0)
	{
		*(int*)cnt += *value;
	}
}

void arrayForeach(void* ctx, callback func, int* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		func(ctx, &arr[i]);
	}
}

void listForeach(void* ctx, callback func, list* head, int n)
{
	list* curr = head->next;
	while (curr != NULL)
	{
		func(ctx, &(curr->value));
		curr = curr->next;
	}
}

list* create_new(int value)
{
	list* new = malloc(sizeof(list));
	new->value = value;
	new->next = NULL;
	return new;
}

int main()
{
	int n = 0;
	scanf("%d", &n);

	int* arr = malloc(sizeof(int) * n);
	memset(arr, 0, sizeof(int) * n);

	list head;
	head.value = 0;
	head.next = NULL;
	list* curr = &head;

	int value = 0;

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &value);
		arr[i] = value;

		curr->next = create_new(value);
		curr = curr->next;
	}

	int sum_arr = 0;
	int sum_list = 0;

	arrayForeach(&sum_arr, callback_f, arr, n);
	listForeach(&sum_list, callback_f, &head, n);

	printf("%d %d", sum_arr, sum_list);
}