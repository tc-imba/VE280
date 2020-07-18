#ifndef P4_BINARYTREE_H
#define P4_BINARYTREE_H

#include <string>

class Node {
    // A node in a binary tree

    std::string str;
    int num;
    Node *left;         // A pointer to the left child of this node.
    // If it does not exist, left should be nullptr
    Node *right;        // A pointer to the right child of this node.
    // If it does not exist, right should be nullptr

public:
    Node(const std::string &str, int num, Node *left = nullptr, Node *right = nullptr);
    // REQUIRES: The input left and right point to a dynamically allocated node object,
    //           if not being NULL.
    // MODIFIES: this
    // EFFECTS: Construct a node with given input values.

    Node(const Node &node);

    ~Node();

    Node *leftSubtree() const;
    // EFFECTS: Return the pointer to the left child of the node.

    void setleft(Node *n);
    // MODIFIES: this
    // EFFECTS: set the left child of the node to be n.

    Node *rightSubtree() const;
    // EFFECTS:  Return the pointer to the right child of the node.

    void setright(Node *n);
    // MODIFIES: this
    // EFFECTS: set the right child of the node to be n.

    std::string getstr() const;
    // EFFECTS:  Return the “str” component of the node.

    int getnum() const;
    // EFFECTS:  Return the “num” component of the node.

    void incnum();
    // MODIFIES: this
    // EFFECTS: increment num by 1

    static Node *mergeNodes(Node *leftNode, Node *rightNode);
    // REQUIRES: leftNode and rightNode points to dynamically allocated node objects.
    // EFFECTS: Returns a pointer to a node with "str" being the result of appending
    //          leftNode->str and rightNode->str, and "num" being leftNode->num +
    //          rightNode->num. Moreover, “left” should be leftNode and “right”
    //          should be rightNode. Also, Please allocate memory for this returned node
    //          object.
    //
    //          For example, if leftNode->str = "a", and rightNode->str = "b", then
    //          the "str" of the merged node is "ab".

    static std::string findPath(const Node *node, const std::string &s);

    static int sum(const Node *node);

    static int depth(const Node *node);

    static void preorder_num(const Node *node);

    static void inorder_str(const Node *node);

    static void postorder_num(const Node *node);

    static bool allPathSumGreater(const Node *node, int sum);

    static bool covered_by(const Node *a, const Node *b);

    static bool contained_by(const Node *a, const Node *b);

};

class BinaryTree {
    // A binary tree object

public:
    Node *root;         // Root node of the binary tree

    BinaryTree(Node *rootNode = nullptr);
    // REQUIRES: The input rootNode points to a dynamically allocated node object,
    //           if not being NULL.
    // MODIFIES: this
    // EFFECTS: Construct a binary tree with a root node.

    ~BinaryTree();
    // MODIFIES: this
    // EFFECTS: Free all the memory allocated for this binary tree.

    std::string findPath(const std::string &s) const;
    // EFFECTS: Return the path from the root node to the node with the string s.
    //          The path is encoded by a string only containing '0' and '1'. Each
    //          character, from left to right, shows whether going left (encoded
    //          by ‘0’) or right (encoded by ‘1’) from a node can lead to the
    //		    target node.
    //
    //          For example, we want to find "g" in the following
    //          tree (only the "str" components are shown):
    //
    //                          "a"
    //                         /   \
    //                        /      \
    //                      "b"      "c"
    //                      / \      / \
    //                        "d"      "e"
    //                        / \      / \
    //                      "f" "g"
    //                      / \ / \
    //
    //          The returned string should be "011". (Go left from "a", then go right from
    //          "b", and finally go right from "d" can lead us to "g".)
    //
    //          If s is in root node, then return an empty string.
    //          If s is not in the tree, then return "-1".
    //          You can assume that the "str" components of all the nodes are unique in a
    //          tree.

    int sum() const;
    // EFFECTS: Returns the sum of "num" values of all nodes in the tree. If the tree is
    //          empty, return 0.

