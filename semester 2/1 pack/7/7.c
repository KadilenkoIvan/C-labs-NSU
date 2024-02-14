#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int n = 0;
    fscanf(in, "%d", &n);

    double** arr = malloc(sizeof(double*) * (n + 1));
    ++n;
    for (int i = 0; i < n; ++i)
    {
        arr[i] = malloc(sizeof(double) * (n + 1));
        memset(arr[i], 0, sizeof(double) * (n + 1));
    }

    int m = n - 1;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fscanf(in, "%lf", &arr[i][j]);
            //fprintf(out, "%lf ", arr[i][j]);
        }
        //fprintf(out, "\n");
    }

    double v = 0;
    double* link;
    for (int k = 0; k < m; ++k)
    {
        if (arr[k][k] == 0)
        {
            link = arr[k];
            arr[k] = arr[k + 1];
            arr[k + 1] = link;

        }
        for (int i = k + 1; i < m; ++i)
        {
            v = arr[i][k] / arr[k][k];
            for (int j = k; j < m; ++j)
            {
                arr[i][j] = arr[i][j] - arr[k][j] * v;
            }
            arr[i][m] = arr[i][m] - v * arr[k][m];
        }
    }

    double* x = malloc(sizeof(double) * (n + 1));
    memset(x, 0, sizeof(double) * (n + 1));

    double s = 0;
    for (int k = m - 1; k >= 0; --k)
    {
        v = 0;
        for (int i = k + 1; i < m; ++i)
        {
            s = arr[k][i] * x[i];
            v = v + s;
        }
        x[k] = (arr[k][m] - v) / arr[k][k];
    }

    for (int i = 0; i < m; ++i)
    {
        fprintf(out, "%lf\n", x[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        free(arr[i]);
    }
    free(x);
    return 0;
}