#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int Query(int l, int64_t sum);
int rig = 0;

long long* arr_sum;

void Init(const int* arr, int n)
{
	arr_sum = malloc(sizeof(long long) * (n + 1));
	memset(arr_sum, 0, sizeof(long long) * (n + 1));
	arr_sum[0] = (long long)arr[0];
	for (int i = 1; i < n; ++i)
	{
		arr_sum[i] = arr_sum[i - 1] + arr[i];
		//printf("%lld\n", arr_sum[i]);
	}
	arr_sum[n] = -1;
	rig = n;
}

int64_t Sum(int l, int r)
{
	return arr_sum[r] - arr_sum[l]; // r - 1  ???
}