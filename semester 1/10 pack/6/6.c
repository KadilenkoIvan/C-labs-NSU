#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int pos = 0, pos2 = 0;

int cmp(const void* a, const void* b)
{
	int x = *(int*)a;
	int y = *(int*)b;
	return (x == y ? 0 : (x < y ? 1 : -1));
}

typedef struct vec_s
{
	int* arr;
	int size;
}vec;

int loop(int v, int* visited, int* rec_stack, vec* arr)
{
	if (visited[v] == 0)
	{
		visited[v] = 1;
		rec_stack[v] = 1;
		for (int i = 0; i < arr[v].size; ++i)
		{
			if (visited[arr[v].arr[i]] == 0 && loop(arr[v].arr[i], visited, rec_stack, arr))
				return 1;
			else if (rec_stack[arr[v].arr[i]])
				return 1;
		}
	}
	rec_stack[v] = 0;
	return 0;
}

void sup(int v, int* used, vec* arr, int* ans, int prev)
{
	used[v] = 1;
	for (int i = 0; i < arr[v].size; ++i)
	{
		if (used[arr[v].arr[i]] == 1)
		{
			continue;
		}
		sup(arr[v].arr[i], used, arr, ans, v);
	}
	ans[pos] = v;
	--pos;
}

int main()//cheak loops
{
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	pos = n;
	vec* arr = malloc(sizeof(vec) * (n + 1));
	memset(arr, NULL, sizeof(vec) * (n + 1));
	int posq = 0, link = 0, cheak = 0;
	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d", &posq, &link);
		if (posq == link)
		{
			printf("bad course");
			exit(0);
		}
		arr[posq].arr = realloc(arr[posq].arr, sizeof(vec) * (arr[posq].size + 1));
		arr[posq].arr[arr[posq].size] = link;
		++arr[posq].size;
	}

	pos = n;
	int* ans1 = malloc(sizeof(int) * (n + 1));
	memset(ans1, 0, sizeof(int) * (n + 1));
	
	int* used = malloc(sizeof(int) * (n + 1));
	memset(used, 0, sizeof(int) * (n + 1));
	int* rec_stack = malloc(sizeof(int) * (n + 1));
	memset(rec_stack, 0, sizeof(int) * (n + 1));

	for (int i = 1; i <= n; ++i)
	{
		if (loop(i, used, rec_stack, arr) == 1)
		{
			printf("bad course");
			exit(0);
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		qsort(arr[i].arr, arr[i].size, sizeof(int), cmp);
	}

	memset(used, 0, sizeof(int) * (n + 1));
	for (int i = 1; i <= n; ++i)
	{
		if (used[i] == 1)
		{
			continue;
		}
		sup(i, used, arr, ans1, i);
	}

	int* ans2 = malloc(sizeof(int) * (n + 1));
	memset(ans2, 0, sizeof(int) * (n + 1));
	memset(used, 0, sizeof(int) * (n + 1));
	pos = n;
	for (int i = n; i >= 1; --i)
	{
		if (used[i] == 1)
		{
			continue;
		}
		sup(i, used, arr, ans2, 0);
	}

	int lower = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (ans1[i] == ans2[i])
			continue;
		if (ans2[i] < ans1[i])
		{
			lower = 2;
			break;
		}
		else
			break;
	}

	if (lower == 1)
	{
		for (int i = 1; i <= n; ++i)
		{
			printf("%d ", ans1[i]);
		}
	}
	else
	{
		for (int i = 1; i <= n; ++i)
		{
			printf("%d ", ans2[i]);
		}
	}
	return 0;
}
//5 8 2 1 3 1 4 1 5 1 4 2 4 3 5 3 5 4
/*for (int i = 1; i <= n; ++i)
	{
		printf("%d) ", i);
		if (arr[i].arr != NULL)
		{
			for (int j = 0; j < arr[i].size; ++j)
			{
				printf("%d ", arr[i].arr[j]);
			}
		}
		printf("\n");
	}*/
	/*for (int i = 1; i <= n; ++i)
	{
		qsort(arr[i].arr, arr[i].size, sizeof(int), cmp);
	}*/
	/*for (int i = 1; i <= n; ++i)
	{
		printf("%d) ", i);
		if (arr[i].arr != NULL)
		{
			for (int j = 0; j < arr[i].size; ++j)
			{
				printf("%d ", arr[i].arr[j]);
			}
		}
		printf("\n");
	}*/