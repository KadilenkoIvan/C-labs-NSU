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

int c = 0;
int trigger = 0;
int cycle(Vertex* graph, int pos)
{
    graph[pos].visit = 1;
    for (int i = 0; i < graph[pos].count; ++i)
    {
        if (graph[graph[pos].arr[i].to].visit == 0)
            cycle(graph, graph[pos].arr[i].to);
        if (graph[graph[pos].arr[i].to].visit == 1)
        {
            if (trigger == -1)
                return pos;
            push_stack(pos);
            if (c == 0)
                trigger = graph[pos].arr[i].to;
            if (pos == trigger)
                trigger = -1;
            ++c;
            return pos;
        }
    }
    graph[pos].visit = 2;
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    int n = 0, m = 0;
    fscanf(in, "%d %d", &n, &m);

    Vertex* graph = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].arr = NULL;
        graph[i].visit = 0;
        graph[i].count = 0;
    }

    int* ans = malloc(sizeof(int) * (n + 1));
    memset(ans, 0, sizeof(int) * (n + 1));
    //init

    //reading
    int to = 0, from = 0;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d", &from, &to);

        graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
        graph[from].arr[graph[from].count].from = from;
        graph[from].arr[graph[from].count].to = to;
        ++graph[from].count;
    }

    //for (int i = 0; i < m + 1; ++i)
    //{
    //    printf("%d = ", i);
    //    for (int j = 0; j < graph[i].count; ++j)
    //    {
    //        printf("[%d %d], ", graph[i].arr[j].from, graph[i].arr[j].to);
    //    }
    //    printf("\n");
    //}
    
    //reading
    
    int trigger = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        if (c != 0)
        {
            fprintf(out, "%d\n", c);
            for (int i = 0; i < c; ++i)
            {
                fprintf(out, "%d ", pop_stack());
            }
            exit(0);
        }
        cycle(graph, i);
    }

    fprintf(out, "-1");
}