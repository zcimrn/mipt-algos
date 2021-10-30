// https://contest.yandex.com/contest/30914/run-report/55704576

#include <iostream>
#include <vector>

int partition(std::vector<int>& a, int l, int r) {
    int i = l + rand() % (r - l);
    std::swap(a[i], a[l]);
    i = r - 1;
    for (int j = i; j >= l; j--) {
        if (a[j] >= a[l]) {
            std::swap(a[j], a[i]);
            i--;
        }
    }
    return i + 1;
}

int get_kth_order_stat(std::vector<int>& a, int k) {
    for (int l = 0, r = a.size(); r - l > 1;) {
        int pivot = partition(a, l, r);
        if (pivot == k) {
            return a[pivot];
        }
        (pivot < k ? l : r) = pivot;
    }
    return a[k];
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n && std::cin >> a[i]; i++);
    srand(time(0));
    std::cout << get_kth_order_stat(a, k) << std::endl;
    return 0;
}

