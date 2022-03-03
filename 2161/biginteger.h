// https://contest.yandex.com/contest/35212/run-report/65710360

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

    static void add(std::vector<int>& a, const std::vector<int>& b) {
        int a_size = a.size(), b_size = b.size(), size = std::min(a_size, b_size);
        long long digit = 0;
        for (int i = 0; i < size; i++) {
            digit += a[i] + b[i];
            a[i] = digit % MOD;
            digit /= MOD;
        }
        for (int i = size; i < a_size && digit > 0; i++) {
            digit += a[i];
            a[i] = digit % MOD;
            digit /= MOD;
        }
        for (int i = size; i < b_size; i++) {
            digit += b[i];
            a.push_back(digit % MOD);
            digit /= MOD;
        }
        if (digit > 0) {
            a.push_back(digit);
        }
    }

    static void invert(std::vector<int>& a) {
        bool overflow = true;
        for (int i = 0, size = a.size(); i < size; i++) {
            a[i] = (MOD - 1 - a[i] + overflow) % MOD;
            if (a[i] > 0) {
                overflow = false;
            }
        }
    }

    static void sub(std::vector<int>& a, const std::vector<int>& b) {
        if (a.size() < b.size()) {
            a.resize(b.size());
        }
        int a_size = a.size(), b_size = b.size();
        long long digit = 0;
        for (int i = 0; i < b_size; i++) {
            digit += MOD + a[i] - b[i];
            a[i] = digit % MOD;
            digit /= MOD;
            digit--;
        }
        for (int i = b_size; i < a_size && digit == -1; i++) {
            digit += MOD + a[i];
            a[i] = digit % MOD;
            digit /= MOD;
            digit--;
        }
        if (digit == -1) {
            invert(a);
        }
        delete_leading_zeros(a);
    }

    static void mult(std::vector<int>& a, int k) {
        long long digit = 0;
        for (int i = 0, size = a.size(); i < size; i++) {
            digit += static_cast<long long>(a[i]) * k;
            a[i] = digit % MOD;
            digit /= MOD;
        }
        if (digit > 0) {
            a.push_back(digit);
        }
    }

    static std::vector<int> mult(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> r;
        for (int i = 0, a_size = a.size(); i < a_size; i++) {
            std::vector<int> t(i);
            t.insert(t.end(), b.begin(), b.end());
            mult(t, a[i]);
            add(r, t);
        }
        return r;
    }

    static std::vector<int> div(const std::vector<int>& a, const std::vector<int>& b, bool remainder = false) {
        std::vector<int> r;
        if (less(a, b)) {
            return remainder ? a : r;
        }
        std::vector<int> t(a.end() - b.size() + 1, a.end());
        for (int i = a.size() - b.size(); i >= 0; i--) {
            t.insert(t.begin(), a[i]);
            int k = 0;
            std::vector<int> c;
            for (int max_k = MOD, mid_k; k + 1 < max_k;) {
                mid_k = (k + max_k) / 2;
                c = b;
                mult(c, mid_k);
                if (less(t, c)) {
                    max_k = mid_k;
                }
                else {
                    k = mid_k;
                }
            }
            c = b;
            mult(c, k);
            r.push_back(k);
            sub(t, c);
        }
        reverse(r);
        return remainder ? t : r;
    }

public:
    BigInteger() = default;

    explicit BigInteger(const std::vector<int>& value_, bool negative_ = false) : value(value_), negative(negative_) {
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
        s += (negative && value.size() > 0 ? "-" : "");
        reverse(s);
        return s;
    }

    bool operator<(const BigInteger& other) const {
        if (negative != other.negative) {
            return negative;
        }
        return (!negative && less(value, other.value)) || (negative && less(other.value, value));
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

    BigInteger& operator+=(const BigInteger& other) {
        if (negative == other.negative) {
            add(value, other.value);
        }
        else {
            negative = less(value, other.value) ? !negative : negative;
            sub(value, other.value);
        }
        return *this;
    }

    BigInteger& operator-=(const BigInteger& other) {
        if (negative == other.negative) {
            negative = less(value, other.value) ? !negative : negative;
            sub(value, other.value);
        }
        else {
            add(value, other.value);
        }
        return *this;
    }

    BigInteger& operator*=(const BigInteger& other) {
        negative = negative != other.negative;
        value = mult(value, other.value);
        return *this;
    }

    BigInteger& operator/=(const BigInteger& other) {
        negative = negative != other.negative;
        value = div(value, other.value);
        return *this;
    }

    BigInteger& operator%=(const BigInteger& other) {
        value = div(value, other.value, true);
        return *this;
    }

    BigInteger& operator++() {
        return *this += 1;
    }

    BigInteger operator++(int) {
        auto result = *this;
        operator++();
        return result;
    }

    BigInteger& operator--() {
        return *this -= 1;
    }

    BigInteger operator--(int) {
        auto result = *this;
        operator--();
        return result;
    }

    BigInteger operator+(const BigInteger& other) const {
        return BigInteger(*this) += other;
    }

    BigInteger operator-(const BigInteger& other) const {
        return BigInteger(*this) -= other;
    }

    BigInteger operator*(const BigInteger& other) const {
        return BigInteger(*this) *= other;
    }

    BigInteger operator/(const BigInteger& other) const {
        return BigInteger(*this) /= other;
    }

    BigInteger operator%(const BigInteger& other) const {
        return BigInteger(*this) %= other;
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

template <class T>
bool operator<(const T& t, const BigInteger& x) {
    return BigInteger(t) < x;
}

template <class T>
bool operator>(const T& t, const BigInteger& x) {
    return BigInteger(t) > x;
}

template <class T>
bool operator==(const T& t, const BigInteger& x) {
    return BigInteger(t) == x;
}

template <class T>
bool operator!=(const T& t, const BigInteger& x) {
    return BigInteger(t) != x;
}

template <class T>
bool operator<=(const T& t, const BigInteger& x) {
    return BigInteger(t) <= x;
}

template <class T>
bool operator>=(const T& t, const BigInteger& x) {
    return BigInteger(t) >= x;
}

template <class T>
BigInteger operator+(const T& t, const BigInteger& x) {
    return BigInteger(t) + x;
}

template <class T>
BigInteger operator-(const T& t, const BigInteger& x) {
    return BigInteger(t) - x;
}

template <class T>
BigInteger operator*(const T& t, const BigInteger& x) {
    return BigInteger(t) * x;
}

template <class T>
BigInteger operator/(const T& t, const BigInteger& x) {
    return BigInteger(t) / x;
}

template <class T>
BigInteger operator%(const T& t, const BigInteger& x) {
    return BigIntger(t) % x;
}
