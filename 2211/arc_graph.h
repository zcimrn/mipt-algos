#ifndef ARC_GRAPH_H_
#define ARC_GRAPH_H_

#include "i_graph.h"
#include <vector>

class ArcGraph : public IGraph {
 private:
   std::size_t vertices_count_ = 0;
   std::vector<std::pair<std::size_t, std::size_t>> edges_;

 public:
  explicit ArcGraph(std::size_t vertices_count);

  explicit ArcGraph(const IGraph* i_graph_ptr);

  void AddEdge(std::size_t v, std::size_t u) override;

  std::size_t VerticesCount() const override;

  std::vector<std::size_t> FindAllAdjacentIn(std::size_t v) const override;
  std::vector<std::size_t> FindAllAdjacentOut(std::size_t v) const override;
};

#endif
