#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "myblas.h"

//====== уровень 2 ======
//вычислить вектор (alpha*A*X + beta*Y) длины m, и записать его в Y
//здесь A Ц- матрица размера m на n, X Ц- вектор длины n, а Y Ц- вектор длины m
void dgemv(
	int m, int n,
	double alpha, const double* A, const double* X,
	double beta, double* Y
)//?!?!?!
{
	//double* new_vec = malloc(sizeof(double) * m);
	//memset(new_vec, 0, sizeof(double) * m);

	dscal(m, beta, Y);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			Y[i] += A[i * n + j] * X[j] * alpha;
		}
	}
}

//вычислить матрицу (alpha*X*Yt + A) и записать еЄ в A
//здесь Yt Ц- это транспонированный вектор Y, то есть записанный как вектор-строка
// A Ц- матрица размера m на n, X Ц- вектор длины m, а Y Ц- вектор длины n
void dger(
	int m, int n,
	double alpha, const double* X, const double* Y,
	double* A
)//?!?!?!
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			A[i * n + j] = A[i * n + j] + (alpha * X[i] * Y[j]);
		}
	}
}