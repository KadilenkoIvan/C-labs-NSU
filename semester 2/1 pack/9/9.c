#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int gcd(int a, int b, int* x, int* y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    int x_new, y_new;
    int ans = gcd((b % a), a, &x_new, &y_new);
    *x = y_new - x_new * (b / a);
    *y = x_new;
    return ans;
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int n = 0;
    fscanf(in, "%d", &n);
    int n2 = n * n;

    int** arr = malloc(sizeof(int*) * (n2));
    for (int i = 0; i < n2; ++i)
    {
        arr[i] = malloc(sizeof(int) * (n2 + 1));
        memset(arr[i], 0, sizeof(int) * (n2 + 1));
    }

    char buf = 0;
    fscanf(in, "%c", &buf);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fscanf(in, "%c", &buf);
            if (buf == '*')
                arr[i * n + j][n2] = 1;
        }
        fscanf(in, "%c", &buf);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n2; ++k)
            {
                arr[i * n + j][i * n + j] = 1;

                if (i != 0)
                {
                    arr[i * n + j][(i - 1) * n + j] = 1;
                }
                if (j != 0)
                {
                    arr[i * n + j][i * n + (j - 1)] = 1;
                }
                if (i != n - 1)
                {
                    arr[i * n + j][(i + 1) * n + j] = 1;
                }
                if (j != n - 1)
                {
                    arr[i * n + j][i * n + (j + 1)] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n2; ++i)// вывод
    {
        for (int j = 0; j < n2 + 1; ++j)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // SLAY

    int x = 0, y = 0, m = 2, v = 0, * link;
    for (int i = 0; i < n2; ++i)
    {
        if (arr[i][i] == 0)//swap
        {
            for (int j = i + 1; j < n2; ++j)
            {
                if (arr[j][i] != 0)
                {
                    link = arr[i];
                    arr[i] = arr[j];
                    arr[j] = link;
                    break;
                }
            }
        }//swap

        x = 0;
        gcd(arr[i][i], m, &x, &y);
        for (int j = i + 1; j < n2; ++j)
        {
            v = ((arr[j][i] * x) % m);
            for (int k = 0; k < n2 + 1; ++k)    //k < n2 + 1 !!!!!!!!!!!!!!!!!!
            {
                arr[j][k] = ((arr[j][k] - (v * arr[i][k]) % m) + m) % m;
            }
        }
    }

    for (int i = 0; i < n2; ++i)
    {
        for (int j = 0; j < n2 + 1; ++j)
        {
            printf("%lld ", arr[i][j]);
        }
        printf("\n");
    }

    int* ans = malloc(sizeof(int) * n2);
    for (int i = n2 - 1; i >= 0; --i)
    {
        x = 0;
        gcd(arr[i][i], m, &x, &y);
        ans[i] = (arr[i][n2] * x) % m;
        for (int j = 0; j < n2; ++j)
        {
            arr[j][n2] = ((arr[j][n2] - (ans[i] * arr[j][i]) % m) + m) % m;
        }
    }

    // SLAY
    //printf("\n");
    //for (int i = 0; i < n2; ++i)// вывод
    //{
    //    for (int j = 0; j < n2 + 1; ++j)
    //    {
    //        printf("%d ", arr[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");
    int count = 0;
    for (int i = 0; i < n2; ++i)
    {
        if (ans[i] == 1)
            ++count;
    }

    fprintf(out, "%d\n", count);
    for (int i = 0; i < n2; ++i)
    {
        if (ans[i] == 1)
        {
            fprintf(out, "%d %d\n", (i / n) + 1, (i % n) + 1);
        }
    }
}