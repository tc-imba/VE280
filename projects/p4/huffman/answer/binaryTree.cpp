#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) :
        str(str), num(num), left(left), right(right) {}

Node::Node(const Node &node) : str(node.str), num(node.num), left(nullptr), right(nullptr) {
    if (node.left) left = new Node(*node.left);
    if (node.right) right = new Node(*node.right);
}

Node::~Node() {
    delete left;
    delete right;
}

Node *Node::leftSubtree() const {
    return left;
}

void Node::setleft(Node *n) {
    left = n;
}

Node *Node::rightSubtree() const {
    return right;
}

void Node::setright(Node *n) {
    right = n;
}

string Node::getstr() const {
    return str;
}

int Node::getnum() const {
    return num;
}

void Node::incnum() {
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    return new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
}

std::string Node::findPath(const Node *node, const std::string &s) {
    if (!node) return "-1";
    if (node->str == s) return "";
    auto str = findPath(node->left, s);
    if (str != "-1") return "0" + str;
    str = findPath(node->right, s);
    if (str != "-1") return "1" + str;
    return "-1";
}

int Node::sum(const Node *node) {
    if (!node) return 0;
    return node->num + sum(node->left) + sum(node->right);
}

int Node::depth(const Node *node) {
    if (!node) return 0;
    return 1 + max(depth(node->left), depth(node->right));
}

void Node::preorder_num(const Node *node) {
    if (!node) return;
    cout << node->num << " ";
    preorder_num(node->left);
    preorder_num(node->right);
}

void Node::inorder_str(const Node *node) {
    if (!node) return;
    inorder_str(node->left);
    cout << node->str << " ";
    inorder_str(node->right);
}

void Node::postorder_num(const Node *node) {
    if (!node) return;
    postorder_num(node->left);
    postorder_num(node->right);
    cout << node->num << " ";
}

bool Node::allPathSumGreater(const Node *node, int sum) {
    if (!node) return true;
    if (!node->left && !node->right) return node->num > sum;
    return allPathSumGreater(node->left, sum - node->num) && allPathSumGreater(node->right, sum - node->num);
}

bool Node::covered_by(const Node *a, const Node *b) {
    if (!a) return true;
    if (!b) return false;
    return a->num == b->num && covered_by(a->left, b->left) && covered_by(a->right, b->right);
}

bool Node::contained_by(const Node *a, const Node *b) {
    if (covered_by(a, b)) return true;
    if (!b) return false;
    return contained_by(a, b->left) || contained_by(a, b->right);
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode) : root(rootNode) {}

BinaryTree::~BinaryTree() {
    delete root;
}

string BinaryTree::findPath(const string &s) const {
    return Node::findPath(root, s);
}

int BinaryTree::sum() const {
    return Node::sum(root);
}

int BinaryTree::depth() const {
    return Node::depth(root);
}

void BinaryTree::preorder_num() const {
    Node::preorder_num(root);
    cout << endl;
}

void BinaryTree::inorder_str() const {
    Node::inorder_str(root);
    cout << endl;
}

void BinaryTree::postorder_num() const {
    Node::postorder_num(root);
    cout << endl;
}

bool BinaryTree::allPathSumGreater(int sum) const {
    return Node::allPathSumGreater(root, sum);
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return Node::covered_by(root, tree.root);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    return Node::contained_by(root, tree.root);
}

BinaryTree BinaryTree::copy() const {
    if (!root) return BinaryTree(nullptr);
    return BinaryTree(new Node(*root));
}
