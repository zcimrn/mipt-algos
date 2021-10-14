#include <iostream>

using namespace std;

int main() {
    int n, x, y, xa, ya;
    cin >> n >> x >> y >> xa >> ya;
    xa -= x;
    ya -= y;
    int ans = 0;
    for (int xb, yb; cin >> xb >> yb;) {
        xb -= x;
        yb -= y;
        ans += xb * ya - yb * xa;
        xa = xb;
        ya = yb;
    }
    cout << (long double)ans / 2 << endl;
}
