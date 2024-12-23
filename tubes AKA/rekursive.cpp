#include <iostream>
#include <vector>
using namespace std;

// Fungsi untuk memasukkan elemen secara rekursif
void insertRecursive(vector<int>& arr, int n) {
    if (n <= 1) return; // Kasus dasar

    // Rekursi untuk bagian sebelumnya dari array
    insertRecursive(arr, n - 1);

    // Menyisipkan elemen pada posisi yang benar
    int key = arr[n - 1];
    int j = n - 2;
    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        --j;
    }
    arr[j + 1] = key;
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

    insertRecursive(arr, arr.size());

    cout << "Array setelah diurutkan (Rekursif): ";
    printArray(arr);

    return 0;
}
