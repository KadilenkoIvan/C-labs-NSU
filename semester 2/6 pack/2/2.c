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

long long func(int sum, int last, int n, long long** memo)
{
	if (memo[sum][last] == -1)
	{
		long long res = 0;
		if (sum == n)
			res = 1;
		else
		{
			for (int x = 1; x <= min(last, n - sum); ++x)
			{
				res = ((((res + func(sum + x, x, n, memo)) % M) + M) % M);
			}
		}
		memo[sum][last] = res;
	}
	return (memo[sum][last]);
}

int main()
{
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");

	int n = 0;
	fscanf(in, "%d", &n);
	long long** memo = (long long**)malloc(sizeof(long long*) * (n + 1));
	for (int i = 0; i < n + 1; ++i)
	{
		memo[i] = (long long*)malloc(sizeof(long long) * (n + 1));
		for (int j = 0; j < n + 1; ++j)
		{
			memo[i][j] = -1;
		}
	}
	fprintf(out, "%d", (((func(0,n,n,memo) % M) + M) % M));
}