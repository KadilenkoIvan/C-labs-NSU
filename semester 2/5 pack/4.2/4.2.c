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

FILE* in;
FILE* out;

typedef struct Edge
{
    int from;
    int to;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int sub_count;
    int count;
    int visit;
} Vertex;

//STACK
typedef struct Stack
{
    int value;
    struct Stack* next;
    struct Stack* prev;
}Stack;

Stack* fst = NULL;
Stack* last = NULL;

Stack* push_stack(int value)
{
    Stack* new_elem = (Stack*)malloc(sizeof(Stack));
    new_elem->value = value;
    if (last == NULL)
    {
        last = new_elem;
        fst = new_elem;
        last->next = NULL;
        last->prev = NULL;
        return last;
    }
    new_elem->next = NULL;
    last->next = new_elem;
    new_elem->prev = last;
    last = new_elem;
    return last;
}

int pop_stack()
{
    int value = last->value;
    Stack* buf = last->prev;
    if (fst == last)
    {
        free(last);
        fst = NULL;
        last = NULL;
        return value;
    }
    free(last);
    buf->next = NULL;
    last = buf; 
    return value;
}
//STACK

void add(Vertex* graph, Edge edge)
{
    graph[edge.from].arr = realloc(graph[edge.from].arr, sizeof(Edge) * (graph[edge.from].count + 1));
    graph[edge.from].arr[graph[edge.from].count] = edge;
    ++graph[edge.from].count;
    ++graph[edge.to].sub_count;
}

void topological_sort(Vertex* graph, int n, int* ans)
{
    int pos_i_zero = 0;
    for (int q = 0; q < n; ++q)
    {
        pos_i_zero = 0;
        for (int i = 1; i < n + 1; ++i)
        {
            if (graph[i].sub_count == 0)
            {
                ans[i - 1] = q + 1;
                pos_i_zero = i;
                --graph[i].sub_count;
                break;
            }
        }
        
        if (pos_i_zero == 0)
        {
            fprintf(out, "NO");
            exit(0);
        }

        for (int i = 0; i < graph[pos_i_zero].count; ++i)
        {
            --graph[graph[pos_i_zero].arr[i].to].sub_count;
        }
    }
}

void DFS(Vertex* graph, int pos, int n)
{
    graph[pos].visit = 1;
    for (int i = 0; i < graph[pos].count; ++i)
    {
        if (graph[graph[pos].arr[i].to].visit != 1)
        {
            DFS(graph, graph[pos].arr[i].to, n);
        }
    }
    push_stack(pos);
}

void cycle(Vertex* graph, int pos, int n)
{
    graph[pos].visit = 2;
    for (int i = 0; i < graph[pos].count; ++i)
    {
        if (graph[graph[pos].arr[i].to].visit == 0)
            cycle(graph, graph[pos].arr[i].to, n);
        if (graph[graph[pos].arr[i].to].visit == 2)
        {
            fprintf(out, "NO");
            exit(0);
        }
    }
    graph[pos].visit = 1;
}

void topological_sort_DFS(Vertex* graph, int n)
{
    for (int i = 1; i < n + 1; ++i)
    {
        cycle(graph, i, n);
    }
    for (int i = 1; i < n + 1; ++i)
    {
        graph[i].visit = 0;
    }
    for (int i = 1; i < n + 1; ++i)
    {
        if (graph[i].visit != 1)
        {
            DFS(graph, i, n);
        }
    }
}

//НУЖНО ИСПОЛЬЗОВАТЬ ОБХОД В ГЛУБИНУ
int main()// ВЫВОДИТЬ НУЖНО НЕ ПОРЯДОК Х[n], А ЗНАЧЕНИЯ ПО ПОРЯДКУ, ТОЕСТЬ X1, X2, X3, ..., X[N]
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    int m = 0, n = 0;
    fscanf(in, "%d%d", &n, &m);

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
        graph[i].sub_count = 0;
        graph[i].visit = 0;
    }

    Edge edge;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d", &edge.from, &edge.to);
        add(graph, edge);
    }

    int* ans = malloc(sizeof(int) * (n + 1));
    memset(ans, 0, sizeof(int) * (n + 1));
    topological_sort_DFS(graph, n);

    for (int i = 0; i < n; ++i)
    {
        ans[pop_stack() - 1] = i + 1;
    }

    fprintf(out, "YES\n");
    for (int i = 0; i < n; ++i)
    {
        fprintf(out, "%d ", ans[i]);
    }
}