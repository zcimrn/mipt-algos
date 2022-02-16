#include <iostream>
#include <vector>
#include <queue>

template <class T>
class BinarySearchTree {
    using Node = BinarySearchTree<T>;

private:
    T key{};
    unsigned size = 0;
    Node *left = nullptr, *right = nullptr;

    BinarySearchTree(const T& key) : key{key} {}

public:
    BinarySearchTree() = default;

    BinarySearchTree(const Node&) = delete;

    BinarySearchTree& operator=(const Node&) = delete;

    BinarySearchTree(const std::vector<T>& keys) {
        for (auto key : keys) {
            insert(key);
        }
    }

    template <class Y>
    BinarySearchTree(const std::vector<std::pair<T, Y>>& items) {
        for (auto item : items) {
            insert(item.first);
        }
    }

    ~BinarySearchTree() {
        if (left != nullptr) {
            delete left;
        }
        if (right != nullptr) {
            delete right;
        }
    }

    unsigned get_size() {
        return size;
    }

    void insert(T key) {
        size++;
        if (size == 1) {
            this->key = key;
            return;
        }
        auto node = this;
        for (;;) {
            if (key < node->key && node->left != nullptr) {
                node = node->left;
            }
            else if (key >= node->key && node->right != nullptr) {
                node = node->right;
            }
            else {
                break;
            }
        }
        (key < node->key ? node->left : node->right) = new Node(key);
    }

    unsigned get_depth() {
        if (size == 0) {
            return 0;
        }
        std::queue<std::pair<Node*, unsigned>> q;
        q.push({this, 1});
        unsigned depth = 0;
        for (; q.size();) {
            auto frame = q.front();
            q.pop();
            auto node = frame.first;
            auto cur_depth = frame.second;
            depth = std::max(depth, cur_depth);
            if (node->left != nullptr) {
                q.push({node->left, cur_depth + 1});
            }
            if (node->right != nullptr) {
                q.push({node->right, cur_depth + 1});
            }
        }
        return depth;
    }
};

template <class X, class Y>
class Treap {
    using Node = Treap<X, Y>;

private:
    X key{};
    Y priority{};
    unsigned size = 0;
    Node *left = nullptr, *right = nullptr;

    Treap(const X& key, const Y& priority) : key{key}, priority{priority} {}

    Treap(Node* node) :
        key{node->key}, priority{node->priority}, left{node->left}, right{node->right} {}

public:
    Treap()  = default;

    Treap(const Node&) = delete;

    Treap& operator=(const Node&) = delete;

    Treap(const std::vector<std::pair<X, Y>>& items) {
        for (auto item : items) {
            insert(item.first, item.second);
        }
    }

    ~Treap() {
        if (left != nullptr) {
            delete left;
        }
        if (right != nullptr) {
            delete right;
        }
    }

    void insert(const X& key, const Y& priority) {
        size++;
        if (size == 1) {
            this->key = key;
            this->priority = priority;
            return;
        }
        auto node = this;
        for (;;) {
            if (key < node->key && priority <= node->priority) {
                if (node->left == nullptr) {
                    node->left = new Node(key, priority);
                    return;
                }
                node = node->left;
            }
            else if (priority <= node->priority) {
                if (node->right == nullptr) {
                    node->right = new Node(key, priority);
                    return;
                }
                node = node->right;
            }
            else {
                break;
            }
        }
        auto new_node = new Node(node);
        node->key = key;
        node->priority = priority;
        node->left = nullptr;
        node->right = nullptr;
        std::swap(node, new_node);
        auto left = new_node, right = new_node;
        for (;;) {
            if (node == nullptr) {
                left->right = nullptr;
                right->left = nullptr;
                break;
            }
            else if (node->key < key) {
                left->right = node;
                left = node;
                node = node->right;
            }
            else {
                right->left = node;
                right = node;
                node = node->left;
            }
        }
        std::swap(new_node->left, new_node->right);
    }

    unsigned get_depth() {
        if (size == 0) {
            return 0;
        }
        std::queue<std::pair<Node*, unsigned>> q;
        q.push({this, 1});
        unsigned depth = 0;
        for (; q.size();) {
            auto frame = q.front();
            q.pop();
            auto node = frame.first;
            auto cur_depth = frame.second;
            depth = std::max(depth, cur_depth);
            if (node->left != nullptr) {
                q.push({node->left, cur_depth + 1});
            }
            if (node->right != nullptr) {
                q.push({node->right, cur_depth + 1});
            }
        }
        return depth;
    }
};



int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cerr.tie(0);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cerr.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.precision(6);
    std::cerr.precision(16);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> items(n);
    for (int i = 0; i < n; std::cin >> items[i].first >> items[i++].second);
    BinarySearchTree<int> bst(items);
    Treap<int, int> treap(items);
    std::cout << abs(bst.get_depth() - treap.get_depth()) << std::endl;
    return 0;
}
