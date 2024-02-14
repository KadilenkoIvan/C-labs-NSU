#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int partition(int* arr, int n, int pivot) 
{
    int count = 0, check = 0;
    for (int i = 0; i < n; ++i)
    {
        if (pivot > arr[i])
        {
            ++count;
            continue;
        }
        if(pivot == arr[i])
        {
            if (check == 0)
            {
                ++count;
                check = 1;
            }
            else
            {
                check = 0;
            }
        }
    }
    return count;
}

int main() 
{
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    int n = 0, p = 0;
    fread(&n, 4, 1, in);
    fread(&p, 4, 1, in);

    int* arr = malloc(sizeof(int) * n);
    memset(arr, 0, sizeof(int) * n);
    fread(arr, 4, n, in);

    int right = partition(arr, n, p);
    int left = 0;

    fwrite(&right, 4, 1, out);

    int* ans = malloc(sizeof(int) * n);
    memset(ans, 0, sizeof(int) * n);

    int check = 0;

    for (int i = 0; i < n; ++i)
    {
        if (arr[i] < p)
        {
            ans[left] = arr[i];
            ++left;
            continue;
        }
        if (arr[i] > p)
        {
            ans[right] = arr[i];
            ++right;
            continue;
        }
        if (arr[i] == p)
        {
            if (check == 0)
            {
                ans[left/*maybe right*/] = arr[i];
                ++left;
                check = 1;
                continue;
            }
            else
            {
                ans[right] = arr[i];
                ++right;
                check = 0;
                continue;
            }
        }
    }

    fwrite(ans, 4, n, out);
}