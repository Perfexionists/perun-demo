#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <iostream>
#include "../structures/SLList.h"
#include "../../profile_api.h"

const int list_max_size = 1000000;


int main() {

    // init the list
    SLList list;
    _profapi_register_size_address(&list, false, &list.size);
    SLList_init(&list);

    // perform the operations
    for(int i = 0; i < list_max_size; i++) {
        SLList_insert(&list, i);

        if(i % 1000 == 0) {
            _profapi_using_size_address(&list);
            SLList_search(&list, 0);
        }
    }
    _profapi_using_size_address(&list);
    SLList_destroy(&list);
}
