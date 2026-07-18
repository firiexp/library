#ifndef FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP
#define FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP

#include "../math/integer_convolution.cpp"

namespace BigIntegerDetail {
    using u32 = unsigned int;
    using u64 = unsigned long long;
    using u128 = __uint128_t;

    struct DecimalRadix {
        static constexpr u64 BASE = 10000000000000000ULL;
        static constexpr int IO_BASE = 10;
        static constexpr int BLOCK_DIGITS = 16;
        static constexpr u32 META_BASE = 10000u;
        static constexpr int META_DIGITS = 4;
    };

    struct HexRadix {
        static constexpr u64 BASE = 1ULL << 60;
        static constexpr int IO_BASE = 16;
        static constexpr int BLOCK_DIGITS = 15;
        static constexpr u32 META_BASE = 1u << 15;
        static constexpr int META_DIGITS = 4;
    };
}

template<class Radix>
class BasicBigInteger {
    using u32 = BigIntegerDetail::u32;
    using u64 = BigIntegerDetail::u64;
    using u128 = BigIntegerDetail::u128;

    static constexpr u64 BASE = Radix::BASE;
    static constexpr int IO_BASE = Radix::IO_BASE;
    static constexpr int BLOCK_DIGITS = Radix::BLOCK_DIGITS;
    static constexpr u32 META_BASE = Radix::META_BASE;
    static constexpr int META_DIGITS = Radix::META_DIGITS;
    static constexpr int SCHOOLBOOK_MIN_THRESHOLD = 32;
    static constexpr long long SCHOOLBOOK_AREA_THRESHOLD = 4096;

    vector<u64> digits;
    bool negative;

    static int digit_value(char c) {
        if ('0' <= c && c <= '9') return c - '0';
        if ('a' <= c && c <= 'z') return c - 'a' + 10;
        if ('A' <= c && c <= 'Z') return c - 'A' + 10;
        return -1;
    }

    static char digit_char(int x) {
        return x < 10 ? char('0' + x) : char('a' + x - 10);
    }

    void normalize() {
        while (!digits.empty() && digits.back() == 0) digits.pop_back();
        if (digits.empty()) negative = false;
    }

