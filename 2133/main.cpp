// https://contest.yandex.com/contest/35212/run-report/65263677

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> coords(n);
    for (auto& coord : coords) {
        std::cin >> coord;
    }
    std::sort(coords.begin(), coords.end());
    int last_disconnected = 2e9, last_connected = coords[1] - coords[0];
    for (int i = 2; i < n; i++) {
        std::swap(last_disconnected, last_connected);
        last_connected = std::min(last_disconnected, last_connected) + coords[i] - coords[i - 1];
    }
    std::cout << last_connected << std::endl;
    return 0;
}
