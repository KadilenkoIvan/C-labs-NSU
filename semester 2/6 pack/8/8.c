//#pragma comment (linker, "/STACK:50000000000000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define M 1000000007

FILE* in;
FILE* out;

typedef struct Item
{
	int weight;
	int cost;
} Item;

int func(int k, int n, int sumW, int maxW, Item* items, int** memo, char** path)//1 - Ctake, 2 - Cskip
{
	if (sumW <= maxW && k <= n)
	{
		if (memo[k][sumW] == -1)
		{
			if (k == n)
				return 0;

			int Cskip = func(k + 1, n, sumW, maxW, items, memo, path);
			int Ctake = 0;
			if (sumW + items[k].weight <= maxW)
			{
				Ctake = func(k + 1, n, sumW + items[k].weight, maxW, items, memo, path) + items[k].cost;
			}
			if (Cskip <= Ctake)//maybe just <
			{
				path[k][sumW] = 1;
				memo[k][sumW] = Ctake;
			}
			else
			{
				path[k][sumW] = 2;
				memo[k][sumW] = Cskip;
			}
			//memo[k][sumW] = max(Cskip, Ctake);
		}
		return memo[k][sumW];
	}
	else
		return -1;
}

void backpack(Item* items, int n, int maxW, int** matrix)
{
	for (int i = 0; i < n + 1; ++i)//maybe juct i < n
	{
		matrix[i][0] = 0;
	}
	for (int i = 0; i <= maxW; ++i)
	{
		matrix[0][i] = 0;
	}

	for (int k = 1; k < n + 1; ++k)
	{
		for (int s = 1; s < maxW + 1; ++s)
		{
			if (s >= items[k].weight)
			{
				matrix[k][s] = max(matrix[k - 1][s], matrix[k - 1][s - items[k].weight] + items[k].cost);
			}
			else
			{
				matrix[k][s] = matrix[k - 1][s];
			}
		}
	}
}

int my_weight = 0;
void find_path(int k, int s, int** matrix, Item* items, int* ans, int* count)
{
	if (matrix[k][s] == 0)
		return;
	if (matrix[k - 1][s] == matrix[k][s])
		find_path(k - 1, s, matrix, items, ans, count);
	else
	{
		find_path(k - 1, s - items[k].weight, matrix, items, ans, count);
		ans[*count] = k;
		++(*count);
		my_weight += items[k].weight;
	}
}

int main()
{
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");

	int n = 0, w = 0;
	fscanf(in, "%d %d", &n, &w);

	Item* items = malloc(sizeof(Item) * (n + 1));
	for (int i = 1; i < n + 1; ++i)
	{
		fscanf(in, "%d %d", &items[i].weight, &items[i].cost);
	}
	int** memo = malloc(sizeof(int*) * (n + 1));
	char** path = malloc(sizeof(char*) * (n + 1));
	for (int i = 0; i < n + 1; ++i)
	{
		memo[i] = malloc(sizeof(int) * (w + 1));
		path[i] = malloc(sizeof(char) * (w + 1));
		//for (int j = 0; j < w + 1; ++j)
		//{
		//	memo[i][j] = -1;
		//	path[i][j] = 0;
		//}
	}
	backpack(items, n, w, memo);
	/*for (int i = 0; i < n + 1; ++i)
	{
		for (int j = 0; j < w + 1; ++j)
		{
			printf("%d ", memo[i][j]);
		}
		printf("\n");
	}*/
	int* ans = malloc(sizeof(int) * (n + 1));
	int count = 0;
	find_path(n, w, memo, items, ans, &count);
	printf("%d %d %d\n", count, my_weight, memo[n][w]);
	for (int i = 0; i < count; ++i)
	{
		printf("%d ", ans[i]);
	}
}
