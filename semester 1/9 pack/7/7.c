#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

swap(int* a, int* b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

void quick_sort(int* arr, int first, int last)
{
    int i = first, j = last, x = arr[(first + last) / 2 + 1];
    do
    {
        while (arr[i] < x)
        {
            ++i;
        }
        while (x < arr[j])
        {
            --j;
        }
        if (i <= j)
        {
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
            ++i;
            --j;
        }
    } while (i <= j);
    if (i < last)
        quick_sort(arr, i, last);
    if (first < j)
        quick_sort(arr, first, j);
}

int main()
{
    int n = 0, count = 0;
    scanf("%d", &n);

    int* arr = malloc(sizeof(int) * n);
    int* ans = malloc(sizeof(int) * n);
    //memset(ans, 0, sizeof(int) * n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    quick_sort(arr, 0, n - 1);

    --n;
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] != arr[i + 1])
        {
            ans[j] = arr[i];
            ++j;
            ++count;
        }
    }

    if (ans[j] != arr[n])
    {
        ans[j] = arr[n];
        ++count;
    }

    printf("%d\n", count);
    for (int i = 0; i < count; ++i)
    {
        printf("%d\n", ans[i]);
    }
}