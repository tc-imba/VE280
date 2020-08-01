//
// Created by liu on 27/7/2020.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include <vector>
#include <stack>
#include <unordered_map>

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
    const unordered_map<char, int> precedence = {
            {'(', 10},
            {')', 0},
            {'*', 3},
            {'/', 3},
            {'+', 2},
            {'-', 2},
    };

    string line;
    getline(cin, line);

    vector<Token> rpn;
    stack<pair<char, int>> operators;

    istringstream iss(line);
    string token;
    while (iss >> token) {
        char *end;
        auto number = strtol(token.c_str(), &end, 10);
        if (end == token.c_str() + token.length()) {
            rpn.push_back(Token{number, Token::INT});
            continue;
        }
        if (token.length() == 1) {
            char op = token[0];
            auto it = precedence.find(op);
            if (it != precedence.end()) {
                if (it->first == '(') {
                    operators.push(*it);
                } else if (it->first == ')') {
                    while (!operators.empty() && operators.top().first != '(') {
                        rpn.push_back(Token{operators.top().first, Token::CHAR});
                        operators.pop();
                    }
                    if (operators.empty()) {
                        cout << "ERROR: Parenthesis mismatch" << endl;
                        return 0;
                    }
                    operators.pop();
                } else {
                    while (!operators.empty() && operators.top().first != '(' && operators.top().second >= it->second) {
                        rpn.push_back(Token{operators.top().first, Token::CHAR});
                        operators.pop();
                    }
                    operators.push(*it);
                }
                continue;
            }
        }
        assert(0);
    }
    while (!operators.empty()) {
        if (operators.top().first == '(') {
            cout << "ERROR: Parenthesis mismatch" << endl;
            return 0;
        }
        rpn.push_back(Token{operators.top().first, Token::CHAR});
        operators.pop();
    }

    for (auto &item : rpn) {
        if (item.type == Token::INT) {
            cout << item.value.number << " ";
        } else {
            cout << item.value.op << " ";
        }
    }
    cout << endl;

    stack<int> rpnStack;
    if (rpn.empty()) {
        cout << "ERROR: Not enough operands" << endl;
        return 0;
    }

    for (auto &item : rpn) {
        if (item.type == Token::INT) {
            rpnStack.push(item.value.number);
        } else {
            if (rpnStack.size() < 2) {
                cout << "ERROR: Not enough operands" << endl;
                return 0;
            }
            int operand = rpnStack.top();
            rpnStack.pop();
            if (item.value.op == '/' && operand == 0) {
                cout << "ERROR: Divide by zero" << endl;
                return 0;
            }
            switch (item.value.op) {
                case '+':
                    rpnStack.top() += operand;
                    break;
                case '-':
                    rpnStack.top() -= operand;
                    break;
                case '*':
                    rpnStack.top() *= operand;
                    break;
                case '/':
                    rpnStack.top() /= operand;
                    break;
                default:
                    assert(0);
            }
        }
    }

    if (rpnStack.size() != 1) {
        cout << "ERROR: Too many operands" << endl;
    } else {
        cout << rpnStack.top() << endl;
    }

    return 0;
}