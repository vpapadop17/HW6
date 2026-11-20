all:
	g++ -std=c++17 -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests
	g++ -std=c++17 -Wall -g RedBlackTree.cpp SpeedTests.cpp -o speed-test

run:
	./rbt-tests
	./speed-test

try: all run
