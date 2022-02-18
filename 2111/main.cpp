// https://contest.yandex.com/contest/35212/run-report/65267815

#include <iostream>
#include <string>
#include <vector>

class StringSet {
private:
    std::vector<std::string> table = std::vector<std::string>(8);
    std::vector<bool> deleted = std::vector<bool>(8);
    int count = 0;

    int hash(const std::string& key, int size) const {
        int hash = 0;
        for (auto c : key) {
            hash = (hash * 29 + c - 'a') % size;
        }
        return hash;
    }

    int get_index(const std::string& key, const std::vector<std::string>& table) const {
        int size = table.size(), index = hash(key, size);
        for (
            int i = 0;
            i < size && table[index] != key && table[index] != "";
            index = (index + ++i) % size
        );
        return index;
    }

    int get_index(const std::string& key) const {
        return get_index(key, table);
    }

    void rehash() {
        std::vector<std::string> new_table(table.size() * 2);
        count = 0;
        for (int i = 0, size = table.size(); i < size; i++) {
            if (table[i] != "" && !deleted[i]) {
                new_table[get_index(table[i], new_table)] = std::move(table[i]);
                count++;
            }
            deleted[i] = false;
        }
        table = std::move(new_table);
        deleted.resize(table.size());
    }

public:
    bool contains(const std::string& key) const {
        int index = get_index(key);
        if (table[index] == "" || deleted[index]) {
            return false;
        }
        return true;
    }

    bool insert(const std::string& key) {
        int index = get_index(key);
        if (table[index] != "" && !deleted[index]) {
            return false;
        }
        table[index] = key;
        deleted[index] = false;
        count++;
        if (count >= table.size() / 4 * 3) {
            rehash();
        }
        return true;
    }

    bool erase(const std::string& key) {
        int index = get_index(key);
        if (table[index] == "" || deleted[index]) {
            return false;
        }
        return deleted[index] = true;
    }
};

int main() {
    StringSet string_set;
    for (std::string command, key; std::cin >> command >> key;) {
        bool ok;
        if (command == "+") {
            ok = string_set.insert(key);
        }
        else if (command == "-") {
            ok = string_set.erase(key);
        }
        else if (command == "?") {
            ok = string_set.contains(key);
        }
        std::cout << (ok ? "OK" : "FAIL") << std::endl;
    }
}
