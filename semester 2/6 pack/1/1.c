//#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

FILE* in;
FILE* out;

int* col, * hasV, * hasS, * hasD;

void Rec(int r, int n, int m, char** field)
{
    if (r == m)
    {
        fprintf(out, "YES\n");
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (j == col[i])
                {
                    fprintf(out, "X");
                }
                else
                {
                    fprintf(out, ".");
                }
            }
            fprintf(out, "\n");
        }
        exit(0);
        //return;
    }
    for (int c = 0; c < n; ++c)
    {
        if (hasV[c] || hasS[r + c] || hasD[r - c] || field[r][c] == '.')
            continue;

        col[r] = c;

        hasV[c] = hasS[r + c] = hasD[r - c] = 1;
        Rec(r + 1, n, m, field);
        hasV[c] = hasS[r + c] = hasD[r - c] = 0;
        col[r] = c;
    }
}

int main()
{
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    int n = 0, m = 0;
    fscanf(in, "%d %d", &m, &n);

    char** field = malloc(m * sizeof(char*));
    for (int i = 0; i < m; ++i)
    {
        field[i] = malloc(n + 1);
        fscanf(in, "%s", field[i]);
        //printf("%s\n", field[i]);
    }

    col = malloc(sizeof(int) * n);
    memset(col, 0, sizeof(int) * n);

    hasV = malloc(sizeof(int) * (n));
    hasS = malloc(sizeof(int) * (2 * n));
    int* buf_hasD = malloc(sizeof(int) * (3 * n + 2));
    memset(buf_hasD, 0, sizeof(int) * (3 * n + 2));
    hasD = buf_hasD + n + n / 2;
    memset(hasV, 0, sizeof(int) * n);
    memset(hasS, 0, sizeof(int) * (2 * n));

    Rec(0, n, m, field);

    fprintf(out, "NO");
}