#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[5001];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
    int sum = 0, max = INT_MIN, max_begin = 0, max_end = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            sum += arr[j];
            if (sum > max)
            {
                max = sum;
                max_begin = i;
                max_end = j;
            }
        }
        sum = 0;
    }
    printf("%d %d %d", max_begin, max_end, max);
}
