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

//structers
typedef struct Elem
{
    int cap;
    int flow;
} Elem;

typedef struct Edge
{
    int to;
    int cap;
    int flow;
} Edge;

typedef struct Vertex
{
    Edge* arr;
    int count;
} Vertex;

void add_edge(Vertex* graph, int from, int to, int cap)
{
    graph[from].arr = realloc(graph[from].arr, sizeof(Edge) * (graph[from].count + 1));
    graph[from].arr[graph[from].count].to = to;
    graph[from].arr[graph[from].count].cap = cap;
    graph[from].arr[graph[from].count].flow = 0;
    graph[from].count++;

    graph[to].arr = realloc(graph[to].arr, sizeof(Edge) * (graph[to].count + 1));
    graph[to].arr[graph[to].count].to = to;
    graph[to].arr[graph[to].count].cap = cap;
    graph[to].arr[graph[to].count].flow = 0;
    graph[to].count++;
}

typedef struct Queue
{
    int value;
    struct Queue* next;
} Queue;

Queue* fst = NULL;
Queue* last = NULL;

Queue* push_q(int value)
{
    Queue* new = malloc(sizeof(Queue));
    new->value = value;
    new->next = NULL;
    if (last != NULL)
    {
        last->next = new;
        last = last->next;
    }
    else
    {
        last = new;
    }
    if (fst == NULL)
        fst = last;
    return last;
}

int pop_q()
{
    int value = fst->value;
    Queue* buf = fst->next;
    if (fst != last)
    {
        free(fst);
        fst = buf;
    }
    else
    {
        free(fst);
        fst = NULL;
        last = NULL;
    }
    return value;
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0;
    fscanf(in, "%d%d", &n, &m);

    Elem** matrix = malloc(sizeof(Elem*) * (n + 1));
    for (int i = 0; i < n + 1; ++i)
    {
        matrix[i] = malloc(sizeof(Elem) * (n + 1));
        memset(matrix[i], 0, sizeof(Elem) * (n + 1));
    }
    
    int from, to, cap;
    for (int i = 0; i < m; ++i)
    {
        fscanf(in, "%d %d %d", &from, &to, &cap);
        matrix[from][to].cap = matrix[to][from].cap = cap;
    }

    int f = 0, * visit = malloc(sizeof(int) * (n + 1)), * path = malloc(sizeof(int) * (n + 1)); 
    memset(path, 0, sizeof(int) * (n + 1));
    int s = 1, t = n, u = 0, CP = 0, x = 0, y = 0;

    /*for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            printf("%d ", matrix[i][j].flow);
        }
        printf("\n");
    }
    printf("\n");*/

    while(1)
    {
        memset(visit, 0, sizeof(int) * (n + 1));
        visit[s] = 1;
        push_q(s);
        while (fst != NULL)
        {
            u = pop_q();
            for (int i = 1; i < n + 1; ++i)
            {
                if (matrix[u][i].cap == 0)
                    continue;

                if (matrix[u][i].cap - matrix[u][i].flow > 0)
                {
                    if (visit[i] != 1)
                    {
                        visit[i] = 1;
                        push_q(i);
                        path[i] = u;
                    }
                }
            }
        }

        if (visit[t] != 1)
            break;

        CP = inf;
        x = t;
        while (x != s)
        {
            y = path[x];
            CP = min(CP, matrix[y][x].cap - matrix[y][x].flow);
            x = y;
        }

        x = t;
        while (x != s)
        {
            y = path[x];
            matrix[y][x].flow += CP;
            matrix[x][y].flow -= CP;
            x = y;
        }
    }

    /*for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            printf("%d - %d ", matrix[i][j].cap, matrix[i][j].flow);
        }
        printf("\n");
    }*/

    int ans = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        ans += matrix[t][i].flow;
    }
    fprintf(out, "%d", -ans);
}