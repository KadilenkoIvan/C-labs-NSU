#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//tokens: структура, в которую нужно положить результаты
typedef struct Tokens_s
{
    int num; //количество слов в строке
    char** arr; //массив слов (каждый элемент –- строка, т.е. char*)
} Tokens;

//str: строка, в которой нужно искать слова
//delims: все символы-разделители в виде строки
void tokensSplit(Tokens* tokens, const char* str, const char* delims)
{
    int n = strlen(str);
    int symbols_len = strlen(delims);

    if (tokens->arr == NULL)
    {
        int count = 0;
        --n;
        for (int i = 0; i < n; ++i)
        {
            if (cheak(str[i], delims, symbols_len) == 1 && cheak(str[i + 1], delims, symbols_len) == 0)
            {
                ++count;
            }
        }
        if (cheak(str[n], delims, symbols_len) == 1)
            ++count;
        tokens->num = count;
        return;
    }

    char* word = malloc(sizeof(char) * 2000001);
    int j = 0, p = 0;

    for (int i = 0; i < n; ++i)
    {
        if (cheak(str[i], delims, symbols_len) == 1)
        {
            p = 0;
            while (cheak(str[i], delims, symbols_len) == 1 && i < n)
            {
                word[p] = str[i];
                ++p;
                ++i;
            }
            word[p] = '\0';
            tokens->arr[j] = (char*)malloc((p + 1) * sizeof(char));
            strcpy(tokens->arr[j], word);
            ++j;
        }
    }
    free(word);
}

//удаляет все ресурсы внутри tokens
void tokensFree(Tokens* tokens)
{
    int n = tokens->num;
    for (int i = 0; i < n; ++i)
    {
        free(tokens->arr[i]);
    }
    free(tokens->arr);
}

void words_print(Tokens* tokens, FILE* out)
{
    int n = tokens->num;
    fprintf(out, "%d\n", n);
    for (int i = 0; i < n; ++i)
    {
        fprintf(out, "%s\n", tokens->arr[i]);
    }
}

int cheak(char a, const char* symbols, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (a == symbols[i])
            return 0;
    }
    return 1;
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    char* str = malloc(sizeof(char) * 2000001);
    memset(str, '\0', 2000001);
    char symbols[5] = ";:,.";
    symbols[4] = '\0';
    fscanf(in, "%s", str);
    Tokens arr;
    arr.arr = NULL;
    arr.num = 0;

    tokensSplit(&arr, str, symbols);
    arr.arr = (char**)malloc(sizeof(char*) * arr.num);
    tokensSplit(&arr, str, symbols);
    words_print(&arr, out);
    tokensFree(&arr);

    free(str);
    fclose(in);
    fclose(out);
}