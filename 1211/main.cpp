// https://contest.yandex.com/contest/30914/run-report/55682172

#include <iostream>
#include <vector>
#include <algorithm>

struct box {
    int x, y, z, num;

    void flip() {
        if (x > y) {
            std::swap(x, y);
        }
        if (x > z) {
            std::swap(x, z);
        }
        if (y > z) {
            std::swap(y, z);
        }
    }

    bool operator<(box& other) {
        return x < other.x && y < other.y && z < other.z;
    }
};

void sort_boxes(std::vector<box>& boxes) {
    int n = boxes.size();
    for (int i = 0; i < n; i++) {
        boxes[i].flip();
    }
    for (int i = 1; i < n; i++) {
        auto box = boxes[i];
        int j = i - 1;
        for (; j >= 0 && box < boxes[j]; j--) {
            boxes[j + 1] = boxes[j];
        }
        boxes[j + 1] = box;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<box> boxes(n);
    for (int i = 0; i < n; i++) {
        std::cin >> boxes[i].x >> boxes[i].y >> boxes[i].z;
        boxes[i].num = i;
    }
    sort_boxes(boxes);
    for (auto box : boxes) {
        std::cout << box.num << ' ';
    }
    std::cout << std::endl;
    return 0;
}

