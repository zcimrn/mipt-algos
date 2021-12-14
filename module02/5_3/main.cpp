#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<unsigned long long> a(n);
    for (int i = 0; i < n && cin >> a[i]; i++);
    sort(a.begin(), a.end());
    for (auto x : a) {
        cout << x << ' ';
    }
    cout << endl;
}
