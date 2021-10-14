#include <iostream>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<int> s;
    for (int x; cin >> x; s.insert(x));
    int ans = 0;
    for (int a, b; s.size() > 1;) {
        a = *s.begin();
        s.erase(s.begin());
        b = *s.begin();
        s.erase(s.begin());
        s.insert(a + b);
        ans += a + b;
    }
    cout << ans << endl;
}
