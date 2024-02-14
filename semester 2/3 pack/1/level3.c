#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "myblas.h"

//====== ������� 3 ======
//��������� ������� (alpha*A*B + beta*C) � �������� � � C
//����� A �- ������� ������� m �� k, B �- ������� ������� k �� n,
// C �- ������� ������� m �� n				| m = 3, k = 2, n = 4
void dgemm(
	int m, int n, int k,
	double alpha, const double* A, const double* B,
	double beta, double* C
)
{
	double new_elem = 0;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			C[i * n + j] *= beta;
			new_elem = 0;
			for (int q = 0; q < k; ++q)
			{
				new_elem += A[i * k + q] * B[q * n + j];
			}
			C[i * n + j] += alpha * new_elem;
		}
	}
}