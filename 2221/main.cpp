#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int v, u, i = 0; i < m; i++) {
    std::cin >> v >> u;
    graph[v].push_back(u);
    graph[u].push_back(v);
  }
  int ans = 2e9;
  for (int i = 0; i < n; i++) {
    std::vector<int> len(n, -1);
    len[i] = 0;
    std::queue<int> q;
    q.push(i);
    std::vector<int> p(n, -1);
    for (bool found = false; q.size() > 0 && !found;) {
      int v = q.front();
      q.pop();
      for (int u : graph[v]) {
        if (p[v] == u) {
          continue;
        }
        if (len[u] < 0) {
          len[u] = len[v] + 1;
          q.push(u);
          p[u] = v;
        } else {
          ans = std::min(ans, len[v] + len[u] + 1);
          found = true;
          break;
        }
      }
    }
  }
  std::cout << (ans < 2e9 ? ans : -1) << std::endl;
  return 0;
}
