#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void next_permut(char* arr, int size)
{
	int index = 0, min = 0, min_ind = 0, buf = 0;
	for (int i = size - 1 ; i > 0; --i)
	{
		if (arr[i] > arr[i - 1])
		{
			index = i;
			min = arr[i];
			min_ind = i;

			for (int j = i; j < size; ++j)
			{
				if (min > arr[j] && arr[j] > arr[i - 1])
				{
					min = arr[j];
					min_ind = j;
				}
			}

			buf = arr[index - 1];
			arr[index - 1] = arr[min_ind];
			arr[min_ind] = buf;
			break;
		}
	}

	for (int i = index; i < index + (size - index) / 2; ++i)
	{
		buf = arr[i];
		arr[i] = arr[size - i + index - 1];
		arr[size - i + index - 1] = buf;
	}

	for (int i = 0; i < size; ++i)
	{
		printf("%c ", arr[i]);
	}
}

int main()
{
	int size = 0;
	char garbage;

	scanf("%d", &size);
	scanf("%c", &garbage);
	char* arr = (char*)malloc(size * sizeof(char));

	for (int i = 0; i < size; ++i)
	{
		scanf("%c", &arr[i]);
		scanf("%c", &garbage);
	}

	next_permut(arr, size);

	free(arr);
}