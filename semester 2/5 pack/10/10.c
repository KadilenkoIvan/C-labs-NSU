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
    int fake;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int count;
    int visit;
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
    graph[from].arr[graph[from].count].fake = 0;
    ++graph[from].count;

    graph[to].arr = realloc(graph[to].arr, sizeof(Edge) * (graph[to].count + 1));
    graph[to].arr[graph[to].count].from = to;
    graph[to].arr[graph[to].count].to = from;
    graph[to].arr[graph[to].count].num = num;
    graph[to].arr[graph[to].count].fake = 0;
    ++graph[to].count;
}

int* ans;
int count = 0;
int cnt = 0;
int flag = 0;

//void dfs(Vertex* graph, int x, int n, int p, int* num, int* low)
//{
//
//}

int bridge_count = 0, o_time = 0;
void DFS(Vertex* graph, int u, int* disc, int* low, int* parent, Edge* bridge)
{
    disc[u] = low[u] = o_time;
    ++o_time;

    for (int i = 0; i < graph[u].count; ++i)
    {
        if (disc[graph[u].arr[i].to] == -1)
        {
            parent[graph[u].arr[i].to] = u;
            DFS(graph, graph[u].arr[i].to, disc, low, parent, bridge);
            low[u] = min(low[u], low[graph[u].arr[i].to]);

            if (low[graph[u].arr[i].to] > disc[u])
            {
                int flag = 0, idx = 0;
                if (graph[u].arr[i].fake != 1)
                {
                    bridge[bridge_count].from = graph[u].arr[i].from;
                    bridge[bridge_count].to = graph[u].arr[i].to;
                    bridge[bridge_count].num = graph[u].arr[i].num;
                    bridge[bridge_count].fake = 0;
                    ++bridge_count;
                }
            }
        }
        else if (graph[u].arr[i].to != parent[u])
        {
            low[u] = min(low[u], disc[graph[u].arr[i].to]);
        }
    }
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
    }

    int from = 0, to = 0;
    int flag = 0;
    for (int i = 1; i < m + 1; ++i)
    {
        flag = 0;
        fscanf(in, "%d %d", &from, &to);
        for (int j = 0; j < graph[from].count; ++j)
        {
            if ((graph[from].arr != NULL && graph[from].arr[j].from == from && graph[from].arr[j].to == to)/* || (graph[to].arr != NULL && graph[to].arr[j].from == to && graph[to].arr[j].to == from)*/)
            {
                graph[from].arr[j].fake = 1;
                flag = 1;
                break;
            }
        }
        for (int j = 0; j < graph[to].count; ++j)
        {
            if ((graph[to].arr != NULL && graph[to].arr[j].from == to && graph[to].arr[j].to == from)/* || (graph[to].arr != NULL && graph[to].arr[j].from == to && graph[to].arr[j].to == from)*/)
            {
                graph[to].arr[j].fake = 1;
                flag = 1;
                break;
            }
        }
        if (!flag)
            add(graph, from, to, i);
    }

    int* disc = malloc(sizeof(int) * (n + 1));
    int* low = malloc(sizeof(int) * (n + 1));
    int* parent = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }

    Edge* bridge = malloc(sizeof(Edge) * (n + 10));
    memset(bridge, 0, sizeof(Edge) * (n + 10));
    int timer = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        if (disc[i] == -1)
        {
            DFS(graph, i, disc, low, parent, bridge);
        }
    }

    fprintf(out, "%d\n", bridge_count);
    qsort(bridge, bridge_count, sizeof(Edge), comp);
    for (int i = 0; i < bridge_count; ++i)
    {
        fprintf(out, "%d ", bridge[i].num);
    }
}