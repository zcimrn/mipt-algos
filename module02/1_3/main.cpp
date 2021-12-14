#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define int long long
#define float long double

float len(pair<int, int> a) {
    return sqrt(a.first * a.first + a.second * a.second);
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second / len(a) > b.second / len(b) ||
        a.second / len(a) == b.second / len(b) && len(a) < len(b);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n && cin >> a[i].first >> a[i].second; i++);
    sort(a.begin(), a.end());
    for (int i = n - 1; i > 0; i--) {
        a[i].first -= a[0].first;
        a[i].second -= a[0].second;
    }
    sort(a.begin() + 1, a.end(), cmp);
    for (int i = 1; i < n; i++) {
        a[i].first += a[0].first;
        a[i].second += a[0].second;
    }
    for (auto p : a) {
        cout << p.first << ' ' << p.second << endl;
    }
}
