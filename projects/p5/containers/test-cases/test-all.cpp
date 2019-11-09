#include <iostream>
#include "dlist.h"
#include "dlist.cpp"

using namespace std;

void test_copy(Dlist<int> l)
{
    int *ip = new int(1);
    l.insertFront(ip);
}

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);

    // Now ilist should be (1)

    // test removing from a list of size one.
    ip = ilist.removeFront();
    // if(*ip != 1)
    //     result = -1;
    cout << *ip << endl;
    delete ip;

    if(!ilist.isEmpty()) {
        cout << "Not Empty" << endl;
    } else {
        cout << "Empty" << endl;
    }

    // Now ilist should be ()

    ip = new int(4);
    ilist.insertFront(ip);
    
    // Now ilist should be (4)

    ip = new int(5);
    ilist.insertBack(ip);

    // Now ilist should be (4 5)

    ip = new int(3);
    ilist.insertFront(ip);

    // Now ilist should be (3 4 5)

    ip = new int(2);
    ilist.insertFront(ip);

    // Now ilist should be (2 3 4 5)

    ip = new int(6);
    ilist.insertBack(ip);

    // Now ilist should be (2 3 4 5 6)

    ip = new int(7);
    ilist.insertBack(ip);

    // Now ilist should be (2 3 4 5 6 7)

    ip = ilist.removeFront();
    cout << *ip << endl;
    delete ip;

    if(ilist.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    // Now ilist should be (3 4 5 6 7)

    ip = ilist.removeBack();
    cout << *ip << endl;
    delete ip;

    if(ilist.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    // Now ilist should be (3 4 5 6)

    ip = new int(7);
    ilist.insertBack(ip);

    // Now ilist should be (3 4 5 6 7)

    ip = ilist.removeFront();
    cout << *ip << endl;
    delete ip;

    if(ilist.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    // Now ilist should be (4 5 6 7)

    ip = ilist.removeFront();
    cout << *ip << endl;
    delete ip;

    if(ilist.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    // Now ilist should be (5 6 7)

    ip = ilist.removeBack();
    cout << *ip << endl;
    delete ip;

    if(ilist.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    // Now ilist should be (5 6)

    ip = ilist.removeBack();
    cout << *ip << endl;
    delete ip;

    if(ilist.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    // Now ilist should be (5)

    ip = ilist.removeBack();
    cout << *ip << endl;
    delete ip;

    if(!ilist.isEmpty()){
        cout << "Not Empty" << endl;
    } else {
        cout << "Empty" << endl;
    }

    // Now ilist should be ()

    ip = new int(4);
    ilist.insertFront(ip);
    
    // Now ilist should be (4)

    ip = new int(5);
    ilist.insertBack(ip);

    // Now ilist should be (4 5)

    ip = new int(3);
    ilist.insertFront(ip);

    // Now ilist should be (3 4 5)

    test_copy(ilist);
    Dlist<int> ilist_copy(ilist);

    ip = ilist_copy.removeBack();
    cout << *ip << endl;
    delete ip;

    if(ilist_copy.isEmpty()){
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }

    Dlist<int> ilist_assign;
    ilist_assign = ilist;
    Dlist<int> ilist_assign2;
    ilist_assign2 = ilist;

    ilist_copy = ilist_assign;

    ip = ilist_assign.removeBack();
    cout << *ip << endl;
    delete ip;
    ip = ilist_assign.removeBack();
    cout << *ip << endl;
    delete ip;
    ip = ilist_assign.removeBack();
    cout << *ip << endl;
    delete ip;

    ip = ilist_assign2.removeBack();
    cout << *ip << endl;
    delete ip;
    ip = ilist_assign2.removeBack();
    cout << *ip << endl;
    delete ip;
    ip = ilist_assign2.removeBack();
    cout << *ip << endl;
    delete ip;
    return 0;
}
