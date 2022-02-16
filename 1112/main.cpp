#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> k;
    for (int i = 2, n = sqrt(k); i <= n; i++) {
        for (; k % i == 0; k /= i) {
            cout << i << ' ';
        }
    }
    if (k > 1) {
        cout << k << ' ';
    }
    cout << endl;
}
