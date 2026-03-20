#ifndef FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP
#define FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP

namespace BigIntegerExactConvolution {
    using u32 = unsigned int;
    using u64 = unsigned long long;

    constexpr int NAIVE_THRESHOLD = 128;

    template <u32 MOD, u32 PRIMITIVE_ROOT>
    struct ModInt {
        u32 val;
        ModInt() : val(0) {}
        template <class T>
        ModInt(T v) {
            long long x = (long long)(v % (long long)MOD);
            if (x < 0) x += MOD;
            val = (u32)x;
        }
        static ModInt raw(u32 v) {
            ModInt x;
            x.val = v;
            return x;
        }
        ModInt &operator+=(const ModInt &rhs) {
            val += rhs.val;
            if (val >= MOD) val -= MOD;
            return *this;
        }
        ModInt &operator-=(const ModInt &rhs) {
            val -= rhs.val;
            if (val >= MOD) val += MOD;
            return *this;
        }
        ModInt &operator*=(const ModInt &rhs) {
            val = (u32)((u64)val * rhs.val % MOD);
            return *this;
        }
        ModInt pow(long long n) const {
            ModInt x = *this, r = 1;
            while (n) {
                if (n & 1) r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        ModInt inv() const { return pow(MOD - 2); }
        friend ModInt operator+(ModInt lhs, const ModInt &rhs) { return lhs += rhs; }
        friend ModInt operator-(ModInt lhs, const ModInt &rhs) { return lhs -= rhs; }
        friend ModInt operator*(ModInt lhs, const ModInt &rhs) { return lhs *= rhs; }
    };

    template <u32 MOD, u32 PRIMITIVE_ROOT>
    struct NTT {
        using mint = ModInt<MOD, PRIMITIVE_ROOT>;
        mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30], inv_pow2[30];
        int max_base;

        NTT() : max_base(__builtin_ctz(MOD - 1)) {
            mint e = mint(PRIMITIVE_ROOT).pow((MOD - 1) >> max_base), ie = e.inv();
            for (int i = max_base; i >= 0; --i) {
                root[i] = e;
                iroot[i] = ie;
                e *= e;
                ie *= ie;
            }
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= max_base - 2; ++i) {
                rate2[i] = root[i + 2] * prod;
                irate2[i] = iroot[i + 2] * iprod;
                prod *= iroot[i + 2];
                iprod *= root[i + 2];
            }
            prod = 1;
            iprod = 1;
            for (int i = 0; i <= max_base - 3; ++i) {
                rate3[i] = root[i + 3] * prod;
                irate3[i] = iroot[i + 3] * iprod;
                prod *= iroot[i + 3];
                iprod *= root[i + 3];
            }
            inv_pow2[0] = 1;
            mint inv2 = mint(2).inv();
            for (int i = 1; i < 30; ++i) inv_pow2[i] = inv_pow2[i - 1] * inv2;
        }

        mint inv_size(int n) const {
            return inv_pow2[__builtin_ctz((unsigned int)n)];
        }

