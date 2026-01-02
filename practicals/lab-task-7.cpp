#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(int arr[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            swaps++;
        }
    }
}

void insertionSort(int arr[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            swaps++;
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    int* marks = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter mark " << (i + 1) << ": ";
        cin >> marks[i];
    }

    int choice;

    do {
        cout << "\nSorting Menu:\n";
        cout << "1. Sort using Bubble Sort\n";
        cout << "2. Sort using Selection Sort\n";
        cout << "3. Sort using Insertion Sort\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            int* temp = new int[n];
            for (int i = 0; i < n; i++) {
                temp[i] = marks[i];
            }

            int comp = 0, swp = 0;

            if (choice == 1) {
                bubbleSort(temp, n, comp, swp);
            } else if (choice == 2) {
                selectionSort(temp, n, comp, swp);
            } else if (choice == 3) {
                insertionSort(temp, n, comp, swp);
            }

            cout << "Sorted marks in ascending order: ";
            for (int i = 0; i < n; i++) {
                cout << temp[i] << " ";
            }
            cout << endl;
            
            cout << "Number of comparisons: " << comp << endl;
            cout << "Number of swaps: " << swp << endl;

            delete[] temp;
        } else if (choice != 4) {
            cout << "Invalid choice. Please try again.\n";
        }
        
    } while (choice != 4);

    delete[] marks;

    return 0;
}