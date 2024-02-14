#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
// /**//
int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    char current, next;

    if (fscanf(in, "%c", &next) != 1)
        goto end;
    current = next;
    if (fscanf(in, "%c", &next) != 1)
        goto end;
    while (1)
    {
        if (current == '/' && next == '*')
        {
            if (fscanf(in, "%c", &next) != 1)
                goto end;
            current = next;
            if (fscanf(in, "%c", &next) != 1)
                goto end;

            while (!(current == '*' && next == '/'))
            {
                if (current == '\n')
                {
                    fprintf(out, "\n");
                }
                current = next;
                if (fscanf(in, "%c", &next) != 1)
                    if (current == '\n')
                        goto end_p;
                    else
                        goto end;
            }

            current = next;
            if (fscanf(in, "%c", &next) != 1)
                goto end;

            current = next;
            if (fscanf(in, "%c", &next) != 1)
                goto end_p;
        }
        else if (current == '/' && next == '/')
        {
            while (current != '\n')
            {
                current = next;
                if (fscanf(in, "%c", &next) != 1)
                    goto end;
            }
            fprintf(out, "\n");

            current = next;
            if (fscanf(in, "%c", &next) != 1)
                goto end;
        }
        else
        {
            fprintf(out, "%c", current);

            current = next;
            if (fscanf(in, "%c", &next) != 1)
                goto end_p;

        }
    }
end_p:
    fprintf(out, "%c", current);
end:
    fclose(in);
    fclose(out);
}