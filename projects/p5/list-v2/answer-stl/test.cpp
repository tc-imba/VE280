#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <random>
#include <cassert>

#include "dlist.h"

using namespace std;
const int SIZE = 1000;

void compare_lists(list<int> &stlList, Dlist<int> dlist) {
    ostringstream oss1, oss2;
    for (auto num : stlList) {
        oss1 << num << " ";
    }
    while (!dlist.isEmpty()) {
        auto num = dlist.removeFront();
        oss2 << *num << " ";
    }
    if (oss1.str() != oss2.str()) {
        cout << "error: " << endl;
        cout << "  stl: " << oss1.str() << endl;
        cout << "dlist: " << oss2.str() << endl;
        exit(-1);
    }
}

int main(int argc, char *argv[]) {

    list<int> stlList;
    Dlist<int> dlist;

    mt19937 gen(280);
    uniform_int_distribution<> distribution(1, 8);

    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        int a = distribution(gen);
        if (a == 1 || a == 7) {
            // insertFront
            cout << i << " insertFront " << count << endl;
            stlList.emplace_front(count);
            dlist.insertFront(new int(count));
            count++;
        } else if (a == 2 || a == 8) {
            // insertBack
            cout << i << " insertBack " << count << endl;
            stlList.emplace_back(count);
            dlist.insertBack(new int(count));
            count++;
        } else if (a == 3 || a == 4) {
            // removeFront/Back
            if (!stlList.empty()) {
                int num1, *num2;
                if (a == 3) {
                    cout << i << " removeFront " << endl;
                    num1 = stlList.front();
                    stlList.pop_front();
                    num2 = dlist.removeFront();
                } else {
                    cout << i << " removeBack " << endl;
                    num1 = stlList.back();
                    stlList.pop_back();
                    num2 = dlist.removeBack();
                }
                if (*num2 != num1) {
                    compare_lists(stlList, dlist);
                    cout << "error: remove wrong number " << *num2 << ", should be " << num1 << endl;
                    exit(-1);
                }
                delete num2;
            }
        } else if (a == 5) {
            if (i == 29) {
                cout << endl;
            }
            // remove
            if (!stlList.empty()) {
                uniform_int_distribution<> dis2(0, count - 1);
                int remove = dis2(gen);
                cout << i << " remove " << remove << endl;
                auto size = stlList.size();
                stlList.remove(remove);
                auto num1 = new int(remove);
                auto num2 = dlist.remove([](const int *a, const int *b) { return *a == *b; }, num1);
                delete num1;
                if (stlList.size() == size) {
                    if (num2 != nullptr) {
                        compare_lists(stlList, dlist);
                        cout << "error: remove wrong number " << *num2 << ", should be nothing" << endl;
                        exit(-1);
                    }
                } else {
                    if (*num2 != remove) {
                        compare_lists(stlList, dlist);
                        cout << "error: remove wrong number " << *num2 << ", should be " << remove << endl;
                        exit(-1);
                    }
                    delete num2;
                }
            }
        } else if (a == 6) {
            cout << i << " copy " << endl;
            Dlist<int> dlist2(dlist);
            dlist = dlist2;
        }
        compare_lists(stlList, dlist);
    }
    return 0;
}
