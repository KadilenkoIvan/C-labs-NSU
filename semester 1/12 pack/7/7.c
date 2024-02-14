#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct maximum_s
{
	long long value;
	long long ind;
}maximum;

void find_max(long long* arr, long long left, long long right, maximum* max)
{
	long long ind = 0;
	max->value = INT64_MIN;
	for (long long i = left; i < right; ++i)
	{
		if (arr[i] > max->value)
		{
			max->value = arr[i];
			max->ind = i;
		}
	}
}

long long main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");
	long long n = 0;
	fscanf(in, "%lld", &n);
	long long* arr = malloc(sizeof(long long) * n);
	for (long long i = 0; i < n; ++i)
	{
		fscanf(in, "%lld", &arr[i]);
	}

	long long size = 2 * n;
	char* str = malloc(size);
	fscanf(in, "%s", str);
	long long l = 0, r = 0;
	--size;

	maximum max;
	max.value = arr[0];
	max.ind = 0;

	for (long long i = 0; i < size; ++i)
	{
		if (str[i] == 'R')
		{
			++r;
			if (max.value < arr[r - 1])
			{
				max.value = arr[r - 1];
				max.ind = r - 1;
			}
			fprintf(out, "%lld\n", max.value);
		}
		else
		{
			++l;
			if (max.ind < l)
			{
				find_max(arr, l, r, &max);
			}
			fprintf(out, "%lld\n", max.value);
		}
	}
}