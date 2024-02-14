#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct actor_bio_s
{
	char name[31];
	int year;
	char country[11];
}actor_bio;

typedef struct actor_in_movie_s
{
	char name[31];
	char movie[21];
}actor_in_movie;

typedef struct join_s
{
	char name1[31];
	int year;
	char country[11];
	char name2[31];
	char movie[21];
}join;

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	int n = 0;
	fscanf(in, "%d", &n);

	actor_bio* actors = malloc(sizeof(actor_bio) * n);
	memset(actors, 0, sizeof(actor_bio) * n);

	char trash = 0;
	//
	for (int i = 0; i < n; ++i)
	{
		fscanf(in, "%c", &trash);
		fscanf(in, "%c", &trash);
		for (int j = 0; 1; ++j)
		{
			fscanf(in, "%c", &actors[i].name[j]);
			if (actors[i].name[j] == '"')
			{
				actors[i].name[j] = '\0';
				break;
			}
		}

		fscanf(in, "%d", &actors[i].year);

		fscanf(in, "%c", &trash);
		fscanf(in, "%c", &trash);

		for (int j = 0; 1; ++j)
		{
			fscanf(in, "%c", &actors[i].country[j]);
			if (actors[i].country[j] == '"')
			{
				actors[i].country[j] = '\0';
				break;
			}
		}
		//printf("%s %d %s\n", actors[i].name, actors[i].year, actors[i].country);
	}
	//

	int m = 0;
	fscanf(in, "%d", &m);

	actor_in_movie* movies = malloc(sizeof(actor_in_movie) * m);
	memset(movies, 0, sizeof(actor_in_movie) * m);

	//
	for (int i = 0; i < m; ++i)
	{
		fscanf(in, "%c", &trash);
		fscanf(in, "%c", &trash);
		for (int j = 0; 1; ++j)
		{
			fscanf(in, "%c", &movies[i].name[j]);
			if (movies[i].name[j] == '"')
			{
				movies[i].name[j] = '\0';
				break;
			}
		}

		fscanf(in, "%c", &trash);
		fscanf(in, "%c", &trash);

		for (int j = 0; 1; ++j)
		{
			fscanf(in, "%c", &movies[i].movie[j]);
			if (movies[i].movie[j] == '"')
			{
				movies[i].movie[j] = '\0';
				break;
			}
		}
		//printf("%s %s\n", movies[i].name, movies[i].movie);
	}
	//

	join* answer = malloc(sizeof(join) * 100000);// MAYBE WRONG SIZE
	memset(answer, 0, sizeof(join) * 100000);

	int size = 0;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (strcmp(actors[i].name, movies[j].name) == 0)
			{
				strcpy(answer[size].name1, actors[i].name);
				answer[size].year = actors[i].year;
				strcpy(answer[size].country, actors[i].country);
				strcpy(answer[size].name2, movies[j].name);
				strcpy(answer[size].movie, movies[j].movie);
				++size;
			}
		}
	}

	for (int i = 0; i < size; ++i)
	{
		fprintf(out, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n", answer[i].name1, answer[i].year, answer[i].country, answer[i].name2, answer[i].movie);
	}
	free(actors);
	free(movies);
	free(answer);
	return(0);
}