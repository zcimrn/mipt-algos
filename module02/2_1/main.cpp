#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(pair<int, int>& a, pair<int, int>& b) {
    return a.second < b.second || a.second == b.second && a.first > b.first;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end(), cmp);
    int ans = 0, l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        if (a[i].first > r) {
            ans += 2;
            l = a[i].second - 1;
            r = a[i].second;
            continue;
        }
        if (a[i].first > l) {
            ans++;
            l = r;
            r = a[i].second;
            continue;
        }
    }
    cout << ans << endl;
}
