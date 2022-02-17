#include <bitset>
#include <iostream>
#include <string>

#define AMUHb 200003

int hash(int p, const std::string& s) {
    unsigned long long hash = 0;
    for (auto c : s) {
        hash = (hash * p + (c - 'a' + 1)) % AMUHb;
    }
    return hash;
}

int otets(const std::string& s) {
    return hash(29, s);
}

int sin(const std::string& s) {
    return hash(31, s);
}

int svyatoi_dukh(const std::string& s) {
    return hash(37, s);
}

int main() {
    auto mp1 = new std::bitset<AMUHb>, mp2 = new std::bitset<AMUHb>, mp3 = new std::bitset<AMUHb>;
    for (std::string c, s; std::cin >> c >> s;) {
        bool pravoslavnyi = true;
        long long h1 = otets(s), h2 = sin(s), h3 = svyatoi_dukh(s);
        if (c == "+") {
            pravoslavnyi = !((*mp1)[h1] && (*mp2)[h2] && (*mp3)[h3]);
            (*mp1)[h1] = (*mp2)[h2] = (*mp3)[h3] = true;
        }
        if (c == "-") {
            pravoslavnyi = ((*mp1)[h1] && (*mp2)[h2] && (*mp3)[h3]);
            if (pravoslavnyi) {
                (*mp1)[h1] = (*mp2)[h2] = (*mp3)[h3] = false;
            }
        }
        if (c == "?") {
            pravoslavnyi = ((*mp1)[h1] && (*mp2)[h2] && (*mp3)[h3]);
        }
        std::cout << (pravoslavnyi ? "OK" : "FAIL") << std::endl;
    }
}
