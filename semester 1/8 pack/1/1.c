#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main()
{
    int n = INT_MIN;
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");
    int arr[2];
    fread(arr, sizeof(int), 2, in);
    long long int b = (long long)arr[0] + (long long)arr[1];
    if (b < 0 && b % 2 != 0)
        b = b / 2 - 1;
    else
        b = b / 2;
    arr[0] = b;
    fwrite(arr, sizeof(int), 1, out);
}
