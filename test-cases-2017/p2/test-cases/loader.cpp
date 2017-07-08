//
// Created by tripack on 2017/6/8.
//

#include "recursive.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using std::string;
using std::vector;

class Exception {};

std::ostream& operator<<(std::ostream& stream, const list_t& list) {
    list_t l = list;
    stream << "( ";
    while (!list_isEmpty(l)) {
        stream << list_first(l) << " ";
        l = list_rest(l);
    }
    return stream << ")";
}

std::istream& operator>>(std::istream& stream, list_t& list) {
    std::string buf;
    stream >> buf;
    if (buf != "(") throw Exception();
    vector<int> numbers;
    while (stream >> buf) {
        if (buf == ")") {
            list = list_make();
            while (!numbers.empty()) {
                list = list_make(numbers.back(), list);
                numbers.pop_back();
            }
            return stream;
        }
        int val = std::stoi(buf);
        numbers.push_back(val);
    }
    throw Exception();
}

std::istream& operator>>(std::istream& stream, tree_t& tree) {
    std::string buf;
    stream >> buf;
    if (buf == "$") {
        tree = tree_make();
        return stream;
    }
    if (buf != "[") throw Exception();
    stream >> buf;
    int val = std::stoi(buf);
    tree_t ltree = tree_make();
    tree_t rtree = tree_make();
    stream >> ltree;
    stream >> rtree;
    stream >> buf;
    if (buf == "]") {
        tree = tree_make(val, ltree, rtree);
        return stream;
    }
    throw Exception();
}

std::ostream &operator<<(std::ostream &stream, const tree_t &tree) {
    if (tree_isEmpty(tree)) {
        stream << "$ ";
        return stream;
    }
    stream << "[ " << tree_elt(tree) << " ";
    stream << tree_left(tree) << "";
    stream << tree_right(tree) << "] ";
    return stream;
}

