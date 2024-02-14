#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void lines(int spaces)
{
    printf("+");
    spaces += 2;
    for (int i = 0; i < spaces; ++i)
    {
        printf("-");
    }
}

void spaces(int spaces)
{
    printf("|");
    for (int i = 0; i < spaces; ++i)
    {
        printf(" ");
    }
}

int count(int num)
{
    int count = 0;
    while (num / 10 != 0)
    {
        num /= 10;
        ++count;
    }
    return count+1;
}

int main()
{
    int n = 0;
    scanf("%d", &n);

    int f_spaces = 0, s_spaces = 0, t_spaces = 0;

    int parts[10000];
    int seconds[10000];

    for (int i = 0; i < 10000; ++i)
    {
        parts[i] = 0;
        seconds[i] = 0;
    }

    int buf_1 = 0, buf_2 = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &buf_1, &buf_2);
        parts[buf_1]++;
        seconds[buf_1] += buf_2;
    }
    
    for (int i = 0; i < 10000; ++i)
    {
        if (parts[i] != 0)
        {
            buf_1 = count(i);
            if (f_spaces < buf_1)
                f_spaces = buf_1;

            buf_1 = count(parts[i]);
            if (s_spaces < buf_1)
                s_spaces = buf_1;

            buf_1 = count(seconds[i]);
            if (t_spaces < buf_1)
                t_spaces = buf_1;
        }
    }

    char line[10000];

    lines(f_spaces);
    lines(s_spaces);
    lines(t_spaces);
    printf("+\n");

    for (int i = 0; i < 10000; ++i)
    {
        if (parts[i] != 0)
        {
            spaces(f_spaces - count(i));
            printf(" %d ", i);
            spaces(s_spaces - count(parts[i]));
            printf(" %d ", parts[i]);
            spaces(t_spaces - count(seconds[i]));
            printf(" %d ", seconds[i]);
            printf("|\n");

            lines(f_spaces);
            lines(s_spaces);
            lines(t_spaces);
            printf("+\n");
        }
    }
}
