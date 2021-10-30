// https://contest.yandex.com/contest/30914/run-report/55659029

#include <iostream>
#include <vector>
#include <algorithm>

struct box {
    int x = 0, y = 0, z = 0, n = 0;

    box(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
        if (x > y) {
            std::swap(x, y);
        }
        if (x > z) {
            std::swap(x, z);
        }
        if (y > z) {
            std::swap(y, z);
        }
    }
};

bool cmp(box a, box b) {
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

std::vector<int> solve(std::vector<box>& a) {
    for (int i = 0; i < a.size(); i++) {
        a[i].n = i;
    }
    std::stable_sort(a.begin(), a.end(), cmp);
    std::vector<int> ans(a.size());
    for (int i = 0; i < a.size(); i++) {
        ans[i] = a[i].n;
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<box> a;
    for (int x, y, z, i = 0; i < n; i++) {
        std::cin >> x >> y >> z;
        a.push_back({x, y, z});
    }
    for (int x : solve(a)) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    return 0;
}

