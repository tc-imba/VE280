all: test
answer:
	cp p3 tc-imba/
	cd tc-imba && bash answer.sh
	
test: p3
	cp p3 tc-imba/
	cd tc-imba && bash test.sh
	cp p3 50-tests/
	cd 50-tests && bash test.sh

p3: p3.cpp simulation.cpp
	g++ -std=c++11 -o p3 p3.cpp simulation.cpp

clean:
	rm -rf p3 */p3
	rm -rf tc-imba/*/*.out
	rm -rf 50-tests/output-*
