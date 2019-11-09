//
// Created by liu on 17-6-5.
//

#include "p2.h"

#ifndef MIN_INT
#define MIN_INT (1 << (8 * sizeof(int) - 1))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

int size(list_t list)
{
    return list_isEmpty(list) ? 0 : size(list_rest(list)) + 1;
}

bool memberOf(list_t list, int val)
{
    return list_isEmpty(list) ? false : (list_first(list) == val || memberOf(list_rest(list), val));
}

int dot(list_t v1, list_t v2)
{
    return (list_isEmpty(v1) || list_isEmpty(v2)) ? 0 : (list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2)));
}

bool isIncreasing(list_t v)
{
    return (list_isEmpty(v) || list_isEmpty(list_rest(v))) ? true : (list_first(v) <= list_first(list_rest(v)) && isIncreasing(list_rest(v)));
}

list_t reverse(list_t list)
{
    return list_isEmpty(list) ? list_make() : append(reverse(list_rest(list)), list_make(list_first(list), list_make()));
}

list_t append(list_t first, list_t second)
{
    return list_isEmpty(first) ? second : list_make(list_first(first), append(list_rest(first), second));
}

bool isArithmeticSequence(list_t v)
{
    return (list_isEmpty(v) || list_isEmpty(list_rest(v)) || list_isEmpty(list_rest(list_rest(v)))) ? true :
           (list_first(v) + list_first(list_rest(list_rest(v))) == 2 * list_first(list_rest(v)) && isArithmeticSequence(list_rest(v)));
}

list_t filter_odd(list_t list)
{
    return filter(list, [](int a)->bool {return a % 2 != 0;});
}

list_t filter(list_t list, bool(*fn)(int))
{
    return list_isEmpty(list) ? list_make() : fn(list_first(list)) ? list_make(list_first(list), filter(list_rest(list), fn)) : filter(list_rest(list), fn);
}

static list_t unique_helper(list_t old, list_t list)
{
    return list_isEmpty(old) ? list :
           (memberOf(list, list_first(old)) ? unique_helper(list_rest(old), list) :
           unique_helper(list_rest(old), list_make(list_first(old), list)));
}

list_t unique(list_t list)
{
    return reverse(unique_helper(list, list_make()));
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
    return append(append(chop(first, size(first) - n), second), reverse(chop(reverse(first), n)));
}

list_t chop(list_t list, unsigned int n)
{
    return n > 0 ? reverse(list_rest(reverse(chop(list, n - 1)))) : list;
}

int tree_sum(tree_t tree)
{
    return tree_isEmpty(tree) ? 0 : tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

bool tree_search(tree_t tree, int key)
{
    return tree_isEmpty(tree) ? false : tree_elt(tree) == key || tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
}

int depth(tree_t tree)
{
    return tree_isEmpty(tree) ? 0 : max(depth(tree_left(tree)), depth(tree_right(tree))) + 1;
}

int tree_max(tree_t tree)
{
    return tree_isEmpty(tree) ? MIN_INT : max(tree_elt(tree), max(tree_max(tree_left(tree)), tree_max(tree_right(tree))));
}

list_t traversal(tree_t tree)
{
    return tree_isEmpty(tree) ? list_make() : append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

static bool tree_hasMonotonicPath_helper(tree_t tree, bool(*fn)(int, int))
{
    return (!tree_isEmpty(tree_left(tree)) ? (fn(tree_elt(tree), tree_elt(tree_left(tree))) && tree_hasMonotonicPath_helper(tree_left(tree), fn)) : true) ||
           (!tree_isEmpty(tree_right(tree)) ? (fn(tree_elt(tree), tree_elt(tree_right(tree))) && tree_hasMonotonicPath_helper(tree_right(tree), fn)) : true);
}

bool tree_hasMonotonicPath(tree_t tree)
{
    return !tree_isEmpty(tree) &&
            (tree_hasMonotonicPath_helper(tree, [](int a, int b)->bool {return a<=b;}) ||
            tree_hasMonotonicPath_helper(tree, [](int a, int b)->bool {return a>=b;}));
}

bool tree_allPathSumGreater(tree_t tree, int sum)
{
    return tree_isEmpty(tree) ||
           ((!tree_isEmpty(tree_left(tree)) && tree_allPathSumGreater(tree_left(tree), sum - tree_elt(tree))) &&
           (!tree_isEmpty(tree_right(tree)) && tree_allPathSumGreater(tree_right(tree), sum - tree_elt(tree))) ||
           (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)) && sum > tree_elt(tree)));
}

bool covered_by(tree_t A, tree_t B)
{
    return tree_isEmpty(A) ? true : (tree_isEmpty(B) ? false :
           (tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B))));
}

bool contained_by(tree_t A, tree_t B)
{
    return covered_by(A, B) || (tree_isEmpty(B) ? false : (contained_by(A, tree_left(B)) || contained_by(A, tree_right(B))));
}

tree_t insert_tree(int elt, tree_t tree)
{
    return tree_isEmpty(tree) ? tree_make(elt, tree_make(), tree_make()) :tree_make(tree_elt(tree), elt < tree_elt(tree) ? insert_tree(elt, tree_left(tree)) : tree_left(tree), elt < tree_elt(tree) ? tree_right(tree) : insert_tree(elt, tree_right(tree)));
}
