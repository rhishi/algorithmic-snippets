#include "binarytreeexamples.h"

BinaryTreeNode* SimpleThreeBinaryTree() {
    BinaryTreeNode* root = new BinaryTreeNode { 1 };
    BinaryTreeNode* left = new BinaryTreeNode { 2 };
    BinaryTreeNode* right = new BinaryTreeNode { 3 };

    root->left = left;
    root->right = right;

    return root;
}

BinaryTreeNode* SimpleFourBinaryTree() {
    return new BinaryTreeNode { 1,
        new BinaryTreeNode { 2 },
        new BinaryTreeNode { 3,
            new BinaryTreeNode { 4 },
            nullptr
        }
    };
}

BinaryTreeNode* SimpleFiveBinaryTree() {
    BinaryTreeNode* root = nullptr;

    root = BinaryTreeAddNewNode(root, 1, "");
    root = BinaryTreeAddNewNode(root, 2, "l");
    root = BinaryTreeAddNewNode(root, 3, "r");
    root = BinaryTreeAddNewNode(root, 4, "ll");
    root = BinaryTreeAddNewNode(root, 5, "lr");

    return root;
}
