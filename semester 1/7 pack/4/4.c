#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int find_last(int find, int* arr, int n, int curr) 
{
    for (int i = curr; i < n - 1; ++i)
    {
        if (arr[i + 1] != find)
            return i;
    }
    return n-1;
}

int bin_find(int find, int* arr, int n)
{
    int plus = 0;
    int size = n;
    n = n / 2;
    int i = n;
    while (n >= 0 && i >= 0)
    {
        if (arr[n] == find)
        {
            return find_last(find, arr, size, n);
        }
        else if (arr[n] > find)
        {
            n = n / 2;
            --i;
            continue;
        }
        else
        {
            n = n + n / 2;
            --i;
            continue;
        }
    }
    return -1;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int q = 0;
    scanf("%d", &q);
    int find = 0, previous = 0;
    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &find);
        find += previous;
        previous = bin_find(find, arr, n);
        printf("%d\n", previous);
    }
    free(arr);

}
