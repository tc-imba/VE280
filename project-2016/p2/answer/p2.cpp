#include "p2.h"
#ifndef MAX_INT
#define MAX_INT (1 << (8 * sizeof(int) - 1)) - 1
#endif
#ifndef max(a,b)
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min(a,b)
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

int size(list_t list)
{
	return list_isEmpty(list) ? 0 : size(list_rest(list)) + 1;
}

int sum(list_t list)
{
	return accumulate(list, [](int a, int b)->int {return a + b;}, 0);
}

int product(list_t list)
{
	return accumulate(list, [](int a, int b)->int {return a * b;}, 1);
}

int accumulate(list_t list, int(*fn)(int, int), int base)
{
	return list_isEmpty(list) ? base : fn(list_first(list), accumulate(list_rest(list), fn, base));
}

list_t reverse(list_t list)
{
	return list_isEmpty(list) ? list_make() : append(reverse(list_rest(list)), list_make(list_first(list), list_make()));
}

list_t append(list_t first, list_t second)
{
	return list_isEmpty(first) ? second : list_make(list_first(first), append(list_rest(first), second));
}

list_t filter_odd(list_t list)
{
	return filter(list, [](int a)->bool {return a % 2 != 0;});
}

list_t filter_even(list_t list)
{
	return filter(list, [](int a)->bool {return a % 2 == 0;});
}

list_t filter(list_t list, bool(*fn)(int))
{
	return list_isEmpty(list) ? list_make() : fn(list_first(list)) ? list_make(list_first(list), filter(list_rest(list), fn)) : filter(list_rest(list), fn);
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
	return tree_isEmpty(tree) ? 0 : tree_elt(tree) == key || tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
}

int depth(tree_t tree)
{
	return tree_isEmpty(tree) ? 0 : max(depth(tree_left(tree)), depth(tree_right(tree))) + 1;
}

int tree_min(tree_t tree)
{
	return tree_isEmpty(tree) ? MAX_INT : min(tree_elt(tree), min(tree_min(tree_left(tree)), tree_min(tree_right(tree))));
}

list_t traversal(tree_t tree)
{
	return tree_isEmpty(tree) ? list_make() : append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

bool tree_hasPathSum(tree_t tree, int sum)
{
	return tree_isEmpty(tree) ? false : (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)) && tree_elt(tree) == sum) ? true : tree_hasPathSum(tree_left(tree), sum - tree_elt(tree)) || tree_hasPathSum(tree_right(tree), sum - tree_elt(tree));
}

bool covered_by(tree_t A, tree_t B)
{
	return tree_isEmpty(A) ? true : tree_isEmpty(B) ? false : (tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B)));
}

bool contained_by(tree_t A, tree_t B)
{
	return covered_by(A, B) || (tree_isEmpty(B) ? false : (contained_by(A, tree_left(B)) || contained_by(A, tree_right(B))));
}

tree_t insert_tree(int elt, tree_t tree)
{
	return tree_isEmpty(tree) ? tree_make(elt, tree_make(), tree_make()) :tree_make(tree_elt(tree), elt < tree_elt(tree) ? insert_tree(elt, tree_left(tree)) : tree_left(tree), elt < tree_elt(tree) ? tree_right(tree) : insert_tree(elt, tree_right(tree)));
}