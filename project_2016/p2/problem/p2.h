#ifndef __P2_H__
#define __P2_H__
#include "recursive.h"

int size(list_t list);
/* 
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/ 

int sum(list_t list);
/* 
// EFFECTS: Returns the sum of each element in "list".
//          Returns zero if "list" is empty.
*/ 

int product(list_t list);
/* 
// EFFECTS: Returns the product of each element in "list".
//          Returns one if "list" is empty.
*/

int accumulate(list_t list, int (*fn)(int, int), int base);
/*
// REQUIRES: "fn" must be associative.
//
// EFFECTS: Returns "base" if "list" is empty.
//          Returns fn(list_first(list), 
//                      accumulate(list_rest(list), fn, base) otherwise.
//
// For example, if you have the following function:
//
//           int add(int x, int y);
//
// Then the following invocation returns the sum of all elements:
//
//           accumulate(list, add, 0);
*/ 

list_t reverse(list_t list);
/*
// EFFECTS: Returns the reverse of "list".
//
// For example: the reverse of ( 3 2 1 ) is ( 1 2 3 )
*/

list_t append(list_t first, list_t second);
/*
// EFFECTS: Returns the list (first second).
//
// For example: append(( 2 4 6 ), ( 1 3 )) gives
// the list ( 2 4 6 1 3 ).
*/ 

list_t filter_odd(list_t list);
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value, 
//          in the order in which they appeared in list.
//
// For example, if you applied filter_odd to the list ( 3 4 1 5 6 )
// you would get the list ( 3 1 5 ).
*/ 

list_t filter_even(list_t list);
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are even in value, 
//          in the order in which they appeared in list.
*/

list_t filter(list_t list, bool (*fn)(int));
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
// For example, if predicate bool odd(int a) returns true if a is odd,
// then the function filter(list, odd) has the same behavior as the
// function filter_odd(list).
*/

list_t insert_list(list_t first, list_t second, unsigned int n);
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
//
//     For example: insert (( 1 2 3 ), ( 4 5 6 ), 2)
//            is  ( 1 2 4 5 6 3 ).
*/

list_t chop(list_t list, unsigned int n);
/*
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
*/

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree);
/*
// EFFECTS: Returns the sum of all elements in "tree". 
//          Returns zero if "tree" is empty.
*/

bool tree_search(tree_t tree, int key);
/*
// EFFECTS: Returns true if and only if there exists any element in
//          "tree" whose value is "key".
*/

int depth(tree_t tree);
/*
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero is "tree" is empty.
//
// For example, the tree
// 
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3        8
//                        / \      / \
//                       6   7
//                      / \ / \
//
// has depth 4.
// The element 4 is on the first layer.
// The elements 2 and 5 are on the second layer.
// The elements 3 and 8 are on the third layer.
// The elements 6 and 7 are on the fourth layer.
//
*/

int tree_min(tree_t tree);
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/

list_t traversal(tree_t tree);
/* 
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints 
//          the "left most" element first, then the second-left-most, 
//          and so on, until the right-most element is printed.
//
//          For any root element, all the elements of its left subtree
//          are considered as on the left of that root element and
//          all the elements of its right subtree are considered as
//          on the right of that root element.
//
// For example, the tree:
// 
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3 
//                        / \
//
// would return the list
//
//       ( 2 3 4 5 )
// 
// An empty tree would print as:
// 
//       ( )
//
*/

bool tree_hasPathSum(tree_t tree, int sum);
/* 
// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
//          path such that adding all elements along the path equals "sum".
//          
// A root-to-leaf path is a sequence of elements in a tree starting
// with the root element and proceeding downward to a leaf (an element
// with no children).
//
// An empty tree has no root-to-leaf path.
//
// For example, the tree:
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
// Given sum = 9, the path 4->5 has the sum 9, so the function
// should return true. If sum = 10, since no path has the sum 10,
// the function should return false.
// 
*/

bool covered_by(tree_t A, tree_t B);
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/       

bool contained_by(tree_t A, tree_t B);
/*
// EFFECTS: Returns true if tree A is covered by tree B
//          or any complete subtree of B.
*/       

tree_t insert_tree(int elt, tree_t tree);
/* 
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted at a leaf such that 
//          the resulting tree is also a sorted binary tree.
//
// For example, inserting 1 into the tree:
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3 
//                        / \
//
// would yield
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                     1   3 
//                    / \ / \
// 
*/

#endif /* __P2_H__ */
