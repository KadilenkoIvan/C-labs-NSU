#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int bitword;

//инициализирует массив битов длины num, устанавливая все его биты в ноль
void bitsetZero(bitword* arr, int num)
{
	memset(arr, 0, num);
}

//возвращает значение idx-ого бита (0 или 1)
int bitsetGet(const bitword* arr, int idx)
{
	int index_in_arr = idx / (sizeof(bitword) * 8);
	/*if (idx % sizeof(bitword) == 0)
		--index_in_arr;*/
	idx -= index_in_arr * sizeof(bitword) * 8;
	bitword mask = 1 << (8 * sizeof(bitword) - idx - 1);
	if (arr[index_in_arr] == (arr[index_in_arr] | mask))
		return 1;
	else
		return 0;
}

//устанавливает значение idx-ого бита в newval (которое равно 0 или 1)
void bitsetSet(bitword* arr, int idx, int newval)
{
	int index_in_arr = idx / (sizeof(bitword) * 8);
	idx -= index_in_arr * sizeof(bitword) * 8;
	bitword max;
	if (newval == 0)
	{
		max = INT_MAX - (1 << (8 * sizeof(bitword) - idx - 1));
		arr[index_in_arr] = arr[index_in_arr] & max;
	}
	else
	{
		max = 1;
		arr[index_in_arr] = arr[index_in_arr] | 1 << (8 * sizeof(bitword) - idx - 1);
	}
}

//возвращает 1, если среди битов с номерами k
//для left <= k < right есть единичный, и 0 иначе
int bitsetAny(const bitword* arr, int left, int right)
{
	int left_index_in_arr = left / (sizeof(bitword) * 8);
	left -= left_index_in_arr * sizeof(bitword) * 8;

	int right_index_in_arr = right / (sizeof(bitword) * 8);
	right -= right_index_in_arr * sizeof(bitword) * 8;

	bitword start_mask = 1 << (8 * sizeof(bitword) - left - 1);
	bitword mask = start_mask;
	int limit;
	if (left_index_in_arr == right_index_in_arr)
		limit = right;
	else
		limit = sizeof(bitword) * 8;

	for (int i = left; i < limit; ++i)
	{
		if(arr[left_index_in_arr] == (arr[left_index_in_arr] | mask))
			return 1;
		mask = mask >> 1;
	}
	
	if (left_index_in_arr == right_index_in_arr)
		return 0;
	
	++left_index_in_arr;

	while (left_index_in_arr != right_index_in_arr)
	{
		mask = start_mask;
		for (int i = 0; i < 32; ++i)
		{
			if (arr[left_index_in_arr] == (arr[left_index_in_arr] | mask))
				return 1;
			mask = mask >> 1;
		}//1441
		++left_index_in_arr;
	}

	limit = right;
	mask = start_mask;
	for (int i = 0; i < limit; ++i)
	{
		if (arr[right_index_in_arr] == (arr[right_index_in_arr] | mask))
			return 1;
		mask = mask >> 1;
	}//2352
	return 0;
}

int main(void)
{
	int n = 0, t = 0, ind = 0, left = 0, right = 0, newval = 0, size = 0, index_in_arr = 0;
	bitword* arr = malloc(1);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &t);
		if (t == 0)
		{
			free(arr);
			scanf("%d", &ind);
			size = (ind / 8 / sizeof(bitword)) * sizeof(bitword) + sizeof(bitword);
			arr = malloc(size);
			bitsetZero(arr, size);
			continue;
		}
		if (t == 1)
		{
			scanf("%d", &ind);
			printf("%d\n", bitsetGet(arr, ind));
			continue;
		}
		if (t == 2)
		{
			scanf("%d %d", &ind, &newval);
			bitsetSet(arr, ind, newval);
			continue;
		}
		if (t == 3)
		{
			scanf("%d %d", &left, &right);
			if (bitsetAny(arr, left, right) == 1)
				printf("some\n");
			else
				printf("none\n");
			continue;
		}
	}
}

/*11
0 100
2 30 1
2 31 1
2 32 1
1 31
1 7
2 31 0
1 31
3 45 67
0 48
1 30*/