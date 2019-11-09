all: p3 test
	rm -f result
	./p3 species test-21 > output-1
	./test 1 >> result
	./p3 species test-21 -5 > output-2
	./test 2 >> result
	./p3 test-3 test-21 5 > output-3
	./test 3 >> result
	./p3 test-4 test-21 5 > output-4
	./test 4 >> result
	./p3 test-5 test-21 5 > output-5
	./test 5 >> result
	./p3 test-6 test-21 5 > output-6
	./test 6 >> result
	./p3 test-7 test-21 5 > output-7
	./test 7 >> result
	./p3 species test-8 5 > output-8
	./test 8 >> result
	./p3 species test-9 5 > output-9
	./test 9 >> result
	./p3 species test-10 5 > output-10
	./test 10 >> result
	./p3 species test-11 5 > output-11
	./test 11 >> result
	./p3 species test-12 5 > output-12
	./test 12 >> result
	./p3 species test-13 5 > output-13
	./test 13 >> result
	./p3 species test-14 5 > output-14
	./test 14 >> result
	./p3 species test-15 5 > output-15
	./test 15 >> result
	./p3 species test-16 5 > output-16
	./test 16 >> result
	./p3 species test-17 5 > output-17
	./test 17 >> result
	./p3 species test-18 5 > output-18
	./test 18 >> result
	./p3 species test-19 5 > output-19
	./test 19 >> result
	./p3 species test-20 5 > output-20
	./test 20 >> result
	./p3 species test-21 5 > output-21
	./test 21 >> result
	./p3 species test-21 5 v > output-22
	./test 22 >> result
	./p3 species test-21 5 verbose > output-23
	./test 23 >> result
	./p3 species test-24 20 > output-24
	./test 24 >> result
	./p3 species test-24 20 v > output-25
	./test 25 >> result
	./p3 species test-26 40 > output-26
	./test 26 >> result
	./p3 species test-26 40 v > output-27
	./test 27 >> result
	./p3 test-27 test-28 10 > output-28
	./test 28 >> result
	./p3 test-25 test-29 2 v > output-29
	./test 29 >> result
	./p3 test-30 test-31 1 v > output-30
	./test 30 >> result
	./p3 species test-32 50 > output-31
	./test 31 >> result
	./p3 species test-32 50 v > output-32
	./test 32 >> result
	./p3 species test-33 50 > output-33
	./test 33 >> result
	./p3 species test-34 50 v > output-34
	./test 34 >> result
	./p3 species test-35 50 > output-35
	./test 35 >> result
	./p3 species test-36 50 v > output-36
	./test 36 >> result
	./p3 species test-37 50 > output-37
	./test 37 >> result
	./p3 species test-38 50 v > output-38
	./test 38 >> result
	./p3 species test-39 50 > output-39
	./test 39 >> result
	./p3 species test-40 50 v > output-40
	./test 40 >> result
	./p3 species test-41 50 > output-41
	./test 41 >> result
	./p3 species test-42 50 v > output-42
	./test 42 >> result
	./p3 species test-43 50 > output-43
	./test 43 >> result
	./p3 species test-44 50 v > output-44
	./test 44 >> result
	./p3 species test-45 50 > output-45
	./test 45 >> result
	./p3 species test-46 50 v > output-46
	./test 46 >> result
	./p3 species test-47 50 > output-47
	./test 47 >> result
	./p3 species test-48 50 v > output-48
	./test 48 >> result
	./p3 species test-49 50 > output-49
	./test 49 >> result
	./p3 species test-50 50 v > output-50
	./test 50 >> result
	rm -f p3 test *.o
	cat result

test: test.o
	g++ -o test test.o

test.o: test.cpp
	g++ -c test.cpp

p3: p3.o simulation.o
	g++ -o p3 p3.o simulation.o

simulation.o: simulation.cpp
	g++ -c simulation.cpp

p3.o: p3.cpp
	g++ -c p3.cpp

clean:
	rm -f p3 test *.o output-* p3.cpp simulation.h simulation.cpp
