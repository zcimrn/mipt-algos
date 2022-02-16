// https://contest.yandex.com/contest/29755/run-report/55220563

#include <iostream>
#include <vector>

float solve(std::vector<std::pair<int, int>>& a) {
    for (int i = 1; i < a.size(); i++) {
        a[i].first -= a[0].first;
        a[i].second -= a[0].second;
    }
    int ans = 0;
    for (int i = 1; i < a.size() - 1; i++) {
        ans += a[i].first * a[i + 1].second - a[i].second * a[i + 1].first;
    }
    return static_cast<float>(ans) / -2;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].first >> a[i].second;
    }
    std::cout << solve(a) << std::endl;
    return 0;
}

