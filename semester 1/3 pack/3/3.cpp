#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    int* cheak = (int*)malloc(10001 * sizeof(int)) ;

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < 10001; ++i)
    {
        cheak[i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        cheak[arr[i]] += 1;
    }

    for (int i = 0; i < 10001; ++i)
    {
        if (cheak[i] > 0)
        {
            printf("%d: %d\n", i, cheak[i]);
        }
    }

    free(arr);
}
