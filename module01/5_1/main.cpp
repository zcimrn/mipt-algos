#include <iostream>
#include <map>
#include <stack>

using namespace std;

bool is_open(char c) {
    return c == '(' || c == '[' || c == '{';
}

signed main() {
    map<char, char> b = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    string a;
    cin >> a;
    stack<char> s;
    for (auto c: a) {
        if (s.size() && is_open(s.top()) && b[s.top()] == c) {
            s.pop();
            continue;
        }
        if (s.size() && is_open(s.top()) && !is_open(c)) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        s.push(c);
    }
    for (; s.size() && is_open(s.top()); s.pop()) {
        a += b[s.top()];
    }
    for (; s.size(); s.pop()) {
        cout << b[s.top()];
    }
    cout << a << endl;
}
