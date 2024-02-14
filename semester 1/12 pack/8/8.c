#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void sort(char** arr, int n, int* ans)
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
			printf("bad course");
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
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", ans[i]);
	}
}

int main()
{
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	char** arr = (char**)malloc(sizeof(char*) * (n));
	memset(arr, 0, sizeof(char*) * (n));
	for (int i = 0; i <= n; ++i)
	{
		arr[i] = (char*)malloc(sizeof(char) * (n + 1));
		memset(arr[i], 0, sizeof(char) * (n + 1));
	}
	int num = 0, link = 0;
	for (int i = 0; i < m; ++i)
	{
		scanf("%d %d", &num, &link);
		if (arr[num][link] != 0)
			continue;

		arr[num][link] = 1;
		arr[link][0]++;
	}

	int* ans = malloc(sizeof(int) * n);
	sort(arr, n, ans);
}//6 6 3 4 4 2 6 2 6 1 5 1 5 3