// https://contest.yandex.com/contest/32613/run-report/61140935

#include <cassert>
#include <bitset>
#include <queue>
#include <stack>
#include <algorithm>
#include "Huffman.h"

const int MAX_SIZE = 256;

class BitReader {
private:
    std::vector<unsigned char> data;
    std::vector<unsigned char>::iterator iterator = data.begin();
    int buffer = 0, buffer_size = 0;

    bool read_bit(bool& bit) {
        if (buffer_size == 0) {
            if (iterator == data.end()) {
                bit = false;
                return false;
            }
            buffer = *iterator++;
            buffer_size += 8;
        }
        bit = buffer & (1 << --buffer_size);
        buffer &= (1 << buffer_size) - 1;
        return true;
    }

public:
    BitReader(IInputStream& input) {
        for (unsigned char value; input.Read(value); data.push_back(value));
        iterator = data.begin();
    }

    void debug() const {
        std::cerr << "input data" << std::endl;
        for (int i = 0; i < data.size(); i++) {
            std::cerr << i << ' ' << (int)data[i] << std::endl;
        }
        std::cerr << std::endl;
    }

    bool read(int& value, int size) {
        assert(size <= 32);
        value = 0;
        for (bool bit; size > 0; size--) {
            if (read_bit(bit)) {
                value = value * 2 + bit;
            }
            else {
                value = 0;
                return false;
            }
        }
        return true;
    }

    void reset() {
        iterator = data.begin();
        buffer = 0;
        buffer_size = 0;
    }
};

class BitWriter {
private:
    IOutputStream& output;
    std::vector<unsigned char> data;
    int buffer = 0, buffer_size = 0;

    void flush_byte() {
        assert(buffer_size == 8);
        unsigned char byte = buffer;
        data.push_back(byte);
        output.Write(byte);
        buffer = 0;
        buffer_size = 0;
    }

    void write_bit(bool bit) {
        buffer = buffer * 2 + bit;
        buffer_size++;
        if (buffer_size == 8) {
            flush_byte();
        }
    }

public:
    BitWriter(IOutputStream& output) : output{output} {}

    void debug() {
        std::cerr << "output data:" << std::endl;
        for (int i = 0; i < data.size(); i++) {
            std::cerr << i << ' ' << (int)data[i] << std::endl;
        }
        std::cerr << std::endl;
    }

    void flush() {
        if (buffer_size > 0) {
            assert(buffer_size < 8);
            buffer <<= 8 - buffer_size;
            buffer_size = 8;
            flush_byte();
        }
    }

    void write(const std::bitset<MAX_SIZE>& value, int size) {
        for (; size > 0;) {
            write_bit(value[--size]);
        }
    }
};

class Huffman {
private:
    BitReader& input;
    BitWriter& output;
    int data_size = 0;
    std::vector<int> frequencies;
    std::vector<std::pair<int, int>> tree;
    std::vector<std::pair<std::bitset<MAX_SIZE>, int>> codes;

    void debug_frequencies() {
        std::cerr << "frequencies:" << std::endl;
        for (int i = 0; i < frequencies.size(); i++) {
            if (frequencies[i]) {
                std::cerr << i << ' ' << frequencies[i] << std::endl;
            }
        }
        std::cerr << std::endl;
    }

    void debug_tree() {
        std::cerr << "tree:" << std::endl;
        for (int i = 0; i < tree.size(); i++) {
            std::cerr << i << ' ' << tree[i].first << ' ' << tree[i].second << std::endl;
        }
        std::cerr << std::endl;
    }

    void debug_codes() {
        std::cerr << "codes:" << std::endl;
        for (int i = 0; i < codes.size(); i++) {
            if (codes[i].second) {
                auto code = codes[i].first.to_string();
                std::reverse(code.begin(), code.end());
                code.resize(codes[i].second);
                std::reverse(code.begin(), code.end());
                std::cerr << i << ' ' << code << ' ' << codes[i].second << std::endl;
            }
        }
        std::cerr << std::endl;
    }

