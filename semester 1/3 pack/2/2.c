#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    int sum = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i+1; j > -1; j += i+1)
        {
            if (j > n)
                break;
            sum += arr[j-1];
        }
        printf("%d\n", sum);
        sum = 0;
    }
    free(arr);
}
