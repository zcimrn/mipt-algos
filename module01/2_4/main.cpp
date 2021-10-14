#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct node {
    int v;
    node *n, *p;

    node(int _v = 0) {
        v = _v;
        n = 0;
        p = 0;
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<node> a(n);
    for (int i = 0; i < n; i++) {
        a[i].v = i + 1;
        a[i].n = &a[(i + 1) % n];
        a[i].p = &a[(i - 1 + n) % n];
    }
    node e = a[n - 1];
    for (; e.v != e.n->v;) {
        for (int i = 0; i < k; i++) {
            e = *e.n;
        }
        e.p->n = e.n;
        e.n->p = e.p;
        e = *e.p;
    }
    cout << e.v << endl;
}
