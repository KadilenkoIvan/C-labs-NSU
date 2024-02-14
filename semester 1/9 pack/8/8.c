#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

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
    FILE* out = fopen("output.txt", "w");
    int n = 0;
    scanf("%d", &n);

    int* arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    int* der = malloc(sizeof(int) * (n - 1));
    for (int i = 0; i < n - 1; ++i)
    {
        der[i] = (arr[i + 1] - arr[i]);
    }

    int q = 0, c = 0, n_new = n - 1, min_i = 0, check = 0, min = 0;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &c);
        check = bin_find(der, -c, n - 1);
        min_i = check;
        min = min_i * c + arr[min_i];

        if (check != 0)
        {
            if (min >= (arr[check - 1] + c * (check - 1)))
            {
                min = arr[check - 1] + c * (check - 1);
                min_i = check - 1;
            }
        }

        if (check != n - 1)
        {
            if (min > (arr[check + 1] + c * (check + 1)))
            {
                min = arr[check + 1] + c * (check + 1);
                min_i = check + 1;
            }
        }

        fprintf(out, "%d\n", min_i);
    }
}
//28 ok
//29 my