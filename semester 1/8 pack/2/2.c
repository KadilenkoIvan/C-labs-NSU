#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

union un
{
    int number;
    struct
    {
        char b1;
        char b2;
        char b3;
        char b4;
    };
};

union un reverse(union un num)
{
    char buf = num.b1;
    num.b1 = num.b4;
    num.b4 = buf;
    buf = num.b2;
    num.b2 = num.b3;
    num.b3 = buf;
    return num;
}

int main()
{
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");
    int size = 0, sum = 0;
    int arr[100001];
    fread(&size, sizeof(int), 1, in);
    if (size <= 10000)
    {
        fread(arr, sizeof(int), size, in);
        for (int i = 0; i < size; ++i)
        {
            sum += arr[i];
        }
        fwrite(&sum, sizeof(int), 1, out);
        return 0;
    }

    union un num;
    num.number = size;
    size = reverse(num).number;
    fread(arr, sizeof(int), size, in);

    for (int i = 0; i < size; ++i)
    {
        num.number = arr[i];
        sum += reverse(num).number;
    }

    num.number = sum;
    sum = reverse(num).number;
    fwrite(&sum, sizeof(int), 1, out);
}
