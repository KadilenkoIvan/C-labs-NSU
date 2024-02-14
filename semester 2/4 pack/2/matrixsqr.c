#include "cblas.h"

void MatrixSqr(int n, const double* A, double* R)
{
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, A, n, A, n, 0, R, n);
}