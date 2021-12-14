// https://contest.yandex.com/contest/32613/run-report/61067251

#include <iostream>
#include <queue>

template <class T>
class AVLTree {
private:
    struct Node {
        T key{};
        int height = 1, count = 1;
        Node *left{}, *right{};

        Node(const T& key, int height = 1, int count = 1, Node* left = nullptr, Node* right = nullptr)
            : key{key}, height{height}, count{count}, left{left}, right{right} {}
    };

    Node* root{};

    int get_height(Node* node) const {
        return node == nullptr ? 0 : node->height;
    }

    int get_count(Node* node) const {
        return node == nullptr ? 0 : node->count;
    }

    void update(Node* node) {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
        node->count = get_count(node->left) + get_count(node->right) + 1;
    }

    int get_balance(Node* node) const {
        return get_height(node->left) - get_height(node->right);
    }

    Node* rotate_right(Node* node) {
        auto left = node->left;
        node->left = left->right;
        left->right = node;
        update(node);
        update(left);
        return left;
    }

    Node* rotate_left(Node* node) {
        auto right = node->right;
        node->right = right->left;
        right->left = node;
        update(node);
        update(right);
        return right;
    }

    Node* balance(Node* node) {
        if (get_balance(node) == -2) {
            if (get_balance(node->right) > 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        if (get_balance(node) == 2) {
            if (get_balance(node->left) < 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        update(node);
        return node;
    }

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
        return balance(node);
    }

    Node* get_min_rec(Node* node) const {
        return node->left == nullptr ? node : get_min_rec(node->left);
    }

    Node* remove_min_rec(Node* node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = remove_min_rec(node->left);
        return balance(node);
    }

    Node* remove_rec(Node* node, const T& key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = remove_rec(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove_rec(node->right, key);
        }
        else {
            auto left = node->left, right = node->right;
            delete node;
            if (right == nullptr) {
                return left;
            }
            node = get_min_rec(right);
            node->right = remove_min_rec(right);
            node->left = left;
        }
        return balance(node);
    }

    const T& get_kth_order_stat_rec(Node* node, int i) const {
        auto count = get_count(node->left);
        if (i < count) {
            return get_kth_order_stat_rec(node->left, i);
        }
        else if (i > count) {
            return get_kth_order_stat_rec(node->right, i - count - 1);
        }
        else {
            return node->key;
        }
    }

    void debug_rec(Node* node, char lr = 0, std::string margin = "") const {
        auto left_margin = margin, right_margin = margin;
        if (lr == 'l') {
            left_margin += "            ";
            right_margin += " |          ";
            margin += " '----------";
        }
        else if (lr == 'r') {
            left_margin += " |          ";
            right_margin += "            ";
            margin += " ,----------";
        }
        if (node->right != nullptr) {
            debug_rec(node->right, 'r', right_margin);
        }
        if (lr) {
            std::cerr << margin;
        }
        std::cerr << '(' << node->key << ' ' << node->height << ' ' << node->count << ' ' << node->left << ' ' << node->right << ')' << std::endl;
        if (node->left != nullptr) {
            debug_rec(node->left, 'l', left_margin);
        }
    }

public:
    AVLTree() = default;

    AVLTree(const AVLTree&) = delete;

    AVLTree(const AVLTree&&) = delete;

    AVLTree& operator=(const AVLTree&) = delete;

    AVLTree& operator=(const AVLTree&&) = delete;

    ~AVLTree() {
        std::queue<Node*> q;
        q.push(root);
        for (Node* node; q.size();) {
            node = q.front();
            q.pop();
            if (node != nullptr) {
                q.push(node->left);
                q.push(node->right);
                delete node;
            }
        }
    }

    void insert(const T& key) {
        root = insert_rec(root, key);
    }

    void remove(const T& key) {
        root = remove_rec(root, key);
    }

    const T& get_kth_order_stat(int i) const {
        return get_kth_order_stat_rec(root, i);
    }

    void debug() const {
        std::cerr << std::endl;
        if (root != nullptr) {
            debug_rec(root);
        }
        std::cerr << std::endl;
    }
};

int main() {
    int n;
    std::cin >> n;
    AVLTree<int> avl_tree;
    for (int i = 0, a, k; i < n; i++) {
        std::cin >> a >> k;
        if (a > 0) {
            avl_tree.insert(a);
        }
        else {
            avl_tree.remove(std::abs(a));
        }
        std::cout << avl_tree.get_kth_order_stat(k) << std::endl;
    }
    return 0;
}
