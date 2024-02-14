#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

Node* front{ nullptr };

void delete_list()
{
    Node* current;
    Node* current_del;
    current_del = front;
    while (current_del != nullptr)
    {
        current = current_del->next;
        delete current_del;
        current_del = current;
    }
    delete current_del;
    front = nullptr;
}

void push_front(int value)
{
    Node* current = new Node;
    current->value = value;
    current->next = front;

    front = current;
}

void pop_front()
{
    if (front == nullptr)
    {
        return;
    }

    if (front->next == nullptr)
    {
        delete front;
        front = nullptr;
        return;
    }
    Node* current;
    current = front;
    front = front->next;
    delete current;
}

void print()
{
    if (front == nullptr)
    {
        cout << "empty" << endl;
        return;
    }
    for (Node* current{ front }; current != nullptr; current = current->next)
        cout << current->value << " ";
    cout << endl;
}

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

void converter(string x)
{
    int a{ 0 };
    if (priority_check(x[0]) == 0)
    {
        push_front(stoi(x));
    }
    else
    {
        int a = front->value;
        pop_front();
        int b = front->value;
        pop_front();
        if (x == "+")
            b += a;
        if (x == "-")
            b -= a;
        if (x == "*")
            b *= a;
        if (x == "/")
            b /= a;

        push_front(b);
    }
}

int main()
{
    string value{ "" }, current{ "" }, answer{ "" };

    getline(cin, value);

    for (int i{ 0 }; i < value.size(); ++i)
    {
        while (value[i] != ' ' && value[i] != '\0')
        {
            if (i < value.size())
            {
                current += value[i];
                i++;
            }
            else
            {
                break;
            }
        }

        converter(current);
        current = "";
    }

    cout << front->value;
    delete_list();
}
