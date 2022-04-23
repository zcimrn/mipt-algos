// https://contest.yandex.com/contest/36361/run-report/67699707

#include <iostream>
#include <set>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<std::pair<size_t, long long>>> list_;

 public:
  Graph(size_t vertices_count) {
    list_.resize(vertices_count);
  }

  size_t GetVerticesCount() const {
    return list_.size();
  }

  void AddEdge(size_t v, size_t u, long long length) {
    list_[v].emplace_back(u, length);
  }

  std::vector<std::pair<size_t, long long>> GetEdges(size_t v) const {
    return std::move(list_[v]);
  }
};

Graph ReadGraph(size_t vertices_count, size_t edges_count) {
  Graph graph(vertices_count);
  for (size_t i = 0; i < edges_count; i++) {
    size_t v, u;
    long long length;
    std::cin >> v >> u >> length;
    if (v != u) {
      graph.AddEdge(v, u, length);
      graph.AddEdge(u, v, length);
    }
  }
  return std::move(graph);
}

long long GetMinWayLength(const Graph& graph, size_t begin, size_t end) {
  size_t vertices_count = graph.GetVerticesCount();
  std::set<std::pair<long long, size_t>> s;
  s.insert({0, begin});
  std::vector<bool> used(vertices_count);
  std::vector<long long> min_way_length(vertices_count, 1e18);
  min_way_length[begin] = 0;
  for (size_t v; s.size() > 0;) {
    v = s.begin()->second;
    s.erase(s.begin());
    used[v] = true;
    for (auto [u, length] : graph.GetEdges(v)) {
      if (!used[u] && min_way_length[v] + length < min_way_length[u]) {
        s.erase({min_way_length[u], u});
        s.insert({min_way_length[v] + length, u});
        min_way_length[u] = min_way_length[v] + length;
      }
    }
  }
  return min_way_length[end];
}

int main() {
  size_t vertices_count, edges_count;
  std::cin >> vertices_count >> edges_count;
  auto graph = ReadGraph(vertices_count, edges_count);
  size_t begin, end;
  std::cin >> begin >> end;
  std::cout << GetMinWayLength(graph, begin, end) << std::endl;
  return 0;
}
