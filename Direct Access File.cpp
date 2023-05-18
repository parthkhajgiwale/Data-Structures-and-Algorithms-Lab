#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Employee {
    int employeeID;
    char name[50];
    char designation[50];
    double salary;
};

void addEmployee() {
    ofstream file("employee.dat", ios::binary | ios::app);

    Employee employee;

    cout << "Enter Employee ID: ";
    cin >> employee.employeeID;

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(employee.name, 50);

    cout << "Enter Designation: ";
    cin.getline(employee.designation, 50);

    cout << "Enter Salary: ";
    cin >> employee.salary;

    file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));

    file.close();

    cout << "Employee information added successfully!" << endl;
}

void deleteEmployee(int employeeID) {
    ifstream file("employee.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    Employee employee;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.employeeID == employeeID) {
            found = true;
            continue;
        }

        temp.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
    }

    file.close();
    temp.close();

    if (found) {
        remove("employee.dat");
        rename("temp.dat", "employee.dat");
        cout << "Employee information deleted successfully!" << endl;
    } else {
        remove("temp.dat");
        cout << "Employee not found!" << endl;
    }
}

void displayEmployee(int employeeID) {
    ifstream file("employee.dat", ios::binary);

    Employee employee;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        if (employee.employeeID == employeeID) {
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Employee ID: " << employee.employeeID << endl;
        cout << "Name: " << employee.name << endl;
        cout << "Designation: " << employee.designation << endl;
        cout << "Salary: " << employee.salary << endl;
    } else {
        cout << "Employee not found!" << endl;
    }
}

int main() {
    int choice;
    int employeeID;

    while (true) {
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                cout << "Enter Employee ID to delete: ";
                cin >> employeeID;
                deleteEmployee(employeeID);
                break;
            case 3:
                cout << "Enter Employee ID to display: ";
                cin >> employeeID;
                displayEmployee(employeeID);
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
