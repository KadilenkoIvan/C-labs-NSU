#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "myblas.h"

//====== ������� 2 ======
//��������� ������ (alpha*A*X + beta*Y) ����� m, � �������� ��� � Y
//����� A �- ������� ������� m �� n, X �- ������ ����� n, � Y �- ������ ����� m
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

//��������� ������� (alpha*X*Yt + A) � �������� � � A
//����� Yt �- ��� ����������������� ������ Y, �� ���� ���������� ��� ������-������
// A �- ������� ������� m �� n, X �- ������ ����� m, � Y �- ������ ����� n
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