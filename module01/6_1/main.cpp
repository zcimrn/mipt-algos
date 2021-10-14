#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double

signed main() {
    int n;
    cin >> n;
    multiset<int> s;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        s.insert(x);
    }
    int k;
    cin >> k;
    int ans = 0;
    for (; s.size(); ans++) {
        int sum = 0;
        vector<int> a;
        for (; s.size() && sum + *s.rbegin() <= k;) {
            sum += *s.rbegin();
            a.push_back(*s.rbegin());
            s.erase(--s.end());
        }
        for (auto x: a) {
            if (x / 2) {
                s.insert(x / 2);
            }
        }
    }
    cout << ans << endl;
}
