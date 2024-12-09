#include "functions.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Node* root = nullptr;

    cout << "=== Populating BST with random integers ===" << endl;
    root = generateRandomTree(root, 10);
    inorder(root);
    cout << endl;
    cout << "=== Running Tests on Randomly Generated Tree ===" << endl;
    runTests(root);
    cout << "=== Binary Search Tree Performance Evaluation ===" << endl;

    // Test with different numbers of nodes
    performanceTest(100);
    performanceTest(1000);
    performanceTest(10000);
    performanceTest(100000);


    return 0;
}
