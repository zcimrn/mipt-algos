// https://contest.yandex.com/contest/29755/run-report/55215222

#include <iostream>

int solve(int n) {
    int ans = 0;
    for (; n; ans += n /= 5);
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << solve(n) << std::endl;
    return 0;
}

