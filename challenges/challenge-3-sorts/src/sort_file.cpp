#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "sorts.h"

int main(int argc, char** argv) {
    // perform all sorts on scaling data
    const char* filename = argv[2];
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
    
    if (strcmp(argv[1], "quicksort") == 0) {
        QuickSort(input, numbers.size());
    } else if (strcmp(argv[1], "quicksort2") == 0) {
        QuickSortBad(input, numbers.size());
    } else if (strcmp(argv[1], "insertsort") == 0) {
        InsertSort(input, numbers.size());
    } else if (strcmp(argv[1], "heapsort") == 0) {
        HeapSort(input, numbers.size());
    } else {
        std::cerr << "Unknown sort " << argv[1];
    }

    return 0;
}
