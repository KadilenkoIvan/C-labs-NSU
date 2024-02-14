//#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct Edge
{
    int from;
    int to;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int visit;
    int count;
} Vertex;

typedef struct Queue
{
    int value;
    struct Queue* next;
} Queue;

Queue* fst = NULL;
Queue* last = NULL;

Queue* push_q(int value)
{
    Queue* new = malloc(sizeof(Queue));
    new->value = value;
    new->next = NULL;
    if (last != NULL)
    {
        last->next = new;
        last = last->next;
    }
    else
    {
        last = new;
    }
    if (fst == NULL)
        fst = last;
    return last;
}

int pop_q()
{
    int value = fst->value;
    Queue* buf = fst->next;
    if (fst != last)
    {
        free(fst);
        fst = buf;
    }
    else
    {
        free(fst);
        fst = NULL;
        last = NULL;
    }    
    return value;
}

void my_bfs(Vertex* graph, int i_vertex, int* paths)
{
    int count = 0, check = 1;
    graph[i_vertex].visit = 1;
    paths[i_vertex] = 0;
    push_q(i_vertex);
    while (fst != NULL)
    {
        i_vertex = fst->value;
        pop_q();
        for (int i = 0; i < graph[i_vertex].count; ++i)
        {
            if (graph[graph[i_vertex].arr[i].to].visit == 0)
            {
                graph[graph[i_vertex].arr[i].to].visit = 1;
                paths[graph[i_vertex].arr[i].to] = paths[graph[i_vertex].arr[i].from] + 1;
                push_q(graph[i_vertex].arr[i].to);
            }
        }
    }
}

int main()
{
    //init
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int n = 0, m = 0;
    fscanf(in, "%d %d", &m, &n);

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (m + 1));
    for (int i = 0; i < m + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].visit = 0;
        graph[i].count = 0;
    }
    //init

    //reading
    int to = 0, from = 0;
    for (int i = 0; i < n; ++i)
    {
        fscanf(in, "%d %d", &from, &to);

        graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
        graph[from].arr[graph[from].count].from = from;
        graph[from].arr[graph[from].count].to = to;
        ++graph[from].count;
    }

    //for (int i = 0; i < m + 1; ++i)
    //{
    //    printf("%d = ", i);
    //    for (int j = 0; j < graph[i].count; ++j)
    //    {
    //        printf("[%d %d], ", graph[i].arr[j].from, graph[i].arr[j].to);
    //    }
    //    printf("\n");
    //}
    //reading

    int* paths = malloc(sizeof(int) * (m + 1));
    for (int i = 2; i < m + 1; ++i)
        paths[i] = -1;
    //paths[1] = 0;

    my_bfs(graph, 1, paths, m, 1);

    for (int i = 1; i < m + 1; ++i)
    {
        //printf("%d = %d\n", i, paths[i]);
        fprintf(out, "%d\n", paths[i]);
    }
}