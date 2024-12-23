#include <iostream>
#include <vector>
using namespace std;

// Algoritma Insertion Sort Iteratif
void insertionSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Fungsi untuk menampilkan array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6}; // Contoh array

    cout << "Array sebelum diurutkan: ";
    printArray(arr);

    insertionSortIterative(arr);

    cout << "Array setelah diurutkan (Iteratif): ";
    printArray(arr);

    return 0;
}
