
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

/**
 * 
 * This "First Step" tests file is useful to get your project started
 * 
 * To run this code you only need to implement
 * 	+ The Constructor
 * 	+ The Insert() function to insert only one node
 * 	+ The ToInfixString() function to print a tree containing only one node
 * 
**/

using namespace std;

struct RBTNode {
    int data;
    int color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;

    //Constructor
    RBTNode(int val) {
        data = val;
        color = COLOR_RED; //New node is red
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

bool RedBlackTree::Contains(int value) const {
    RBTNode* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            return true;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

//this is teh website I used to figure out how to set the thing equal to a color 
//https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/
void RedBlackTree::Insert(int value){
	
	//check if I already have this value in the tree
	bool isDuplicate = Contains(value);
	if (isDuplicate == true){
		throw invalid_argument("Value already exists!"); 
	}
	
	RBTNode* newnode = new RBTNode()
	newnode->data = value;
	newnode->color = COLOR_RED;  //all inserted nodes red
	newnode->left = nullptr;     
	newnode->right = nullptr;    
	newnode->parent = nullptr;
	
	if (root == nullptr){
		newnode->color = COLOR_BLACK;
		root = newnode; 
		numItems++;
		return ;
	}
	RBTNode* current = root; 
	RBTNode* parentNode = nullptr; //when i increment later I will need to know what teh previous node was 
	
	while (current != nullptr){
		parentNode = current; 
		if (value < current->data){
			current = current->left; 
		} else {
			current = current->right;
		}
	} 
	newnode->parent = parentNode; 
	
	if (value < parentNode->data) {
    parentNode->left = newnode;
	} else {
		parentNode->right = newnode;
	}
	numItems++;
}
	
	
	
	

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToInfixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


int main(){	
	TestSimpleConstructor();
	TestInsertFirstNode();

	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
