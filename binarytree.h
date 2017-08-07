#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <ostream>

// First, the absolute basics of C, C++.  For a node of a binary tree, we need
// a struct (or a class, but struct makes members public by default, and just
// seems more natural, small-scale).  That struct needs to refer to other two
// nodes i.e. the left and the right children.  If you attempt to declare those
// as fields of the type of the struct, then the C++ compiler will give error.
// GCC 7 says:
//   error: field 'left' has incomplete type 'BinaryTreeNode'
//   note: definition of 'struct BinaryTreeNode' is not complete until the closing brace
#if 0
struct BinaryTreeNode {
    int value;
    BinaryTreeNode left;
    BinaryTreeNode right;
};
#endif

// Making it a class doesn't fix the problem in C++, as it does in C# or Java.
// GCC 7 still gives the same error, as struct and class are quite same in C++.
// In C#, struct is a value type (like in C++) and class is a reference type.
#if 0
class BinaryTreeNode {
    int value;
    BinaryTreeNode left;
    BinaryTreeNode right;
};
#endif

// Correct struct for a node in binary tree is with two pointers pointing to the
// left and right children.
struct BinaryTreeNode {
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

BinaryTreeNode* BinaryTreeAddNewNode(BinaryTreeNode* root, int value, const char * const position);

void BinaryTreeDelete(BinaryTreeNode* root);

void BinaryTreePrintPreOrderRecursive(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintInOrderRecursive(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintPostOrderRecursive(BinaryTreeNode* root, std::ostream& os);

void BinaryTreePrintPreOrderNonRecursive(BinaryTreeNode* root, std::ostream& os);

void BinaryTreePrintInOrderNonRecursiveStackAndMap(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintInOrderNonRecursiveStackOfPair(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintPostOrderNonRecursiveStackOfPair(BinaryTreeNode* root, std::ostream& os);

void BinaryTreePrintInOrderNonRecursiveStackOfPair2(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintInOrderNonRecursiveStackOfPair3(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintInOrderNonRecursiveStackOfPair4(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintInOrderNonRecursiveStackOfPair5(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintInOrderNonRecursiveStackOfPair6(BinaryTreeNode* root, std::ostream& os);

void BinaryTreePrintInOrderNonRecursive(BinaryTreeNode* root, std::ostream& os);
void BinaryTreePrintPostOrderNonRecursive(BinaryTreeNode* root, std::ostream& os);

#endif // #ifndef BINARYTREE_H_
