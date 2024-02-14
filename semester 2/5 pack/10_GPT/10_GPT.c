#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int low[MAX_VERTICES];
int parent[MAX_VERTICES];
bool bridge[MAX_VERTICES][MAX_VERTICES];
int num_vertices;
int num_edges;
int bridge_count;

void dfs(int u) {
    static int time = 0;
    visited[u] = low[u] = ++time;
    for (int v = 0; v < num_vertices; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                parent[v] = u;
                dfs(v);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];
                if (visited[u] < low[v]) {
                    bridge[u][v] = true;
                    bridge[v][u] = true;
                    bridge_count++;
                }
            }
            else if (v != parent[u]) {
                low[u] = (low[u] < visited[v]) ? low[u] : visited[v];
            }
        }
    }
}

void find_bridges() {
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
        for (int j = 0; j < num_vertices; j++) {
            bridge[i][j] = false;
        }
    }
    bridge_count = 0;
    int components = 0;
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            components++;
            dfs(i);
        }
    }
    if (components > 1) {
        bridge_count = 0;
    }
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);

    for (int i = 0; i < num_edges; i++) {
        int u, v;
        printf("Enter edge %d (u v): ", i + 1);
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    find_bridges();

    printf("Bridges:\n");
    int bridge_num = 1;
    for (int u = 0; u < num_vertices; u++) {
        for (int v = u + 1; v < num_vertices; v++) {
            if (bridge[u][v]) {
                printf("%d. Edge %d-%d\n", bridge_num++, u, v);
            }
        }
        if (bridge[u][num_vertices - 1]) {
            printf("%d. Edge %d-%d\n", bridge_num++, u, num_vertices - 1);
        }
    }
    if (bridge_count == 0) {
        printf("No bridges found.\n");
    }
    else {
        printf("%d bridge%s found.\n", bridge_count, (bridge_count == 1) ? "" : "s");
    }

    return 0;
}
