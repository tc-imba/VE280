//
// Created by liu on 16-7-19.
//

#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const char op[] = "q+-*/ndrpca";

void two(char c, Dlist<int> *stack)
{
    int *a, *b;
    try
    {
        a = stack->removeBack();
    }
    catch (emptyList)
    {
        throw;
    }
    try
    {
        b = stack->removeBack();
    }
    catch (emptyList)
    {
        stack->insertBack(a);
        throw;
    }
    switch (c)
    {
    case '+':
        *b = *b + *a;
        break;
    case '-':
        *b = *b - *a;
        break;
    case '*':
        *b = *b * *a;
        break;
    case '/':
        if (*a != 0)
        {
            *b = *b / *a;
        }
        else
        {
            cout << "Divide by zero\n";
            return;
        }
        break;
    case 'r':
        stack->insertBack(a);
        break;
    default:
        break;
    }
    stack->insertBack(b);
}

void one(char c, Dlist<int> *stack)
{
    int *a;
    try
    {
        a = stack->removeBack();
    }
    catch (emptyList)
    {
        throw;
    }
    switch (c)
    {
    case 'n':
        *a *= 1;
        break;
    case 'd':
    {
        auto b = new int(*a);
        stack->insertBack(b);
        break;
    }
    case 'p':
        cout << *a << endl;
        break;
    default:
        break;
    }
    stack->insertBack(a);
}

void clear(Dlist<int> *stack)
{
    try
    {
        while (true)
        {
            stack->removeBack();
        }
    }
    catch (emptyList)
    { }
}

void print(const Dlist<int> *stack)
{
    auto temp = new Dlist<int>(*stack);
    try
    {
        while (true)
        {
            cout << temp->removeBack() << " ";
        }
    }
    catch (emptyList)
    {
        cout << endl;
    }
}

bool input(string cmd, Dlist<int> *stack)
{
    if (cmd.length() == 1)
    {
        try
        {
            switch (cmd[0])
            {
            case 'q':
                return false;
            case '+':
            case '-':
            case '*':
            case '/':
            case 'r':
                two(cmd[0], stack);
                return true;
            case 'n':
            case 'd':
            case 'p':
                one(cmd[0], stack);
                return true;
            case 'c':
                clear(stack);
                return true;
            case 'a':
                print(stack);
                return true;
            default:
                if (cmd[0] < '0' || cmd[0] > '9')
                {
                    cout << "Bad input\n";
                    return true;
                }
            }
        }
        catch (emptyList)
        {
            cout << "Not enough operands\n";
            return true;
        }
    }

    int sym = 1;
    if (cmd[0] == '-')
    {
        sym = -1;
        cmd = cmd.substr(1);
        if (cmd.length() < 1)
        {
            cout << "Bad input\n";
            return true;
        }
    }
    int num = 0;
    for (int i = 0; i < cmd.length(); i++)
    {
        if (cmd[i] >= '0' && cmd[i] <= '9')
        {
            num *= 10;
            num += cmd[i] - '0';
        }
        else
        {
            cout << "Bad input\n";
            return true;
        }
    }
    num *= sym;
    stack->insertBack(new int(num));
    return true;
}

int main()
{
    string str;
    auto *stack = new Dlist<int>;
    do
    {
        cin >> str;
    }
    while (input(str, stack));
    delete stack;
    return 0;
}