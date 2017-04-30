#include <iostream>
#include "recursive.h"
#include "p3.h"

using namespace std;

int add(int a, int b)
{
	return a+b;
}

int mult(int a, int b)
{
	return a*b;
}

bool mod3(int a)
{
	return (a%3 == 0);
}

int main(int argc, char *argv[])
{
	int checkId;
	int i;
	list_t listA = list_make();
	list_t listB = list_make();
	list_t listZero = list_make();
	list_t listOne = list_make();

	for(i = 5; i > 0; i--)
	{
		listA = list_make(i, listA);
		listB = list_make(i+10, listB);
	}

	listOne = list_make(11, listOne);


	tree_t treeA = tree_make(2,
				     tree_make(1, tree_make(), tree_make()),
				     tree_make(4, tree_make(), tree_make()));

   	tree_t treeB = tree_make(2,
			   tree_make(3, tree_make(), tree_make()),
			   tree_make(4, 
				     tree_make(0, tree_make(), tree_make()),
				     tree_make()));
	
	tree_t treeC = tree_make(2,
			   tree_make(1,
			   		 tree_make(),
					 tree_make(5,
					 	tree_make(6, tree_make(), tree_make()),
						tree_make())),
			   tree_make(4, 
				     tree_make(0, tree_make(), tree_make()),
				     tree_make()));

	tree_t treeSingle = tree_make(1, tree_make(), tree_make());
	tree_t treeEmpty = tree_make();

	cin >> checkId;

	switch (checkId) {
		case 1: {
			cout << "Size of listA is " << size(listA) << endl;
			cout << "Size of listZero is " << size(listZero) << endl;
			cout << "Size of listOne is " << size(listOne) << endl;
			break;	
		} case 2: {
			cout << "Sum of listA is " << sum(listA) << endl;
			cout << "Sum of listZero is " << sum(listZero) << endl;
			cout << "Sum of listOne is " << sum(listOne) << endl;
			break;	
		} case 3: {
			cout << "Product of listA is " << product(listA) << endl;
			cout << "Product of listZero is " << product(listZero)
				<< endl;
			cout << "Product of listOne is " << product(listOne)
			<< endl;
			break;
		} case 4: {
			cout << "Sum of listB is " << accumulate(listB, add, 0)
				<< endl;
			cout << "Sum of listZero is " << accumulate(listZero, add, 0)
				<< endl;
			break;	
		} case 5: {
			cout << "Product of listB is " << accumulate(listB, mult, 1)
				<< endl;
			cout << "Product of listZero is " << accumulate(listZero,
				mult, 1) << endl;
			cout << "Product of listOne is " << accumulate(listOne,
				mult, 1) << endl;
			break;	
		} case 6: {
			cout << "Reverse of listA is " << flush;
			list_print(reverse(listA));
			cout << endl;

			cout << "Reverse of listZero is " << flush;
			list_print(reverse(listZero));
			cout << endl;

			cout << "Reverse of listOne is " << flush;
			list_print(reverse(listOne));
			cout << endl;
			break;	
		} case 7: {
			cout << "Append listB after listA is " << flush;
			list_print(append(listA, listB));
			cout << endl;

			cout << "Append listZero after listA is " << flush;
			list_print(append(listA, listZero));
			cout << endl;

			cout << "Append listB after listZero is " << flush;
			list_print(append(listZero, listB));
			cout << endl;

			cout << "Append listZero after listZero is " << flush;
			list_print(append(listZero, listZero));
			cout << endl;
			break;
		} case 8: {
			cout << "Filter odd of listA is " << flush;
			list_print(filter_odd(listA));
			cout << endl;

			cout << "Filter odd of listZero is " << flush;
			list_print(filter_odd(listZero));
			cout << endl;

			cout << "Filter odd of listOne is " << flush;
			list_print(filter_odd(listOne));
			cout << endl;
			break;	
		} case 9: {
			cout << "Filter even of listA is " << flush;
			list_print(filter_even(listA));
			cout << endl;

			cout << "Filter even of listZero is " << flush;
			list_print(filter_even(listZero));
			cout << endl;

			cout << "Filter even of listOne is " << flush;
			list_print(filter_even(listOne));
			cout << endl;
			break;	
		} case 10: {
			cout << "Filter mod 3 of listB is " << flush;
			list_print(filter(listB, mod3));
			cout << endl;

			cout << "Filter mod 3 of listZero is " << flush;
			list_print(filter(listZero, mod3));
			cout << endl;

			cout << "Filter mod 3 of listOne is " << flush;
			list_print(filter(listOne, mod3));
			cout << endl;
			break;
		} case 11: {
			cout << "Insert listA at the 2nd position of listB gives "
				<< flush;
			list_print(insert_list(listB, listA, 2));
			cout << endl;

			cout << "Insert listA at the 0th position of listOne gives "
				<< flush;
			list_print(insert_list(listOne, listA, 0));
			cout << endl;

			cout << "Insert listA at the 1st position of listOne gives "
				<< flush;
			list_print(insert_list(listOne, listA, 1));
			cout << endl;

			cout << "Insert listA at the 0th position of listZero gives "
				<< flush;
			list_print(insert_list(listZero, listA, 0));
			cout << endl;
			break;
		} case 12: {
			cout << "Chop the last 2 elements of listA " << flush;
			list_print(chop(listA, 2));
			cout << endl;

			cout << "Chop the last 0 elements of listZero " << flush;
			list_print(chop(listZero, 0));
			cout << endl;

			cout << "Chop the last 1 elements of listOne " << flush;
			list_print(chop(listOne, 1));
			cout << endl;
			break;
		} case 13: {
			cout << "Sum of treeA is " << tree_sum(treeA) << endl;
			cout << "Sum of treeB is " << tree_sum(treeB) << endl;
			cout << "Sum of treeSingle is " << tree_sum(treeSingle) << endl;
			cout << "Sum of treeEmpty is " << tree_sum(treeEmpty) << endl;
			break;	
		} case 14: {
			cout << "Searching key = 3 in treeA is " 
				<< (tree_search(treeA, 3) ? "successful":"failed") << endl;

			cout << "Searching key = 3 in treeB is " 
				<< (tree_search(treeB, 3) ? "successful":"failed") << endl;

			cout << "Searching key = 5 in treeEmpty is " 
				<< (tree_search(treeEmpty, 5) ? "successful":"failed") << endl;
			break;	
		} case 15: {
			cout << "Depth of treeA is " << depth(treeA) << endl;
			cout << "Depth of treeB is " << depth(treeB) << endl;
			cout << "Depth of treeC is " << depth(treeC) << endl;
			cout << "Depth of treeSingle is " << depth(treeSingle) << endl;
			cout << "Depth of treeEmpty is " << depth(treeEmpty) << endl;
			break;
		} case 16: {
			cout << "The smallest value of treeA is " << tree_min(treeA) << endl;
			cout << "The smallest value of treeB is " << tree_min(treeB) << endl;
			cout << "The smallest value of treeC is " << tree_min(treeC) << endl;
			cout << "The smallest value of treeSingle is " << tree_min(treeSingle) << endl;
			break;
		} case 17: {
			cout << "In-order traversal of treeA is " << flush;
			list_print(traversal(treeA));
			cout << endl;

			cout << "In-order traversal of treeB is " << flush;
			list_print(traversal(treeB));
			cout << endl;

			cout << "In-order traversal of treeC is " << flush;
			list_print(traversal(treeC));
			cout << endl;

			cout << "In-order traversal of treeSingle is " << flush;
			list_print(traversal(treeSingle));
			cout << endl;

			cout << "In-order traversal of treeEmpty is " << flush;
			list_print(traversal(treeEmpty));
			cout << endl;
			break;
		} case 18: {
			cout << "Does treeA have a path sum 3? "
				<< (tree_hasPathSum(treeA, 3) ? "Yes":"No") << endl;

			cout << "Does treeA have a path sum 5? "
				<< (tree_hasPathSum(treeA, 5) ? "Yes":"No") << endl;

			cout << "Does treeC have a path sum 3? "
				<< (tree_hasPathSum(treeC, 3) ? "Yes":"No") << endl;

			cout << "Does treeC have a path sum 5? "
				<< (tree_hasPathSum(treeC, 5) ? "Yes":"No") << endl;

			cout << "Does treeC have a path sum 8? "
				<< (tree_hasPathSum(treeC, 8) ? "Yes":"No") << endl;

			cout << "Does treeC have a path sum 14? "
				<< (tree_hasPathSum(treeC, 14) ? "Yes":"No") << endl;

			cout << "Does treeSingle have a path sum 1? "
				<< (tree_hasPathSum(treeSingle, 1) ? "Yes":"No") << endl;

			cout << "Does treeSingle have a path sum 0? "
				<< (tree_hasPathSum(treeSingle, 0) ? "Yes":"No") << endl;

			cout << "Does treeEmpty have a path sum 3? "
				<< (tree_hasPathSum(treeEmpty, 3) ? "Yes":"No") << endl;

			cout << "Does treeEmpty have a path sum 0? "
				<< (tree_hasPathSum(treeEmpty, 0) ? "Yes":"No") << endl;
			break;
		} case 19: {
		    tree_t treeBCover = tree_make(2,
					   tree_make(3, tree_make(), tree_make()),
					   tree_make(4, tree_make(), tree_make()));

		    cout << "treeBCover is " << endl;
		    tree_print(treeBCover);
		    cout << endl;

		    cout << "Is treeBCover covered by treeB? "
		         << (covered_by(treeBCover, treeB) ? "Yes":"No")
		         << endl;
			
		    tree_t treeCCover = tree_make(2,
					   tree_make(1,
					   		 tree_make(),
							 tree_make(5, tree_make(), tree_make())),
					   tree_make());

		    cout << "treeCCover is " << endl;
		    tree_print(treeCCover);
		    cout << endl;

		    cout << "Is treeCCover covered by treeC? "
		         << (covered_by(treeCCover, treeC) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeSingle covered by treeB? "
		         << (covered_by(treeSingle, treeB) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeEmpty covered by treeB? "
		         << (covered_by(treeEmpty, treeB) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeB covered by treeEmpty? "
		         << (covered_by(treeB, treeEmpty) ? "Yes":"No")
		         << endl;

		    cout << "Is treeEmpty covered by treeEmpty? "
		         << (covered_by(treeEmpty, treeEmpty) ? "Yes":"No")
		         << endl;
			break;
		} case 20: {
		    cout << "Is treeSingle contained by treeB? "
		         << (contained_by(treeSingle, treeB) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeSingle contained by treeC? "
		         << (contained_by(treeSingle, treeC) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeB contained by treeSingle? "
		         << (contained_by(treeB, treeSingle) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeEmpty contained by treeSingle? "
		         << (contained_by(treeEmpty, treeSingle) ? "Yes":"No")
		         << endl;
			
		    cout << "Is treeEmpty covered by treeEmpty? "
		         << (contained_by(treeEmpty, treeEmpty) ? "Yes":"No")
		         << endl;
			
		    tree_t treeC_Contain = tree_make(1,
					   		 tree_make(),
							 tree_make(5, tree_make(), tree_make()));

		    cout << "treeC_Contain is " << endl;
		    tree_print(treeC_Contain);
		    cout << endl;

		    cout << "Is treeC_Contain contained by treeC? "
		         << (contained_by(treeC_Contain, treeC) ? "Yes":"No")
		         << endl;
			
		    tree_t treeC_Not_Contain = tree_make(1,
							 	tree_make(6, tree_make(), tree_make()),
								tree_make());

		    cout << "treeC_Not_Contain is " << endl;
		    tree_print(treeC_Not_Contain);
		    cout << endl;

		    cout << "Is treeC_Not_Contain contained by treeC? "
		         << (contained_by(treeC_Not_Contain, treeC) ? "Yes":"No")
			     << endl;
			    break;
		} case 21: {
		    int numbers[] = {4, 7, 5, 3, 0, 1, 6, 3};
		    const int length = sizeof(numbers)/sizeof(int);

		    tree_t sorted_tree = tree_make();

		    cout << "Construct a sorted binary tree from an array of numbers ( "
		        << flush;
		    
		    for(i = 0; i < length; i++)
		        cout << numbers[i] << " " << flush;
		    cout << ")" << endl;

		    for(i = 0; i < length; i++)
		    {
		        sorted_tree = insert_tree(numbers[i], sorted_tree);
		        cout << endl;
		        tree_print(sorted_tree);
		        cout << endl;
		    }
		    break;
		} case 22: {
			cout << "Size of listA is " << size(listA) << endl;
			break;	
		} case 23: {
			cout << "Sum of listA is " << sum(listA) << endl;
			break;	
		} case 24: {
			cout << "Product of listA is " << product(listA) << endl;
			break;
		} case 25: {
			cout << "Sum of listB is " << accumulate(listB, add, 0)
				<< endl;
			break;	
		} case 26: {
			cout << "Product of listB is " << accumulate(listB, mult, 1)
				<< endl;
			break;	
		} case 27: {
			cout << "Reverse of listA is " << flush;
			list_print(reverse(listA));
			cout << endl;
			break;	
		} case 28: {
			cout << "Append listB after listA is " << flush;
			list_print(append(listA, listB));
			cout << endl;
			break;
		} case 29: {
			cout << "Sum of treeA is " << tree_sum(treeA) << endl;
			break;	
		} case 30: {
			cout << "Depth of treeA is " << depth(treeA) << endl;
			break;
		} default: {
			break;
		}
	}
	return 0;
}
