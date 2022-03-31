// https://contest.yandex.com/contest/36361/run-report/66619090

#include <iostream>
#include <vector>

std::vector<std::vector<long double>> read_graph(int n) {
    std::vector<std::vector<long double>> graph(n, std::vector<long double>(n, 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                std::cin >> graph[i][j];
            }
        }
    }
    return std::move(graph);
}

bool floyd(std::vector<std::vector<long double>>& dp) {
    int n = dp.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][k] != -1 && dp[k][j] != -1 && dp[i][j] < dp[i][k] * dp[k][j]) {
                    if (i == j) {
                        return true;
                    }
                    dp[i][j] = dp[i][k] * dp[k][j];
                }
            }
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    auto graph = read_graph(n);
    std::cout << (floyd(graph) ? "YES" : "NO") << std::endl;
    return 0;
}
