#include <bits/stdc++.h>

using namespace std;

pair<int, int> gcd(int a, int b) {
    if (!b) {
        return {1, 0};
    }
    auto p = gcd(b, a % b);
    return {p.second, p.first - a / b * p.second};
}

signed main() {
    int a, b;
    cin >> a >> b;
    swap(a, b);
    auto p = gcd(a, b);
    int x = p.first, y = p.second, d = x * a + y * b;
    assert(d < 3);
    x *= 2 / d;
    y *= 2 / d;
    for (; x <= 0 || y >= 0;) {
        x += b / d;
        y -= a / d;
    }
    cout << x * a - 1 << endl;
}
