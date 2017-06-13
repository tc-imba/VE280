//
// Created by tripack on 2017/6/8.
//

#include "recursive.h"
#include "loader.h"
#include "p2.h"

#include <iostream>

#define READ_FROM_CIN(TYPE, VAR) TYPE VAR; cin >> VAR

using namespace std;

int main() {
    for(;;) {
        string buf;
        cin >> buf;
        if (buf == "exit") return 0;
        if (buf == "size") {
            READ_FROM_CIN(list_t, list);
            cout << size(list);
        } else if (buf == "memberOf") {
            READ_FROM_CIN(list_t, list);
            READ_FROM_CIN(int, val);
            cout << memberOf(list, val);
        } else if (buf == "dot") {
            READ_FROM_CIN(list_t, list1);
            READ_FROM_CIN(list_t, list2);
            cout << dot(list1, list2);
        } else if (buf == "isIncreasing") {
            READ_FROM_CIN(list_t, l1);
            cout << isIncreasing(l1);
        } else if (buf == "reverse") {
            READ_FROM_CIN(list_t, list);
            cout << reverse(list);
        } else if (buf == "append") {
            READ_FROM_CIN(list_t, list);
            READ_FROM_CIN(list_t, second);
            cout << append(list, second);
        } else if (buf == "isArithmeticSequence") {
            READ_FROM_CIN(list_t, list);
            cout << isArithmeticSequence(list);
        } else if (buf == "filterOdd") {
            READ_FROM_CIN(list_t, list);
            cout << filter_odd(list);
        } else if (buf == "filter") {
            READ_FROM_CIN(list_t, list);
            cout << filter(list, [](int n) {return n * n / 2 > 15;});
        } else if (buf == "unique") {
            READ_FROM_CIN(list_t, list);
            cout << unique(list);
        } else if (buf == "insert_list") {
            READ_FROM_CIN(list_t, first);
            READ_FROM_CIN(list_t, second);
            READ_FROM_CIN(unsigned int, n);
            cout << insert_list(first, second, n);
        } else if (buf == "chop") {
            READ_FROM_CIN(list_t, list);
            READ_FROM_CIN(unsigned int, n);
            cout << chop(list, n);
        } else if (buf == "tree_sum") {
            READ_FROM_CIN(tree_t, tree);
            cout << tree_sum(tree);
        } else if (buf == "tree_search") {
            READ_FROM_CIN(tree_t, tree);
            READ_FROM_CIN(int, val);
            cout << tree_search(tree, val);
        } else if (buf == "depth") {
            READ_FROM_CIN(tree_t, tree);
            cout << depth(tree);
        } else if (buf == "tree_max") {
            READ_FROM_CIN(tree_t, tree);
            cout << tree_max(tree);
        } else if (buf == "traversal") {
            READ_FROM_CIN(tree_t, tree);
            cout << traversal(tree);
        } else if (buf == "tree_hasMonotonicPath") {
            READ_FROM_CIN(tree_t, tree);
            cout << tree_hasMonotonicPath(tree);
        } else if (buf == "tree_allPathSumGreater") {
            READ_FROM_CIN(tree_t, tree);
            READ_FROM_CIN(int, sum);
            cout << tree_allPathSumGreater(tree, sum);
        } else if (buf == "tree_allPathSumGreater") {
            READ_FROM_CIN(tree_t, tree);
            READ_FROM_CIN(int, sum);
            cout << tree_allPathSumGreater(tree, sum);
        } else if (buf == "covered_by") {
            READ_FROM_CIN(tree_t, treeA);
            READ_FROM_CIN(tree_t, treeB);
            cout << covered_by(treeA, treeB);
        } else if (buf == "contained_by") {
            READ_FROM_CIN(tree_t, treeA);
            READ_FROM_CIN(tree_t, treeB);
            cout << contained_by(treeA, treeB);
        } else if (buf == "insert_tree") {
            READ_FROM_CIN(int, element);
            READ_FROM_CIN(tree_t, tree);
            cout << insert_tree(element, tree);
        } else {
            cerr << "Not a command!" << endl;
            throw -1;
        }
    }
}
