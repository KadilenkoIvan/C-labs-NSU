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

#define inf 10000000

FILE* in;
FILE* out;

typedef struct Edge
{
    int from;
    int to;
    int weight;
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
    if (last != NULL)
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
    return NULL;
}
//STACK

void add(Vertex* graph, int from, int to, int weigth)
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    //graph[from].arr[graph[from].count].from = from;
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].weight = weigth;
    ++graph[from].count;
}

void floyd_yorshal_m(int** matrix, int n, int** path)
{
    for (int w = 1; w < n + 1; ++w)
    {
        for (int u = 1; u < n + 1; ++u)
        {
            for (int v = 1; v < n + 1; ++v)
            {
                if (matrix[u][v] > matrix[u][w] + matrix[w][v] && matrix[u][w] != inf && matrix[w][v] != inf)
                {
                    matrix[u][v] = matrix[u][w] + matrix[w][v];
                    path[u][v] = path[u][w];
                }
            }
        }
    }
}

void floyd_yorshal_g(int** matrix, int n, int** path)
{
    for (int w = 1; w < n + 1; ++w)
    {
        for (int u = 1; u < n + 1; ++u)
        {
            for (int v = 1; v < n + 1; ++v)
            {
                if (matrix[u][v] > matrix[u][w] + matrix[w][v] && matrix[u][w] != inf && matrix[w][v] != inf)
                {
                    matrix[u][v] = matrix[u][w] + matrix[w][v];
                    path[u][v] = path[u][w];
                }
            }
        }
    }
}

void belman_ford(Edge* edges, int src, int n, int m, int* path, int* dist)
{
    dist[src] = 0;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < m; ++i)
        {
            if (dist[edges[i].from] < inf && dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
            {
                dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
                path[edges[i].to] = edges[i].from;
                flag = 1;
            }
        }
    }
}

int find_path(int* path, int src, int end)
{
    int count = 0;
    for (int i = end; i != -1; i = path[i])
    {
        push_stack(i);
        ++count;
    }
    return count;
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    int m = 0, n = 0, k = 0;
    fscanf(in, "%d%d%d", &n, &m, &k);

    int* friends = malloc(sizeof(int) * k);
    for (int i = 0; i < k; ++i)
    {
        fscanf(in, "%d", &friends[i]);
    }

    Edge* edges = malloc(sizeof(Edge) * (m));

    int from = 0, to = 0, weight = 0;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
        //add(graph, from, to, weight);
    }

    int* path = malloc(sizeof(int) * (n + 1));
    int* dist = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        path[i] = -1;
        dist[i] = inf;
    }

    belman_ford(edges, 1, n, m, path, dist);

    int count = 0;
    int* arr = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < k; ++i)
    {
        count = find_path(path, 1, friends[i]);

        fprintf(out, "%d  %d  ", dist[friends[i]], count);

        for (int j = 0; j < count; ++j)
        {
            fprintf(out, "%d ", pop_stack());
        }
        fprintf(out, "\n");
    }

    free(edges);
    free(arr);
    free(dist);
    free(path);
    free(friends);
}