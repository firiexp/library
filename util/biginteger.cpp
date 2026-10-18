#ifndef FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP
#define FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP

#include "../math/integer_convolution.cpp"

namespace BigIntegerDetail {
    using u32 = unsigned int;
    using u64 = unsigned long long;

    struct DecimalRadix {
        static constexpr u64 BASE = 100000000;
        static constexpr u32 META_BASE = 10000;
        static constexpr int IO_BASE = 10;
        static constexpr int BLOCK_DIGITS = 8;
    };

    struct HexRadix {
        static constexpr u64 BASE = 1ULL << 32;
        static constexpr u32 META_BASE = 1u << 16;
        static constexpr int IO_BASE = 16;
        static constexpr int BLOCK_DIGITS = 8;
    };

    template<class Radix>
    struct Magnitude {
        using Digits = vector<u32>;
        static constexpr u64 BASE = Radix::BASE;
        static constexpr u32 META_BASE = Radix::META_BASE;
        static constexpr size_t SCHOOLBOOK_MIN = 32;
        static constexpr u64 SCHOOLBOOK_AREA = 16384;
        static constexpr size_t KARATSUBA_LIMIT = Radix::IO_BASE == 10 ? 192 : 768;
        static constexpr size_t DIVISION_MIN = 64;
        static constexpr u64 DIVISION_AREA = 16384;
        static constexpr size_t DIVIDE_CONQUER_MAX = 4096;
        static constexpr size_t CYCLIC_MIN = 4096;

        static void trim(Digits &a) {
            while (!a.empty() && a.back() == 0) a.pop_back();
        }

        static int compare(const Digits &a, const Digits &b) {
            if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
            for (size_t i = a.size(); i-- > 0;) {
                if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
            }
            return 0;
        }

        static void add(Digits &a, const Digits &b) {
            if (a.size() < b.size()) a.resize(b.size());
            u64 carry = 0;
            size_t i = 0;
            for (; i < b.size(); ++i) {
                u64 value = u64(a[i]) + b[i] + carry;
                carry = value >= BASE;
                a[i] = u32(value - carry * BASE);
            }
            for (; carry && i < a.size(); ++i) {
                u64 value = u64(a[i]) + carry;
                carry = value >= BASE;
                a[i] = u32(value - carry * BASE);
            }
            if (carry) a.push_back(1);
        }

        static void subtract(Digits &a, const Digits &b) {
            u64 borrow = 0;
            size_t i = 0;
            for (; i < b.size(); ++i) {
                u64 value = u64(b[i]) + borrow;
                borrow = a[i] < value;
                a[i] = u32(u64(a[i]) + borrow * BASE - value);
            }
            for (; borrow && i < a.size(); ++i) {
                borrow = a[i] == 0;
                a[i] = u32(u64(a[i]) + borrow * BASE - 1);
            }
            assert(!borrow);
            trim(a);
        }

        static void increment(Digits &a) {
            size_t i = 0;
            while (i < a.size() && u64(a[i]) + 1 == BASE) a[i++] = 0;
            if (i == a.size()) a.push_back(1);
            else ++a[i];
        }

        static void decrement(Digits &a) {
            size_t i = 0;
            while (a[i] == 0) a[i++] = u32(BASE - 1);
            --a[i];
            trim(a);
        }

        static void multiply_small(Digits &a, u32 b) {
            if (b == 0) { a.clear(); return; }
            if (b == 1) return;
            u64 carry = 0;
            for (u32 &digit : a) {
                u64 value = u64(digit) * b + carry;
                digit = u32(value % BASE);
                carry = value / BASE;
            }
            while (carry) {
                a.push_back(u32(carry % BASE));
                carry /= BASE;
            }
        }

        static u32 divide_small(Digits &a, u32 b) {
            assert(b);
            u64 remainder = 0;
            for (size_t i = a.size(); i-- > 0;) {
                u64 value = remainder * BASE + a[i];
                a[i] = u32(value / b);
                remainder = value % b;
            }
            trim(a);
            return u32(remainder);
        }

