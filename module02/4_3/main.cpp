#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

int merge(vector<int>& a, int l, int m, int r) {
    vector<int> v;
    int i = l, j = m, k = 0;
    for (; i < m && j < r;) {
        if (a[i] <= a[j]) {
            v.push_back(a[i++]);
        }
        else {
            k += m - i;
            v.push_back(a[j++]);
        }
    }
    for (; i < m;) {
        v.push_back(a[i++]);
    }
    for (; j < r;) {
        v.push_back(a[j++]);
    }
    for (i = 0; i < v.size(); i++) {
        a[l + i] = v[i];
    }
    return k;
}

signed main() {
    vector<int> a;
    for (int x; cin >> x; a.push_back(x));
    int n = a.size(), ans = 0;
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n; j += i * 2) {
            ans += merge(a, j, min(j + i, n), min(j + i * 2, n));
        }
    }
    cout << ans << endl;
}
