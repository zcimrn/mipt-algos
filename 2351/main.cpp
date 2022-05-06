// https://contest.yandex.com/contest/37787/run-report/68152479

#include <cmath>
#include <iostream>
#include <vector>

size_t CountDiffSubstrings(std::string s) {
  s += '\0';
  size_t n = s.size();
  std::vector<size_t> temp(256);
  for (uint8_t c : s) {
    temp[c]++;
  }
  for (size_t i = 1; i < temp.size(); i++) {
    temp[i] += temp[i - 1];
  }
  std::vector<size_t> order(n);
  for (size_t i = 0; i < n; i++) {
    order[--temp[static_cast<uint8_t>(s[i])]] = i;
  }
  std::vector<std::vector<size_t>> classes(1, std::vector<size_t>(n));
  classes[0][order[0]] = 0;
  size_t classes_count = 1;
  for (size_t i = 1; i < n; i++) {
    if (s[order[i]] != s[order[i - 1]]) {
      classes_count++;
    }
    classes[0][order[i]] = classes_count - 1;
  }
  for (size_t k = 0; (1ull << k) < n; k++) {
    std::vector<size_t> new_order(n);
    for (size_t i = 0; i < n; i++) {
      new_order[i] = (order[i] + n - (1ull << k)) % n;
    }
    std::vector<size_t> temp(classes_count);
    for (size_t i = 0; i < n; i++) {
      temp[classes[k][new_order[i]]]++;
    }
    for (size_t i = 1; i < classes_count; i++) {
      temp[i] += temp[i - 1];
    }
    for (int64_t i = n - 1; i >= 0; i--) {
      order[--temp[classes[k][new_order[i]]]] = new_order[i];
    }
    classes.push_back(std::vector<size_t>(n));
    classes[k + 1][order[0]] = 0;
    classes_count = 1;
    for (size_t i = 1; i < n; i++) {
      if (classes[k][order[i]] != classes[k][order[i - 1]] ||
          classes[k][(order[i] + (1ull << k)) % n] != classes[k][(order[i - 1] + (1ull << k)) % n]) {
        classes_count++;
      }
      classes[k + 1][order[i]] = classes_count - 1;
    }
  }
  size_t diff_substrings_count = 0;
  for (size_t i = 1; i < n; i++) {
    size_t lcp = 0;
    for (int64_t l = order[i - 1], r = order[i], k = log(n); k >= 0; k--) {
      if (classes[k][l] == classes[k][r]) {
        lcp += (1ull << k);
        l += (1ull << k);
        r += (1ull << k);
      }
    }
    diff_substrings_count += n - 1 - order[i] - lcp;
  }
  return diff_substrings_count;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << CountDiffSubstrings(s) << std::endl;
  return 0;
}