        void transform(vector<mint> &a, bool invert) const {
            int n = (int)a.size();
            assert(n > 0);
            assert((n & (n - 1)) == 0);
            assert(__builtin_ctz((unsigned int)n) <= max_base);
            int h = __builtin_ctz((unsigned int)n);
            if (!invert) {
                int len = 0;
                while (len < h) {
                    if (h - len == 1) {
                        int p = 1 << (h - len - 1);
                        mint rot = 1;
                        for (int s = 0; s < (1 << len); ++s) {
                            int offset = s << (h - len);
                            for (int i = 0; i < p; ++i) {
                                mint l = a[i + offset];
                                mint r = a[i + offset + p] * rot;
                                a[i + offset] = l + r;
                                a[i + offset + p] = l - r;
                            }
                            if (s + 1 != (1 << len)) {
                                rot *= rate2[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        ++len;
                    } else {
                        int p = 1 << (h - len - 2);
                        mint rot = 1, imag = root[2];
                        u64 mod2 = (u64)MOD * MOD;
                        for (int s = 0; s < (1 << len); ++s) {
                            mint rot2 = rot * rot;
                            mint rot3 = rot2 * rot;
                            int offset = s << (h - len);
                            for (int i = 0; i < p; ++i) {
                                u64 a0 = a[i + offset].val;
                                u64 a1 = (u64)a[i + offset + p].val * rot.val;
                                u64 a2 = (u64)a[i + offset + 2 * p].val * rot2.val;
                                u64 a3 = (u64)a[i + offset + 3 * p].val * rot3.val;
                                u64 a1na3imag = (u64)mint(a1 + mod2 - a3).val * imag.val;
                                u64 na2 = mod2 - a2;
                                a[i + offset] = mint(a0 + a2 + a1 + a3);
                                a[i + offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));
                                a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);
                                a[i + offset + 3 * p] = mint(a0 + na2 + (mod2 - a1na3imag));
                            }
                            if (s + 1 != (1 << len)) {
                                rot *= rate3[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        len += 2;
                    }
                }
            } else {
                int len = h;
                while (len) {
                    if (len == 1) {
                        int p = 1 << (h - len);
                        mint irot = 1;
                        for (int s = 0; s < (1 << (len - 1)); ++s) {
                            int offset = s << (h - len + 1);
                            for (int i = 0; i < p; ++i) {
                                mint l = a[i + offset];
                                mint r = a[i + offset + p];
                                a[i + offset] = l + r;
                                a[i + offset + p] = mint((u64)(MOD + l.val - r.val) * irot.val);
                            }
                            if (s + 1 != (1 << (len - 1))) {
                                irot *= irate2[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        --len;
                    } else {
                        int p = 1 << (h - len);
                        mint irot = 1, iimag = iroot[2];
                        for (int s = 0; s < (1 << (len - 2)); ++s) {
                            mint irot2 = irot * irot;
                            mint irot3 = irot2 * irot;
                            int offset = s << (h - len + 2);
                            for (int i = 0; i < p; ++i) {
                                u64 a0 = a[i + offset].val;
                                u64 a1 = a[i + offset + p].val;
                                u64 a2 = a[i + offset + 2 * p].val;
                                u64 a3 = a[i + offset + 3 * p].val;
                                u64 a2na3iimag = (u64)mint((u64)(MOD + a2 - a3) * iimag.val).val;
                                a[i + offset] = mint(a0 + a1 + a2 + a3);
                                a[i + offset + p] = mint(a0 + (MOD - a1) + a2na3iimag) * irot;
                                a[i + offset + 2 * p] = mint(a0 + a1 + (MOD - a2) + (MOD - a3)) * irot2;
                                a[i + offset + 3 * p] = mint(a0 + (MOD - a1) + (MOD - a2na3iimag)) * irot3;
                            }
                            if (s + 1 != (1 << (len - 2))) {
                                irot *= irate3[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        len -= 2;
                    }
                }
            }
        }
    };

    using NTT1 = NTT<998244353u, 3u>;
    using NTT2 = NTT<1004535809u, 3u>;

    inline const NTT1 &ntt1() {
        static const NTT1 value;
        return value;
    }

    inline const NTT2 &ntt2() {
        static const NTT2 value;
        return value;
    }

    inline u64 combine_u64(u32 x1, u32 x2) {
        static constexpr u64 m1 = 998244353ULL;
        static constexpr u64 m2 = 1004535809ULL;
        static const u64 m1_inv_m2 = ModInt<1004535809u, 3u>(m1).inv().val;
        u64 t = (x2 + m2 - (x1 % m2)) % m2;
        u64 k = t * m1_inv_m2 % m2;
        return x1 + m1 * k;
    }

    inline vector<u64> convolution_u64(const vector<u32> &a, const vector<u32> &b) {
        if (a.empty() || b.empty()) return {};
        if ((int)min(a.size(), b.size()) <= NAIVE_THRESHOLD) {
            vector<u64> res(a.size() + b.size() - 1, 0);
            for (size_t i = 0; i < a.size(); ++i) {
                for (size_t j = 0; j < b.size(); ++j) {
                    res[i + j] += (u64)a[i] * b[j];
                }
            }
            return res;
        }
        int need = (int)a.size() + (int)b.size() - 1;
        int n = 1;
        while (n < need) n <<= 1;

        vector<typename NTT1::mint> a1(n), b1(n);
        vector<typename NTT2::mint> a2(n), b2(n);
        for (int i = 0; i < (int)a.size(); ++i) {
            a1[i] = a[i];
            a2[i] = a[i];
        }
        for (int i = 0; i < (int)b.size(); ++i) {
            b1[i] = b[i];
            b2[i] = b[i];
        }
        ntt1().transform(a1, false);
        ntt1().transform(b1, false);
        ntt2().transform(a2, false);
        ntt2().transform(b2, false);
        for (int i = 0; i < n; ++i) {
            a1[i] *= b1[i];
            a2[i] *= b2[i];
        }
        ntt1().transform(a1, true);
        ntt2().transform(a2, true);
        typename NTT1::mint inv1 = ntt1().inv_size(n);
        typename NTT2::mint inv2 = ntt2().inv_size(n);
        vector<u64> res(need);
        for (int i = 0; i < need; ++i) {
            res[i] = combine_u64((a1[i] * inv1).val, (a2[i] * inv2).val);
        }
        return res;
    }
}

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
    static constexpr int DEC_ASSIGN_LINEAR_BLOCK_THRESHOLD = 256;
    static constexpr int DEC_TO_STRING_LINEAR_LIMB_THRESHOLD = 256;
    static constexpr int MUL_SCHOOLBOOK_LIMB_THRESHOLD = 32;
    static constexpr int MUL_SCHOOLBOOK_AREA_THRESHOLD = 2048;
    static constexpr int BURNIKEL_ZIEGLER_THRESHOLD = 80;
    static constexpr int BURNIKEL_ZIEGLER_OFFSET = 40;

    mutable vector<u32> d;
    int sign;
    mutable string dec;
    mutable bool binary_ready;
    mutable bool decimal_ready;

    BigInteger() : d(), sign(0), dec(), binary_ready(true), decimal_ready(false) {}
    BigInteger(long long x) { *this = x; }
    BigInteger(const string &s, int base = 10) { assign(s, base); }

    BigInteger &operator=(long long x) {
        d.clear();
        dec.clear();
        decimal_ready = false;
        binary_ready = true;
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

    void invalidate_decimal() {
        dec.clear();
        decimal_ready = false;
    }

    static int compare_abs_decimal(const string &a, const string &b) {
        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
        if (a == b) return 0;
        return a < b ? -1 : 1;
    }

    static string add_abs_decimal(const string &a, const string &b) {
        string res(max(a.size(), b.size()) + 1, '0');
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int k = (int)res.size() - 1;
        int carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int x = carry;
            if (i >= 0) x += a[i--] - '0';
            if (j >= 0) x += b[j--] - '0';
            res[k--] = char('0' + (x % 10));
            carry = x / 10;
        }
        while (i >= 0) res[k--] = a[i--];
        while (j >= 0) res[k--] = b[j--];
        return res.substr(k + 1);
    }

    static string sub_abs_decimal(const string &a, const string &b) {
        string res(a.size(), '0');
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int borrow = 0;
        for (int k = (int)res.size() - 1; k >= 0; --k, --i, --j) {
            int x = (a[i] - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);
            if (x < 0) {
                x += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res[k] = char('0' + x);
        }
        int p = 0;
        while (p + 1 < (int)res.size() && res[p] == '0') ++p;
        return res.substr(p);
    }

    static vector<u32> split_decimal_blocks(const string &s) {
        vector<u32> blocks;
        if (s.empty()) return blocks;
        int block_count = ((int)s.size() + DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;
        blocks.reserve(block_count);
        int first = (int)s.size() % DEC_BLOCK_DIGITS;
        if (first == 0) first = DEC_BLOCK_DIGITS;
        for (int i = 0; i < (int)s.size(); ) {
            int width = blocks.empty() ? first : DEC_BLOCK_DIGITS;
            int r = min((int)s.size(), i + width);
            u32 x = 0;
            for (int j = i; j < r; ++j) x = x * 10 + u32(s[j] - '0');
            blocks.push_back(x);
            i = r;
        }
        return blocks;
    }

    static vector<u32> split_decimal_blocks_le(const string &s, int block_digits) {
        vector<u32> blocks;
        if (s.empty()) return blocks;
        int block_count = ((int)s.size() + block_digits - 1) / block_digits;
        blocks.reserve(block_count);
        for (int r = (int)s.size(); r > 0; r -= block_digits) {
            int l = max(0, r - block_digits);
            u32 x = 0;
            for (int i = l; i < r; ++i) x = x * 10 + u32(s[i] - '0');
            blocks.push_back(x);
        }
        return blocks;
    }

    template <class T>
    static void ensure_pow_cache_size(vector<T> &cache, vector<char> &ready, int n) {
        if ((int)cache.size() > n) return;
        cache.resize(n + 1);
        ready.resize(n + 1, 0);
    }

    static string build_decimal_string(const vector<u32> &parts, int block_digits, bool negative) {
        string res;
        res.reserve((negative ? 1 : 0) + decimal_digits_u32(parts.back()) +
                    max(0, (int)parts.size() - 1) * block_digits);
        if (negative) res.push_back('-');
        append_u32_decimal(res, parts.back());
        for (int i = (int)parts.size() - 2; i >= 0; --i) {
            append_u32_decimal_padded(res, parts[i], block_digits);
        }
        return res;
    }

    void ensure_binary() const {
        if (binary_ready) return;
        d.clear();
        if (sign == 0) {
            binary_ready = true;
            return;
        }
        vector<u32> blocks = split_decimal_blocks(dec);
        int block_count = (int)blocks.size();
        if (block_count <= DEC_ASSIGN_LINEAR_BLOCK_THRESHOLD) {
            BigInteger tmp;
            tmp.sign = 1;
            tmp.d.clear();
            tmp.binary_ready = true;
            tmp.decimal_ready = false;
            for (u32 x : blocks) {
                tmp.mul_small_assign(DEC_BLOCK);
                tmp.add_small_assign(x);
            }
            d = std::move(tmp.d);
        } else {
            BigInteger tmp = from_decimal_blocks(blocks, 0, (int)blocks.size());
            d = std::move(tmp.d);
        }
        binary_ready = true;
    }

    bool is_zero() const { return sign == 0; }

    int bit_length() const {
        if (is_zero()) return 0;
        ensure_binary();
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
        ensure_pow_cache_size(cache, ready, blocks);
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
        auto conv = BigIntegerExactConvolution::convolution_u64(a, b);
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
        ensure_pow_cache_size(cache, ready, limbs);
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

    static int decimal_digits_u32(u32 x) {
        if (x >= 1000000000u) return 10;
        if (x >= 100000000u) return 9;
        if (x >= 10000000u) return 8;
        if (x >= 1000000u) return 7;
        if (x >= 100000u) return 6;
        if (x >= 10000u) return 5;
        if (x >= 1000u) return 4;
        if (x >= 100u) return 3;
        if (x >= 10u) return 2;
        return 1;
    }

    static void append_u32_decimal(string &res, u32 x) {
        char buf[10];
        int pos = 10;
        do {
            buf[--pos] = char('0' + (x % 10));
            x /= 10;
        } while (x);
        res.append(buf + pos, buf + 10);
    }

    static void append_u32_decimal_padded(string &res, u32 x, int width) {
        char buf[10];
        for (int i = width - 1; i >= 0; --i) {
            buf[i] = char('0' + (x % 10));
            x /= 10;
        }
        res.append(buf, buf + width);
    }

    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
        if (d.empty()) sign = 0;
    }

    int compare_abs(const BigInteger &other) const {
        if (decimal_ready && other.decimal_ready) return compare_abs_decimal(dec, other.dec);
        ensure_binary();
        other.ensure_binary();
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
        ensure_binary();
        other.ensure_binary();
        invalidate_decimal();
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
        ensure_binary();
        other.ensure_binary();
        invalidate_decimal();
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
        ensure_binary();
        invalidate_decimal();
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
        ensure_binary();
        invalidate_decimal();
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
        ensure_binary();
        invalidate_decimal();
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
        ensure_binary();
        invalidate_decimal();
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
        ensure_binary();
        invalidate_decimal();
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
        a.ensure_binary();
        b.ensure_binary();
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
        a.ensure_binary();
        b.ensure_binary();
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
        auto conv = BigIntegerExactConvolution::convolution_u64(x, y);
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
        if (a.decimal_ready && b.decimal_ready) {
            if (a.is_zero() || b.is_zero()) return BigInteger();
            vector<u32> x = split_decimal_blocks_le(a.dec, DEC_CONV_DIGITS);
            vector<u32> y = split_decimal_blocks_le(b.dec, DEC_CONV_DIGITS);
            vector<u32> parts = mul_decimal_vectors(x, y);
            BigInteger res;
            if (parts.empty()) return res;
            res.sign = a.sign * b.sign;
            res.dec = build_decimal_string(parts, DEC_CONV_DIGITS, false);
            res.binary_ready = false;
            res.decimal_ready = true;
            return res;
        }
        a.ensure_binary();
        b.ensure_binary();
        if (a.is_zero() || b.is_zero()) return BigInteger();
        BigInteger res;
        size_t n = a.d.size(), m = b.d.size();
        if (min(n, m) <= MUL_SCHOOLBOOK_LIMB_THRESHOLD || n * m <= MUL_SCHOOLBOOK_AREA_THRESHOLD) {
            res = mul_schoolbook(a, b);
        }
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

    static BigInteger from_limbs(vector<u32> limbs) {
        BigInteger res;
        res.d = std::move(limbs);
        while (!res.d.empty() && res.d.back() == 0) res.d.pop_back();
        res.sign = res.d.empty() ? 0 : 1;
        res.binary_ready = true;
        res.decimal_ready = false;
        return res;
    }

    static BigInteger lower_limbs(const BigInteger &x, int limbs) {
        x.ensure_binary();
        if (limbs <= 0 || x.d.empty()) return BigInteger();
        int len = min((int)x.d.size(), limbs);
        return from_limbs(vector<u32>(x.d.begin(), x.d.begin() + len));
    }

    static BigInteger upper_limbs(const BigInteger &x, int limbs) {
        x.ensure_binary();
        if (limbs <= 0) return x;
        if (limbs >= (int)x.d.size()) return BigInteger();
        return from_limbs(vector<u32>(x.d.begin() + limbs, x.d.end()));
    }

    static BigInteger shift_left_limbs(const BigInteger &x, int limbs) {
        x.ensure_binary();
        if (x.is_zero() || limbs <= 0) return x;
        vector<u32> res;
        res.reserve((size_t)limbs + x.d.size());
        res.insert(res.end(), (size_t)limbs, 0);
        res.insert(res.end(), x.d.begin(), x.d.end());
        return from_limbs(std::move(res));
    }

    static BigInteger ones_limbs(int limbs) {
        if (limbs <= 0) return BigInteger();
        return from_limbs(vector<u32>((size_t)limbs, BASE_MASK));
    }

    static BigInteger get_block(const BigInteger &x, int index, int num_blocks, int block_length) {
        x.ensure_binary();
        int block_start = index * block_length;
        if (block_start >= (int)x.d.size()) return BigInteger();
        int block_end = index == num_blocks - 1 ? (int)x.d.size() : (index + 1) * block_length;
        if (block_end > (int)x.d.size()) return BigInteger();
        return from_limbs(vector<u32>(x.d.begin() + block_start, x.d.begin() + block_end));
    }

    static void add_shifted_abs(BigInteger &dst, const BigInteger &src, int limb_shift) {
        dst.ensure_binary();
        src.ensure_binary();
        dst.invalidate_decimal();
        if (src.is_zero()) return;
        size_t need = src.d.size() + (size_t)limb_shift;
        if (dst.d.size() < need) dst.d.resize(need, 0);
        u64 carry = 0;
        size_t i = 0;
        for (; i < src.d.size(); ++i) {
            u64 cur = u64(dst.d[i + limb_shift]) + src.d[i] + carry;
            dst.d[i + limb_shift] = u32(cur);
            carry = cur >> 32;
        }
        size_t pos = i + limb_shift;
        while (carry) {
            if (pos == dst.d.size()) dst.d.push_back(0);
            u64 cur = u64(dst.d[pos]) + carry;
            dst.d[pos] = u32(cur);
            carry = cur >> 32;
            ++pos;
        }
        dst.sign = 1;
    }

    static void add_disjoint_abs(BigInteger &dst, const BigInteger &src, int limb_shift) {
        dst.ensure_binary();
        src.ensure_binary();
        dst.invalidate_decimal();
        if (src.is_zero()) return;
        size_t need = max(dst.d.size(), src.d.size() + (size_t)limb_shift);
        if (dst.d.size() < need) dst.d.resize(need, 0);
        for (size_t i = 0; i < src.d.size(); ++i) dst.d[i + limb_shift] = src.d[i];
        dst.trim();
        if (!dst.is_zero()) dst.sign = 1;
    }

    static void sub_one_abs(BigInteger &x) {
        x.ensure_binary();
        x.invalidate_decimal();
        for (size_t i = 0; i < x.d.size(); ++i) {
            if (x.d[i] != 0) {
                --x.d[i];
                break;
            }
            x.d[i] = BASE_MASK;
        }
        x.trim();
    }

    static int compare_shifted_abs(const BigInteger &a, const BigInteger &b, int limb_shift) {
        a.ensure_binary();
        b.ensure_binary();
        int as = (int)a.d.size() - limb_shift;
        int bs = (int)b.d.size();
        if (as != bs) return as < bs ? -1 : 1;
        for (int i = as - 1; i >= 0; --i) {
            if (a.d[i + limb_shift] != b.d[i]) return a.d[i + limb_shift] < b.d[i] ? -1 : 1;
        }
        return 0;
    }

    static BigInteger divmod_knuth_abs(const BigInteger &u0, const BigInteger &v0, BigInteger &rem) {
        u0.ensure_binary();
        v0.ensure_binary();
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

    static BigInteger divide3n2n_abs(const BigInteger &a, const BigInteger &b, BigInteger &quotient) {
        int n = (int)b.d.size() / 2;
        BigInteger a12 = upper_limbs(a, n);
        BigInteger b1 = upper_limbs(b, n);
        BigInteger b2 = lower_limbs(b, n);
        BigInteger r, d;
        if (compare_shifted_abs(a, b, n) < 0) {
            r = divide2n1n_abs(a12, b1, quotient);
            d = multiply(quotient, b2);
            d.sign = d.is_zero() ? 0 : 1;
        } else {
            quotient = ones_limbs(n);
            a12.add_abs(b1);
            a12.sub_abs(shift_left_limbs(b1, n));
            r = a12;
            d = shift_left_limbs(b2, n);
            if (!b2.is_zero()) d.sub_abs(b2);
        }
        r = shift_left_limbs(r, n);
        r.add_abs(lower_limbs(a, n));
        while (r.compare_abs(d) < 0) {
            r.add_abs(b);
            sub_one_abs(quotient);
        }
        r.sub_abs(d);
        return r;
    }

    static BigInteger divide2n1n_abs(const BigInteger &a, const BigInteger &b, BigInteger &quotient) {
        int n = (int)b.d.size();
        if ((n & 1) || n < BURNIKEL_ZIEGLER_THRESHOLD) {
            BigInteger rem;
            quotient = divmod_knuth_abs(a, b, rem);
            return rem;
        }
        int half = n / 2;
        BigInteger a_upper = upper_limbs(a, half);
        BigInteger a_lower = lower_limbs(a, half);
        BigInteger q1;
        BigInteger r1 = divide3n2n_abs(a_upper, b, q1);
        add_disjoint_abs(a_lower, r1, half);
        BigInteger r2 = divide3n2n_abs(a_lower, b, quotient);
        add_disjoint_abs(quotient, q1, half);
        return r2;
    }

    static BigInteger divmod_burnikel_ziegler_abs(const BigInteger &u, const BigInteger &v, BigInteger &quotient) {
        u.ensure_binary();
        v.ensure_binary();
        int r = (int)u.d.size();
        int s = (int)v.d.size();
        quotient = BigInteger();
        if (r < s) return u;

        int m = 1;
        while ((long long)m * BURNIKEL_ZIEGLER_THRESHOLD <= s) m <<= 1;
        int j = (s + m - 1) / m;
        int n = j * m;
        long long n_bits = 32LL * n;
        int sigma = max(0LL, n_bits - v.bit_length());
        BigInteger b_shifted = v;
        BigInteger a_shifted = u;
        if (sigma) {
            b_shifted.shift_left_bits_assign(sigma);
            a_shifted.shift_left_bits_assign(sigma);
        }
        int t = (int)((a_shifted.bit_length() + n_bits) / n_bits);
        if (t < 2) t = 2;

        BigInteger a1 = get_block(a_shifted, t - 1, t, n);
        BigInteger z = get_block(a_shifted, t - 2, t, n);
        add_disjoint_abs(z, a1, n);
        BigInteger qi, ri;
        for (int i = t - 2; i > 0; --i) {
            ri = divide2n1n_abs(z, b_shifted, qi);
            z = get_block(a_shifted, i - 1, t, n);
            add_disjoint_abs(z, ri, n);
            add_shifted_abs(quotient, qi, i * n);
        }
        ri = divide2n1n_abs(z, b_shifted, qi);
        quotient.add_abs(qi);
        quotient.sign = quotient.is_zero() ? 0 : 1;
        if (sigma) ri.shift_right_bits_assign(sigma);
        ri.sign = ri.is_zero() ? 0 : 1;
        return ri;
    }

    static BigInteger divmod_abs(const BigInteger &u0, const BigInteger &v0, BigInteger &rem) {
        u0.ensure_binary();
        v0.ensure_binary();
        if (v0.is_zero()) {
            rem = BigInteger();
            return BigInteger();
        }
        if (u0.compare_abs(v0) < 0) {
            rem = u0;
            return BigInteger();
        }
        if (v0.d.size() == 1) {
            BigInteger q = u0;
            u32 r = q.div_small_assign(v0.d[0]);
            rem = BigInteger(r);
            rem.sign = r == 0 ? 0 : 1;
            q.sign = q.is_zero() ? 0 : 1;
            return q;
        }
        if ((int)v0.d.size() >= BURNIKEL_ZIEGLER_THRESHOLD &&
            (int)u0.d.size() - (int)v0.d.size() >= BURNIKEL_ZIEGLER_OFFSET) {
            BigInteger q;
            divmod_burnikel_ziegler_abs(u0, v0, q);
            BigInteger prod = multiply(q, v0);
            prod.sign = prod.is_zero() ? 0 : 1;
            if (u0.compare_abs(prod) >= 0) {
                rem = u0;
                rem.sub_abs(prod);
                if (rem.compare_abs(v0) < 0) return q;
            }
        }
        return divmod_knuth_abs(u0, v0, rem);
    }

    static pair<BigInteger, BigInteger> divmod_abs(const BigInteger &u, const BigInteger &v) {
        u.ensure_binary();
        v.ensure_binary();
        BigInteger r;
        BigInteger q = divmod_abs(u, v, r);
        return {q, r};
    }

    static pair<BigInteger, BigInteger> divmod(const BigInteger &a, const BigInteger &b) {
        a.ensure_binary();
        b.ensure_binary();
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
        dec.clear();
        binary_ready = true;
        decimal_ready = false;
        sign = 0;
        int p = 0;
        bool neg = false;
        if (p < (int)s.size() && (s[p] == '+' || s[p] == '-')) {
            neg = s[p] == '-';
            ++p;
        }
        while (p < (int)s.size() && s[p] == '0') ++p;
        if (p == (int)s.size()) return;
        int q = p;
        while (q < (int)s.size()) {
            int v = digit_value(s[q]);
            if (v < 0 || v >= base) {
                d.clear();
                sign = 0;
                return;
            }
            ++q;
        }
        if (base == 16) {
            for (int i = (int)s.size(); i > p; ) {
                int l = max(p, i - HEX_BLOCK_DIGITS);
                u32 x = 0;
                for (int j = l; j < i; ++j) {
                    int v = digit_value(s[j]);
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
            dec.assign(s.begin() + p, s.end());
            binary_ready = false;
            decimal_ready = true;
            sign = 1;
            if (neg && !is_zero()) sign = -1;
            return;
        }
        for (; p < (int)s.size(); ++p) {
            int v = digit_value(s[p]);
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
            ensure_binary();
            string res;
            res.reserve((sign < 0 ? 1 : 0) + (int)d.size() * HEX_BLOCK_DIGITS);
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
        if (decimal_ready) {
            string res;
            res.reserve((sign < 0 ? 1 : 0) + dec.size());
            if (sign < 0) res.push_back('-');
            res += dec;
            return res;
        }
        if ((int)d.size() <= DEC_TO_STRING_LINEAR_LIMB_THRESHOLD) {
            BigInteger tmp;
            tmp.sign = 1;
            tmp.d = d;
            tmp.binary_ready = true;
            tmp.decimal_ready = false;
            vector<u32> parts;
            parts.reserve((bit_length() + 28) / 29);
            while (!tmp.is_zero()) parts.push_back(tmp.div_small_assign(DEC_BLOCK));
            return build_decimal_string(parts, DEC_BLOCK_DIGITS, sign < 0);
        }
        vector<u32> parts = limbs_to_decimal(d, 0, (int)d.size());
        return build_decimal_string(parts, DEC_CONV_DIGITS, sign < 0);
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
        if (decimal_ready && rhs.decimal_ready) {
            if (is_zero()) {
                *this = rhs;
                return *this;
            }
            if (sign == rhs.sign) {
                dec = add_abs_decimal(dec, rhs.dec);
            } else {
                int c = compare_abs_decimal(dec, rhs.dec);
                if (c == 0) {
                    dec.clear();
                    decimal_ready = false;
                    sign = 0;
                    binary_ready = true;
                    d.clear();
                    return *this;
                }
                if (c > 0) {
                    dec = sub_abs_decimal(dec, rhs.dec);
                } else {
                    dec = sub_abs_decimal(rhs.dec, dec);
                    sign = rhs.sign;
                }
            }
            d.clear();
            binary_ready = false;
            decimal_ready = true;
            return *this;
        }
        ensure_binary();
        rhs.ensure_binary();
        invalidate_decimal();
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
        BigInteger tmp = rhs;
        tmp.sign = -tmp.sign;
        return *this += tmp;
    }

    BigInteger &operator*=(const BigInteger &rhs) {
        if (is_zero() || rhs.is_zero()) {
            d.clear();
            dec.clear();
            binary_ready = true;
            decimal_ready = false;
            sign = 0;
            return *this;
        }
        BigInteger a = *this;
        BigInteger b = rhs;
        *this = multiply(a, b);
        return *this;
    }

    BigInteger &operator/=(const BigInteger &rhs) {
        ensure_binary();
        rhs.ensure_binary();
        invalidate_decimal();
        *this = divmod(*this, rhs).first;
        return *this;
    }

    BigInteger &operator%=(const BigInteger &rhs) {
        ensure_binary();
        rhs.ensure_binary();
        invalidate_decimal();
        *this = divmod(*this, rhs).second;
        return *this;
    }

    BigInteger &operator<<=(int bits) {
        ensure_binary();
        invalidate_decimal();
        if (bits < 0) return *this >>= -bits;
        if (is_zero()) return *this;
        shift_left_bits_assign(bits);
        return *this;
    }

    BigInteger &operator>>=(int bits) {
        ensure_binary();
        invalidate_decimal();
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
