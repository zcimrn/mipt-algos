// https://contest.yandex.com/contest/29755/run-report/55230216

#include <iostream>
#include <vector>
#include <set>

int solve(std::vector<int>& a) {
    std::multiset<int> s;
    for (auto x : a) {
        s.insert(x);
    }
    int ans = 0;
    for (int a, b; s.size() > 1;) {
        a = *s.begin();
        s.erase(s.begin());
        b = *s.begin();
        s.erase(s.begin());
        s.insert(a + b);
        ans += a + b;
    }
    return ans;
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

