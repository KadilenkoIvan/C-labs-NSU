#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//merges sorted arrays a[0..ak-1] and b[0..bk-1] into
//one sorted array res[0..rk-1], returning rk from function
int merge(const int* a, int ak, const int* b, int bk, int* res)
{
    int i = 0, j = 0, q = 0, size = ak + bk;
    while (i < ak && j < bk)
    {
        if (a[i] <= b[j])
        {
            res[q] = a[i];
            ++i;
            ++q;
            continue;
        }
        res[q] = b[j];
        ++j;
        ++q;
        continue;
    }
    if (i >= ak)
    {
        while (j < bk)
        {
            res[q] = b[j];
            ++j;
            ++q;
        }
        return;
    }
    while (i < ak)
    {
        res[q] = a[i];
        ++i;
        ++q;
    }
    return;
}


int main()
{
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    int n = 0, m = 0;
    fread(&n, 4, 1, in);
    fread(&m, 4, 1, in);

    int* arr_1 = malloc(sizeof(int) * n);
    int* arr_2 = malloc(sizeof(int) * m);

    memset(arr_1, NULL, sizeof(int) * n);
    memset(arr_2, NULL, sizeof(int) * m);

    fread(arr_1, sizeof(int), n, in);
    fread(arr_2, sizeof(int), m, in);

    int* res = malloc(sizeof(int) * (n + m));
    memset(res, 0, sizeof(int) * (n + m));

    merge(arr_1, n, arr_2, m, res);

    fwrite(res, 4, n + m, out);
}