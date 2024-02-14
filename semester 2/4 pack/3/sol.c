#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "sol.h"

typedef struct Graph_h
{
	Edge* arr;
	int count;
} Graph;

Graph* graph;

int getVerticesCount();
int readEdge(Edge* oEdge);

void init()
{
	int count = getVerticesCount();
	graph = (Graph*)malloc(sizeof(Graph) * count);
	for (int i = 0; i < count; ++i)
	{
		graph[i].arr = NULL;
		graph[i].count = 0;
	}

	Edge curr_edge;
	while (readEdge(&curr_edge))
	{
		graph[curr_edge.to].arr = realloc(graph[curr_edge.to].arr, sizeof(Edge) * (graph[curr_edge.to].count + 1));
		graph[curr_edge.to].arr[graph[curr_edge.to].count].from = curr_edge.to;
		graph[curr_edge.to].arr[graph[curr_edge.to].count].to = curr_edge.from;
		graph[curr_edge.to].arr[graph[curr_edge.to].count].weight = curr_edge.weight;
		++graph[curr_edge.to].count;

		graph[curr_edge.from].arr = realloc(graph[curr_edge.from].arr, sizeof(Edge) * (graph[curr_edge.from].count + 1));
		graph[curr_edge.from].arr[graph[curr_edge.from].count].from = curr_edge.from;
		graph[curr_edge.from].arr[graph[curr_edge.from].count].to = curr_edge.to;
		graph[curr_edge.from].arr[graph[curr_edge.from].count].weight = curr_edge.weight;
		++graph[curr_edge.from].count;
	}
}

int getEdgesCount(int iVertex)
{
	return graph[iVertex].count;
}

Edge getIncidentEdge(int iVertex, int iIndex)
{
	return graph[iVertex].arr[iIndex];
}