#define _CRT_SECURE_NO_WARNINGS
#pragma comment (linker,"/STACK:50000000 ")
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

char* text;                               //весь текст лежит здесь
int pos = 0;                                      //текущая позиция в тексте
char* token;

double ParseAtom();
double ParseExpr();
double ParseMonome();

char* readToken() 
{
    while (isspace(text[pos]))//пропускаем пробельные символы ' ', '\n', '\t', и т.п.
        pos++;                                    //(см. функцию isspace из стандартной библиотеки)

    if (text[pos] == 0 || text[pos] == '\n' || text[pos] == '\0')
    {//если символ нулевой, то это конец текста
        strcpy(token, "");
        return (token);                        //возвращаем токен [eof]
    }

    if (text[pos] == '+' || text[pos] == '-' || text[pos] == '*' || text[pos] == '/' || text[pos] == '(' || text[pos] == ')')
    {//это простой односимвольный токен
        strcpy(token, "");
        token[0] = text[pos];
        token[1] = '\0';
        ++pos;
        return (token);                                                                                             //копируем его в буфер token и возвращаем
    }

    int count = 0;
    int buf = pos;
    while (isdigit(text[buf]))
    {
        ++count;
        ++buf;
    }

    char* new_str = malloc(count + 5);
    memset(new_str, 0, count + 5);
    new_str[count] = '\0';
    int i = 0;                            //остался один случай: целое число
    while (isdigit(text[pos]))                  //токен продолжается, пока идут цифры
    {
        new_str[i] = text[pos];
        ++i;
        ++pos;
    }
    strcpy(token, new_str);
    return token;             //копируем отрезок в буфер token и возвращаем
}

char* peekToken()
{
    int oldPos = pos;
    token = readToken();
    pos = oldPos;
    return token;
}

double ParseExpr() 
{
    double res = ParseMonome(); 
    char oper = 0;// в любом случае выражение начинается с монома
    while (strcmp(peekToken(), "+") == 0 || strcmp(peekToken(), "-") == 0)
    {
        oper = readToken()[0];   //КАВО?           // читаем и запоминаем знак операции (плюс или минус)
        double add = ParseMonome();      // разбираем идущий далее моном, запоминаем его значение
        if (oper == '+')
            res += add;// выполняем над res и add операцию oper, запоминаем в res
        else if (oper == '-')
            res -= add;
    }
    return res;                        // когда выражение закончится, в res будет его значение
}

double ParseMonome()
{
    double res = ParseAtom(); 
    char oper = 0;// в любом случае выражение начинается с монома
    while (strcmp(peekToken(), "*") == 0 || strcmp(peekToken(), "/") == 0)
    {
        oper = readToken()[0];              // читаем и запоминаем знак операции (плюс или минус)
        double add = ParseAtom();      // разбираем идущий далее моном, запоминаем его значение
        if (oper == '*')
            res *= add;// выполняем над res и add операцию oper, запоминаем в res
        else if (oper == '/')
            res /= add;
    }
    return res;
}

double ParseAtom() 
{
    if (strcmp(peekToken(), "(") == 0)
    {                                    // вариант 1: это выражение в скобках
        readToken();                     // не забываем прочитать скобку!
        double res = ParseExpr();        // рекурсивно разбираем выражение
        readToken();                     // не забываем прочитать скобку!
        return res;
    }
    else if (strcmp(peekToken(), "-") == 0)
    {
        readToken();
        return 0 - ParseAtom();
    }
    else
        return atoi(readToken());        // вариант 2: это целое число
}

int main()// скорей всего проблема в унарном минусе, ответ должен быть 5 * 7 /2/2/2 *-7 +-7 +-(8) +(-2) / 1 = -47.625
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    text = malloc(500010);
    token = malloc(500010);
    memset(text, 0, 500010);
    memset(token, 0, 500010);
    for (int i = 0; scanf("%c", &text[i]) != -1; ++i);

    double ans = ParseExpr();
    printf("%.20lf", ans);
}