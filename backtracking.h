#pragma once

#include "utilities.h"

void backtracking();

void ternary_tree_paths(NodeN<int> *root, std::vector<std::string> path, std::vector<std::string> &res);

void n_letter_composition(int n, int start_index, std::string path, std::vector<std::string> &res);

void letter_combination_phone_digit(std::vector<char> path, std::vector<std::string> &res, std::string digits, int i);

void partition(std::vector<std::vector<std::string>> &res, std::vector<std::string> path, std::string s, int start);