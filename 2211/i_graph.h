#ifndef I_GRAPH_H_
#define I_GRAPH_H_

#include <vector>

class IGraph {
 public:
  virtual ~IGraph() {}

  virtual void AddEdge(std::size_t v, std::size_t u) = 0;

  virtual std::size_t VerticesCount() const = 0;

  virtual std::vector<std::size_t> FindAllAdjacentIn(std::size_t v) const = 0;
  virtual std::vector<std::size_t> FindAllAdjacentOut(std::size_t v) const = 0;
};

#endif
