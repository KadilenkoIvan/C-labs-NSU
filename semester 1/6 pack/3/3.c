#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

char* create_new_str(int n, char* str)
{

    //return new_elem;
}

int how_much_symbols(char symbol, char* str)
{
    int n = strlen(str);
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == symbol)
        {
            ++count;
        }
    }
    return count;
}

int main()
{
    char str[100001];

    int n = 0;
    scanf("%d", &n);

    char** arr = (char*)malloc(sizeof(char*) * n);

    int request = 0;
    int j = 0, size_or_ind = 0;
    char symbol = NULL;

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &request);
        if (request == 0)
        {
            scanf("%d", &size_or_ind);
            scanf("%s", &str);
            char* new_elem = (char*)malloc((size_or_ind + 1) * sizeof(char));
            strcpy(new_elem, str);
            arr[j] = new_elem;
            j++;
        }
        else if (request == 1)
        {
            scanf("%d", &size_or_ind);
            free(arr[size_or_ind]);
        }
        else if (request == 2)
        {
            scanf("%d", &size_or_ind);
            printf("%s\n", arr[size_or_ind]);
        }
        else if (request == 3)
        {
            scanf("%d", &size_or_ind);
            scanf(" %c", &symbol);
            printf("%d\n", how_much_symbols(symbol, arr[size_or_ind]));
        }
    }
    free(arr);
}