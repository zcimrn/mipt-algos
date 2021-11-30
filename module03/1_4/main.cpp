// https://contest.yandex.com/contest/32613/run-report/59616734

#include <iostream>
#include <vector>
#include <queue>

struct node {
    int key;
    node *l, *r;

    node() : key {0}, l {0}, r {0} {}

    node(int key) : key {key} {}

    node(int key, node *l, node *r) : key {key}, l {l}, r {r} {}
};

void add(node *root, int key) {
    for (;;) {
        if (key < root->key && root->l) {
            root = root->l;
            continue;
        }
        if (key >= root->key && root->r) {
            root = root->r;
            continue;
        }
        break;
    }
    (key < root->key ? root->l : root->r) = new node(key);
}

void solve(std::vector<int>& a) {
    int n = a.size();
    node *root = new node(a[0]);
    for (int i = 1; i < n; add(root, a[i++]));
    std::queue<node*> q;
    q.push(root);
    for (int i = 0; q.size();) {
        root = q.front();
        q.pop();
        a[i++] = root->key;
        if (root->l) {
            q.push(root->l);
        }
        if (root->r) {
            q.push(root->r);
        }
    }
}

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
    std::vector<int> a(n);
    for (int i = 0; i < n; std::cin >> a[i++]);
    solve(a);
    for (int x : a) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    return 0;
}

