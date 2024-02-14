#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "myblas.h"

//====== ������� 1 ======
// (��� ������� ����� n)

//����������� ������ �� X � Y
void dcopy(int n, const double* X, double* Y)
{
	for (int i = 0; i < n; ++i)
	{
		Y[i] = X[i];
	}
}

//�������� ������� ���������� �������� X � Y
void dswap(int n, double* X, double* Y) //�� ��������, �� ������
{
	double tmp = 0;
	for (int i = 0; i < n; ++i)
	{
		tmp = X[i];
		X[i] = Y[i];
		Y[i] = tmp;
	}
}

//��������� ������ X �� ����������� alpha
void dscal(int n, double alpha, double* X)
{
	for (int i = 0; i < n; ++i)
	{
		X[i] *= alpha;
	}
}

//��������� � ������� Y ������ X, ���������� �� ����������� alpha
void daxpy(int n, double alpha, const double* X, double* Y)
{
	for (int i = 0; i < n; ++i)
	{
		Y[i] += X[i] * alpha;
	}
}

//��������� ��������� ������������ �������� X � Y
double ddot(int n, const double* X, const double* Y)
{
	double ans = 0;
	for (int i = 0; i < n; ++i)
	{
		ans += Y[i] * X[i];
	}
	return ans;
}