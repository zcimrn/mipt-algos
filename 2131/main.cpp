#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1, 2e9);
    a[1] = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] != 2e9) {
            if (i + 1 <= n && a[i] + 1 < a[i + 1]) {
                a[i + 1] = a[i] + 1;
            }
            if (i * 4 <= n && a[i] + 1 < a[i * 4]) {
                a[i * 4] = a[i] + 1;
            }
            if (i * 5 <= n && a[i] + 1 < a[i * 5]) {
                a[i * 5] = a[i] + 1;
            }
        }
    }
    std::cout << a[n] << std::endl;
}
