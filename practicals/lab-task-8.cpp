#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n = right - left + 1;
    int* temp = new int[n];
    
    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int i = 0; i < n; i++) {
        arr[left + i] = temp[i];
    }

    delete[] temp;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    
    int size;
    cout << "Enter number of books: ";
    cin >> size;
    
    int* bookIDs = new int[size];
    
    for (int i = 0; i < size; i++) {
        bookIDs[i] = rand() % 10000 + 1;
    }
    
    cout << "\nUnsorted Book IDs: ";
    printArray(bookIDs, size);
    
    clock_t start = clock();
    mergeSort(bookIDs, 0, size - 1);
    clock_t end = clock();
    
    cout << "Sorted Book IDs (Merge Sort): ";
    printArray(bookIDs, size);
    
    double timeTaken = double(end - start) / CLOCKS_PER_SEC * 1000;
    cout << "\nTime taken by Merge Sort: " << timeTaken << " milliseconds" << endl;
    
    delete[] bookIDs;
    
    return 0;
}