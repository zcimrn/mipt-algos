// https://contest.yandex.com/contest/36361/run-report/67710886

#include <iostream>
#include <set>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<std::pair<size_t, int>>> list_;

 public:
  Graph(size_t vertices_count) {
    list_.resize(vertices_count);
  }

  size_t GetVerticesCount() const {
    return list_.size();
  }

  void AddEdge(size_t v, size_t u, int weight) {
    list_[v].emplace_back(u, weight);
  }

  std::vector<std::pair<size_t, int>> GetEdges(size_t v) const {
    return std::move(list_[v]);
  }
};

Graph ReadGraph(size_t vertices_count, size_t edges_count) {
  Graph graph(vertices_count);
  for (size_t i = 0; i < edges_count; i++) {
    size_t v, u;
    int weight;
    std::cin >> v >> u >> weight;
    v--;
    u--;
    graph.AddEdge(v, u, weight);
    graph.AddEdge(u, v, weight);
  }
  return std::move(graph);
}

int CountMSTLength(const Graph& graph) {
  size_t vertices_count = graph.GetVerticesCount();
  std::vector<bool> used(vertices_count);
  std::vector<int> d(vertices_count, 1e9);
  d[0] = 0;
  std::set<std::pair<int, size_t>> s;
  s.insert({0, 0});
  int mst_length = 0;
  for (; s.size() > 0;) {
    auto [weight, v] = *s.begin();
    s.erase(s.begin());
    used[v] = true;
    mst_length += weight;
    for (auto [u, weight] : graph.GetEdges(v)) {
      if (!used[u] && d[u] > weight) {
        s.erase({d[u], u});
        d[u] = weight;
        s.insert({d[u], u});
      }
    }
  }
  return mst_length;
}

int main() {
  size_t vertices_count, edges_count;
  std::cin >> vertices_count >> edges_count;
  auto graph = ReadGraph(vertices_count, edges_count);
  std::cout << CountMSTLength(graph) << std::endl;
  return 0;
}
