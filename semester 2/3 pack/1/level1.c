#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "myblas.h"

//====== уровень 1 ======
// (все векторы длины n)

//скопировать вектор из X в Y
void dcopy(int n, const double* X, double* Y)
{
	for (int i = 0; i < n; ++i)
	{
		Y[i] = X[i];
	}
}

//обмен€ть местами содержимое векторов X и Y
void dswap(int n, double* X, double* Y) //не работает, хз почему
{
	double tmp = 0;
	for (int i = 0; i < n; ++i)
	{
		tmp = X[i];
		X[i] = Y[i];
		Y[i] = tmp;
	}
}

//домножить вектор X на коэффициент alpha
void dscal(int n, double alpha, double* X)
{
	for (int i = 0; i < n; ++i)
	{
		X[i] *= alpha;
	}
}

//прибавить к вектору Y вектор X, умноженный на коэффициент alpha
void daxpy(int n, double alpha, const double* X, double* Y)
{
	for (int i = 0; i < n; ++i)
	{
		Y[i] += X[i] * alpha;
	}
}

//вычислить скал€рное произведение векторов X и Y
double ddot(int n, const double* X, const double* Y)
{
	double ans = 0;
	for (int i = 0; i < n; ++i)
	{
		ans += Y[i] * X[i];
	}
	return ans;
}