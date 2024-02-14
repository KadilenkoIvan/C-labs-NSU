#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void merge(int* arr, int left, int s, int right)
{
    int p1 = left;
    int p2 = s + 1;
    int p3 = 0;

    int* buf = malloc((right - left + 1) * sizeof(int));//

    while (p1 <= s && p2 <= right)
    {
        if (arr[p1] < arr[p2])
        {
            buf[p3] = arr[p1];
            ++p1;
        }
        else
        {
            buf[p3] = arr[p2];
            ++p2;
        }
        ++p3;
    }

    while (p2 <= right)
    {
        buf[p3] = arr[p2];
        ++p3;
        ++p2;
    }
    while (p1 <= s)//?//
    {
        buf[p3] = arr[p1];
        ++p3;
        ++p1;
    }

    int size = right - left + 1;
    for (int i = 0; i < size; ++i)
    {
        arr[left + i] = buf[i];
    }
    free(buf);
}

void mergesort(int* arr, int left, int right)
{
    int s;
    if (left < right)
    {
        s = (left + right) / 2;

        mergesort(arr, left, s);
        mergesort(arr, s + 1, right);
        merge(arr, left, s, right);
    }
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

    mergesort(arr, 0, n - 1);

    /*for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }*/

    fwrite(arr, 4, n, out);
    free(arr);
}