// https://contest.yandex.com/contest/37787/run-report/68373854

#include <iostream>
#include <vector>

class Trie {
 private:
  class Node {
   public:
    std::vector<int> Children = std::vector<int>(26, -1), Meta;
    int Value = 0, Parent = -1, SuffLink = -1, TerminalLink = -1;
    bool IsTerminal = false;

    Node() = default;

    Node(int value, int parent) : Value(value), Parent(parent) {}
  };

  std::vector<Node> nodes = std::vector<Node>(1);

 public:
  int AddPattern(const std::string& pattern) {
    int v = 0;
    for (uint8_t value : pattern) {
      if (nodes[v].Children[value] == -1) {
        nodes[v].Children[value] = nodes.size();
        nodes.emplace_back(value, v);
      }
      v = nodes[v].Children[value];
    }
    nodes[v].IsTerminal = true;
    return v;
  }

  void AddPattern(const std::string& pattern, const int position) {
    int v = AddPattern(pattern);
    nodes[v].Meta.push_back(position);
  }

  int AddPatterns(const std::string& pattern) {
    std::string sub_pattern;
    int sub_pattern_number = 0;
    for (int i = 0; i < pattern.size(); i++) {
      if (pattern[i] != '?') {
        sub_pattern += pattern[i] - 'a';
      } else if (sub_pattern.size()) {
        AddPattern(sub_pattern, i - 1);
        sub_pattern_number++;
        sub_pattern.clear();
      }
    }
    if (sub_pattern.size()) {
      AddPattern(sub_pattern, pattern.size() - 1);
      sub_pattern_number++;
    }
    return sub_pattern_number;
  }

  int GetSuffLink(const int v) {
    if (nodes[v].SuffLink != -1) {
      return nodes[v].SuffLink;
    }
    if (v == 0 || nodes[v].Parent == 0) {
      return nodes[v].SuffLink = 0;
    }
    return nodes[v].SuffLink = GetLink(GetSuffLink(nodes[v].Parent), nodes[v].Value);
  }

  int GetLink(const int v, const int value) {
    if (nodes[v].Children[value] != -1) {
      return nodes[v].Children[value];
    }
    if (v == 0) {
      return nodes[v].Children[value] = 0;
    }
    return nodes[v].Children[value] = GetLink(GetSuffLink(v), value);
  }

  int GetTerminalLink(const int v) {
    if (nodes[v].TerminalLink != -1) {
      return nodes[v].TerminalLink;
    }
    int u = GetSuffLink(v);
    if (nodes[u].IsTerminal || u == 0) {
      return nodes[v].TerminalLink = u;
    }
    return nodes[v].TerminalLink = GetTerminalLink(u);
  }

  bool IsTerminal(const int v) const {
    return nodes[v].IsTerminal;
  }

  std::vector<int> GetMeta(const int v) {
    return nodes[v].Meta;
  }
};

std::vector<int> Search(const std::string& pattern, const std::string& text) {
  Trie trie;
  int pattern_number = trie.AddPatterns(pattern);
  std::vector<int> found_pattern_numbers(text.size());
  int v = 0;
  for (int i = 0; i < text.size(); i++) {
    v = trie.GetLink(v, text[i] - 'a');
    for (int u = v; u != 0; u = trie.GetTerminalLink(u)) {
      for (int position : trie.GetMeta(u)) {
        if (i - position >= 0) {
          found_pattern_numbers[i - position]++;
        }
      }
    }
  }
  std::vector<int> result;
  for (int i = 0, end = text.size() - pattern.size(); i <= end; i++) {
    if (found_pattern_numbers[i] == pattern_number) {
      result.push_back(i);
    }
  }
  return std::move(result);
}

int main() {
  std::string pattern, text;
  std::cin >> pattern >> text;
  for (auto position : Search(pattern, text)) {
    std::cout << position << ' ';
  }
  std::cout << std::endl;
  return 0;
}
