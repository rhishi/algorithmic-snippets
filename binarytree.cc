#include <ostream>
#include <stack>
#include <unordered_map>
#include <utility>
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

void BinaryTreeDelete(BinaryTreeNode* root) {
    if (root == nullptr) return;
    BinaryTreeDelete(root->left);
    BinaryTreeDelete(root->right);
    delete root;
}

void BinaryTreePrintNode(BinaryTreeNode* node, std::ostream& os) {
    os << node->value << " ";
}

// -----------------------------------------------------------------------------
// Pre-Order, In-Order, Post-Order using recursive invocation

void BinaryTreePrintPreOrderRecursive(BinaryTreeNode* root, std::ostream& os) {
    if (root == nullptr) return;

    BinaryTreePrintNode(root, os);
    BinaryTreePrintPreOrderRecursive(root->left, os);
    BinaryTreePrintPreOrderRecursive(root->right, os);
}

void BinaryTreePrintInOrderRecursive(BinaryTreeNode* root, std::ostream& os) {
    if (root == nullptr) return;

    BinaryTreePrintInOrderRecursive(root->left, os);
    BinaryTreePrintNode(root, os);
    BinaryTreePrintInOrderRecursive(root->right, os);
}

void BinaryTreePrintPostOrderRecursive(BinaryTreeNode* root, std::ostream& os) {
    if (root == nullptr) return;

    BinaryTreePrintPostOrderRecursive(root->left, os);
    BinaryTreePrintPostOrderRecursive(root->right, os);
    BinaryTreePrintNode(root, os);
}

// -----------------------------------------------------------------------------
// Pre-Order, In-Order, Post-Order non-recursive

// Pre-order using stack is easy, because it's tail recursion i.e. nothing needs
// to be done with the current node _after_ the recursive calls.  So the top of
// the stack is popped, printed, and its children are added to the stack.
void BinaryTreePrintPreOrderNonRecursive(BinaryTreeNode* root, std::ostream& os) {
    std::stack<BinaryTreeNode*> stack;

    if (root != nullptr) {
        stack.push(root);
    }

    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();

        BinaryTreePrintNode(node, os);

        if (node->right != nullptr) {
            stack.push(node->right);
        }
        if (node->left != nullptr) {
            stack.push(node->left);
        }
    }
}

// In-order using stack is tricky.  First attempt is to maintain extra state for
// the nodes on the stack.  How to store this state?  Here we use a map, but
// better would be to pair up the state with the node pointer on the stack.
// State means:
// 0: neither children have been added to the stack yet
// 1: the left child was added to the stack
// 2: the right child was added to the stack
void BinaryTreePrintInOrderNonRecursiveStackAndMap(BinaryTreeNode* root, std::ostream& os) {
    std::stack<BinaryTreeNode*> stack;
    std::unordered_map<BinaryTreeNode*, int> state;

    if (root != nullptr) {
        stack.push(root);
        state[root] = 0;
    }

    while (!stack.empty()) {
        auto node = stack.top();

        if (state[node] == 0) {
            if (node->left != nullptr) {
                stack.push(node->left);
                state[node->left] = 0;
            }
            state[node] = 1;
        } else if (state[node] == 1) {
            BinaryTreePrintNode(node, os);
            if (node->right != nullptr) {
                stack.push(node->right);
                state[node->right] = 0;
            }
            state[node] = 2;
        } else {
            stack.pop();
        }
    }
}

// In-order using stack of node & state.  The state is useful only while the
// node is on the stack, so no point wasting memory for a map of node to state.
// State still means:
// 0: neither children have been added to the stack yet
// 1: the left child was added to the stack
// 2: the right child was added to the stack
void BinaryTreePrintInOrderNonRecursiveStackOfPair(BinaryTreeNode* root, std::ostream& os) {
    std::stack<std::pair<BinaryTreeNode*, int>> stack;

    if (root != nullptr) {
        stack.push({root, 0});
    }

    while (!stack.empty()) {
        auto& pair = stack.top();
        auto node = pair.first;
        auto& state = pair.second;

        if (state == 0) {
            if (node->left != nullptr) {
                stack.push({node->left, 0});
            }
            state = 1;
        } else if (state == 1) {
            BinaryTreePrintNode(node, os);
            if (node->right != nullptr) {
                stack.push({node->right, 0});
            }
            state = 2;
        } else {
            stack.pop();
        }
    }
}

// Post-order using stack of node & state.  This illustrates why our template
// used three states, even though the in-order could be done with just two.
// Here's another interpretation of state:
//   Imagine the children of a node are stored in array { left, right }.
//   state is then the index of the child to be put on the stack next:
//   0 means the left child is to be put on the stack.
//   1 means the right child is to be put on the stack.
//   2 equals the size of the children array, so done with all the children.
void BinaryTreePrintPostOrderNonRecursiveStackOfPair(BinaryTreeNode* root, std::ostream& os) {
    std::stack<std::pair<BinaryTreeNode*, int>> stack;

    if (root != nullptr) {
        stack.push({root, 0});
    }

    while (!stack.empty()) {
        auto& pair = stack.top();
        auto node = pair.first;
        auto& state = pair.second;

        if (state == 0) {
            if (node->left != nullptr) {
                stack.push({node->left, 0});
            }
            state = 1;
        } else if (state == 1) {
            if (node->right != nullptr) {
                stack.push({node->right, 0});
            }
            state = 2;
        } else {
            BinaryTreePrintNode(node, os);
            stack.pop();
        }
    }
}

