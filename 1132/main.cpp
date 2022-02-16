#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double

signed main() {
    int n, ans = -1e18;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            ans = i;
            break;
        }
    }
    if (ans == -1e18) {
        ans = n - 1;
    }
    cout << ans << endl;
    int kekw;
    if (cin >> kekw) {
        assert(kekw == 9066);
    }
}
