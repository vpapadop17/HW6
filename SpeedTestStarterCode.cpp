#include <cstdlib>
#include <iostream>
#include <ctime>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;


	// Your code goes here to simulate leaving / joining.
	start = clock();
	for (int i = 0; i < 100000; i++) {
		rbt.Remove(i);      // ID i leaves
		rbt.Insert(N + i);  // New ID (3700000 + i) joins
	}
	stop = clock();

	duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Simulated 100,000 leave/join operations in " << duration << " seconds." << endl;

	return 0;
}
