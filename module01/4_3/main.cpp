// https://contest.yandex.com/contest/29755/run-report/55227352

#include <iostream>
#include <vector>
#include <map>
#include <set>

int solve(std::vector<int>& a) {
    std::map<int, int> m;
    for (auto x : a) {
        m[x]++;
    }
    std::set<std::pair<int, int>> s;
    for (auto p : m) {
        s.insert({p.second, p.first});
    }
    for (std::pair<int, int> a, b; s.size() > 1;) {
        a = *s.rbegin();
        s.erase(a);
        b = *s.rbegin();
        s.erase(b);
        if (--a.first) {
            s.insert(a);
        }
        if (--b.first) {
            s.insert(b);
        }
    }
    if (s.size() == 0) {
        return 0;
    }
    return s.begin()->first;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cout << solve(a) << std::endl;
    return 0;
}

