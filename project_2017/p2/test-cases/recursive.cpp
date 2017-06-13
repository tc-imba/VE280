#include <iostream>
#include <cassert>
#include "recursive.h"

using namespace std;

// Implementation of the list ADT 
const unsigned int  list_node_id = 0x11341134;
const unsigned int  list_empty_id = 0x22452245;

struct list_node {
    unsigned int      ln_id;    // Are we really a list_node?
    int               ln_elt;   // This element
    struct list_node *ln_rest;  // rest of this list, null for empty node
} list_node_t;


static struct list_node *
list_checkValid(list_t list)
    // MODIFIES: cerr
    // EFFECTS: assert if lnp does not appear to be a valid list.
    //          writing an appropriate error message to cerr.
{
    struct list_node *lnp = (struct list_node *)list.toPtr();

    if ((lnp->ln_id != list_node_id) && (lnp->ln_id != list_empty_id)) {
        cerr << "Error: user passed invalid list\n";
        assert(0);
    }

    return lnp;
}

static void
list_checkNonEmpty(list_t list)
    // MODIFIES: cerr
    // EFFECTS: assert if lnp is an empty list, 
    //          writing an appropriate error message to cerr.
{
    if (list_isEmpty(list)) {
        cerr << "error: user passed empty list where non-empty requried\n";
        assert(0);
    }
}

static void
not_allocated()
{
    cerr << "Your test case is too large for this machine\n";
    cerr << "Try using a smaller test case\n";
    assert(0);
}

bool
list_isEmpty(list_t list)
{
    struct list_node *lnp = list_checkValid(list);
    return (lnp->ln_id == list_empty_id);
}

list_t
list_make()
{
    struct list_node *newp = 0; 

    try {
        newp = new struct list_node;
    } catch (bad_alloc a) {
        not_allocated();
    }

    newp->ln_id = list_empty_id;
    newp->ln_rest = NULL;
    
    return (list_t)(newp);
}

list_t
list_make(int elt, list_t list) 
{
    struct list_node *newp = 0; 
    struct list_node *restp = list_checkValid(list);

    try {
        newp = new struct list_node;
    } catch (bad_alloc a) {
        not_allocated();
    }

    newp->ln_id = list_node_id;
    newp->ln_elt = elt;
    newp->ln_rest = restp;
    
    return list_t(newp);
}

int
list_first(list_t list) 
{
    list_checkNonEmpty(list);
    struct list_node *lnp = list_checkValid(list);
    return lnp->ln_elt;
}

list_t
list_rest(list_t list) 
{
    list_checkNonEmpty(list);
    struct list_node *lnp = list_checkValid(list);
    return list_t(lnp->ln_rest);
}

static void
list_print_helper(list_t list)
    // MODIFIES: cout
    // EFFECTS: prints list contents to cout, with no parens
{
    if (list_isEmpty(list)) {
        return;
    } else {
        cout << list_first(list) << " ";
        list_print_helper(list_rest(list));
    }
}

void
list_print(list_t list)
{
    cout << "( ";
    list_print_helper(list);
    cout << ")";
}

/**************************************************/

// Implementation of the tree ADT
const unsigned int  tree_node_id = 0x45ee45ee;
const unsigned int  tree_empty_id = 0x56ff56ff;

struct tree_node {
    unsigned int       tn_id;    // Are we really a tree_node?
    int                tn_elt;   // This element
    struct tree_node  *tn_left;  // left subtree
    struct tree_node  *tn_right; // right subtree
};

static struct tree_node *
tree_checkValid(tree_t tree)
    // MODIFIES: cerr
    // EFFECTS: assert if tnp does not appear to be a valid tree, 
    //          writing an appropriate error message to cerr.
{
    struct tree_node *tnp = (struct tree_node *)tree.toPtr();

    if ((tnp->tn_id != tree_node_id) && (tnp->tn_id != tree_empty_id)) {
        cerr << "Error: user passed invalid tree\n";
        assert(0);
    }
    return tnp;
}

static void
tree_checkNonEmpty(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        cerr << "Error: user passed empty tree\n";
        assert(0);
    }
}

bool
tree_isEmpty(tree_t tree)
{
    struct tree_node *tnp = tree_checkValid(tree);
    return (tnp->tn_id == tree_empty_id);
}

tree_t
tree_make()
{
    struct tree_node *tnp = 0;

    try {
        tnp = new struct tree_node;
    } catch (bad_alloc a) {
        not_allocated();
    }

    tnp->tn_id = tree_empty_id;
    tnp->tn_left = NULL;
    tnp->tn_right = NULL;

    return (tree_t)(tnp);
}

tree_t
tree_make(int elt, tree_t left, tree_t right)
{
    struct tree_node *tnp = 0;

    try {
        tnp = new struct tree_node;
    } catch (bad_alloc a) {
        not_allocated();
    }

    if (!tree_isEmpty(left)) {
        tree_checkValid(left);
    }
    if (!tree_isEmpty(right)) {
        tree_checkValid(right);
    }

    tnp->tn_id = tree_node_id;
    tnp->tn_elt = elt;
    tnp->tn_left = (struct tree_node *)left.toPtr();
    tnp->tn_right = (struct tree_node *)right.toPtr();

    return (tree_t)(tnp);
}

int
tree_elt(tree_t tree)
{
    tree_checkNonEmpty(tree);
    struct tree_node *tnp = tree_checkValid(tree);
    return tnp->tn_elt;
}

tree_t
tree_left(tree_t tree)
{
    tree_checkNonEmpty(tree);
    struct tree_node *tnp = tree_checkValid(tree);
    return (tree_t)(tnp->tn_left);
}

tree_t
tree_right(tree_t tree)
{
    tree_checkNonEmpty(tree);
    struct tree_node *tnp = tree_checkValid(tree);
    return (tree_t)(tnp->tn_right);
}

static void
print_spaces(int spaces)
    // MODIFIES: cout
    // EFFECTS: prints n spaces
{
    while (spaces--) {
        cout << "  ";
    }
}

static void
tree_print_internal_old(tree_t tree, int spaces)
    // MODIFIES: cout
    // EFFECTS: prints tree contents recursively, with newlines 
    //          for each node, with each level indented
{
    print_spaces(spaces);
    if (tree_isEmpty(tree)) {
        cout << "( )\n";
    } else {
        cout << "(" << tree_elt(tree) << "\n";
        tree_print_internal_old(tree_left(tree), spaces+1);
        tree_print_internal_old(tree_right(tree), spaces+1);
        print_spaces(spaces);
        cout << " )\n";
    }
}

static void
tree_print_internal(tree_t tree, int spaces)
    // MODIFIES: cout
    // EFFECTS: prints tree contents recursively, with newlines 
    //          for each node, with each level indented
{
    if(tree_isEmpty(tree))
        return;
    else
    {
        tree_print_internal(tree_left(tree), spaces+2);
        print_spaces(spaces+1);
        cout << "/" << endl;
        print_spaces(spaces);
        cout << tree_elt(tree) << endl;
        print_spaces(spaces+1);
        cout << "\\" << endl;
        tree_print_internal(tree_right(tree), spaces+2);
    }
}

void
tree_print(tree_t tree)
{
    //tree_print_internal_old(tree, 0);
    tree_print_internal(tree, 0);
}
    
