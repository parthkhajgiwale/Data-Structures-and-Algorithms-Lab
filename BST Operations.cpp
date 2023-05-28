/*Beginning with an empty binary search tree, Construct binary search tree by inserting the values
in the order given. After constructing a binary tree -
i. Insert new node
ii. Find number of nodes in longest path from root
iii. Minimum data value found in the tree
iv. Change a tree so that the roles of the left and right pointers are swapped at every
node
v. Search a value.*/

#include <iostream>
using namespace std;

// Binary Search Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = new Node();
    if (newNode == nullptr) {
        cout << "Memory allocation failed!" << endl;
        return nullptr;
    }
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a node in BST
Node* insertNode(Node* root, int value) {
    if (root == nullptr) {
        root = createNode(value);
        return root;
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Function to find the number of nodes in the longest path from the root
int findMaxDepth(Node* root) {
    if (root == nullptr)
        return 0;
    else {
        int leftDepth = findMaxDepth(root->left);
        int rightDepth = findMaxDepth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
}

// Function to find the minimum value in BST
int findMinValue(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return -1;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

// Function to swap left and right pointers at every node in BST
Node* swapTreePointers(Node* root) {
    if (root == nullptr)
        return nullptr;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    swapTreePointers(root->left);
    swapTreePointers(root->right);
    return root;
}

// Function to search for a value in BST
bool searchValue(Node* root, int value) {
    if (root == nullptr)
        return false;
    if (root->data == value)
        return true;
    if (value < root->data)
        return searchValue(root->left, value);
    else
        return searchValue(root->right, value);
}

// Function to display the BST in Inorder traversal
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\n------------------------" << endl;
    cout << "Binary Search Tree Menu" << endl;
    cout << "------------------------" << endl;
    cout << "1. Insert Node" << endl;
    cout << "2. Find Number of Nodes in Longest Path from Root" << endl;
    cout << "3. Find Minimum Value in the Tree" << endl;
    cout << "4. Swap the Roles of Left and Right Pointers" << endl;
    cout << "5. Search a Value" << endl;
    cout << "6. Display Tree (Inorder Traversal)" << endl;
    cout << "7. Exit" << endl;
    cout << "------------------------" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Node* root = nullptr;
    int choice, value;
    bool exitMenu = false;

    while (!exitMenu) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                root = insertNode(root, value);
                cout << "Node inserted successfully." << endl;
                break;
            case 2:
                cout << "Number of nodes in the longest path from root: " << findMaxDepth(root) << endl;
                break;
            case 3:
                cout << "Minimum value in the tree: " << findMinValue(root) << endl;
                break;
            case 4:
                root = swapTreePointers(root);
                cout << "Tree pointers swapped successfully." << endl;
                break;
            case 5:
                cout << "Enter the value to search: ";
                cin >> value;
                if (searchValue(root, value))
                    cout << "Value found in the tree." << endl;
                else
                    cout << "Value not found in the tree." << endl;
                break;
            case 6:
                cout << "Tree (Inorder Traversal): ";
                inorderTraversal(root);
                cout << endl;
                break;
            case 7:
                exitMenu = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
