#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n * 2);
    for (int i = 0, l, r; i < n && cin >> l >> r; i++) {
        a[i * 2] = {l, -1};
        a[i * 2 + 1] = {r, 1};
    }
    sort(a.begin(), a.end());
    int b = 0, p = -1e9, ans = 0;
    for (int i = 0; i < n * 2; i++) {
        b -= a[i].second;
        if (b && p == -1e9) {
            p = a[i].first;
        }
        if (!b) {
            ans += a[i].first - p;
            p = -1e9;
        }
    }
    cout << ans << endl;
}
