/* Department maintains a student information. The file contains roll number, name, division 
and address. Allow user to add, delete information of student. Display information of 
particular employee. If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details. Use sequential file to main the data. */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

void addStudent() {
    ofstream file("student_info.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    Student student;

    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    file << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;
    file.close();

    cout << "Student information added successfully." << endl;
}

void deleteStudent() {
    ifstream inputFile("student_info.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cout << "Error opening temporary file." << endl;
        inputFile.close();
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number of student to delete: ";
    cin >> rollNumber;

    bool found = false;
    Student student;

    while (inputFile >> student.rollNumber >> student.name >> student.division >> student.address) {
        if (student.rollNumber != rollNumber) {
            tempFile << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;
        } else {
            found = true;
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        remove("student_info.txt");
        rename("temp.txt", "student_info.txt");
        cout << "Student information deleted successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "Student information not found." << endl;
    }
}

void displayStudent() {
    ifstream file("student_info.txt");
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number of student to display: ";
    cin >> rollNumber;

    bool found = false;
    Student student;

    while (file >> student.rollNumber >> student.name >> student.division >> student.address) {
        if (student.rollNumber == rollNumber) {
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Student information not found." << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "------------------------" << endl;
        cout << "Student Information Menu" << endl;
        cout << "------------------------" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Exit" << endl;
        cout << "------------------------" << endl;
        cout << "Enter your choice: ";
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
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
