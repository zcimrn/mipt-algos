// https://contest.yandex.com/contest/35212/run-report/65263977

#include <iostream>
#include <vector>

void make_cache(std::vector<std::vector<long long>>& cache, long long layer_count, long long count) {
    cache[layer_count][count] = 1;
    for (
        long long next_layer_count = layer_count + 1;
        next_layer_count * 2 < count;
        next_layer_count++
    ) {
        if (cache[next_layer_count][count - next_layer_count] == 9e18) {
            make_cache(cache, next_layer_count, count - next_layer_count);
        }
        cache[layer_count][count] += cache[next_layer_count][count - next_layer_count];
    }
}

int main() {
    int count;
    std::cin >> count;
    std::vector<std::vector<long long>> cache(count + 1, std::vector<long long>(count + 1, 9e18));
    make_cache(cache, 0, count);
    std::cout << cache[0][count] << std::endl;
    return 0;
}
