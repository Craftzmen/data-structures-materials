#include <iostream>
#include <string>

using namespace std;

struct Employee {
    int empNumber;
    string name;
    double salary;
    int deptNumber;
    Employee* next;
};

Employee* createEmployee(int empNo, string name, double salary, int deptNo) {
    Employee* newEmp = new Employee();
    newEmp->empNumber = empNo;
    newEmp->name = name;
    newEmp->salary = salary;
    newEmp->deptNumber = deptNo;
    newEmp->next = NULL;
    return newEmp;
}

void insertAtFront(Employee** head, int empNo, string name, double salary, int deptNo) {
    Employee* newEmp = createEmployee(empNo, name, salary, deptNo);
    newEmp->next = *head;
    *head = newEmp;
    cout << "Employee " << empNo << " inserted at front successfully!" << endl;
}

void insertAtEnd(Employee** head, int empNo, string name, double salary, int deptNo) {
    Employee* newEmp = createEmployee(empNo, name, salary, deptNo);
    
    if (*head == NULL) {
        *head = newEmp;
        cout << "Employee " << empNo << " inserted at end successfully!" << endl;
        return;
    }
    
    Employee* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newEmp;
    cout << "Employee " << empNo << " inserted at end successfully!" << endl;
}

void insertAtPosition(Employee** head, int empNo, string name, double salary, int deptNo, int position) {
    if (position < 1) {
        cout << "Invalid position!" << endl;
        return;
    }
    
    Employee* newEmp = createEmployee(empNo, name, salary, deptNo);
    
    if (position == 1) {
        newEmp->next = *head;
        *head = newEmp;
        cout << "Employee " << empNo << " inserted at position " << position << " successfully!" << endl;
        return;
    }
    
    Employee* temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        cout << "Position out of range!" << endl;
        delete newEmp;
        return;
    }
    
    newEmp->next = temp->next;
    temp->next = newEmp;
    cout << "Employee " << empNo << " inserted at position " << position << " successfully!" << endl;
}

void deleteFirst(Employee** head) {
    if (*head == NULL) {
        cout << "List is empty! Cannot delete." << endl;
        return;
    }
    
    Employee* temp = *head;
    int empNo = temp->empNumber;
    *head = (*head)->next;
    delete temp;
    cout << "Employee " << empNo << " deleted from front successfully!" << endl;
}

void deleteLast(Employee** head) {
    if (*head == NULL) {
        cout << "List is empty! Cannot delete." << endl;
        return;
    }
    
    if ((*head)->next == NULL) {
        int empNo = (*head)->empNumber;
        delete *head;
        *head = NULL;
        cout << "Employee " << empNo << " deleted from end successfully!" << endl;
        return;
    }
    
    Employee* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    int empNo = temp->next->empNumber;
    delete temp->next;
    temp->next = NULL;
    cout << "Employee " << empNo << " deleted from end successfully!" << endl;
}

void deleteAtPosition(Employee** head, int position) {
    if (*head == NULL) {
        cout << "List is empty! Cannot delete." << endl;
        return;
    }
    
    if (position < 1) {
        cout << "Invalid position!" << endl;
        return;
    }
    
    if (position == 1) {
        Employee* temp = *head;
        int empNo = temp->empNumber;
        *head = (*head)->next;
        delete temp;
        cout << "Employee " << empNo << " deleted from position " << position << " successfully!" << endl;
        return;
    }
    
    Employee* temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL || temp->next == NULL) {
        cout << "Position out of range!" << endl;
        return;
    }
    
    Employee* nodeToDelete = temp->next;
    int empNo = nodeToDelete->empNumber;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
    cout << "Employee " << empNo << " deleted from position " << position << " successfully!" << endl;
}

void searchByEmpNumber(Employee* head, int empNo) {
    Employee* temp = head;
    int position = 1;
    bool found = false;
    
    while (temp != NULL) {
        if (temp->empNumber == empNo) {
            cout << "\n=== Employee Found ===" << endl;
            cout << "Position: " << position << endl;
            cout << "Employee Number: " << temp->empNumber << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Salary: $" << temp->salary << endl;
            cout << "Department Number: " << temp->deptNumber << endl;
            found = true;
            break;
        }
        temp = temp->next;
        position++;
    }
    
    if (!found) {
        cout << "Employee with number " << empNo << " not found!" << endl;
    }
}

void searchByDeptNumber(Employee* head, int deptNo) {
    Employee* temp = head;
    int count = 0;
    
    cout << "\n=== Employees in Department " << deptNo << " ===" << endl;
    
    while (temp != NULL) {
        if (temp->deptNumber == deptNo) {
            cout << "\nEmployee " << (++count) << ":" << endl;
            cout << "Employee Number: " << temp->empNumber << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Salary: $" << temp->salary << endl;
            cout << "Department Number: " << temp->deptNumber << endl;
        }
        temp = temp->next;
    }
    
    if (count == 0) {
        cout << "No employees found in department " << deptNo << endl;
    } else {
        cout << "\nTotal employees in department " << deptNo << ": " << count << endl;
    }
}

void displayAll(Employee* head) {
    if (head == NULL) {
        cout << "No employees in the list!" << endl;
        return;
    }
    
    cout << "\n=== Employee Records ===" << endl;
    cout << "Emp No\tName\t\tSalary\t\tDept No" << endl;
    
    Employee* temp = head;
    int count = 0;
    
    while (temp != NULL) {
        cout << temp->empNumber << "\t" 
             << temp->name << "\t\t$" 
             << temp->salary << "\t\t" 
             << temp->deptNumber << endl;
        temp = temp->next;
        count++;
    }
    
    cout << "Total Employees: " << count << endl;
}

int countEmployees(Employee* head) {
    int count = 0;
    Employee* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}