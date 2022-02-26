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

    template<class T>
    static void reverse(T& a) {
        for (int l = 0, r = a.size() - 1; l < r;) {
            std::swap(a[l++], a[r--]);
        }
    }

    static void delete_leading_zeros(std::string& s) {
        int i = s.size() - 1;
        for (; i >= 0 && s[i] == '0'; i--);
        s.resize(i + 1);
    }

    static void delete_leading_zeros(std::vector<int>& a) {
        int i = a.size() - 1;
        for (; i >= 0 && a[i] == 0; i--);
        a.resize(i + 1);
    }

    static bool less(const std::vector<int>& a, const std::vector<int>& b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return false;
    }

    static std::vector<int> add(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> r;
        for (int i = 0, a_size = a.size(), b_size = b.size(), digit = 0; i < a_size || i < b_size || digit > 0; i++) {
            digit += (i < a_size ? a[i] : 0) + (i < b_size ? b[i] : 0);
            r.push_back(digit % MOD);
            digit /= MOD;
        }
        return std::move(r);
    }

    static std::vector<int> sub(const std::vector<int>& a, const std::vector<int>& b) {
        if (less(a, b)) {
            return sub(b, a);
        }
        auto r = a;
        for (int i = 0, size = r.size(), b_size = b.size(); i < size; i++) {
            r[i] -= (i < b_size ? b[i] : 0);
            if (r[i] < 0) {
                r[i + 1]--;
                r[i] += MOD;
            }
        }
        delete_leading_zeros(r);
        return std::move(r);
    }

    static std::vector<int> mult(const std::vector<int>& a, int k) {
        std::vector<int> r;
        long long digit = 0;
        for (int i = 0, size = a.size(); i < size; i++) {
            digit += (long long)a[i] * k;
            r.push_back(digit % MOD);
            digit /= MOD;
        }
        if (digit > 0) {
            r.push_back(digit);
        }
        return std::move(r);
    }

    static std::vector<int> mult(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> r;
        for (int i = 0, a_size = a.size(); i < a_size; i++) {
            std::vector<int> t(i);
            t.insert(t.end(), b.begin(), b.end());
            r = add(r, mult(t, a[i]));
        }
        return std::move(r);
    }

    static std::vector<int> div(const std::vector<int>& a, const std::vector<int>& b, bool remainder = false) {
        std::vector<int> r;
        if (less(a, b)) {
            return remainder ? std::move(a) : std::move(r);
        }
        std::vector<int> t(a.end() - b.size() + 1, a.end());
        for (int i = a.size() - b.size(); i >= 0; i--) {
            t.insert(t.begin(), a[i]);
            int k = 0;
            for (int max_k = MOD, mid_k; k + 1 < max_k;) {
                mid_k = (k + max_k) / 2;
                if (less(t, mult(b, mid_k))) {
                    max_k = mid_k;
                }
                else {
                    k = mid_k;
                }
            }
            r.push_back(k);
            t = sub(t, mult(b, k));
        }
        reverse(r);
        return remainder ? std::move(t) : std::move(r);
    }

public:
    void debug() {
        std::cerr << "debug "  << (negative ? "-" : "") << "value[" << value.size() << "]:" << std::endl;
        for (int i = 0, size = value.size(); i < size; i++) {
            std::cerr << i << ' ' << value[i] << std::endl;
        }
    }

    BigInteger() = default;

    explicit BigInteger(const std::vector<int>& value_, bool negative_ = false) : value(value_), negative(negative_) {
        for (int i = 0, size = value.size(); i < size; i++) {
            assert(value[i] >= 0 && value[i] < MOD);
        }
        delete_leading_zeros(value);
        if (value.size() == 0) {
            negative = false;
        }
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
        return !negative && less(value, other.value) || negative && less(other.value, value);
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
        return std::move(BigInteger(value, !negative));
    }

    BigInteger operator+(const BigInteger& other) const {
        if (negative != other.negative) {
            return BigInteger(sub(value, other.value), less(value, other.value) ? !negative : negative);
        }
        return BigInteger(add(value, other.value), negative);
    }

    BigInteger operator-(const BigInteger& other) const {
        if (negative != other.negative) {
            return BigInteger(add(value, other.value), negative);
        }
        return BigInteger(sub(value, other.value), less(value, other.value) ? !negative : negative);
    }

    BigInteger operator*(const BigInteger& other) const {
        return BigInteger(mult(value, other.value), negative != other.negative);
    }

    BigInteger operator/(const BigInteger& other) const {
        return BigInteger(div(value, other.value), negative != other.negative);
    }

    BigInteger operator%(const BigInteger& other) const {
        return BigInteger(div(value, other.value, true), negative);
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
        return std::move(result);
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
        return std::move(result);
    }

    BigInteger& operator*=(const BigInteger& other) {
        return *this = *this * other;
    }

    BigInteger& operator/=(const BigInteger& other) {
        return *this = *this / other;
    }

    BigInteger& operator%=(const BigInteger& other) {
        return *this = *this % other;
    }
};

std::istream& operator>>(std::istream& stream, BigInteger& x) {
    std::string s;
    stream >> s;
    x = BigInteger(s);
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const BigInteger& x) {
    return stream << x.toString();
}
