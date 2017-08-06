#include <string>
#include <sstream>
#include "binarytreeexamples.h"

BinaryTreeNode* BinaryTreeFromValuePositionListString(const std::string& str);

// -----------------------------------------------------------------------------
// Three simple binary trees constructed in three different ways

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

// -----------------------------------------------------------------------------
// Examples from Victor Adamchik's CS 15-121 Fall 2009 at CMU
// https://www.cs.cmu.edu/~adamchik/15-121/lectures/Trees/trees.html

// A random 6-node binary tree
// 1 { 2 4 } { 3 5 6 }
BinaryTreeNode* SimpleSixBinaryTree() {
    return BinaryTreeFromValuePositionListString(
        "1 \
         2 l \
         3 r \
         4 ll \
         5 rl \
         6 rr");
}

// A full binary tree (and also a faux binary search tree)
// 3  { 2 1 { 4 1 5 } }  4
BinaryTreeNode* SimpleFullBinaryTree() {
    return BinaryTreeFromValuePositionListString(
        "3 \
         4 r \
         2 l \
         1 ll \
         4 lr \
         1 lrl \
         5 lrr");
}

// A complete binary tree
// 5  { 3 { 3 5 2 } 4 }  { 4 5 6 }
BinaryTreeNode* SimpleCompleteBinaryTree() {
    return BinaryTreeFromValuePositionListString(
        "5 \
         3 l \
         4 r \
         6 rr \
         5 rl \
         4 lr \
         3 ll \
         5 lll \
         2 llr");
}

// A random 10-node binary tree
// 8 { 5
//     9
//     { 7 1 { 6 2 } }
//   }
//   { 4
//     { }
//     { 5 3 }
//   }
BinaryTreeNode* SimpleTenBinaryTree() {
    return BinaryTreeFromValuePositionListString(
        "8 \
         5 l \
         9 ll \
         7 lr \
         1 lrl \
         6 lrr \
         2 lrrl \
         4 r \
         5 rr \
         3 rrl");
}

// -----------------------------------------------------------------------------

BinaryTreeNode* BinaryTreeFromValuePositionListString(const std::string& str) {
    std::istringstream in { str };
    int value;
    std::string position;
    BinaryTreeNode* root = nullptr;
    if (in) {
        in >> value;
        root = BinaryTreeAddNewNode(root, value, "");
    }
    while (in) {
        in >> value >> position;
        root = BinaryTreeAddNewNode(root, value, position.c_str());
    }
    return root;
}
