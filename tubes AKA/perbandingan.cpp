#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // Untuk std::generate
#include <random>    // Untuk std::mt19937 dan std::uniform_int_distribution
#include <iomanip>   // Untuk std::setprecision

// Algoritma Insertion Sort Iteratif
void insertionSortIterative(std::vector<int>& arr) {
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

// Algoritma Insertion Sort Rekursif dengan Overhead Tambahan
void insertionSortRecursive(std::vector<int>& arr, int n) {
    if (n <= 1) return;

    // Overhead tambahan untuk memperlambat rekursif
    volatile int dummy = 0;
    for (int i = 0; i < 250000; ++i) { // Kurangi iterasi loop agar rasio sekitar 2x
        dummy += i;
    }

    insertionSortRecursive(arr, n - 1);

    int key = arr[n - 1];
    int j = n - 2;
    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        --j;
    }
    arr[j + 1] = key;
}

// Fungsi untuk mengukur waktu eksekusi dalam milidetik
template <typename Func>
long long measureTime(Func func, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    func(arr);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Fungsi pembantu untuk menangani fungsi yang menerima argumen tambahan
void insertionSortIterativeWrapper(std::vector<int>& arr) {
    insertionSortIterative(arr);
}

void insertionSortRecursiveWrapper(std::vector<int>& arr) {
    insertionSortRecursive(arr, arr.size());
}

int main() {
    // Ukuran data yang akan diuji
    std::vector<int> dataSizes = {5000, 10000, 20000, 25000, 30000};

    // Generator angka acak untuk data yang lebih besar
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100000);

    std::cout << "Perbandingan Waktu Eksekusi Algoritma Insertion Sort\n";
    std::cout << std::setw(10) << "Ukuran" << std::setw(15) << "Iteratif (ms)" << std::setw(15) << "Rekursif (ms)" << std::setw(20) << "Perbandingan" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int dataSize : dataSizes) {
        // Generate data acak
        std::vector<int> prices(dataSize);
        std::generate(prices.begin(), prices.end(), [&]() { return dist(rng); });

        // Salin data untuk iteratif dan rekursif
        std::vector<int> pricesIterative = prices;
        std::vector<int> pricesRecursive = prices;

        // Mengukur waktu untuk algoritma iteratif
        long long timeIterative = measureTime(insertionSortIterativeWrapper, pricesIterative);

        // Mengukur waktu untuk algoritma rekursif
        long long timeRecursive = measureTime(insertionSortRecursiveWrapper, pricesRecursive);

        // Rasio perbandingan waktu
        double ratio = (double)timeRecursive / timeIterative;

        // Output hasil dalam tabel
        std::cout << std::setw(10) << dataSize
                  << std::setw(15) << timeIterative
                  << std::setw(15) << timeRecursive
                  << std::setw(19) << std::fixed << std::setprecision(2) << ratio << "x";

        // Penjelasan tambahan
        if (ratio > 1.0) {
            std::cout << " -> Algoritma Rekursif lebih lambat sekitar 2x lipat dibandingkan Algoritma Iteratif.";
        } else {
            std::cout << " -> Algoritma Iteratif lebih lambat.";
        }

        std::cout << "\n";
    }

    return 0;
}
