// https://contest.yandex.com/contest/30914/run-report/55659178

#include <iostream>
#include <vector>
#include <algorithm>

int solve(std::vector<std::pair<int, int>>& v) {
    std::vector<std::pair<int, char>> a;
    for (auto x : v) {
        if (x.first == x.second) {
            continue;
        }
        a.push_back({std::min(x.first, x.second), 1});
        a.push_back({std::max(x.first, x.second), -1});
    }
    std::stable_sort(a.begin(), a.end());
    int ans = 0, p = -2e9, c = 0;
    for (int i = 0; i < a.size(); i++) {
        c += a[i].second;
        if (c == 1) {
            p = a[i].first;
        }
        if (c != 1 && p != -2e9) {
            ans += a[i].first - p;
            p = -2e9;
        }
    }
    return ans;
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

