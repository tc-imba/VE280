#pragma once
#include "recursive.h"

class Tester
{
protected:
	void print(const char*) const;
};

class listTester : Tester
{
public:
	listTester();
	static bool equal(const list_t&, const list_t&);
	void testSize() const;
	void testSum() const;
	void testProduct() const;
	void testAccumulate() const;
	void testReverse() const;
	void testAppend() const;
	void testFilterOdd() const;
	void testFilterEven() const;
	void testFilter() const;
	void testInsertList() const;
	void testChop() const;

private:
	list_t empty, one, several;
};

class treeTester : Tester
{
public:
	treeTester();
	static bool equal(const tree_t&, const tree_t&);
	void testTreeSum() const;
	void testTreeSearch() const;
	void testDepth() const;
	void testTreeMin() const;
	void testTraversal() const;
	void testTreeHasPathSum() const;
	void testCoveredBy() const;
	void testContainedBy() const;
	void testInsertTree() const;
private:
	tree_t empty, one, two, several;
};