#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

char* get_JSON(char* text, char* end, FILE* file)
{
	char* buf = malloc(500010);
	int i = 0;

	fgets(buf, 500010, file);
	while (strcmp(buf, end) != 0)
	{
		strcpy(&text[i], buf);
		i += strlen(buf);
		fgets(buf, 500010, file);
	}
	free(buf);
	return text;
}

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	char text[500010];
	int i = 0;

	//функция считывания
	get_JSON(text, "<<<>>>\n", in);
	//функция считывания
	
	printf("%s", text);// вывод JSON

	int count = 0;

	char buf[500010], garbage = 0;
	fscanf(in, "%d%c", &count, &garbage);
	while (count != -1)
	{
		for (int i = 0; i < count; ++i)//обработка запроса из count составляющих
		{
			fgets(buf, 500010, in);
		}
		printf("%d\n", count);
		fscanf(in, "%d%c", &count, &garbage);
	}
}