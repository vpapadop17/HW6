#include <queue>
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

RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

RedBlackTree::RedBlackTree(int value) {
    root = nullptr;
    numItems = 0;
    if (value != -99999) {
        Insert(value);
    }
}

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


void RedBlackTree::Insert(int value) {
    // Check if the value is already present in the tree (throw exception if it is)
    bool isDuplicate = Contains(value);
    if (isDuplicate == true) {
        throw invalid_argument("Value already exists!"); 
    }

    RBTNode* newnode = new RBTNode(value);

    //Step 1: If tree is empty, make newnode the root with color Black and exit
    if (root == nullptr) {
        newnode->color = COLOR_BLACK;
        root = newnode; 
        numItems++;
        return;
    }

    //Step 2
    RBTNode* current = root; 
    RBTNode* parentNode = nullptr; 

    while (current != nullptr) {
        parentNode = current; 
        if (value < current->data) {
            current = current->left; 
        } else {
            current = current->right;
        }
    } 

    // Set parent and child connections
    newnode->parent = parentNode; 
    if (value < parentNode->data) {
        parentNode->left = newnode;
    } else {
        parentNode->right = newnode;
    }
    numItems++;

    //This is what rebalances teh tree
    //Step 3: If parent is Black, loop won't run and we exit
    //Step 4: If parent is Red, enter loop to check uncle's color
    while (newnode != root && newnode->parent->color == COLOR_RED) {
        RBTNode* pNode = newnode->parent;
        RBTNode* gNode = pNode->parent;

        //Parent is the left child of Grandparent
        if (pNode == gNode->left) {
            RBTNode* uncle = gNode->right;

            //Step 6: Uncle is RED 
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                pNode->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                gNode->color = COLOR_RED;
                newnode = gNode; // Move up to check Grandparent 
            } 
            // STEP 5: Uncle is black or null
            else {
                //The left right case, rotate Left around Parent to make it a straight line[cite: 6]
                if (newnode == pNode->right) {
                    newnode = pNode;
                    
                    //Rotate Left around newnode
                    RBTNode* temp = newnode->right;
                    newnode->right = temp->left;
                    if (temp->left != nullptr) temp->left->parent = newnode;
                    temp->parent = newnode->parent;
                    if (newnode->parent == nullptr) root = temp;
                    else if (newnode == newnode->parent->left) newnode->parent->left = temp;
                    else newnode->parent->right = temp;
                    temp->left = newnode;
                    newnode->parent = temp;
                }

                //The left left case: recolor and rotate right around Grandparent
                newnode->parent->color = COLOR_BLACK;
                gNode->color = COLOR_RED;

                //Rotate right around gNode
                RBTNode* temp = gNode->left;
                gNode->left = temp->right;
                if (temp->right != nullptr) temp->right->parent = gNode;
                temp->parent = gNode->parent;
                if (gNode->parent == nullptr) root = temp;
                else if (gNode == gNode->parent->right) gNode->parent->right = temp;
                else gNode->parent->left = temp;
                temp->right = gNode;
                gNode->parent = temp;
            }
        } 
        //Parent is the right child of Grandparent
        else {
            RBTNode* uncle = gNode->left;

            //Step 6: Uncle is red 
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                pNode->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                gNode->color = COLOR_RED;
                newnode = gNode; // Move up to check Grandparent next[cite: 6]
            } 
            //Step 5: Uncle is black or null
            else {
                //The right left case: Rotate righ around parent
                if (newnode == pNode->left) {
                    newnode = pNode;

                    //Rotate Right around newnode (pNode)
                    RBTNode* temp = newnode->left;
                    newnode->left = temp->right;
                    if (temp->right != nullptr) temp->right->parent = newnode;
                    temp->parent = newnode->parent;
                    if (newnode->parent == nullptr) root = temp;
                    else if (newnode == newnode->parent->right) newnode->parent->right = temp;
                    else newnode->parent->left = temp;
                    temp->right = newnode;
                    newnode->parent = temp;
                }

                //The right right case: Recolor and rotate left around Grandparent
                newnode->parent->color = COLOR_BLACK;
                gNode->color = COLOR_RED;

                //Rotate left around gNode
                RBTNode* temp = gNode->right;
                gNode->right = temp->left;
                if (temp->left != nullptr) temp->left->parent = gNode;
                temp->parent = gNode->parent;
                if (gNode->parent == nullptr) root = temp;
                else if (gNode == gNode->parent->left) gNode->parent->left = temp;
                else gNode->parent->right = temp;
                temp->left = gNode;
                gNode->parent = temp;
            }
        }
    }

    //Ensure the root is black
    root->color = COLOR_BLACK;
}
	
