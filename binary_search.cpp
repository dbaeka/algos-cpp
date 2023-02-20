#include "binary_search.h"
#include <string>
#include <iostream>
#include "utilities.h"

void binary_search() {
    std::cout << "Choose a binary search option" << std::endl;
    std::string options[]{"Vanilla Binary Search", "First True in Sorted Array",
                          "First Elem Not Smaller Than Target Sorted Array", "First Occurrence of Target Sorted Array",
                          "Square Root Estimate", "Minimum in Rotated Sorted Array", "Peak of Mountain Array"};
    int count = 1;
    for (const auto &option: options) {
        printf("%d. %s\n", count, option.c_str());
        count++;
    }

    int choice = get_word<int>();

    std::vector<int> list;
    int target;

    std::vector<bool> bool_list;

    int res;
    switch (choice) {
        case 1:
            list = get_words<int>();
            target = get_word<int>();
            res = binary_search(list, target);
            break;
        case 2:
            bool_list = get_words<bool>();
            res = find_boundary(bool_list);
            break;
        case 3:
            list = get_words<int>();
            target = get_word<int>();
            res = first_not_smaller(list, target);
            break;
        case 4:
            list = get_words<int>();
            target = get_word<int>();
            res = find_first_occurrence(list, target);
            break;
        case 5:
            target = get_word<int>();
            res = square_root_estimate(target);
            break;
        case 6:
            list = get_words<int>();
            res = find_min_rotated(list);
            break;
        case 7:
            list = get_words<int>();
            res = find_mountain_peak(list);
            break;
        default:
            break;
    }

    put_word(res);
}


int binary_search(std::vector<int> arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) { // equality important for single element list
        int mid = left + (right - left) / 2;
        if (arr.at(mid) == target) return mid;
        if (arr.at(mid) < target) { // discard left half
            left = mid + 1;
        } else { // use right half
            right = mid - 1;
        }
    }
    return -1;
}

int find_boundary(std::vector<bool> arr) {
    int left = 0, right = arr.size() - 1;
    int boundary_index = -1;
    while (left <= right) { // equality important for single element list
        int mid = left + (right - left) / 2;
        if (arr.at(mid)) {
            boundary_index = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }// }
    return boundary_index;
}

int first_not_smaller(std::vector<int> arr, int target) {
    int left = 0, right = arr.size() - 1;
    int boundary_index = -1;
    while (left <= right) { // equality important for single element list
        int mid = left + (right - left) / 2;
        if (arr.at(mid) >= target) {
            boundary_index = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }// }
    return boundary_index;
}

int find_first_occurrence(std::vector<int> arr, int target) {
    int left = 0, right = arr.size() - 1;
    int boundary_index = -1;
    while (left <= right) { // equality important for single element list
        int mid = left + (right - left) / 2;
        if (arr.at(mid) >= target) {
            if (arr.at(mid) == target) {
                boundary_index = mid;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }// }
    return boundary_index;
}

int square_root_estimate(int n) {
    int left = 1, right = n;
    int boundary_index = -1;
    while (left <= right) { // equality important for single element list
        int mid = left + (right - left) / 2;
        if (mid * mid >= n) {
            if (mid * mid == n) { // return early because want value not index
                return mid;
            }
            // get the first occurrence
            boundary_index = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }// }
    return boundary_index - 1; // minus 1 to get truncated and not rounded up
}

int find_min_rotated(std::vector<int> arr) {
    int left = 0, right = arr.size() - 1;
    int boundary_index = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr.at(mid) <= arr.at(arr.size() - 1)) {
            // boundary exists at the last element where either all items are lower or bigger than it
            boundary_index = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return boundary_index;
}

int find_mountain_peak(std::vector<int> arr) {
    int left = 0, right = arr.size() - 1, boundary_index = -1, arr_len = arr.size();
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid == arr_len - 1 || arr[mid] > arr[mid + 1]) {
            boundary_index = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return boundary_index;
}
