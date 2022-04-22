#include "list_graph.h"
#include <vector>

ListGraph::ListGraph(std::size_t vertices_count) {
  children_.resize(vertices_count);
  parents_.resize(vertices_count);
}

ListGraph::ListGraph(const IGraph* i_graph_ptr) {
  auto vertices_count = i_graph_ptr->VerticesCount();
  children_.resize(vertices_count);
  parents_.resize(vertices_count);
  for (std::size_t v = 0; v < vertices_count; v++) {
    for (auto u : i_graph_ptr->FindAllAdjacentOut(v)) {
      children_[v].push_back(u);
      parents_[u].push_back(v);
    }
  }
}

void ListGraph::AddEdge(std::size_t v, std::size_t u) {
  children_[v].push_back(u);
  parents_[u].push_back(v);
}

std::size_t ListGraph::VerticesCount() const {
  return children_.size();
}

std::vector<std::size_t> ListGraph::FindAllAdjacentIn(std::size_t v) const {
  return std::move(parents_[v]);
}

std::vector<std::size_t> ListGraph::FindAllAdjacentOut(std::size_t v) const {
  return std::move(children_[v]);
}