        static Digits high(const Digits &a, size_t drop) {
            if (drop >= a.size()) return {};
            return Digits(a.begin() + drop, a.end());
        }

        static Digits schoolbook(const Digits &a, const Digits &b) {
            Digits result(a.size() + b.size());
            for (size_t i = 0; i < a.size(); ++i) {
                u64 carry = 0;
                for (size_t j = 0; j < b.size(); ++j) {
                    u64 value = u64(a[i]) * b[j] + result[i + j] + carry;
                    result[i + j] = u32(value % BASE);
                    carry = value / BASE;
                }
                result[i + b.size()] = u32(carry);
            }
            trim(result);
            return result;
        }

        static Digits split(const Digits &a) {
            Digits result(2 * a.size());
            for (size_t i = 0; i < a.size(); ++i) {
                result[2 * i] = a[i] % META_BASE;
                result[2 * i + 1] = a[i] / META_BASE;
            }
            trim(result);
            return result;
        }

        static void add_shifted(Digits &a, const Digits &b, size_t shift) {
            if (a.size() < b.size() + shift) a.resize(b.size() + shift);
            u64 carry = 0;
            size_t i = 0;
            for (; i < b.size(); ++i) {
                u64 value = u64(a[i + shift]) + b[i] + carry;
                carry = value >= BASE;
                a[i + shift] = u32(value - carry * BASE);
            }
            for (; carry && i + shift < a.size(); ++i) {
                u64 value = u64(a[i + shift]) + carry;
                carry = value >= BASE;
                a[i + shift] = u32(value - carry * BASE);
            }
            if (carry) a.push_back(1);
        }

        static Digits karatsuba(const Digits &a, const Digits &b) {
            size_t k = max(a.size(), b.size()) / 2;
            Digits a0(a.begin(), a.begin() + min(k, a.size()));
            Digits b0(b.begin(), b.begin() + min(k, b.size()));
            Digits a1 = high(a, k), b1 = high(b, k);
            trim(a0);
            trim(b0);
            Digits z0 = multiply(a0, b0), z2 = multiply(a1, b1);
            add(a0, a1);
            add(b0, b1);
            Digits z1 = multiply(a0, b0);
            subtract(z1, z0);
            subtract(z1, z2);
            add_shifted(z0, z1, k);
            add_shifted(z0, z2, 2 * k);
            trim(z0);
            return z0;
        }

        static Digits multiply(const Digits &a, const Digits &b) {
            if (a.empty() || b.empty()) return {};
            if (min(a.size(), b.size()) == 1) {
                Digits result = a.size() == 1 ? b : a;
                multiply_small(result, a.size() == 1 ? a[0] : b[0]);
                return result;
            }
            if (min(a.size(), b.size()) <= SCHOOLBOOK_MIN || u64(a.size()) * b.size() <= SCHOOLBOOK_AREA) {
                return a.size() < b.size() ? schoolbook(a, b) : schoolbook(b, a);
            }
            if (min(a.size(), b.size()) <= KARATSUBA_LIMIT && max(a.size(), b.size()) <= 2 * min(a.size(), b.size())) return karatsuba(a, b);
            Digits x = split(a);
            vector<u64> product;
            if (&a == &b || a == b) product = BoundedConvolution::square_u64(x);
            else product = BoundedConvolution::convolution_u64(x, split(b));
            Digits result;
            result.reserve(a.size() + b.size());
            u64 carry = 0;
            for (size_t i = 0; i < product.size(); i += 2) {
                u64 value = product[i] + carry;
                u32 low = u32(value % META_BASE);
                carry = value / META_BASE;
                if (i + 1 < product.size()) carry += product[i + 1];
                result.push_back(low + u32(carry % META_BASE) * META_BASE);
                carry /= META_BASE;
            }
            while (carry) {
                result.push_back(u32(carry % BASE));
                carry /= BASE;
            }
            trim(result);
            return result;
        }

