// https://contest.yandex.com/contest/36361/run-report/66620048

#include <iostream>
#include <set>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> read_graph(int n, int m) {
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int v, u, l;
        std::cin >> v >> u >> l;
        if (v != u) {
            graph[v].push_back({u, l});
            graph[u].push_back({v, l});
        }
    }
    return std::move(graph);
}

int find_min_way(const std::vector<std::vector<std::pair<int, int>>>& graph, int a, int b) {
    int n = graph.size();
    std::set<std::pair<int, int>> s;
    s.insert({0, a});
    std::vector<bool> used(n);
    std::vector<int> min_way(n, 2e9);
    min_way[a] = 0;
    for (int v; s.size() > 0;) {
        v = s.begin()->second;
        s.erase(s.begin());
        used[v] = true;
        for (auto [u, l] : graph[v]) {
            if (!used[u] && min_way[v] + l < min_way[u]) {
                s.erase({min_way[u], u});
                s.insert({min_way[v] + l, u});
                min_way[u] = min_way[v] + l;
            }
        }
    }
    return min_way[b];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    auto graph = read_graph(n, m);
    int a, b;
    std::cin >> a >> b;
    std::cout << find_min_way(graph, a, b) << std::endl;
    return 0;
}
