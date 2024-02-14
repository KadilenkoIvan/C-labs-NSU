#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int pos = 0;
int pos_for_value = 0;

typedef struct elem_s
{
	char name[100];//мб нужно больше
	char value[2000];//мб нужно больше
}elem;

char* get_JSON(char* text, char* end, FILE* file)//без '\n'
{
	char* buf = malloc(500010);
	int i = 0;

	fgets(buf, 500010, file);
	while (strcmp(buf, end) != 0)
	{
		strcpy(&text[i], buf);
		i += strlen(buf) - 1;
		fgets(buf, 500010, file);
	}
	free(buf);
	return text;
}

//char* read_value_qwerty

char* read_value(char* text, char* str)
{
	if (text[pos] == '[')
	{
		str[pos_for_value] = text[pos];
		++pos;
		++pos_for_value;
		while (text[pos] != ']')
		{
			if (isspace(text[pos]))
			{
				++pos;
				continue;
			}
			if (text[pos] == '[' || text[pos] == '{')
			{
				read_value(text, str);
			}
			str[pos_for_value] = text[pos];
			++pos_for_value;
			++pos;
		}
	}
	else if (text[pos] == '{')
	{
		str[pos_for_value] = text[pos];
		++pos;
		++pos_for_value;
		while (text[pos] != '}')
		{
			if (isspace(text[pos]))
			{
				++pos;
				continue;
			}
			if (text[pos] == '[' || text[pos] == '{')
			{
				read_value(text, str);
			}
			str[pos_for_value] = text[pos];
			++pos_for_value;
			++pos;
		}
	}
}

int parse(char* text, elem* arr)
{
	int num_arr = 0;
	char* name = malloc(10001);
	while (text[pos] != '\0')
	{
		if (isspace(text[pos]))
		{
			++pos;
			continue;
		}

		if (text[pos] == '"')
		{
			//read name;
			int j = 0;
			name[j] = text[pos];
			++pos;
			++j;
			while (text[pos] != '"')
			{
				name[j] = text[pos];
				++pos;
				++j;
			}
			name[j] = text[pos];
			++pos;
			++j;
			name[j] = '\0';
			strcpy(arr[num_arr].name, name);
			//read name

			//read value
			while(isspace(text[pos]) || text[pos] == ':')//могут быть проблемы из-за "|| ..."
				++pos;

			memset(name, 0, 10001);
			pos_for_value = 0;
			if (text[pos] == '[' || text[pos] == '{')
			{
				//pos_for_value = j;
				read_value(text, name);
			}
			while (text[pos] != ',' && text[pos] != '}')
			{
				name[pos_for_value] = text[pos];
				++pos_for_value;
				++pos;
			}
			strcpy(arr[num_arr].value, name);
			++num_arr;
			continue;
		}
		++pos;
	}
	free(name);
	return num_arr;
}

char* request_processing(elem* arr, int count_of_elements, char** request, int n)
{
	int ind = 0;
	for (int i = 0; i < count_of_elements; ++i)
	{
		if (strcmp(request[0], arr[ind].name) == 0) break;
		++ind;
	}
	int ost = n - 1, ind_in_arr = 0, curr = 1, in_arr = 0, r = 0, check = 0, zapiatie = 0;
	while (ost != 0)
	{
		if (request[curr][0] == '[')
		{
			zapiatie = 0;
			int razmernost_arr = 0;// если [[ то = 1, если [ то = 0
			while (arr[ind].value[in_arr] == '[')
			{
				++razmernost_arr;
				++in_arr;
			}
			
			request[curr][strlen(request[curr]) - 1] = '\0';
			request[curr] = &request[curr][1];
			ind_in_arr = atoi(request[curr]);
			
			if (razmernost_arr > 1)
			{
				//zapiatie *= razmernost_arr;
				//pow(ind_in_arr, razmernost_arr);
				int power = ind_in_arr;
				for (int z = 1; z < razmernost_arr; ++z)
					ind_in_arr *= power;

				while (zapiatie != ind_in_arr)
				{
					if (arr[ind].value[in_arr] == ']')
						++zapiatie;
					in_arr++;
				}
				in_arr++;//!?!?!?!?!?!?
			}
			else
			{
				zapiatie = 0;
				while (zapiatie != ind_in_arr)
				{
					if (arr[ind].value[in_arr] == ',')
						++zapiatie;
					++in_arr;
				}
				//++in_arr;
			}
		}
		else
		{
			r = strlen(request[curr]);
			while (1)
			{
				char buf = arr[ind].value[r + in_arr];
				arr[ind].value[r + in_arr] = '\0';
				//
				if (strcmp(request[curr], &arr[ind].value[in_arr]) == 0)
				{
					arr[ind].value[r + in_arr] = buf;
					break;
				}
				//
				arr[ind].value[r + in_arr] = buf;
				++in_arr;
			}
		}
		++curr;
		--ost;
		check = 1;
	}

	char* ans = malloc(10001);
	int j = 0, end = strlen(arr[ind].value);
	if (check == 0)
	{
		return arr[ind].value;
	}
	else if (arr[ind].value[in_arr + r] == ':')
	{
		in_arr++;
		while (arr[ind].value[in_arr + r] != '}' && arr[ind].value[in_arr + r] != ']' && arr[ind].value[in_arr + r] != ',' && in_arr + r != end)
		{
			ans[j] = arr[ind].value[in_arr + r];
			++j;
			++in_arr;
		}
		ans[j] = '\0';
	}
	else
	{
		while (arr[ind].value[in_arr] == '[')
			in_arr++;
		while (arr[ind].value[in_arr + r] != '}' && arr[ind].value[in_arr + r] != ']' && arr[ind].value[in_arr + r] != ',' && in_arr + r != end)
		{
			ans[j] = arr[ind].value[in_arr + r];
			++j;
			++in_arr;
		}
		ans[j] = '\0';
	}

	return ans;
}

int main()//можно попробовать, чтобы value в elem было указателем на значение
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	char text[500010];

	//функция считывания
	get_JSON(text, "<<<>>>\n", in);
	//функция считывания
	printf("%s\n", text);// вывод JSON
	
	// считывание в масси  структур
	elem* arr = malloc(sizeof(elem) * 1000);// мб больше
	int count_of_elements = parse(text, arr);
	// считывание в массив структур

	//вывод полученного массива
	for (int i = 0; i < count_of_elements; ++i)
	{
		printf("%s:%s\n", arr[i].name, arr[i].value);
	}
	//вывод полученного массива

	//создание строки ответа и массива строк запросов
	char* ans = malloc(10000);
	char** request = malloc(sizeof(char*) * 100);//мб больше
	for (int i = 0; i < 100; ++i)
	{
		request[i] = malloc(1000);//мб больше
	}
	//создание строки ответа и массива строк запросов

	int n = 0;
	char garbage = 0;
	fscanf(in, "%d%c", &n, &garbage);
	while (n != -1)
	{
		for (int i = 0; i < n; ++i)//обработка запроса из count составляющих
		{
			fgets(request[i], 500010, in);
			request[i][strlen(request[i]) - 1] = '\0';
		}
		strcpy(ans, request_processing(arr, count_of_elements, request, n));
		fscanf(in, "%d%c", &n, &garbage);


		printf("\n%s", ans);
	}

	free(ans);
	free(arr);
	for (int i = 0; i < 100; ++i)
	{
		free(request[i]);
	}
	return 0;
}