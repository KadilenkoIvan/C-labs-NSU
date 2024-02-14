#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int gcd(int a, int b, int* x, int* y)
{
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}
	int x_new, y_new;
	int ans = gcd((b % a), a, &x_new, &y_new);
	*x = y_new - x_new * (b / a);
	*y = x_new;
	return ans;
}

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	long long n = 0, k = 0, p = 0;
	fscanf(in, "%lld%lld%lld", &n, &k, &p);

	long long** matrix = malloc(sizeof(long long*) * k);
	for (int i = 0; i < k; ++i)
	{
		matrix[i] = malloc(sizeof(long long) * (n + 1));
		for (int j = 0; j < n + 1; ++j)
		{
			fscanf(in, "%lld", &matrix[i][j]);
			//printf("%d ", matrix[i][j]);
		}
		//printf("\n");
	}

	int x = 0, y = 0, v = 0;
	int* link = NULL;



	return 0;
}
/*
нет решений если при ступенчетом виде вся строка == 0, но последний столбец != 0

много решений если есть не связанный x (нулевые столбцы)

КОЛ-ВО РЕШЕНИЙ:
((p-1) ^ кол-во свободных переменных(нулевух столбцов) % p)
мб просто p, а не (p-1)
*/