// https://contest.yandex.com/contest/30914/run-report/55735133

#include <iostream>
#include <vector>
#include <stack>

struct frame {
    int l = 0, r = 0;
    unsigned long long mask = 0;

    frame(int _l, int _r, unsigned long long _mask) : l {_l}, r {_r}, mask {_mask} {}
};

int partition(std::vector<unsigned long long>& a, int l, int r, unsigned long long mask) {
    for (int i = l; i < r; i++) {
        if (!(a[i] & mask)) {
            std::swap(a[i], a[l]);
            l++;
        }
    }
    return l;
}

void super_sort(std::vector<unsigned long long>& a) {
    std::stack<frame> frames;
    frames.push({0, static_cast<int>(a.size()), 1ull << 63});
    for (; frames.size();) {
        auto frame = frames.top();
        frames.pop();
        int pivot = partition(a, frame.l, frame.r, frame.mask);
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

