#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

struct NodeCompare {
    bool operator()(const Node *left, const Node *right) const {
        if (left->getnum() != right->getnum()) return left->getnum() > right->getnum();
        return left->getstr() > right->getstr();
    }
};


int main(int argc, char *argv[]) {
    string filename;
    bool treeFlag = false;
    if (argc == 2) {
        filename = argv[1];
    } else {
        treeFlag = string(argv[1]) == "-tree";
        filename = argv[2];
    }
    ifstream fin(filename);
    int count[128] = {0};
    char ch;
    while (fin.get(ch)) {
        count[ch]++;
    }

    typedef pair<int, Node *> Pair;
    priority_queue<Node *, vector<Node *>, NodeCompare> pq;

    for (int i = 0; i < 128; i++) {
        if (count[i] > 0) {
            string str;
            str += char(i);
            pq.push(new Node(str, count[i], nullptr, nullptr));
        }
    }

    while (pq.size() > 1) {
        auto right = pq.top();
        pq.pop();
        auto left = pq.top();
        pq.pop();
        pq.push(Node::mergeNodes(left, right));
    }

    HuffmanTree huffmanTree(pq.top());
    if (treeFlag) {
        huffmanTree.printTree();
        fin.close();
        return 0;
    }

    string coding[128];
    for (int i = 0; i < 128; i++) {
        if (count[i] > 0) {
            string str;
            str += char(i);
            coding[i] = huffmanTree.findPath(str);
            if (coding[i] == "-1") {
                assert(0);
            }
        }
    }

//    ofstream fout("binary.txt");
//    cout.rdbuf(fout.rdbuf());
    fin.clear();
    fin.seekg(0);
    while (fin.get(ch)) {
        cout << coding[ch] << " ";
    }
    cout << endl;
    fin.close();
    return 0;
}