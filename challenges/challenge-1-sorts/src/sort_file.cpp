#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sorts.h"

void printUsage() {
    std::cout << "Usage: program <file> <flags?>\n";
    std::cout << "Flags: quicksort, insertsort, heapsort, quicksort-alt\n"; 
    std::cout << "  - Run without flags to run all sorts\n";
    std::cout << "  - Run with any number of flags to run selected sorts\n";
}

int main(int argc, char** argv) {
    // perform all sorts on scaling data
    if (argc < 2) {
        printUsage();
        return 1;
    }

    bool quicksort = false;
    bool insertsort = false;
    bool heapsort = false;
    bool quicksort_alt = false;

    if (argc == 2) 
        quicksort = insertsort = heapsort = quicksort_alt = true;

    // Collect flags from arguments
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "quicksort") {
            quicksort = true;
        } else if (arg == "insertsort") {
            insertsort = true;
        } else if (arg == "heapsort") {
            heapsort = true;
        } else if (arg == "quicksort-alt") {
            quicksort_alt = true;
        } else {
            std::cerr << "Skipping unknown sort: " << arg << std::endl;
        }
    }

    const char* filename = argv[1];
    std::ifstream inputFile(filename);
    if(!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    std::string line;
    std::cout << "Loading file";
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int number;
        while(iss >> number) {
            numbers.push_back(number);
        }
    }
    std::cout << " - done\n\n";
    inputFile.close();
    int* input = &numbers[0];
    
    if (quicksort) {
        std::cout << "QuickSort";
        QuickSort(input, numbers.size());
        std::cout << " - done\n";
    }
    if (quicksort_alt) {
        std::cout << "QuickSort (alt)";
        QuickSortAlt(input, numbers.size());
        std::cout << " - done\n";
    }
    if (insertsort) {
        std::cout << "InsertSort";
        InsertSort(input, numbers.size());
        std::cout << " - done\n";
    }
    if (heapsort) {
        std::cout << "HeapSort";
        HeapSort(input, numbers.size());
        std::cout << " - done\n";
    }

    return 0;
}