// In-order using stack of node & state, with only two states used, not three.
void BinaryTreePrintInOrderNonRecursiveStackOfPair2(BinaryTreeNode* root, std::ostream& os) {
    std::stack<std::pair<BinaryTreeNode*, int>> stack;

    if (root != nullptr) {
        stack.push({root, 0});
    }

    while (!stack.empty()) {
        auto& pair = stack.top();
        auto node = pair.first;
        auto& state = pair.second;

        if (state == 0) {
            if (node->left != nullptr) {
                stack.push({node->left, 0});
            }
            state = 1;
        } else if (state == 1) {
            stack.pop();
            BinaryTreePrintNode(node, os);
            if (node->right != nullptr) {
                stack.push({node->right, 0});
            }
        }
    }
}

// In in-order using stack of node & state, a node transitions from state 0 to
// state 1 almost immediately.  So then, can one get rid of state 0 and go
// directly to state 1?   But then node->left needs to be put on the stack, and
// if node->left is to be on the stack with state 1, then node->left->left
// needs to be on the stack.  And so on!  So the solution is to replace every
// push with a loop that pushes the entire chain of left children onto the stack.
void BinaryTreePrintInOrderNonRecursiveStackOfPair3(BinaryTreeNode* root, std::ostream& os) {
    std::stack<std::pair<BinaryTreeNode*, int>> stack;

    auto node = root;
    while (node != nullptr) {
        stack.push({node, 1});
        node = node->left;
    }

    while (!stack.empty()) {
        auto& pair = stack.top();
        auto node = pair.first;
        auto& state = pair.second;

        if (state == 0) {
            node = node->left;
            while (node != nullptr) {
                stack.push({node, 1});
                node = node->left;
            }
            state = 1;
        } else if (state == 1) {
            stack.pop();
            BinaryTreePrintNode(node, os);
            node = node->right;
            while (node != nullptr) {
                stack.push({node, 1});
                node = node->left;
            }
        }
    }
}

// The state is never going to be 0.  So remove the if (state == 0) branch.
void BinaryTreePrintInOrderNonRecursiveStackOfPair4(BinaryTreeNode* root, std::ostream& os) {
    std::stack<std::pair<BinaryTreeNode*, int>> stack;

    auto node = root;
    while (node != nullptr) {
        stack.push({node, 1});
        node = node->left;
    }

    while (!stack.empty()) {
        auto& pair = stack.top();
        auto node = pair.first;
        auto& state = pair.second;

        if (state == 1) {
            stack.pop();
            BinaryTreePrintNode(node, os);
            node = node->right;
            while (node != nullptr) {
                stack.push({node, 1});
                node = node->left;
            }
        }
    }
}

// The state is always going to be 1.  So remove the if (state == 1) check.
void BinaryTreePrintInOrderNonRecursiveStackOfPair5(BinaryTreeNode* root, std::ostream& os) {
    std::stack<std::pair<BinaryTreeNode*, int>> stack;

    auto node = root;
    while (node != nullptr) {
        stack.push({node, 1});
        node = node->left;
    }

    while (!stack.empty()) {
        auto& pair = stack.top();
        auto node = pair.first;

        stack.pop();
        BinaryTreePrintNode(node, os);
        node = node->right;
        while (node != nullptr) {
            stack.push({node, 1});
            node = node->left;
        }
    }
}

// The state is never used.  So get rid of it.
void BinaryTreePrintInOrderNonRecursiveStackOfPair6(BinaryTreeNode* root, std::ostream& os) {
    std::stack<BinaryTreeNode*> stack;

    auto node = root;
    while (node != nullptr) {
        stack.push(node);
        node = node->left;
    }

    while (!stack.empty()) {
        auto node = stack.top();

        stack.pop();
        BinaryTreePrintNode(node, os);
        node = node->right;
        while (node != nullptr) {
            stack.push(node);
            node = node->left;
        }
    }
}

// In-order using stack & one extra pointer.  Rearrangement of the multiple while
// loops above.  Matches the version on Wikipedia https://en.wikipedia.org/wiki/Tree_traversal.
void BinaryTreePrintInOrderNonRecursive(BinaryTreeNode* root, std::ostream& os) {
    std::stack<BinaryTreeNode*> stack;

    auto node = root;
    while (node != nullptr || !stack.empty()) {
        if (node != nullptr) {
            stack.push(node);
            node = node->left;
        } else {
            auto top = stack.top();
            stack.pop();
            BinaryTreePrintNode(top, os);
            node = top->right;
        }
    }
}

// Post-order using stack & two extra pointers.  Matches the version on Wikipedia
// https://en.wikipedia.org/wiki/Tree_traversal.
void BinaryTreePrintPostOrderNonRecursive(BinaryTreeNode* root, std::ostream& os) {
    std::stack<BinaryTreeNode*> stack;

    auto node = root;
    BinaryTreeNode* prev = nullptr;
    while (node != nullptr || !stack.empty()) {
        if (node != nullptr) {
            stack.push(node);
            node = node->left;
        } else {
            auto top = stack.top();
            if (top->right == nullptr || top->right == prev) {
                stack.pop();
                BinaryTreePrintNode(top, os);
                prev = top;
            } else {
                node = top->right;
            }
        }
    }
}
