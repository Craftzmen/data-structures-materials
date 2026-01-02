#include <iostream>

using namespace std;

int binarySearch(int studentRollNos[], int size, int target) {
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (studentRollNos[mid] == target) {
            return mid;
        } else if (studentRollNos[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int studentRollNos[] = {4, 5, 7, 9, 14, 19, 23};

    int size = sizeof(studentRollNos) / sizeof(studentRollNos[0]);

    int targetValue;
    cout << "Enter the value to search: ";
    cin >> targetValue;

    int valueSearched = binarySearch(studentRollNos, size, targetValue);
    
    if (!valueSearched) {
        cout << "Value not found" << endl;
    } else {
        cout << "Value found at index " << valueSearched << endl;
    }

    return 0;
}