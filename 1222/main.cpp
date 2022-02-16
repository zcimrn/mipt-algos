#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct date {
    int d, m, y, t;

    date() : d {0}, m {0}, y {0}, t {0} {}

    date(int d, int m, int y, int t) : d {d}, m {m}, y {y}, t {t} {}
};

bool operator<(const date a, const date b) {
    return a.y < b.y ||
        a.y == b.y && a.m < b.m ||
        a.y == b.y && a.m == b.m && a.d < b.d ||
        a.y == b.y && a.m == b.m && a.d == b.d && a.t < b.t;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<date> a;
    for (int i = 0; i < n; i++) {
        date l, r;
        cin >> l.d >> l.m >> l.y >> r.d >> r.m >> r.y;
        l.y += 80;
        r = min(r, l);
        l.y -= 62;
        if (l < r) {
            l.t = 1;
            r.t = -1;
            a.push_back(l);
            a.push_back(r);
        }
    }
    sort(a.begin(), a.end());
    int c = 0, ans = 0;
    for (auto x : a) {
        c += x.t;
        ans = max(ans, c);
    }
    cout << ans << endl;
}
