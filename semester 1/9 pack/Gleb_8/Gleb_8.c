#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int main()//long long maybe
{
    FILE* out = fopen("output.txt", "w");
    int n = 0;
    scanf("%d", &n);

    int* arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    int q = 0, c = 0, min = 0, min_i = 0;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &c);
        min = arr[0];
        min_i = 0;
        for (int j = 0; j < n; ++j)
        {
            if (arr[j] + (c * j) < min)
            {
                min = arr[j] + (c * j);
                min_i = j;
            }
        }
        fprintf(out, "%d) %d\n", c, min_i);
    }
}
