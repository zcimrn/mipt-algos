#include <bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    cin >> s;
    s = '(' + s + ')';
    map<char, int> p = {
        {'-', 2},
        {'+', 2},
        {'*', 1},
        {'/', 1},
        {'(', 0},
        {')', 3}
    };
    stack<int> s1;
    stack<char> s2;
    string t = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            t += s[i];
            continue;
        }
        else if (t != "") {
            s1.push(stoi(t));
            t = "";
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')') {
            for (int a, b; s2.size() && s2.top() != '(' && p[s[i]] >= p[s2.top()]; s2.pop()) {
                b = s1.top();
                s1.pop();
                a = s1.top();
                s1.pop();
                if (s2.top() == '+') {
                    s1.push(a + b);
                }
                if (s2.top() == '-') {
                    s1.push(a - b);
                }
                if (s2.top() == '*') {
                    s1.push(a * b);
                }
                if (s2.top() == '/') {
                    s1.push(a / b);
                }
            }
            if (s[i] == ')') {
                s2.pop();
            }
            else {
                s2.push(s[i]);
            }
        }
    }
    cout << s1.top() << endl;
}
