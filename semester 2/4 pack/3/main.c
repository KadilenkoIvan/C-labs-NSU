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

int main()
{
	int n = 0;
	Edge curr;
	init();
	n = getEdgesCount(0);
	printf("%d\n", n);
	n = getEdgesCount(1);
	printf("%d\n", n);
	n = getEdgesCount(2);
	printf("%d\n", n);
	n = getEdgesCount(3);
	printf("%d\n", n);
	n = getEdgesCount(4);
	printf("%d\n", n);
	curr = getIncidentEdge(0, 0);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(0, 1);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(1, 0);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(1, 3);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(1, 2);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(1, 1);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(2, 0);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(2, 1);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(3, 0);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(4, 2);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(4, 0);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
	curr = getIncidentEdge(4, 1);printf("%d %d %d\n", curr.from, curr.to, curr.weight);
}