#include "binarytree.h"

// Inserts a new node in a binary tree given the root node, a value for the new
// node, and a character string denoting its position in the tree.
//
// The string must contain only characters 'l' and 'r', and each successive
// character means the direction you pick at every fork, starting from the root.
//
// The last character of the string must land you on a null node, and no sooner.
//
// If the tree structure and the position string don't match or are invalid,
// then no new node is created and you get the original tree back.
//
// Returns the (possibly) new root of the tree.
BinaryTreeNode* BinaryTreeAddNewNode(BinaryTreeNode* root, int value, const char * position) {

    // ""   means make new node and return it.         parent is null.
    // "l"  means root->left = new node, return root.  parent is root + place is 'l'
    // "r"  means root->right = new node, return root. parent is root + place is 'r'
    // "lr" means root->left->right = new node, return root.  parent is root->left + place is 'r'

    BinaryTreeNode* parent = nullptr;
    char place;

    BinaryTreeNode* nodePosition = root;
    char pos;
    for (pos = *position; pos != '\0' && nodePosition != nullptr; pos = *++position) {
        place = pos;
        parent = nodePosition;
        if (pos == 'l') {
            nodePosition = nodePosition->left;
        } else if (pos == 'r') {
            nodePosition = nodePosition->right;
        } else {
            return root;
        }
    }

    // if pos isn't null char, there is more string;
    // if nodePosition is not null ptr, there is more tree.
    // Both are mismatches that are treated as errors.
    if (pos != '\0' || nodePosition != nullptr) {
        return root;
    }

    // for the insertion at the computed position, use the parent and the place.

    BinaryTreeNode* node = new BinaryTreeNode { value, nullptr, nullptr };

    if (parent == nullptr) {
        return node;
    }

    if (place == 'l') {
        parent->left = node;
    } else if (place == 'r') {
        parent->right = node;
    }
    return root;
}

std::string BinaryTreePreOrderString(BinaryTreeNode* root) {
    if (root == nullptr) return "";

    return std::to_string(root->value) + " "
        + BinaryTreePreOrderString(root->left)
        + BinaryTreePreOrderString(root->right);
}
