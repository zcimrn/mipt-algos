// https://contest.yandex.com/contest/36361/run-report/67691031

#include <cmath>
#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<long double>> matrix_;
  long double null_edge_ = -1e18;

 public:
  Graph(size_t vertices_count) {
    matrix_.resize(vertices_count, std::vector<long double>(vertices_count, null_edge_));
    for (size_t i = 0; i < vertices_count; i++) {
      matrix_[i][i] = 0;
    }
  }

  void AddEdge(size_t v, size_t u, long double l) {
    matrix_[v][u] = l;
  }

  bool HasNegativeCycle() const {
    auto matrix = matrix_;
    size_t vertices_count = matrix.size();
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
};

Graph ReadGraph(size_t vertices_count) {
  Graph graph(vertices_count);
  for (size_t i = 0; i < vertices_count; i++) {
    for (size_t j = 0; j < vertices_count; j++) {
      if (i == j) {
        continue;
      }
      long double length;
      std::cin >> length;
      if (length != -1) {
        graph.AddEdge(i, j, log(length));
      }
    }
  }
  return std::move(graph);
}

int main() {
  int vertices_count;
  std::cin >> vertices_count;
  auto graph = ReadGraph(vertices_count);
  std::cout << (graph.HasNegativeCycle() ? "YES" : "NO") << std::endl;
  return 0;
}
