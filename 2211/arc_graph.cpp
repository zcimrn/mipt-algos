#include "arc_graph.h"
#include <vector>

ArcGraph::ArcGraph(std::size_t vertices_count) {
  vertices_count_ = vertices_count;
}

ArcGraph::ArcGraph(const IGraph* i_graph_ptr) {
  vertices_count_ = i_graph_ptr->VerticesCount();
  for (std::size_t v = 0; v < vertices_count_; v++) {
    for (auto u : i_graph_ptr->FindAllAdjacentOut(v)) {
      edges_.emplace_back(v, u);
    }
  }
}

void ArcGraph::AddEdge(std::size_t v, std::size_t u) {
  edges_.emplace_back(v, u);
}

std::size_t ArcGraph::VerticesCount() const {
  return vertices_count_;
}

std::vector<std::size_t> ArcGraph::FindAllAdjacentIn(std::size_t v) const {
  std::vector<std::size_t> vertices;
  for (auto [u, i] : edges_) {
    if (i == v) {
      vertices.push_back(u);
    }
  }
  return std::move(vertices);
}

std::vector<std::size_t> ArcGraph::FindAllAdjacentOut(std::size_t v) const {
  std::vector<std::size_t> vertices;
  for (auto [i, u] : edges_) {
    if (i == v) {
      vertices.push_back(u);
    }
  }
  return std::move(vertices);
}
