#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

swap(long long* a, long long* b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

void heapify(long long* arr, int length, int root)
{

    int left = 2 * root + 1;
    int right = 2 * root + 2;

    int largest = root;
    if (left < length && arr[left] > arr[largest])
        largest = left;

    if (right < length && arr[right] > arr[largest])
        largest = right;

    if (largest != root)
    {
        swap(&arr[largest], &arr[root]);
        heapify(arr, length, largest);
    }
}

void heapSort(long long* arr, int length)
{
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        heapify(arr, length, i);
    }

    for (int i = length - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    int n = 0, f = 0;
    scanf("%d", &n);

    long long sum = 0;
    
    long long* arr = malloc(sizeof(long long) * n);
    memset(arr, 0, sizeof(long long) * n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%lld", &arr[i]);
    }

    heapSort(arr, n);

    for (int i = 0; i < n; ++i)
    {
        sum += (long long)arr[i] * (long long)(n - i - 1);
    }

    printf("%lld", sum);
    free(arr);
}
