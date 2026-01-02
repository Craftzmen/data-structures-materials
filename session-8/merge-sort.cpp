#include<iostream>

using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n = right - left + 1;
    int* temp = new int[n];
    
    int i = left;      // Start of left subarray
    int j = mid + 1;   // Start of right subarray
    int k = 0;         // Index for temp array

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

    // Copy back to original array
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

int main() {
    int arr[] = {7, 5, 6, 4, 8, 2, 1, 9};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    
    mergeSort(arr, 0, arrSize - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}