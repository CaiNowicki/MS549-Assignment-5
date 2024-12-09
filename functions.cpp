#include "functions.h"

#include <iostream>
#include <chrono>
using namespace std;

//code snippet from https://www.geeksforgeeks.org/insertion-in-binary-search-tree

// A utility function to insert a new node with 
// the given key
Node* insert(Node* node, int key) {

    // If the tree is empty, return a new node
    if (node == NULL)
        return new Node(key);

    // If the key is already present in the tree,
    // return the node
    if (node->key == key)
        return node;

    // Otherwise, recur down the tree/ If the key
    // to be inserted is greater than the node's key,
    // insert it in the right subtree
    if (node->key < key)
        node->right = insert(node->right, key);

    // If the key to be inserted is smaller than 
    // the node's key,insert it in the left subtree
    else
        node->left = insert(node->left, key);

    // Return the (unchanged) node pointer
    return node;
}

// A utility function to do inorder tree traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
//end code snippet

//code snippet from https://www.geeksforgeeks.org/deletion-in-binary-search-tree/


// Note that it is not a generic inorder
// successor function. It mainly works
// when right child is not empty which is 
// the case wwe need in BST delete
Node* getSuccessor(Node* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

// This function deletes a given key x from
// the give BST and returns modified root of
// the BST (if it is modified)
Node* delNode(Node* root, int x) {

    // Base case
    if (root == nullptr)
        return root;

    // If key to be searched is in a subtree
    if (root->key > x)
        root->left = delNode(root->left, x);
    else if (root->key < x)
        root->right = delNode(root->right, x);

    // If root matches with the given key
    else {

        // Cases when root has 0 children
        // or only right child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // When root has only left child
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // When both children are present
        Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right, succ->key);
    }
    return root;
}
//end code snippet

//code snippet from https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion

// function to search a key in a BST
Node* search(Node* root, int key) {

    // Base Cases: root is null or key 
    // is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}
//end code snippet

// code snippet from https://www.geeksforgeeks.org/find-the-node-with-maximum-value-in-a-binary-search-tree/
// Function to find the node with maximum value
// i.e. rightmost leaf node
int maxValue(struct Node* node)
{
    /* loop down to find the rightmost leaf */
    Node* current = node;
    while (current->right != nullptr)
        current = current->right;

    return (current->key);
}

//end code snippet

Node* generateRandomTree(Node* root, int count) {
    srand(time(nullptr));
    for (int i = 0; i < count; ++i) {
        int num = rand() % 1000; // Random integers between 0 and 999
        cout << "Inserting: " << num << endl;
        root = insert(root, num);
    }
    return root;
}

void runTests(Node* root) {
    if (!root) {
        cout << "Error: Tree is empty. Populate the tree before running tests." << endl;
        return;
    }

    cout << "=== Initial In-Order Traversal of Randomly Generated Tree ===" << endl;
    inorder(root);
    cout << endl;

    cout << "=== Test 1: Attempting to remove a node from an empty BST ===" << endl;
    Node* emptyTree = nullptr;
    emptyTree = delNode(emptyTree, 10); // Should gracefully handle empty tree
    cout << "Result: No errors encountered when removing from an empty BST." << endl;

    cout << "=== Test 2: Attempting to insert a duplicate value ===" << endl;
    int duplicateValue = root->key; // Use the root's value as a duplicate
    cout << "Inserting duplicate value: " << duplicateValue << endl;
    root = insert(root, duplicateValue);
    inorder(root);
    cout << endl;

    cout << "=== Test 3: Removing a node with no children ===" << endl;
    int leafNode = findLeafNode(root); // Helper function to find a leaf node
    cout << "Removing leaf node: " << leafNode << endl;
    root = delNode(root, leafNode);
    inorder(root);
    cout << endl;

    cout << "=== Test 4: Removing a node with one child ===" << endl;
    int oneChildNode = findNodeWithOneChild(root); // Helper to find such a node
    if (oneChildNode != -1) {
        cout << "Removing node with one child: " << oneChildNode << endl;
        root = delNode(root, oneChildNode);
        inorder(root);
        cout << endl;
    }
    else {
        cout << "No nodes with one child were found in the current tree." << endl;
    }

    cout << "=== Test 5: Removing a node with two children ===" << endl;
    int twoChildrenNode = findNodeWithTwoChildren(root); // Helper to find such a node
    if (twoChildrenNode != -1) {
        cout << "Removing node with two children: " << twoChildrenNode << endl;
        root = delNode(root, twoChildrenNode);
        inorder(root);
        cout << endl;
    }
    else {
        cout << "No nodes with two children were found in the current tree." << endl;
    }

    cout << "=== Final In-Order Traversal After All Tests ===" << endl;
    inorder(root);
    cout << endl;
}

// Example helper functions to find specific types of nodes
int findLeafNode(Node* root) {
    if (!root) return -1;
    if (!root->left && !root->right) return root->key;
    int leftResult = root->left ? findLeafNode(root->left) : -1;
    int rightResult = root->right ? findLeafNode(root->right) : -1;
    return leftResult != -1 ? leftResult : rightResult;
}

int findNodeWithOneChild(Node* root) {
    if (!root) return -1;
    if ((root->left && !root->right) || (!root->left && root->right)) return root->key;
    int leftResult = findNodeWithOneChild(root->left);
    int rightResult = findNodeWithOneChild(root->right);
    return leftResult != -1 ? leftResult : rightResult;
}

int findNodeWithTwoChildren(Node* root) {
    if (!root) return -1;
    if (root->left && root->right) return root->key;
    int leftResult = findNodeWithTwoChildren(root->left);
    int rightResult = findNodeWithTwoChildren(root->right);
    return leftResult != -1 ? leftResult : rightResult;
}

void performanceTest(int numNodes) {
    Node* root = nullptr;
    srand(time(nullptr));

    cout << "Testing insertion performance for " << numNodes << " nodes..." << endl;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numNodes; ++i) {
        int randomValue = rand() % 10000;
        root = insert(root, randomValue);
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Time taken to insert " << numNodes << " nodes: "
        << elapsed.count() << " seconds" << endl;

}