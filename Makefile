all:
	g++ -std=c++17 -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

run:
	./rbt-tests

try: all run
