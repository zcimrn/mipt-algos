#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) {
            cout << n / i << ' ' << n - n / i << endl;
            return 0;
        }
    }
    cout << "1 " << n - 1 << endl;
}
