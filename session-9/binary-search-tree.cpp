#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node *root = nullptr;

void insertNode(int data) {
    Node *newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    
    if (root == nullptr) {
        root = newNode;
        return;
    }
    
    Node *current = root;
    Node *parent = nullptr;
    
    while (current != nullptr) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

void inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

void preOrderTraversal(Node* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void postOrderTraversal(Node* node) {
    if (node != nullptr) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->data << " ";
    }
}

void displayTree(Node* node, string prefix = "", bool isLeft = true) {
    if (node == nullptr) {
        return;
    }
    
    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << node->data << endl;
    
    if (node->left != nullptr || node->right != nullptr) {
        if (node->left != nullptr) {
            displayTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
        }
        if (node->right != nullptr) {
            displayTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }
}

int main() {
    insertNode(10);
    insertNode(8);
    insertNode(13);
    insertNode(4);
    insertNode(9);
    insertNode(12);
    insertNode(14);
    insertNode(17);
    insertNode(15);

    cout << "Tree Structure:" << endl;
    displayTree(root);
    cout << endl;
    
    cout << "Pre-order Traversal: ";
    preOrderTraversal(root);
    cout << endl;

    cout << "In-order Traversal: ";
    inorderTraversal(root);
    cout << endl;
     
    cout << "Post-order Traversal: ";
    postOrderTraversal(root);
    cout << endl;
    
    return 0;
}