// https://contest.yandex.com/contest/37787/run-report/68155698

#include <cmath>
#include <iostream>
#include <vector>

std::vector<size_t> CountOrder(const std::string& s) {
  std::vector<size_t> temp(256);
  for (uint8_t c : s) {
    temp[c]++;
  }
  for (size_t i = 1; i < temp.size(); i++) {
    temp[i] += temp[i - 1];
  }
  size_t size = s.size();
  std::vector<size_t> order(size);
  for (size_t i = 0; i < size; i++) {
    order[--temp[static_cast<uint8_t>(s[i])]] = i;
  }
  return std::move(order);
}

size_t InitClasses(std::vector<std::vector<size_t>>& classes, const std::vector<size_t>& order, const std::string& s) {
  size_t size = order.size(), last_class = 0;
  classes.push_back(std::vector<size_t>(size));
  classes[0][order[0]] = last_class;
  for (size_t i = 1; i < size; i++) {
    if (s[order[i]] != s[order[i - 1]]) {
      last_class++;
    }
    classes[0][order[i]] = last_class;
  }
  return ++last_class;
}

void UpdateOrder(std::vector<size_t>& order, const std::vector<size_t>& classes, const size_t classes_count, const size_t offset) {
  size_t size = order.size();
  std::vector<size_t> new_order(size);
  for (size_t i = 0; i < size; i++) {
    new_order[i] = (order[i] + size - offset) % size;
  }
  std::vector<size_t> temp(classes_count);
  for (size_t i = 0; i < size; i++) {
    temp[classes[new_order[i]]]++;
  }
  for (size_t i = 1; i < classes_count; i++) {
    temp[i] += temp[i - 1];
  }
  for (int64_t i = size - 1; i >= 0; i--) {
    order[--temp[classes[new_order[i]]]] = new_order[i];
  }
}

size_t UpdateClasses(std::vector<std::vector<size_t>>& classes, const std::vector<size_t>& order, const size_t k) {
  size_t size = order.size(), last_class = 0;
  classes.push_back(std::vector<size_t>(size));
  classes[k + 1][order[0]] = last_class;
  for (size_t offset = (1ull << k), i = 1; i < size; i++) {
    if (classes[k][order[i]] != classes[k][order[i - 1]] ||
        classes[k][(order[i] + offset) % size] != classes[k][(order[i - 1] + offset) % size]) {
      last_class++;
    }
    classes[k + 1][order[i]] = last_class;
  }
  return ++last_class;
}

std::pair<std::vector<size_t>, std::vector<std::vector<size_t>>> CountOrderAndClasses(const std::string& s) {
  auto order = CountOrder(s);
  std::vector<std::vector<size_t>> classes;
  size_t classes_count = InitClasses(classes, order, s);
  for (size_t k = 0, offset = (1ull << k), size = order.size(); offset < size; k++, offset *= 2) {
    UpdateOrder(order, classes[k], classes_count, offset);
    classes_count = UpdateClasses(classes, order, k);
  }
  return {std::move(order), std::move(classes)};
}

size_t CountDiffSubstrings(const std::vector<size_t>& order, const std::vector<std::vector<size_t>>& classes) {
  size_t diff_substrings_count = 0;
  for (size_t i = 1, size = order.size(); i < size; i++) {
    size_t lcp = 0;
    for (int64_t l = order[i - 1], r = order[i], k = log(size), offset = (1ull << k); k >= 0; k--, offset /= 2) {
      if (classes[k][l] == classes[k][r]) {
        lcp += offset;
        l += offset;
        r += offset;
      }
    }
    diff_substrings_count += size - 1 - order[i] - lcp;
  }
  return diff_substrings_count;
}

int main() {
  std::string s;
  std::cin >> s;
  s += '\0';
  auto [order, classes] = CountOrderAndClasses(s);
  std::cout << CountDiffSubstrings(order, classes) << std::endl;
  return 0;
}