int RedBlackTree::GetMin() const{
	if (root == nullptr) {
        throw runtime_error("Tree is empty");
    }

    // 2. Start at the root
    RBTNode* current = root;

    // 3. Keep moving left until there are no left children
    while (current->left != nullptr) {
        current = current->left;
    }

    // 4. Return the data stored in the leftmost node
    return current->data;
}
	
int RedBlackTree::GetMax() const{
    //Check if empty
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }

    //Start at the root
    RBTNode* current = root;

    //Keep moving right until there are no right children
    while (current->right != nullptr) {
        current = current->right;
    }

    //Return the data stored in the node that is at the last right spot
    return current->data;
}

unsigned long long int RedBlackTree::Size() const {
    return numItems;
}

string RedBlackTree::ToInfixString(RBTNode* n) const {
    if (n == nullptr) {
        return "";
    }

    string result = "";
    result += ToInfixString(n->left);
    
    // Add color prefix and data value
    if (n->color == COLOR_BLACK) {
        result += " B" + to_string(n->data) + " ";
    } else {
        result += " R" + to_string(n->data) + " ";
    }
    
    result += ToInfixString(n->right);
    return result;
}

string RedBlackTree::ToPrefixString(RBTNode* n) const {
    if (n == nullptr) {
        return "";
    }

    string result = "";
    
    // Process root/current node first
    if (n->color == COLOR_BLACK) {
        result += " B" + to_string(n->data) + " ";
    } else {
        result += " R" + to_string(n->data) + " ";
    }
    
    result += ToPrefixString(n->left);
    result += ToPrefixString(n->right);
    return result;
}

string RedBlackTree::ToPostfixString(RBTNode* n) const {
    if (n == nullptr) {
        return "";
    }

    string result = "";
    result += ToPostfixString(n->left);
    result += ToPostfixString(n->right);
    
    // Process root/current node last
    if (n->color == COLOR_BLACK) {
        result += " B" + to_string(n->data) + " ";
    } else {
        result += " R" + to_string(n->data) + " ";
    }
    
    return result;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other) {

    root = nullptr;
    numItems = other.numItems;

    if (other.root == nullptr) {
        return;
    }

    queue<const RBTNode*> originalQueue;
    queue<RBTNode*> copyQueue;

    // Copy the root
    root = new RBTNode(other.root->data);
    root->color = other.root->color;

    originalQueue.push(other.root);
    copyQueue.push(root);

    // Copy the remaining nodes
    while (!originalQueue.empty()) {

        const RBTNode* original = originalQueue.front();
        originalQueue.pop();

        RBTNode* copy = copyQueue.front();
        copyQueue.pop();

        // Copy left child
        if (original->left != nullptr) {

            copy->left = new RBTNode(original->left->data);
            copy->left->color = original->left->color;
            copy->left->parent = copy;

            originalQueue.push(original->left);
            copyQueue.push(copy->left);
        }

        // Copy right child
        if (original->right != nullptr) {

            copy->right = new RBTNode(original->right->data);
            copy->right->color = original->right->color;
            copy->right->parent = copy;

            originalQueue.push(original->right);
            copyQueue.push(copy->right);
        }
    }
}

RBTNode* RedBlackTree::GetInOrderSuccessor(RBTNode* node) const {
    // right, then all left and take it
    RBTNode* curr = node->right;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

void RedBlackTree::Remove(int data) {
	RBTNode* D = root;

    //Search for the node
    while (D != nullptr && D->data != data) {
        if (data < D->data) {
            D = D->left;
        } else {
            D = D->right;
        }
    }
        if (D == nullptr) {
			throw std::invalid_argument("Value not foudn in Tree!";	
		}
		// If D has two children, swap data with in-order successor
		// and make the successor the new node D 
		if (D->left != nullptr && D->right != nullptr) {
			RBTNode* successor = GetInOrderSuccessor(D);
			D->data = successor->data;
			D = successor;
		}
		
		
		
		
		
		
		
		
		
    }
    
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

RedBlackTree::~RedBlackTree() {
    while (root != nullptr) {
        if (root->left != nullptr) {
            // Rotate the tree right to flatten the left branch
            RBTNode* temp = root->left;
            root->left = temp->right;
            temp->right = root;
            root = temp;
        } else {
            // Move down to the right and delete the leaf
            RBTNode* temp = root;
            root = root->right;
            delete temp;
        }
    }
    numItems = 0;
}
