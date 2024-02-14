#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int main(int argc, char** argv)
{
	char comand[50];
	char plagin[50];

	//int n = strlen(argv[1]);
	int i = 0;
	while (argv[1][i] != ':')
	{
		comand[i] = argv[1][i];
		++i;
	}
	++i;
	comand[i] = '\0';
	int j = 0;
	while (argv[1][i] != '\0')
	{
		plagin[j] = argv[1][i];
		++i;
		++j;
	}
	++j;
	comand[j] = '\0';

	//проверка на существование команды и плагина
	
	//проверка на существование команды и плагина
}
