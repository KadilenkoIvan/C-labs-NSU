//РАБОТАЕТ В VISUAL STUDIO, САЙТ НЕ ПРИНИМАЕТ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_s
{
    void* value;
    struct List_s* next;
    struct List_s* prev;
} List;

void initList(List* list)
{
    list->value = NULL;
    list->prev = NULL;
    list->next = NULL;
}

List* new_elem(void* value)
{
    List* new = malloc(sizeof(List));
    new->value = value;
    return new;
}

//создаёт новый узел со значением ptr и вставляет его после узла node
//возвращает указатель на созданный узел
List* addAfter(List* curr, void* ptr)
{
    List* new = new_elem(ptr);
    if (curr->next != NULL)
    {
        curr->next->prev = new;
        new->next = curr->next;
    }
    else
    {
        new->next = NULL;
    }
    curr->next = new;
    new->prev = curr;
    return new;
}
//создаёт новый узел со значением ptr и вставляет его перед узлом node
//возвращает указатель на созданный узел
List* addBefore(List* curr, void* ptr)
{
    List* new = new_elem(ptr);
    if (curr->prev != NULL)
    {
        curr->prev->next = new;
        new->prev = curr->prev;
    }
    else
    {
        curr->prev = NULL;
    }
    curr->prev = new;
    new->next = curr;
    return new;
}

void* erase(List* curr)
{
    void* deleted = curr->value;
    if (curr->next != NULL)
        curr->next->prev = curr->prev;
    if (curr->prev != NULL)
        curr->prev->next = curr->next;
    free(curr);
    return deleted;
}

int main()
{
    int T = 0, Q = 0, request = 0, value = 0, index = 0, k = 0;
    scanf("%d", &T);
    List* arr[100001];
    memset(arr, NULL, 100001);
    List Head;
    for (int i = 0; i < T; ++i)
    {
        initList(&Head);
        scanf("%d", &Q);
        for (int j = 0; j < Q; ++j)
        {
            scanf("%d", &request);
            if (request == 1)
            {
                scanf("%d", &index);
                scanf("%d", &value);
                if (index == -1)
                {
                    arr[k] = addAfter(&Head, value);
                    k++;
                    continue;
                }
                arr[k] = addAfter(arr[index], value);
                k++;
                continue;
            }
            else if (request == -1)
            {
                scanf("%d", &index);
                scanf("%d", &value);
                if (index == -1)
                {
                    List* curr = &Head;
                    while (curr->next != NULL)
                        curr = curr->next;
                    arr[k] = addAfter(curr, value);
                    k++;
                    continue;
                }
                arr[k] = addBefore(arr[index], value);
                k++;
                continue;
            }
            else if (request == 0)
            {
                scanf("%d", &index);
                erase(arr[index]);
            }
        }

        k = 0;

        List* curr = Head.next;
        while (curr != NULL)
        {
            printf("%d\n", curr->value);
            curr = curr->next;
        }

        printf("===\n");

        while (curr != NULL)
        {
            curr = curr->prev;
            free(curr);
        }

        memset(arr, NULL, 10001);
    }
}
/*
1
7
1 -1 1
1 0 2
-1 1 3
-1 -1 4
0 1
0 3
-1 2 5
*/