all:
	g++ -std=c++17 -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests
	g++ -std=c++17 -Wall -g RedBlackTree.cpp SpeedTest.cpp -o speed-test

run:
	./rbt-tests
	./speed-test

try: all run
