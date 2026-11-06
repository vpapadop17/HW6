#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <stdexcept>


const int COLOR_RED = 0;
const int COLOR_BLACK = 1;


struct RBTNode {
    int data;
    int color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;

    RBTNode(int val) {
        data = val;
        color = COLOR_RED; //New node is red
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
	private:
		RBTNode* root;
		int numItems;

	public:
		
		RedBlackTree();
		~RedBlackTree();

    
    void Insert(int value);
    bool Contains(int value) const;
    int GetMin();
};

#endif // REDBLACKTREE_H
