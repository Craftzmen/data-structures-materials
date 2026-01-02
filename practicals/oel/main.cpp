#include <iostream>

using namespace std;

struct Node {
    int rollNo;
    string name;
    string department;
    int semester;
    float cgpa;
    Node* next;
    Node* prev;
};

Node* head = nullptr;

Node* createStudent(int rollNo, string name, string department, int semester, float cgpa) {
    Node* newStudent =  new Node();
    newStudent->rollNo = rollNo;
    newStudent->name = name;
    newStudent->department = department;
    newStudent->semester = semester;
    newStudent->cgpa = cgpa;
    newStudent->next =  nullptr;
    newStudent->prev = nullptr;
    return newStudent;
}

void insertAtBeginning(int rollNo, string name, string department, int semester, float cgpa) {
    Node* newStudent =  createStudent(rollNo, name, department, semester, cgpa);
    if (head == nullptr) {
        head = newStudent;
        return;
    }
    newStudent->next = head;
    head->prev = newStudent;
    head = newStudent;
}

void insertAtEnd(int rollNo, string name, string department, int semester, float cgpa) {
    Node* newStudent =  createStudent(rollNo, name, department, semester, cgpa);
    if (head == nullptr) {
        head = newStudent;
        return;
    }
    Node* curr = head;
    while(curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newStudent;
    newStudent->prev = curr;
}

void insertAtPosition(int rollNo, string name, string department, int semester, float cgpa, int pos) {
    if (pos < 1) {}
    if (pos == 1) {
        insertAtBeginning(rollNo, name, department, semester, cgpa);
    }
    Node* curr = head;
    for (int i = 1; i < pos - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {}
    Node* newNode = createStudent(rollNo, name, department, semester, cgpa);
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    }
    curr->next = newNode;
}

void deleteFromBeginning() {
    if (head == nullptr) {
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

void deleteByRollNo(int rollNo) {
    if (rollNo < 1 || head == nullptr) {}
    if (rollNo == head->rollNo) {
        deleteFromBeginning();
    }
    Node* curr = head;
    for (int i = 1; i < rollNo && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {}
    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    }
    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    }
    delete curr;
}

void searchByRollNo(int rollNo) {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    Node* curr = head;
    int pos = 1;
    int found = 0;
    cout << "Student with roll no " << rollNo << " found at position(s): ";
    while (curr != nullptr) {
        if (curr->rollNo == rollNo) {
            cout << pos << " ";
            found = 1;
        }
        curr = curr->next;
        pos++;
    }
    if (found == 0) {
        cout << "Student with " <<  rollNo << " Not found!";
    }
    cout << "\n";
}

void updateStudentDetails(int rollNo, string name, string department, int semester, float cgpa) {
    if (rollNo < 1) {
        cout << "Invalid roll number!\n";
        return;
    }
    Node* curr = head;
    for (int i = 1; i < rollNo && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        cout << "Student not found!\n";
        return;
    }
    curr->name = name;
    curr->department = department;
    curr->semester = semester;
    curr->cgpa = cgpa;
}

void displayTopCGPAStudent() {
    if (head == nullptr) {
        cout << "Student List is empty!\n";
        return;
    }
    
    Node* topStudent = head;
    Node* curr = head->next;
    
    while (curr != nullptr) {
        if (curr->cgpa > topStudent->cgpa) {
            topStudent = curr;
        }
        curr = curr->next;
    }
    
    cout << "Student with highest CGPA:\n";
    cout << "Name: " << topStudent->name << "\n";
    cout << "Roll No: " << topStudent->rollNo << "\n";
    cout << "CGPA: " << topStudent->cgpa << "\n";
    cout << "Department: " << topStudent->department << "\n";
    cout << "Semester: " << topStudent->semester << "\n";
}

void displayMenu() {
    cout << "\nStudent Doubly Linked List Operations\n";
    cout << "1. Insert at beginning\n";
    cout << "2. Insert at end\n";
    cout << "3. Insert at specific position\n";
    cout << "4. Delete by roll no\n";
    cout << "5. Search for a student by roll no\n";
    cout << "6. Update student data by roll no\n";
    cout << "7. Exit\n";
}

int main() {
    int choice;
    int rollNo;
    string name, updatedName;
    string department, updatedDepartment;
    int semester, updatedSemster;
    float cgpa, updatedCGPA;
    int pos;

}