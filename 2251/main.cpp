// https://contest.yandex.com/contest/36361/run-report/67696491

#include <cmath>
#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<long double>> matrix_;
  constexpr static const long double null_edge_weight_ = -1e18;

 public:
  Graph(size_t vertices_count) {
    matrix_.resize(vertices_count, std::vector<long double>(vertices_count, null_edge_weight_));
    for (size_t i = 0; i < vertices_count; i++) {
      matrix_[i][i] = 0;
    }
  }

  size_t GetVerticesCount() const {
    return matrix_.size();
  }

  void AddEdge(size_t v, size_t u, long double weight) {
    matrix_[v][u] = weight;
  }

  long double GetEdgeWeight(size_t v, size_t u) const {
    return matrix_[v][u];
  }
};

Graph ReadGraph(size_t vertices_count) {
  Graph graph(vertices_count);
  for (size_t i = 0; i < vertices_count; i++) {
    for (size_t j = 0; j < vertices_count; j++) {
      if (i == j) {
        continue;
      }
      long double k;
      std::cin >> k;
      if (k != -1) {
        graph.AddEdge(i, j, log(k));
      }
    }
  }
  return std::move(graph);
}

bool HasNegativeCycle(const Graph& graph) {
  size_t vertices_count = graph.GetVerticesCount();
  auto matrix = std::vector<std::vector<long double>>(vertices_count, std::vector<long double>(vertices_count));
  for (size_t i = 0; i < vertices_count; i++) {
    for (size_t j = 0; j < vertices_count; j++) {
      matrix[i][j] = graph.GetEdgeWeight(i, j);
    }
  }
  for (size_t k = 0; k < vertices_count; k++) {
    for (size_t i = 0; i < vertices_count; i++) {
      for (size_t j = 0; j < vertices_count; j++) {
        if (matrix[i][j] < matrix[i][k] + matrix[k][j]) {
          if (i == j) {
            return true;
          }
          matrix[i][j] = matrix[i][k] + matrix[k][j];
        }
      }
    }
  }
  return false;
}

int main() {
  int vertices_count;
  std::cin >> vertices_count;
  auto graph = ReadGraph(vertices_count);
  std::cout << (HasNegativeCycle(graph) ? "YES" : "NO") << std::endl;
  return 0;
}
