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

#define inf LLONG_MAX - 1000000000000001

FILE* in;
FILE* out;

typedef struct Edge
{
    int from;
    int to;
    long long weight;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int count;
} Vertex;

void fill_neg_count(Vertex* graph, int from, int* neg_cycle)
{
    for (int i = 0; i < graph[from].count; ++i)
    {
        if (neg_cycle[graph[from].arr[i].to] != 1)
        {
            neg_cycle[graph[from].arr[i].to] = 1;
            fill_neg_count(graph, graph[from].arr[i].to, neg_cycle);
        }
    }
}

void belman_ford(Vertex* graph, Edge* edges, int src, int n, int m, long long* dist, int* neg_cycle)
{
    dist[src] = 0;
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < m; ++i)
        {
            if (dist[edges[i].from] < inf && dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
            {
                dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
            }
        }
    }

    //neg cycle check (n-th iterashion)
    for (int i = 0; i < m; ++i)
    {
        if (dist[edges[i].from] < inf && dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
        {
            dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
            neg_cycle[edges[i].to] = 1;
            fill_neg_count(graph, edges[i].to, neg_cycle);
        }
    }
    //neg cycle check (n-th iterashion)
}

void add_edge(Vertex* graph, int from, int to, long long weight)
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].from = from;
    graph[from].arr[graph[from].count].weight = weight;
    graph[from].count++;
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    int m = 0, n = 0, src = 0;
    fscanf(in, "%d%d%d", &n, &m, &src);

    Edge* edges = malloc(sizeof(Edge) * (m));
    Vertex* graph = malloc(sizeof(Vertex) * (n + 1));

    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
    }

    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d %lld", &edges[i].from, &edges[i].to, &edges[i].weight);
        add_edge(graph, edges[i].from, edges[i].to, edges[i].weight);
    }

    long long* dist = malloc(sizeof(long long) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        dist[i] = inf;
    }

    int* neg_cycle = malloc(sizeof(int) * (n + 1));
    memset(neg_cycle, 0, sizeof(int) * (n + 1));

    belman_ford(graph, edges, src, n, m, dist, neg_cycle);

    for (int i = 1; i < n + 1; ++i)
    {
        if (neg_cycle[i] == 1)
        {
            fprintf(out, "-\n");
            continue;
        }
        else if (dist[i] >= inf)
        {
            fprintf(out, "*\n");
        }
        else
        {
            fprintf(out, "%lld\n", dist[i]);
        }
    }

    free(edges);
    free(dist);
    free(neg_cycle);
}