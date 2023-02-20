#include <iostream>
#include <vector>
#include "dfs.h"

void dfs() {
    std::cout << "Choose a dfs option" << std::endl;
    std::string options[]{"In-order traversal", "Pre-order traversal", "Post-order traversal", "DFS Search",
                          "Find Tree Max Depth", "Count Visible Nodes", "Balanced Binary Tree Detect",
                          "Invert Binary Tree", "Valid BST", "LCA"};
    int count = 1;
    for (const auto &option: options) {
        printf("%d. %s\n", count, option.c_str());
        count++;
    }

    int choice = get_word<int>();

    std::vector<std::string> list;
    Node<int> *root, *res_node;

    auto stoi_lambda = [](auto s) { return std::stoi(s); };
    auto to_str_lambda = [](auto v) { return std::to_string(v); };

    list = get_words<std::string>();
    auto root_it = list.begin();

    root = build_tree<int>(root_it, stoi_lambda);

    int target, res_int, target2;

    switch (choice) {
        case 1:
            in_order_traversal(root);
            break;
        case 2:
            pre_order_traversal(root);
            break;
        case 3:
            post_order_traversal(root);
            break;
        case 4:
            target = get_word<int>();
            dfs_search(root, target);
            break;
        case 5:
            res_int = root ? find_tree_max_depth(root) - 1 : 0;
            break;
        case 6:
            res_int = visible_tree_node(root, std::numeric_limits<int>::min());
            break;
        case 7:
            res_int = balanced_binary_tree(root);
            break;
        case 8:
            res_node = invert_binary_tree(root);
            break;
        case 9:
            res_int = valid_bst(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            break;
        case 10:
            target = get_word<int>();
            target2 = get_word<int>();
            res_node = lca(root, find_node(root, target), find_node(root, target2));
            break;
        default:
            break;
    }
}

void in_order_traversal(Node<int> *root) {
    if (root != nullptr) {
        in_order_traversal(root->left);
        std::cout << root->val << std::endl;
        in_order_traversal(root->right);
    }
}

void pre_order_traversal(Node<int> *root) {
    if (root != nullptr) {
        std::cout << root->val << std::endl;
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}


void post_order_traversal(Node<int> *root) {
    if (root != nullptr) {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        std::cout << root->val << std::endl;
    }
}

Node<int> *dfs_search(Node<int> *root, int target) {
    if (root == nullptr) return nullptr;
    if (root->val == target) return root;
    Node<int> *left = dfs_search(root->left, target);
    if (left != nullptr) return left;
    return dfs_search(root->right, target);
}

int find_tree_max_depth(Node<int> *root) {
    if (root == nullptr) return 0;
    return std::max(find_tree_max_depth(root->left), find_tree_max_depth(root->right)) + 1;
}

int visible_tree_node(Node<int> *root, int max_so_far) {
    if (root == nullptr) return 0;
    int total = 0;
    int new_max = std::max(root->val, max_so_far);
    if (root->val >= max_so_far) total++;
    total += visible_tree_node(root->left, new_max) + visible_tree_node(root->right, new_max);
    return total;
}

int balanced_binary_tree(Node<int> *root) {
    if (root == nullptr) return 0;
    int left_height = balanced_binary_tree(root->left);
    int right_height = balanced_binary_tree(root->right);
    if (std::abs(left_height - right_height) > 1) return -1;
    return std::max(left_height, right_height) + 1;
    // for each subtree its height when it doesn't exceed the 1 difference is the max of its left or right subtree
}

Node<int> *invert_binary_tree(Node<int> *root) {
    if (root == nullptr) return nullptr;
    Node<int> *left_subtree = invert_binary_tree(root->left);
    Node<int> *right_subtree = invert_binary_tree(root->right);
    root->left = right_subtree;
    root->right = left_subtree;
    return root;
}

bool find_in_bst(Node<int> *root, int val) {
    if (root == nullptr) return false;
    if (root->val == val) return true;
    else if (val < root->val) return find_in_bst(root->left, val);
    else return find_in_bst(root->right, val);
}

Node<int> *find_node(Node<int> *root, int target) {
    if (root == nullptr || root->val == target) return root;
    Node<int> *left = find_node(root->left, target);
    if (left != nullptr) return left;
    return find_node(root->right, target);
}

Node<int> *insert_in_bst(Node<int> *root, int val) {
    if (root == nullptr) return new Node<int>(val);
    if (val < root->val) {
        root->left = insert_in_bst(root->left, val);
    } else if (val > root->val) {
        root->right = insert_in_bst(root->right, val);
    }
    return root;
}

Node<int> *find_min_in_bst(Node<int> *root) {
    auto current = root;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node<int> *delete_in_bst(Node<int> *root, int val) {
    if (root == nullptr) return nullptr;
    if (val > root->val) root->right = delete_in_bst(root->right, val);
    else if (val < root->val) root->left = delete_in_bst(root->left, val);
    else {
        // Delete here
        // 1. if no children
        // 1. if one child
        // 2. else find leftmost node in right subtree, remove and make node
        if (root->right == nullptr && root->left == nullptr) {
            return nullptr;
        } else if (root->left == nullptr) {
            auto temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            auto temp = root->left;
            delete root;
            return temp;
        }
        // find the leftmost node in right subtree
        auto successor = find_min_in_bst(root->right);
        // replace current node
        root->val = successor->val; // we swapped values because it might be more efficient
        // left is untouched, node was replaced, so modify right to reflect
        root->right = delete_in_bst(root->right, successor->val);
    }
    return root;
}

bool valid_bst(Node<int> *root, int min, int max) {
    if (root == nullptr) return true;
    if (!(min < root->val && root->val < max)) return false;
    return valid_bst(root->left, min, root->val) && valid_bst(root->right, root->val, max);
}

Node<int> *lca(Node<int> *root, Node<int> *node1, Node<int> *node2) {
    if (root == nullptr) return nullptr;

    // check if node found as current and return
    if (root == node1 || root == node2) return root;
    Node<int> *left = lca(root->left, node1, node2);
    Node<int> *right = lca(root->right, node1, node2);

    // found both nodes in both subtrees at this point so just return the current node as the lca
    if (left && right) return root;

    // at this point, left and right can't be both non-null since we checked above
    // bubble up the node as the right or left subtree of the parent. akin to moving a level higher because
    // the level still does not contain both nodes for both subtrees
    if (left) return left;
    if (right) return right;

    // traversed a subtree where none where found to be node 1 or node 2
    return nullptr;
}