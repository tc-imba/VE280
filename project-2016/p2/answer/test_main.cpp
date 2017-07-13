#include <iostream>
#include "test.h"

int main()
{
	listTester lt;
	lt.testSize();
	lt.testSum();
	lt.testProduct();
	lt.testAccumulate();
	lt.testReverse();
	lt.testAppend();
	lt.testFilterOdd();
	lt.testFilterEven();
	lt.testFilter();
	lt.testInsertList();
	lt.testChop();
	
	treeTester tt;
	tt.testTreeSum();
	tt.testTreeSearch();
	tt.testDepth();
	tt.testTreeMin();
	tt.testTraversal();
	tt.testTreeHasPathSum();
	tt.testCoveredBy();
	tt.testContainedBy();
	tt.testInsertTree();

	std::cin.get();
	return 0;
}