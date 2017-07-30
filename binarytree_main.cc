#include <iostream>
#include "binarytree.h"
#include "binarytreeexamples.h"

void PrintPreOrder(BinaryTreeNode* root);
void PrintInOrder(BinaryTreeNode* root);
void PrintPostOrder(BinaryTreeNode* root);

int main() {

    // print pre-order
    // 1 2 3
    // 1 2 3 4
    // 1 2 4 5 3
    PrintPreOrder(SimpleThreeBinaryTree());
    PrintPreOrder(SimpleFourBinaryTree());
    PrintPreOrder(SimpleFiveBinaryTree());
    std::cout << std::endl;

    // print in-order
    // 2 1 3
    // 2 1 4 3
    // 4 2 5 1 3
    PrintInOrder(SimpleThreeBinaryTree());
    PrintInOrder(SimpleFourBinaryTree());
    PrintInOrder(SimpleFiveBinaryTree());
    std::cout << std::endl;

    // print post-order
    // 2 3 1
    // 2 4 3 1
    // 4 5 2 3 1
    PrintPostOrder(SimpleThreeBinaryTree());
    PrintPostOrder(SimpleFourBinaryTree());
    PrintPostOrder(SimpleFiveBinaryTree());
    std::cout << std::endl;

    return 0;
}

void PrintPreOrder(BinaryTreeNode* root) {
    BinaryTreePrintPreOrderRecursive(root, std::cout);
    std::cout << std::endl;
}

void PrintInOrder(BinaryTreeNode* root) {
    BinaryTreePrintInOrderRecursive(root, std::cout);
    std::cout << std::endl;
}

void PrintPostOrder(BinaryTreeNode* root) {
    BinaryTreePrintPostOrderRecursive(root, std::cout);
    std::cout << std::endl;
}
