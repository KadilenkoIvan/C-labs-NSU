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
#define inf 100001

FILE* in;
FILE* out;

//STRUCTURES
typedef struct Edge
{
    int from;
    int to;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int count;
    int visit;
    int num;
} Vertex;

typedef struct PathTree
{
    int prev;
}PathTree;
//STRUCTURES

//STACK
typedef struct Stack
{
    int value;
    struct Stack* next;
    struct Stack* prev;
}Stack;

Stack* fst1 = NULL;
Stack* last1 = NULL;

Stack* fst2 = NULL;
Stack* last2 = NULL;

Stack* push_stack1(int value)
{
    Stack* new_elem = (Stack*)malloc(sizeof(Stack));
    new_elem->value = value;
    if (last1 == NULL)
    {
        last1 = new_elem;
        fst1 = new_elem;
        last1->next = NULL;
        last1->prev = NULL;
        return last1;
    }
    new_elem->next = NULL;
    last1->next = new_elem;
    new_elem->prev = last1;
    last1 = new_elem;
    return last1;
}

int pop_stack1()
{
    int value = last1->value;
    Stack* buf = last1->prev;
    if (fst1 == last1)
    {
        free(last1);
        fst1 = NULL;
        last1 = NULL;
        return value;
    }
    free(last1);
    buf->next = NULL;
    last1 = buf;
    return value;
}

Stack* push_stack2(int value)
{
    Stack* new_elem = (Stack*)malloc(sizeof(Stack));
    new_elem->value = value;
    if (last2 == NULL)
    {
        last2 = new_elem;
        fst2 = new_elem;
        last2->next = NULL;
        last2->prev = NULL;
        return last2;
    }
    new_elem->next = NULL;
    last2->next = new_elem;
    new_elem->prev = last2;
    last2 = new_elem;
    return last2;
}

int pop_stack2()
{
    int value = last2->value;
    Stack* buf = last2->prev;
    if (fst2 == last2)
    {
        free(last2);
        fst2 = NULL;
        last2 = NULL;
        return value;
    }
    free(last2);
    buf->next = NULL;
    last2 = buf;
    return value;
}
//STACK

void add(Vertex* graph, int from, int to) //мб дефектный
{
    graph[from].arr = (Edge*)realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].from = from;
    graph[from].arr[graph[from].count].to = to;
    ++graph[from].count;

    /*graph[from].arr = (Edge*)realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].from = to;
    graph[from].arr[graph[from].count].to = from;
    ++graph[from].count;*/
}

void dfs1(Vertex* graph, int src, int n, int* visit)
{
    visit[src] = 1;
    for (int i = 0; i < graph[src].count; ++i)
    {
        if (visit[graph[src].arr[i].to] != 1)
        {
            dfs1(graph, graph[src].arr[i].to, n, visit);
        }
    }
    push_stack1(src);
}

void dfs2(Vertex* graph, int src, int n, int* visit)
{
    visit[src] = 1;
    for (int i = 0; i < graph[src].count; ++i)
    {
        if (visit[graph[src].arr[i].to] != 1)
        {
            dfs2(graph, graph[src].arr[i].to, n, visit);
        }
    }
    push_stack2(src);
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0;
    fscanf(in, "%d%d", &n, &m);

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    Vertex* graph_reverse = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].count = 0;
        graph[i].visit = 0;
        graph[i].num = 0;

        graph_reverse[i].arr = NULL;
        graph_reverse[i].count = 0;
        graph_reverse[i].visit = 0;
        graph_reverse[i].num = 0;
    }

    int from = 0, to = 0;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d", &from, &to);
        add(graph, from, to);
        add(graph_reverse, to, from);
    }

    int* visit = malloc(sizeof(int) * (n + 1));
    memset(visit, 0, sizeof(int) * (n + 1));

    for (int i = 1; i < n + 1; ++i)
    {
        if (visit[i] != 1)
            dfs1(graph, i, n, visit);
    }

    int v = 0, count = 1, ans_size = 0;
    int* ans = malloc(sizeof(int) * (n + 1));
    memset(visit, 0, sizeof(int) * (n + 1));
    for (int i = 1; i < n + 1; ++i)
    {
        v = pop_stack1();
        if (visit[v] != 1)
        {
            dfs2(graph_reverse, v, n, visit);
            while (last2 != NULL)
            {
                //fprintf(out, "%d\n", pop_stack2());
                graph[pop_stack2()].num = count;
                ans[ans_size] = count;
                ++ans_size;
            }
            ++count;
            //fprintf(out, "\n\n");
        }
    }

    fprintf(out, "%d\n", count - 1);
    for (int i = 1; i < n + 1; ++i)
    {
        fprintf(out, "%d ", graph[i].num);
    }
}