#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent, rank;
  int size = 0;

  int find_set_rec(int x) {
    if (parent[x] == x) {
      return x;
    }
    return parent[x] = find_set_rec(parent[x]);
  }

 public:
  DSU(int size_) {
    size = size_;
    parent.resize(size, -1);
    rank.resize(size);
  }

  void make_set(int x) {
    assert(x >= 0 && x < size);
    parent[x] = x;
    rank[x] = 0;
  }

  int find_set(int x) {
    assert(x >= 0 && x < size);
    if (parent[x] == -1) {
      make_set(x);
    }
    return find_set_rec(x);
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) {
      return;
    }
    if (rank[a] < rank[b]) {
      std::swap(a, b);
    }
    parent[b] = a;
    if (rank[a] == rank[b]) {
      rank[a]++;
    }
  }
};

struct Edge {
  int a, b, l;

  Edge(int a = -1, int b = -1, int l = 0) : a{a}, b{b}, l{l} {}
};

std::vector<Edge> read_edges(int edge_count) {
  std::vector<Edge> edges;
  for (int i = 0, a, b, l; i < edge_count; i++) {
    std::cin >> a >> b >> l;
    edges.push_back({--a, --b, l});
  }
  return std::move(edges);
}

bool edges_cmp(const Edge& e1, const Edge& e2) {
  return e1.l < e2.l || e1.l == e2.l && e1.a < e2.a || e1.l == e2.l && e1.a == e2.a && e1.b < e2.b;
}

int get_mst_length(int node_count, std::vector<Edge>& edges) {
  std::sort(edges.begin(), edges.end(), edges_cmp);
  std::vector<Edge> mst_edges;
  DSU dsu(node_count);
  int answer = 0;
  for (const auto& edge : edges) {
    int a = dsu.find_set(edge.a), b = dsu.find_set(edge.b);
    if (a != b) {
      mst_edges.push_back(edge);
      dsu.union_sets(a, b);
      answer += edge.l;
    }
  }
  return answer;
}

int main() {
  int node_count, edge_count;
  std::cin >> node_count >> edge_count;
  auto edges = read_edges(edge_count);
  int answer = get_mst_length(node_count, edges);
  std::cout << answer << std::endl;
  return 0;
}
