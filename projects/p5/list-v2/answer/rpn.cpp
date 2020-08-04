//
// Created by liu on 27/7/2020.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "dlist.h"

//#include <vector>
//#include <stack>
//#include <unordered_map>

using namespace std;

struct Token {
    union {
        long number;
        char op;
    } value;
    enum {
        INT,
        CHAR
    } type;
};

int main() {
    int precedence[128] = {};
    precedence['('] = 10;
    precedence[')'] = 1;
    precedence['*'] = 3;
    precedence['/'] = 3;
    precedence['+'] = 2;
    precedence['-'] = 2;


    string line;
    getline(cin, line);

    Dlist<Token> rpn;
    Dlist<char> operators;

    istringstream iss(line);
    string token;
    while (iss >> token) {
        char *end;
        auto number = strtol(token.c_str(), &end, 10);
        if (end == token.c_str() + token.length()) {
            rpn.insertBack(new Token{number, Token::INT});
            continue;
        }
        if (token.length() == 1) {
            char op = token[0];
            if (precedence[op] > 0) {
                if (op == '(') {
                    operators.insertBack(new char(op));
                } else if (op == ')') {
                    while (true) {
                        if (operators.isEmpty()) {
                            cout << "ERROR: Parenthesis mismatch" << endl;
                            return 0;
                        }
                        auto op2 = operators.removeBack();
                        if (*op2 != '(') {
                            rpn.insertBack(new Token{*op2, Token::CHAR});
                            delete op2;
                        } else {
                            delete op2;
                            break;
                        }
                    }
//                    while (!operators.isEmpty() && operators.top().first != '(') {
//                        rpn.push_back(Token{operators.top().first, Token::CHAR});
//                        operators.pop();
//                    }
//                    if (operators.empty()) {
//                        cout << "ERROR: Parenthesis mismatch" << endl;
//                        return 0;
//                    }
//                    operators.pop();
                } else {
                    while (!operators.isEmpty()) {
                        auto op2 = operators.removeBack();
                        if (*op2 == '(' || precedence[*op2] < precedence[op]) {
                            operators.insertBack(op2);
                            break;
                        }
                        rpn.insertBack(new Token{*op2, Token::CHAR});
                        delete op2;
                    }
                    operators.insertBack(new char(op));
//                    while (!operators.empty() && operators.top().first != '(' && operators.top().second >= it->second) {
//                        rpn.push_back(Token{operators.top().first, Token::CHAR});
//                        operators.pop();
//                    }
//                    operators.push(*it);
                }
                continue;
            }
        }
        assert(0);
    }
    while (!operators.isEmpty()) {
        auto op2 = operators.removeBack();
        if (*op2 == '(') {
            cout << "ERROR: Parenthesis mismatch" << endl;
            delete op2;
            return 0;
        }
        rpn.insertBack(new Token{*op2, Token::CHAR});
        delete op2;
    }
    
    auto temp = rpn;
    while (!temp.isEmpty()) {
        auto item = temp.removeFront();
        if (item->type == Token::INT) {
            cout << item->value.number << " ";
        } else {
            cout << item->value.op << " ";
        }
        delete item;
    }
    cout << endl;

    Dlist<int> rpnStack;
    if (rpn.isEmpty()) {
        cout << "ERROR: Not enough operands" << endl;
        return 0;
    }

    while (!rpn.isEmpty()) {
        auto item = rpn.removeFront();
        if (item->type == Token::INT) {
            rpnStack.insertBack(new int(item->value.number));
        } else {
            int *b = rpnStack.removeBack();
            if (rpnStack.isEmpty()) {
                cout << "ERROR: Not enough operands" << endl;
                delete b;
                delete item;
                return 0;
            }
            int *a = rpnStack.removeBack();
            if (item->value.op == '/' && *b == 0) {
                cout << "ERROR: Divide by zero" << endl;
                delete a;
                delete b;
                delete item;
                return 0;
            }
            switch (item->value.op) {
                case '+':
                    *a += *b;
                    break;
                case '-':
                    *a -= *b;
                    break;
                case '*':
                    *a *= *b;
                    break;
                case '/':
                    *a /= *b;
                    break;
                default:
                    assert(0);
            }
            delete b;
            rpnStack.insertBack(a);
        }
        delete item;
    }

    auto result = rpnStack.removeFront();
    if (!rpnStack.isEmpty()) {
        cout << "ERROR: Too many operands" << endl;
    } else {
        cout << *result << endl;
    }
    delete result;
    return 0;
}