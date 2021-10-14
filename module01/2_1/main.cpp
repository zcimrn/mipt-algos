#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double


signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i].first = i;
        cin >> a[i].second;
        if (i && a[i].second <= a[i - 1].second) {
            a[i] = a[i - 1];
        }
    }
    int ans = -1e18, ansi, ansj;
    for (int x, i = 0; cin >> x; i++) {
        if (ans < x + a[i].second) {
            ans = x + a[i].second;
            ansi = a[i].first;
            ansj = i;
        }
    }
    cout << ansi << ' ' << ansj << endl;
}
