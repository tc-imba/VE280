#include "huffmanTree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


HuffmanTree::HuffmanTree(Node *rootNode) {
    this->root = rootNode;
}


static Node *filehelper(int pos, int row, vector<vector<string> > &vec) {
    string line;
    if (vec[row][pos][0] >= '0' && vec[row][pos][0] <= '9') {
        // will have child
        Node *left = filehelper(2 * pos, row + 1, vec);
        Node *right = filehelper(2 * pos + 1, row + 1, vec);
        return new Node("", stoi(vec[row][pos]), left, right);
    } else {
        if (vec[row][pos].size() == 2) return new Node("\n", 0);
        return new Node(vec[row][pos], 0);
    }
}

HuffmanTree::HuffmanTree(const string &treefile) {
    // Construct tree from file
    string line;
    vector<vector<string> > vec;
    ifstream ifile;
    ifile.open(treefile);
    while (getline(ifile, line)) {
        stringstream ss(line);
        vector<string> v;
        while (getline(ss, line, ',')) {
            v.push_back(line);
        }
        vec.push_back(v);
    }
    ifile.close();
    if (!vec.empty()) {
        root = filehelper(0, 0, vec);
    }
}

static void printTree_helper(Node *n, int depth, int targetDepth) {
    // Iterative deepening printer
    if (targetDepth > depth) {
        return;
    } else if (targetDepth == depth) {
        if (n->getstr().length() != 1) {
            cout << n->getnum() << ",";
        } else {
            if (n->getstr()=="\n") cout << "\\n,";
            else cout << n->getstr() << ",";
        }
        return;
    } else {
        printTree_helper(n->leftSubtree(), depth - 1, targetDepth);
        printTree_helper(n->rightSubtree(), depth - 1, targetDepth);
    }
}

static void fill_nodes(Node *n, int depth) {
    // Fill the tree to be a full binary tree
    if (depth == 0) return;
    if (n->leftSubtree() == nullptr)
        n->setleft(new Node("-", 0, nullptr, nullptr));
    if (n->rightSubtree() == nullptr)
        n->setright(new Node("-", 0, nullptr, nullptr));
    fill_nodes(n->leftSubtree(), depth - 1);
    fill_nodes(n->rightSubtree(), depth - 1);
}

static Node *copy_node(Node *node) {
    if (!node)
        return nullptr;
    Node *copy = new Node(node->getstr(), node->getnum(), copy_node(node->leftSubtree()), 
                        copy_node(node->rightSubtree()));

    return copy;
}

void HuffmanTree::printTree() {
    Node *cpRoot = copy_node(this->root);
    HuffmanTree cp(cpRoot);
    int depth = this->depth();
    fill_nodes(cp.root, depth - 1);

    // print
    for (int i = depth - 1; i >= 0; i--) {
        printTree_helper(cp.root, depth - 1, i);
        cout << endl;
    }
}