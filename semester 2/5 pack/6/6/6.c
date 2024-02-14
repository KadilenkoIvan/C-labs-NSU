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

#define inf 1000000

FILE* in;
FILE* out;

typedef struct Edge
{
    int from;
    int to;
    int weigth;
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

void add(Vertex* graph, Edge edge)
{
    graph[edge.from].arr = realloc(graph[edge.from].arr, sizeof(Edge) * (graph[edge.from].count + 1));
    graph[edge.from].arr[graph[edge.from].count] = edge;
    ++graph[edge.from].count;
}

void add_tree(PathTree* graph, int to, int from)
{
    graph[to].prev = from;
}

void bellman_ford(Vertex* graph, int n, int* dist, Vertex* tree_of_path)
{
    Edge edge;
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 0; j < graph[i].count; ++j)
        {
            edge.from = 0;
            if (dist[graph[i].arr[j].to] > dist[graph[i].arr[j].from] + graph[i].arr[j].weigth)
            {
                dist[graph[i].arr[j].to] = dist[graph[i].arr[j].from] + graph[i].arr[j].weigth;
                edge.from = graph[i].arr[j].from;
                edge.to = graph[i].arr[j].to;
                edge.weigth = graph[i].arr[j].weigth;
                add_tree(tree_of_path, edge.to, edge.from);
            }
        }
    }
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

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    PathTree* tree_of_paths = (PathTree*)malloc(sizeof(PathTree) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
        graph[i].visit = 0;

        tree_of_paths[i].prev = 0;
    }

    Edge edge;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d %d", &edge.from, &edge.to, &edge.weigth);
        add(graph, edge);
    }

    //вывод графа
    /*for (int i = 1; i < n + 1; ++i)
    {
        printf("%d = ", i);
        for (int j = 0; j < graph[i].count; ++j)
        {
            printf("[%d %d, %d], ", graph[i].arr[j].from, graph[i].arr[j].to, graph[i].arr[j].weigth);
        }
        printf("\n");
    }*/

    int* dist = malloc(sizeof(int) * (n + 1));
    dist[0] = 0;
    dist[1] = 0;
    for (int i = 2; i < n + 1; ++i)
    {
        dist[i] = inf;
    }

    bellman_ford(graph, n, dist, tree_of_paths);

    //вывод дерева пути
    /*for (int i = 1; i < n + 1; ++i)
    {
        printf("%d = %d ", i, tree_of_paths[i].prev);
        for (int j = 0; j < tree_of_paths[i].count; ++j)
        {
            printf("[%d %d, %d], ", tree_of_paths[i].arr[j].from, tree_of_paths[i].arr[j].to, tree_of_paths[i].arr[j].weigth);
        }
        printf("\n");
    }*/

    //вывод
    int count = 0;
    for (int i = 0; i < k; ++i)
    {
        count = search_path(tree_of_paths, 1, friends[i]);
        fprintf(out, "%d  %d  ", dist[friends[i]], count);
        for (; last != NULL;)
        {
            fprintf(out, "%d ", pop_stack());
        }
        fprintf(out, "\n");
    }

}
