#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "myblas.h"

int main()
{
	int n = 4, m = 3, k = 2;
	double* A = (double*)malloc(sizeof(double) * m * k);
	double* B = (double*)malloc(sizeof(double) * k * n);
	double* C = (double*)malloc(sizeof(double) * m * n);
	memset(C, 1, sizeof(double) * m * n);

	int alpha = 5;
	double x[2] = { 6,8 }, y[2] = { 4,5 }, a[4] = { 9,2,6,5 };
	dger(2, 2, alpha, x, y, a);
	for (int i = 0; i < 4; ++i)
		printf("%lf ", a[i]);

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			scanf("%lf", &A[i * k + j]);
		}
	}

	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%lf", &B[i * n + j]);
		}
	}

	dgemm(m, n, k, 2, A, B, 1, C);

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%lf ", C[i * n + j]);
		}
		printf("\n");
	}
	double X[5] = { 1,2,3,4,5 };
	double Y[5] = { 6,7,8,9,10 };
	daxpy(5, 2, X, X);

	int qwe = 0;
	scanf("%d", &qwe);
	return 0;
}