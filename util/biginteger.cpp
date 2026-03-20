#ifndef FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP
#define FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP

#define FIRIEXP_LIBRARY_FFT_EXACT_ONLY
#include "../math/fft.cpp"
#undef FIRIEXP_LIBRARY_FFT_EXACT_ONLY

struct BigInteger {
    using u32 = unsigned int;
    using u64 = unsigned long long;
    using u128 = __uint128_t;

    static constexpr u64 BASE = 1ULL << 32;
    static constexpr u32 BASE_MASK = 0xffffffffu;
    static constexpr u32 DEC_BLOCK = 1000000000u;
    static constexpr int DEC_BLOCK_DIGITS = 9;
    static constexpr u32 DEC_CONV_BASE = 1000000u;
    static constexpr int DEC_CONV_DIGITS = 6;
    static constexpr int HEX_BLOCK_DIGITS = 8;

    vector<u32> d;
    int sign;

    BigInteger() : d(), sign(0) {}
    BigInteger(long long x) { *this = x; }
    BigInteger(const string &s, int base = 10) { assign(s, base); }

    BigInteger &operator=(long long x) {
        d.clear();
        if (x == 0) {
            sign = 0;
            return *this;
        }
        sign = x < 0 ? -1 : 1;
        u64 y;
        if (x < 0) y = u64(-(x + 1)) + 1;
        else y = u64(x);
        while (y) {
            d.push_back(u32(y & BASE_MASK));
            y >>= 32;
        }
        return *this;
    }

    static int digit_value(char c) {
        if ('0' <= c && c <= '9') return c - '0';
        if ('a' <= c && c <= 'z') return c - 'a' + 10;
        if ('A' <= c && c <= 'Z') return c - 'A' + 10;
        return -1;
    }

    static char digit_char(int x) {
        return x < 10 ? char('0' + x) : char('a' + (x - 10));
    }

    bool is_zero() const { return sign == 0; }

    int bit_length() const {
        if (is_zero()) return 0;
        return 32 * ((int)d.size() - 1) + 32 - __builtin_clz(d.back());
    }

    static vector<BigInteger> &decimal_pow_cache() {
        static vector<BigInteger> cache = [] {
            vector<BigInteger> v(2);
            v[0] = BigInteger(1);
            v[1] = BigInteger((long long)DEC_BLOCK);
            return v;
        }();
        return cache;
    }

    static vector<char> &decimal_pow_ready() {
        static vector<char> ready = {1, 1};
        return ready;
    }

    static const BigInteger &decimal_pow_blocks(int blocks) {
        auto &cache = decimal_pow_cache();
        auto &ready = decimal_pow_ready();
        if ((int)cache.size() <= blocks) {
            cache.resize(blocks + 1);
            ready.resize(blocks + 1, 0);
        }
        if (ready[blocks]) return cache[blocks];
        int left = blocks >> 1;
        int right = blocks - left;
        cache[blocks] = decimal_pow_blocks(left) * decimal_pow_blocks(right);
        ready[blocks] = 1;
        return cache[blocks];
    }

    static BigInteger from_decimal_blocks(const vector<u32> &blocks, int l, int r) {
        if (l >= r) return BigInteger();
        if (r - l <= 32) {
            BigInteger res;
            for (int i = l; i < r; ++i) {
                res.mul_small_assign(DEC_BLOCK);
                res.add_small_assign(blocks[i]);
            }
            return res;
        }
        int m = (l + r) >> 1;
        BigInteger left = from_decimal_blocks(blocks, l, m);
        BigInteger right = from_decimal_blocks(blocks, m, r);
        if (!left.is_zero()) left *= decimal_pow_blocks(r - m);
        left += right;
        return left;
    }

