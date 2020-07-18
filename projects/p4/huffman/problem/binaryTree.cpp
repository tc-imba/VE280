#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {
    // TODO: implement this function.
}

Node* Node::leftSubtree() const{
    // TODO: implement this function.  
}

void Node::setleft(Node *n) {
    // TODO: implement this function.  
}

Node* Node::rightSubtree() const{
    // TODO: implement this function.  
}

void Node::setright(Node *n) {
    // TODO: implement this function.  
}

string Node::getstr() const {
    // TODO: implement this function.  
}

int Node::getnum() const {
    // TODO: implement this function.  
}

void Node::incnum() {
    // TODO: implement this function.
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    // TODO: implement this function.
}

BinaryTree::~BinaryTree() {
    // TODO: implement this function.
}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
}

int BinaryTree::sum() const {
    // TODO: implement this function.
}

int BinaryTree::depth() const {
    // TODO: implement this function.
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
}

bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
}
