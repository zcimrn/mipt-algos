#include <iostream>
#include <string>
#include <vector>

bool assert(bool good) {
    return 1 / good;
}

class BigInteger {
private:
    std::vector<int> value;
    bool negative = false;
    static const int MOD = 1e9;

    void reverse(std::string& s) const {
        for (int l = 0, r = s.size() - 1; l < r;) {
            std::swap(s[l++], s[r--]);
        }
    }

    void delete_leading_zeros(std::string& s) const {
        int size = s.size();
        for (int i = size - 1; i >= 0 && s[i] == '0'; i--, size--);
        s.resize(size);
    }

    void reverse(std::vector<int>& a) const {
        for (int l = 0, r = a.size() - 1; l < r;) {
            std::swap(a[l++], a[r--]);
        }
    }

    void delete_leading_zeros(std::vector<int>& a) const {
        int size = a.size();
        for (int i = size - 1; i >= 0 && a[i] == 0; i--, size--);
        a.resize(size);
    }

public:
    void debug() {
        std::cerr << "debug "  << (negative ? "-" : "") << "value[" << value.size() << "]:" << std::endl;
        for (int i = 0, size = value.size(); i < size; i++) {
            std::cerr << i << ' ' << value[i] << std::endl;
        }
    }

    BigInteger() = default;

    explicit BigInteger(const std::vector<int>& other_value, bool negative = false) : value(other_value), negative(negative) {
        for (int i = 0, size = value.size(); i < size; i++) {
            assert(value[i] >= 0 && value[i] < MOD);
        }
        delete_leading_zeros(value);
    }

    explicit operator bool() const {
        return value.size() > 0;
    }

    BigInteger(std::string s) {
        reverse(s);
        if (s.back() == '-') {
            negative = true;
            s.resize(s.size() - 1);
        }
        delete_leading_zeros(s);
        if (s.size() == 0) {
            negative = false;
            return;
        }
        int digit = 0, k = 1;
        for (int i = 0, size = s.size(); i < size; i++) {
            assert(s[i] >= '0' && s[i] <= '9');
            digit += (s[i] - '0') * k;
            k *= 10;
            if (k == MOD) {
                value.push_back(digit);
                digit = 0;
                k = 1;
            }
        }
        if (digit > 0) {
            value.push_back(digit);
        }
    }

    BigInteger(const char* s) : BigInteger(std::string(s)) {}

    BigInteger(long long x) : BigInteger(std::to_string(x)) {}

    std::string toString() const {
        std::string s;
        for (auto digit : value) {
            for (int i = 0; i < 9; i++) {
                s += '0' + digit % 10;
                digit /= 10;
            }
        }
        delete_leading_zeros(s);
        s += (s.size() == 0 ? "0" : "");
        s += (negative ? "-" : "");
        reverse(s);
        return std::move(s);
    }

    bool operator<(const BigInteger& other) const {
        if (negative != other.negative) {
            return negative;
        }
        if (value.size() != other.value.size()) {
            return negative && value.size() > other.value.size() || !negative && value.size() < other.value.size();
        }
        for (int i = value.size() - 1; i >= 0; i--) {
            if (value[i] != other.value[i]) {
                return negative && value[i] > other.value[i] || !negative && value[i] < other.value[i];
            }
        }
        return false;
    }

    bool operator>(const BigInteger& other) const {
        return other < *this;
    }

    bool operator==(const BigInteger& other) const {
        return !(*this < other) && !(other < *this);
    }

    bool operator!=(const BigInteger& other) const {
        return *this < other || other < *this;
    }

    bool operator<=(const BigInteger& other) const {
        return *this < other || !(other < *this);
    }

    bool operator>=(const BigInteger& other) const {
        return other < *this || !(*this < other);
    }

    BigInteger operator+() const {
        return std::move(*this);
    }

    BigInteger operator-() const {
        auto other = BigInteger(*this);
        other.negative = !other.negative;
        return std::move(other);
    }

    BigInteger operator+(const BigInteger& other) const {
        if (negative != other.negative) {
            return *this - -other;
        }
        std::vector<int> result_value;
        for (
            int i = 0, size = value.size(), other_size = other.value.size(), digit = 0;
            i < size || i < other_size || digit > 0;
            i++
        ) {
            digit += (i < size ? value[i] : 0) + (i < other_size ? other.value[i] : 0);
            result_value.push_back(digit % MOD);
            digit /= MOD;
        }
        return std::move(BigInteger(result_value, negative));
    }

    BigInteger& operator+=(const BigInteger& other) {
        return *this = *this + other;
    }

    BigInteger& operator++() {
        return *this += 1;
    }

    BigInteger operator++(int) {
        auto result = *this;
        operator++();
        return result;
    }

    BigInteger operator-(const BigInteger& other) const {
        if (negative != other.negative) {
            return *this + -other;
        }
        if (negative) {
            return -(-*this - -other);
        }
        if (*this < other) {
            return -(other - *this);
        }
        auto result_value = value;
        for (
            int i = 0, size = value.size(), other_size = other.value.size();
            i < size;
            i++
        ) {
            result_value[i] -= (i < other_size ? other.value[i] : 0);
            if (result_value[i] < 0) {
                result_value[i + 1]--;
                result_value[i] += MOD;
            }
        }
        delete_leading_zeros(result_value);
        return BigInteger(result_value);
    }

    BigInteger& operator-=(const BigInteger& other) {
        return *this = *this - other;
    }

    BigInteger& operator--() {
        return *this -= 1;
    }

    BigInteger operator--(int) {
        auto result = *this;
        operator--();
        return result;
    }

    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        for (int i = 0, size = value.size(); i < size; i++) {
            std::vector<int> t(i);
            long long digit = 0;
            for (int j = 0, other_size = other.value.size(); j < other_size; j++) {
                digit += (long long)other.value[j] * value[i];
                t.push_back(digit % MOD);
                digit /= MOD;
            }
            if (digit > 0) {
                t.push_back(digit);
            }
            result = result + BigInteger(t);
        }
        if (negative != other.negative) {
            result.negative = true;
        }
        return std::move(result);
    }

    BigInteger operator*=(const BigInteger& other) {
        return *this = *this * other;
    }

    BigInteger operator/(const BigInteger& other) const {
        if (value.size() < other.value.size()) {
            return {};
        }
        BigInteger result, d = other, t(std::vector<int>(value.end() - d.value.size() + 1, value.end()));
        d.negative = false;
        for (int i = value.size() - d.value.size(); i >= 0; i--) {
            t = t * MOD + value[i];
            int k = 0;
            for (int max_k = MOD, m; k + 1 < max_k;) {
                m = (k + max_k) / 2;
                if (t < d * m) {
                    max_k = m;
                }
                else {
                    k = m;
                }
            }
            result = result * MOD + k;
            t = t - d * k;
        }
        if (negative != other.negative) {
            result.negative = true;
        }
        return result;
    }

    BigInteger operator/=(const BigInteger& other) {
        return *this = *this / other;
    }

    BigInteger operator%(const BigInteger& other) const {
        return *this - *this / other * other;
    }

    BigInteger operator%=(const BigInteger& other) {
        return *this = *this % other;
    }
};

std::istream& operator>>(std::istream& in, BigInteger& x) {
    std::string s;
    in >> s;
    x = BigInteger(s);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
    return out << x.toString();
}
