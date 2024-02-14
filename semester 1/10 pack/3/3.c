#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s
{
	int value;
	struct node_s* prev;
	struct node_s* next;
}node;

node* create_new(int value)
{
	node* new = malloc(sizeof(node));
	new->value = value;
	return new;
}

int main()//НУЖНО СОЗДАТЬ ОТДЕЛЬНЫЙ HEAD, LAST, В КОТОРЫХ БУДУТ ТОЛЬКО NEXT, PREV
{
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	int size = 2 * n + 1;

	node* right_head = malloc(sizeof(node));
	node* left_head = malloc(sizeof(node));
	node* right_last = malloc(sizeof(node));
	node* left_last = malloc(sizeof(node));

	right_head->next = right_last;
	right_head->prev = NULL;
	right_last->prev = right_head;
	right_last->next = NULL;

	left_head->next = left_last;
	left_head->prev = NULL;
	left_last->prev = left_head;
	left_last->next = NULL;

	node* new_r, *new_l, *curr_right, *curr_left;

	curr_right = create_new(-1);
	right_head->next = curr_right;
	right_last->prev = curr_right;

	curr_left = create_new(1);
	left_head->next = curr_left;
	left_last->prev = curr_left;

	for (int i = 2; i <= n; ++i)
	{
		new_r = create_new(-i);
		curr_right->next = new_r;
		new_r->prev = curr_right;
		curr_right = new_r;
		//right_last->prev = new_r;//		

		new_l = create_new(i);
		curr_left->next = new_l;
		new_l->prev = curr_left;
		curr_left = new_l;
		//right_last->prev = new_l;//
	}

	right_last->prev = curr_right;
	curr_right->next = right_last;
	left_last->prev = curr_left;
	curr_left->next = left_last;

	int left_size = n, right_size = n, curr_comand = 0, left_or_right = 0;
	char* commands = malloc(sizeof(char) * m);
	if (m != 0)
		scanf("%s", commands);

	node* buf;

	for (int i = 0; i < m; ++i)
	{
		if (commands[i] >= '0' && commands[i] <= '9')
		{
			curr_comand = commands[i] - '0';
		}
		else
		{
			curr_comand = commands[i] - 'A' + 10;
		}
		if (curr_comand == 15 || curr_comand == 10 || curr_comand == 5 || curr_comand == 0)
		{
			continue;
		}

		if (curr_comand >= 8)
		{
			left_or_right = 1;
			curr_comand -= 8;
		}
		else
		{
			left_or_right = -1;
		}

		if (curr_comand >= 4)//from bottom(last)
		{
			if (left_or_right == 1)//right
			{
				if (right_head->next == right_last)
				{
					continue;
				}
				buf = right_last->prev;
				if (right_head->next == right_last->prev)
				{
					right_head->next = right_last;
					right_last->prev = right_head;
				}
				else
				{
					right_last->prev = right_last->prev->prev;
					right_last->prev->next = right_last;
				}
				--right_size;
			}
			else//???//
			{
				if (left_head->next == left_last)
				{
					continue;
				}
				buf = left_last->prev;
				if (left_head->next == left_last->prev)
				{
					left_head->next = left_last;
					left_last->prev = left_head;
				}
				else
				{
					left_last->prev = left_last->prev->prev;
					left_last->prev->next = left_last;
				}
				--left_size;
			}
			curr_comand -= 4;
		}
		else//from top(head)
		{
			if (left_or_right == 1)
			{
				if (right_head->next == right_last)
				{
					continue;
				}
				buf = right_head->next;
				if (right_head->next == right_last->prev)
				{
					right_head->next = right_last;
					right_last->prev = right_head;
				}
				else
				{
					right_head->next = right_head->next->next;
					right_head->next->prev = right_head;
				}
				--right_size;
			}
			else//???//
			{
				if (left_head->next == left_last)
				{
					continue;
				}
				buf = left_head->next;
				if (left_head->next == left_last->prev)
				{
					left_head->next = left_last;
					left_last->prev = left_head;
				}
				else
				{
					left_head->next = left_head->next->next;
					left_head->next->prev = left_head;
				}
				--left_size;
			}
		}

		if (curr_comand >= 2)
		{
			left_or_right = 1;
			curr_comand -= 2;
		}
		else
		{
			left_or_right = -1;
		}

		if (curr_comand == 1)//to bottom(last)
		{
			if (left_or_right == 1)//right
			{
				buf->prev = right_last->prev;
				right_last->prev->next = buf;
				right_last->prev = buf;
				buf->next = right_last;
				++right_size;
			}
			else//left
			{
				buf->prev = left_last->prev;
				left_last->prev->next = buf;
				left_last->prev = buf;
				buf->next = left_last;
				++left_size;
			}
		}
		else//to top(head)
		{
			if (left_or_right == 1)//right
			{
				buf->next = right_head->next;
				right_head->next->prev = buf;
				right_head->next = buf;
				buf->prev = right_head;
				++right_size;
			}
			else//left
			{
				buf->next = left_head->next;
				left_head->next->prev = buf;
				left_head->next = buf;
				buf->prev = left_head;
				++left_size;
			}
		}
	}

	node* delete;
	printf("%d ", left_size);
	buf = left_head->next;
	while (buf != left_last)//
	{
		printf("%d ", buf->value);
		delete = buf;
		buf = buf->next;
		free(delete);
	}
	printf("\n%d ", right_size);
	buf = right_head->next;
	while (buf != right_last)//
	{
		printf("%d ", buf->value);
		delete = buf;
		buf = buf->next;
		free(delete);
	}
}
