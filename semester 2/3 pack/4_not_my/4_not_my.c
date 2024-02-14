#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

double function(double t, double a, double* x, double* y, double* z)
{
	double sub = t - a;
	double x_cord = x[1] + 2 * x[2] * sub + 3 * x[3] * sub * sub;
	double y_cord = y[1] + 2 * y[2] * sub + 3 * y[3] * sub * sub;
	double z_cord = z[1] + 2 * z[2] * sub + 3 * z[3] * sub * sub;
	return sqrt(x_cord * x_cord + y_cord * y_cord + z_cord * z_cord);
}

int main() 
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	int n = 0;
	fscanf(in, "%d", &n);

	double b = 0, step = 0, a = 0, res = 0;
	double x[4], y[4], z[4];
	int counter = 0;
	for (int i = 0; i < n; i++) 
	{
		fscanf(in, "%lf %lf", &a, &b);
		counter = (b - a) * 1000 + 1;
		step = (b - a) / counter;

		for (int q = 0; q < 4; ++q)
		{
			fscanf(in, "%lf", &x[q]);
		}
		for (int q = 0; q < 4; ++q)
		{
			fscanf(in, "%lf", &y[q]);
		}		
		for (int q = 0; q < 4; ++q)
		{
			fscanf(in, "%lf", &z[q]);
		}

		double left = a;
		for (int j = 0; j < counter; j++)//step = b - a, left = a, step+left = b
		{
			res += step / 6 * (function(left, a, x, y, z) + (4 * function(left + step / 2, a, x, y, z)) + function(left + step, a, x, y, z));
			left += step;
		}
		//printf("check");
	}
	fprintf(out, "%.20lf", res);
	return 0;
}