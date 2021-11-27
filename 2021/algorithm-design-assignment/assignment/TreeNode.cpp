// TreeNode.cpp

using namespace std;

 /* The node contain parent node, left child node and right child node, all of which are default to NULL pointer (unless specified)
    The node must contain the value to use for comparison, otherwise it is unusable
    The pointer is visualised as:
           parent
              |
             node
            /   \
    leftChild   rightChild */
struct TreeNode {
    string value;
    int balanceFactor;
    TreeNode *parent;
    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode(string value, TreeNode *parent = NULL, TreeNode *left = NULL, TreeNode *right = NULL) {
        this->value = value;
        this->balanceFactor = 0;
        this->parent = parent;
        this->leftChild = left;
        this->rightChild = right;
    }

    // Node function for ease of code and reuse
    // If node has no parent, then it is a root
    bool isRoot() {
        return !this->parent;
    }
    // If node has no children, then it is a leaf
    bool isLeaf() {
        return !(this->rightChild || this->leftChild);
    }
    // If node has a parent and the parent node has the left child pointing to this, then this node is a left child
    bool isLeftChild() {
        return this->parent && this->parent->leftChild == this;
    }
    // If node has a parent and the parent node has the right child pointing to this, then this node is a right child
    bool isRightChild() {
        return this->parent && this->parent->rightChild == this;
    }
    // If node has any child
    bool hasAnyChildren() {
        return this->rightChild || this->leftChild;
    }
    // If node has both child
    bool hasBothChildren() {
        return this->rightChild && this->leftChild;
    }
    // If node has left child
    bool hasLeftChild() {
        return this->leftChild;
    }
    // If node has right child
    bool hasRightChild() {
        return this->rightChild;
    }
};
