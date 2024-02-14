#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct cycle_bufer_s
{
    int* arr;
    int begin;
    int end;
	int size;
    int max_size;
}cycle_bufer;

int main()
{
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);

    cycle_bufer left;
    cycle_bufer right;

    left.arr = malloc(sizeof(int) * (2 * n + 1));
	memset(left.arr, 0, sizeof(int) * (2 * n + 1));
    left.max_size = 2 * n + 1;
    left.begin = 0;
    left.end = n - 1;
	left.size = n;

    right.arr = malloc(sizeof(int) * (2 * n + 1));
	memset(right.arr, 0, sizeof(int) * (2 * n + 1));
    right.max_size = 2 * n + 1;
    right.begin = 0;
    right.end = n - 1;
	right.size = n;

    for (int i = 0; i < n; ++i)
    {
        left.arr[i] = i + 1;
        right.arr[i] = -left.arr[i];
    }
    
    char* commands = malloc(sizeof(char) * m);
    if (m != 0)
        scanf("%s", commands);

	int curr_comand = 0, left_or_right = 0, buf = 0;

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
				if ((right.end + 1) % right.max_size == right.begin)// maybe wrong, use %
				{
					continue;
				}
				buf = right.arr[right.end];
				right.arr[right.end] = 0;
				right.end = (right.end - 1 + right.max_size) % right.max_size;
				--right.size;
			}
			else//left
			{
				if ((left.end + 1) % left.max_size == left.begin)// maybe wrong, use %
				{
					continue;
				}
				buf = left.arr[left.end];
				left.arr[left.end] = 0;
				left.end = (left.end - 1 + left.max_size) % left.max_size;
				--left.size;
			}
			curr_comand -= 4;
		}
		else//from top(begin)
		{
			if (left_or_right == 1)//right
			{
				if ((right.end + 1) % right.max_size == right.begin)// maybe wrong, use %
				{
					continue;
				}
				buf = right.arr[right.begin];
				right.arr[right.begin] = 0;
				right.begin = (right.begin + 1 + right.max_size) % right.max_size;//???//
				--right.size;
			}
			else//left
			{
				if ((left.end + 1) % left.max_size == left.begin)// maybe wrong, use %
				{
					continue;
				}
				buf = left.arr[left.begin];
				left.arr[left.begin] = 0;
				left.begin = (left.begin + 1 + left.max_size) % left.max_size;//???//
				--left.size;
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
				right.end = (right.end + 1 + right.max_size) % right.max_size;
				right.arr[right.end] = buf;
				++right.size;
			}
			else//left
			{
				left.end = (left.end + 1 + left.max_size) % left.max_size;
				left.arr[left.end] = buf;
				++left.size;
			}
		}
		else//to top(begin)
		{
			if (left_or_right == 1)//right
			{
				right.begin = (right.begin - 1 + right.max_size) % right.max_size;
				right.arr[right.begin] = buf;
				++right.size;
			}
			else//left
			{
				left.end = (left.end - 1 + left.max_size) % left.max_size;
				left.arr[left.begin] = buf;
				++left.size;
			}
		}
	}

	printf("%d ", left.size);
	if (left.begin > left.end)
	{
		while (left.begin < left.max_size)
		{
			printf("%d ", left.arr[left.begin]);
			left.begin++;
		}
		for (int i = 0; i <= left.end; ++i)
		{
			printf("%d ", left.arr[i]);
		}
	}
	else
	{
		for (int i = left.begin; i <= left.end; ++i)
		{
			printf("%d ", left.arr[i]);
		}
	}
	printf("\n%d ",right.size);
	if (right.begin > right.end)
	{
		while (right.begin < right.max_size)
		{
			printf("%d ", right.arr[right.begin]);
			right.begin++;
		}
		for (int i = 0; i <= right.end; ++i)
		{
			printf("%d ", right.arr[i]);
		}
	}
	else
	{
		for (int i = right.begin; i <= right.end; ++i)
		{
			printf("%d ", right.arr[i]);
		}
	}

    return 0;
}//4,8,C <- work wrong (5 1 _)