#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n && cin >> a[i]; i++);
    sort(a.begin(), a.end());
    for (auto s : a) {
        cout << s << endl;
    }
}
