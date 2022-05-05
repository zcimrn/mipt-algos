#include <iostream>
#include <vector>

std::vector<size_t> ReadPrefixFunction() {
  std::vector<size_t> prefix_function;
  for (size_t x; std::cin >> x;) {
    prefix_function.push_back(x);
  }
  return std::move(prefix_function);
}

std::string BuildStringFromPrefixFunction(const std::vector<size_t>& prefix_function) {
  std::string s = "a";
  for (size_t i = 1; i < prefix_function.size(); i++) {
    if (prefix_function[i] > 0) {
      s += s[prefix_function[i] - 1];
      continue;
    }
    std::vector<bool> alphabet(26);
    for (size_t j = prefix_function[i - 1]; j > 0; j = prefix_function[j - 1]) {
      alphabet[s[j] - 'a'] = true;
    }
    char c = 1;
    for (; c < alphabet.size() && alphabet[c]; c++) {
    }
    s += c + 'a';
  }
  return std::move(s);
}

int main() {
  auto prefix_function = ReadPrefixFunction();
  std::cout << BuildStringFromPrefixFunction(prefix_function) << std::endl;
  return 0;
}