    int depth() const;
    // EFFECTS: Returns the depth of the tree, which equals the number of layers of nodes
    //          in the tree. Returns zero if the tree is empty.
    //
    // For example, the tree
    //
    //                           a
    //                         /   \
    //                        /      \
    //                       b        c
    //                      / \      / \
    //                         d        e
    //                        / \      / \
    //                       f   g
    //                      / \ / \
    //
    // has depth 4.
    // The node a is on the first layer.
    // The nodes b and c are on the second layer.
    // The nodes d and e are on the third layer.
    // The nodes f and g are on the fourth layer.

    void preorder_num() const;
    // EFFECTS: Prints the "num" component of each node using a pre-order traversal.
    //          Seperate each "num" with a space. A pre-order traversal prints the
    //          current node first, then recursively visit its left subtree, and then
    //          recursively visit its right subtree and so on, until the right-most
    //          element is printed.
    //
    //          For any node, all the elements of its left subtree
    //          are considered as on the left of that node and
    //          all the elements of its right subtree are considered as
    //          on the right of that node.
    //
    //          For example, the tree:
    //
    //                           4
    //                         /   \
    //                        /     \
    //                       2       5
    //                      / \
    //                     7   3
    //                        / \
    //                       8   9
    //
    //          would print 4 2 7 3 8 9 5
    //
    //          An empty tree would print nothing.

    void inorder_str() const;
    // EFFECTS: Prints the "str" component of each node using an in-order traversal.
    //          Separate each "str" with a space. An in-order traversal prints the
    //          "left most" element first, then the second-left-most, and so on,
    //          until the right-most element is printed.
    //
    //          For any node, all the elements of its left subtree
    //          are considered as on the left of that node and
    //          all the elements of its right subtree are considered as
    //          on the right of that node.
    //
    //          For example, the tree:
    //
    //                           a
    //                         /   \
    //                        /     \
    //                       bb     ddd
    //                      /  \
    //                     e    c
    //
    //          would print e bb c a ddd
    //
    //          An empty tree would print nothing.

    void postorder_num() const;
    // EFFECTS: Prints the "num" component of each node using a post-order traversal.
    //          Seperate each "num" with a space. A post-order traversal recursively
    //          visit its left subtree, and then recursively visit its right subtree
    //          and then print the current node.
    //
    //          For any node, all the elements of its left subtree
    //          are considered as on the left of that node and
    //          all the elements of its right subtree are considered as
    //          on the right of that node.
    //
    //          For example, the tree:
    //
    //                           4
    //                         /   \
    //                        /     \
    //                       2       5
    //                      / \
    //                     7   3
    //                        / \
    //                       8   9
    //
    //          would print 7 8 9 3 2 5 4
    //
    //          An empty tree would print nothing.

    bool allPathSumGreater(int sum) const;
    // REQUIRES: The tree is not empty
    //
    // EFFECTS: Returns true if and only if for each root-to-leaf path of the tree,
    //          the sum of "num" of all nodes along the path is greater than "sum".
    //
    //          A root-to-leaf path is a sequence of nodes in a tree starting with
    //          the root element and proceeding downward to a leaf (an element with
    //          no children).
    //
    // For example, the tree (only the "num" components are shown):
    //
    //                           4
    //                         /   \
    //                        /     \
    //                       1       5
    //                      / \     / \
    //                     3   6
    //                    / \ / \
    //
    // has three root-to-leaf paths: 4->1->3, 4->1->6 and 4->5.
    // Given the input sum = 9, the path 4->5 has the sum 9, so the function
    // should return false. If the input sum = 7, since all paths have the sums
    // greater than 7, the function should return true.

    bool covered_by(const BinaryTree &tree) const;
    // EFFECTS: Returns true if this tree is covered by the input binary tree "tree".
    //          (only consider the "num" component)

    bool contained_by(const BinaryTree &tree) const;
    // EFFECTS: Returns true if this tree is contained by the input binary tree "tree".
    //          (only consider the "num" component)

    BinaryTree copy() const;
    // EFFECTS: Returns a copy of this tree. Hint: use deep copy.
};


#endif