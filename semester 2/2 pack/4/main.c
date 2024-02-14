#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

void Init(const int* arr, int n);
int64_t Sum(int l, int r);
int Query(int l, int64_t sum);

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int n = 0, m = 0;
    fscanf(in, "%d %d", &n, &m);

    int* arr = malloc(sizeof(int) * n);
    memset(arr, 0, sizeof(int) * n);

    for (int i = 0; i < n; ++i)
    {
        fscanf(in, "%d", &arr[i]);
    }

    //long long* arr_sum = malloc(sizeof(long long) * n);
    //memset(arr_sum, 0, sizeof(long long) * n);

    Init(arr, n);
    long long s = 0;
    int l = 0, r = 0, ans = 0;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %lld", &l, &s);

        ans = Query(l, s);
        fprintf(out, "%d\n", ans);
        //printf("%d\n", ans);
    }

    return 0;
}