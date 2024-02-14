#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int calcLetters(char* iStr, int* oLowerCnt, int* oUpperCnt, int* oDigitsCnt)
{
    int size = strlen(iStr);
    //printf("%d %d %d\n", oLowerCnt, oUpperCnt, oDigitsCnt);
    for (int i = 0; i < size; ++i)
    {
        if (iStr[i] >= 'a' && iStr[i] <= 'z')
            (*oLowerCnt)++;
        else if (iStr[i] >= 'A' && iStr[i] <= 'Z')
            (*oUpperCnt)++;
        else if (iStr[i] >= '0' && iStr[i] <= '9')
            (*oDigitsCnt)++;
    }
    //printf("%d %d %d\n", *oLowerCnt, *oUpperCnt, *oDigitsCnt);
    return size;
}

int main()
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    char iStr[101];
    int oLowerCnt = 0, oUpperCnt = 0, oDigitsCnt = 0, i = 1, j = -1, size = 0;
    while (1)
    {
        do
        {
            j++;
            if (fscanf(in, "%c", &iStr[j]) != 1)
                goto end;
        } while (iStr[j] != '\n');
        iStr[j] = '\0';
        j = -1;
        size = calcLetters(iStr, &oLowerCnt, &oUpperCnt, &oDigitsCnt);
        fprintf(out, "Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", i, size, oLowerCnt + oUpperCnt, oLowerCnt, oUpperCnt, oDigitsCnt);
        oLowerCnt = 0;
        oUpperCnt = 0;
        oDigitsCnt = 0;
        i++;
    }
last:
    iStr[j] = '\0';
    j = 0;
    size = calcLetters(iStr, &oLowerCnt, &oUpperCnt, &oDigitsCnt);
    fprintf(out, "Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", i, size, oLowerCnt + oUpperCnt, oLowerCnt, oUpperCnt, oDigitsCnt);
    oLowerCnt = 0;
    oUpperCnt = 0;
    oDigitsCnt = 0;
    i++;
end:
    fclose(in);
    fclose(out);
}
