#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

void func(int** arr, int n, int m, int i, int j, int prev_i, int prev_j)
{
    if (j > 0 && arr[i][j - 1] == 1&& arr[i][j - 1] != -2 && j - 1 != prev_j)
    {
        arr[i][j] = -2;
        func(arr, n, m, i, j - i, i, j);
    }
    if (j < m - 1 && arr[i][j + 1] == 1 && arr[i][j + 1] != -2 && j + 1 != prev_j)
    {
        arr[i][j] = -2;
        func(arr, n, m, i, j + 1, i, j);
    }
    if (i > 0 && arr[i - 1][j] == 1 && arr[i - 1][j] != -2 && i - 1 != prev_i)
    {
        arr[i][j] = -2;
        func(arr, n, m, i - 1, j, i, j);
    }
    if (i < n - 1 && arr[i + 1][j] == 1&& arr[i + 1][j] != -2 && i + 1 != prev_i)
    {
        arr[i][j] = -2;
        func(arr, n, m, i + 1, j, i, j);
    }
    arr[i][j] = 0;
}

int main()// острова
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int n = 0, m = 0;
    fscanf(in, "%d%d", &n, &m);

    int** matrix = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = malloc(sizeof(int) * m);
    }

    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (matrix[i][j] == 1)
            {
                ++count;
                func(matrix, n, m, i, j, -1, -1);
            }
        }
    }
    fprintf(out, "count = %d", count);
}
/*
5 5
0 0 1 1 0
0 1 1 1 0
0 0 0 1 1
0 1 0 0 0
0 0 0 0 0
*/