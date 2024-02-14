#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int simbol_cheak(char letter, char* symbols, int size_symbol)
{
	for (int q = 0; q < size_symbol; ++q)
	{
		if (letter == symbols[q])
		{
			return 0;
		}
	}
	return 1;
}

void* words_split(char* str, char* symbols)
{	
	int size = strlen(str), size_symbol = strlen(symbols);
	int j = -1, cheak = 0;

	for (int i = 0; i < size; ++i)
	{
		cheak = simbol_cheak(str[i], symbols, size_symbol);
		if (cheak == 1)
		{
			while (i < size && cheak == 1)
			{
				cheak = simbol_cheak(str[i], symbols, size_symbol);
				if (cheak == 1)
				{
					++j;
					str[j] = str[i];
					++i;
				}

			}
		}
		
		if (str[j] != '|' && j >= 0)
		{
			str[j + 1] = '|';
			j++;
		}
	}
	str[j] = '|';
	str[j+1] = '\0';
}

void symbols_count(char* str)
{
	int size = strlen(str), count = 0, up = 0;
	for (int i = 0; i < size; ++i)
	{
		while(str[i] != '|')
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				++up;
			++count;
			++i;
		}
		printf("%d/%d ", up, count);
		i -= count;
		while (str[i] != '|')
		{
			printf("%c", str[i]);
			++i;
		}
		printf("\n");
		count = 0;
		up = 0;
	}
}

int main()
{
	char str[1000002] = "";
	char symbols[100] = ";:,.";
	scanf("%s", str);

	words_split(str, symbols);
	
	//printf("%s", str);

	symbols_count(str);
}