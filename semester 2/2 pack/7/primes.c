#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "primes.h"

char* arr_p = NULL;
char buf = 0;

static void create_arr()
{
	int n = 664580;
	arr_p = malloc(sizeof(char) * n);

	arr_p[0] = 0;
	arr_p[1] = 0;

	for (int i = 0; i < n; ++i)
		arr_p[i] = 1;

	for (int i = 3; i * i <= n; i += 2)
	{
		if (arr_p[i / 2] == 1)
		{
			for (int j = i * i; j < n; j += 2 * i)
			{
				arr_p[j / 2] = 0;
			}
		}
	}
}

//returns: 1 if x is prime number, 0 otherwise
int isPrime(int x)
{
	if (buf == 0)
	{
		create_arr();
		buf = 1;
	}

	if ((x % 2 == 0 && x != 2) || x == 1)
		return 0;

	if (arr_p[x / 2] == 1)
		return 1;

	return 0;
	/*if (x < 2) return 0;
	if (x < 4) return 1;
	if (x % 2 == 0 || x % 3 == 0) return 0;
	for (int i = 5; i * i <= x; i += 6)
	{
		if (x % i == 0 || x % (i + 2) == 0)
			return 0;
	}
	return 1;*/
}

//returns minimal prime number p such that p >= x
int findNextPrime(int x)
{
	if (buf == 0)
	{
		create_arr();
		buf = 1;
	}

	while (1)
	{
		if (isPrime(x) == 1)
			return x;
		++x;
	}

	/*if (x % 2 == 0)
		++x;

	while (1)
	{
		if (isPrime(x) == 1)
			return x;
		x += 2;
	}*/
}

//returns the number of primes x such that l <= x < r
int getPrimesCount(int l, int r)
{
	if (buf == 0)
	{
		create_arr();
		buf = 1;
	}

	int count = 0;

	if (l <= 2)
	{
		l = 2;
		if (r > 2)
			++count;
	}

	if (l % 2 == 0)
		++l;

	for (int i = l; i < r; i += 2)
	{
		if (arr_p[i / 2] == 1)
			++count;
	}

	return count;

	//int n = r + 1, count = 0;
	//int* arr = malloc(sizeof(int) * n);
	////memset(arr, 1, sizeof(int) * n);
	//for (int i = 0; i < n; ++i)
	//	arr[i] = 1;

	//if (l <= 2)
	//{
	//	l = 2;
	//	if (r > 2)
	//		++count;
	//}

	//for (int i = 3; i * i <= n; i += 2)
	//{
	//	if (arr[i / 2] == 1)
	//	{
	//		for (int j = i * i; j < n; j += 2 * i)
	//		{
	//			arr[j / 2] = 0;
	//		}
	//	}
	//}

	//if (l % 2 == 0)
	//	++l;

	//for (int i = l; i < r; i += 2)
	//{
	//	if (arr[i / 2] == 1)
	//		++count;
	//}

	//free(arr);
	//return count;
}