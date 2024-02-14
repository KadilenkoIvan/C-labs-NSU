void cblas_dgemm(const int garbage1, const int garbage2, const int garbage3, const int m, const int n, const int k, const double alpha, const double* a, const int garbage4, const double* b, const int garbage5, const double beta, double* c, const int garbage6)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c[i * n + j] = 0;
			for (int k = 0; k < n; ++k)
			{
				c[i * n + j] += a[i * n + k] * a[k * n + j];
			}
		}
	}
}