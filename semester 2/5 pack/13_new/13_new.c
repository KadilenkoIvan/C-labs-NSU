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

#define inf 1000000000000

FILE* in;
FILE* out;

//structers
typedef struct Edge
{
    int num;
    int to;
    long long weight;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int count;
} Vertex;

typedef struct PathTree
{
    int prev;
    int idx;
} PathTree;

typedef struct Request
{
    int from;
    int to;
} Request;

typedef struct HeapElem
{
    int idx;
    long long weigth;
} HeapElem;

typedef struct Heap
{
    HeapElem* arr;
    int size;
} Heap;
//structers

void add_edge(Vertex* graph, int num, int from, int to, long long weight)
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].weight = weight;
    graph[from].arr[graph[from].count].num = num;
    graph[from].count++;
}

//HEAP
Heap heap;

void swap(HeapElem* a, HeapElem* b)
{
    HeapElem buf = *a;
    *a = *b;
    *b = buf;
}

void sift_up(int i)
{
    int parent = (i - 1) / 2;

    if (heap.arr[i].weigth < heap.arr[parent].weigth)
    {
        swap(&heap.arr[i], &heap.arr[parent]);
        sift_up(parent);
    }
}

void heap_push(int idx, long long weight)
{
    heap.arr[heap.size].idx = idx;
    heap.arr[heap.size].weigth = weight;
    ++heap.size;
    sift_up(heap.size - 1);
}

void sift_down(int i)
{
    int pos = i;
    if (2 * i + 1 < heap.size && heap.arr[2 * i + 1].weigth < heap.arr[pos].weigth)
    {
        pos = 2 * i + 1;
    }
    if (2 * i + 2 < heap.size && heap.arr[2 * i + 2].weigth < heap.arr[pos].weigth)
    {
        pos = 2 * i + 2;
    }
    if (i != pos)
    {
        swap(&heap.arr[i], &heap.arr[pos]);
        sift_down(pos);
    }
}

void heap_pop()
{
    swap(&heap.arr[0], &heap.arr[heap.size - 1]);
    --heap.size;
    sift_down(0);
}
//HEAP

int search_path(PathTree* tree_of_path, int from, int to, int* ans)
{
    int curr = to, count = 0;
    while (curr != from)
    {
        ans[count] = tree_of_path[curr].idx;
        curr = tree_of_path[curr].prev;
        ++count;
    }
    return count;
}

void dijkstra(Vertex* graph, int n, int src, long long* dist, PathTree* tree_of_path)
{
    memset(tree_of_path, 0, sizeof(PathTree) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        dist[i] = inf;
    }
    dist[src] = 0;
    heap_push(src, dist[src]);

    int u = 0;
    long long u_weight = 0;

    while (heap.size > 0)
    {
        u = heap.arr[0].idx;
        u_weight = heap.arr[0].weigth;
        heap_pop();

        if (u_weight > dist[u]) continue;

        for (int i = 0; i < graph[u].count; ++i)
        {
            if (dist[graph[u].arr[i].to] > dist[u] + graph[u].arr[i].weight)
            {
                dist[graph[u].arr[i].to] = dist[u] + graph[u].arr[i].weight;

                tree_of_path[graph[u].arr[i].to].prev = u;
                tree_of_path[graph[u].arr[i].to].idx = graph[u].arr[i].num;

                heap_push(graph[u].arr[i].to, dist[graph[u].arr[i].to]);
            }
        }
    }
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0, k = 0;
    fscanf(in, "%d%d%d", &n, &m, &k);

    Request* request = malloc(sizeof(Request) * (k));
    for (int i = 0; i < k; ++i)
    {
        fscanf(in, "%d %d", &request[i].from, &request[i].to);
    }

    Vertex* graph = malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
    }

    int from = 0, to = 0;
    long long weight = 0;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d %lld", &from, &to, &weight);
        add_edge(graph, i + 1, from, to, weight);
    }

    PathTree* tree_of_path = malloc(sizeof(PathTree) * (n + 1));
    long long* dist = malloc(sizeof(long long) * (n + 1));

    int* path = malloc(sizeof(int) * (n + 1));
    int path_count = 0;

    heap.arr = malloc(sizeof(HeapElem) * (m + 1));//maybe not N, maybe M
    heap.size = 0;

    int count = 0;
    int* ans = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < k; ++i)
    {
        dijkstra(graph, n, request[i].from, dist, tree_of_path);
        if (dist[request[i].to] == inf)
        {
            fprintf(out, "DOOMED\n");
            continue;
        }

        fprintf(out, "quarantine  %lld ", dist[request[i].to]);
        count = search_path(tree_of_path, request[i].from, request[i].to, ans);
        fprintf(out, "%d  ", count);

        for (int i = count - 1; i >= 0; --i)
        {
            fprintf(out, "%d ", ans[i]);
        }
        fprintf(out, "\n");
    }
}