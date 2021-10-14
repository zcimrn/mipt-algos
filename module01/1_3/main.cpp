#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double

int gcd(int a, int b) {
    for (; b;) {
        a %= b;
        swap(a, b);
    }
    return a;
}

signed main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << (a * d + c * b) / gcd(a * d + c * b, b * d) << ' ' << b * d / gcd(a * d + c * b, b * d) << endl;
}