    static vector<u32> mul_decimal_vectors(const vector<u32> &a, const vector<u32> &b) {
        if (a.empty() || b.empty()) return {};
        if (min(a.size(), b.size()) <= 32 || a.size() * b.size() <= 4096) {
            vector<u32> res(a.size() + b.size(), 0);
            for (size_t i = 0; i < a.size(); ++i) {
                u64 carry = 0;
                size_t j = 0;
                for (; j < b.size(); ++j) {
                    u128 cur = u128(a[i]) * b[j] + res[i + j] + carry;
                    res[i + j] = u32(cur % DEC_CONV_BASE);
                    carry = u64(cur / DEC_CONV_BASE);
                }
                size_t pos = i + j;
                while (carry) {
                    u64 cur = u64(res[pos]) + carry;
                    res[pos] = u32(cur % DEC_CONV_BASE);
                    carry = cur / DEC_CONV_BASE;
                    ++pos;
                }
            }
            while (!res.empty() && res.back() == 0) res.pop_back();
            return res;
        }
        auto conv = ArbitraryConvolution::convolution_u64(a, b);
        vector<u32> res;
        res.reserve(conv.size() + 3);
        u64 carry = 0;
        for (u64 v : conv) {
            u64 cur = v + carry;
            res.push_back(u32(cur % DEC_CONV_BASE));
            carry = cur / DEC_CONV_BASE;
        }
        while (carry) {
            res.push_back(u32(carry % DEC_CONV_BASE));
            carry /= DEC_CONV_BASE;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    static vector<u32> add_decimal_vectors(vector<u32> a, const vector<u32> &b) {
        if (a.size() < b.size()) a.resize(b.size(), 0);
        u64 carry = 0;
        size_t i = 0;
        for (; i < b.size(); ++i) {
            u64 cur = u64(a[i]) + b[i] + carry;
            a[i] = u32(cur % DEC_CONV_BASE);
            carry = cur / DEC_CONV_BASE;
        }
        for (; i < a.size() && carry; ++i) {
            u64 cur = u64(a[i]) + carry;
            a[i] = u32(cur % DEC_CONV_BASE);
            carry = cur / DEC_CONV_BASE;
        }
        if (carry) a.push_back(u32(carry));
        while (!a.empty() && a.back() == 0) a.pop_back();
        return a;
    }

    static vector<vector<u32>> &binary_pow_decimal_cache() {
        static vector<vector<u32>> cache = {{1}, {967296u, 4294u}};
        return cache;
    }

    static vector<char> &binary_pow_decimal_ready() {
        static vector<char> ready = {1, 1};
        return ready;
    }

    static const vector<u32> &binary_pow_decimal(int limbs) {
        auto &cache = binary_pow_decimal_cache();
        auto &ready = binary_pow_decimal_ready();
        if ((int)cache.size() <= limbs) {
            cache.resize(limbs + 1);
            ready.resize(limbs + 1, 0);
        }
        if (ready[limbs]) return cache[limbs];
        int left = limbs >> 1;
        int right = limbs - left;
        cache[limbs] = mul_decimal_vectors(binary_pow_decimal(left), binary_pow_decimal(right));
        ready[limbs] = 1;
        return cache[limbs];
    }

    static vector<u32> small_limbs_to_decimal(const vector<u32> &limbs, int l, int r) {
        BigInteger tmp;
        tmp.sign = 1;
        tmp.d.assign(limbs.begin() + l, limbs.begin() + r);
        tmp.trim();
        vector<u32> res;
        while (!tmp.is_zero()) res.push_back(tmp.div_small_assign(DEC_CONV_BASE));
        return res;
    }

    static vector<u32> limbs_to_decimal(const vector<u32> &limbs, int l, int r) {
        while (l < r && limbs[r - 1] == 0) --r;
        if (l >= r) return {};
        if (r - l <= 32) return small_limbs_to_decimal(limbs, l, r);
        int m = (l + r) >> 1;
        vector<u32> low = limbs_to_decimal(limbs, l, m);
        vector<u32> high = limbs_to_decimal(limbs, m, r);
        if (high.empty()) return low;
        vector<u32> shifted = mul_decimal_vectors(high, binary_pow_decimal(m - l));
        if (low.empty()) return shifted;
        return add_decimal_vectors(std::move(low), shifted);
    }

    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
        if (d.empty()) sign = 0;
    }

    int compare_abs(const BigInteger &other) const {
        if (d.size() != other.d.size()) return d.size() < other.d.size() ? -1 : 1;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            if (d[i] != other.d[i]) return d[i] < other.d[i] ? -1 : 1;
        }
        return 0;
    }

