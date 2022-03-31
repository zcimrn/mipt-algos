// https://contest.yandex.com/contest/36361/run-report/66619614

#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> read_graph(int n, int m) {
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int v, u;
        std::cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    return std::move(graph);
}

int count_diff_ways(const std::vector<std::vector<int>>& graph, int a, int b) {
    int n = graph.size();
    std::queue<int> q;
    q.push(a);
    std::vector<int> depth(n, -1), diff_ways_count(n);
    depth[a] = 0;
    diff_ways_count[a] = 1;
    for (int v; q.size() > 0;) {
        v = q.front();
        q.pop();
        for (int u : graph[v]) {
            if (depth[u] < 0) {
                q.push(u);
                depth[u] = depth[v] + 1;
            }
            if (depth[u] > depth[v]) {
                diff_ways_count[u] += diff_ways_count[v];
            }
        }
    }
    return diff_ways_count[b];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    auto graph = read_graph(n, m);
    int a, b;
    std::cin >> a >> b;
    std::cout << count_diff_ways(graph, a, b) << std::endl;
    return 0;
}
