#include <iostream>
using namespace std;

int main() {
    int studentRollNos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int size = sizeof(studentRollNos) / sizeof(int);

    cout << "Size of student array: " << size << endl;

    int studentToFind;
    cout << "Enter the student id to find: ";
    cin >> studentToFind;

    bool valueFound = false;

    for (int i = 0; i < size; i++) {
        if (studentRollNos[i] == studentToFind) {
            valueFound = true;
            cout << "Student with roll no " << studentToFind << " exists" << endl;
            break;
        }
    }

    if (!valueFound) {
        cout << "Value not found" << endl;
    }

    return 0;
}
