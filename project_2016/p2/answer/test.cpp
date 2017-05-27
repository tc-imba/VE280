#include <iostream>
#include <assert.h>
#include "test.h"
#include "p2.h"

void Tester::print(const char* funcName) const
{
	std::cout << "Test of function \"" << funcName << "\" passed." << std::endl;
}

listTester::listTester()
{
	this->empty = list_make();
	this->one = list_make(1, empty);
	this->several = list_make();
	for (int i = 20;i >= -15;i--)
	{
		if (i != 0)
		{
			this->several = list_make(i, this->several);
		}
	}
}

bool listTester::equal(const list_t &l1, const list_t &l2)
{
	if (list_isEmpty(l1) && list_isEmpty(l2))
	{
		return true;
	}
	else if (list_isEmpty(l1) || list_isEmpty(l2))
	{
		return false;
	}
	else if (list_first(l1) != list_first(l2))
	{
		return false;
	}
	else
	{
		return equal(list_rest(l1), list_rest(l2));
	}
}
void listTester::testSize() const
{
	assert(size(this->empty) == 0);
	assert(size(this->one) == 1);
	assert(size(this->several) == 35);
	this->print("size");
}

void listTester::testSum() const
{
	assert(sum(this->empty) == 0);
	assert(sum(this->one) == 1);
	assert(sum(this->several) == 90);
	this->print("sum");
}

void listTester::testProduct() const
{
	assert(product(this->empty) == 1);
	assert(product(this->one) == 1);
	assert(product(this->several) == 536870912);
	this->print("product");
}

void listTester::testAccumulate() const
{
	auto f1 = [](int a, int b)->int {return a + b;};
	auto f2 = [](int a, int b)->int {return a * b;};
	assert(accumulate(this->empty, f1, 0) == 0);
	assert(accumulate(this->one, f1, 0) == 1);
	assert(accumulate(this->several, f1, 0) == 90);
	assert(accumulate(this->empty, f2, 1) == 1);
	assert(accumulate(this->one, f2, 1) == 1);
	assert(accumulate(this->several, f2, 1) == 536870912);
	this->print("accumulate");
}