        static pair<Digits, Digits> knuth(Digits a, const Digits &b) {
            assert(b.size() >= 2 && b.back() >= BASE / 2);
            if (compare(a, b) < 0) return {{}, std::move(a)};
            size_t n = b.size(), count = a.size() - n + 1;
            Digits quotient(count);
            a.push_back(0);
            for (size_t j = count; j-- > 0;) {
                u64 numerator = u64(a[j + n]) * BASE + a[j + n - 1];
                u64 q = numerator / b.back(), r = numerator % b.back();
                if (q >= BASE) { q = BASE - 1; r = numerator - q * b.back(); }
                while (r < BASE && q * b[n - 2] > r * BASE + a[j + n - 2]) {
                    --q;
                    r += b.back();
                }
                u64 carry = 0;
                for (size_t i = 0; i < n; ++i) {
                    u64 product = q * b[i] + carry;
                    u64 low = product % BASE;
                    carry = product / BASE;
                    if (a[j + i] < low) { a[j + i] = u32(u64(a[j + i]) + BASE - low); ++carry; }
                    else a[j + i] -= u32(low);
                }
                bool underflow = a[j + n] < carry;
                a[j + n] = u32(u64(a[j + n]) + (underflow ? BASE : 0) - carry);
                if (underflow) {
                    --q;
                    u64 c = 0;
                    for (size_t i = 0; i < n; ++i) {
                        u64 value = u64(a[j + i]) + b[i] + c;
                        c = value >= BASE;
                        a[j + i] = u32(value - c * BASE);
                    }
                    a[j + n] = u32((u64(a[j + n]) + c) % BASE);
                }
                quotient[j] = u32(q);
            }
            a.resize(n);
            trim(a);
            trim(quotient);
            return {std::move(quotient), std::move(a)};
        }

        template<class Transform>
        static vector<u32> cyclic_convolution(const Digits &a, const Digits &b,
                                               size_t size, const Transform &transform) {
            using mint = typename Transform::mint;
            vector<mint> x(size), y(size);
            for (size_t i = 0; i < a.size(); ++i) x[i] = mint::raw(a[i]);
            for (size_t i = 0; i < b.size(); ++i) y[i] = mint::raw(b[i]);
            transform.ntt(x, false);
            transform.ntt(y, false);
            for (size_t i = 0; i < size; ++i) x[i] *= y[i];
            transform.ntt(x, true);
            mint scale = transform.inv_size(size);
            vector<u32> result(size);
            for (size_t i = 0; i < size; ++i) result[i] = (x[i] * scale).val;
            return result;
        }

        static void cyclic_normalize(Digits &a, size_t size) {
            if (a.size() > size) {
                Digits extra = high(a, size);
                a.resize(size);
                add(a, extra);
                if (a.size() > size) {
                    a.resize(size);
                    increment(a);
                }
            }
            if (a.size() == size && all_of(a.begin(), a.end(), [](u32 x) { return x == BASE - 1; })) a.clear();
            trim(a);
        }

        static Digits cyclic_product(const Digits &a, const Digits &b, size_t size) {
            assert(a.size() <= size && b.size() <= size);
            Digits x = split(a), y = split(b);
            auto c1 = cyclic_convolution(x, y, 2 * size, BoundedConvolution::internal::ntt1());
            auto c2 = cyclic_convolution(x, y, 2 * size, BoundedConvolution::internal::ntt2());
            Digits result(size);
            u64 carry = 0;
            for (size_t i = 0; i < size; ++i) {
                u64 value = BoundedConvolution::internal::combine_u64(c1[2 * i], c2[2 * i]) + carry;
                u32 low = u32(value % META_BASE);
                carry = value / META_BASE + BoundedConvolution::internal::combine_u64(c1[2 * i + 1], c2[2 * i + 1]);
                result[i] = low + u32(carry % META_BASE) * META_BASE;
                carry /= META_BASE;
            }
            while (carry) {
                result.push_back(u32(carry % BASE));
                carry /= BASE;
            }
            cyclic_normalize(result, size);
            return result;
        }

