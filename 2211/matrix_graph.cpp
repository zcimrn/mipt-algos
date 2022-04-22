#include "i_graph.h"
#include "matrix_graph.h"
#include <vector>

MatrixGraph::MatrixGraph(std::size_t vertices_count) {
  matrix_ = std::vector<std::vector<bool>>(vertices_count, std::vector<bool>(vertices_count));
}

MatrixGraph::MatrixGraph(const IGraph* i_graph_ptr) {
  auto vertices_count = i_graph_ptr->VerticesCount();
  matrix_ = std::vector<std::vector<bool>>(vertices_count, std::vector<bool>(vertices_count));
  for (std::size_t v = 0; v < vertices_count; v++) {
    for (auto u : i_graph_ptr->FindAllAdjacentOut(v)) {
      matrix_[v][u] = true;
    }
  }
}

void MatrixGraph::AddEdge(std::size_t v, std::size_t u) {
  matrix_[v][u] = true;
}

std::size_t MatrixGraph::VerticesCount() const {
  return matrix_.size();
}

std::vector<std::size_t> MatrixGraph::FindAllAdjacentIn(std::size_t v) const {
  std::vector<std::size_t> vertices;
  for (std::size_t u = 0; u < matrix_.size(); u++) {
    if (matrix_[u][v]) {
      vertices.push_back(u);
    }
  }
  return std::move(vertices);
}

std::vector<std::size_t> MatrixGraph::FindAllAdjacentOut(std::size_t v) const {
  std::vector<std::size_t> vertices;
  for (std::size_t u = 0; u < matrix_.size(); u++) {
    if (matrix_[v][u]) {
      vertices.push_back(u);
    }
  }
  return std::move(vertices);
}
