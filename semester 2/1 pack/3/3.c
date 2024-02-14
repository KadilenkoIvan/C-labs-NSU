
;

#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main()
{
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	char *str = malloc(200);
	memset(str, 0, 200);
	char *word = malloc(200);
	memset(word, 0, 200);

	int i = 1, j = 0;
	while (fscanf(in, "%c", &str[i]) != -1)
	{
		if (str[i] == ' ' || str[i] == '\n')
		{
			++i;
			continue;
		}

		if (str[i] == '"')
		{
			fscanf(in, "%c", &word[j]);
			while (word[j] != '"')
			{
				++j;
				fscanf(in, "%c", &word[j]);
			}
			word[j] = '\0';
			fprintf(out, "[%s]\n", word);
			j = 0;
			continue;
		}

		word[j] = str[i];
		++j;
		//fscanf(in, "%c", &word[j]);
		while (word[j - 1] != ' ')
		{
			if (fscanf(in, "%c", &word[j]) == -1)
				break;
			++j;
		}
		if (word[j - 1] == ' ' || word[j - 1] == '\n')
			word[j - 1] = '\0';
		else
			word[j] = '\0';
		fprintf(out, "[%s]\n", word);
		j = 0;
	}
	return 0;
}
//   " qwerty "      ""    qwe asd "zxc fgh"       polt    "    " exit
//"v  t"  " qwerty "    e  ""    qwe      asd "zxc fgh"       polt    "    " exit ""