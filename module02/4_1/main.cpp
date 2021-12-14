#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    for (int i = 0; i < k && cin >> a[i]; i++);
    sort(a.begin(), a.end());
    for (int i = k, x; i < n && cin >> x; i++) {
        int j = k - 1;
        for (; j >= 0 && x < a[j]; j--) {
            a[j] = a[j - 1];
        }
        a[j + 1] = x;
    }
    for (int x : a) {
        cout << x << ' ';
    }
    cout << endl;
}