        static Digits cyclic_difference(Digits a, const Digits &b, size_t size) {
            if (a.size() > size) {
                Digits top = high(a, size);
                a.resize(size);
                add(a, top);
            }
            cyclic_normalize(a, size);
            if (compare(a, b) >= 0) subtract(a, b);
            else {
                Digits modulus(size, u32(BASE - 1));
                subtract(modulus, b);
                add(a, modulus);
            }
            return a;
        }

        static pair<Digits, Digits> divide_three_two(const Digits &a, const Digits &b, size_t k) {
            Digits a12 = high(a, k), a2 = high(a, 2 * k), b1 = high(b, k);
            Digits quotient, remainder;
            if (compare(a2, b1) < 0) {
                auto qr = divide_two_one(a12, b1);
                quotient = std::move(qr.first);
                remainder = std::move(qr.second);
            } else {
                quotient.assign(k, u32(BASE - 1));
                remainder = a12;
                subtract(remainder, multiply(quotient, b1));
            }
            Digits low(a.begin(), a.begin() + min(k, a.size()));
            low.resize(k);
            low.insert(low.end(), remainder.begin(), remainder.end());
            trim(low);
            Digits b0(b.begin(), b.begin() + k);
            trim(b0);
            Digits product = multiply(quotient, b0);
            for (int i = 0; i < 2 && compare(low, product) < 0; ++i) {
                decrement(quotient);
                add(low, b);
            }
            subtract(low, product);
            return {std::move(quotient), std::move(low)};
        }

        static pair<Digits, Digits> divide_two_one(const Digits &a, const Digits &b) {
            size_t n = b.size();
            if (n <= 64 || n % 2) return knuth(a, b);
            size_t k = n / 2;
            auto top = divide_three_two(high(a, k), b, k);
            Digits low(a.begin(), a.begin() + min(k, a.size()));
            low.resize(k);
            low.insert(low.end(), top.second.begin(), top.second.end());
            trim(low);
            auto bottom = divide_three_two(low, b, k);
            bottom.first.resize(k);
            bottom.first.insert(bottom.first.end(), top.first.begin(), top.first.end());
            trim(bottom.first);
            return bottom;
        }

        static pair<Digits, Digits> burnikel(Digits a, Digits b) {
            size_t unit = 1;
            while ((b.size() + unit - 1) / unit > 64) unit *= 2;
            size_t n = (b.size() + unit - 1) / unit * unit;
            size_t padding = n - b.size();
            a.insert(a.begin(), padding, 0);
            b.insert(b.begin(), padding, 0);
            size_t end = a.size() - n;
            Digits quotient(end + 1), remainder = high(a, end);
            if (compare(remainder, b) >= 0) {
                quotient[end] = 1;
                subtract(remainder, b);
            }
            while (end) {
                size_t begin = end > n ? end - n : 0;
                Digits block(a.begin() + begin, a.begin() + end);
                block.insert(block.end(), remainder.begin(), remainder.end());
                trim(block);
                auto qr = divide_two_one(block, b);
                copy(qr.first.begin(), qr.first.end(), quotient.begin() + begin);
                remainder = std::move(qr.second);
                end = begin;
            }
            trim(quotient);
            remainder = high(remainder, padding);
            return {std::move(quotient), std::move(remainder)};
        }

        static Digits reciprocal(const Digits &b) {
            assert(b.size() >= 2 && b.back() >= BASE / 2);
            size_t n = b.size();
            if (n <= 64) {
                Digits power(2 * n + 1);
                power.back() = 1;
                return knuth(std::move(power), b).first;
            }
            size_t h = (n + 1) / 2 + 1;
            Digits x = reciprocal(high(b, n - h));
            for (int i = 0; i < 4; ++i) decrement(x);
            size_t size = 1;
            while (size <= n) size *= 2;
            Digits error;
            if (size >= CYCLIC_MIN && size < n + x.size() - 1) {
                error.resize((n + h) % size + 1);
                error.back() = 1;
                error = cyclic_difference(std::move(error), cyclic_product(b, x, size), size);
            } else {
                error.resize(n + h + 1);
                error.back() = 1;
                subtract(error, multiply(b, x));
            }
            Digits correction = high(multiply(x, error), 2 * h);
            x.insert(x.begin(), n - h, 0);
            add(x, correction);
            return x;
        }

