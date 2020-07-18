#include "binaryTree.h"
#include "huffmanTree.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;


char decode(const string &code, const Node *node, unordered_map<string, char> &dict) {
    auto it = dict.find(code);
    if (it != dict.end()) {
        return it->second;
    }
    auto temp = node;
    for (char c : code) {
        if (c == '0') temp = temp->leftSubtree();
        else temp = temp->rightSubtree();
    }
    char result = temp->getstr().front();
    dict.emplace_hint(it, code, result);
    return result;
}

int main(int argc, char *argv[]) {
    string treeFile = argv[1];
    string binaryFile = argv[2];

    HuffmanTree huffmanTree(treeFile);

    ifstream fin(binaryFile);
    string code;

    unordered_map<string, char> dict;

    while (fin >> code) {
        cout << decode(code, huffmanTree.root, dict);
    }
    return 0;
}
