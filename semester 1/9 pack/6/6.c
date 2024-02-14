#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct num_s
{
    unsigned int key;
    unsigned int number;
}num;

void radix_step(num* arr, num* buf, unsigned long long n, unsigned long long ind)
{
    unsigned char* arr_for_count = arr;
    unsigned int count[256];
    memset(count, 0, 256 * sizeof(int));
    unsigned long long index[256];
    memset(index, 0, 256 * sizeof(unsigned long long));
    for (unsigned long long i = 0; i < n; ++i)
    {
        count[arr_for_count[i*8+ind]]++;
    }
    for (int i = 1; i < 256; ++i)
    {
        index[i] = index[i - 1] + count[i - 1];
    }
    for (unsigned long long i = 0; i < n; ++i)
    {
        buf[index[arr_for_count[i*8+ind]]++] = arr[i];
    }
}

void radix_sort(num* arr, num* buf, unsigned long long  n)
{
    int size = sizeof(num) / 4;
    for (int i = 0; i < size; ++i)
    {
        radix_step(arr, buf, n, i*2);
        radix_step(buf, arr, n, i*2+1);
    }
}

int main()
{
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    unsigned long long n = 0;
    fread(&n, 4, 1, in);

    num* arr = malloc(sizeof(num) * n);
    fread(arr, 8, n, in);

    num* buf = malloc(sizeof(num) * n);
    memset(buf, 0, n * sizeof(num));

    radix_sort(arr, buf, n, 0);

    fwrite(arr, 8, n, out);

    free(arr);
    free(buf);
}
/*

$"
%%
*/