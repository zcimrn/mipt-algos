// https://contest.yandex.com/contest/37787/run-report/68585803

#include <algorithm>
#include <iostream>
#include <vector>

class SuffTree {
 private:
  struct Node {
    int Start{0}, Count{0}, Parent{-1}, SuffLink{-1};
    bool IsLeaf{false}, IsCommon{false}, HasFirst{false}, HasSecond{false};
    std::vector<int> Children = std::vector<int>(28, -1);

    Node() = default;

    Node(int start, int count, int parent, bool is_leaf = false)
        : Start{start}, Count{count}, Parent{parent}, IsLeaf{is_leaf} {}
  };

  std::string text;
  std::vector<Node> nodes{1};

  bool HasLetter(const int v, const int count, const uint8_t letter) const {
    if (count < nodes[v].Count) {
      return text[nodes[v].Start + count] == letter;
    }
    return nodes[v].Children[letter] != -1;
  }

  std::pair<int, int> Go(const int v, const int count, const uint8_t letter) const {
    if (count < nodes[v].Count) {
      return {v, count + 1};
    }
    return {nodes[v].Children[letter], 1};
  }

  void AddLeaf(const int v, const int count, const int i) {
    nodes.emplace_back(i, text.size() - i, v, true);
    nodes[v].Children[static_cast<uint8_t>(text[i])] = nodes.size() - 1;
  }

  int AddNode(const int v, const int count) {
    Node node(nodes[v].Start, count, nodes[v].Parent);
    node.Children[static_cast<uint8_t>(text[node.Start + count])] = v;
    nodes[v].Parent = nodes.size();
    nodes[v].Start += count;
    nodes[v].Count -= count;
    nodes[node.Parent].Children[static_cast<uint8_t>(text[node.Start])] = nodes.size();
    nodes.push_back(std::move(node));
    return nodes.size() - 1;
  }

  std::pair<int, int> AddLetter(int v, int count, const int i) {
    const uint8_t letter = text[i];
    int p = -1;
    for (; !HasLetter(v, count, letter);) {
      if (count < nodes[v].Count) {
        v = AddNode(v, count);
      }
      AddLeaf(v, count, i);
      if (p != -1) {
        nodes[p].SuffLink = v;
      }
      p = v;
      if (nodes[v].SuffLink != -1) {
        v = nodes[v].SuffLink;
        continue;
      }
      v = nodes[nodes[nodes[v].Parent].SuffLink].Children[static_cast<uint8_t>(text[nodes[v].Start])];
      for (; nodes[v].Count < count;) {
        count -= nodes[v].Count;
        v = nodes[v].Children[static_cast<uint8_t>(text[nodes[p].Start + nodes[p].Count - count])];
      }
    }
    if (p != -1) {
      nodes[p].SuffLink = v;
    }
    return std::move(Go(v, count, letter));
  }

  void MarkCommonNodes(const int v, const int sep_pos) {
    if (nodes[v].IsLeaf) {
      nodes[v].HasFirst |= nodes[v].Start <= sep_pos;
      nodes[v].HasSecond |= nodes[v].Start > sep_pos;
      return;
    }
    for (int u : nodes[v].Children) {
      if (u != -1) {
        MarkCommonNodes(u, sep_pos);
        nodes[v].HasFirst |= nodes[u].HasFirst;
        nodes[v].HasSecond |= nodes[u].HasSecond;
        nodes[v].IsCommon |= nodes[u].IsCommon;
      }
    }
    nodes[v].IsCommon |= nodes[v].HasFirst && nodes[v].HasSecond;
  }

  std::pair<int, int> GetKthCommonState(int v, long long& k) const {
    if (nodes[v].IsCommon) {
      k -= nodes[v].Count;
    }
    if (k < 0) {
      return {v, nodes[v].Count + k + 1};
    }
    for (auto u : nodes[v].Children) {
      if (u != -1 && !nodes[u].IsLeaf) {
        const auto state = GetKthCommonState(u, k);
        if (state.first > 0) {
          return state;
        }
      }
    }
    return {0, 0};
  }

 public:
  explicit SuffTree(const std::string& text) : text{text} {
    nodes[0].Children.assign(256, 1);
    nodes.emplace_back(-1, 1, 0);
    nodes[1].SuffLink = 0;
    for (int v = 1, count = 1, i = 0; i < text.size(); i++) {
      const auto state = AddLetter(v, count, i);
      v = state.first;
      count = state.second;
    }
  }

  std::string SolveTask(const int sep_pos, long long k) {
    MarkCommonNodes(1, sep_pos);
    auto [v, count] = GetKthCommonState(1, k);
    std::string answer;
    for (; v > 1;) {
      for (int i = count - 1; i >= 0; i--) {
        answer += text[nodes[v].Start + i];
      }
      v = nodes[v].Parent;
      count = nodes[v].Count;
    }
    std::reverse(answer.begin(), answer.end());
    return std::move(answer);
  }
};

std::string encode(const std::string& a, const std::string& b) {
  std::string text = a + '\x5f' + b + '\x60';
  for (int i = 0; i < text.size(); i++) {
    text[i] -= '\x5f';
  }
  return std::move(text);
}

std::string decode(const std::string& text) {
  std::string answer = text;
  for (int i = 0; i < answer.size(); i++) {
    answer[i] += '\x5f';
  }
  return std::move(answer);
}

int main() {
  std::string a, b;
  std::cin >> a >> b;
  SuffTree suff_tree(encode(a, b));
  long long k;
  std::cin >> k;
  auto answer = decode(suff_tree.SolveTask(a.size(), k));
  std::cout << (answer.size() ? answer : "-1") << std::endl;
  return 0;
}
