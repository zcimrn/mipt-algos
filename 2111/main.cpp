// https://contest.yandex.com/contest/35212/run-report/65304871

#include <iostream>
#include <string>
#include <vector>

struct Hash {
    unsigned long long operator()(const std::string& key) const {
        unsigned long long hash = 0;
        for (auto c : key) {
            hash = (hash * 29 + c - 'a');
        }
        return hash;
    }
};

template <class Key, class Hash = std::hash<Key>>
class HashSet {
private:
    std::vector<Key> table = std::vector<Key>(8);
    std::vector<bool> deleted = std::vector<bool>(8);
    int count = 0;
    Hash hash = Hash();
    Key null = Key();

    int get_index(const Key& key, const std::vector<Key>& table) const {
        int size = table.size(), index = hash(key) % size;
        for (
            int i = 0;
            i < size && table[index] != key && table[index] != null;
            index = (index + ++i) % size
        );
        return index;
    }

    int get_index(const Key& key) const {
        return get_index(key, table);
    }

    void rehash() {
        std::vector<Key> new_table(table.size() * 2);
        count = 0;
        for (int i = 0, size = table.size(); i < size; i++) {
            if (table[i] != null && !deleted[i]) {
                new_table[get_index(table[i], new_table)] = std::move(table[i]);
                count++;
            }
            deleted[i] = false;
        }
        table = std::move(new_table);
        deleted.resize(table.size());
    }

public:
    bool contains(const Key& key) const {
        int index = get_index(key);
        return table[index] != null && !deleted[index];
    }

    bool insert(const Key& key) {
        int index = get_index(key);
        if (table[index] != null && !deleted[index]) {
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

    bool erase(const Key& key) {
        int index = get_index(key);
        if (table[index] == null || deleted[index]) {
            return false;
        }
        return deleted[index] = true;
    }
};

int main() {
    HashSet<std::string, Hash> string_set;
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
    return 0;
}
