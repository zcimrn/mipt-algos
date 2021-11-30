// https://contest.yandex.com/contest/32613/run-report/59627289

#include <iostream>
#include <vector>
#include <queue>

template<class T>
class BinarySearchTreeNode {
    T key;
    BinarySearchTreeNode<T> *left = nullptr, *right = nullptr;

public:
    BinarySearchTreeNode(T key) : key{key} {}

    T getKey() {
        return key;
    }

    void setLeft(BinarySearchTreeNode<T> *left) {
        this->left = left;
    }

    BinarySearchTreeNode<T>* getLeft() {
        return left;
    }

    void setRight(BinarySearchTreeNode<T> *right) {
        this->right = right;
    }

    BinarySearchTreeNode<T>* getRight() {
        return right;
    }
};

template<class T>
class BinarySearchTree {
    BinarySearchTreeNode<T> *root = nullptr;

public:
    BinarySearchTree(std::vector<T>& keys) {
        for (auto key : keys) {
            insert(key);
        }
    }

    ~BinarySearchTree() {
        std::queue<BinarySearchTreeNode<T>*> q;
        q.push(root);
        root = nullptr;
        for (BinarySearchTreeNode<T> *node; q.size();) {
            node = q.front();
            q.pop();
            if (node != nullptr) {
                q.push(node->getLeft());
                q.push(node->getRight());
                delete node;
            }
        }
    }

    void insert(T key) {
        if (root == nullptr) {
            root = new BinarySearchTreeNode<T>(key);
            return;
        }
        auto newNode = new BinarySearchTreeNode(key);
        auto node = root;
        for (;;) {
            if (key < node->getKey()) {
                if (node->getLeft() == nullptr) {
                    node->setLeft(newNode);
                    return;
                }
                node = node->getLeft();
            }
            else if (key >= node->getKey()) {
                if (node->getRight() == nullptr) {
                    node->setRight(newNode);
                    return;
                }
                node = node->getRight();
            }
        }
    }

    std::vector<T> BreadthFirstSearch() {
        std::vector<T> keys;
        std::queue<BinarySearchTreeNode<T>*> q;
        q.push(root);
        for (BinarySearchTreeNode<T> *node; q.size();) {
            node = q.front();
            q.pop();
            if (node != nullptr) {
                keys.push_back(node->getKey());
                q.push(node->getLeft());
                q.push(node->getRight());
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
    keys = binarySearchTree.BreadthFirstSearch();
    for (int key : keys) {
        std::cout << key << ' ';
    }
    std::cout << std::endl;
    return 0;
}