    static int compare_abs(const BasicBigInteger &a, const BasicBigInteger &b) {
        if (a.digits.size() != b.digits.size()) {
            return a.digits.size() < b.digits.size() ? -1 : 1;
        }
        for (int i = (int)a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i] ? -1 : 1;
        }
        return 0;
    }

    static int compare(const BasicBigInteger &a, const BasicBigInteger &b) {
        if (a.negative != b.negative) return a.negative ? -1 : 1;
        int cmp = compare_abs(a, b);
        return a.negative ? -cmp : cmp;
    }

    void add_abs(const BasicBigInteger &other) {
        if (digits.size() < other.digits.size()) digits.resize(other.digits.size(), 0);
        u64 carry = 0;
        size_t i = 0;
        for (; i < other.digits.size(); ++i) {
            u128 cur = u128(digits[i]) + other.digits[i] + carry;
            if (cur >= BASE) {
                digits[i] = u64(cur - BASE);
                carry = 1;
            } else {
                digits[i] = u64(cur);
                carry = 0;
            }
        }
        for (; i < digits.size() && carry; ++i) {
            if (++digits[i] == BASE) digits[i] = 0;
            else carry = 0;
        }
        if (carry) digits.push_back(1);
    }

    void sub_abs(const BasicBigInteger &other) {
        u64 borrow = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            u128 rhs = borrow;
            if (i < other.digits.size()) rhs += other.digits[i];
            if (u128(digits[i]) < rhs) {
                digits[i] = u64(u128(digits[i]) + BASE - rhs);
                borrow = 1;
            } else {
                digits[i] = u64(u128(digits[i]) - rhs);
                borrow = 0;
            }
        }
        normalize();
    }

    void add_small_abs(u64 value) {
        assert(value < BASE);
        if (value == 0) return;
        if (digits.empty()) {
            digits.push_back(value);
            return;
        }
        u128 cur = u128(digits[0]) + value;
        digits[0] = u64(cur % BASE);
        u64 carry = u64(cur / BASE);
        for (size_t i = 1; i < digits.size() && carry; ++i) {
            if (++digits[i] == BASE) digits[i] = 0;
            else carry = 0;
        }
        if (carry) digits.push_back(carry);
    }

    void mul_small_abs(u64 value) {
        assert(value < BASE);
        if (digits.empty() || value == 1) return;
        if (value == 0) {
            digits.clear();
            negative = false;
            return;
        }
        u64 carry = 0;
        for (u64 &digit : digits) {
            u128 cur = u128(digit) * value + carry;
            digit = u64(cur % BASE);
            carry = u64(cur / BASE);
        }
        if (carry) digits.push_back(carry);
    }

    u64 div_small_abs(u64 value) {
        assert(value != 0 && value < BASE);
        u64 remainder = 0;
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            u128 cur = u128(remainder) * BASE + digits[i];
            digits[i] = u64(cur / value);
            remainder = u64(cur % value);
        }
        normalize();
        return remainder;
    }

    static vector<u64> mul_small_digits(const vector<u64> &src, u64 value) {
        if (src.empty() || value == 0) return {};
        vector<u64> res;
        res.reserve(src.size() + 1);
        u64 carry = 0;
        for (u64 digit : src) {
            u128 cur = u128(digit) * value + carry;
            res.push_back(u64(cur % BASE));
            carry = u64(cur / BASE);
        }
        if (carry) res.push_back(carry);
        return res;
    }

    static u64 div_small_digits(vector<u64> &src, u64 value) {
        u64 remainder = 0;
        for (int i = (int)src.size() - 1; i >= 0; --i) {
            u128 cur = u128(remainder) * BASE + src[i];
            src[i] = u64(cur / value);
            remainder = u64(cur % value);
        }
        while (!src.empty() && src.back() == 0) src.pop_back();
        return remainder;
    }

    static vector<u64> mul_schoolbook_digits(const vector<u64> &a, const vector<u64> &b) {
        if (a.empty() || b.empty()) return {};
        vector<u64> res(a.size() + b.size(), 0);
        for (size_t i = 0; i < a.size(); ++i) {
            u64 carry = 0;
            for (size_t j = 0; j < b.size(); ++j) {
                u128 cur = u128(a[i]) * b[j] + res[i + j] + carry;
                res[i + j] = u64(cur % BASE);
                carry = u64(cur / BASE);
            }
            size_t pos = i + b.size();
            while (carry) {
                u128 cur = u128(res[pos]) + carry;
                res[pos] = u64(cur % BASE);
                carry = u64(cur / BASE);
                ++pos;
            }
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    static vector<u32> to_meta_digits(const vector<u64> &src) {
        vector<u32> res(src.size() * META_DIGITS);
        for (size_t i = 0; i < src.size(); ++i) {
            u64 value = src[i];
            for (int j = 0; j < META_DIGITS; ++j) {
                res[i * META_DIGITS + j] = u32(value % META_BASE);
                value /= META_BASE;
            }
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    static vector<u64> from_meta_digits(const vector<u32> &src) {
        vector<u64> res;
        res.reserve((src.size() + META_DIGITS - 1) / META_DIGITS);
        for (size_t i = 0; i < src.size(); i += META_DIGITS) {
            u128 value = 0;
            for (int j = META_DIGITS - 1; j >= 0; --j) {
                value *= META_BASE;
                size_t index = i + (size_t)j;
                if (index < src.size()) value += src[index];
            }
            res.push_back(u64(value));
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    static vector<u64> mul_convolution_digits(const vector<u64> &a, const vector<u64> &b) {
        vector<u32> x = to_meta_digits(a);
        vector<u32> y = to_meta_digits(b);
        vector<u64> convolution;
        if (a == b) convolution = BoundedConvolution::square_u64(x);
        else convolution = BoundedConvolution::convolution_u64(x, y);

        vector<u32> meta;
        meta.reserve(convolution.size() + 4);
        u128 carry = 0;
        for (u64 value : convolution) {
            u128 cur = value + carry;
            meta.push_back(u32(cur % META_BASE));
            carry = cur / META_BASE;
        }
        while (carry) {
            meta.push_back(u32(carry % META_BASE));
            carry /= META_BASE;
        }
        while (!meta.empty() && meta.back() == 0) meta.pop_back();
        return from_meta_digits(meta);
    }

    static BasicBigInteger multiply_abs(const BasicBigInteger &a, const BasicBigInteger &b) {
        BasicBigInteger res;
        if (a.is_zero() || b.is_zero()) return res;
        if (a.digits.size() == 1) {
            res = b.abs();
            res.mul_small_abs(a.digits[0]);
            return res;
        }
        if (b.digits.size() == 1) {
            res = a.abs();
            res.mul_small_abs(b.digits[0]);
            return res;
        }
        long long area = (long long)a.digits.size() * (long long)b.digits.size();
        if ((int)min(a.digits.size(), b.digits.size()) <= SCHOOLBOOK_MIN_THRESHOLD ||
            area <= SCHOOLBOOK_AREA_THRESHOLD) {
            res.digits = mul_schoolbook_digits(a.digits, b.digits);
        } else {
            res.digits = mul_convolution_digits(a.digits, b.digits);
        }
        return res;
    }

    void pad_inplace(size_t count) {
        if (!digits.empty() && count) digits.insert(digits.begin(), count, 0);
    }

    BasicBigInteger pad(size_t count) const {
        BasicBigInteger res = *this;
        res.pad_inplace(count);
        return res;
    }

    void drop_inplace(size_t count) {
        if (count >= digits.size()) {
            digits.clear();
            negative = false;
            return;
        }
        digits.erase(digits.begin(), digits.begin() + (int)count);
        normalize();
    }

    BasicBigInteger top(size_t count) const {
        BasicBigInteger res = *this;
        if (count >= res.digits.size()) res.pad_inplace(count - res.digits.size());
        else res.drop_inplace(res.digits.size() - count);
        return res;
    }

    static BasicBigInteger divmod_knuth_abs(const BasicBigInteger &a,
                                             const BasicBigInteger &b,
                                             BasicBigInteger &remainder) {
        assert(!b.is_zero());
        if (compare_abs(a, b) < 0) {
            remainder = a;
            return BasicBigInteger();
        }
        if (b.digits.size() == 1) {
            BasicBigInteger quotient = a;
            u64 rem = quotient.div_small_abs(b.digits[0]);
            remainder = BasicBigInteger((long long)rem);
            return quotient;
        }

        u64 norm = BASE / (b.digits.back() + 1);
        vector<u64> un = norm == 1 ? a.digits : mul_small_digits(a.digits, norm);
        vector<u64> vn = norm == 1 ? b.digits : mul_small_digits(b.digits, norm);
        size_t n = vn.size();
        size_t m = un.size() - n;
        un.push_back(0);

        BasicBigInteger quotient;
        quotient.digits.assign(m + 1, 0);
        for (size_t jj = m + 1; jj-- > 0;) {
            size_t j = jj;
            u128 numerator = u128(un[j + n]) * BASE + un[j + n - 1];
            u128 qhat = numerator / vn[n - 1];
            u128 rhat = numerator % vn[n - 1];
            if (qhat == BASE) {
                --qhat;
                rhat += vn[n - 1];
            }
            if (n >= 2) {
                while (rhat < BASE &&
                       qhat * vn[n - 2] > rhat * BASE + un[j + n - 2]) {
                    --qhat;
                    rhat += vn[n - 1];
                }
            }

            u64 carry = 0;
            u64 borrow = 0;
            for (size_t i = 0; i < n; ++i) {
                u128 product = qhat * vn[i] + carry;
                carry = u64(product / BASE);
                u128 sub = product % BASE + borrow;
                if (u128(un[j + i]) < sub) {
                    un[j + i] = u64(u128(un[j + i]) + BASE - sub);
                    borrow = 1;
                } else {
                    un[j + i] = u64(u128(un[j + i]) - sub);
                    borrow = 0;
                }
            }

            u128 sub = u128(carry) + borrow;
            bool underflow = u128(un[j + n]) < sub;
            if (underflow) un[j + n] = u64(u128(un[j + n]) + BASE - sub);
            else un[j + n] = u64(u128(un[j + n]) - sub);

            if (underflow) {
                --qhat;
                u64 add_carry = 0;
                for (size_t i = 0; i < n; ++i) {
                    u128 cur = u128(un[j + i]) + vn[i] + add_carry;
                    if (cur >= BASE) {
                        un[j + i] = u64(cur - BASE);
                        add_carry = 1;
                    } else {
                        un[j + i] = u64(cur);
                        add_carry = 0;
                    }
                }
                un[j + n] = u64(u128(un[j + n]) + add_carry);
            }
            quotient.digits[j] = u64(qhat);
        }

        quotient.normalize();
        remainder.digits.assign(un.begin(), un.begin() + n);
        if (norm != 1) div_small_digits(remainder.digits, norm);
        remainder.normalize();
        return quotient;
    }

    struct Scaled {
        BasicBigInteger value;
        long long scale;

        Scaled(long long value_ = 0, long long scale_ = 0) : value(value_), scale(scale_) {}
        Scaled(BasicBigInteger value_, long long scale_ = 0)
            : value(std::move(value_)), scale(scale_) {}

        Scaled &operator*=(const Scaled &other) {
            value *= other.value;
            scale += other.scale;
            return *this;
        }

        Scaled &operator+=(const Scaled &other) {
            if (scale < other.scale) {
                value += other.value.pad((size_t)(other.scale - scale));
            } else {
                value.pad_inplace((size_t)(scale - other.scale));
                value += other.value;
                scale = other.scale;
            }
            return *this;
        }

        Scaled &operator-=(const Scaled &other) {
            if (scale < other.scale) {
                value -= other.value.pad((size_t)(other.scale - scale));
            } else {
                value.pad_inplace((size_t)(scale - other.scale));
                value -= other.value;
                scale = other.scale;
            }
            return *this;
        }

        friend Scaled operator*(Scaled lhs, const Scaled &rhs) { return lhs *= rhs; }
        friend Scaled operator+(Scaled lhs, const Scaled &rhs) { return lhs += rhs; }
        friend Scaled operator-(Scaled lhs, const Scaled &rhs) { return lhs -= rhs; }

        BasicBigInteger round() const {
            if (scale >= 0) return value.pad((size_t)scale);
            if (-scale > (long long)value.digits.size()) return BasicBigInteger();
            BasicBigInteger res = value.top(value.digits.size() - (size_t)(-scale));
            if (value.digits[(size_t)(-scale - 1)] * 2 >= BASE) res += 1;
            return res;
        }

        Scaled trunc(size_t count) const {
            count = min(count, value.digits.size());
            return Scaled(value.top(count), scale + (long long)value.digits.size() - (long long)count);
        }

        long long magnitude() const {
            static constexpr long long NEG_INF = -(1LL << 60);
            if (value.is_zero()) return NEG_INF;
            return (long long)value.digits.size() + scale;
        }

        Scaled inv(long long precision) const {
            assert(precision >= 0 && !value.is_zero());
            long double estimate = (long double)BASE / (long double)value.digits.back();
            long long lead = (long long)(estimate + 0.5L);
            Scaled result(BasicBigInteger(lead), -(long long)value.digits.size());
            size_t current = 2;
            Scaled amend = Scaled(1) - trunc(current) * result;
            while (-amend.magnitude() < precision) {
                result += result * amend;
                current = 2 * (size_t)(1 - amend.magnitude());
                result = result.trunc(current);
                amend = Scaled(1) - trunc(current) * result;
            }
            return result;
        }
    };

    static bool divmod_reciprocal_abs(const BasicBigInteger &a,
                                       const BasicBigInteger &b,
                                       BasicBigInteger &quotient,
                                       BasicBigInteger &remainder) {
        Scaled A(a);
        Scaled B(b);
        long long precision = A.magnitude() - B.magnitude() + 1;
        if (precision < 0) precision = 0;
        quotient = (A * B.inv(precision)).round();
        remainder = a - quotient * b;

        int correction = 0;
        while (remainder.is_negative()) {
            if (++correction > 8) return false;
            quotient -= 1;
            remainder += b;
        }
        while (remainder >= b) {
            if (++correction > 8) return false;
            quotient += 1;
            remainder -= b;
        }
        return !quotient.is_negative() && !remainder.is_negative() && remainder < b;
    }

    static pair<BasicBigInteger, BasicBigInteger> divmod_abs(const BasicBigInteger &a,
                                                              const BasicBigInteger &b) {
        assert(!b.is_zero());
        if (compare_abs(a, b) < 0) return {BasicBigInteger(), a};
        if (b.digits.size() == 1) {
            BasicBigInteger quotient = a;
            u64 remainder = quotient.div_small_abs(b.digits[0]);
            return {quotient, BasicBigInteger((long long)remainder)};
        }

        size_t quotient_size = a.digits.size() - b.digits.size() + 1;
        if (b.digits.size() >= 4 && quotient_size >= 3) {
            BasicBigInteger quotient, remainder;
            if (divmod_reciprocal_abs(a, b, quotient, remainder)) {
                return {std::move(quotient), std::move(remainder)};
            }
        }
        BasicBigInteger remainder;
        BasicBigInteger quotient = divmod_knuth_abs(a, b, remainder);
        return {std::move(quotient), std::move(remainder)};
    }

    static pair<int, u64> shift_chunk() {
        int bits = 0;
        u64 value = 1;
        while (bits < 62 && value <= (BASE - 1) / 2) {
            value *= 2;
            ++bits;
        }
        return {bits, value};
    }

    static void append_in_base(string &out, u64 value, int base, int width) {
        char buffer[70];
        int pos = 70;
        do {
            buffer[--pos] = digit_char((int)(value % (u64)base));
            value /= (u64)base;
        } while (value);
        int length = 70 - pos;
        while (length < width) {
            out.push_back('0');
            ++length;
        }
        out.append(buffer + pos, buffer + 70);
    }

public:
    BasicBigInteger() : digits(), negative(false) {}

    BasicBigInteger(long long value) : digits(), negative(false) {
        *this = value;
    }

    BasicBigInteger(const string &value, int base = IO_BASE) : digits(), negative(false) {
        bool ok = assign(value, base);
        assert(ok);
        (void)ok;
    }

    BasicBigInteger &operator=(long long value) {
        digits.clear();
        negative = value < 0;
        u64 magnitude = value < 0 ? u64(-(value + 1)) + 1 : u64(value);
        while (magnitude) {
            digits.push_back(magnitude % BASE);
            magnitude /= BASE;
        }
        normalize();
        return *this;
    }

    bool assign(const string &value, int base = IO_BASE) {
        digits.clear();
        negative = false;
        if (base < 2 || base > 36 || value.empty()) return false;

        int begin = 0;
        bool is_negative = false;
        if (value[begin] == '+' || value[begin] == '-') {
            is_negative = value[begin] == '-';
            if (++begin == (int)value.size()) return false;
        }
        for (int i = begin; i < (int)value.size(); ++i) {
            int digit = digit_value(value[i]);
            if (digit < 0 || digit >= base) {
                digits.clear();
                negative = false;
                return false;
            }
        }
        while (begin < (int)value.size() && value[begin] == '0') ++begin;
        if (begin == (int)value.size()) return true;

        if (base == IO_BASE) {
            for (int right = (int)value.size(); right > begin; right -= BLOCK_DIGITS) {
                int left = max(begin, right - BLOCK_DIGITS);
                u64 block = 0;
                for (int i = left; i < right; ++i) {
                    block = block * (u64)base + (u64)digit_value(value[i]);
                }
                digits.push_back(block);
            }
        } else {
            u64 chunk_base = 1;
            int chunk_digits = 0;
            while (chunk_base <= (BASE - 1) / (u64)base) {
                chunk_base *= (u64)base;
                ++chunk_digits;
            }
            int first = ((int)value.size() - begin) % chunk_digits;
            if (first == 0) first = chunk_digits;
            for (int pos = begin; pos < (int)value.size();) {
                int width = pos == begin ? first : chunk_digits;
                u64 block = 0;
                u64 power = 1;
                for (int i = 0; i < width; ++i) {
                    block = block * (u64)base + (u64)digit_value(value[pos + i]);
                    power *= (u64)base;
                }
                mul_small_abs(power);
                add_small_abs(block);
                pos += width;
            }
        }
        negative = is_negative;
        normalize();
        return true;
    }

    string to_string(int base = IO_BASE) const {
        assert(2 <= base && base <= 36);
        if (is_zero()) return "0";
        string out;
        if (negative) out.push_back('-');

        if (base == IO_BASE) {
            append_in_base(out, digits.back(), base, 0);
            for (int i = (int)digits.size() - 2; i >= 0; --i) {
                append_in_base(out, digits[i], base, BLOCK_DIGITS);
            }
            return out;
        }

        u64 chunk_base = 1;
        int chunk_digits = 0;
        while (chunk_base <= (BASE - 1) / (u64)base) {
            chunk_base *= (u64)base;
            ++chunk_digits;
        }
        BasicBigInteger value = abs();
        vector<u64> parts;
        while (!value.is_zero()) parts.push_back(value.div_small_abs(chunk_base));
        append_in_base(out, parts.back(), base, 0);
        for (int i = (int)parts.size() - 2; i >= 0; --i) {
            append_in_base(out, parts[i], base, chunk_digits);
        }
        return out;
    }

    bool is_zero() const { return digits.empty(); }
    bool is_negative() const { return negative; }

    BasicBigInteger abs() const {
        BasicBigInteger res = *this;
        res.negative = false;
        return res;
    }

    BasicBigInteger operator+() const { return *this; }

    BasicBigInteger operator-() const {
        BasicBigInteger res = *this;
        if (!res.is_zero()) res.negative = !res.negative;
        return res;
    }

    BasicBigInteger &operator+=(const BasicBigInteger &other) {
        if (other.is_zero()) return *this;
        if (is_zero()) {
            *this = other;
            return *this;
        }
        if (negative == other.negative) {
            add_abs(other);
            return *this;
        }
        int cmp = compare_abs(*this, other);
        if (cmp == 0) {
            digits.clear();
            negative = false;
        } else if (cmp > 0) {
            sub_abs(other);
        } else {
            BasicBigInteger res = other;
            res.sub_abs(*this);
            *this = std::move(res);
        }
        return *this;
    }

    BasicBigInteger &operator-=(const BasicBigInteger &other) {
        return *this += -other;
    }

    BasicBigInteger &operator*=(const BasicBigInteger &other) {
        if (is_zero() || other.is_zero()) {
            digits.clear();
            negative = false;
            return *this;
        }
        bool result_negative = negative != other.negative;
        BasicBigInteger result = multiply_abs(*this, other);
        result.negative = result_negative;
        *this = std::move(result);
        return *this;
    }

    friend BasicBigInteger operator+(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs += rhs; }
    friend BasicBigInteger operator-(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs -= rhs; }
    friend BasicBigInteger operator*(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs *= rhs; }

    friend bool operator==(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) == 0; }
    friend bool operator!=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) != 0; }
    friend bool operator<(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) < 0; }
    friend bool operator<=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) <= 0; }
    friend bool operator>(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) > 0; }
    friend bool operator>=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) >= 0; }

    static pair<BasicBigInteger, BasicBigInteger> divmod(const BasicBigInteger &a,
                                                         const BasicBigInteger &b) {
        assert(!b.is_zero());
        auto result = divmod_abs(a.abs(), b.abs());
        if (!result.first.is_zero()) result.first.negative = a.negative != b.negative;
        if (!result.second.is_zero()) result.second.negative = a.negative;
        return result;
    }

    static pair<BasicBigInteger, BasicBigInteger> floor_divmod(const BasicBigInteger &a,
                                                               const BasicBigInteger &b) {
        auto result = divmod(a, b);
        if (!result.second.is_zero() && a.negative != b.negative) {
            result.first -= 1;
            result.second += b;
        }
        return result;
    }

    friend pair<BasicBigInteger, BasicBigInteger> divmod(const BasicBigInteger &a,
                                                         const BasicBigInteger &b) {
        return BasicBigInteger::divmod(a, b);
    }

    friend pair<BasicBigInteger, BasicBigInteger> floor_divmod(const BasicBigInteger &a,
                                                               const BasicBigInteger &b) {
        return BasicBigInteger::floor_divmod(a, b);
    }

    BasicBigInteger &operator/=(const BasicBigInteger &other) {
        *this = divmod(*this, other).first;
        return *this;
    }

    BasicBigInteger &operator%=(const BasicBigInteger &other) {
        *this = divmod(*this, other).second;
        return *this;
    }

    BasicBigInteger &operator<<=(int bits) {
        assert(bits >= 0);
        if (is_zero() || bits == 0) return *this;
        auto chunk = shift_chunk();
        while (bits) {
            int take = min(bits, chunk.first);
            mul_small_abs(1ULL << take);
            bits -= take;
        }
        return *this;
    }

    BasicBigInteger &operator>>=(int bits) {
        assert(bits >= 0);
        if (is_zero() || bits == 0) return *this;
        bool was_negative = negative;
        bool discarded = false;
        auto chunk = shift_chunk();
        while (bits && !is_zero()) {
            int take = min(bits, chunk.first);
            discarded |= div_small_abs(1ULL << take) != 0;
            bits -= take;
        }
        if (was_negative && discarded) {
            add_small_abs(1);
            negative = true;
        }
        normalize();
        return *this;
    }

    friend BasicBigInteger operator/(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs /= rhs; }
    friend BasicBigInteger operator%(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs %= rhs; }
    friend BasicBigInteger operator<<(BasicBigInteger lhs, int bits) { return lhs <<= bits; }
    friend BasicBigInteger operator>>(BasicBigInteger lhs, int bits) { return lhs >>= bits; }
};

using BigInteger = BasicBigInteger<BigIntegerDetail::DecimalRadix>;
using HexBigInteger = BasicBigInteger<BigIntegerDetail::HexRadix>;

#endif

/**
 * @brief 多倍長整数(BigInteger)
 */
