#include <iostream>

using namespace std;

int linearSearch(int arr[], int size, int target, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[], int size, int target, int& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = size - 1;
    int mid;
    
    while (left <= right) {
        comparisons++;
        mid = (left + right) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void displayArray(int arr[], int size) {
    cout << "Student IDs: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    int studentIDs[10] = {101, 105, 110, 120, 125, 130, 140, 150, 160, 170};
    int size = sizeof(studentIDs) / sizeof(int);
    int searchID;
    int linearComparisons, binaryComparisons;
    
    displayArray(studentIDs, size);
    cout << endl;
    
    cout << "Enter Student ID to search: ";
    cin >> searchID;
    
    int linearResult = linearSearch(studentIDs, size, searchID, linearComparisons);
    
    int binaryResult = binarySearch(studentIDs, size, searchID, binaryComparisons);
    
    if (linearResult != -1) {
        cout << "Linear Search → Found at index " << linearResult << " (Comparisons: " << linearComparisons << ")" << endl;
    } else {
        cout << "Linear Search → Not Found (Comparisons: " << linearComparisons << ")" << endl;
    }
    
    if (binaryResult != -1) {
        cout << "Binary Search → Found at index " << binaryResult << " (Comparisons: " << binaryComparisons << ")" << endl;
    } else {
        cout << "Binary Search → Not Found (Comparisons: " << binaryComparisons << ")" << endl;
    }
    
    return 0;
}