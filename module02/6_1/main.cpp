// https://contest.yandex.com/contest/30914/run-report/55927504

#include "sort.h"
#include <deque>

void easy_sort(unsigned* a, int size) {
    for (int i = size - 1; i > 0; i--) {
        int t = i;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[t]) {
                t = j;
            }
        }
        if (t != i) {
            std::swap(a[t], a[i]);
        }
    }
}

std::pair<int, int> partition(unsigned* a, int size) {
    int l = 0, r = size - 1;
    unsigned min = a[l], pivot = a[(l + r) / 2], max = a[r];
    if (min > pivot) {
        std::swap(min, pivot);
    }
    if (min > max) {
        std::swap(min, max);
    }
    if (pivot > max) {
        std::swap(pivot, max);
    }
    for (int i = l; i <= r; i++) {
        if (a[i] < pivot) {
            std::swap(a[i], a[l++]);
        }
    }
    for (int i = r; i >= l; i--) {
        if (a[i] > pivot) {
            std::swap(a[i], a[r--]);
        }
    }
    return {l, r + 1};
}

void Sort(unsigned* a, unsigned size) {
    int easy_size = 5;
    if (size <= easy_size) {
        easy_sort(a, size);
        return;
    }
    std::deque<std::pair<int, int>> frames;
    frames.push_back({0, size});
    for (int l, r; frames.size();) {
        l = frames.back().first;
        r = frames.back().second;
        frames.pop_back();
        auto pivot_lr = partition(a + l, r - l);
        int pivot_l = l + pivot_lr.first, pivot_r = l + pivot_lr.second;
        if (pivot_l - l > easy_size) {
            frames.push_back({l, pivot_l});
        }
        else if (pivot_l - l > 1) {
            easy_sort(a + l, pivot_l - l);
        }
        if (r - pivot_r > easy_size) {
            frames.push_back({pivot_r, r});
        }
        else if (r - pivot_r > 1) {
            easy_sort(a + pivot_r, r - pivot_r);
        }
    }
}

