//
// Created by delmwin on 1/2/23.
//

#include <unordered_map>
#include "backtracking.h"


void backtracking() {
    std::cout << "Choose a backtracking option" << std::endl;
    std::string options[]{"Ternary Tree Path", "N-Letter Word Composition", "Phone Letter Combo", "Partitioning"};
    int count = 1;
    for (const auto &option: options) {
        printf("%d. %s\n", count, option.c_str());
        count++;
    }

    int choice = get_word<int>();

    std::vector<std::string> list;
    NodeN<int> *root, *res_node;

    auto stoi_lambda = [](auto s) { return std::stoi(s); };
    auto to_str_lambda = [](auto v) { return std::to_string(v); };

    int target, res_int, target2;

    std::vector<std::string>::iterator root_it;

    std::vector<std::string> res_vec;

    std::vector<std::vector<std::string>> res_vec_vec;

    std::string target_str;

    switch (choice) {
        case 1:
            list = get_words<std::string>();
            root_it = list.begin();
            root = build_tree_nary<int>(root_it, stoi_lambda);
            ternary_tree_paths(root, {}, res_vec);
            break;
        case 2:
            target = get_word<int>();
            n_letter_composition(target, 0, "", res_vec);
            break;
        case 3:
            target_str = get_word<std::string>();
            letter_combination_phone_digit({}, res_vec, target_str, 0);
            break;
        case 4:
            target_str = get_word<std::string>();
            partition(res_vec_vec, {}, target_str, 0);
            break;
        default:
            break;
    }
}

void ternary_tree_paths(NodeN<int> *root, std::vector<std::string> path, std::vector<std::string> &res) {
    // handle the leaf node here
    if (root->children.size() == 0) {
        path.emplace_back(std::to_string(root->val));

        // handle result building here into string
        std::string s = "";
        for (int i = 0; i < path.size(); i++) {
            if (i == path.size() - 1) {
                s += path[i];
            } else {
                s += path[i] + "->";
            }
        }
        res.emplace_back(s);

        // return or not but next loop won't run cos of size 0
        return;
    }

    // loop through the internal nodes depth first
    for (auto &child: root->children) {
        if (child) {
            path.emplace_back(std::to_string(root->val));
            ternary_tree_paths(child, path, res);
            path.pop_back();
        }
    }
}

void n_letter_composition(int n, int start_index, std::string path, std::vector<std::string> &res) {
    if (start_index == n) { // is leaf block
        std::string s(path.begin(), path.end());
        res.emplace_back(s);
        return;
    }
    for (std::string edge: {"a", "b"}) {
        path += edge;
        n_letter_composition(n, start_index + 1, path, res);
        path.pop_back();
    }
}

std::unordered_map<char, std::string> keyboard = {{'2', "abc"},
                                                  {'3', "def"},
                                                  {'4', "ghi"},
                                                  {'5', "jkl"},
                                                  {'6', "mno"},
                                                  {'7', "pqrs"},
                                                  {'8', "tuv"},
                                                  {'9', "wxyz"}};

void letter_combination_phone_digit(std::vector<char> path, std::vector<std::string> &res, std::string digits, int i) {
    if (digits.size() == i) {
        std::string s(path.begin(), path.end());
        res.emplace_back(s);
        return;
    }
    for (auto edge: keyboard[digits[i]]) {
        path.emplace_back(edge);
        letter_combination_phone_digit(path, res, digits, i + 1);
        path.pop_back();
    }
}

bool is_palindrome(std::string word) {
    int l = 0, r = word.size() - 1;
    while (l < r) {
        if (word[l] != word[r]) return false;
        r--;
        l++;
    }
    return true;
}

void partition(std::vector<std::vector<std::string>> &res, std::vector<std::string> path, std::string s, int start) {
    if (s.size() == start) {
        std::vector<std::string> li(path);
        res.emplace_back(li);
    }

    for (int end = start; end < s.size(); end++) {
        if (is_palindrome(s.substr(start, end + 1 - start))) {
            path.emplace_back(s.substr(start, end + 1 - start));
            partition(res, path, s, end + 1);
            path.pop_back();
        }
    }
}