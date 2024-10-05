#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Employee {
private:
    int empID;
    string name;
    double basicSalary, allowances, deductions, netSalary;

    double calculateNetSalary() {
        return basicSalary + allowances - deductions;
    }

public:
    Employee() : empID(0), basicSalary(0.0), allowances(0.0), deductions(0.0), netSalary(0.0) {}

    void inputEmployeeDetails() {
        cout << "Enter Employee ID: ";
        cin >> empID;
        cin.ignore();  // Ignore leftover newline character
        cout << "Enter Employee Name: ";
        getline(cin, name);
        cout << "Enter Basic Salary: ";
        cin >> basicSalary;
        cout << "Enter Allowances: ";
        cin >> allowances;
        cout << "Enter Deductions: ";
        cin >> deductions;
        netSalary = calculateNetSalary();
    }

    void displayEmployeeDetails() const {
        cout << "Employee ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Basic Salary: " << basicSalary << endl;
        cout << "Allowances: " << allowances << endl;
        cout << "Deductions: " << deductions << endl;
        cout << "Net Salary: " << netSalary << endl;
    }

    int getEmpID() const {
        return empID;
    }

    void saveToFile(ofstream& outFile) const {
        outFile << empID << endl;
        outFile << name << endl;
        outFile << basicSalary << endl;
        outFile << allowances << endl;
        outFile << deductions << endl;
        outFile << netSalary << endl;
    }

    void readFromFile(ifstream& inFile) {
        inFile >> empID;
        inFile.ignore();  // Ignore newline character after empID
        getline(inFile, name);
        inFile >> basicSalary >> allowances >> deductions >> netSalary;
    }

    void modifyDetails() {
        cout << "Modify details for Employee ID " << empID << endl;
        cout << "Enter new Basic Salary: ";
        cin >> basicSalary;
        cout << "Enter new Allowances: ";
        cin >> allowances;
        cout << "Enter new Deductions: ";
        cin >> deductions;
        netSalary = calculateNetSalary();
    }
};

void addEmployee() {
    ofstream outFile("employee.dat", ios::app); // Append to the file
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    emp.inputEmployeeDetails();
    emp.saveToFile(outFile);

    cout << "Employee added successfully!" << endl;
    outFile.close();
}

void displayAllEmployees() {
    ifstream inFile("employee.dat");
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    while (!inFile.eof()) {
        emp.readFromFile(inFile);
        if (inFile.eof()) break; // Prevents duplicate last record
        emp.displayEmployeeDetails();
        cout << "-----------------------------" << endl;
    }

    inFile.close();
}

void searchEmployee(int id) {
    ifstream inFile("employee.dat");
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    bool found = false;
    while (!inFile.eof()) {
        emp.readFromFile(inFile);
        if (inFile.eof()) break; // Prevents duplicate last record
        if (emp.getEmpID() == id) {
            emp.displayEmployeeDetails();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
    }

    inFile.close();
}

void modifyEmployee(int id) {
    fstream file("employee.dat", ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Employee emp;
    bool found = false;
    long pos;
    while (!file.eof()) {
        pos = file.tellg();
        emp.readFromFile(file);
        if (file.eof()) break;
        if (emp.getEmpID() == id) {
            emp.modifyDetails();
            file.seekp(pos); // Move the write pointer to the correct position
            emp.saveToFile(file);
            found = true;
            cout << "Employee details updated successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found." << endl;
    }

    file.close();
}

void menu() {
    int choice, id;
    while (true) {
        cout << "\n=== Employee Payroll Management ===\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee by ID\n";
        cout << "4. Modify Employee Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            displayAllEmployees();
            break;
        case 3:
            cout << "Enter Employee ID to search: ";
            cin >> id;
            searchEmployee(id);
            break;
        case 4:
            cout << "Enter Employee ID to modify: ";
            cin >> id;
            modifyEmployee(id);
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
