#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

char* concat(char* pref, char* suff) 
{
    int i = 0;
    while(suff[i] != '\0')
    {
        pref[i] = suff[i];
        ++i;
    }
    pref[i] = '\0';
    return &pref[i];
}

int main()
{
    char str[1000001];
    char buf[101];
    char* end = str;

    int n = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; ++i)
    {
        scanf("%s", buf);
        end = concat(end, buf);
    }

    printf("%s", str);
}
