#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 0; i < n && cin >> a[i]; i++);
    a[n] = 1e9;
    cin >> n;
    for (int x; cin >> x;) {
        int l = 0, r = a.size() - 1;
        for (int m = (l + r) / 2; r - l > 1; m = (l + r) / 2) {
            if (a[m] > x) {
                r = m;
            }
            else {
                l = m;
            }
        }
        cout << (x - a[l] <= a[r] - x ? l : r) << ' ';
    }
    cout << endl;
}
