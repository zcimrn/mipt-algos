#include "i_graph.h"
#include "set_graph.h"

SetGraph::SetGraph(std::size_t vertices_count) {
  children_.resize(vertices_count);
  parents_.resize(vertices_count);
}

SetGraph::SetGraph(const IGraph* i_graph_ptr) {
  auto vertices_count = i_graph_ptr->VerticesCount();
  children_.resize(vertices_count);
  parents_.resize(vertices_count);
  for (std::size_t v = 0; v < vertices_count; v++) {
    for (auto u : i_graph_ptr->FindAllAdjacentOut(v)) {
      children_[v].insert(u);
      parents_[u].insert(v);
    }
  }
}

void SetGraph::AddEdge(std::size_t v, std::size_t u) {
  children_[v].insert(u);
  parents_[u].insert(v);
}

std::size_t SetGraph::VerticesCount() const {
  return children_.size();
}

std::vector<std::size_t> SetGraph::FindAllAdjacentIn(std::size_t v) const {
  return std::move(std::vector<std::size_t>(parents_[v].begin(), parents_[v].end()));
}

std::vector<std::size_t> SetGraph::FindAllAdjacentOut(std::size_t v) const {
  return std::move(std::vector<std::size_t>(children_[v].begin(), children_[v].end()));
}
