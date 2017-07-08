/*
 * recursive.h
 * 
 * A simple interface to two recursively-defined, applicative
 * structures, lists and trees.
 */

#ifndef __RECURSIVE_H__
#define __RECURSIVE_H__

/*
 * lists
 *
 * A well-formed list is either:
 *      the empty list
 *   or an integer followed by a well-formed list.
 *
 * Lists are applicative (functional) data structures---in other
 * words, they are immutable.
 */
 

/*
 * We define lists using the following type declaration.  Don't worry
 * if you don't understand what this means---we haven't covered the
 * syntax for this sort of declaration yet.  For the purposes of this
 * project, just assume that "list_t" is the name of a type that you can
 * use just like "int" or "double".
 */

struct opaque_list;
typedef opaque_list *list_t;

extern bool list_isEmpty(list_t list);
   // EFFECTS: returns true if list is empty, false otherwise

list_t list_make();
   // EFFECTS: returns an empty list.

list_t list_make(int elt, list_t list);
   // EFFECTS: given the list (list) make a new list consisting of
   //          the new element followed by the elements of the
   //          original list. 

extern int list_first(list_t list);
   // REQUIRES: list is not empty
   // EFFECTS: returns the first element of list

extern list_t list_rest(list_t list);
   // REQUIRES: list is not empty
   // EFFECTS: returns the list containing all but the first element of list

extern void list_print(list_t list);
    // MODIFIES: cout
    // EFFECTS: prints list to cout.

/*
 * Trees
 *
 * A well-formed tree is either:
 *      the empty tree
 * or   an integer element with two well-formed trees as "children",
 *        a left "subtree" and a right subtree.
 * 
 * Here is an example of a well-formed tree:
 *
 *                     2
 *                   /   \
 *                  1    MT 
 *                /  \   
 *               MT  MT 
 *
 * This tree has two "internal" nodes (1 and 2), and three "external"
 * nodes.  By our definition, all external nodes are precisely the
 * empty tree.
 */

struct opaque_tree;
typedef opaque_tree *tree_t;

extern bool tree_isEmpty(tree_t tree);
    // EFFECTS: returns true if tree is empty, false otherwise

extern tree_t tree_make();
    // EFFECTS: creates an empty tree.

extern tree_t tree_make(int elt, tree_t left, tree_t right);
    // EFFECTS: creates a new tree, with elt as it's element, left as
    //          its left subtree, and right as its right subtree

extern int tree_elt(tree_t tree);
    // REQUIRES: tree is not empty
    // EFFECTS: returns the element at the top of tree.

extern tree_t tree_left(tree_t tree);
    // REQUIRES: tree is not empty
    // EFFECTS: returns the left subtree of tree

extern tree_t tree_right(tree_t tree);
    // REQUIRES: tree is not empty
    // EFFECTS: returns the right subtree of tree

extern void tree_print(tree_t tree);
    // MODIFIES: cout
    // EFFECTS: prints tree to cout.

#endif /* __RECURSIVE_H__ */
