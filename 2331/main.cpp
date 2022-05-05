// https://contest.yandex.com/contest/37787/run-report/68128562

#include <iostream>
#include <vector>

size_t CountPalindromes(const std::string& s, bool with_odd_size = true) {
  size_t n = s.size(), palindrome_count = 0;
  std::vector<size_t> palindrome_counts(n);
  for (size_t l = 0, r = 0, k, i = 1 - with_odd_size; i < n; i++) {
    k = 0;
    if (i < r) {
      k = std::min(r - i, palindrome_counts[l + r - i]);
    }
    for (; i - k > 0 && i + k + with_odd_size < n && s[i - k - 1] == s[i + k + with_odd_size]; k++) {
    }
    if (r < i + k) {
      l = i - k;
      r = i + k;
    }
    palindrome_counts[i] = k;
    palindrome_count += k;
  }
  return palindrome_count;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << CountPalindromes(s, true) + CountPalindromes(s, false) << std::endl;
  return 0;
}
