#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n && cin >> a[i]; i++);
    int k;
    cin >> k;
    for (int i = 0; i < (int)log2(k); i++) {
        vector<int> t(a.size() - 1);
        for (int j = 0; j < t.size(); j++) {
            t[j] = max(a[j], a[j + 1]);
        }
        a = t;
    }
    for (int i = 0; i <= n - k; i++) {
        cout << max(a[i], a[i + k - (int)log2(k) - 1]) << ' ';
    }
    cout << endl;
}
