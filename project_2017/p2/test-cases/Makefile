all:
	perl -0777pe 's/list_t[\s\n]*&[\s\n]*[\w]*/Cannot_Use_Reference/' p2.cpp > p2_no_list.cpp
	perl -0777pe 's/tree_t[\s\n]*&[\s\n]*[\w]*/Cannot_Use_Reference/' p2_no_list.cpp > p2_clean.cpp
	g++ -std=c++11 -O2 -o p2 p2_clean.cpp main.cpp recursive.cpp loader.cpp
	rm -f p2_clean.cpp p2_no_list.cpp