    static int compare(const BigInteger &a, const BigInteger &b) {
        if (a.sign != b.sign) return a.sign < b.sign ? -1 : 1;
        if (a.sign == 0) return 0;
        int c = a.compare_abs(b);
        return a.sign > 0 ? c : -c;
    }

    void add_abs(const BigInteger &other) {
        if (other.is_zero()) return;
        if (d.size() < other.d.size()) d.resize(other.d.size(), 0);
        u64 carry = 0;
        for (size_t i = 0; i < other.d.size(); ++i) {
            u64 cur = carry + u64(d[i]) + other.d[i];
            d[i] = u32(cur);
            carry = cur >> 32;
        }
        for (size_t i = other.d.size(); carry && i < d.size(); ++i) {
            u64 cur = carry + u64(d[i]);
            d[i] = u32(cur);
            carry = cur >> 32;
        }
        if (carry) d.push_back(u32(carry));
        if (!d.empty()) sign = 1;
    }

    void sub_abs(const BigInteger &other) {
        // assume |*this| >= |other|
        u64 borrow = 0;
        for (size_t i = 0; i < other.d.size(); ++i) {
            u64 cur = u64(d[i]);
            u64 rhs = u64(other.d[i]) + borrow;
            if (cur < rhs) {
                d[i] = u32((cur + BASE) - rhs);
                borrow = 1;
            } else {
                d[i] = u32(cur - rhs);
                borrow = 0;
            }
        }
        for (size_t i = other.d.size(); borrow && i < d.size(); ++i) {
            u64 cur = u64(d[i]);
            if (cur == 0) {
                d[i] = BASE_MASK;
                borrow = 1;
            } else {
                d[i] = u32(cur - 1);
                borrow = 0;
            }
        }
        trim();
    }

