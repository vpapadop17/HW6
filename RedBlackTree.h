#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <stdexcept>
#include <string>

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
        color = COLOR_RED; // New node is red
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
private:
    RBTNode* root = nullptr;
    unsigned long long int numItems = 0;

    // Private recursive helper methods for string formatting
    std::string ToInfixString(RBTNode* n) const;
    std::string ToPrefixString(RBTNode* n) const;
    std::string ToPostfixString(RBTNode* n) const;

public:
    // Constructors & Destructor
    RedBlackTree();
    RedBlackTree(int value);
    RedBlackTree(const RedBlackTree& other);
    ~RedBlackTree();

    // Public inline ToString methods
    std::string ToInfixString() const { return ToInfixString(root); }
    std::string ToPrefixString() const { return ToPrefixString(root); }
    std::string ToPostfixString() const { return ToPostfixString(root); }

    // Core functionality
    void Insert(int value);
    bool Contains(int value) const;
    int GetMin() const;
    int GetMax() const;
    unsigned long long int Size() const;
};

#endif // REDBLACKTREE_H
