/*A Dictionary stores keywords &amp; its meanings. Provide facility for adding new keywords, deleting
keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/
Descending order. Also find how many maximum comparisons may require for finding any keyword.
Use Height balance tree and find the complexity for finding a keyword.*/

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class Node {
public:
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;
};

class AVLTree {
    Node* root;

public:
    AVLTree() {
        root = nullptr;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* createNode(string keyword, string meaning) {
        Node* newNode = new Node();
        newNode->keyword = keyword;
        newNode->meaning = meaning;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    Node* rotateLeft(Node* node) {
        Node* rightChild = node->right;
        Node* leftGrandchild = rightChild->left;

        rightChild->left = node;
        node->right = leftGrandchild;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        rightChild->height = 1 + max(getHeight(rightChild->left), getHeight(rightChild->right));

        return rightChild;
    }

    Node* rotateRight(Node* node) {
        Node* leftChild = node->left;
        Node* rightGrandchild = leftChild->right;

        leftChild->right = node;
        node->left = rightGrandchild;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));

        return leftChild;
    }

    Node* insertNode(Node* node, string keyword, string meaning) {
        if (node == nullptr)
            return createNode(keyword, meaning);

        if (keyword < node->keyword)
            node->left = insertNode(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insertNode(node->right, keyword, meaning);
        else {
            cout << "Keyword already exists. Updating meaning..." << endl;
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Left-Left Case
        if (balance > 1 && keyword < node->left->keyword)
            return rotateRight(node);

        // Right-Right Case
        if (balance < -1 && keyword > node->right->keyword)
            return rotateLeft(node);

        // Left-Right Case
        if (balance > 1 && keyword > node->left->keyword) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left Case
        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, string keyword) {
        if (node == nullptr)
            return node;

        if (keyword < node->keyword)
            node->left = deleteNode(node->left, keyword);
        else if (keyword > node->keyword)
            node->right = deleteNode(node->right, keyword);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else {
                Node* temp = minValueNode(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Left-Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        // Left-Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        // Right-Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* searchKeyword(Node* node, string keyword, int& comparisons) {
        if (node == nullptr)
            return nullptr;

        comparisons++;
        if (keyword == node->keyword)
            return node;
        else if (keyword < node->keyword)
            return searchKeyword(node->left, keyword, comparisons);
        else
            return searchKeyword(node->right, keyword, comparisons);
    }

    void displayInOrder(Node* node) {
        if (node != nullptr) {
            displayInOrder(node->left);
            cout << node->keyword << ": " << node->meaning << endl;
            displayInOrder(node->right);
        }
    }

    void displayPreOrder(Node* node) {
        if (node != nullptr) {
            cout << node->keyword << ": " << node->meaning << endl;
            displayPreOrder(node->left);
            displayPreOrder(node->right);
        }
    }

    void displayPostOrder(Node* node) {
        if (node != nullptr) {
            displayPostOrder(node->left);
            displayPostOrder(node->right);
            cout << node->keyword << ": " << node->meaning << endl;
        }
    }

    void displayAscending() {
        cout << "Dictionary data sorted in ascending order:" << endl;
        displayInOrder(root);
    }

    void displayDescending() {
        cout << "Dictionary data sorted in descending order:" << endl;
        displayPostOrder(root);
    }

    void addKeyword() {
        string keyword, meaning;
        cout << "Enter the keyword: ";
        cin.ignore();
        getline(cin, keyword);
        cout << "Enter the meaning: ";
        getline(cin, meaning);

        root = insertNode(root, keyword, meaning);
        cout << "Keyword added successfully!" << endl;
    }

    void deleteKeyword() {
        string keyword;
        cout << "Enter the keyword to delete: ";
        cin.ignore();
        getline(cin, keyword);

        root = deleteNode(root, keyword);
        cout << "Keyword deleted successfully!" << endl;
    }

    void updateKeyword() {
        string keyword, newMeaning;
        cout << "Enter the keyword to update: ";
        cin.ignore();
        getline(cin, keyword);

        Node* node = searchKeyword(root, keyword);
        if (node != nullptr) {
            cout << "Enter the new meaning: ";
            getline(cin, newMeaning);
            node->meaning = newMeaning;
            cout << "Keyword updated successfully!" << endl;
        }
        else {
            cout << "Keyword not found!" << endl;
        }
    }

    void findKeyword() {
        string keyword;
        cout << "Enter the keyword to find: ";
        cin.ignore();
        getline(cin, keyword);

        int comparisons = 0;
        Node* node = searchKeyword(root, keyword, comparisons);
        if (node != nullptr) {
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            cout << "Number of comparisons: " << comparisons << endl;
        }
        else {
            cout << "Keyword not found!" << endl;
        }
    }

    void displayMenu() {
        cout << "------- Dictionary Management System -------" << endl;
        cout << "1. Add Keyword" << endl;
        cout << "2. Delete Keyword" << endl;
        cout << "3. Update Keyword" << endl;
        cout << "4. Display Data Sorted in Ascending Order" << endl;
        cout << "5. Display Data Sorted in Descending Order" << endl;
        cout << "6. Find a Keyword" << endl;
        cout << "0. Exit" << endl;
        cout << "--------------------------------------------" << endl;
    }

    void processUserInput() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addKeyword();
                    break;
                case 2:
                    deleteKeyword();
                    break;
                case 3:
                    updateKeyword();
                    break;
                case 4:
                    displayAscending();
                    break;
                case 5:
                    displayDescending();
                    break;
                case 6:
                    findKeyword();
                    break;
                case 0:
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }

            cout << endl;
        } while (choice != 0);
    }
};

int main() {
    AVLTree dictionary;
    dictionary.processUserInput();

    return 0;
}
