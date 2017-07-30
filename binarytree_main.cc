#include "binarytree.h"
#include <iostream>

BinaryTreeNode* MakeSimpleThreeTree();
BinaryTreeNode* MakeSimpleFourTree();
BinaryTreeNode* MakeSimpleFiveTree();

int main() {

    // prints pre-order
    // 1 2 3
    // 1 2 3 4
    // 1 2 4 5 3
    BinaryTreePrintPreOrderRecursive(MakeSimpleThreeTree());
    std::cout << std::endl;
    BinaryTreePrintPreOrderRecursive(MakeSimpleFourTree());
    std::cout << std::endl;
    BinaryTreePrintPreOrderRecursive(MakeSimpleFiveTree());
    std::cout << std::endl;
    std::cout << std::endl;

    // prints in-order
    // 2 1 3
    // 2 1 4 3
    // 4 2 5 1 3
    BinaryTreePrintInOrderRecursive(MakeSimpleThreeTree());
    std::cout << std::endl;
    BinaryTreePrintInOrderRecursive(MakeSimpleFourTree());
    std::cout << std::endl;
    BinaryTreePrintInOrderRecursive(MakeSimpleFiveTree());
    std::cout << std::endl;
    std::cout << std::endl;

    // prints post-order
    // 2 3 1
    // 2 4 3 1
    // 4 5 2 3 1
    BinaryTreePrintPostOrderRecursive(MakeSimpleThreeTree());
    std::cout << std::endl;
    BinaryTreePrintPostOrderRecursive(MakeSimpleFourTree());
    std::cout << std::endl;
    BinaryTreePrintPostOrderRecursive(MakeSimpleFiveTree());
    std::cout << std::endl;
    std::cout << std::endl;

    // prints
    // 1 2 3
    // 1 2 3 4
    // 1 2 4 5 3
    BinaryTreePrintPreOrderNonRecursive(MakeSimpleThreeTree());
    std::cout << std::endl;
    BinaryTreePrintPreOrderNonRecursive(MakeSimpleFourTree());
    std::cout << std::endl;
    BinaryTreePrintPreOrderNonRecursive(MakeSimpleFiveTree());
    std::cout << std::endl;

    return 0;
}

BinaryTreeNode* MakeSimpleThreeTree() {
    BinaryTreeNode* root = new BinaryTreeNode { 1 };
    BinaryTreeNode* left = new BinaryTreeNode { 2 };
    BinaryTreeNode* right = new BinaryTreeNode { 3 };

    root->left = left;
    root->right = right;

    return root;
}

BinaryTreeNode* MakeSimpleFourTree() {
    return new BinaryTreeNode { 1,
        new BinaryTreeNode { 2 },
        new BinaryTreeNode { 3,
            new BinaryTreeNode { 4 },
            nullptr
        }
    };
}

BinaryTreeNode* MakeSimpleFiveTree() {
    BinaryTreeNode* root = nullptr;

    root = BinaryTreeAddNewNode(root, 1, "");
    root = BinaryTreeAddNewNode(root, 2, "l");
    root = BinaryTreeAddNewNode(root, 3, "r");
    root = BinaryTreeAddNewNode(root, 4, "ll");
    root = BinaryTreeAddNewNode(root, 5, "lr");

    return root;
}
