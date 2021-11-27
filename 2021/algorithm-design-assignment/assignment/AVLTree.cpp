// AVLTree.cpp
// Balanced Search Tree (AVL)
// Derived from Runestone
// https://runestone.academy/runestone/books/published/cppds/Trees/BinarySearchTrees.html

// For debugging, remove comment off cout line

#include <iostream>
#include "TreeNode.cpp"
using namespace std;

class AVLTree {
    TreeNode *root; // see TreeNode.cpp for details
    int size;

     /* Search through tree and compare the new value with the current node value.
        If the new value is lesser than the current node, search the left subtree.
        If the new value is greater than the current node, search the right subtree.
        If the current node does not have left or right child, then the new node can be inserted into the empty child. */
    void insert(string value, TreeNode *curNode) {
        // cout << "Inside Node: " << curNode->value << endl;
        if (value < curNode->value) {
            // cout << value << " < " << curNode->value << endl;
            if (curNode->hasLeftChild()) {
                // cout << " To left\n";
                this->insert(value, curNode->leftChild);
            }
            else {
                curNode->leftChild = new TreeNode(value, curNode);
                // cout << " >> Left <<\n";
                this->updateBalance(curNode->leftChild);
            }
        }
        else {
            // cout << value << " >= " << curNode->value << endl;
            if (curNode->hasRightChild()) {
                // cout << " To right\n";
                this->insert(value, curNode->rightChild);
            }
            else {
                curNode->rightChild = new TreeNode(value, curNode);
                // cout << " >> Right <<\n";
                this->updateBalance(curNode->rightChild);
            }
        }
    }
     /* Update balance for every insertion and check for rebalance
        If the node is a left child, update the parent node balance factor by -1
        If the node is a right child, update the parent node balance factor by +1
        Then check for balance factor of the parent node, if it is not 0 then check/update balance of the parent node
        If the node balance factor is more than 1 or less than -1, then the node will require to be balanced
        Balance factor visualisation:
            node -> 0

            node -> -1
            /
         node

            node -> +1
               \
                node

            node -> 0
            /  \
        node    node

            node -> -2 (Require R Rotation)
            /
         node -> -1
         /
      node

            node -> +2 (Require L Rotation)
               \
                node -> +1
                   \
                   node

            node -> -2 (Require LR Rotation)
            /
         node -> +1 (rotate L this first)
            \
            node

            node -> +2 (Require RL Rotation)
               \
                node -> -1 (rotate R this first)
                /
            node
        */
    void updateBalance(TreeNode *node) {
        if (node->balanceFactor > 1 || node->balanceFactor < -1) {
            // cout << " ## Tree is not balanced ##\n";
            this->rebalance(node);
            return;
        }
        if (node->parent != NULL) {
            if (node->isLeftChild()) {
                node->parent->balanceFactor += 1;
            }
            else if (node->isRightChild()) {
                node->parent->balanceFactor -= 1;
            }
            if (node->parent->balanceFactor != 0) {
                // recursion
                this->updateBalance(node->parent);
            }
        }
    }
    void rebalance(TreeNode *node) {
        // cout << " Balance: " << node->balanceFactor;
        if (node->balanceFactor < 0) {
            // cout << " < 0\n";
            if (node->rightChild->balanceFactor > 0) {
                // cout << " Initiate Right-Left Rotation\n";
                this->rotateRight(node->rightChild);
                this->rotateLeft(node);
            }
            else {
                // cout << " Initiate Single Left Rotation\n";
                this->rotateLeft(node);
            }
        }
        else if (node->balanceFactor > 0) {
            // cout << " > 0\n";
            if (node->leftChild->balanceFactor < 0) {
                // cout << " Initiate Left-Right Rotation\n";
                this->rotateLeft(node->leftChild);
                this->rotateRight(node);
            }
            else {
                // cout << " Initiate Single Right Rotation\n";
                this->rotateRight(node);
            }
        }
    }
     // Rotate left
     // I can't visualise this properly so hopefully explanation works
    void rotateLeft(TreeNode *rotNode) {
        // cout << " > Left Rotation\n";
        TreeNode *newNode = rotNode->rightChild;

        // newNode's left child points to rotNode's right child
        rotNode->rightChild = newNode->leftChild;
        // if newNode's left child exist, then point newNode's left child's parent to rotNode
        if (newNode->leftChild != NULL)
            newNode->leftChild->parent = rotNode;

        // newNode's parent points to rotNode's parent
        newNode->parent = rotNode->parent;
        // If the newNode is root (parent is NULL), then point this AVLTree root to newNode
        if (rotNode->isRoot())
            this->root = newNode;
        else {
            // If rotNode is left child, then point rotNode's parent's left child to newNode
            if (rotNode->isLeftChild())
                rotNode->parent->leftChild = newNode;
            // If rotNode is right child, then point rotNode's parent's right child to newNode
            else
                rotNode->parent->rightChild = newNode;
        }

        // perform rotation
        newNode->leftChild = rotNode;
        rotNode->parent = newNode;

        // update balance
        rotNode->balanceFactor = rotNode->balanceFactor + 1 - min(newNode->balanceFactor, 0);
        newNode->balanceFactor = newNode->balanceFactor + 1 + max(rotNode->balanceFactor, 0);
        // for verification reason
        // cout << "  -> Previous node balance factor: " << rotNode->balanceFactor << endl;
        // cout << "  -> New node balance factor: " << newNode->balanceFactor << endl;
    }
    // similar concept as to left rotation
    void rotateRight(TreeNode *rotNode) {
        // cout << " > Right Rotation\n";
        TreeNode *newNode = rotNode->leftChild;

        rotNode->leftChild = newNode->rightChild;
        if (newNode->rightChild != NULL)
            newNode->rightChild->parent = rotNode;

        newNode->parent = rotNode->parent;
        if (rotNode->isRoot())
            this->root = newNode;
        else {
            if (rotNode->isLeftChild())
                rotNode->parent->leftChild = newNode;
            else
                rotNode->parent->rightChild = newNode;
        }

        // perform rotation
        newNode->rightChild = rotNode;
        rotNode->parent = newNode;

        // update balance
        rotNode->balanceFactor = rotNode->balanceFactor - 1 - max(newNode->balanceFactor, 0);
        newNode->balanceFactor = newNode->balanceFactor - 1 + min(rotNode->balanceFactor, 0);
        // cout << "  -> Previous node balance factor: " << rotNode->balanceFactor << endl;
        // cout << "  -> New node balance factor: " << newNode->balanceFactor << endl;
    }
    // Search through tree by recursion, return pointer value
    TreeNode *get(string value, TreeNode *curNode) {
        if (!curNode)
            return NULL;
        else if (curNode->value == value)
            return curNode;
        else if (value < curNode->value)
            return this->get(value, curNode->leftChild);
        else
            return this->get(value, curNode->rightChild);
    }
    // Get the height of the tree
    int height(TreeNode *curNode) {
        if (!curNode) return 0;
        return 1 + max(height(curNode->leftChild), height(curNode->rightChild));
    }
    // Recursive function for display
    void inorder(TreeNode *curNode) {
        if (!curNode) return; // The node does not exist
        inorder(curNode->leftChild);
        cout << curNode-> value << " ";
        inorder(curNode->rightChild);
    }
    void preorder(TreeNode *curNode) {
        if (!curNode) return;
        cout << curNode-> value << " ";
        preorder(curNode->leftChild);
        preorder(curNode->rightChild);
    }
    void postorder(TreeNode *curNode) {
        if (!curNode) return;
        postorder(curNode->leftChild);
        postorder(curNode->rightChild);
        cout << curNode-> value << " ";
    }
    void levelorder(TreeNode* curNode, int level) {
        if (!curNode) return;
        if (level == 1)
            cout << curNode->value << " ";
        else if (level > 1) {
            levelorder(curNode->leftChild, level-1);
            levelorder(curNode->rightChild, level-1);
        }
    }
public:
    AVLTree() {
        this->root = NULL;
        this->size = 0;
    }
    int length() {
        return size;
    }
     /* Insert value into tree
        If the root (tree) exist, then search through node and insert
        Otherwise, create new root (tree) */
    void insert(string value) {
        if (this->root)
            this->insert(value, this->root);
        else
            this->root = new TreeNode(value);
        this->size = this->size + 1;
        // cout << "\n-> New Root: " << this->root->value << endl;
    }
     /* Search for value inside tree
        Similar method as insertion */
    string get(string value){
        if (this->root) {
            TreeNode *node = this->get(value, this->root);
            if (node)
                return node->value;
            return "Could not be found.";
        }
        return "BST is empty.";
    }
     /* Display tree with different traversal
        0: In order traversal
        1: Pre order traversal
        2: Post order traversal
        3: Level order traversal */
    void display(int d) {
        if (!this->root) { // if root returns null, tree is empty
            cout << "Tree is empty." << endl;
            return;
        }
        switch (d) {
        case 0:
            inorder(this->root);
            break;
        case 1:
            preorder(this->root);
            break;
        case 2:
            postorder(this->root);
            break;
        case 3:
            int h = height(this->root);
            for (int i = 0; i < h; i++) {
                levelorder(this->root, i+1);
                cout << endl; // remove or comment this out to see in one line
            }
            break;
        }
    }
};

/*
int main() {
    AVLTree avl;
    // string arr[] = {"A","J","H","F","B","E","I","D","C","G"};
    // string arr[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    string arr[] = {"Z","Y","X","W","V","U","T","S","R","Q","P","O","N","M","L","K","J","I","H","G","F","E","D","C","B","A"};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        // cout << "Insert [ " << arr[i] << " ]" << endl;
        avl.insert(arr[i]);
    }
    cout << endl;

    // 0 - inorder
    // 1 - preorder
    // 2 - postorder
    // 3 - levelorder
    avl.display(3);

    return 0;
} // for testing reason due to numerous issues encountered */
