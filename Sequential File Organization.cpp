#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to hold student information
struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

// Function to add a new student record
void addStudent() {
    ofstream file("students.txt", ios::app); // Open the file in append mode

    Student student;

    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore(); // Ignore the newline character from previous input
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    // Write the student record to the file
    file << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;

    file.close();
    cout << "Student information added successfully!" << endl;
}

// Function to delete a student record
void deleteStudent() {
    ifstream file("students.txt"); // Open the file for reading
    ofstream tempFile("temp.txt"); // Open a temporary file for writing

    int rollNumber;
    cout << "Enter Roll Number of the student to be deleted: ";
    cin >> rollNumber;

    bool found = false;
    Student student;

    while (file >> student.rollNumber >> student.name >> student.division >> student.address) {
        if (student.rollNumber != rollNumber) {
            // Write the non-matching student record to the temporary file
            tempFile << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("students.txt");     // Delete the original file
        rename("temp.txt", "students.txt"); // Rename the temporary file to the original file name
        cout << "Student information deleted successfully!" << endl;
    } else {
        remove("temp.txt"); // Delete the temporary file
        cout << "Student record not found!" << endl;
    }
}

// Function to display information of a particular student
void displayStudent() {
    ifstream file("students.txt"); // Open the file for reading

    int rollNumber;
    cout << "Enter Roll Number of the student to display: ";
    cin >> rollNumber;

    bool found = false;
    Student student;

    while (file >> student.rollNumber >> student.name >> student.division >> student.address) {
        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break; // Exit the loop after finding the student record
        }
    }

    file.close();

    if (!found) {
        cout << "Student record not found!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "------ Student Information System ------" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
