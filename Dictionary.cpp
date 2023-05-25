#include <iostream>
using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
};

class Dictionary {
private:
    Node* root;

    Node* createNode(string keyword, string meaning) {
        Node* newNode = new Node;
        newNode->keyword = keyword;
        newNode->meaning = meaning;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    Node* insertNode(Node* root, string keyword, string meaning) {
        if (root == nullptr) {
            return createNode(keyword, meaning);
        }

        if (keyword < root->keyword) {
            root->left = insertNode(root->left, keyword, meaning);
        } else if (keyword > root->keyword) {
            root->right = insertNode(root->right, keyword, meaning);
        }

        return root;
    }

    Node* searchNode(Node* root, string keyword, int& comparisons) {
        if (root == nullptr || root->keyword == keyword) {
            return root;
        }

        comparisons++;
        if (keyword < root->keyword) {
            return searchNode(root->left, keyword, comparisons);
        } else {
            return searchNode(root->right, keyword, comparisons);
        }
    }

    Node* findMinNode(Node* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    Node* deleteNode(Node* root, string keyword) {
        if (root == nullptr) {
            return root;
        }

        if (keyword < root->keyword) {
            root->left = deleteNode(root->left, keyword);
        } else if (keyword > root->keyword) {
            root->right = deleteNode(root->right, keyword);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMinNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }

        return root;
    }

    void inorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderTraversal(root->left);
        cout << root->keyword << ": " << root->meaning << endl;
        inorderTraversal(root->right);
    }

    void reverseInorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        reverseInorderTraversal(root->right);
        cout << root->keyword << ": " << root->meaning << endl;
        reverseInorderTraversal(root->left);
    }

public:
    Dictionary() {
        root = nullptr;
    }

    void addKeyword(string keyword, string meaning) {
        root = insertNode(root, keyword, meaning);
        cout << "Keyword added successfully." << endl;
    }

    void deleteKeyword(string keyword) {
        int comparisons = 0;
        Node* node = searchNode(root, keyword, comparisons);
        if (node != nullptr) {
            root = deleteNode(root, keyword);
            cout << "Keyword deleted successfully." << endl;
        } else {
            cout << "Keyword not found in the dictionary." << endl;
        }
    }

    void updateKeyword(string keyword, string newMeaning) {
        int comparisons = 0;
        Node* node = searchNode(root, keyword, comparisons);
        if (node != nullptr) {
            node->meaning = newMeaning;
            cout << "Keyword updated successfully." << endl;
        } else {
            cout << "Keyword not found in the dictionary." << endl;
        }
    }

    void displayAscending() {
        if (root == nullptr) {
            cout << "Dictionary is empty." << endl;
        } else {
            cout << "Dictionary in ascending order:" << endl;
            inorderTraversal(root);
        }
    }

    void displayDescending() {
        if (root == nullptr) {
            cout << "Dictionary is empty." << endl;
        } else {
            cout << "Dictionary in descending order:" << endl;
            reverseInorderTraversal(root);
        }
    }

    int getMaxComparisons(string keyword) {
        int comparisons = 0;
        searchNode(root, keyword, comparisons);
        return comparisons;
    }
};

int main() {
    Dictionary dict;
    int choice;
    string keyword, meaning;

    while (true) {
        cout << "1. Add a keyword" << endl;
        cout << "2. Delete a keyword" << endl;
        cout << "3. Update a keyword" << endl;
        cout << "4. Display dictionary in ascending order" << endl;
        cout << "5. Display dictionary in descending order" << endl;
        cout << "6. Get maximum comparisons for a keyword" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.addKeyword(keyword, meaning);
                break;

            case 2:
                cout << "Enter keyword: ";
                cin >> keyword;
                dict.deleteKeyword(keyword);
                break;

            case 3:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.updateKeyword(keyword, meaning);
                break;

            case 4:
                dict.displayAscending();
                break;

            case 5:
                dict.displayDescending();
                break;

            case 6:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Maximum comparisons required: " << dict.getMaxComparisons(keyword) << endl;
                break;

            case 7:
                exit(0);

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
