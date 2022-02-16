// https://contest.yandex.com/contest/29755/run-report/55225171

#include <iostream>
#include <vector>

std::vector<int> solve(std::vector<int>& a, std::vector<int>& b) {
    a.push_back(1e9);
    std::vector<int> ans(b.size());
    for (int i = 0; i < b.size(); i++) {
        int l = 0, r = a.size() - 1;
        for (int m = (l + r) / 2; l + 1 < r; m = (l + r) / 2) {
            if (a[m] > b[i]) {
                r = m;
            }
            else {
                l = m;
            }
        }
        if (b[i] - a[l] <= a[r] - b[i]) {
            ans[i] = l;
        }
        else {
            ans[i] = r;
        }
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
    std::cin >> n;
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    for (auto i : solve(a, b)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}

