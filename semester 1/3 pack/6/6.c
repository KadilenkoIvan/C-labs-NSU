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

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int n = 0;
    fscanf(in, "%d", &n);

    int arr1[100000] = { 0 };
    for (int i = 0; i < n; ++i)
    {
        fscanf(in, "%d", &arr1[i]);
    }
    select_sort(arr1, n);

    int m = 0;
    fscanf(in, "%d", &m);

    int arr2[100000] = { 0 };
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d", &arr2[i]);
    }
    select_sort(arr2, m);

    int cheak = 1, count = 0;

    int arr_answer[100000] = { 0 };

    for (int i = 0; i < n; ++i)
    {
        if (arr1[i] == arr1[i + 1])
        {
            continue;
        }

        for (int j = 0; j < m; ++j)
        {
            /*if (arr1[j] == arr1[j + 1])
            {
                continue;
            }*/

            if (arr1[i] == arr2[j])
            {
                cheak = 0;
                break;
            }
        }

        if (cheak == 1)
        {
            arr_answer[count] = arr1[i];
            count += 1;
        }
        cheak = 1;
    }

    int count_q = 0;
    for (int i = 0; arr_answer[i] > 0; ++i)
    {
        ++count_q;
    }

    if (count_q == 0)
        fprintf(out, "%d", count);
    else
        fprintf(out, "%d\n", count);

    for (int i = 0; i < count_q; ++i)
    {
        if (i == count - 1)
        {
            fprintf(out, "%d", arr_answer[i]);
        }
        else
        {
            fprintf(out, "%d ", arr_answer[i]);
        }
    }
}