#ifndef LIST_GRAPH_H_
#define LIST_GRAPH_H_

#include "i_graph.h"
#include <vector>

class ListGraph : public IGraph {
 private:
  std::vector<std::vector<std::size_t>> children_;
  std::vector<std::vector<std::size_t>> parents_;

 public:
  explicit ListGraph(std::size_t vertices_count);

  explicit ListGraph(const IGraph* i_graph_ptr);

  void AddEdge(std::size_t v, std::size_t u) override;

  std::size_t VerticesCount() const override;

  std::vector<std::size_t> FindAllAdjacentIn(std::size_t v) const override;
  std::vector<std::size_t> FindAllAdjacentOut(std::size_t v) const override;
};

#endif
