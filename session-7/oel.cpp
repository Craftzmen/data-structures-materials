#include <iostream>
#include <string>

using namespace std;

struct StudentRecord {
    int rollNo;
    string name;
    string department;
    int semester;
    float cgpa;
    StudentRecord* next;
};

StudentRecord* head = nullptr;

void addStudentRecord(int rollNo, const string& name, const string& department, int semester, float cgpa) {
    StudentRecord* newStudent = new StudentRecord();
    newStudent->rollNo = rollNo;
    newStudent->name = name;
    newStudent->department = department;
    newStudent->semester = semester;
    newStudent->cgpa = cgpa;
    newStudent->next = nullptr;

    if (head == nullptr) {
        head = newStudent;
    } else {
        StudentRecord* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
    cout << "Student Record successfully added: ";
}

void searchStudentRecord(int rollNo) {
    if (head == nullptr) {
        cout << " Linked list is empty: ";
        return;
    }

    StudentRecord* temp = head;
    while (temp != nullptr) {
        if (temp->rollNo == rollNo) {
            cout << "Student Record found: ";
            cout << "Roll No    : " << temp->rollNo;
            cout << "Name       : " << temp->name;
            cout << "Department : " << temp->department;
            cout << "Semester   : " << temp->semester;
            cout << "CGPA       : " << temp->cgpa;
            return;
        }
        temp = temp->next;
    }
    cout << "Student with Roll No " << rollNo;
}

void removeStudentRecord(int rollNo) {
    if (head == nullptr) {
        cout << " No Student Records available to delete: ";
        return;
    }

    StudentRecord* current = head;
    StudentRecord* previous = nullptr;

    while (current != nullptr && current->rollNo != rollNo) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Student Record with Roll No " << rollNo << " not found: ";
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    cout << " Student Record deleted successfully: ";
}

void displayAllRecords() {
    if (head == nullptr) {
        cout << " No Student Records to display: ";
        return;
    }

    StudentRecord* temp = head;
    cout << "All Student Records: ";
    while (temp != nullptr) {
        cout << "Roll No    : " << temp->rollNo;
        cout << "Name       : " << temp->name;
        cout << "Department : " << temp->department;
        cout << "Semester   : " << temp->semester;
        cout << "CGPA       : " << temp->cgpa;
        temp = temp->next;
    }
}

int main() {
    int choice;
    int rollNo;
    string name, department;
    int semester;
    float cgpa;

    do {
        cout << " Student Record Management System: ";
        cout << "1. Add New Student Record: ";
        cout << "2. Search for Student Record by Roll No: ";
        cout << "3. Delete Student Record by Roll No: ";
        cout << "4. Display All Student Records: ";
        cout << "5. Exit: ";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student Roll No: ";
                cin >> rollNo;
                cout << "Enter Student Name: ";
                cin >> name;
                cout << "Enter Student Department: ";
                 cin >> department;
                cout << "Enter Student Semester: ";
                cin >> semester;
                cout << "Enter Student CGPA: ";
                cin >> cgpa;
                addStudentRecord(rollNo, name, department, semester, cgpa);
                break;

            case 2:
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                searchStudentRecord(rollNo);
                break;

            case 3:
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                removeStudentRecord(rollNo);
                break;

            case 4:
                displayAllRecords();
                break;

            case 5:
                cout << " Exiting the program: ";
                break;

            default:
                cout << "Invalid choice. Please try again: ";
        }
    } 
    while (choice != 5);

    return 0;
}