#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

void swap(int* a, int* b)
{
    int buf = *a;
    *a = *b;
    *b = buf;
}

void heapify(int* arr, int length, int root)
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

void heapSort(int* arr, int length)
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
	FILE* in = fopen("input.bin", "rb");
	FILE* out = fopen("output.bin", "wb");
	int n = 0;
	fread(&n, sizeof(int), 1, in);

	int* arr = malloc(sizeof(int) * n);
	fread(arr, sizeof(int), n, in);

    heapSort(arr, n);

    fwrite(arr, sizeof(int), n, out);
}