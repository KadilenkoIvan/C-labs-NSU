;
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

	char* str = malloc(1000);
	memset(str, 0, 1000);
	char* word = malloc(1000);
	memset(word, 0, 1000);

	int n = 0, j = 0, count = 0;
	while (fscanf(in, "%c", &str[n]) != -1) ++n;

	for (int i = 0; i < n; ++i)
	{
		if (str[i] == ' ' || str[i] == '\n')
			continue;
		while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		{
			if (str[i] == '\\')
			{
				count = 0;
				if (str[i + 1] == '"')
				{
					word[j] = '"';
					i += 2;
					++j;
					continue;
				}
				if (str[i + 1] == '\\')
				{
					while (str[i] == '\\')
					{
						++count;
						++i;
					}
					if (str[i] == '"')
					{
						if (count % 2 == 0)
						{
							count /= 2;
							for (int k = j; j < k + count; ++j)
							{
								word[j] = '\\';
							}
							goto qav;
						}
						else
						{
							count /= 2;
							for (int k = j; j < k + count; ++j)
							{
								word[j] = '\\';
							}
							word[j] = '"';
							++i;
							++j;
							continue;
						}
					}
					else
					{
						for (int k = j; j < k + count; ++j)
						{
							word[j] = '\\';
						}
					}
					continue;
				}
				word[j] = '\\';
				++i;
				++j;
				continue;
			}

			if (str[i] == '"')
			{
			qav:
				++i;
				if (str[i] == '\n' || str[i] == '\0')
				{
					continue;
				}
				while(1)
				{
					if (str[i] == '\n' || str[i] == '\0')
					{
						break;
					}

					if (str[i] == '\\')
					{
						count = 0;
						if (str[i + 1] == '"')
						{
							word[j] = '"';
							i += 2;
							++j;
							continue;
						}
						if (str[i + 1] == '\\')
						{
							while (str[i] == '\\')
							{
								++count;
								++i;
							}
							if (str[i] == '"')
							{
								if (count % 2 == 0)
								{
									count /= 2;
									for (int k = j; j < k + count; ++j)
									{
										word[j] = '\\';
									}
									break;
								}
								else
								{
									count /= 2;
									for (int k = j; j < k + count; ++j)
									{
										word[j] = '\\';
									}
									word[j] = '"';
									++i;
									++j;
									continue;
								}
							}
							else
							{
								for (int k = j; j < k + count; ++j)
								{
									word[j] = '\\';
								}
							}
							continue;
						}
						word[j] = '\\';
						++i;
						++j;
						continue;
					}
					if (str[i] == '"')
					{
						if (str[i + 1] != '"')
						{
							break;
						}
						++i;
					}
					word[j] = str[i];
					++i;
					++j;
				}
				++i;
				continue;
			}
			word[j] = str[i];
			++i;
			++j;
		}
		fprintf(out, "[%s]\n", word);
		printf("[%s]\n", word);
		memset(word, 0, 200);
		j = 0;
	}
	return 0;
}