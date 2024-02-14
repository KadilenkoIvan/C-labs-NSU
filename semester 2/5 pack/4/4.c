//#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

FILE* in;
FILE* out;

typedef struct Edge
{
    int from;
    int to;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    //int visit;
    int count;
} Vertex;

void sort(int** arr, int n, int* ans)
{
	int pos_i_zero = 0;
	for (int q = 0; q < n; ++q)
	{
		pos_i_zero = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (arr[i][0] == 0)
			{
				ans[q] = i;
				pos_i_zero = i;
				arr[i][0] = -1;
				break;
			}
		}
		if (pos_i_zero == 0)
		{
			fprintf(out, "NO");
			exit(0);
		}
		for (int i = 1; i <= n; ++i)
		{
			if (arr[pos_i_zero][i] == 1)
			{
				--arr[i][0];
			}
		}
	}
}

int main()
{
    //init
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");

	int m = 0, n = 0;
	fscanf(in, "%d %d", &n, &m);

	int** arr = (int**)malloc(sizeof(int*) * (n + 1));
	memset(arr, 0, sizeof(int*) * (n + 1));
	for (int i = 0; i <= n; ++i)
	{
		arr[i] = (int*)malloc(sizeof(int) * (n + 1));
		memset(arr[i], 0, sizeof(int) * (n + 1));
	}
	int num = 0, link = 0;
	for (int i = 0; i < m; ++i)
	{
		fscanf(in, "%d %d", &num, &link);
		if (arr[num][link] != 0)
			continue;

		arr[num][link] = 1;
		arr[link][0]++;
	}
	int* ans = malloc(sizeof(int) * n);
	sort(arr, n, ans);

	fprintf(out, "YES\n");
	for (int i = 0; i < n; ++i)
	{
		fprintf(out, "%d ", ans[i]);
	}
}