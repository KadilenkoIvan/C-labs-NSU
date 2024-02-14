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
	char check;
	struct actor_bio_s* next;
	struct actor_bio_s* last;
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

unsigned long long hash_func(unsigned char* str)
{
	unsigned long long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

actor_bio* create(actor_bio* curr)
{
	actor_bio* new = malloc(sizeof(actor_bio));
	*new = *curr;
	return new;
}

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	int n = 0;
	fscanf(in, "%d", &n);

	actor_bio* actors = malloc(sizeof(actor_bio) * n * 2);
	memset(actors, 0, sizeof(actor_bio) * n * 2);

	char trash = 0;

	actor_bio curr;
	curr.next = NULL;
	curr.last = &curr;

	unsigned long long hash = 0, col_ind = 0;
	// START READ INFO ABOUT ACTORS
	for (int i = 0; i < n; ++i)
	{
		fscanf(in, "%c", &trash);
		fscanf(in, "%c", &trash);
		for (int j = 0; 1; ++j)
		{
			fscanf(in, "%c", &curr.name[j]);
			if (curr.name[j] == '"')
			{
				curr.name[j] = '\0';
				break;
			}
		}

		fscanf(in, "%d", &curr.year);

		fscanf(in, "%c", &trash);
		fscanf(in, "%c", &trash);

		for (int j = 0; 1; ++j)
		{
			fscanf(in, "%c", &curr.country[j]);
			if (curr.country[j] == '"')
			{
				
				curr.country[j] = '\0';
				break;
			}
		}
		//printf("%s %d %s\n", actors[i].name, actors[i].year, actors[i].country);

		// HASH
		hash = hash_func(curr.name) % n;
		if (actors[hash].check == 1)
		{
			col_ind = hash;
			while ((actors[col_ind].check == 1) && (strcmp(actors[col_ind].name, curr.name) != 0))
			{
				col_ind = col_ind + 1;
			}
			if (strcmp(actors[col_ind].name, curr.name) == 0 && actors[col_ind].check == 1)
			{
				if(actors[col_ind].year == curr.year && strcmp(actors[col_ind].country, curr.country) == 0)
					continue;

				actors[col_ind].last->next = create(&curr);
				actors[col_ind].last = actors[col_ind].last->next;
				actors[col_ind].last->next = NULL;
				continue;
			}
			actors[col_ind] = curr;
			actors[col_ind].last = &actors[col_ind];
			actors[col_ind].check = 1;
			//printf("%d) %s %d %s\n", col_ind, actors[col_ind].name, actors[col_ind].year, actors[col_ind].country);
			continue;
		}

		actors[hash] = curr;
		actors[hash].last = &actors[hash];
		actors[hash].check = 1;
		//printf("%d) %s %d %s\n",hash, actors[hash].name, actors[hash].year, actors[hash].country);
		//HASH
	}
	// END READ INFO ABOUT ACTORS

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

	join* answer = malloc(sizeof(join) * 200000);// MAYBE WRONG SIZE
	memset(answer, 0, sizeof(join) * 200000);

	int size = 0;
	hash = 0;
	col_ind = 0;

	for (int i = 0; i < m; ++i)
	{
		//HASH CHEAK
		hash = hash_func(movies[i].name) % n;
		if (actors[hash].check == 1)
		{
			if (strcmp(actors[hash].name, movies[i].name) != 0)
			{
				while (actors[hash].check == 1 && strcmp(actors[hash].name, movies[i].name) != 0)
				{
					++hash;
				}
				if (actors[hash].check == 0)
					continue;

			}
			strcpy(answer[size].name1, actors[hash].name);
			answer[size].year = actors[hash].year;
			strcpy(answer[size].country, actors[hash].country);
			strcpy(answer[size].name2, movies[i].name);
			strcpy(answer[size].movie, movies[i].movie);
			++size;
		}
		//HASH CHEAK
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