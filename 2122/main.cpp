#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> a;
    for (int begin, end; std::cin >> begin >> end; a.push_back({end, begin}));
    std::sort(a.begin(), a.end());
    int last = -2e9, count = 0;
    for (auto [end, begin] : a) {
        if (begin >= last) {
            count++;
            last = end;
        }
    }
    std::cout << count << std::endl;
}
