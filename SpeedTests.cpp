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


	//remove 5 random existing IDs
    for (int i = 0; i < 5; i++) {
        int id = rand() % N;
        while (!rbt.Contains(id)) {
            id = rand() % N;
        }

        start = clock();
        rbt.Remove(id);
        stop = clock();

        duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
        cout << "Remove " << i + 1 << ": " << duration << " seconds" << endl;
    }

    // insert 5 new IDs
    for (int i = 0; i < 5; i++) {
        int newId = N + (rand() % 100000);
        while (rbt.Contains(newId)) {
            newId++;
        }

        start = clock();
        rbt.Insert(newId);
        stop = clock();

        duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
        cout << "Insert " << i + 1 << ": " << duration << " seconds" << endl;
    }
	return 0;
}
