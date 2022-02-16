#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, char>> a(n * 2);
    for (int i = 0; i < n * 2; i += 2) {
        cin >> a[i].first;
        a[i].second = 0;
        cin >> a[i + 1].first;
        a[i + 1].second = 1;
    }
    stable_sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0, c = 0; i < a.size(); i++) {
        if (a[i].second == 0) {
            c++;
        }
        else {
            c--;
        }
        ans = max(ans, c);
    }
    cout << ans << endl;
}
