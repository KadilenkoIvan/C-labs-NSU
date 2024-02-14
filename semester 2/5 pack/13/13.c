//#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define inf 600000000000

FILE* in;
FILE* out;

//STRUCTURES
typedef struct Edge
{
    int num;
    int from;
    int to;
    long long weight;
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
    int idx;
}PathTree;

typedef struct Request
{
    int from;
    int to;
} Request;

typedef struct ElemHeap
{
    int idx;
    long long weight;
}ElemHeap;

typedef struct Heap
{
    ElemHeap* arr;
    int count;
}Heap;
//STRUCTURES

//HEAP
void swap(ElemHeap* a, ElemHeap* b)
{
    ElemHeap buf = *a;
    *a = *b;
    *b = buf;
}

void heapify_up(Heap* heap, int i)
{
    int parent = i / 2;
    if (heap->arr[i].weight != heap->arr[parent].weight)
    {
        swap(&heap->arr[i], &heap->arr[parent]);
        heapify_up(heap, parent);
    }
}

void heapify_down(Heap* heap, int i)
{
    int pos = i;

    if (2 * i < heap->count && heap->arr[2 * i].weight != heap->arr[pos].weight)
    {
        pos = 2 * i;
    }
    if (2 * i + 1 < heap->count && heap->arr[2 * i + 1].weight != heap->arr[pos].weight)
    {
        pos = 2 * i + 1;
    }
    if (i != pos)
    {
        swap(&heap->arr[i], &heap->arr[pos]);
        heapify_down(heap, pos);
    }
}

void insert_heap(Heap* heap, long long value, int idx)//???
{
    heap->arr[heap->count].weight = value;
    heap->arr[heap->count].idx = idx;
    heap->count++;
    heapify_up(heap, heap->count - 1);
}

void pop_heap(Heap* heap)
{
    swap(&heap->arr[0], &heap->arr[heap->count - 1]);
    --heap->count;
    heapify_down(heap, 0);
}

//HEAP
void add(Vertex* graph, int num, int from, int to, long long weigth)
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].num = num;
    graph[from].arr[graph[from].count].from = from;
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].weight = weigth;
    ++graph[from].count;
}

int search_path2(PathTree* tree, int start, int finish, int* ans)
{
    int curr = finish, count = 0;
    while (curr != start)
    {
        ans[count] = tree[curr].idx;
        curr = tree[curr].prev;
        ++count;
    }
    return count;
}

int dijkstra(Vertex* graph, long long* matrix, int n, int m, int src, int finish, PathTree* tree_of_paths)
{
    for (int i = 0; i < n + 1; ++i)
    {
        matrix[i] = inf;
    }

    int u = 0, u_dist = 0;

    matrix[src] = 0;

    Heap my_heap;
    my_heap.arr = malloc(sizeof(ElemHeap) * (m + 1));
    my_heap.count = 0;
    insert_heap(&my_heap, 0, src);

    while (my_heap.count > 0)
    {
        u = my_heap.arr[0].idx;
        u_dist = my_heap.arr[0].weight;
        pop_heap(&my_heap);

        if (u_dist > matrix[u]) continue;

        for (int i = 0; i < graph[u].count; ++i)
        {
            if (matrix[graph[u].arr[i].to] > matrix[graph[u].arr[i].from] + graph[u].arr[i].weight)
            {
                matrix[graph[u].arr[i].to] = matrix[graph[u].arr[i].from] + graph[u].arr[i].weight;

                tree_of_paths[graph[u].arr[i].to].prev = u;
                tree_of_paths[graph[u].arr[i].to].idx = graph[u].arr[i].num;

                insert_heap(&my_heap, matrix[graph[u].arr[i].to], graph[u].arr[i].to);
            }
        }
    }
    free(my_heap.arr);
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0, k = 0;
    fscanf(in, "%d%d%d", &n, &m, &k);

    Request* request = malloc(sizeof(Request) * (k + 1));
    for (int i = 0; i < k; ++i)
    {
        fscanf(in, "%d %d", &request[i].from, &request[i].to);
    }

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
        graph[i].visit = 0;
    }

    PathTree** tree_of_paths = (PathTree**)malloc(sizeof(PathTree*) * (n + 1));
    long long** matrix = (long long**)malloc(sizeof(long long*) * (n + 1));

    int from = 0, to = 0;
    long long weight = 0;
    for (int i = 1; i < m + 1; ++i)
    {
        fscanf(in, "%d %d %lld", &from, &to, &weight);
        add(graph, i, from, to, weight);
    }

    int* complete_vertex = malloc(sizeof(int) * (n + 1));
    memset(complete_vertex, 0, sizeof(int) * (n + 1));

    int count = 0;
    int* ans = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < k; ++i)
    {
        if (complete_vertex[request[i].from] == 0)
        {
            matrix[request[i].from] = malloc(sizeof(long long) * (n + 1));
            tree_of_paths[request[i].from] = malloc(sizeof(PathTree) * (n + 1));
            dijkstra(graph, matrix[request[i].from], n, m, request[i].from, request[i].to, tree_of_paths[request[i].from]);
            complete_vertex[request[i].from] = 1;
        }
        if (matrix[request[i].from][request[i].to] == inf)
        {
            fprintf(out, "DOOMED\n");
            continue;
        }

        fprintf(out, "quarantine  %lld ", matrix[request[i].from][request[i].to]);

        count = search_path2(tree_of_paths[request[i].from], request[i].from, request[i].to, ans);
        //print_path(tree_of_paths[request[i].from], request[i].from, request[i].to, &count);
        fprintf(out, "%d  ", count);

        for (int i = count - 1; i >= 0; --i)
        {
            fprintf(out, "%d ", ans[i]);
        }
        fprintf(out, "\n");
    }

    //free
    free(tree_of_paths);
    free(matrix);

    for (int i = 0; i < n; ++i)
    {
        if(graph[i].arr != NULL)
            free(graph[i].arr);
    }
    free(graph);
    //free
}