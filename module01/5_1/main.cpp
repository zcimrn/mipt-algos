// https://contest.yandex.com/contest/29755/run-report/55229143

#include <iostream>
#include <map>
#include <stack>

bool is_open(char c) {
    return c == '(' || c == '[' || c == '{';
}

std::string solve(std::string a) {
    std::map<char, char> b = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    std::stack<char> s;
    for (auto c : a) {
        if (s.size() && is_open(s.top()) && b[s.top()] == c) {
            s.pop();
            continue;
        }
        if (s.size() && is_open(s.top()) && !is_open(c)) {
            return "IMPOSSIBLE";
        }
        s.push(c);
    }
    for (; s.size() && is_open(s.top()); s.pop()) {
        a += b[s.top()];
    }
    std::string t = "";
    for (; s.size(); s.pop()) {
        t += b[s.top()];
    }
    return t + a;
}

int main() {
    std::string a;
    std::cin >> a;
    std::cout << solve(a) << std::endl;
    return 0;
}

