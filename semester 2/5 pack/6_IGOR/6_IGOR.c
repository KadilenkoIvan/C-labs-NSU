#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#pragma comment (linker , "/STACK:50000000")

int N, M, P, K;
int visit[301] = { 0 };
int graph[301][301];
int dist[301][301];
int count = 0;
int arr[301];

void printPathCount(int** path, int u, int v)
{
	int x, y;
	int i = 0;
	x = u - 1;
	y = v - 1;
	int c = x;
	while (c != y)
	{
		count++;
		c = path[c][y];
	}
	count++;
	printf("%d ", count);
	count = 0;
}

void printPath(int** path, int u, int v)
{
	int x, y;
	int i = 0;
	x = u - 1;
	y = v - 1;
	int c = x;
	while (c != y)
	{
		count++;
		printf("%d ", c + 1);
		c = path[c][y];
	}

	count = 0;
	printf("%d\n", v);
}

void floydWarshall(int** path)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (graph[i][j])
			{
				dist[i][j] = graph[i][j];
			}
			if (i == j)
			{
				dist[i][j] = 0;
			}
			if (!graph[i][j])
			{
				dist[i][j] = INT_MAX;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (dist[i][j] == INT_MAX)
			{
				path[i][j] = -1;
			}
			else {
				path[i][j] = j;
			}
		}
	}
	for (int k = 0; k < N; k++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d%d%d%d", &N, &M, &P, &K);

	int** path = (int**)malloc((sizeof(int*) * N) + 1);
	for (int i = 0; i <= N; i++)
	{
		path[i] = (int*)malloc((sizeof(int*) * N) + 1);
	}

	int u, v, s;

	for (size_t i = 0; i < M; i++)
	{
		scanf("%d%d%d", &u, &v, &s);
		if (graph[u - 1][v - 1] != 0 || graph[v - 1][u - 1] != 0)
		{
			if (graph[u - 1][v - 1] > s || graph[v - 1][u - 1] > s)
			{
				graph[u - 1][v - 1] = s;
				graph[v - 1][u - 1] = s;
			}
			continue;
		}
		else
		{
			graph[u - 1][v - 1] = s;
			graph[v - 1][u - 1] = s;
		}
	}

	floydWarshall(path);

	int start, end;
	for (size_t i = 0; i < P; i++)
	{
		scanf("%d%d", &start, &end);
		printf("%d ", dist[start - 1][end - 1]);
		printPathCount(path, start, end);
		printPath(path, start, end);
	}

	for (size_t i = 0; i < K; i++)
	{
		scanf("%d%d", &start, &end);
		printf("%d\n", dist[start - 1][end - 1]);
	}

	return 0;
}