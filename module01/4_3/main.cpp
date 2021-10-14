#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> m;
    for (int x; cin >> x; m[x]++);
    set<pair<int, int>> s;
    for (auto p: m) {
        s.insert({p.second, p.first});
    }
    for (pair <int, int> a, b; s.size() > 1;) {
        a = *s.rbegin();
        s.erase(a);
        b = *s.rbegin();
        s.erase(b);
        if (--a.first) {
            s.insert(a);
        }
        if (--b.first) {
            s.insert(b);
        }
    }
    if (s.size() == 0) {
        cout << 0 << endl;
        return 0;
    }
    cout << s.begin()->first << endl;
}
