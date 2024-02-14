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
    return n - 1;
}

int bin_find(int* arr, int find, int right)
{
    int left = 0;
    int middle = 0;
    int cheak = 0;
    while (left != right)
    {
        cheak = left + right;
        if (cheak % 2 == 1)
            middle = cheak / 2 + 1;
        else
            middle = cheak / 2;

        if (arr[middle] > find)
        {
            right = middle - 1;
        }
        else
        {
            left = middle;
        }
    }
    return left;
}

int main()
{
    int n = 0, ind = 0;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int q = 0;
    scanf("%d", &q);
    int find = 0;
    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &find);
        ind = bin_find(arr, find, n - 1);
        if (abs(arr[ind] - find) >= abs(arr[ind + 1] - find))
            ++ind;
        printf("%d", ind);
        if (arr[ind] == find)
            printf(" 0\n");
        else
            printf(" %d\n", abs(arr[ind] - find));
    }
    free(arr);

}
