// https://contest.yandex.com/contest/37787/run-report/68069644

#include <iostream>
#include <vector>

std::vector<size_t> CountZFunction(const std::string& s) {
  std::vector<size_t> z_function(s.size());
  long long left = 0, right = 0;
  for (long long i = 1; i < z_function.size(); i++) {
    z_function[i] = std::max(0ll, std::min(right - i, static_cast<long long>(z_function[i - left])));
    for (; i + z_function[i] < z_function.size() && s[z_function[i]] == s[i + z_function[i]];) {
      z_function[i]++;
    }
    if (right < i + z_function[i]) {
      left = i;
      right = i + z_function[i];
    }
  }
  return std::move(z_function);
}

std::vector<size_t> FindPattern(const std::string& text, const std::string& pattern) {
  std::string s = pattern + '@' + text;
  auto z_function = CountZFunction(s);
  std::vector<size_t> answer;
  for (size_t i = pattern.size() + 1; i < z_function.size(); i++) {
    if (z_function[i] == pattern.size()) {
      answer.push_back(i - pattern.size() - 1);
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
