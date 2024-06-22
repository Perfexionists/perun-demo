#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include "skiplist.h"
#include "SLList.h"


int MAX_HEIGHT = 2;
int LEVEL_PROBABILITY = 2;

void printUsage() {
    std::cout << "usage: ./search <file> <skiplist_height> <skiplist_probability>" << std::endl;
}

int main(int argc, char** argv) {

    // init the skip list and list
    Skiplist skiplist = skiplistCreate();
    SLList list;
    SLList_init(&list);
    bool use_skiplists = false;

    if (argc < 2 || argc == 3 || argc > 4) {
        printUsage();
        return 1;
    }

    if (argc == 4) {
        try {
            use_skiplists = true;
            MAX_HEIGHT = std::stoi(argv[2]);
            LEVEL_PROBABILITY = std::stoi(argv[3]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid parameter, must be integers" << std::endl;
            return 1;
        }
    }

    const char* filename = argv[1];
    std::ifstream inputFile(filename);
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int number;
        while(iss >> number) {
            if (use_skiplists) {
                skiplistInsert(skiplist, number);
            } else {
                SLList_insert(&list, number);
            }
        }
    }

    srand(time(NULL));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, INT_MAX-1);

    for (int i = 0; i < 10; i++) {
        if (use_skiplists) {
            SLList_search(&list, i);
        } else {
            skiplistSearch(skiplist, i);
        }
    }

    // Cleanup
    SLList_destroy(&list);
    skiplistDestroy(skiplist);
}
