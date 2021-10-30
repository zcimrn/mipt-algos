// https://contest.yandex.com/contest/30914/run-report/55704898

#include <iostream>
#include <vector>
#include <algorithm>

void merge(std::vector<int>& a) {
    int n = a.size(), k = n / 2;
    std::vector<int> t(n);
    int l = 0, r = k, i = 0;
    for (; l < k && r < n;) {
        if (a[l] < a[r]) {
            t[i++] = a[l++];
        }
        else {
            t[i++] = a[r++];
        }
    }
    for (; l < k;) {
        t[i++] = a[l++];
    }
    for (; r < n;) {
        t[i++] = a[r++];
    }
    for (i = 0; i < n; i++) {
        a[i] = t[i];
    }
}

std::vector<int> get_sorted_part(std::vector<int>& a) {
    int n = a.size(), k = n / 2;
    std::stable_sort(a.begin() + k, a.end());
    merge(a);
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
    std::stable_sort(a.begin(), a.end());
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