        static pair<Digits, Digits> divide_with_inverse(const Digits &a, const Digits &b,
                                                       const Digits &inverse, size_t precision) {
            Digits top = high(a, b.size() - precision);
            Digits quotient = high(multiply(top, inverse), 2 * precision);
            size_t size = 1;
            while (size <= b.size()) size *= 2;
            Digits remainder;
            if (size >= CYCLIC_MIN && quotient.size() > SCHOOLBOOK_MIN && size < quotient.size() + b.size() - 1) {
                remainder = cyclic_difference(a, cyclic_product(quotient, b, size), size);
                if (remainder.size() > b.size() + 1 ||
                    (remainder.size() == b.size() + 1 && remainder.back() >= 3)) {
                    decrement(quotient);
                    add(remainder, b);
                    cyclic_normalize(remainder, size);
                }
            } else {
                Digits product = multiply(quotient, b);
                if (compare(product, a) > 0) {
                    decrement(quotient);
                    subtract(product, b);
                }
                remainder = a;
                subtract(remainder, product);
            }
            for (int i = 0; i < 2 && compare(remainder, b) >= 0; ++i) {
                increment(quotient);
                subtract(remainder, b);
            }
            assert(compare(remainder, b) < 0);
            return {std::move(quotient), std::move(remainder)};
        }

        static pair<Digits, Digits> divide(const Digits &a, const Digits &b) {
            assert(!b.empty());
            if (compare(a, b) < 0) return {{}, a};
            if (b.size() == 1) {
                Digits quotient = a;
                u32 r = divide_small(quotient, b[0]);
                return {std::move(quotient), r ? Digits{r} : Digits{}};
            }
            if (a.size() == 2) {
                u64 dividend = u64(a[1]) * BASE + a[0];
                u64 divisor = u64(b[1]) * BASE + b[0];
                u64 q = dividend / divisor, r = dividend % divisor;
                Digits remainder;
                if (r) remainder.push_back(u32(r % BASE));
                if (r >= BASE) remainder.push_back(u32(r / BASE));
                return {Digits{u32(q)}, std::move(remainder)};
            }
            u32 norm = u32(BASE / (u64(b.back()) + 1));
            Digits dividend = a, divisor = b;
            multiply_small(dividend, norm);
            multiply_small(divisor, norm);
            size_t m = divisor.size(), q = dividend.size() - m + 1;
            pair<Digits, Digits> result;
            if (min(m, q) <= DIVISION_MIN || u64(m) * q <= DIVISION_AREA) {
                result = knuth(std::move(dividend), divisor);
            } else if (max(m, q) <= DIVIDE_CONQUER_MAX) {
                result = burnikel(std::move(dividend), std::move(divisor));
            } else {
                size_t precision = min(q, (m + 1) / 2 + 1);
                size_t step = precision - 1;
                Digits inverse = reciprocal(high(divisor, m - precision));
                if (q <= precision) {
                    result = divide_with_inverse(dividend, divisor, inverse, precision);
                } else {
                    Digits quotient(q);
                    size_t end = dividend.size() - m;
                    Digits remainder = high(dividend, end);
                    if (compare(remainder, divisor) >= 0) {
                        quotient[end] = 1;
                        subtract(remainder, divisor);
                    }
                    while (end) {
                        size_t begin = end > step ? end - step : 0;
                        Digits block(dividend.begin() + begin, dividend.begin() + end);
                        block.insert(block.end(), remainder.begin(), remainder.end());
                        trim(block);
                        auto qr = divide_with_inverse(block, divisor, inverse, precision);
                        copy(qr.first.begin(), qr.first.end(), quotient.begin() + begin);
                        remainder = std::move(qr.second);
                        end = begin;
                    }
                    trim(quotient);
                    result = {std::move(quotient), std::move(remainder)};
                }
            }
            if (norm != 1) divide_small(result.second, norm);
            return result;
        }

