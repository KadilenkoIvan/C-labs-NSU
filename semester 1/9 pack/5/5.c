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
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    int n = 0;
    fread(&n, 4, 1, in);

    int* arr = malloc(sizeof(int) * n);
    fread(arr, 4, n, in);

    /*for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");*/

    quick_sort(arr, 0, n - 1);

    /*for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }*/

    fwrite(arr, 4, n, out);
}
