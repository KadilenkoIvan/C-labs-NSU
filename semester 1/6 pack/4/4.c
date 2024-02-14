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
    int prev;
}List;

int addAfter(List* arr, int index, char* value, int i, int* first, int* last)
{
    strcpy(arr[i].value, value);
    if (index == -1)
    {
        arr[i].next = *first;
        arr[*first].prev = i;
        arr[i].prev = arr[*first].prev;
        *first = i;
        return i;
    }
    if (arr[index].prev == -1)
        *last = i;
    arr[i].next = arr[index].next;
    arr[i].prev = index;
    arr[arr[index].next].prev = i;
    arr[index].next = i;
    return i;
}

int addBefore(List* arr, int index, char* value, int i, int* last, int* first)
{
    strcpy(arr[i].value, value);
    if (index == -1)
    {
        arr[i].next = arr[*last].next;
        arr[*last].next = i;
        arr[i].prev = *last;
        *last = i;
        return i;
    }
    if (arr[index].prev == -1)
        *first = i;
    arr[i].prev = arr[index].prev;
    arr[i].next = index;
    arr[arr[index].prev].next = i;
    arr[index].prev = i;
    return i;
}

char* erase(List* arr, int index, int* f, int* l)// maybe int* l
{
    char str[8];
    if (index == *f)
        *f = arr[index].next;
    if (index == *l)
        *l = arr[index].prev;
    arr[arr[index].next].prev = arr[index].prev;
    arr[arr[index].prev].next = arr[index].next;

    return arr[index].value;
}

List arr[200001];
int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int T = 0;
    int n = 0, f = 0, q = 0, index_n = 0, index_p = 0, request = 0, j = 0, i = 0, l = 0;
    char value[8];
    char str[8];
    List curr;
    fscanf(in, "%d", &T);
    for (int t = 0; t < T; ++t)
    {
        fscanf(in, "%d%d%d%d", &n, &f, &l, &q);
        for (i = 0; i < n; ++i)
        {
            fscanf(in, "%s %d %d", value, &index_n, &index_p);
            strcpy(arr[i].value, value);
            arr[i].next = index_n;
            arr[i].prev = index_p;
        }

        j = i;
        for (int i = 0; i < q; ++i)
        {
            fscanf(in, "%d%d", &request, &index_n);
            if (request == 1)
            {
                fscanf(in, "%s", &value);
                fprintf(out, "%d\n", addAfter(arr, index_n, value, j, &f, &l));
                ++j;
                continue;
            }
            if (request == -1)
            {
                fscanf(in, "%s", &value);
                fprintf(out, "%d\n", addBefore(arr, index_n, value, j, &l, &f));
                if (f == -1)
                {
                    f = j;
                }
                ++j;
                continue;
            }
            if (request == 0)
            {
                strcpy(str, erase(arr, index_n, &f, &l));
                fprintf(out, "%s\n", str);
                continue;
            }
        }

        curr = arr[f];
        fprintf(out, "===\n");
        while (curr.next != -1 && f != -1)////
        {
            fprintf(out, "%s\n", curr.value);
            curr = arr[curr.next];
        }
        fprintf(out, "%s\n===\n", curr.value);
    }
}