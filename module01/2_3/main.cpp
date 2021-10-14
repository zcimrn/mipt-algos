#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = m - 1; i >= 0; i--) {
        cin >> b[i];
    }
    int k;
    cin >> k;
    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m; i++) {
        for (; j < m && a[i] + b[j] > k; j++);
        if (j < m && a[i] + b[j] == k) {
            ans++;
        }
    }
    cout << ans << endl;
}
