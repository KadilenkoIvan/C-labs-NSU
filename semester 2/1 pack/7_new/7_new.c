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

    double** arr = malloc(sizeof(double*) * (n + 10));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = malloc(sizeof(double) * (n + 10));
        memset(arr[i], 0, sizeof(double) * (n + 10));
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            fscanf(in, "%lf", &arr[i][j]);
        }
    }

    double* x = malloc(sizeof(double) * (n + 10));
    memset(x, 0, sizeof(double) * (n + 10));

    double v = 0;
    double* link;
    int d = n - 1;

    //

    //for (int i = 0; i < n; ++i)
    //{
    //    /*for (int i = 0; i < n; ++i)
    //    {
    //        for (int j = 0; j < n + 1; ++j)
    //        {
    //            printf("%lf ", arr[i][j]);
    //        }
    //        printf("\n");
    //    }
    //    printf("\n");*/

    //    if (arr[i][i] == 0)
    //    {
    //        for (int j = i + 1; j < n; ++j)
    //        {
    //            if (arr[j][i] != 0)
    //            {
    //                link = arr[i];
    //                arr[i] = arr[j];
    //                arr[j] = link;
    //                break;
    //            }
    //        }
    //    }
    //}

    for (int i = 0; i < n; ++i)// вывод
    {
        for (int j = 0; j < n + 1; ++j)
        {
            printf("%.0lf ", arr[i][j]);
        }
        printf("\n");
    }
    printf("start\n\n");

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            /*if (arr[j][i] == 0)
                continue;*/
            if (arr[i][i] != 0)
                v = arr[j][i] / arr[i][i];
            else
                v = 0;

            for (int k = 0; k < n + 1; ++k)
            {
                arr[j][k] = arr[j][k] - arr[i][k] * v;
                if (arr[j][k] == -1)
                    arr[j][k] = 1;
            }
        }

        for (int i = 0; i < n; ++i)// вывод
        {
            for (int j = 0; j < n + 1; ++j)
            {
                printf("%.0lf ", arr[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = n - 1; i >= 0; --i)
    {
        x[i] = arr[i][n] / arr[i][i];
        for (int j = 0; j < i; ++j)
        {
            arr[j][n] = arr[j][n] - x[i] * arr[j][i];
        }
    }

    //
    /*for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            printf("%lf ", arr[i][j]);
        }
        printf("\n");
    }*/
    for (int i = 0; i < n; ++i)
    {
        fprintf(out, "%lf\n", x[i]);
    }

    free(x);
    return 0;
}