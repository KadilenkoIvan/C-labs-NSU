#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int main()
{
	FILE* out = fopen("output.txt", "w");
	srand(time(0));
	int q = 0;
	for (int i = 0; i < 400000; ++i)
	{
		q = rand() & 1;
		if (q == 1)
		{
			fprintf(out, "R");
		}
		else
		{

		}
		fprintf(out, "L");
	}
}