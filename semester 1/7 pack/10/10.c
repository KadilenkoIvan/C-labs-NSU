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
	if (newval == 0)
	{
		bitword max = UINT_MAX - (1 << (8 * sizeof(bitword) - idx - 1));
		arr[index_in_arr] = arr[index_in_arr] & max;
	}
	else
	{
		arr[index_in_arr] = arr[index_in_arr] | 1 << (8 * sizeof(bitword) - idx - 1);
	}
}

//возвращает 1, если среди битов с номерами k
//для left <= k < right есть единичный, и 0 иначе


int bitsetAny(const bitword* arr, int left, int right)
{
	if (left >= right)
		return 0;
	int size = sizeof(bitword);

	int left_index_in_arr = left / (size * 8);
	left -= left_index_in_arr * size * 8;

	--right;
	int right_index_in_arr = right / (size * 8);
	right -= right_index_in_arr * size * 8;

	bitword mask = 0;
	if (left_index_in_arr == right_index_in_arr)
	{
		for (int i = left; i <= right; ++i)
		{
			mask = mask + (1 << (8 * size - i - 1));
		}
		if ((arr[left_index_in_arr] & mask) != 0)
			return 1;
		return 0;
	}

	for (int i = left; i < 32; ++i)
	{
		mask = mask + (1 << (8 * size - i - 1));
	}
	if ((arr[left_index_in_arr] & mask) != 0)
		return 1;

	++left_index_in_arr;
	mask = UINT_MAX;
	while (left_index_in_arr != right_index_in_arr)
	{
		if ((arr[left_index_in_arr] & mask) != 0)
			return 1;
		++left_index_in_arr;
	}

	mask = 0;
	for (int i = 0; i <= right; ++i)
	{
		mask = mask + (1 << (8 * size - i - 1));
	}
	if ((arr[left_index_in_arr] & mask) != 0)
		return 1;
	return 0;
}

//установить в val значение всех k-ых битов для left <= k < right
void bitsetSetSeg(bitword* arr, int left, int right, int newval)
{
	if (left >= right)
		return;
	int size = sizeof(bitword);

	int left_index_in_arr = left / (size * 8);
	left -= left_index_in_arr * size * 8;

	--right;
	int right_index_in_arr = right / (size * 8);
	right -= right_index_in_arr * size * 8;

	bitword mask = 0;
	if (newval == 1)
	{
		if (left_index_in_arr == right_index_in_arr)
		{
			for (int i = left; i <= right; ++i)
			{
				mask = mask + (1 << (8 * size - i - 1));
			}
			arr[left_index_in_arr] = arr[left_index_in_arr] | mask;
			return;
		}

		for (int i = left; i < 32; ++i)
		{
			mask = mask + (1 << (8 * size - i - 1));
		}
		arr[left_index_in_arr] = arr[left_index_in_arr] | mask;

		++left_index_in_arr;
		mask = UINT_MAX;
		while (left_index_in_arr != right_index_in_arr)
		{
			arr[left_index_in_arr] = arr[left_index_in_arr] | mask;
			++left_index_in_arr;
		}

		mask = 0;
		for (int i = 0; i <= right; ++i)
		{
			mask = mask + (1 << (8 * size - i - 1));
		}
		arr[left_index_in_arr] = arr[left_index_in_arr] | mask;
		return;
	}

	mask = UINT_MAX;
	if (left_index_in_arr == right_index_in_arr)
	{
		for (int i = left; i <= right; ++i)
		{
			mask = mask - (1 << (8 * size - i - 1));
		}
		arr[left_index_in_arr] = arr[left_index_in_arr] & mask;
		return;
	}

	for (int i = left; i < 32; ++i)
	{
		mask = mask - (1 << (8 * size - i - 1));
	}
	arr[left_index_in_arr] = arr[left_index_in_arr] & mask;

	++left_index_in_arr;
	while (left_index_in_arr != right_index_in_arr)
	{
		arr[left_index_in_arr] = 0;
		++left_index_in_arr;
	}

	mask = UINT_MAX;
	for (int i = 0; i <= right; ++i)
	{
		mask = mask - (1 << (8 * size - i - 1));
	}
	arr[left_index_in_arr] = arr[left_index_in_arr] & mask;
	return;

}

//посчитать, сколько битов равно единице на отрезке left <= k < right
int bitsetCount(const bitword* arr, int left, int right)
{
	if (left >= right)
		return 0;

	bitword elem;
	int count = 0;
	int size = sizeof(bitword);
	int size_bit = size * 8;

	int left_index_in_arr = left / (size * 8);
	left -= left_index_in_arr * size * 8;

	--right;
	int right_index_in_arr = right / (size * 8);
	right -= right_index_in_arr * size * 8;

	bitword mask = 0;
	if (left_index_in_arr == right_index_in_arr)
	{
		elem = arr[left_index_in_arr] >> (size_bit - right - 1);
		for (int i = left; i <= right; ++i)
		{
			if (elem % 2 == 1)
				++count;
			elem = elem >> 1;
		}
		return count;
	}

	elem = arr[left_index_in_arr];
	for (int i = left; i < size_bit; ++i)
	{
		if (elem % 2 == 1)
			++count;
		elem = elem >> 1;
	}

	++left_index_in_arr;
	while (left_index_in_arr != right_index_in_arr)
	{
		elem = arr[left_index_in_arr];
		for (int i = 0; i < size_bit; ++i)
		{
			if (elem % 2 == 1)
				++count;
			elem = elem >> 1;
		}
		++left_index_in_arr;
	}

	elem = arr[left_index_in_arr] >> (size_bit - right - 1);
	for (int i = 0; i <= right; ++i)
	{
		if (elem % 2 == 1)
			++count;
		elem = elem >> 1;
	}
	return count;
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
			scanf("%d %d %d", &left, &right, &newval);
			bitsetSetSeg(arr, left, right, newval);
		}
		if (t == 4)
		{
			scanf("%d %d", &left, &right);
			printf("%d\n", bitsetCount(arr, left, right));
		}
	}
}
