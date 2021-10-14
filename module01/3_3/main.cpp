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
    for (int i = 0, x; i < n && cin >> x;) {
        for (; i < n && a[i] < x; i++);
        if (i < n && a[i] == x) {
            cout << x << ' ';
        }
    }
    cout << endl;
}
