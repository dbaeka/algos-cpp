#pragma once

#include "utilities.h"

void dfs();

void in_order_traversal(Node<int> *root);

void pre_order_traversal(Node<int> *root);

void post_order_traversal(Node<int> *root);

Node<int> *dfs_search(Node<int> *root, int target);

int find_tree_max_depth(Node<int> *root);

int visible_tree_node(Node<int> *root, int max_so_far);

int balanced_binary_tree(Node<int> *root);

Node<int> *invert_binary_tree(Node<int> *root);

bool find_in_bst(Node<int> *root, int val);

Node<int> *insert_in_bst(Node<int> *root, int val);

Node<int> *delete_in_bst(Node<int> *root, int val);

Node<int> *find_min_in_bst(Node<int> *root);

bool valid_bst(Node<int> *root, int min, int max);

Node<int> *lca(Node<int> *root, Node<int> *node1, Node<int> *node2);

Node<int> *find_node(Node<int> *root, int target);