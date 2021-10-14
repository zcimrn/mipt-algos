#include <bits/stdc++.h>

using namespace std;

signed main() {
    string a, b;
    cin >> a >> b;
    stack<char> s;
    for (int i = 0, j = 0; i < b.size(); i++) {
        if (s.size() && s.top() == b[i]) {
            s.pop();
            continue;
        }
        for (; j < b.size() && a[j] != b[i]; j++) {
            s.push(a[j]);
        }
        if (a[j] == b[i]) {
            j++;
            continue;
        }
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
}
