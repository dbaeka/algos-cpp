#include <iostream>
#include <string>
#include "utilities.h"
#include "binary_search.h"
#include "sorting.h"
#include "dfs.h"
#include "backtracking.h"

int main() {
    std::cout << "Welcome to the Algo Runner!" << std::endl;
    std::cout << "Choose an option to run the algorithm: " << std::endl;
    std::string options[]{"Sorting", "Binary Search", "DFS", "Backtracking"};
    int count = 1;
    for (const auto &option: options) {
        printf("%d. %s\n", count, option.c_str());
        count++;
    }

    int choice = get_word<int>();

    switch (choice) {
        case 1:
            sorting();
            break;
        case 2:
            binary_search();
            break;
        case 3:
            dfs();
            break;
        case 4:
            backtracking();
            break;
        default:
            break;
    }
    return 0;
}
