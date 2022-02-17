#include <iostream>
#include <vector>

void f(std::vector<std::vector<long long>>& cache, long long p, long long n) {
    cache[p][n] = 1;
    for (long long i = p; i * 2 <= n; i++) {
        if (cache[i][n - i] == 9e18) {
            f(cache, i, n - i);
        }
        cache[p][n] += cache[i][n - i];
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>> cache(n + 1, std::vector<long long>(n + 1, 9e18));
    f(cache, 0, n);
    std::cout << cache[0][n] - 1 << std::endl;
}
