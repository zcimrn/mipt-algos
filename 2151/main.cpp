#include <iostream>
#include <vector>

std::vector<std::vector<int>> read_graph(int n) {
    std::vector<std::vector<int>> g(n);
    for (int i = 0, v, u; i < n - 1; i++) {
        std::cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    return std::move(g);
}

void count_depths(const std::vector<std::vector<int>>& g, std::vector<int>& d, int f, int v) {
    for (auto u : g[v]) {
        if (u != f) {
            d[u] = d[v] + 1;
            count_depths(g, d, v, u);
        }
    }
}

int find_root(const std::vector<int>& d) {
    int n = d.size(), root = 0;
    for (int v = 0; v < n; v++) {
        if (d[root] < d[v]) {
            root = v;
        }
    }
    return root;
}

void print_ans(const std::vector<int> d1, const std::vector<int> d2) {
    int n = d1.size();
    for (int i = 0; i < n; i++) {
        std::cout << std::max(d1[i], d2[i]) << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;
    auto graph = read_graph(n);
    std::vector<int> depths(n);
    count_depths(graph, depths, -1, 0);
    int root = find_root(depths);
    std::vector<int> depths1(n);
    count_depths(graph, depths1, -1, root);
    root = find_root(depths1);
    std::vector<int> depths2(n);
    count_depths(graph, depths2, -1, root);
    print_ans(depths1, depths2);
}
