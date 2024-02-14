#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b)
{
	int x = *(int*)a;
	int y = *(int*)b;
	return (x == y ? 0 : (x < y ? 1 : -1));
}

typedef struct pair_s
{
	int* arr[2];
}pair;

typedef struct set_s
{
	pair* arr;
	int size;
}set;

typedef struct vec_s
{
	int* arr;
	int size;
}vec;

int pos = 0;

void sort(int n, vec* arr)
{
	int* indegree = malloc(sizeof(int) * (n + 1));
	memset(indegree, 0, sizeof(int) * (n + 1));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < arr[i].size; ++j)
		{
			indegree[arr[i].arr[j]]++;
		}
	}
	vec my_set;
	my_set.arr = NULL;
	my_set.size = 0;
	for (int i = 0; i < n; ++i)
	{
		if (indegree[i] == 0)
		{
			my_set.arr = realloc(my_set.arr, sizeof(int) * (my_set.size + 1));
			my_set.arr[my_set.size] = i;
			my_set.size++;
		}
	}
	qsort(my_set.arr, my_set.size, sizeof(int), cmp);
	int count = 0, u = 0;
	vec top_order;
	top_order.arr = NULL;
	top_order.size = 0;
	while (my_set.size != 0)//6 6 5 2 5 0 4 0 4 1 2 3 3 1
	{
		u = my_set.arr[my_set.size - 1];
		--my_set.size;
		top_order.arr = realloc(top_order.arr, sizeof(int) * (top_order.size + 1));
		top_order.arr[top_order.size] = u + 1;
		top_order.size++;
		for (int x = 0; x < arr[u].size; ++x)
		{	
			--indegree[arr[u].arr[x]];
			if (indegree[arr[u].arr[x]] == 0)
			{
				my_set.arr = realloc(my_set.arr, sizeof(int) * (my_set.size + 1));
				my_set.arr[my_set.size] = arr[u].arr[x];
				my_set.size++;
			}
		}
		count++;
	}

	if (count != n)
	{
		printf("bad course");
		exit(0);
	}

	for (int i = 0; i < top_order.size; ++i)
	{
		printf("%d ", top_order.arr[i]);
	}
}

int main()
{
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);

	vec* arr = malloc(sizeof(vec) * (n + 1));
	memset(arr, NULL, sizeof(vec) * (n + 1));
	int posq = 0, link = 0, cheak = 0;
	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d", &posq, &link);
		--posq;
		--link;
		if (posq == link)
		{
			printf("bad course");
			exit(0);
		}
		arr[posq].arr = realloc(arr[posq].arr, sizeof(int) * (arr[posq].size + 1));
		arr[posq].arr[arr[posq].size] = link;
		++arr[posq].size;
	}

	sort(n, arr);
	free(arr);
}
//