#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char value;
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

string converter(char x)
{
    string answer{ "" };
    if (x == ' ')
        return "";

    if (priority_check(x) == 0)
    {
        answer += x;
        answer += ' ';
        return answer;
    }

    if (x == '(')
    {
        push_front(x);
        return answer;
    }

    if (x == ')')
    {
        while (front->value != '(')
        {
            answer += front->value;
            answer += ' ';
            pop_front();
        }
        pop_front();
        return answer;
    }

    if (x == '+' || x == '-' || x == '*' || x == '/')
    {
        while (front != nullptr && priority_check(front->value) >= priority_check(x))
        {
            answer += front->value;
            //answer += ' ';
            pop_front();
        }
        push_front(x);
        push_front(' ');
        return answer;
    }

    answer += x;
    answer += ' ';
    return answer;
}

int main()
{
    string value{ "" }, answer{ "" };

    getline(cin, value);

    for (int i{ 0 }; i < value.size(); ++i)
    {
        answer += converter(value[i]);
    }

    while (front != nullptr)
    {
        answer += front->value;
        pop_front();
    }

    cout << answer;
    delete_list();
}