    void count_frequencies() {
        frequencies.resize(0);
        frequencies.resize(256);
        for (int value; input.read(value, 8);) {
            frequencies[value]++;
            data_size++;
        }
        input.reset();
    }

    void make_tree() {
        tree.resize(0);
        std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>
        > heap;
        for (int i = 0; i < frequencies.size(); i++) {
            if (frequencies[i]) {
                heap.push({frequencies[i], tree.size()});
                tree.push_back({i, -1});
            }
        }
        for (; heap.size() > 1;) {
            auto left = heap.top();
            heap.pop();
            auto right = heap.top();
            heap.pop();
            heap.push({left.first + right.first, tree.size()});
            tree.push_back({left.second, right.second});
        }
    }

    void make_codes_rec(int i, std::bitset<MAX_SIZE>& code, int code_size) {
        if (tree[i].second == -1) {
            codes[tree[i].first] = {code, code_size};
            return;
        }
        code <<= 1;
        make_codes_rec(tree[i].first, code, code_size + 1);
        code[0] = true;
        make_codes_rec(tree[i].second, code, code_size + 1);
        code >>= 1;
    }

    void make_codes() {
        codes.resize(0);
        codes.resize(256);
        std::bitset<MAX_SIZE> code;
        make_codes_rec(tree.size() - 1, code, 0);
    }

    void write_tree_rec(int i, bool only_commands = false) {
        if (tree[i].second == -1) {
            if (only_commands) {
                output.write(0, 1);
            }
            else {
                output.write(tree[i].first, 8);
            }
            return;
        }
        write_tree_rec(tree[i].first, only_commands);
        write_tree_rec(tree[i].second, only_commands);
        if (only_commands) {
            output.write(1, 1);
        }
    }

    void write_tree() {
        int frequencies_count = 0;
        for (auto frequency : frequencies) {
            if (frequency) {
                frequencies_count++;
            }
        }
        output.write(frequencies_count, 8);
        write_tree_rec(tree.size() - 1);
        write_tree_rec(tree.size() - 1, true);
    }

    void write_encoded() {
        output.write(data_size, 32);
        for (int value; input.read(value, 8);) {
            output.write(codes[value].first, codes[value].second);
        }
    }

    void read_tree() {
        tree.resize(0);
        int size;
        input.read(size, 8);
        size = (size ? size : 256); // here is a problem, what if the size is really equal to 0???
        std::vector<int> values(size);
        for (int i = 0; i < size; i++) {
            input.read(values[i], 8);
        }
        std::stack<std::pair<int, int>> s;
        for (int i = 0; i < size || s.size() > 1;) {
            int command;
            input.read(command, 1);
            if (command) {
                auto right = s.top();
                s.pop();
                auto left = s.top();
                s.pop();
                tree.push_back(left);
                tree.push_back(right);
                s.push({tree.size() - 2, tree.size() - 1});
            }
            else {
                s.push({values[i++], -1});
            }
        }
        tree.push_back(s.top());
    }

    void decode_data() {
        int size;
        input.read(size, 32);
        for (int i = 0, j; i < size; i++) {
            j = tree.size() - 1;
            for (int bit; tree[j].second != -1;) {
                input.read(bit, 1);
                j = (bit ? tree[j].second : tree[j].first);
            }
            output.write(tree[j].first, 8);
        }
    }


public:
    Huffman(BitReader& input, BitWriter& output) : input{input}, output{output} {}

    void debug() {
        debug_frequencies();
        debug_tree();
        debug_codes();
    }

    void encode() {
        count_frequencies();
        make_tree();
        write_tree();
        make_codes();
        write_encoded();
        output.flush();
    }

    void decode() {
        read_tree();
        decode_data();
        output.flush();
    }
};

void Encode(IInputStream& input, IOutputStream& output) {
    BitReader bit_reader(input);
    BitWriter bit_writer(output);
    Huffman huffman{bit_reader, bit_writer};
    huffman.encode();
}

void Decode(IInputStream& input, IOutputStream& output) {
    BitReader bit_reader(input);
    BitWriter bit_writer(output);
    Huffman huffman{bit_reader, bit_writer};
    huffman.decode();
}
