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
    std::cout << "Flags: quicksort, insertsort, heapsort, quicksort2; run without flags to run all sorts.\n";
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
    bool quicksort2 = false;

    if (argc == 2) 
        quicksort = insertsort = heapsort = quicksort2 = true;

    // Collect flags from arguments
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "quicksort") {
            quicksort = true;
        } else if (arg == "insertsort") {
            insertsort = true;
        } else if (arg == "heapsort") {
            heapsort = true;
        } else if (arg == "quicksort2") {
            quicksort2 = true;
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
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int number;
        while(iss >> number) {
            numbers.push_back(number);
        }
    }
    inputFile.close();
    int* input = &numbers[0];
    
    if (quicksort) QuickSort(input, numbers.size());
    if (quicksort2) QuickSortAlt(input, numbers.size());
    if (insertsort) InsertSort(input, numbers.size());
    if (heapsort) HeapSort(input, numbers.size());

    return 0;
}
