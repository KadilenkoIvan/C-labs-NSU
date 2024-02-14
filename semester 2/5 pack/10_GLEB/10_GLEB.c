#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Vertex {
	struct Vertex* self;
	char color; //1 - white; 0 - gray -1 - black
	int distance;
	int tup;
	int num;
	char used;
	struct Vector* adjacent;
	struct Vertex* ancestor;
}Vertex;

typedef struct Edge {
	int num;
	char isOnly;
	Vertex* end;
}Edge;

typedef struct Vector {//global[1].adjacent->first[1]
	Edge** first;
	int used;
	int len;
} Vector;

void addToVector(Edge* el, Vector* vector) {
	if (vector->used == vector->len) {
		vector->first = (Edge**)realloc(vector->first, (vector->len + 1) * sizeof(Edge*));
		vector->len += 1;
	}
	vector->first[vector->used] = el;
	vector->used++;
}

Edge* getLastFromVector(Vector* vector) {
	if (vector->used > 0) {
		vector->used--;
		return vector->first[vector->used];
	}
	return NULL;
}

typedef struct VectorInt {
	int* val;
	int used;
	int len;
} VectorInt;

void addToVectorInt(int el, VectorInt* vector) {
	if (vector->used == vector->len) {
		vector->val = (int*)realloc(vector->val, (vector->len + 1) * sizeof(int));
		vector->len += 1;
	}
	vector->val[vector->used] = el;
	vector->used++;
}

Vertex** heap;
VectorInt* bridges;
int tin;
char* edges;
int edgeCount;
int v;

void dfsVisit(Vertex* vert, Vertex* p) 
{
	vert->color = 0;
	vert->distance = vert->tup = tin++;
	for (int i = 0; i < vert->adjacent->used; i++) {
		Vertex* tmp = (Vertex*)vert->adjacent->first[i]->end;
		if (tmp == NULL) continue;
		if (tmp->used == 1) {
			edges[vert->adjacent->first[i]->num] = -1;
			edgeCount--;
			for (int j = 0; j < vert->adjacent->used; j++) {
				if (vert->adjacent->first[i]->end->num == tmp->num) {
					edges[vert->adjacent->first[j]->num] = -1;
				}
			}
			tmp->used = 2;
			continue;
		}
		if (tmp == p) continue;
		if (tmp->color == 1) {
			dfsVisit(tmp, vert);
			if (vert->tup > tmp->tup) vert->tup = tmp->tup;
			if (tmp->tup > vert->distance) {
				// addToVectorInt(vert->adjacent->first[i]->num, bridges);
				edges[vert->adjacent->first[i]->num] = 1;
				edgeCount++;
				// tmp->color = -1;
				tmp->used = 1;
			}
		}
		else if (tmp->color == 0) {
			if (vert->tup > tmp->distance) vert->tup = tmp->distance;
			else vert->tup = vert->tup;
		}
	}
	for (int i = 0; i < vert->adjacent->used; i++) {
		vert->adjacent->first[i]->end->used = 0;
	}
	// vert->color = -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, e, p, k;
	scanf("%d %d\n", &n, &e);
	v = n;
	Vertex* vertices = (Vertex*)calloc(n + 1, sizeof(Vertex));
	// bridges = (VectorInt*) calloc(1, sizeof(VectorInt));
	// bridges->used = 0;
	edges = (char*)calloc(e + 1, sizeof(char));
	// bridges->len = 0;

	int count = 0;
	tin = 1;
	edgeCount = 0;

	//FIRST INITIALIZE
	for (int i = 1; i <= n; i++) {
		vertices[i].distance = -1;
		vertices[i].color = 1;
		vertices[i].num = i;
		vertices[i].adjacent = NULL;
		vertices[i].ancestor = NULL;
		vertices[i].used = 0;

		vertices[i].adjacent = (Vector*)calloc(1, sizeof(Vector));
		vertices[i].adjacent->first = NULL;
		vertices[i].adjacent->used = 0;
		vertices[i].adjacent->len = 0;
		//vertices[i].self = vertices[i];
	}

	for (int i = 1; i <= e; i++) {
		int row, column;
		scanf("%d %d", &row, &column);
		count++;
		if (column == row) continue;

		Edge* fst = (Edge*)malloc(sizeof(Edge));
		fst->end = &vertices[column];
		fst->num = count;
		addToVector(fst, vertices[row].adjacent);

		Edge* snd = (Edge*)malloc(sizeof(Edge));
		snd->end = &vertices[row];
		snd->num = count;
		addToVector(snd, vertices[column].adjacent);

		// edges[i] = 1;
	}

	for (int i = 1; i <= n; i++) {
		if (vertices[i].color == 1) dfsVisit(&vertices[i], NULL);
	}

	// edgeCount = 0;
	// for(int i = 1; i <= e; i++){
	// if(edges[i] == 1) edgeCount++;
	// }
	printf("%d\n", edgeCount);
	for (int i = 1; i <= e; i++) {
		if (edges[i] == 1) printf("%d ", i);
	}

	return 0;
}