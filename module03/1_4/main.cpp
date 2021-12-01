// https://contest.yandex.com/contest/32613/run-report/59702907

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

    BinarySearchTree(const T& key, Node* left, Node* right) :
        key{key}, left{left}, right{right} {}

public:
    BinarySearchTree() = default;

    BinarySearchTree(const Node&) = delete;

    BinarySearchTree& operator=(const Node&) = delete;

    BinarySearchTree(const std::vector<T>& keys) {
        for (auto key : keys) {
            insert(key);
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

    std::vector<T> LevelOrderTraverse() {
        std::vector<T> keys(size);
        if (size == 0) {
            return std::move(keys);
        }
        std::queue<Node*> q;
        q.push(this);
        for (unsigned i = 0; q.size(); i++) {
            auto node = q.front();
            q.pop();
            keys[i] = node->key;
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        return std::move(keys);
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
    std::vector<int> keys(n);
    for (int i = 0; i < n; std::cin >> keys[i++]);
    BinarySearchTree<int> binarySearchTree(keys);
    keys = binarySearchTree.LevelOrderTraverse();
    for (int key : keys) {
        std::cout << key << ' ';
    }
    std::cout << std::endl;
    return 0;
}

