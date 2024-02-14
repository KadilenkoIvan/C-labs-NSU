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
    char** arr = (char**)malloc(sizeof(char*) * (n + 1));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = (char*)malloc(sizeof(char) * (n + 1));
        scanf("%s", arr[i]);
        arr[i][i] = '1';
        arr[i][n] = '\0';
    }
    int i = 0, j = 0;
    for (int k = 0; k < n; ++k)
    {
        while (i < n)
        {
            while (j < n)
            {
                while (j < n && arr[k][j] == '0')
                {
                    ++j;
                }
                if (arr[i][k] == '1' && arr[j][k] == '1')
                    arr[i][j] = '1';
                
                ++j;
            }
            j = 0;
            ++i;
            while (i < n && arr[i][k] == '0')
            {
                ++i;
            }
        }     
        i = 0;
    }

    int size = n - 1;
    for (int i = 0; i < size; ++i)
    {
        printf("%s\n", arr[i]);
    }
    printf("%s", arr[size]);

    free(arr);
}