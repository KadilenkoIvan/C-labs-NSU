#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int ind = 0;

typedef struct tree_s
{
	int value;
	struct tree_s* left;
	struct tree_s* right;
	int count;
	unsigned char height;
}tree;

tree* create(int value)
{
	tree* new = malloc(sizeof(tree));
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	new->count = 1;
	new->height = 0;
	return new;
}

void shafl(int* arr, int n)
{
	int buf = 0, ind1 = 0, ind2 = 0;
	for (int i = 0; i < n; ++i)
	{
		ind1 = rand() % n;
		ind2 = rand() % n;
		buf = arr[ind1];
		arr[ind1] = arr[ind2];
		arr[ind2] = buf;
	}
}

unsigned char height(tree* elem)
{
	if (elem == NULL)
	{
		return 0;
	}
	else
	{
		return elem->height;
	}
}

int bfactor(tree* elem)
{
	return (height(elem->right) - height(elem->left));
}

void fixheight(tree* elem)
{
	unsigned char hl = height(elem->left);
	unsigned char hr = height(elem->right);
	if (hl > hr)
	{
		elem->height = hl + 1;
	}
	else
	{
		elem->height = hr + 1;
	}
}

tree* rotateright(tree* elem)
{
	tree* buf = elem->left;
	elem->left = buf->right;
	buf->right = elem;
	fixheight(elem);
	fixheight(buf);
	return buf;
}

tree* rotateleft(tree* elem)
{
	tree* buf = elem->right;
	elem->right = buf->left;
	buf->left = elem;
	fixheight(elem);
	fixheight(buf);
	return buf;
}

tree* balance(tree* elem)
{
	fixheight(elem);
	if (bfactor(elem) == 2)
	{
		if (bfactor(elem->right) < 0)
			elem->right = rotateright(elem->right);
		return rotateleft(elem);
	}
	if (bfactor(elem) == -2)
	{
		if (bfactor(elem->left) > 0)
			elem->left = rotateleft(elem->left);
		return rotateright(elem);
	}
	return elem;
}

tree* add_to_tree(int value, tree* elem)
{
	if (elem == NULL)
	{
		return create(value);
	}
	if (elem->value == value)
	{
		elem->count += 1;
	}
	else if (elem->value > value)
	{
		elem->left = add_to_tree(value, elem->left);
	}
	else
	{
		elem->right = add_to_tree(value, elem->right);
	}
	return balance(elem);
}

int* take_from_tree(int* arr, tree* elem)
{
	int count = 0;
	if (elem->left != NULL)
	{
		take_from_tree(arr, elem->left);
	}

	count = elem->count;
	for (int i = 0; i < count; ++i)
	{
		arr[ind] = elem->value;
		++ind;
	}

	if (elem->right != NULL)
	{
		take_from_tree(arr, elem->right);
	}
}

int* tree_sort(int* arr, int n)
{
	tree* root = create(arr[0]);
	for (int i = 1; i < n; ++i)
	{
		root = add_to_tree(arr[i], root);
	}

	return(take_from_tree(arr, root));
}

int main()
{
	FILE* in = fopen("input.bin", "rb");
	FILE* out = fopen("output.bin", "wb");
	int n = 0;
	fread(&n, sizeof(int), 1, in);

	int* arr = malloc(sizeof(int) * n);
	fread(arr, sizeof(int), n, in);

	tree_sort(arr, n);

	fwrite(arr, sizeof(int), n, out);
}