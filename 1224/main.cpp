// https://contest.yandex.com/contest/30914/run-report/55709559

#include <iostream>
#include <vector>
#include <cmath>

void heapify(std::vector<std::pair<int, char>>& heap, int i) {
    int n = heap.size();
    for (;;) {
        if (i * 2 + 2 < n && heap[i * 2 + 2] < heap[i * 2 + 1] && heap[i * 2 + 2] < heap[i]) {
            std::swap(heap[i * 2 + 2], heap[i]);
            i = i * 2 + 2;
            continue;
        }
        if (i * 2 + 1 < n && heap[i * 2 + 1] < heap[i]) {
            std::swap(heap[i * 2 + 1], heap[i]);
            i = i * 2 + 1;
            continue;
        }
        break;
    }
}

void build_heap(std::vector<std::pair<int, char>>& heap) {
    int n = (1 << static_cast<int>(log2(heap.size() * 2)));
    for (int i = n / 2 - 2; i >= 0; i--) {
        heapify(heap, i);
    }
}

std::pair<int, char> get_min(std::vector<std::pair<int, char>>& heap) {
    auto min = heap[0];
    heap[0] = *heap.rbegin();
    heap.resize(heap.size() - 1);
    heapify(heap, 0);
    return min;
}

int get_one_layer_length(std::vector<std::pair<int, int>>& sections) {
    std::vector<std::pair<int, char>> points;
    for (auto section : sections) {
        if (section.first == section.second) {
            continue;
        }
        points.push_back({std::min(section.first, section.second), 1});
        points.push_back({std::max(section.first, section.second), -1});
    }
    build_heap(points);
    int answer = 0;
    for (int point, start_point = -2e9, layer = 0; points.size();) {
        auto point_info = get_min(points);
        point = point_info.first;
        layer += point_info.second;
        if (layer == 1) {
            start_point = point;
        }
        else if (start_point != -2e9) {
            answer += point - start_point;
            start_point = -2e9;
        }
    }
    return answer;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> sections(n);
    for (int i = 0; i < n; i++) {
        std::cin >> sections[i].first >> sections[i].second;
    }
    std::cout << get_one_layer_length(sections) << std::endl;
    return 0;
}