    void mul_small_assign(u32 m) {
        if (is_zero() || m == 1) return;
        if (m == 0) {
            d.clear();
            sign = 0;
            return;
        }
        u64 carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            u64 cur = u64(d[i]) * m + carry;
            d[i] = u32(cur);
            carry = cur >> 32;
        }
        if (carry) d.push_back(u32(carry));
    }

    void add_small_assign(u32 a) {
        if (a == 0) return;
        if (is_zero()) {
            sign = 1;
            d.push_back(a);
            return;
        }
        u64 carry = a;
        for (size_t i = 0; i < d.size() && carry; ++i) {
            u64 cur = u64(d[i]) + carry;
            d[i] = u32(cur);
            carry = cur >> 32;
        }
        if (carry) d.push_back(u32(carry));
    }

    u32 div_small_assign(u32 m) {
        u64 rem = 0;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            u64 cur = (rem << 32) | d[i];
            d[i] = u32(cur / m);
            rem = cur % m;
        }
        trim();
        return u32(rem);
    }

    void shift_left_bits_assign(int bits) {
        if (bits < 0) {
            shift_right_bits_assign(-bits);
            return;
        }
        if (is_zero() || bits == 0) return;
        int word = bits >> 5;
        int rem = bits & 31;
        if (word) d.insert(d.begin(), (size_t)word, 0);
        if (rem == 0) return;
        u64 carry = 0;
        for (size_t i = word; i < d.size(); ++i) {
            u64 cur = (u64(d[i]) << rem) | carry;
            d[i] = u32(cur);
            carry = cur >> 32;
        }
        if (carry) d.push_back(u32(carry));
    }

    void shift_right_bits_assign(int bits) {
        if (bits < 0) {
            shift_left_bits_assign(-bits);
            return;
        }
        if (is_zero() || bits == 0) return;
        int word = bits >> 5;
        int rem = bits & 31;
        if (word >= (int)d.size()) {
            d.clear();
            sign = 0;
            return;
        }
        if (word) d.erase(d.begin(), d.begin() + word);
        if (rem == 0) {
            trim();
            return;
        }
        u64 carry = 0;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            u64 cur = d[i];
            d[i] = u32((cur >> rem) | (carry << (32 - rem)));
            carry = cur & ((1ULL << rem) - 1);
        }
        trim();
    }

    static BigInteger mul_schoolbook(const BigInteger &a, const BigInteger &b) {
        BigInteger res;
        if (a.is_zero() || b.is_zero()) return res;
        res.sign = 1;
        res.d.assign(a.d.size() + b.d.size(), 0);
        for (size_t i = 0; i < a.d.size(); ++i) {
            u64 carry = 0;
            for (size_t j = 0; j < b.d.size(); ++j) {
                u64 cur = u64(res.d[i + j]) + u64(a.d[i]) * b.d[j] + carry;
                res.d[i + j] = u32(cur);
                carry = cur >> 32;
            }
            size_t pos = i + b.d.size();
            while (carry) {
                u64 cur = u64(res.d[pos]) + carry;
                res.d[pos] = u32(cur);
                carry = cur >> 32;
                ++pos;
            }
        }
        res.trim();
        return res;
    }

    static BigInteger mul_convolution(const BigInteger &a, const BigInteger &b) {
        BigInteger res;
        if (a.is_zero() || b.is_zero()) return res;
        vector<u32> x;
        vector<u32> y;
        x.reserve(a.d.size() * 2);
        y.reserve(b.d.size() * 2);
        for (u32 v : a.d) {
            x.push_back(v & 0xffffu);
            x.push_back(v >> 16);
        }
        for (u32 v : b.d) {
            y.push_back(v & 0xffffu);
            y.push_back(v >> 16);
        }
        while (!x.empty() && x.back() == 0) x.pop_back();
        while (!y.empty() && y.back() == 0) y.pop_back();
        if (x.empty() || y.empty()) return res;
        auto conv = ArbitraryConvolution::convolution_u64(x, y);
        vector<u32> digits;
        digits.reserve(conv.size() + 2);
        u64 carry = 0;
        for (u64 v : conv) {
            u64 cur = v + carry;
            digits.push_back(u32(cur & 0xffffu));
            carry = cur >> 16;
        }
        while (carry) {
            digits.push_back(u32(carry & 0xffffu));
            carry >>= 16;
        }
        while (!digits.empty() && digits.back() == 0) digits.pop_back();
        if (digits.empty()) return res;
        res.sign = 1;
        res.d.reserve((digits.size() + 1) / 2);
        for (size_t i = 0; i < digits.size(); i += 2) {
            u32 lo = digits[i];
            u32 hi = i + 1 < digits.size() ? digits[i + 1] : 0;
            res.d.push_back(lo | (hi << 16));
        }
        res.trim();
        return res;
    }

    static BigInteger multiply(const BigInteger &a, const BigInteger &b) {
        if (a.is_zero() || b.is_zero()) return BigInteger();
        BigInteger res;
        size_t n = a.d.size(), m = b.d.size();
        if (min(n, m) <= 64 || n * m <= 4096) res = mul_schoolbook(a, b);
        else res = mul_convolution(a, b);
        res.sign = a.sign * b.sign;
        if (res.is_zero()) res.sign = 0;
        return res;
    }

    static vector<u32> shift_left_copy_limbs(const vector<u32> &src, int bits) {
        if (src.empty()) return {};
        if (bits == 0) return src;
        vector<u32> res(src.size() + 1, 0);
        u32 carry = 0;
        for (size_t i = 0; i < src.size(); ++i) {
            u64 cur = (u64(src[i]) << bits) | carry;
            res[i] = u32(cur);
            carry = u32(cur >> 32);
        }
        res[src.size()] = carry;
        if (res.back() == 0) res.pop_back();
        return res;
    }

    static void shift_right_limbs_assign(vector<u32> &src, int bits) {
        if (src.empty() || bits == 0) return;
        u32 carry = 0;
        for (int i = (int)src.size() - 1; i >= 0; --i) {
            u32 cur = src[i];
            src[i] = (cur >> bits) | (carry << (32 - bits));
            carry = cur & ((u32(1) << bits) - 1);
        }
        while (!src.empty() && src.back() == 0) src.pop_back();
    }

    static BigInteger divmod_abs(const BigInteger &u0, const BigInteger &v0, BigInteger &rem) {
        if (v0.is_zero()) {
            rem = BigInteger();
            return BigInteger();
        }
        if (u0.compare_abs(v0) < 0) {
            rem = u0;
            BigInteger q;
            return q;
        }
        if (v0.d.size() == 1) {
            BigInteger q = u0;
            u32 r = q.div_small_assign(v0.d[0]);
            rem = BigInteger(r);
            if (r == 0) rem.sign = 0;
            else rem.sign = 1;
            q.sign = q.is_zero() ? 0 : 1;
            return q;
        }

        int shift = __builtin_clz(v0.d.back());
        vector<u32> un = shift ? shift_left_copy_limbs(u0.d, shift) : u0.d;
        vector<u32> vn = shift ? shift_left_copy_limbs(v0.d, shift) : v0.d;
        size_t n = vn.size();
        size_t m = un.size() - n;
        un.push_back(0);

        BigInteger q;
        q.sign = 1;
        q.d.assign(m + 1, 0);

        for (size_t jj = m + 1; jj-- > 0; ) {
            size_t j = jj;
            u64 numerator = (u64(un[j + n]) << 32) | un[j + n - 1];
            u64 qhat = numerator / vn[n - 1];
            u64 rhat = numerator % vn[n - 1];
            if (qhat == BASE) {
                --qhat;
                rhat += vn[n - 1];
            }
            if (n >= 2 && rhat < BASE &&
                qhat * vn[n - 2] > (rhat << 32) + un[j + n - 2]) {
                --qhat;
                rhat += vn[n - 1];
                if (rhat < BASE && qhat * vn[n - 2] > (rhat << 32) + un[j + n - 2]) {
                    --qhat;
                    rhat += vn[n - 1];
                }
            }

            u64 carry = 0;
            u64 borrow = 0;
            for (size_t i = 0; i < n; ++i) {
                u64 prod = qhat * vn[i] + carry;
                carry = prod >> 32;
                u64 sub = u64(u32(prod)) + borrow;
                if (u64(un[j + i]) < sub) {
                    un[j + i] = u32(u64(un[j + i]) + BASE - sub);
                    borrow = 1;
                } else {
                    un[j + i] = u32(u64(un[j + i]) - sub);
                    borrow = 0;
                }
            }

            u64 sub = carry + borrow;
            bool negative = false;
            if (u64(un[j + n]) < sub) {
                un[j + n] = u32(u64(un[j + n]) + BASE - sub);
                negative = true;
            } else {
                un[j + n] = u32(u64(un[j + n]) - sub);
            }

            if (negative) {
                --qhat;
                u64 add_carry = 0;
                for (size_t i = 0; i < n; ++i) {
                    u64 cur = u64(un[j + i]) + vn[i] + add_carry;
                    un[j + i] = u32(cur);
                    add_carry = cur >> 32;
                }
                un[j + n] = u32(u64(un[j + n]) + add_carry);
            }
            q.d[j] = u32(qhat);
        }

        q.trim();
        rem.d.assign(un.begin(), un.begin() + n);
        rem.sign = rem.d.empty() ? 0 : 1;
        if (shift) shift_right_limbs_assign(rem.d, shift);
        rem.trim();
        return q;
    }

    static pair<BigInteger, BigInteger> divmod_abs(const BigInteger &u, const BigInteger &v) {
        BigInteger r;
        BigInteger q = divmod_abs(u, v, r);
        return {q, r};
    }

    static pair<BigInteger, BigInteger> divmod(const BigInteger &a, const BigInteger &b) {
        if (b.is_zero()) return {BigInteger(), BigInteger()};
        if (a.is_zero()) return {BigInteger(), BigInteger()};
        BigInteger aa = a;
        BigInteger bb = b;
        aa.sign = aa.is_zero() ? 0 : 1;
        bb.sign = bb.is_zero() ? 0 : 1;
        auto qr = divmod_abs(aa, bb);
        BigInteger q = qr.first;
        BigInteger r = qr.second;
        if (a.sign == b.sign) {
            q.sign = q.is_zero() ? 0 : 1;
            if (!r.is_zero()) r.sign = b.sign;
            return {q, r};
        }
        if (r.is_zero()) {
            q.sign = q.is_zero() ? 0 : -1;
            return {q, r};
        }
        BigInteger one = 1;
        q += one;
        q.sign = -1;
        r = bb - r;
        r.sign = b.sign;
        if (q.is_zero()) q.sign = 0;
        return {q, r};
    }

    void assign(const string &s, int base = 10) {
        d.clear();
        sign = 0;
        int p = 0;
        bool neg = false;
        if (p < (int)s.size() && (s[p] == '+' || s[p] == '-')) {
            neg = s[p] == '-';
            ++p;
        }
        while (p < (int)s.size() && s[p] == '0') ++p;
        if (p == (int)s.size()) return;
        if (base == 16) {
            for (int i = (int)s.size(); i > p; ) {
                int l = max(p, i - HEX_BLOCK_DIGITS);
                u32 x = 0;
                for (int j = l; j < i; ++j) {
                    int v = digit_value(s[j]);
                    if (v < 0 || v >= 16) {
                        d.clear();
                        sign = 0;
                        return;
                    }
                    x = (x << 4) | u32(v);
                }
                d.push_back(x);
                i = l;
            }
            sign = 1;
            trim();
            if (neg && !is_zero()) sign = -1;
            return;
        }
        if (base == 10) {
            vector<u32> blocks;
            blocks.reserve(((int)s.size() - p + DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS);
            int i = p;
            int first = ((int)s.size() - p) % DEC_BLOCK_DIGITS;
            if (first == 0) first = DEC_BLOCK_DIGITS;
            while (i < (int)s.size()) {
                int r = min((int)s.size(), i + (blocks.empty() ? first : DEC_BLOCK_DIGITS));
                u32 x = 0;
                for (int j = i; j < r; ++j) {
                    char c = s[j];
                    if (c < '0' || c > '9') {
                        d.clear();
                        sign = 0;
                        return;
                    }
                    x = x * 10 + u32(c - '0');
                }
                blocks.push_back(x);
                i = r;
            }
            *this = from_decimal_blocks(blocks, 0, (int)blocks.size());
            if (neg && !is_zero()) sign = -1;
            return;
        }
        for (; p < (int)s.size(); ++p) {
            int v = digit_value(s[p]);
            if (v < 0 || v >= base) {
                d.clear();
                sign = 0;
                return;
            }
            mul_small_assign((u32)base);
            add_small_assign((u32)v);
        }
        sign = 1;
        trim();
        if (neg && !is_zero()) sign = -1;
    }

    string to_string(int base = 10) const {
        if (is_zero()) return "0";
        if (base == 16) {
            string res;
            if (sign < 0) res.push_back('-');
            int i = (int)d.size() - 1;
            auto append_hex32 = [&](u32 x, bool leading) {
                char buf[8];
                for (int k = 0; k < 8; ++k) {
                    buf[7 - k] = digit_char((x >> (k * 4)) & 15);
                }
                int start = 0;
                if (leading) {
                    while (start < 8 && buf[start] == '0') ++start;
                }
                res.append(buf + start, buf + 8);
            };
            append_hex32(d[i], true);
            for (--i; i >= 0; --i) append_hex32(d[i], false);
            return res;
        }
        vector<u32> parts = limbs_to_decimal(d, 0, (int)d.size());
        string res;
        if (sign < 0) res.push_back('-');
        res += std::to_string(parts.back());
        char buf[DEC_CONV_DIGITS];
        for (int i = (int)parts.size() - 2; i >= 0; --i) {
            u32 x = parts[i];
            for (int j = DEC_CONV_DIGITS - 1; j >= 0; --j) {
                buf[j] = char('0' + (x % 10));
                x /= 10;
            }
            res.append(buf, buf + DEC_CONV_DIGITS);
        }
        return res;
    }

    BigInteger operator+() const { return *this; }
    BigInteger operator-() const {
        BigInteger res = *this;
        if (!res.is_zero()) res.sign = -res.sign;
        return res;
    }

    BigInteger &operator+=(const BigInteger &rhs) {
        if (rhs.is_zero()) return *this;
        if (this == &rhs) {
            BigInteger tmp = rhs;
            return *this += tmp;
        }
        if (is_zero()) {
            *this = rhs;
            return *this;
        }
        if (sign == rhs.sign) {
            add_abs(rhs);
            sign = rhs.sign;
            return *this;
        }
        int c = compare_abs(rhs);
        if (c == 0) {
            d.clear();
            sign = 0;
        } else if (c > 0) {
            sub_abs(rhs);
        } else {
            BigInteger tmp = rhs;
            tmp.sub_abs(*this);
            *this = tmp;
        }
        return *this;
    }

    BigInteger &operator-=(const BigInteger &rhs) {
        if (rhs.is_zero()) return *this;
        if (is_zero()) {
            *this = rhs;
            if (!is_zero()) sign = -sign;
            return *this;
        }
        if (sign != rhs.sign) {
            int s = sign;
            add_abs(rhs);
            sign = s;
            return *this;
        }
        int c = compare_abs(rhs);
        if (c == 0) {
            d.clear();
            sign = 0;
        } else if (c > 0) {
            sub_abs(rhs);
        } else {
            BigInteger tmp = rhs;
            tmp.sub_abs(*this);
            tmp.sign = -sign;
            *this = tmp;
        }
        return *this;
    }

    BigInteger &operator*=(const BigInteger &rhs) {
        if (is_zero() || rhs.is_zero()) {
            d.clear();
            sign = 0;
            return *this;
        }
        BigInteger a = *this;
        BigInteger b = rhs;
        *this = multiply(a, b);
        return *this;
    }

    BigInteger &operator/=(const BigInteger &rhs) {
        *this = divmod(*this, rhs).first;
        return *this;
    }

    BigInteger &operator%=(const BigInteger &rhs) {
        *this = divmod(*this, rhs).second;
        return *this;
    }

    BigInteger &operator<<=(int bits) {
        if (bits < 0) return *this >>= -bits;
        if (is_zero()) return *this;
        shift_left_bits_assign(bits);
        return *this;
    }

    BigInteger &operator>>=(int bits) {
        if (bits < 0) return *this <<= -bits;
        if (is_zero() || bits == 0) return *this;
        if (sign > 0) {
            shift_right_bits_assign(bits);
            return *this;
        }
        BigInteger p = 1;
        p <<= bits;
        *this = divmod(*this, p).first;
        return *this;
    }

    friend BigInteger operator+(BigInteger lhs, const BigInteger &rhs) { return lhs += rhs; }
    friend BigInteger operator-(BigInteger lhs, const BigInteger &rhs) { return lhs -= rhs; }
    friend BigInteger operator*(BigInteger lhs, const BigInteger &rhs) { return lhs *= rhs; }
    friend BigInteger operator/(BigInteger lhs, const BigInteger &rhs) { return lhs /= rhs; }
    friend BigInteger operator%(BigInteger lhs, const BigInteger &rhs) { return lhs %= rhs; }
    friend BigInteger operator<<(BigInteger lhs, int bits) { return lhs <<= bits; }
    friend BigInteger operator>>(BigInteger lhs, int bits) { return lhs >>= bits; }

    friend bool operator==(const BigInteger &a, const BigInteger &b) { return compare(a, b) == 0; }
    friend bool operator!=(const BigInteger &a, const BigInteger &b) { return compare(a, b) != 0; }
    friend bool operator<(const BigInteger &a, const BigInteger &b) { return compare(a, b) < 0; }
    friend bool operator<=(const BigInteger &a, const BigInteger &b) { return compare(a, b) <= 0; }
    friend bool operator>(const BigInteger &a, const BigInteger &b) { return compare(a, b) > 0; }
    friend bool operator>=(const BigInteger &a, const BigInteger &b) { return compare(a, b) >= 0; }
};

#endif

/**
 * @brief 多倍長整数(BigInteger)
 */
