#include <iostream>
#include <vector>

bool f(const std::vector<std::vector<int>>& graph, std::vector<int>& colors, int color, int v) {
  colors[v] = color;
  for (int u : graph[v]) {
    if (colors[u] == colors[v] || colors[u] < 0 && f(graph, colors, color ^ 1, u)) {
      return true;
    }
  }
  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int v, u, i = 0; i < m; i++) {
    std::cin >> v >> u;
    graph[v].push_back(u);
    graph[u].push_back(v);
  }
  std::vector<int> colors(n, -1);
  for (int v = 0; v < n; v++) {
    if (colors[v] < 0 && f(graph, colors, 0, v)) {
      std::cout << "NO" << std::endl;
      return 0;
    }
  }
  std::cout << "YES" << std::endl;
  return 0;
}
