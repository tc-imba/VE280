#include <iostream>
#include "dlist.h"
#include "dlist.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    Dlist<int> ilist;
    try {
        int *ip = ilist.removeFront();
    } catch (...) {
        cout << "Exception" << endl;
    }
    return 0;
}