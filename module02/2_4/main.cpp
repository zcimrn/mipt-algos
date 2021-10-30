// https://contest.yandex.com/contest/30914/run-report/55686340

#include <iostream>
#include <vector>
#include <queue>

int get_one_layer_length(std::vector<std::pair<int, int>>& sections) {
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::greater<std::pair<int, int>>> points;
    for (auto section : sections) {
        if (section.first == section.second) {
            continue;
        }
        points.push({std::min(section.first, section.second), 1});
        points.push({std::max(section.first, section.second), -1});
    }
    int answer = 0, start_point = -2e9, layer = 0;
    for (int point; points.size(); points.pop()) {
        point = points.top().first;
        layer += points.top().second;
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

