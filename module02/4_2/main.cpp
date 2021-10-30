// https://contest.yandex.com/contest/30914/run-report/55694438

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> get_sorted_part(std::vector<int>& a) {
    int n = a.size(), k = n / 2;
    std::stable_sort(a.begin(), a.end());
    std::vector<int> sorted_part(k);
    for (int i = 0; i < k; i++) {
        sorted_part[i] = a[i];
        a[i] = a[i + k];
        a[i + k] = 2e9;
    }
    return sorted_part;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(k * 2, 2e9);
    for (int i = 0; i < k && std::cin >> a[i]; i++);
    for (int i = k; i < n; i += k) {
        for (int j = 0; j < k && std::cin >> a[k + j]; j++);
        for (int x : get_sorted_part(a)) {
            std::cout << x << ' ';
        }
    }
    for (int i = 0, m = n - (n - 1) / k * k; i < m && std::cout << a[i] << ' '; i++);
    std::cout << std::endl;
    return 0;
}

