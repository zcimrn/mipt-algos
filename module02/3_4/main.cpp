// https://contest.yandex.com/contest/30914/run-report/55608994

#include <iostream>
#include <vector>

int partition(std::vector<int>& a, int l, int r) {
    int i = l + rand() % (r - l);
    std::swap(a[i], a[l]);
    i = r - 1;
    for (int j = i; j >= l; j--) {
        if (a[j] >= a[l]) {
            std::swap(a[j], a[i]);
            i--;
        }
    }
    return i + 1;
}

int solve(std::vector<int>& a, int k) {
    for (int l = 0, r = a.size(); r - l > 1;) {
        int p = partition(a, l, r);
        if (p == k) {
            return a[p];
        }
        if (p < k) {
            l = p;
        }
        else {
            r = p;
        }
    }
    return a[k];
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n && std::cin >> a[i]; i++);
    srand(time(0));
    std::cout << solve(a, k) << std::endl;
    return 0;
}

