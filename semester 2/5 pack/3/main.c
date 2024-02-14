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

typedef struct Cell
{
    char value;
    char visit;
    int length;
} Cell;

typedef struct Pos
{
    int i;
    int j;
}Pos;

typedef struct Queue
{
    Pos value;
    struct Queue* next;
} Queue;

Queue* fst = NULL;
Queue* last = NULL;

Queue* push_q(Pos value)
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

Pos pop_q()
{
    Pos value = fst->value;
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

void my_bfs(Cell** arr, Pos start, Pos finish, int n, int m)
{
    arr[start.i][start.j].visit = 1;
    arr[start.i][start.j].length = 0;
    push_q(start);
    Pos curr_pos, new_pos;
    while (fst != NULL)
    {
        curr_pos = fst->value;
        pop_q();
        if (curr_pos.i > 0)
        {
            if (arr[curr_pos.i - 1][curr_pos.j].visit == 0 && arr[curr_pos.i - 1][curr_pos.j].value != 'X')
            {
                arr[curr_pos.i - 1][curr_pos.j].visit = 1;
                arr[curr_pos.i - 1][curr_pos.j].length = arr[curr_pos.i][curr_pos.j].length + 1;
                new_pos.i = curr_pos.i - 1;
                new_pos.j = curr_pos.j;
                push_q(new_pos);
            }
        }
        if (curr_pos.j > 0)
        {
            if (arr[curr_pos.i][curr_pos.j - 1].visit == 0 && arr[curr_pos.i][curr_pos.j - 1].value != 'X')
            {
                arr[curr_pos.i][curr_pos.j - 1].visit = 1;
                arr[curr_pos.i][curr_pos.j - 1].length = arr[curr_pos.i][curr_pos.j].length + 1;
                new_pos.i = curr_pos.i;
                new_pos.j = curr_pos.j - 1;
                push_q(new_pos);
            }
        }
        if (curr_pos.i < n - 1)
        {
            if (arr[curr_pos.i + 1][curr_pos.j].visit == 0 && arr[curr_pos.i + 1][curr_pos.j].value != 'X')
            {
                arr[curr_pos.i + 1][curr_pos.j].visit = 1;
                arr[curr_pos.i + 1][curr_pos.j].length = arr[curr_pos.i][curr_pos.j].length + 1;
                new_pos.i = curr_pos.i + 1;
                new_pos.j = curr_pos.j;
                push_q(new_pos);
            }
        }
        if (curr_pos.j < m - 1)
        {
            if (arr[curr_pos.i][curr_pos.j + 1].visit == 0 && arr[curr_pos.i][curr_pos.j + 1].value != 'X')
            {
                arr[curr_pos.i][curr_pos.j + 1].visit = 1;
                arr[curr_pos.i][curr_pos.j + 1].length = arr[curr_pos.i][curr_pos.j].length + 1;
                new_pos.i = curr_pos.i;
                new_pos.j = curr_pos.j + 1;
                push_q(new_pos);
            }
        }

        //for (int i = 0; i < n; ++i)
        //{
        //    for (int j = 0; j < m; ++j)
        //    {
        //        printf("%d ", arr[i][j].length);
        //    }
        //    printf("\n");
        //}
        //printf("\n");
    }
}

int main()
{
	//init
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	int m = 0, n = 0;
	fscanf(in, "%d %d", &m, &n);
    Cell** lab = (Cell**)malloc(sizeof(Cell) * m);
    char garbage = 0;
    //int start_i = 0, start_j = 0, finish_i = 0, finish_j = 0;
    Pos start, finish;
    fscanf(in, "%c", &garbage);
	for (int i = 0; i < m; ++i)
	{
		lab[i] = (Cell*)malloc(sizeof(Cell) * (n));
        for (int j = 0; j < n; ++j)
        {
            fscanf(in, "%c", &lab[i][j].value);
            lab[i][j].visit = 0;
            lab[i][j].length = 0;
            if (lab[i][j].value == 'S')
            {
                start.i = i;
                start.j = j;
            }
			if (lab[i][j].value == 'F')
			{
				finish.i = i;
				finish.j = j;
			}
        }
        //lab[i][n] = '\0';
		fscanf(in, "%c", &garbage);
	}
	//init НЕ ФАКТ ЧТО ПРАВИЛЬНО

    my_bfs(lab, start, finish, m, n);
    if (lab[finish.i][finish.j].length == 0)
        fprintf(out, "-1");
    else
        fprintf(out, "%d", lab[finish.i][finish.j].length);

    for (int i = 0; i < m; ++i)
    {
        free(lab[i]);
    }
    free(lab);
	return 0;
}