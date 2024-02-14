#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    char letter;
    int cheak[256] = { 0 };

    while (fscanf(in,"%c", &letter) == 1)
    {
        if (letter != '\n')
            ++cheak[letter];
    }

    for (int i = 0; i < 256; ++i)
    {
        if (cheak[i] != 0)
        {
            fprintf(out,"%c ", i);
            for (int j = 0; j < cheak[i]; ++j)
            {
                fprintf(out, "#");
            }
            fprintf(out, "\n");
        }
    }
    fclose(in);
    fclose(out);
}
