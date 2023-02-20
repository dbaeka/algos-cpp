#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include <limits>

template<typename T>
struct Node {
    T val;
    Node<T> *left;
    Node<T> *right;

    explicit Node(T val, Node<T> *left = nullptr, Node<T> *right = nullptr) : val{val}, left{left}, right{right} {}

    ~Node() {
        delete left;
        delete right;
    }
};

template<typename T>
struct NodeN {
    T val;
    std::vector<NodeN<T> *> children;

    explicit NodeN(T val, std::vector<NodeN<T> *> children = {}) : val{val}, children{children} {}
};

template<typename T, typename Iter, typename F>
Node<T> *build_tree(Iter &it, F f) {
    std::string val = *it;
    ++it;
    if (val == "x") return nullptr;
    Node<T> *left = build_tree<T>(it, f);
    Node<T> *right = build_tree<T>(it, f);
    return new Node<T>{f(val), left, right};
}

template<typename T, typename Iter, typename F>
NodeN<T> *build_tree_nary(Iter &it, F f) {
    std::string val = *it;
    ++it;
    int num = std::stoi(*it);
    ++it;
    std::vector<NodeN<T> *> children;
    for (int i = 0; i < num; ++i) {
        children.emplace_back(build_tree_nary<T>(it, f));
    }
    return new NodeN<T>{f(val), std::move(children)};
}


template<typename T, typename F>
void format_tree(Node<T> *root, F f, std::vector<std::string> &out) {
    if (root == nullptr) {
        out.emplace_back("x");
        return;
    }
    out.emplace_back(f(root->val));
    format_tree(root->left, f, out);
    format_tree(root->right, f, out);
}

template<typename T>
std::vector<T> get_words() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    std::vector<T> v;
    std::copy(std::istream_iterator<T>{ss}, std::istream_iterator<T>{}, std::back_inserter(v));
    return v;
}

template<typename T>
T get_word() {
    std::string line;

    std::getline(std::cin, line);
    std::istringstream ss{line};

    T input;
    ss >> input;

    return input;
}

template<typename T>
void put_words(const std::vector<T> &v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
}

template<typename T>
void put_word(const T &value) {
    std::cout << value << std::endl;
}
//
//void ignore_line() {
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//}
