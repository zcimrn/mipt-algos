// https://contest.yandex.com/contest/35212/run-report/65264355

#include <iostream>
#include <vector>

std::vector<std::vector<int>> read_tree(int n) {
    std::vector<std::vector<int>> tree(n);
    for (int i = 0, v, u; i < n - 1; i++) {
        std::cin >> v >> u;
        if (v > u) {
            std::swap(v, u);
        }
        tree[v].push_back(u);
    }
    return std::move(tree);
}

void count_for_root(
    const std::vector<std::vector<int>>& tree,
    std::vector<int>& count,
    std::vector<int>& ans,
    int v
) {
    for (auto u : tree[v]) {
        count_for_root(tree, count, ans, u);
        count[v] += count[u];
        ans[v] += ans[u];
    }
    ans[v] += count[v];
    count[v]++;
}

void count_for_all(
    const std::vector<std::vector<int>>& tree,
    std::vector<int>& count,
    std::vector<int>& ans,
    int v
) {
    for (auto u : tree[v]) {
        ans[u] = ans[v] - count[u] + count[v] - count[u];
        count[u] = count[v];
        count_for_all(tree, count, ans, u);
    }
}

void print_ans(const std::vector<int>& ans) {
    for (auto x : ans) {
        std::cout << x << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;
    auto tree = read_tree(n);
    std::vector<int> count(n), ans(n);
    count_for_root(tree, count, ans, 0);
    count_for_all(tree, count, ans, 0);
    print_ans(ans);
    return 0;
}
