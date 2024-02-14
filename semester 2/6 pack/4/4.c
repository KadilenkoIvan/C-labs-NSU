//#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define inf 1000000000001

FILE* in;
FILE* out;

typedef struct Item
{
	int value;
	int pos;
} Item;

Item* func(int n, int* arr)
{
	int* prev = malloc(sizeof(int) * n);
	int* d = malloc(sizeof(int) * n);

	for (int i = 0; i < n; ++i)
	{
		d[i] = 1;
		prev[i] = -1;
		for (int j = 0; j < i; ++j)
		{
			if (arr[j] < arr[i] && d[j] + 1 > d[i])
			{
				d[i] = d[j] + 1;
				prev[i] = j;
			}
		}
	}

	int pos = 0;
	int length = d[0];
	for (int i = 0; i < n; ++i)
	{
		if (d[i] > length)
		{
			pos = i;
			length = d[i];
		}
	}

	Item* ans = malloc(sizeof(Item) * (n + 1));
	ans[n].value = 0;
	while (pos != -1)
	{
		ans[ans[n].value].value = arr[pos];
		ans[ans[n].value].pos = pos;
		pos = prev[pos];
		++ans[n].value;
	}

	return ans;
}

int main()
{
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	int n = 0;
	fscanf(in, "%d", &n);
	int* arr = malloc(sizeof(int) * (n));
	for (int i = 0; i < n; ++i)
	{
		fscanf(in, "%d ", &arr[i]);
	}

	int* arr_ind = malloc(sizeof(int) * n);

	Item* ans = func(n, arr);
	fprintf(out, "%d\n", ans[n]);
	for (int i = ans[n].value - 1; i >= 0; --i)
	{
		fprintf(out, "A[%d] = %d\n", ans[i].pos + 1, ans[i].value);
	}
}