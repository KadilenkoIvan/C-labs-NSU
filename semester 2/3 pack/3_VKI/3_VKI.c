#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct Node_s
{
    int value;
    struct Node_s* next;
}Node;

Node* front = NULL;

void delete_list()
{
    Node* current = malloc(sizeof(Node));
    Node* current_del = malloc(sizeof(Node));
    current_del = front;
    while (current_del != NULL)
    {
        current = current_del->next;
        free (current_del);
        current_del = current;
    }
    free (current_del);
    front = NULL;
}

void push_front(int value)
{
    Node* current = malloc(sizeof(Node));
    current->value = value;
    current->next = front;

    front = current;
}

void pop_front()
{
    if (front == NULL)
    {
        return;
    }

    if (front->next == NULL)
    {
        //delete front;
        front = NULL;
        return;
    }
    Node* current = malloc(sizeof(Node));
    current = front;
    front = front->next;
    //delete current;
}

//void print()
//{
//    if (front == nullptr)
//    {
//        cout << "empty" << endl;
//        return;
//    }
//    for (Node* current{ front }; current != nullptr; current = current->next)
//        cout << current->value << " ";
//    cout << endl;
//}

int priority_check(char letter)
{
    if (letter == '(')
    {
        return 1;
    }

    if (letter == ')')
    {
        return 2;
    }

    if (letter == '=')
    {
        return 3;
    }

    if (letter == '+' || letter == '-')
    {
        return 4;
    }

    if (letter == '*' || letter == '/')
    {
        return 5;
    }

    return 0;
}

void converter_kalk(char* x)
{
    int a = 0;
    if (priority_check(x[0]) == 0)
    {
        push_front(atoi(x));
    }
    else
    {
        if (front == NULL) return;
        int a = front->value;
        pop_front();
        if (front == NULL)
        {
            push_front(a);
            return;
        }
        int b = front->value;
        pop_front();
        if (x[0] == '+') //тут везде были x == "+" и т.д.
            b += a;
        if (x[0] == '-' && x[1] == '\0')
            b -= a;
        if (x[0] == '*')
            b *= a;
        if (x[0] == '/')
            b /= a;

        push_front(b);
    }
}

int main()
{
    char* value = malloc(500000);
    char* current = malloc(500000);
    char* answer = malloc(500000);
    memset(value, 0, 500000);
    memset(current, 0, 500000);
    memset(answer, 0, 500000);

    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    for (int i = 0; fscanf(in, "%c", &value[i]) != -1; ++i);//считывание

    long long size = strlen(value);
    int j = 0;
    for (int i = 0; i < size; ++i)
    {
        while (value[i] != ' ' && value[i] != '\0')
        {
            if (i < size)
            {
                current[j] = value[i];
                i++;
                j++;
            }
            else
            {
                break;
            }
        }

        converter_kalk(current);
        memset(current, 0, 500000);
        j = 0;
    }

    //cout << front->value;
    printf("%d", front->value);
    delete_list();
}