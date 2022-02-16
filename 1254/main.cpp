// https://contest.yandex.com/contest/30914/run-report/55735647

#include <iostream>
#include <vector>
#include <stack>

struct frame {
    size_t l = 0, r = 0;
    unsigned long long mask = 0;

    frame(size_t l, size_t r, unsigned long long mask) : l {l}, r {r}, mask {mask} {}
};

size_t partition(std::vector<unsigned long long>& a, frame& frame) {
    size_t pivot = frame.l;
    for (size_t i = pivot; i < frame.r; i++) {
        if (!(a[i] & frame.mask)) {
            std::swap(a[i], a[pivot]);
            pivot++;
        }
    }
    return pivot;
}

void super_sort(std::vector<unsigned long long>& a) {
    std::stack<frame> frames;
    frames.push({0, a.size(), 1ull << 63});
    for (; frames.size();) {
        auto frame = frames.top();
        frames.pop();
        size_t pivot = partition(a, frame);
        if (pivot - frame.l > 1 && frame.mask > 1) {
            frames.push({frame.l, pivot, frame.mask >> 1});
        }
        if (frame.r - pivot > 1 && frame.mask > 1) {
            frames.push({pivot, frame.r, frame.mask >> 1});
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<unsigned long long> a(n);
    for (int i = 0; i < n && std::cin >> a[i]; i++);
    super_sort(a);
    for (auto x : a) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    return 0;
}

