#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double


signed main() {
    int n;
    cin >> n;
    for (int a = 0, i = 0; i < n; i++) {
        a = a + i + i + 1;
        cout << a << ' ';
    }
    cout << endl;
}
