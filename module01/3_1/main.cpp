#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a[0];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int x; cin >> x;) {
        int r = n;
        for (int l = -1, m = (l + r / 2); r - l > 1; m = (l + r) / 2) {
            if (x > a[m]) {
                l = m;
            }
            else {
                r = m;
            }
        }
        cout << r << ' ';
    }
    cout << endl;
}
