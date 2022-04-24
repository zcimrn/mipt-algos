// https://contest.yandex.com/contest/36361/run-report/67728344

#include <iostream>
#include <stack>
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
    if (v != u) {
      graph.AddEdge(--v, --u);
    }
  }
  return std::move(graph);
}

std::vector<size_t> TopSort(const Graph& graph) {
  size_t vertices_count = graph.GetVerticesCount();
  std::vector<bool> used(vertices_count);
  std::vector<size_t> order;
  for (size_t v = 0; v < vertices_count; v++) {
    if (!used[v]) {
      std::stack<std::pair<size_t, size_t>> stack;
      stack.emplace(v, 0);
      for (; stack.size() > 0;) {
        auto [v, i] = stack.top();
        used[v] = true;
        const auto& children = graph.GetChildren(v);
        for (; i < children.size() && used[children[i]]; i++) {
        }
        if (i < children.size()) {
          stack.top().second = i + 1;
          stack.emplace(children[i], 0);
        } else {
          stack.pop();
          order.push_back(v);
        }
      }
    }
  }
  return std::move(order);
}

std::vector<size_t> OrderedColor(const Graph& graph, const std::vector<size_t>& order) {
  static const size_t NULL_COLOR = 1e18;
  size_t vertices_count = graph.GetVerticesCount();
  std::vector<size_t> colors(vertices_count, NULL_COLOR);
  size_t color = 0;
  for (auto v : order) {
    if (colors[v] == NULL_COLOR) {
      std::stack<std::pair<size_t, size_t>> stack;
      stack.emplace(v, 0);
      for (; stack.size() > 0;) {
        auto [v, i] = stack.top();
        colors[v] = color;
        const auto& children = graph.GetChildren(v);
        for (; i < children.size() && colors[children[i]] != NULL_COLOR; i++) {
        }
        if (i < children.size()) {
          stack.top().second = i + 1;
          stack.emplace(children[i], 0);
        } else {
          stack.pop();
        }
      }
      color++;
    }
  }
  return std::move(colors);
}

std::pair<size_t, size_t> CountCondensedSourcesAndSinks(const Graph& graph, const std::vector<size_t>& colors) {
  size_t colors_count = 0;
  for (auto color : colors) {
    colors_count = std::max(colors_count, color);
  }
  colors_count++;
  if (colors_count == 1) {
    return {0, 0};
  }
  std::vector<bool> are_sources(colors_count, true), are_sinks(colors_count, true);
  size_t vertices_count = graph.GetVerticesCount(), sources_count = colors_count, sinks_count = colors_count;
  for (size_t v = 0; v < vertices_count; v++) {
    for (auto u : graph.GetChildren(v)) {
      if (colors[v] == colors[u]) {
        continue;
      }
      if (are_sources[u]) {
        are_sources[u] = false;
        sources_count--;
      }
      if (are_sinks[v]) {
        are_sinks[v] = false;
        sinks_count--;
      }
    }
  }
  return {sources_count, sinks_count};
}

int main() {
  size_t vertices_count, edges_count;
  std::cin >> vertices_count >> edges_count;
  auto graph = ReadGraph(vertices_count, edges_count);
  auto order = TopSort(graph);
  auto colors = OrderedColor(graph, order);
  auto [sources_count, sinks_count] = CountCondensedSourcesAndSinks(graph, colors);
  std::cout << std::max(sources_count, sinks_count) << std::endl;
  return 0;
}
