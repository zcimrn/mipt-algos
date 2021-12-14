// https://contest.yandex.com/contest/32613/run-report/61105596

#include <iostream>
#include <queue>

template <class Node>
class Tree {
protected:
    Node* root{};

    void destruct_rec(Node* node) {
        if (node != nullptr) {
            destruct_rec(node->left);
            destruct_rec(node->right);
            delete node;
        }
    }

    void debug_rec(Node* node, char lr = 0, std::string margin = "") const {
        auto left_margin = margin, right_margin = margin;
        if (lr == 'l') {
            left_margin += "        ";
            right_margin += " |      ";
            margin += " '------";
        }
        else if (lr == 'r') {
            left_margin += " |      ";
            right_margin += "        ";
            margin += " ,------";
        }
        if (node->right != nullptr) {
            debug_rec(node->right, 'r', right_margin);
        }
        if (lr) {
            std::cerr << margin;
        }
        node->debug();
        if (node->left != nullptr) {
            debug_rec(node->left, 'l', left_margin);
        }
    }

public:
    Tree() = default;

    Tree(const Tree&) = delete;

    Tree(const Tree&&) = delete;

    Tree& operator=(const Tree&) = delete;

    Tree& operator=(const Tree&&) = delete;

    ~Tree() {
        destruct_rec(root);
    }

    void debug() const {
        std::cerr << std::endl;
        if (root != nullptr) {
            debug_rec(root);
        }
        std::cerr << std::endl;
    }

    int get_width() const {
        std::queue<std::pair<Node*, int>> q;
        q.push({root, 1});
        int width = 0;
        for (int cur_depth = 0, cur_width = 0; q.size();) {
            auto node = q.front().first;
            auto depth = q.front().second;
            q.pop();
            if (depth != cur_depth) {
                cur_depth = depth;
                width = std::max(width, cur_width);
                cur_width = 0;
            }
            if (node != nullptr) {
                cur_width++;
                q.push({node->left, depth + 1});
                q.push({node->right, depth + 1});
            }
        }
        return width;
    }
};

template <class T>
struct BSTreeNode {
    T key{};
    BSTreeNode<T> *left{}, *right{};

    BSTreeNode(const T& key, BSTreeNode* left = nullptr, BSTreeNode* right = nullptr)
        : key{key}, left{left}, right{right} {}

    void debug() const {
        std::cerr << '(' << key << ')' << std::endl;
    }
};

template <class T>
class BSTree : public Tree<BSTreeNode<T>> {
private:
    using Node = BSTreeNode<T>;

    Node* insert_rec(Node* node, const T& key) {
        if (node == nullptr) {
            return new Node{key};
        }
        if (key < node->key) {
            node->left = insert_rec(node->left, key);
        }
        else {
            node->right = insert_rec(node->right, key);
        }
        return node;
    }

public:
    void insert(const T& key) {
        this->root = insert_rec(this->root, key);
    }
};

template <class X, class Y>
struct TreapNode {
    X key{};
    Y priority{};
    TreapNode<X, Y> *left{}, *right{};

    TreapNode(const X& key, const Y& priority, TreapNode* left = nullptr, TreapNode* right = nullptr)
        : key{key}, priority{priority}, left{left}, right{right} {}

    void debug() const {
        std::cerr << '(' << key << ", " << priority << ')' << std::endl;
    }
};

template <class X, class Y>
class Treap : public Tree<TreapNode<X, Y>> {
private:
    using Node = TreapNode<X, Y>;

    std::pair<Node*, Node*> split(Node* node, const X& key) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        if (node->key < key) {
            auto nodes = split(node->right, key);
            node->right = nodes.first;
            return {node, nodes.second};
        }
        else {
            auto nodes = split(node->left, key);
            node->left = nodes.second;
            return {nodes.first, node};
        }
    }

    Node* insert_rec(Node* node, const X& key, const Y& priority) {
        if (node == nullptr) {
            return new Node{key, priority};
        }
        if (priority > node->priority) {
            auto children = split(node, key);
            return new Node{key, priority, children.first, children.second};
        }
        if (key < node->key) {
            node->left = insert_rec(node->left, key, priority);
        }
        else {
            node->right = insert_rec(node->right, key, priority);
        }
        return node;
    }

public:
    void insert(const X& key, const Y& priority) {
        this->root = insert_rec(this->root, key, priority);
    }
};

int main() {
    int n;
    std::cin >> n;
    BSTree<int> bst;
    Treap<int, int> treap;
    for (int i = 0, key, priority; i < n; i++) {
        std::cin >> key >> priority;
        bst.insert(key);
        treap.insert(key, priority);
    }
    std::cout << treap.get_width() - bst.get_width() << std::endl;
    return 0;
}