        static Digits power_of_two(int bits) {
            Digits result{1}, factor{2};
            while (bits) {
                if (bits & 1) result = multiply(result, factor);
                bits >>= 1;
                if (bits) factor = multiply(factor, factor);
            }
            return result;
        }
    };
}

template<class Radix>
class BasicBigInteger {
    using u32 = BigIntegerDetail::u32;
    using u64 = BigIntegerDetail::u64;
    using Ops = BigIntegerDetail::Magnitude<Radix>;
    using Digits = typename Ops::Digits;
    static constexpr u64 BASE = Radix::BASE;
    static constexpr int IO_BASE = Radix::IO_BASE;
    static constexpr int BLOCK_DIGITS = Radix::BLOCK_DIGITS;

    Digits digits;
    bool negative = false;

    static int digit_value(char c) {
        if ('0' <= c && c <= '9') return c - '0';
        if ('a' <= c && c <= 'z') return c - 'a' + 10;
        if ('A' <= c && c <= 'Z') return c - 'A' + 10;
        return -1;
    }

    static void append_digits(string &out, u32 value, int base, int width) {
        char buffer[32];
        int pos = 32;
        do {
            int digit = value % base;
            buffer[--pos] = char(digit < 10 ? '0' + digit : 'a' + digit - 10);
            value /= base;
        } while (value);
        out.append(max(0, width - (32 - pos)), '0');
        out.append(buffer + pos, buffer + 32);
    }

    BasicBigInteger(Digits value, bool sign) : digits(std::move(value)), negative(sign && !digits.empty()) {}

    BasicBigInteger &add_signed(const BasicBigInteger &other, bool sign) {
        if (negative == sign) Ops::add(digits, other.digits);
        else {
            int cmp = Ops::compare(digits, other.digits);
            if (cmp >= 0) Ops::subtract(digits, other.digits);
            else {
                Digits result = other.digits;
                Ops::subtract(result, digits);
                digits = std::move(result);
                negative = sign;
            }
        }
        if (digits.empty()) negative = false;
        return *this;
    }

    static int compare(const BasicBigInteger &a, const BasicBigInteger &b) {
        if (a.negative != b.negative) return a.negative ? -1 : 1;
        int cmp = Ops::compare(a.digits, b.digits);
        return a.negative ? -cmp : cmp;
    }

public:
    BasicBigInteger() = default;
    BasicBigInteger(long long value) { *this = value; }
    BasicBigInteger(const string &value, int base = IO_BASE) {
        bool ok = assign(value, base);
        assert(ok);
        (void)ok;
    }

    BasicBigInteger &operator=(long long value) {
        digits.clear();
        negative = value < 0;
        u64 magnitude = negative ? u64(-(value + 1)) + 1 : u64(value);
        while (magnitude) {
            digits.push_back(u32(magnitude % BASE));
            magnitude /= BASE;
        }
        return *this;
    }

    bool assign(const string &value, int base = IO_BASE) {
        digits.clear();
        negative = false;
        if (base < 2 || base > 36 || value.empty()) return false;
        size_t begin = value[0] == '+' || value[0] == '-';
        if (begin == value.size()) return false;
        for (size_t i = begin; i < value.size(); ++i) {
            int digit = digit_value(value[i]);
            if (digit < 0 || digit >= base) return false;
        }
        while (begin < value.size() && value[begin] == '0') ++begin;
        if (begin == value.size()) return true;
        if (base == IO_BASE) {
            digits.reserve((value.size() - begin + BLOCK_DIGITS - 1) / BLOCK_DIGITS);
            for (size_t right = value.size(); right > begin;) {
                size_t left = right - min(size_t(BLOCK_DIGITS), right - begin);
                u32 block = 0;
                for (size_t i = left; i < right; ++i) block = block * base + digit_value(value[i]);
                digits.push_back(block);
                right = left;
            }
        } else if (IO_BASE == 16 && (base & (base - 1)) == 0) {
            int bits = __builtin_ctz(unsigned(base)), filled = 0;
            digits.reserve(((value.size() - begin) * bits + 31) / 32);
            u64 buffer = 0;
            for (size_t i = value.size(); i-- > begin;) {
                buffer |= u64(digit_value(value[i])) << filled;
                filled += bits;
                if (filled >= 32) {
                    digits.push_back(u32(buffer));
                    buffer >>= 32;
                    filled -= 32;
                }
            }
            if (buffer) digits.push_back(u32(buffer));
        } else {
            u32 power = 1;
            int count = 0;
            while (power <= (BASE - 1) / base) { power *= base; ++count; }
            size_t width = (value.size() - begin - 1) % count + 1;
            for (size_t pos = begin; pos < value.size(); width = count) {
                u32 block = 0, multiplier = 1;
                for (size_t i = 0; i < width; ++i) {
                    block = block * base + digit_value(value[pos++]);
                    multiplier *= base;
                }
                Ops::multiply_small(digits, multiplier);
                if (block) Ops::add(digits, Digits{block});
            }
        }
        negative = value[0] == '-';
        return true;
    }

