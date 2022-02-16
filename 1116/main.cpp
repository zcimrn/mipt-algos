#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double


signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n / 2; i++) {
        swap(a[i], a[n - 1 - i]);
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}
