#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i+1; j < n; ++j)
        {
            if (arr[i] > arr[j])
                ++count;
        }
        printf("%d ", count);
        count = 0;
    }
    free(arr);
}
