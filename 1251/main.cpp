#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<string> a;
    for (string s; cin >> s; a.push_back(s));
    sort(a.begin(), a.end());
    for (auto s : a) {
        cout << s << endl;
    }
}
