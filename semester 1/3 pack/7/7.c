#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void select_sort(int* arr, int size)
{
    int x = 0, j = 0;
    for (int i = 0; i < size; ++i)
    {
        x = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > x)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = x;
    }
}

void print(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
    select_sort(arr, n);
    print(arr, n);
}