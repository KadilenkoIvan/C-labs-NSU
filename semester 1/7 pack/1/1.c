#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//(*p).next == p->next

typedef struct ListElem_s
{
    char* value;
    struct ListElem_s* next;
} ListElem;

typedef struct MyList_s
{
    ListElem* first;
    ListElem* last;
} MyList;

ListElem* new_elem(char* str)
{
    int n = strlen(str) + 1;
    ListElem* new = malloc(sizeof(ListElem));
    new->value = malloc(sizeof(char) * n);
    strcpy(new->value, str);
    new->value[n - 1] = '\0';
    new->next = NULL;
    return new;
}

ListElem* insert(ListElem* curr, char* str)
{
    int n = strlen(str) + 1;
    ListElem* new = malloc(sizeof(ListElem));
    new->value = malloc(sizeof(char) * n);
    strcpy(new->value, str);
    new->value[n - 1] = '\0';
    new->next = NULL;
    curr->next = new;
    return new;
}

//ListElem* arr[1000000001];
//MyList arr_fe[1000000001];

int main()
{
    int n = 0, ind = 0;
    scanf("%d", &n);

    ListElem** arr = (ListElem*)malloc(sizeof(ListElem*) * 1000000001);
    MyList* arr_fe = malloc(sizeof(MyList) * 1000000001);

    memset(arr, NULL, 1000000001 * sizeof(ListElem*));
    memset(arr_fe, NULL, 1000000001 * sizeof(MyList));

    ListElem* curr;
    char str[8];

    int i = 0;
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &ind);
        if (arr[ind] == NULL)
        {
            scanf(" %s", str);
            arr[ind] = new_elem(str);
            arr_fe[ind].first = arr[ind];
            arr_fe[ind].last = arr[ind];
            continue;
        }

        scanf(" %s", str);
        arr_fe[ind].last = insert(arr_fe[ind].last, str);
    }

    int j = 0;

    for (int i = 0; i < 1000000001; ++i)
    {
        if (arr[i] == NULL)
            continue;

        if (arr[i]->next == NULL)
        {
            printf("%d %s\n", i, arr[i]->value);
            continue;
        }

        curr = arr[i];
        while (curr->next != NULL)
        {
            printf("%d %s\n", i, curr->value);
            curr = curr->next;
        }
        printf("%d %s\n", i, curr->value);
    }
    free(arr);
    free(arr_fe);
}
/*
5
3 qwerty
3 string
3 ab
3 hello
3 world
*/