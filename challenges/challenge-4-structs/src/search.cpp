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

/* int MAX_HEIGHT = 5; */
/* int LEVEL_PROBABILITY = 10; */

/* int MAX_HEIGHT = 50; */
/* int LEVEL_PROBABILITY = 2; */

/* int MAX_HEIGHT = 3; */
/* int LEVEL_PROBABILITY = 10; */

/* int MAX_HEIGHT = 13; */
/* int LEVEL_PROBABILITY = 2; */

/* int MAX_HEIGHT = 3; */
/* int LEVEL_PROBABILITY = 2; */


int MAX_HEIGHT = 50;
int LEVEL_PROBABILITY = 2;

int main(int argc, char** argv) {

    // init the skip list and list
    Skiplist skiplist = skiplistCreate();
    SLList list;
    SLList_init(&list);
    bool use_skiplists = false;

    if (argc == 3 && strcmp(argv[2], "--skiplist") == 0) {
        use_skiplists = true;
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
