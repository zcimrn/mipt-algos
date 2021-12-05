#include <iostream>
#include <vector>
#include <ctime>


typedef unsigned char byte;

class IInputStream {
private:
    int i = 0;
    std::vector<byte> data;

public:
    IInputStream(const std::vector<byte>& input) {
        data = input;
    }

    bool Read(byte& value) {
        if (i < data.size()) {
            value = data[i++];
            return 1;
        }
        return 0;
    }
};

class IOutputStream {
private:
    std::vector<byte> data;

public:
    void Write(byte value) {
        data.push_back(value);
    }

    std::vector<byte> get_data() {
        return data;
    }
};

void Encode(IInputStream& input, IOutputStream& output);

void Decode(IInputStream& input, IOutputStream& output);

int main() {
    srand(time(0));
    int n = 100000000;
    std::vector<byte> original(n);
    for (int i = 0; i < n; i++) {
        unsigned temp = 100;
        /*if (i % 2 == 1) {
            temp = 101;
        }
        if (i % 4 == 3) {
            temp = 102;
        }
        if (i % 8 == 7) {
            temp = 103;
        }
        if (i % 16 == 15) {
            temp = 104;
        }*/
        original[i] = rand() % 256;
    }
    /*freopen("file", "rb", stdin);
    for (int i = 0; i < n; i++) {
        char c;
        std::cin.read(&c, 1);
        original[i] = c;
    }*/
    auto original_stream = IInputStream{original};
    auto compressed_stream = IOutputStream{};
    Encode(original_stream, compressed_stream);
    auto compressed = compressed_stream.get_data();
    /*for (int i = 0; i < compressed.size(); i++) {
        auto bits = std::bitset<8>(compressed[i]).to_string();
        for (int j = 0; j < 8; j++) {
            if ((i * 8 + j) % 9 == 0) {
                std::cerr << std::endl;
            }
            std::cerr << i * 8 + j << ' ' << bits[j] << std::endl;
        }
    }
    */
    auto temp = IInputStream{compressed};
    auto decompressed_stream = IOutputStream{};
    Decode(temp, decompressed_stream);
    auto decompressed = decompressed_stream.get_data();
    std::cerr << original.size() << ' ' << compressed.size() << ' ';
    std::cerr << (long double)compressed.size() * 100 / original.size() << '%' << std::endl;
    std::cerr << (original == decompressed ? "OK" : "FAILED") << std::endl;
    /*freopen("decoded", "wb", stdout);
    for (auto value : decompressed) {
        std::cout << value;
    }
    std::cout.flush();
    */
}
