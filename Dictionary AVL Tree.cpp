/*A Dictionary stores keywords &amp; its meanings. Provide facility for adding new keywords, deleting
keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/
Descending order. Also find how many maximum comparisons may require for finding any keyword.
Use Height balance tree and find the complexity for finding a keyword.*/

#include<iostream>
#include<string>
using namespace std;

struct DictionaryEntry {
    string keyword;
    string meaning;
};

struct Node {
    DictionaryEntry entry;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* insertNode(Node* node, DictionaryEntry entry);
    Node* deleteNode(Node* node, string keyword);
    Node* findMinValueNode(Node* node);
    Node* searchNode(Node* node, string keyword);
    void displayAscendingOrder(Node* node);
    void displayDescendingOrder(Node* node);
    int getMaxComparisons(Node* node, string keyword, int comparisons);

public:
    AVLTree();
    void addEntry(string keyword, string meaning);
    void deleteEntry(string keyword);
    void updateEntry(string keyword, string newMeaning);
    void displayAscending();
    void displayDescending();
    int findMaxComparisons(string keyword);
};

AVLTree::AVLTree() {
    root = nullptr;
}

int AVLTree::getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* temp = newRoot->left;

    newRoot->left = node;
    node->right = temp;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node* AVLTree::insertNode(Node* node, DictionaryEntry entry) {
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->entry = entry;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (entry.keyword < node->entry.keyword)
        node->left = insertNode(node->left, entry);
    else if (entry.keyword > node->entry.keyword)
        node->right = insertNode(node->right, entry);
    else
        return node; // Duplicate keywords are not allowed

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    // Left-Left case
    if (balanceFactor > 1 && entry.keyword < node->left->entry.keyword)
        return rotateRight(node);

    // Right-Right case
    if (balanceFactor < -1 && entry.keyword > node->right->entry.keyword)
        return rotateLeft(node);

    // Left-Right case
    if (balanceFactor > 1 && entry.keyword > node->left->entry.keyword) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left case
    if (balanceFactor < -1 && entry.keyword < node->right->entry.keyword) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* AVLTree::deleteNode(Node* node, string keyword) {
    if (node == nullptr)
        return node;

    if (keyword < node->entry.keyword)
        node->left = deleteNode(node->left, keyword);
    else if (keyword > node->entry.keyword)
        node->right = deleteNode(node->right, keyword);
    else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = (node->left != nullptr) ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else
                *node = *temp;
            delete temp;
        }
        else {
            Node* temp = findMinValueNode(node->right);
            node->entry = temp->entry;
            node->right = deleteNode(node->right, temp->entry.keyword);
        }
    }

    if (node == nullptr)
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    // Left-Left case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left-Right case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Right case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right-Left case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* AVLTree::findMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* AVLTree::searchNode(Node* node, string keyword) {
    if (node == nullptr || node->entry.keyword == keyword)
        return node;

    if (keyword < node->entry.keyword)
        return searchNode(node->left, keyword);

    return searchNode(node->right, keyword);
}

void AVLTree::displayAscendingOrder(Node* node) {
    if (node != nullptr) {
        displayAscendingOrder(node->left);
        cout << "Keyword: " << node->entry.keyword << ", Meaning: " << node->entry.meaning << endl;
        displayAscendingOrder(node->right);
    }
}

void AVLTree::displayDescendingOrder(Node* node) {
    if (node != nullptr) {
        displayDescendingOrder(node->right);
        cout << "Keyword: " << node->entry.keyword << ", Meaning: " << node->entry.meaning << endl;
        displayDescendingOrder(node->left);
    }
}

int AVLTree::getMaxComparisons(Node* node, string keyword, int comparisons) {
    if (node == nullptr)
        return comparisons;

    if (keyword < node->entry.keyword)
        return getMaxComparisons(node->left, keyword, comparisons + 1);

    if (keyword > node->entry.keyword)
        return getMaxComparisons(node->right, keyword, comparisons + 1);

    return comparisons + 1;
}

void AVLTree::addEntry(string keyword, string meaning) {
    DictionaryEntry entry;
    entry.keyword = keyword;
    entry.meaning = meaning;
    root = insertNode(root, entry);
    cout << "Entry added successfully!" << endl;
}

void AVLTree::deleteEntry(string keyword) {
    root = deleteNode(root, keyword);
    cout << "Entry deleted successfully!" << endl;
}

void AVLTree::updateEntry(string keyword, string newMeaning) {
    Node* node = searchNode(root, keyword);
    if (node != nullptr) {
        node->entry.meaning = newMeaning;
        cout << "Entry updated successfully!" << endl;
    }
    else {
        cout << "Keyword not found!" << endl;
    }
}

void AVLTree::displayAscending() {
    displayAscendingOrder(root);
}

void AVLTree::displayDescending() {
    displayDescendingOrder(root);
}

int AVLTree::findMaxComparisons(string keyword) {
    Node* node = searchNode(root, keyword);
    if (node != nullptr) {
        int maxComparisons = getMaxComparisons(root, keyword, 0);
        cout << "Maximum comparisons required: " << maxComparisons << endl;
        return maxComparisons;
    }
    else {
        cout << "Keyword not found!" << endl;
        return -1;
    }
}

void printMenu() {
    cout << "\n------ Dictionary Menu ------" << endl;
    cout << "1. Add Entry" << endl;
    cout << "2. Delete Entry" << endl;
    cout << "3. Update Entry" << endl;
    cout << "4. Display Ascending Order" << endl;
    cout << "5. Display Descending Order" << endl;
    cout << "6. Find Maximum Comparisons for a Keyword" << endl;
    cout << "7. Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice: ";
}

int main() {
    AVLTree dictionary;
    int choice;
    string keyword, meaning;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            cin.ignore();
            getline(cin, keyword);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            dictionary.addEntry(keyword, meaning);
            break;

        case 2:
            cout << "Enter keyword to delete: ";
            cin.ignore();
            getline(cin, keyword);
            dictionary.deleteEntry(keyword);
            break;

        case 3:
            cout << "Enter keyword to update: ";
            cin.ignore();
            getline(cin, keyword);
            cout << "Enter new meaning: ";
            getline(cin, meaning);
            dictionary.updateEntry(keyword, meaning);
            break;

        case 4:
            cout << "\nDictionary Entries in Ascending Order:" << endl;
            dictionary.displayAscending();
            break;

        case 5:
            cout << "\nDictionary Entries in Descending Order:" << endl;
            dictionary.displayDescending();
            break;

        case 6:
            cout << "Enter keyword to find maximum comparisons: ";
            cin.ignore();
            getline(cin, keyword);
            dictionary.findMaxComparisons(keyword);
            break;

        case 7:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }

        cout << endl;
    } while (choice != 7);

    return 0;
}
