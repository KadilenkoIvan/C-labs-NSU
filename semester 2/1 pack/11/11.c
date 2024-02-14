﻿
;
// https://translated.turbopages.org/proxy_u/auto-en-ru.en.4d947d80-63eb2c06-bde06240-74722d776562/https/learn.microsoft.com/en-us/cpp/cpp/main-function-command-line-args?view=msvc-170&viewFallbackFrom=vs-2017
// https://daviddeley.com/autohotkey/parameters/parameters.htm#WIN
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
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	char* str = malloc(200);
	memset(str, 0, 200);
	char* word = malloc(200);
	memset(word, 0, 200);

	int n = 0, j = 0;
	while (fscanf(in, "%c", &str[n]) != -1) ++n;

	int count_of_slash = 0, count_of_letters = 0;
	for (int i = 0; i < n; ++i)
	{
		if (str[i] == '\\')// '\' maybe something wrong
		{
			count_of_slash = 0;
			while (str[i] == '\\')
			{
				count_of_slash++;
				i++;
			}
			continue;
		}

		if (str[i] == '"')
		{
			if (count_of_slash % 2 == 0)//even
			{

			}
			else//odd
			{

			}
		}

		/*for (int j = 0; j < count_of_slash; ++j)
		{
			word[count_of_letters] = '\\';
			count_of_letters++;
		}*/

		if (str[i] == ' ' || str[i] == '\n')//end of word
		{
			word[count_of_letters] = '\0';//???//
			fprintf(out, "[%s]\n", word);
			count_of_letters = 0;
			memset(word, 0, 200);
		}
	}

	return 0;
}
//   " qwerty "      ""    qwe asd "zxc fgh"       polt    "    " exit
//"v  t"  " qwerty "    e  ""    qwe      asd "zxc fgh"       polt    "    " exit ""