#include <string>
#include <iostream>
#include "sorting.h"
#include "utilities.h"


void sorting() {
    std::cout << "Choose a sorting option" << std::endl;
    std::string options[]{"Insertion Sort", "Selection Sort", "Bubble Sort"};
    int count = 1;
    for (const auto &option: options) {
        printf("%d. %s\n", count, option.c_str());
        count++;
    }

    int choice = get_word<int>();

    std::vector<int> unsorted_list = get_words<int>();
    std::vector<int> res;
    switch (choice) {
        case 1:
            res = insertion_sort(unsorted_list);
            break;
        case 2:
            res = selection_sort(unsorted_list);
            break;
        case 3:
            res = bubble_sort(unsorted_list);
            break;
        default:
            break;
    }

    put_words(res);
}

std::vector<int> selection_sort(std::vector<int> unsorted_list) {
    int n = unsorted_list.size();
    for (int i = 0; i < n; i++) {
        int min_index = i;
        for (int j = i; j < n; j++) {
            if (unsorted_list[j] < unsorted_list[min_index]) { // check rest of array for new minimum
                min_index = j;
            }
        }
        // swap current element with new minimum value
        int temp = unsorted_list[i];
        unsorted_list[i] = unsorted_list[min_index];
        unsorted_list[min_index] = temp;
    }
    return unsorted_list;
}

std::vector<int> insertion_sort(std::vector<int> unsorted_list) {
    int n = unsorted_list.size();
    for (int i = 0; i < n; i++) {
        int current = i;
        while (current > 0 && unsorted_list[current] < unsorted_list[current -
                                                                     1]) { // keep swapping current with previous till it gets to the right spot
            int temp = unsorted_list[current];
            unsorted_list[current] = unsorted_list[current - 1];
            unsorted_list[current - 1] = temp;
            current--;
        }
    }
    return unsorted_list;
}

std::vector<int> bubble_sort(std::vector<int> unsorted_list) {
    int n = unsorted_list.size();
    for (int i = n - 1; i >= 0; i--) {
        // after every pass, last element is largest so reduce size to compare in inner loop
        bool swapped = false;
        for (int j = 0; j < i; j++) {
            if (unsorted_list[j] > unsorted_list[j + 1]) { // swap if current bigger than next
                int temp = unsorted_list[j];
                unsorted_list[j] = unsorted_list[j + 1];
                unsorted_list[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) return unsorted_list;
    }
    return unsorted_list;
}