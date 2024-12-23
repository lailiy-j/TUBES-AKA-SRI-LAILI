#include <iostream>

using namespace std;

int main()
{
    vector<int> arr = {12, 11, 13, 5, 6}; // Contoh array

    cout << "Array sebelum diurutkan: ";
    printArray(arr);

    insertRecursive(arr, arr.size());

    cout << "Array setelah diurutkan (Rekursif): ";
    printArray(arr);

    return 0;
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
