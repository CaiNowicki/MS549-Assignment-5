#pragma once
#include <cstddef>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int item) {
        key = item;
        left = nullptr;
        right = nullptr;
    }
};

void inorder(Node* root);

Node* insert(Node* node, int key);

Node* getSuccessor(Node* curr);

Node* delNode(Node* root, int x);

Node* search(Node* root, int key);

int maxValue(struct Node* node);

Node* generateRandomTree(Node* root, int count);

void runTests(Node* root);
int findLeafNode(Node* root);
int findNodeWithOneChild(Node* root);
int findNodeWithTwoChildren(Node* root);
void performanceTest(int numNodes);