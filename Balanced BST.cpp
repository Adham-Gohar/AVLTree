#include <iostream>
using namespace std;

// a structure for the AVL tree node
struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
    int count;
};

// creates a new node
Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    newNode->count = 1;
    return newNode;
}

// gets the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// updates the height of a node
void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

//gets the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// performs the left rotation
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

// Function to perform right rotation
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

// Function to balance the AVL tree
Node* balance(Node* node) {
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Function to insert a value into the AVL tree
Node* insert(Node* node, int value) {
    if (node == nullptr) {
        return createNode(value);
    }

    if (value < node->value) {
        node->left = insert(node->left, value);
    }
    else if (value > node->value) {
        node->right = insert(node->right, value);
    }
    else {
        node->count++;
        return node;
    }

    return balance(node);
}


// Function to draw the AVL tree using inorder traversal
void drawTree(Node* node, int space) {
    if (node == nullptr)
        return;

    space += 5;

    drawTree(node->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << node->value << " (" << node->count << ")" << endl;

    drawTree(node->left, space);
}

// Function to find the minimum value node in the AVL tree
Node* findMinNode(Node* node) {
    if (node == nullptr)
        return nullptr;
    if (node->left == nullptr)
        return node;
    return findMinNode(node->left);
}



// Function to find the leaf nodes of the AVL tree
void findLeafNodes(Node* node) {
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr) {
        cout << node->value << " ";
    }

    findLeafNodes(node->left);
    findLeafNodes(node->right);
}

int main() {
    int arr[] = { 9, 11, 18, 3, 4, 12, 3, 4, 2, 20 };
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    Node* root = nullptr;

    // Insert each element of the array into the AVL tree
    for (int i = 0; i < arrSize; i++) {
        root = insert(root, arr[i]);
    }

    // Draw the AVL tree
    cout << "AVL Tree:" << endl;
    drawTree(root, 0);
    cout << endl;

    // Get the height of the AVL tree
    int height = getHeight(root);

    // Find the root node of the AVL tree
    int rootValue = root->value;

    // Find the leaf nodes of the AVL tree
    cout << "Leaf Nodes: ";
    findLeafNodes(root);
    cout << endl;

    // Print the height, root value, and leaf nodes of the AVL tree
    cout << "Height: " << height << endl;
    cout << "Root: " << rootValue << endl;

    return 0;
}