void listTester::testReverse() const
{
	assert(this->equal(reverse(this->empty), this->empty));
	assert(this->equal(reverse(this->one), this->one));
	auto several_new = list_make();
	for (int i = -15;i <= 20;i++)
	{
		if (i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(reverse(this->several), several_new));
	this->print("reverse");
}

void listTester::testAppend() const
{
	assert(this->equal(append(this->empty, this->empty), this->empty));
	assert(this->equal(append(this->empty, this->one), this->one));
	assert(this->equal(append(this->one, this->empty), this->one));
	assert(this->equal(append(this->one, this->one), list_make(1, this->one)));
	assert(this->equal(append(this->empty, this->several), this->several));
	assert(this->equal(append(this->one, this->several), list_make(1, this->several)));
	auto several_new = list_make();
	for (int j = 0;j < 3;j++)
	{
		for (int i = 20;i >= -15;i--)
		{
			if (i != 0)
			{
				several_new = list_make(i, several_new);
			}
		}
	}
	assert(this->equal(append(this->several, append(this->several, this->several)), several_new));
	this->print("append");
}

void listTester::testFilterOdd() const
{
	assert(this->equal(filter_odd(this->empty), this->empty));
	assert(this->equal(filter_odd(this->one), this->one));
	auto several_new = list_make();
	for (int i = 20;i >= -15;i--)
	{
		if ((i + 1000) % 2 == 1)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(filter_odd(this->several), several_new));
	this->print("filter_odd");
}

void listTester::testFilterEven() const
{
	assert(this->equal(filter_even(this->empty), this->empty));
	assert(this->equal(filter_even(this->one), this->empty));
	auto several_new = list_make();
	for (int i = 20;i >= -15;i--)
	{
		if ((i + 1000) % 2 == 0 && i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(filter_even(this->several), several_new));
	this->print("filter_even");
}

void listTester::testFilter() const
{
	auto f1 = [](int a)->bool {return a % 2 != 0;};
	auto f2 = [](int a)->bool {return a % 2 == 0;};
	assert(this->equal(filter(this->empty, f1), this->empty));
	assert(this->equal(filter(this->empty, f2), this->empty));
	assert(this->equal(filter(this->one, f1), this->one));
	assert(this->equal(filter(this->one, f2), this->empty));
	auto several_new = list_make();
	for (int i = 20;i >= -15;i--)
	{
		if ((i + 1000) % 2 == 1)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(filter(this->several, f1), several_new));
	several_new = list_make();
	for (int i = 20;i >= -15;i--)
	{
		if ((i + 1000) % 2 == 0 && i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(filter(this->several, f2), several_new));
	this->print("filter");
}

void listTester::testInsertList() const
{
	assert(this->equal(insert_list(this->empty, this->empty, 0), this->empty));
	assert(this->equal(insert_list(this->empty, this->one, 0), this->one));
	assert(this->equal(insert_list(this->one, this->empty, 0), this->one));
	assert(this->equal(insert_list(this->one, this->empty, 1), this->one));
	assert(this->equal(insert_list(this->one, this->one, 0), list_make(1, this->one)));
	assert(this->equal(insert_list(this->one, this->one, 1), list_make(1, this->one)));
	assert(this->equal(insert_list(this->empty, this->several, 0), this->several));
	assert(this->equal(insert_list(this->one, this->several, 0), append(this->several, this->one)));
	assert(this->equal(insert_list(this->one, this->several, 1), list_make(1, this->several)));
	auto several_new = list_make();
	for (int i = 20;i >= -5;i--)
	{
		if (i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	for (int i = 20;i >= -15;i--)
	{
		if (i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	for (int i = -6;i >= -15;i--)
	{
		if (i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(insert_list(this->several, this->several, 10), several_new));
	this->print("insert_list");
}

void listTester::testChop() const
{
	assert(this->equal(chop(this->empty, 0), this->empty));
	assert(this->equal(chop(this->one, 0) , this->one));
	assert(this->equal(chop(this->one, 1) ,this->empty));
	assert(this->equal(chop(this->several, 0), this->several));
	auto several_new = list_make();
	for (int i = 10;i >= -15;i--)
	{
		if (i != 0)
		{
			several_new = list_make(i, several_new);
		}
	}
	assert(this->equal(chop(this->several, 10), several_new));
	this->print("chop");
}

treeTester::treeTester()
{
	this->empty = tree_make();
	this->one = tree_make(1, this->empty, this->empty);
	this->two = tree_make(2, this->one, this->empty);
	this->several = tree_make(0,
		tree_make(-3,
			tree_make(-4, 
				tree_make(-5, tree_make(), tree_make()),
				tree_make()),
			tree_make(-2, 
				tree_make(),
				tree_make(-1, tree_make(), tree_make()))),
		tree_make(4,
			tree_make(2,
				tree_make(1, tree_make(), tree_make()),
				tree_make(3, tree_make(), tree_make())),
			tree_make(5, tree_make(), tree_make())));
}

bool treeTester::equal(const tree_t &t1, const tree_t &t2)
{
	if (tree_isEmpty(t1) && tree_isEmpty(t2))
	{
		return true;
	}
	else if (tree_isEmpty(t1) || tree_isEmpty(t2))
	{
		return false;
	}
	else
	{
		return ((tree_elt(t1) == tree_elt(t2))
			&& equal(tree_left(t1), tree_left(t2))
			&& equal(tree_right(t1), tree_right(t2)));
	}
}

void treeTester::testTreeSum() const
{
	assert(tree_sum(this->empty) == 0);
	assert(tree_sum(this->one) == 1);
	assert(tree_sum(this->two) == 3);
	assert(tree_sum(this->several) == 0);
	this->print("tree_sum");
}

void treeTester::testTreeSearch() const
{
	assert(tree_search(this->empty, 100) == false);
	assert(tree_search(this->one, 100) == false);
	assert(tree_search(this->one, 1) == true);
	assert(tree_search(this->two, 1) == true);
	assert(tree_search(this->two, 2) == true);
	assert(tree_search(this->two, 3) == false);
	assert(tree_search(this->several, -5) == true);
	assert(tree_search(this->several, 4) == true);
	assert(tree_search(this->several, 6) == false);
	this->print("tree_search");
}

void treeTester::testDepth() const
{
	assert(depth(this->empty) == 0);
	assert(depth(this->one) == 1);
	assert(depth(this->two) == 2);
	assert(depth(this->several) == 4);
	this->print("depth");
}

void treeTester::testTreeMin() const
{
	assert(tree_min(this->one) == 1);
	assert(tree_min(this->two) == 1);
	assert(tree_min(this->several) == -5);
	this->print("tree_min");
}

void treeTester::testTraversal() const
{
	assert(listTester::equal(traversal(this->empty), list_make()));
	assert(listTester::equal(traversal(this->one), list_make(1, list_make())));
	assert(listTester::equal(traversal(this->two), list_make(1,list_make(2, list_make()))));
	auto list_new = list_make();
	for (int i = 5;i >= -5;i--)
	{
		list_new = list_make(i, list_new);
	}
	assert(listTester::equal(traversal(this->several), list_new));
	this->print("traversal");
}

void treeTester::testTreeHasPathSum() const
{
	assert(tree_hasPathSum(this->empty, 0) == false);
	assert(tree_hasPathSum(this->one, 100) == false);
	assert(tree_hasPathSum(this->one, 1) == true);
	assert(tree_hasPathSum(this->two, 1) == false);
	assert(tree_hasPathSum(this->two, 2) == false);
	assert(tree_hasPathSum(this->two, 3) == true);
	assert(tree_hasPathSum(this->several, 10) == false);
	assert(tree_hasPathSum(this->several, 9) == true);
	assert(tree_hasPathSum(this->several, 7) == true);
	assert(tree_hasPathSum(this->several, 8) == false);
	assert(tree_hasPathSum(this->several, -6) == true);
	assert(tree_hasPathSum(this->several, -12) == true);
	for (int i = -5;i <= 0;i++)
	{
		assert(tree_hasPathSum(this->several, i) == false);
	}
	this->print("tree_hasPathSum");
}

void treeTester::testCoveredBy() const
{
	assert(covered_by(this->empty, this->empty) == true);
	assert(covered_by(this->empty, this->one) == true);
	assert(covered_by(this->empty, this->two) == true);
	assert(covered_by(this->one, this->empty) == false);
	assert(covered_by(this->two, this->empty) == false);
	assert(covered_by(this->one, this->two) == false);
	this->print("covered_by");
}

void treeTester::testContainedBy() const
{
	assert(contained_by(this->empty, this->empty) == true);
	assert(contained_by(this->empty, this->one) == true);
	assert(contained_by(this->empty, this->two) == true);
	assert(contained_by(this->one, this->empty) == false);
	assert(contained_by(this->two, this->empty) == false);
	assert(contained_by(this->one, this->two) == true);
	assert(contained_by(this->empty, this->several) == true);
	assert(contained_by(this->one, this->several) == true);
	assert(contained_by(this->two, this->several) == true);
	this->print("contained_by");
}

void treeTester::testInsertTree() const
{
	assert(equal(insert_tree(1, this->empty), this->one));
	assert(equal(insert_tree(2, this->one), tree_make(1, tree_make(), tree_make(2, tree_make(), tree_make()))));
	auto several_new = tree_make(0,
		tree_make(-3,
			tree_make(-4,
				tree_make(-5, 
					tree_make(-6, tree_make(), tree_make()),
					tree_make()),
				tree_make()),
			tree_make(-2,
				tree_make(),
				tree_make(-1, tree_make(), tree_make()))),
		tree_make(4,
			tree_make(2,
				tree_make(1, tree_make(), tree_make()),
				tree_make(3, tree_make(), tree_make())),
			tree_make(5, 
				tree_make(), 
				tree_make(6, tree_make(), tree_make()))));
	assert(equal(insert_tree(-6, insert_tree(6, this->several)), several_new));
	this->print("insert_tree");
}
