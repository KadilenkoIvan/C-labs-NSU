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
#define inf 100000000

FILE* in;
FILE* out;

//STRUCTURES
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

typedef struct Request
{
    int from;
    int to;
} Request;
//STRUCTURES

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

void add(Vertex* graph, int from, int to, int weigth) //мб дефектный
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].from = from;
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].weight = weigth;
    ++graph[from].count;

    graph[to].arr = realloc(graph[to].arr, sizeof(Edge) * (graph[to].count + 1));
    graph[to].arr[graph[to].count].from = to;
    graph[to].arr[graph[to].count].to = from;
    graph[to].arr[graph[to].count].weight = weigth;
    ++graph[to].count;
}

int search_path(PathTree* tree, int start, int finish)
{
    int curr = finish, count = 1;
    while (curr != start)
    {
        push_stack(curr);
        curr = tree[curr].prev;
        ++count;
    }
    push_stack(start);
    return count;
}

int dijkstra(Vertex* graph, int** matrix, int n, int src, PathTree** tree_of_paths)
{
    int* dist = malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        dist[i] = inf;
    }
    char* visit = malloc(n + 1);
    memset(visit, 0, n + 1);

    int min = inf, u = 0;

    dist[src] = 0;
    visit[src] = 1;//0 = W, 1 = G, 2 = B
    do
    {
        min = inf;
        u = 0;
        for (int i = 1; i < n + 1; ++i)///!!1
        {
            if (visit[i] == 1 && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        visit[u] = 2;
        for (int i = 0; i < graph[u].count; ++i)
        {
            if (dist[graph[u].arr[i].to] > dist[graph[u].arr[i].from] + graph[u].arr[i].weight)
            {
                dist[graph[u].arr[i].to] = dist[graph[u].arr[i].from] + graph[u].arr[i].weight;
                visit[graph[u].arr[i].to] = 1;

                matrix[src][graph[u].arr[i].to] = dist[graph[u].arr[i].from] + graph[u].arr[i].weight;
                tree_of_paths[src][graph[u].arr[i].to].prev = u;
            }
        }

    } while (u != 0);
    free(dist);
    free(visit);
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0, p = 0, k = 0;
    fscanf(in, "%d%d%d", &n, &m, &k);

    Request* friends = malloc(sizeof(Request) * k);
    for (int i = 0; i < k; ++i)
    {
        fscanf(in, "%d %d", &friends[i].from, &friends[i].to);
    }

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
        graph[i].visit = 0;
    }

    PathTree** tree_of_paths = (PathTree**)malloc(sizeof(PathTree*) * (n + 1));
    int** matrix = (int**)malloc(sizeof(int*) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        tree_of_paths[i] = (PathTree*)malloc(sizeof(PathTree) * (n + 1));
        matrix[i] = (int*)malloc(sizeof(int) * (n + 1));
        memset(tree_of_paths[i], 0, sizeof(PathTree) * (n + 1));
        for (int j = 0; j < n + 1; ++j)
        {
            matrix[i][j] = inf;
        }
    }

    int from = 0, to = 0, weight = 0;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d %d", &from, &to, &weight);
        add(graph, from, to, weight);
    }

    int* complet_vertex = malloc(sizeof(int) * (n + 1));
    memset(complet_vertex, 0, sizeof(int) * (n + 1));
    int count = 0, ans = 0;

    /*for (int i = 1; i < n + 1; ++i)
    {
        dijkstra(graph, matrix, n, i, tree_of_paths);
    }*/

    int* complete_vertex = malloc(sizeof(int) * (n + 1));
    memset(complete_vertex, 0, sizeof(int) * (n + 1));
    for (int i = 0; i < k; ++i)
    {
        if (complete_vertex[i] == 0)
            dijkstra(graph, matrix, n, friends[i].from, tree_of_paths);

        if (matrix[friends[i].from][friends[i].to] >= inf)
        {
            fprintf(out, "NO\n");
        }
        else
        {
            fprintf(out, "YES  %d ", matrix[friends[i].from][friends[i].to]);

            count = search_path(tree_of_paths[friends[i].from], friends[i].from, friends[i].to);
            fprintf(out, "%d  ", count);

            for (; last != NULL;)
            {
                fprintf(out, "%d ", pop_stack());
            }
            fprintf(out, "\n");
        }
    }
}