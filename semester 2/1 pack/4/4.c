#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

void make_arr(int** arr,int m)
{
    arr[1][1] = 1;
    for (int i = 2; i < 2002; ++i)
    {
        for (int j = 1; j < 2002; ++j)
        {
            arr[i][j] = (arr[i - 1][j] + arr[i - 1][j - 1]) % m;
        }
    }
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int** arr = malloc(sizeof(int*) * 2002);
    for (int i = 0; i < 2002; ++i)
    {
        arr[i] = malloc(sizeof(int) * 2002);
        memset(arr[i], 0, 2002 * sizeof(int));
    }

    int t = 0, m = 0;
    fscanf(in,"%d%d", &m, &t);
    
    make_arr(arr, m);

    int n = 0, k = 0, koef = 0;
    for (int i = 0; i < t; i++)
    {
        fscanf(in,"%d%d", &n, &k);
        ++n;
        ++k;
        if (k < 0 || k > n)
        {
            fprintf(out, "0\n");
            continue;
        }
        fprintf(out, "%d\n", arr[n][k]);
    }
    
    return 0;
}
//213458
//120
//120