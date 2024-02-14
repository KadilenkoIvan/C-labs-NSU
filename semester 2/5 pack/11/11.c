#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#define inf 10000001

FILE* in;
FILE* out;

//STRUCTURES
typedef struct Edge
{
    int from;
    int to;
    int num;
    int count;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int count;
    int visit;
    int cutpoint;
} Vertex;

typedef struct PathTree
{
    int prev;
}PathTree;
//STRUCTURES

int comp(void* a, void* b)
{
    Edge A = *(Edge*)a;
    Edge B = *(Edge*)b;
    if (A.num > B.num)
        return 1;
    if (A.num == B.num)
        return 0;
    if (A.num < B.num)
        return -1;
}

int comp2(const void* a, const void* b)
{
    return(*(int*)a > *(int*)b ? 1 : (*(int*)a == *(int*)b) ? 0 : -1);
}

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

void add(Vertex* graph, int from, int to, int num)
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].from = from;
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].num = num;
    graph[from].arr[graph[from].count].count = 0;
    ++graph[from].count;

    graph[to].arr = realloc(graph[to].arr, sizeof(Edge) * (graph[to].count + 1));
    graph[to].arr[graph[to].count].from = to;
    graph[to].arr[graph[to].count].to = from;
    graph[to].arr[graph[to].count].num = num;
    graph[to].arr[graph[to].count].count = 0;
    ++graph[to].count;
}

int bridge_count = 0, bridge_count_real = 0; o_time = 0;
void dfs(Vertex* graph, int v, int p, int p_edge, int* tin, int* fup, int* used_V, int* used_E)
{
    used_V[v] = 1;
    used_E[p_edge] = 1;
    tin[v] = fup[v] = ++o_time;
    int child = 0;

    for (int i = 0; i < graph[v].count; ++i)
    {
        int to = graph[v].arr[i].to;
        if (to == p) continue;
        //if (used_E[graph[v].arr[i].num] == 1)
        //    continue;
        if (used_V[to] == 1)
            fup[v] = min(fup[v], tin[to]);
        else
        {
            dfs(graph, to, v, graph[v].arr[i].num, tin, fup, used_V, used_E);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && p != -1)
            {
                graph[v].cutpoint++;
            }
            ++child;
        }
    }
    if (p == -1 && child > 1)
        graph[v].cutpoint++;
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0;
    fscanf(in, "%d%d", &n, &m);

    Vertex* graph = malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
        graph[i].visit = 0;
        graph[i].cutpoint = 0;
    }

    int from = 0, to = 0;
    for (int i = 1; i < m + 1; ++i)
    {
        fscanf(in, "%d %d", &from, &to);
        add(graph, from, to, i);
    }

    int* tin = malloc(sizeof(int) * (n + 1));
    int* fup = malloc(sizeof(int) * (n + 1));
    int* used = malloc(sizeof(int) * (n + 1));
    int* used_E = malloc(sizeof(int) * (m + 1));
    memset(tin, 0, sizeof(int) * (n + 1));
    memset(fup, 0, sizeof(int) * (n + 1));
    memset(used, 0, sizeof(int) * (n + 1));
    memset(used_E, 0, sizeof(int) * (m + 1));

    int* bridge = malloc(sizeof(int) * (n + 10));
    memset(bridge, 0, sizeof(int) * (n + 10));
    int timer = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        if (used[i] == 0)
        {
            dfs(graph, i, -1, 0, tin, fup, used, used_E);
        }
    }

    for (int i = 1; i < n + 1; ++i)
    {
        if (graph[i].cutpoint > 0)
        {
            bridge[bridge_count] = i;
            ++bridge_count;
        }
    }

    fprintf(out, "%d\n", bridge_count);
    qsort(bridge, bridge_count, sizeof(int), comp2);
    for (int i = 0; i < bridge_count; ++i)
    {
        if (bridge[i] > 0)
            fprintf(out, "%d ", bridge[i]);
    }
}