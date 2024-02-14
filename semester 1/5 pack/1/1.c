#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct DateTime_s {
    int year, month, day;
    int hours, minutes, seconds;
}DateTime;

DateTime minimum(const DateTime* arr, int cnt)
{
    DateTime minimum = arr[0];
    for (int i = 1; i < cnt; ++i)
    {
        if (arr[i].year < minimum.year)//maybe <=
        {
            minimum = arr[i];
            continue;
        }
        else if (arr[i].year == minimum.year)
        {
            if (arr[i].month < minimum.month)//maybe <=
            {
                minimum = arr[i];
                continue;
            }
            else if (arr[i].month == minimum.month)
            {
                if (arr[i].day < minimum.day)//maybe <=
                {
                    minimum = arr[i];
                    continue;
                }
                else if (arr[i].day == minimum.day)
                {
                    if (arr[i].hours < minimum.hours)//maybe <=
                    {
                        minimum = arr[i];
                        continue;
                    }
                    else if (arr[i].hours == minimum.hours)
                    {
                        if (arr[i].minutes < minimum.minutes)//maybe <=
                        {
                            minimum = arr[i];
                            continue;
                        }
                        else if (arr[i].minutes == minimum.minutes)
                        {
                            if (arr[i].seconds < minimum.seconds)//maybe <=
                            {
                                minimum = arr[i];
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    return minimum;
}

DateTime arr[50000];

int main()
{
    printf("9");
    for (int i = 0; i < 999; ++i)
        printf("9");
    /*int n = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d%d%d%d",&arr[i].year, &arr[i].month, &arr[i].day, &arr[i].hours, &arr[i].minutes, &arr[i].seconds);
    }

    DateTime answer;
    answer = minimum(arr, n);

    printf("%d %d %d %d %d %d", answer.year, answer.month, answer.day, answer.hours, answer.minutes, answer.seconds);*/
}