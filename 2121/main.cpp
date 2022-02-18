// https://contest.yandex.com/contest/35212/run-report/65301233

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> athletes;
    for (
        int weight, power;
        std::cin >> weight >> power;
        athletes.emplace_back(weight, power)
    );
    std::sort(athletes.begin(), athletes.end());
    int all_weight = 0, count = 0;
    for (auto [weight, power] : athletes) {
        if (all_weight <= power) {
            all_weight += weight;
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}
