#ifndef SET_GRAPH_H_
#define SET_GRAPH_H_

#include "i_graph.h"
#include <unordered_set>
#include <vector>

class SetGraph : public IGraph {
 private:
  std::vector<std::unordered_set<std::size_t>> children_;
  std::vector<std::unordered_set<std::size_t>> parents_;

 public:
  explicit SetGraph(std::size_t vertices_count);

  explicit SetGraph(const IGraph* i_graph_ptr);

  void AddEdge(std::size_t v, std::size_t u) override;

  std::size_t VerticesCount() const override;

  std::vector<std::size_t> FindAllAdjacentIn(std::size_t v) const override;
  std::vector<std::size_t> FindAllAdjacentOut(std::size_t v) const override;
};

#endif
