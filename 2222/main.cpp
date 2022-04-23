// https://contest.yandex.com/contest/36361/run-report/67709026

#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<size_t>> list_;

 public:
  Graph(size_t vertices_count) {
    list_.resize(vertices_count);
  }

  size_t GetVerticesCount() const {
    return list_.size();
  }

  void AddEdge(size_t v, size_t u) {
    list_[v].push_back(u);
  }

  std::vector<size_t> GetChildren(size_t v) const {
    return std::move(list_[v]);
  }
};

Graph ReadGraph(size_t vertices_count, size_t edges_count) {
  Graph graph(vertices_count);
  for (size_t i = 0; i < edges_count; i++) {
    size_t v, u;
    std::cin >> v >> u;
    graph.AddEdge(v, u);
    graph.AddEdge(u, v);
  }
  return std::move(graph);
}

int CountDiffWays(const Graph& graph, size_t begin, size_t end) {
  size_t vertices_count = graph.GetVerticesCount();
  std::vector<int> depth(vertices_count, -1);
  depth[begin] = 0;
  std::vector<int> diff_ways_count(vertices_count);
  diff_ways_count[begin] = 1;
  std::queue<size_t> q;
  q.push(begin);
  for (int v; q.size() > 0;) {
    v = q.front();
    q.pop();
    for (int u : graph.GetChildren(v)) {
      if (depth[u] < 0) {
        q.push(u);
        depth[u] = depth[v] + 1;
      }
      if (depth[u] > depth[v]) {
        diff_ways_count[u] += diff_ways_count[v];
      }
    }
  }
  return diff_ways_count[end];
}

int main() {
  size_t vertices_count, edges_count;
  std::cin >> vertices_count >> edges_count;
  auto graph = ReadGraph(vertices_count, edges_count);
  size_t begin, end;
  std::cin >> begin >> end;
  std::cout << CountDiffWays(graph, begin, end) << std::endl;
  return 0;
}
