#ifndef P4_HUFFMANTREE_H
#define P4_HUFFMANTREE_H

#include "binaryTree.h"

class HuffmanTree : public BinaryTree {
    // Huffman tree

public:

    HuffmanTree(Node *rootNode = nullptr);
    // REQUIRES: The input rootNode points to a dynamically allocated 
    // 	         node object, if not, it is NULL.
    // MODIFIES: this
    // EFFECTS: Construct a huffman tree with a root node.

    HuffmanTree(const std::string &treefile);
    // MODIFIES: this
    // EFFECTS: Constructs a huffman tree from the treefile. (treefile 
    //          corresponds to the file name.) The treefile saves all the
    //          node information needed for a huffman tree. You do not 
    //          need to understand the details of the implementation of
    //          this function.
    //
    // In a huffman tree, all the leaf nodes contains information of  
    // a character. You can find the encoding for each character just
    // by the path from root node to it. So only the "str" components
    // of leaf nodes need to be save in the treefile (we do not care 
    // about its "num" when doing compression or decompression). For 
    // nodes other than leaf nodes, they contain information about
    // frequencies. So we only care about the "num" components of 
    // those nodes. Thus a huffman tree can be saved in a file like  
    // the following example:
    //
    // 8,
    // a,4,
    // -,-,b,c,
    //
    // which represents the tree
    //
    //           8 
    //         /   \
    //        a     4
    //       / \   / \
    //            b   c
    //           / \ / \
    //
    // Each '-' in the file means there is no node present in that position.
    //

    void printTree();
    // EFFECTS: Prints the huffman tree following the format explained above.
    //          You do not need to understand the details of the implementation 
    //          of this function.
         
};

#endif