#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

double arr[1001][1001];

void koef()
{
    for (int i = 0; i < 1001; ++i)
    {
        for (int j = 0; j < i+1; ++j)
        {
            arr[i][j] = 0;
        }
    }

    arr[0][0] = 1;

    for (int i = 1; i < 1001; ++i)
    {
        arr[i][0] = 1;
        arr[i][i] = 1;
    }

    for (int i = 1; i < 1001; ++i)
    {
        for (int j = 1; j < i+1; ++j)
        {
            arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
        }
    }
}

int main()
{
    //printf("%0.10g", pow(10,300));
    //return 0;
    int q = 0, k = 0, n = 0;
    scanf("%d", &q);
    koef();
    for (int i = 0; i < q; ++i)
    {
        scanf("%d%d", &k, &n);
        printf("%0.10g\n", arr[k][n]);
    }
    return 0;
}
