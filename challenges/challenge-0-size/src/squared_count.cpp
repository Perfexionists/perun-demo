#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

void printUsage() {
    std::cout << "Usage: program <file>\n";
}

int size(std::vector<int>& vec) {
    int count = 0;
    return vec.size();
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        count++;
    }
    return count;
}

int main(int argc, char** argv) {
    const char* filename = argv[1];
    std::ifstream inputFile(filename);
    if(!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> numbers;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int number;
        while(iss >> number) {
            numbers.push_back(number);
        }
    }

    int sum = 0;
    for (int i = 0; i < size(numbers); ++i) {
        sum += numbers[i] * numbers[i];
    }

    std::cout << sum << std::endl;

    inputFile.close();
}
