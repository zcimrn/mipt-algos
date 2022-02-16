#include <bits/stdc++.h>

using namespace std;

signed main() {
    stack<pair<int, int>> s;
    int ans, w;
    cin >> ans >> w >> ans;
    s.push({0, ans});
    ans = 0;
    for (int tw, h; cin >> tw >> h; w += tw) {
        if (h > s.top().second) {
            s.push({w, h});
            continue;
        }
        int th;
        for (; s.size() && h <= s.top().second; s.pop()) {
            ans = max(ans, (w - s.top().first) * s.top().second);
            th = s.top().first;
        }
        s.push({th, h});
    }
    for (; s.size(); s.pop()) {
        ans = max(ans, (w - s.top().first) * s.top().second);
    }
    cout << ans << endl;
}