    string to_string(int base = IO_BASE) const {
        assert(2 <= base && base <= 36);
        if (is_zero()) return "0";
        if (IO_BASE == 16 && base != IO_BASE && (base & (base - 1)) == 0) {
            int bits = __builtin_ctz(unsigned(base));
            size_t length = ((digits.size() - 1) * 32 + 32 - __builtin_clz(digits.back()) + bits - 1) / bits;
            string out(size_t(negative) + length, '0');
            if (negative) out[0] = '-';
            for (size_t i = 0; i < length; ++i) {
                size_t word = i * bits / 32;
                int shift = i * bits % 32;
                u64 value = digits[word] >> shift;
                if (shift + bits > 32 && word + 1 < digits.size()) value |= u64(digits[word + 1]) << (32 - shift);
                int digit = value & (base - 1);
                out[out.size() - 1 - i] = char(digit < 10 ? '0' + digit : 'a' + digit - 10);
            }
            return out;
        }
        string out;
        out.reserve(digits.size() * BLOCK_DIGITS + 1);
        if (negative) out.push_back('-');
        if (base == IO_BASE) {
            append_digits(out, digits.back(), base, 0);
            for (size_t i = digits.size() - 1; i-- > 0;) append_digits(out, digits[i], base, BLOCK_DIGITS);
        } else {
            u32 power = 1;
            int count = 0;
            while (power <= (BASE - 1) / base) { power *= base; ++count; }
            Digits value = digits, parts;
            while (!value.empty()) parts.push_back(Ops::divide_small(value, power));
            append_digits(out, parts.back(), base, 0);
            for (size_t i = parts.size() - 1; i-- > 0;) append_digits(out, parts[i], base, count);
        }
        return out;
    }

    bool is_zero() const { return digits.empty(); }
    bool is_negative() const { return negative; }
    BasicBigInteger abs() const { return BasicBigInteger(digits, false); }
    BasicBigInteger operator+() const { return *this; }
    BasicBigInteger operator-() const { return BasicBigInteger(digits, !negative); }

    BasicBigInteger &operator+=(const BasicBigInteger &other) { return add_signed(other, other.negative); }
    BasicBigInteger &operator-=(const BasicBigInteger &other) { return add_signed(other, !other.negative); }
    BasicBigInteger &operator*=(const BasicBigInteger &other) {
        bool sign = negative != other.negative;
        digits = Ops::multiply(digits, other.digits);
        negative = sign && !digits.empty();
        return *this;
    }

    static pair<BasicBigInteger, BasicBigInteger> divmod(const BasicBigInteger &a, const BasicBigInteger &b) {
        auto result = Ops::divide(a.digits, b.digits);
        return {BasicBigInteger(std::move(result.first), a.negative != b.negative),
                BasicBigInteger(std::move(result.second), a.negative)};
    }

    static pair<BasicBigInteger, BasicBigInteger> floor_divmod(const BasicBigInteger &a, const BasicBigInteger &b) {
        auto result = divmod(a, b);
        if (!result.second.is_zero() && a.negative != b.negative) {
            result.first -= 1;
            result.second += b;
        }
        return result;
    }

