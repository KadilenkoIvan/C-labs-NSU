#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_s
{
    char value[8];
    int next;
}List;

int insert(List* arr, int index, char* value, int i, int* first)
{
    strcpy(arr[i].value, value);
    if (index == -1)
    {
        arr[i].next = *first;
        *first = i;
        return i;
    }
    arr[i].next = arr[index].next;
    arr[index].next = i;
    return i;
}

char* erase(List* arr, int index, int* first)
{
    char str[8];
    if (index == -1)
    {
        strcpy(str, arr[*first].value);
        *first = arr[*first].next;
        return str;
    }
    List buf = arr[arr[index].next];
    arr[index].next = buf.next;

    return buf.value;
}

List arr[200001];
int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int T = 0;
    int n = 0, f = 0, q = 0, index = 0, request = 0, j = 0, i = 0;
    char value[8];
    char str[8];
    List curr;
    fscanf(in, "%d", &T);
    //memset(arr, NULL, 10000);
    for (int t = 0; t < T; ++t)
    {
        fscanf(in, "%d%d%d", &n, &f, &q);
        for (i = 0; i < n; ++i)
        {
            fscanf(in, "%s %d", value, &index);
            strcpy(arr[i].value, value);
            arr[i].next = index;
        }

        j = i;
        for (int i = 0; i < q; ++i)
        {
            fscanf(in, "%d%d", &request, &index);
            if (request == 0)
            {
                fscanf(in, "%s", &value);
                fprintf(out,"%d\n", insert(arr, index, value, j, &f));
                ++j;
                continue;
            }
            if (request == 1)
            {
                strcpy(str,erase(arr, index, &f));
                fprintf(out,"%s\n", str);
                continue;
            }
        }

        curr = arr[f];
        fprintf(out,"===\n");
        while (curr.next != -1 && f != -1)////
        {
            fprintf(out,"%s\n", curr.value);
            curr = arr[curr.next];
        }
        fprintf(out,"%s\n===\n", curr.value);
    }
}