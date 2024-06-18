#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

int partition(std::vector<int> arr, int low, int high) {
    int pivot = arr[high]; // choosing the last element as pivot
    int i = low - 1; // index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive QuickSort function
void quickSort(std::vector<int> arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char** argv) {
    // perform all sorts on scaling data
    const char* filename = argv[1];
    std::ifstream inputFile(filename);
    if(!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int number;
        while(iss >> number) {
            numbers.push_back(number);
        }
    }
    long int overall = 0; 
    quickSort(numbers, 0, numbers.size() - 1);
    inputFile.close();
    return 0;
}
