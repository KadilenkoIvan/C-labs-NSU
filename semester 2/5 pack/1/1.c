#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

void func(char** arr, int n, int i, int j, int prev_i, int prev_j)
{
    if (j > 0 && arr[i][j - 1] == ' ' && arr[i][j - 1] != '#' && j - 1 != prev_j)
    {
        arr[i][j] = '#';
        func(arr, n, i, j - 1, i, j);
    }
    if (j < n - 1 && arr[i][j + 1] == ' ' && arr[i][j + 1] != '#' && j + 1 != prev_j)
    {
        arr[i][j] = '#';
        func(arr, n, i, j + 1, i, j);
    }
    if (i > 0 && arr[i - 1][j] == ' ' && arr[i - 1][j] != '#' && i - 1 != prev_i)
    {
        arr[i][j] = '#';
        func(arr, n, i - 1, j, i, j);
    }
    if (i < n - 1 && arr[i + 1][j] == ' ' && arr[i + 1][j] != '#' && i + 1 != prev_i)
    {
        arr[i][j] = '#';
        func(arr, n, i + 1, j, i, j);
    }
    arr[i][j] = '*';
}

int main()
{
    //init
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int n = 0;
    fscanf(in, "%d", &n);
    char** lab = (char**)malloc(sizeof(char*) * n), garbage = 0;
    fscanf(in, "%c", &garbage);
    for (int i = 0; i < n; ++i)
    {
        lab[i] = (char*)malloc(n + 1);
        for (int j = 0; j < n; ++j)
            fscanf(in, "%c", &lab[i][j]);
        lab[i][n] = '\0';
        fscanf(in, "%c", &garbage);
    }
    //init

    //find start pos and fill fst space
    int start_x = 0, start_y = 0;
    for (int i = 0; i < n; ++i)
    {
        if (lab[0][i] == ' ')
        {
            start_y = i;
            break;
        }
    }

    func(lab, n, start_x, start_y, -1, -1);
    //find start pos and fill fst space

    for (int i = 0; i < n; ++i)
        printf("%s\n", lab[i]);

    //find count of spacec
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (lab[i][j] == ' ')
            {
                ++count;
                func(lab, n, i, j, -1, -1);
            }
        }
    }
    fprintf(out, "%d", count);
    printf("\n\ncount = %d\n\n", count);
    //find count of spacec
}