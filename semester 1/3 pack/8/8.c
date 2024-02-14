#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

char* string_reverse(char* str)
{
    int buf = 0, size = strlen(str);

    for (int i = 0; i < size/2; ++i)
    {
        buf = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = buf;
    }

    return str;
}

long long int from_notation1_to_ten(char* str, int notation1)
{
    int degree = strlen(str) - 1;
    long long int answer = 0, number = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            number = (int)str[i] - '0';
        }
        else
        {
            number = (int)str[i] - 'a' + 10;
        }
        answer += number * pow(notation1, degree);
        --degree;
    }

    return answer;
}

char* from_ten_to_notation2(long long int num, int notation2)
{
    char answer[100];
    int buf = 0, i = 0;
    while (num / notation2 != 0)
    {
        buf = num % notation2;
        if (buf <= 9)
        {
            answer[i] = (char)buf + '0';
            //printf("%d %c\n",buf, answer[i]);
        }
        else
        {
            answer[i] = 'a' + ((char)buf) - 10;
            //printf("%d %c\n", buf, answer[i]);
        }
        num /= notation2;
        ++i;
    }

    buf = num % notation2;
    if (buf <= 9)
    {
        answer[i] = (char)buf + '0';
        //printf("%d %c\n", buf, answer[i]);
    }
    else
    {
        answer[i] = 'a' + ((char)buf) - 10;
        //printf("%d %c\n", buf, answer[i]);
    }

    answer[i + 1] = '\0';
    //printf("%d %s\n",strlen(answer), answer);

    return string_reverse(answer);
}

int main()
{
    int notation1 = 0, notation2 = 0;
    char* number[31];
    int qwerty;
    scanf("%d%d%s", &notation1, &notation2, &number);
    printf("%s", from_ten_to_notation2(from_notation1_to_ten(number, notation1), notation2));


}
