#include <iostream>
#include <vector>

std::vector<size_t> CountPrefixFunction(const std::string& s) {
  std::vector<size_t> prefix_function(s.size());
  for (size_t i = 1; i < prefix_function.size(); i++) {
    size_t j = prefix_function[i - 1];
    for (; j > 0 && s[i] != s[j];) {
      j = prefix_function[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    prefix_function[i] = j;
  }
  return std::move(prefix_function);
}

std::vector<size_t> FindPattern(const std::string& text, const std::string& pattern) {
  std::string s = pattern + '@' + text;
  auto prefix_function = CountPrefixFunction(s);
  std::vector<size_t> answer;
  for (size_t i = pattern.size() + 1; i < prefix_function.size(); i++) {
    if (prefix_function[i] == pattern.size()) {
      answer.push_back(i - prefix_function[i] - pattern.size());
    }
  }
  return std::move(answer);
}

int main() {
  std::string pattern, text;
  std::cin >> pattern >> text;
  for (auto answer : FindPattern(text, pattern)) {
    std::cout << answer << ' ';
  }
  std::cout << std::endl;
  return 0;
}
