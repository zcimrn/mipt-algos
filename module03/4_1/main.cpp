#include <bitset>
#include <queue>
#include <stack>
#include "Huffman.h"

std::vector<std::pair<unsigned, unsigned>> temp;

class BitReader {
private:
    std::bitset<1024> buffer{};
    unsigned buffer_size{};
    IInputStream& input;

public:
    BitReader(IInputStream& input) : input{input} {}

    bool read(unsigned& value, unsigned size) {
        if (buffer_size < size) {
            for (byte value; buffer_size < size; buffer_size += 8) {
                if (input.Read(value)) {
                    buffer = (buffer << 8) | std::bitset<1024>(value);
                }
                else {
                    return false;
                }
            }
        }
        buffer_size -= size;
        value = (buffer >> buffer_size).to_ulong();
        buffer = buffer << 1024 - buffer_size >> 1024 - buffer_size;
        return true;
    }
};

class BitWriter {
private:
    std::bitset<1024> buffer{};
    unsigned buffer_size{};
    IOutputStream& output;

    void write_part() {
        for (; buffer_size >= 8;) {
            buffer_size -= 8;
            output.Write((buffer >> buffer_size).to_ulong());
            buffer = buffer << 1024 - buffer_size >> 1024 - buffer_size;
        }
    }

public:
    BitWriter(IOutputStream& output) : output{output} {}

    void flush() {
        write_part();
        buffer <<= 8 - buffer_size;
        output.Write((byte)buffer.to_ulong());
        buffer >>= 8;
        buffer_size = 0;
    }

    void write(unsigned value, unsigned size) {
        buffer = (buffer << size) | std::bitset<1024>(value);
        buffer_size += size;
        write_part();
    }
};

class Huffman {
private:
    IInputStream& input;
    IOutputStream& output;
    std::vector<byte> data;
    std::vector<unsigned> frequencies;
    std::vector<std::pair<unsigned, unsigned>> tree, codes;

    void debug_data() {
        std::cerr << "data:" << std::endl;
        for (unsigned i = 0; i < data.size(); i++) {
            std::cerr << i << ' ' << (unsigned)data[i] << std::endl;
        }
        std::cerr << std::endl;
    }

    void debug_frequencies() {
        std::cerr << "frequencies:" << std::endl;
        for (unsigned i = 0; i < frequencies.size(); i++) {
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
                auto code = std::bitset<1024>(codes[i].first).to_string();
                reverse(code.begin(), code.end());
                code.resize(codes[i].second);
                reverse(code.begin(), code.end());
                std::cerr << i << ' ' << code << ' ' << codes[i].second << std::endl;
            }
        }
        std::cerr << std::endl;
    }

    void read_data() {
        data.resize(0);
        for (byte value; input.Read(value); data.push_back(value));
    }

    void count_frequencies() {
        frequencies.resize(256);
        for (auto value : data) {
            frequencies[value]++;
        }
    }

    void make_tree() {
        tree.resize(0);
        std::priority_queue<
            std::pair<unsigned, unsigned>,
            std::vector<std::pair<unsigned, unsigned>>,
            std::greater<std::pair<unsigned, unsigned>>
        > heap;
        for (int i = 0; i < 256; i++) {
            if (frequencies[i]) {
                heap.push({frequencies[i], tree.size()});
                tree.push_back({i, 511});
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

    void make_codes_dfs(unsigned i, unsigned code, unsigned code_size) {
        if (tree[i].second == 511) {
            codes[tree[i].first] = {code, code_size};
            return;
        }
        make_codes_dfs(tree[i].first, code * 2, code_size + 1);
        make_codes_dfs(tree[i].second, code * 2 + 1, code_size + 1);
    }

    void make_codes() {
        codes.resize(256);
        make_codes_dfs(tree.size() - 1, 0, 0);
    }

    void write_tree_dfs(BitWriter& bit_writer, unsigned i, bool only_commands = false) {
        if (tree[i].second == 511) {
            if (only_commands) {
                bit_writer.write(0, 1);
                std::cerr << "get value " << tree[i].first << std::endl;
            }
            else {
                bit_writer.write(tree[i].first, 8);
            }
            return;
        }
        write_tree_dfs(bit_writer, tree[i].first, only_commands);
        write_tree_dfs(bit_writer, tree[i].second, only_commands);
        if (only_commands) {
            bit_writer.write(1, 1);
            std::cerr << "make node" << std::endl;
        }
    }

    void write_tree(BitWriter& bit_writer) {
        unsigned frequencies_count = 0;
        for (auto frequency : frequencies) {
            if (frequency) {
                frequencies_count++;
            }
        }
        std::cerr << "frequencies_count: " << frequencies_count << std::endl;
        bit_writer.write(frequencies_count % 256, 8);
        write_tree_dfs(bit_writer, tree.size() - 1);
        write_tree_dfs(bit_writer, tree.size() - 1, true);
    }

    void write_encoded(BitWriter& bit_writer) {
        bit_writer.write(data.size(), 64);
        for (auto value : data) {
            auto [code, code_size] = codes[value];
            bit_writer.write(code, code_size);
        }
    }

    void read_tree(BitReader& bit_reader) {
        tree.resize(0);
        unsigned size;
        bit_reader.read(size, 8);
        size = (size ? size : 256);
        std::cerr << "size: " << size << std::endl;
        std::vector<unsigned> values(size);
        for (unsigned i = 0; i < size; i++) {
            bit_reader.read(values[i], 8);
        }
        std::stack<std::pair<unsigned, unsigned>> s;
        for (unsigned i = 0; i < size || s.size() > 1;) {
            unsigned command;
            if (!bit_reader.read(command, 1)) {
                std::cerr << "can't read" << std::endl;
                exit(0);
            }
            std::cerr << "command: " << (command ? "make node" : "get value") << std::endl;
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
                s.push({values[i++], 511});
            }
        }
        tree.push_back(s.top());
    }

    void decode_data(BitReader& bit_reader) {
        unsigned size;
        bit_reader.read(size, 64);
        data.resize(size);
        for (unsigned i = 0, j; i < size; i++) {
            j = tree.size() - 1;
            for (unsigned bit; tree[j].second != 511;) {
                bit_reader.read(bit, 1);
                j = (bit ? tree[j].second : tree[j].first);
            }
            data[i] = tree[j].first;
        }
    }

    void write_data() {
        for (auto value : data) {
            output.Write(value);
        }
    }


public:
    Huffman(IInputStream& input, IOutputStream& output) : input{input}, output{output} {}

    void debug() {
        debug_data();
        debug_frequencies();
        debug_tree();
        debug_codes();
    }

    void encode() {
        std::cerr << "encoding..." << std::endl;
        read_data();
        temp_data = data;
        count_frequencies();
        debug_frequencies();
        make_tree();
        debug_tree();
        make_codes();
        debug_codes();
        temp = codes;
        BitWriter bit_writer(output);
        write_tree(bit_writer);
        write_encoded(bit_writer);
        bit_writer.flush();
    }

    void decode() {
        std::cerr << "decoding..." << std::endl;
        BitReader bit_reader(input);
        read_tree(bit_reader);
        debug_tree();
        make_codes();
        debug_codes();
        std::swap(temp, codes);
        debug_codes();
        std::cerr << (temp == codes ? "OK" : "FAILED") << std::endl;
        decode_data(bit_reader);
        write_data();
    }
};

void Encode(IInputStream& input, IOutputStream& output) {
    Huffman huffman(input, output);
    huffman.encode();
}

void Decode(IInputStream& input, IOutputStream& output) {
    Huffman huffman(input, output);
    huffman.decode();
}