    BasicBigInteger &operator/=(const BasicBigInteger &other) { *this = divmod(*this, other).first; return *this; }
    BasicBigInteger &operator%=(const BasicBigInteger &other) { *this = divmod(*this, other).second; return *this; }

    BasicBigInteger &operator<<=(int bits) {
        assert(bits >= 0);
        if (is_zero() || bits == 0) return *this;
        if constexpr (IO_BASE == 16) {
            u32 carry = 0;
            int shift = bits % 32;
            for (u32 &digit : digits) {
                u64 value = (u64(digit) << shift) | carry;
                digit = u32(value);
                carry = u32(value >> 32);
            }
            if (carry) digits.push_back(carry);
            digits.insert(digits.begin(), bits / 32, 0);
        } else if (bits < 32) Ops::multiply_small(digits, 1u << bits);
        else digits = Ops::multiply(digits, Ops::power_of_two(bits));
        return *this;
    }

    BasicBigInteger &operator>>=(int bits) {
        assert(bits >= 0);
        if (is_zero() || bits == 0) return *this;
        bool discarded = false;
        if constexpr (IO_BASE == 16) {
            size_t drop = min(digits.size(), size_t(bits / 32));
            for (size_t i = 0; i < drop; ++i) discarded |= digits[i] != 0;
            digits.erase(digits.begin(), digits.begin() + drop);
            int shift = bits % 32;
            if (shift) {
                u32 carry = 0, mask = (1u << shift) - 1;
                for (size_t i = digits.size(); i-- > 0;) {
                    u32 next = digits[i] & mask;
                    digits[i] = (digits[i] >> shift) | (carry << (32 - shift));
                    carry = next;
                }
                discarded |= carry != 0;
            }
            Ops::trim(digits);
        } else if (bits < 32) discarded = Ops::divide_small(digits, 1u << bits) != 0;
        else if (u64(bits) >= 27ULL * digits.size()) { digits.clear(); discarded = true; }
        else {
            auto result = Ops::divide(digits, Ops::power_of_two(bits));
            digits = std::move(result.first);
            discarded = !result.second.empty();
        }
        if (negative && discarded) Ops::increment(digits);
        if (digits.empty()) negative = false;
        return *this;
    }

    friend BasicBigInteger operator+(BasicBigInteger a, const BasicBigInteger &b) { a += b; return a; }
    friend BasicBigInteger operator-(BasicBigInteger a, const BasicBigInteger &b) { a -= b; return a; }
    friend BasicBigInteger operator*(const BasicBigInteger &a, const BasicBigInteger &b) {
        return BasicBigInteger(Ops::multiply(a.digits, b.digits), a.negative != b.negative);
    }
    friend BasicBigInteger operator/(const BasicBigInteger &a, const BasicBigInteger &b) { return divmod(a, b).first; }
    friend BasicBigInteger operator%(const BasicBigInteger &a, const BasicBigInteger &b) { return divmod(a, b).second; }
    friend BasicBigInteger operator<<(BasicBigInteger a, int bits) { a <<= bits; return a; }
    friend BasicBigInteger operator>>(BasicBigInteger a, int bits) { a >>= bits; return a; }
    friend bool operator==(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) == 0; }
    friend bool operator!=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) != 0; }
    friend bool operator<(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) < 0; }
    friend bool operator<=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) <= 0; }
    friend bool operator>(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) > 0; }
    friend bool operator>=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a, b) >= 0; }
    friend pair<BasicBigInteger, BasicBigInteger> divmod(const BasicBigInteger &a, const BasicBigInteger &b) {
        return BasicBigInteger::divmod(a, b);
    }
    friend pair<BasicBigInteger, BasicBigInteger> floor_divmod(const BasicBigInteger &a, const BasicBigInteger &b) {
        return BasicBigInteger::floor_divmod(a, b);
    }
};

using BigInteger = BasicBigInteger<BigIntegerDetail::DecimalRadix>;
using HexBigInteger = BasicBigInteger<BigIntegerDetail::HexRadix>;

#endif

/**
 * @brief 多倍長整数(BigInteger)
 */
