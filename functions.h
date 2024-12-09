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

