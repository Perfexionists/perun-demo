#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include "sorts.h"

const int MAX_SORT_ARR_LEN = 5000;
const int SORT_ARR_LEN_INC = 50;

int main() {

    // init the rng
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, INT_MAX - 1);

    // perform all sorts on scaling data
    for(int i = SORT_ARR_LEN_INC; i <= MAX_SORT_ARR_LEN; i += SORT_ARR_LEN_INC) {
        int *input = new int[i];
        int *input_save = new int[i];
        for(int j = 0; j < i; j++) {
            input_save[j] = dis(gen);
        }


        for(int j = 0; j < i; j++) {
            input[j] = input_save[j];
        }

        QuickSort(input, i);

        for(int j = 0; j < i; j++) {
            input[j] = input_save[j];
        }

        InsertSort(input, i);

        for(int j = 0; j < i; j++) {
            input[j] = input_save[j];
        }

        HeapSort(input, i);

        delete[] input;
    }

    return 0;
}
