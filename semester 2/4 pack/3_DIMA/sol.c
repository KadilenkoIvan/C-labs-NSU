#include <stdlib.h>
#include "sol.h"

typedef struct growArray 
{
    Edge** edges;
    int num;
} growArray;

growArray arr;

int readEdge(Edge* oEdge);
int getVerticesCount();

void init() 
{
    arr.num = getVerticesCount();
    arr.edges = (Edge**)malloc(sizeof(Edge*) * arr.num);
    int i = 0;
    while (arr.num > i)
    {
        arr.edges[i] = (Edge*)malloc(sizeof(Edge));
        arr.edges[i][0].weight = 0;
        i++;
    }

    while (0 == 0) 
    {
        Edge* tmp;
        tmp = (Edge*)malloc(sizeof(Edge));
        int status = readEdge(tmp);
        if (status != 0) 
        {
            int idF = tmp->from;
            int idT = tmp->to;
            ++(arr.edges[idF][0].weight);
            arr.edges[idF] = realloc(arr.edges[idF], (arr.edges[idF][0].weight + 1) * sizeof(Edge));
            arr.edges[idF][arr.edges[idF][0].weight].from = tmp->from;
            arr.edges[idF][arr.edges[idF][0].weight].to = tmp->to;
            arr.edges[idF][arr.edges[idF][0].weight].weight = tmp->weight;

            ++(arr.edges[idT][0].weight);
            arr.edges[idT] = realloc(arr.edges[idT], (arr.edges[idT][0].weight + 1) * sizeof(Edge));
            arr.edges[idT][arr.edges[idT][0].weight].from = tmp->to;
            arr.edges[idT][arr.edges[idT][0].weight].to = tmp->from;
            arr.edges[idT][arr.edges[idT][0].weight].weight = tmp->weight;
        }
        else break;
    }
}

int getEdgesCount(int iVertex) 
{ 
    return arr.edges[iVertex][0].weight; 
}

Edge getIncidentEdge(int iVertex, int iIndex)
{ 
    return arr.edges[iVertex][iIndex + 1]; 
}