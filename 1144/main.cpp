#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double

signed main() {
    string s;
    cin >> s;
    int ans = 0;
    for (int l = 0, r = s.size() - 1; l < r;) {
        if (s[l] == s[r]) {
            l++;
            r--;
            continue;
        }
        else if (s[l + 1] == s[r] && !ans) {
            ans = l + 1;
            l += 2;
            r--;
            continue;
        }
        ans = 0;
        break;
    }
    if (ans) {
        cout << ans << endl;
        return 0;
    }
    for (int l = 0, r = s.size() - 1; l < r;) {
        if (s[l] == s[r]) {
            l++;
            r--;
            continue;
        }
        else if (s[l] == s[r - 1] && !ans) {
            ans = r + 1;
            l++;
            r -= 2;
            continue;
        }
        ans = 0;
        break;
    }
    if (ans) {
        cout << ans << endl;
        return 0;
    }
    cout << 0 << endl;
}
