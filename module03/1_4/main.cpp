//https://contest.yandex.com/contest/32613/run-report/59844580

#include <iostream>
#include <vector>
#include <queue>

template <class T>
class Node {
private:
    T key{};
    Node<T> *left{}, *right{};

public:
    Node(const T& key, Node* left = {}, Node* right = {}) :
        key{key}, left{left}, right{right} {}

    void set_key(const T& key) {
        this->key = key;
    }

    const T& get_key() {
        return key;
    }

    void set_left(Node* left) {
        this->left = left;
    }

    bool has_left() {
        return left != nullptr;
    }

    Node* get_left() {
        return left;
    }

    void set_right(Node* right) {
        this->right = right;
    }

    bool has_right() {
        return right != nullptr;
    }

    Node* get_right() {
        return right;
    }

    void debug(char lr = 0, std::string margin = "") {
        auto left_margin = margin, right_margin = margin;
        if (lr == 'l') {
            left_margin += "    ";
            right_margin += " |  ";
            margin += " '--";
        }
        else if (lr == 'r') {
            left_margin += " |  ";
            right_margin += "    ";
            margin += " ,--";
        }
        if (right) {
            right->debug('r', right_margin);
        }
        if (lr) {
            std::cerr << margin + '(' << key << ')' << std::endl;
        }
        else {
            std::cerr << '(' << key << ')' << std::endl;
        }
        if (left) {
            left->debug('l', left_margin);
        }
    }
};

template <class T>
class BinarySearchTree {
private:
    Node<T>* root{};

    std::vector<T> breadth_first_search(bool destruct = false) {
        std::vector<T> keys;
        if (root == nullptr) {
            return std::move(keys);
        }
        std::queue<Node<T>*> q;
        q.push(root);
        for (Node<T>* node; q.size();) {
            node = q.front();
            q.pop();
            if (node->has_left()) {
                q.push(node->get_left());
            }
            if (node->has_right()) {
                q.push(node->get_right());
            }
            if (destruct) {
                delete node;
            }
            else {
                keys.push_back(node->get_key());
            }
        }
        return std::move(keys);
    }


public:
    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree&) = delete;

    BinarySearchTree(const BinarySearchTree&&) = delete;

    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    BinarySearchTree& operator=(const BinarySearchTree&&) = delete;

    void debug() {
        if (root) {
            root->debug();
        }
    }

    BinarySearchTree(const std::vector<T>& keys) {
        for (auto key : keys) {
            insert(key);
        }
    }

    ~BinarySearchTree() {
        breadth_first_search(true);
    }

    void insert(const T& key) {
        if (root == nullptr) {
            root = new Node{key};
            return;
        }
        auto node = root;
        for (;;) {
            if (key < node->get_key() && node->has_left()) {
                node = node->get_left();
            }
            else if (key >= node->get_key() && node->has_right()) {
                node = node->get_right();
            }
            else {
                break;
            }
        }
        if (key < node->get_key()) {
            node->set_left(new Node{key});
        }
        else {
            node->set_right(new Node{key});
        }
    }

    std::vector<T> level_order_traverse() {
        return breadth_first_search();
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> keys(n);
    for (int i = 0; i < n; std::cin >> keys[i++]);
    BinarySearchTree<int> bst(keys);
    keys = bst.level_order_traverse();
    for (int key : keys) {
        std::cout << key << ' ';
    }
    std::cout << std::endl;
    return 0;
}

