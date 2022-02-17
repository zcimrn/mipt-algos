#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> x(n);
    for (auto& xi : x) {
        std::cin >> xi;
    }
    int s;
    std::cin >> s;
    std::vector<int> a(s + 1, 2e9);
    a[0] = 0;
    std::vector<int> p(s + 1, 2e9);
    for (int i = 0; i < s; i++) {
        if (a[i] != 2e9) {
            for (auto xi : x) {
                if (i + xi <= s && a[i] + 1 < a[i + xi]) {
                    a[i + xi] = a[i] + 1;
                    p[i + xi] = i;
                }
            }
        }
    }
    if (a[s] == 2e9) {
        std::cout << -1 << std::endl;
        return 0;
    }
    std::cout << a[s] << std::endl;
    for (int i = s; p[i] != 2e9; i = p[i]) {
        std::cout << i - p[i] << ' ';
    }
    std::cout << std::endl;
}
