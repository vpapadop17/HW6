#include <queue>
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

// Citations & Resources:
// - Red-Black Tree deletion reference: http://www.cs.toronto.edu/~wgeorge/csc265/2013/09/26/tutorial-3-red-black-tree-deletion.html
// https://www.usna.edu/Users/cs/crabbe/SI321/current/red-black/red-black.html

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
	// SpeedTest: On a tree of 3.7 million nodes, Insert() is very fast,
    // taking between 0 and 1e-06 seconds per insertion because Red-Black
    // trees maintain O(log n) height.
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

void RedBlackTree::RotateLeft(RBTNode* x) {
	//grab the nodes we want to change right child and call it y, x is teh node i want to rotate 
    RBTNode* y = x->right;
    //y is going to put x on its left
    x->right = y->left;
    //if y has a left child, then make x its new parent 
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    //connect y to x's old parent to complete the transfornation
    y->parent = x->parent;
    //if x had NO parent then make it the root
    if (x->parent == nullptr) {
        root = y;
        //if it was on the left side of somehting then hold it on the left side
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
		//the same as above but on the right 
        x->parent->right = y;
    }
    //putu x underneath y as its left child 
    y->left = x;
    //make x the parent of y 
    x->parent = y;
}

void RedBlackTree::RotateRight(RBTNode* x) {
	//Grab x's left child and call it y 
    RBTNode* y = x->left;
    //y is about to put x on its rigth side , so y's old left child becomes x's left one
    x->left = y->right;
    //if y has a rigth child then its new parent is x 
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    //connect y to x's old parent 
    y->parent = x->parent;
    //if no parent make it root 
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::Remove(int data) {
	// SpeedTest: On a tree of 3.7 million nodes, Remove() takes roughly 1.1e-05 to 2.7e-05
    // seconds per deletion. It has O(log n) and is very fast,
    // though it is slightly slower than Insert() due to rebalancing and null-node cleanup.
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
			throw std::invalid_argument("Value not found in Tree!");	
		}
		// If D has two children, swap with in-order successor
		// and make the successor the new node D 
		if (D->left != nullptr && D->right != nullptr) {
			RBTNode* successor = GetInOrderSuccessor(D);
			D->data = successor->data;
			D = successor;
		}
		// 3. Find replacement node R (D now has at most 1 non-null child)
		RBTNode* R = nullptr;
		if (D->left != nullptr) {
			R = D->left;
		} else if (D->right != nullptr) {
			R = D->right;
		} else {
			// D has no child therefore, create a black null as R
			R = new RBTNode(0, true);
		}
		// Replace D with R in the tree, make D's parent R's parent
		RBTNode* parent = D->parent;
		//get R to have that as a parent
		R->parent = parent;
		if (parent == nullptr) {
			root = R;
		} else if (D == parent->left) {
			parent->left = R;
		} else {
			parent->right = R;
		}

		//we need to know the color of D before we delete it 
		unsigned short int deletedColor = D->color;
		delete D;
		numItems--;
		
		if (R == root) {
        // Rule 1: R is at root position -> mark black and stop
        R->color = COLOR_BLACK;
		} else if (deletedColor == COLOR_RED) {
			// Rule 2: Deleted node D was red -> mark R black and stop
			R->color = COLOR_BLACK;
			//at this point I know that D was black here on
		} else if (R->color == COLOR_RED) {
        // Rule 3: Replacement node R is red -> mark R black and stop
			R->color = COLOR_BLACK;
		} else {
        // Rule 4: Both D and R are black -> Double Black!
			R->color = COLOR_DOUBLE_BLACK;
			FixDoubleBlack(R);
		}
		 // Clean up  null node so no invisible nodes stay in the tree
		 //if R is not nullnode it skips this
		if (R->isNullNode) {
			if (R == root) {
				root = nullptr;
		//If the fake node is hanging on its parent's left side, unhook it and set that left side back to nullptr
        } else if (R->parent->left == R) {
            R->parent->left = nullptr;
        //same as above but for right
        } else if (R->parent->right == R) {
            R->parent->right = nullptr;
        }
        delete R;
		}	
		
    }



void RedBlackTree::FixDoubleBlack(RBTNode* dbNode) {
	// 1: Double black is at the root -> remove it and mark root black
    if (dbNode == root) {
        dbNode->color = COLOR_BLACK;
        return;
    }
    RBTNode* parent = dbNode->parent;
    bool dbIsLeftChild = false;
	RBTNode* sibling = nullptr;

	if (dbNode == parent->left) {
		dbIsLeftChild = true;
		sibling = parent->right; // If dbNode is on the left, its sibling is on the right
	} else {
		dbIsLeftChild = false;
		sibling = parent->left;  // If dbNode is on the right, its sibling is on the left
	}
	// Case 3: Sibling is RED
    if (sibling != nullptr && sibling->color == COLOR_RED) {
        parent->color = COLOR_RED;
        sibling->color = COLOR_BLACK;
        if (dbIsLeftChild) {
            RotateLeft(parent);  // Sibling on right -> left rotate parent
        } else {
            RotateRight(parent); // Sibling on left -> right rotate parent
        }
        // Double black still isn't fixed, recall function to fall into new case
        FixDoubleBlack(dbNode);
        return;
    }
    // Case 2: Sibling is BLACK
    if (sibling == nullptr) {
    return;
	}
    bool leftRed = (sibling->left != nullptr && sibling->left->color == COLOR_RED);
    bool rightRed = (sibling->right != nullptr && sibling->right->color == COLOR_RED);

    //2a: Sibling has all black children (no red children)
    if (!leftRed && !rightRed) {
        sibling->color = COLOR_RED;
        dbNode->color = COLOR_BLACK;

        if (parent->color == COLOR_RED) {
            parent->color = COLOR_BLACK;
        } else {
            parent->color = COLOR_DOUBLE_BLACK;
            FixDoubleBlack(parent);
        }
        return;
    }
        // Subcase 2b: Sibling has 1 or 2 red children
    if (!dbIsLeftChild) {
        // Sibling is on the LEFT (LL or LR)
        if (leftRed) {
            // 1) LL case: sibling on left + red child on left (or two red children)
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            parent->color = COLOR_BLACK;
            dbNode->color = COLOR_BLACK;
            RotateRight(parent);
        } else {
            // 2) LR case: sibling on left + 1 red child on right
            sibling->right->color = parent->color;
            parent->color = COLOR_BLACK;
            dbNode->color = COLOR_BLACK;
            RotateLeft(sibling);
            RotateRight(parent);
        }
    } else {
        // Sibling is on the RIGHT (RR or RL)
        if (rightRed) {
            // 3) RR case: sibling on right + red child on right (or two red children)
            sibling->right->color = sibling->color;
            sibling->color = parent->color;
            parent->color = COLOR_BLACK;
            dbNode->color = COLOR_BLACK;
            RotateLeft(parent);
        } else {
            // 4) RL case: sibling on right + 1 red child on left
            sibling->left->color = parent->color;
            parent->color = COLOR_BLACK;
            dbNode->color = COLOR_BLACK;
            RotateRight(sibling);
            RotateLeft(parent);
        }
    }
    
}

RedBlackTree::~RedBlackTree() {
    while (root != nullptr) {
        Remove(root->data);
    }
}
