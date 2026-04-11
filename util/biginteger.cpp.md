---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_addition_of_big_integers.test.cpp
    title: test/yosupo_addition_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_addition_of_hex_big_integers.test.cpp
    title: test/yosupo_addition_of_hex_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_division_of_big_integers.test.cpp
    title: test/yosupo_division_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_division_of_hex_big_integers.test.cpp
    title: test/yosupo_division_of_hex_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_multiplication_of_big_integers.test.cpp
    title: test/yosupo_multiplication_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_multiplication_of_hex_big_integers.test.cpp
    title: test/yosupo_multiplication_of_hex_big_integers.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u500D\u9577\u6574\u6570(BigInteger)"
    links: []
  bundledCode: "#line 1 \"util/biginteger.cpp\"\n\n\n\nnamespace BigIntegerExactConvolution\
    \ {\n    using u32 = unsigned int;\n    using u64 = unsigned long long;\n\n  \
    \  constexpr int NAIVE_THRESHOLD = 128;\n\n    template <u32 MOD, u32 PRIMITIVE_ROOT>\n\
    \    struct ModInt {\n        u32 val;\n        ModInt() : val(0) {}\n       \
    \ template <class T>\n        ModInt(T v) {\n            long long x = (long long)(v\
    \ % (long long)MOD);\n            if (x < 0) x += MOD;\n            val = (u32)x;\n\
    \        }\n        static ModInt raw(u32 v) {\n            ModInt x;\n      \
    \      x.val = v;\n            return x;\n        }\n        ModInt &operator+=(const\
    \ ModInt &rhs) {\n            val += rhs.val;\n            if (val >= MOD) val\
    \ -= MOD;\n            return *this;\n        }\n        ModInt &operator-=(const\
    \ ModInt &rhs) {\n            val -= rhs.val;\n            if (val >= MOD) val\
    \ += MOD;\n            return *this;\n        }\n        ModInt &operator*=(const\
    \ ModInt &rhs) {\n            val = (u32)((u64)val * rhs.val % MOD);\n       \
    \     return *this;\n        }\n        ModInt pow(long long n) const {\n    \
    \        ModInt x = *this, r = 1;\n            while (n) {\n                if\
    \ (n & 1) r *= x;\n                x *= x;\n                n >>= 1;\n       \
    \     }\n            return r;\n        }\n        ModInt inv() const { return\
    \ pow(MOD - 2); }\n        friend ModInt operator+(ModInt lhs, const ModInt &rhs)\
    \ { return lhs += rhs; }\n        friend ModInt operator-(ModInt lhs, const ModInt\
    \ &rhs) { return lhs -= rhs; }\n        friend ModInt operator*(ModInt lhs, const\
    \ ModInt &rhs) { return lhs *= rhs; }\n    };\n\n    template <u32 MOD, u32 PRIMITIVE_ROOT>\n\
    \    struct NTT {\n        using mint = ModInt<MOD, PRIMITIVE_ROOT>;\n       \
    \ mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30], inv_pow2[30];\n\
    \        int max_base;\n\n        NTT() : max_base(__builtin_ctz(MOD - 1)) {\n\
    \            mint e = mint(PRIMITIVE_ROOT).pow((MOD - 1) >> max_base), ie = e.inv();\n\
    \            for (int i = max_base; i >= 0; --i) {\n                root[i] =\
    \ e;\n                iroot[i] = ie;\n                e *= e;\n              \
    \  ie *= ie;\n            }\n            mint prod = 1, iprod = 1;\n         \
    \   for (int i = 0; i <= max_base - 2; ++i) {\n                rate2[i] = root[i\
    \ + 2] * prod;\n                irate2[i] = iroot[i + 2] * iprod;\n          \
    \      prod *= iroot[i + 2];\n                iprod *= root[i + 2];\n        \
    \    }\n            prod = 1;\n            iprod = 1;\n            for (int i\
    \ = 0; i <= max_base - 3; ++i) {\n                rate3[i] = root[i + 3] * prod;\n\
    \                irate3[i] = iroot[i + 3] * iprod;\n                prod *= iroot[i\
    \ + 3];\n                iprod *= root[i + 3];\n            }\n            inv_pow2[0]\
    \ = 1;\n            mint inv2 = mint(2).inv();\n            for (int i = 1; i\
    \ < 30; ++i) inv_pow2[i] = inv_pow2[i - 1] * inv2;\n        }\n\n        mint\
    \ inv_size(int n) const {\n            return inv_pow2[__builtin_ctz((unsigned\
    \ int)n)];\n        }\n\n        void transform(vector<mint> &a, bool invert)\
    \ const {\n            int n = (int)a.size();\n            assert(n > 0);\n  \
    \          assert((n & (n - 1)) == 0);\n            assert(__builtin_ctz((unsigned\
    \ int)n) <= max_base);\n            int h = __builtin_ctz((unsigned int)n);\n\
    \            if (!invert) {\n                int len = 0;\n                while\
    \ (len < h) {\n                    if (h - len == 1) {\n                     \
    \   int p = 1 << (h - len - 1);\n                        mint rot = 1;\n     \
    \                   for (int s = 0; s < (1 << len); ++s) {\n                 \
    \           int offset = s << (h - len);\n                            for (int\
    \ i = 0; i < p; ++i) {\n                                mint l = a[i + offset];\n\
    \                                mint r = a[i + offset + p] * rot;\n         \
    \                       a[i + offset] = l + r;\n                             \
    \   a[i + offset + p] = l - r;\n                            }\n              \
    \              if (s + 1 != (1 << len)) {\n                                rot\
    \ *= rate2[__builtin_ctz(~(unsigned int)s)];\n                            }\n\
    \                        }\n                        ++len;\n                 \
    \   } else {\n                        int p = 1 << (h - len - 2);\n          \
    \              mint rot = 1, imag = root[2];\n                        u64 mod2\
    \ = (u64)MOD * MOD;\n                        for (int s = 0; s < (1 << len); ++s)\
    \ {\n                            mint rot2 = rot * rot;\n                    \
    \        mint rot3 = rot2 * rot;\n                            int offset = s <<\
    \ (h - len);\n                            for (int i = 0; i < p; ++i) {\n    \
    \                            u64 a0 = a[i + offset].val;\n                   \
    \             u64 a1 = (u64)a[i + offset + p].val * rot.val;\n               \
    \                 u64 a2 = (u64)a[i + offset + 2 * p].val * rot2.val;\n      \
    \                          u64 a3 = (u64)a[i + offset + 3 * p].val * rot3.val;\n\
    \                                u64 a1na3imag = (u64)mint(a1 + mod2 - a3).val\
    \ * imag.val;\n                                u64 na2 = mod2 - a2;\n        \
    \                        a[i + offset] = mint(a0 + a2 + a1 + a3);\n          \
    \                      a[i + offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));\n\
    \                                a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);\n\
    \                                a[i + offset + 3 * p] = mint(a0 + na2 + (mod2\
    \ - a1na3imag));\n                            }\n                            if\
    \ (s + 1 != (1 << len)) {\n                                rot *= rate3[__builtin_ctz(~(unsigned\
    \ int)s)];\n                            }\n                        }\n       \
    \                 len += 2;\n                    }\n                }\n      \
    \      } else {\n                int len = h;\n                while (len) {\n\
    \                    if (len == 1) {\n                        int p = 1 << (h\
    \ - len);\n                        mint irot = 1;\n                        for\
    \ (int s = 0; s < (1 << (len - 1)); ++s) {\n                            int offset\
    \ = s << (h - len + 1);\n                            for (int i = 0; i < p; ++i)\
    \ {\n                                mint l = a[i + offset];\n               \
    \                 mint r = a[i + offset + p];\n                              \
    \  a[i + offset] = l + r;\n                                a[i + offset + p] =\
    \ mint((u64)(MOD + l.val - r.val) * irot.val);\n                            }\n\
    \                            if (s + 1 != (1 << (len - 1))) {\n              \
    \                  irot *= irate2[__builtin_ctz(~(unsigned int)s)];\n        \
    \                    }\n                        }\n                        --len;\n\
    \                    } else {\n                        int p = 1 << (h - len);\n\
    \                        mint irot = 1, iimag = iroot[2];\n                  \
    \      for (int s = 0; s < (1 << (len - 2)); ++s) {\n                        \
    \    mint irot2 = irot * irot;\n                            mint irot3 = irot2\
    \ * irot;\n                            int offset = s << (h - len + 2);\n    \
    \                        for (int i = 0; i < p; ++i) {\n                     \
    \           u64 a0 = a[i + offset].val;\n                                u64 a1\
    \ = a[i + offset + p].val;\n                                u64 a2 = a[i + offset\
    \ + 2 * p].val;\n                                u64 a3 = a[i + offset + 3 * p].val;\n\
    \                                u64 a2na3iimag = (u64)mint((u64)(MOD + a2 - a3)\
    \ * iimag.val).val;\n                                a[i + offset] = mint(a0 +\
    \ a1 + a2 + a3);\n                                a[i + offset + p] = mint(a0\
    \ + (MOD - a1) + a2na3iimag) * irot;\n                                a[i + offset\
    \ + 2 * p] = mint(a0 + a1 + (MOD - a2) + (MOD - a3)) * irot2;\n              \
    \                  a[i + offset + 3 * p] = mint(a0 + (MOD - a1) + (MOD - a2na3iimag))\
    \ * irot3;\n                            }\n                            if (s +\
    \ 1 != (1 << (len - 2))) {\n                                irot *= irate3[__builtin_ctz(~(unsigned\
    \ int)s)];\n                            }\n                        }\n       \
    \                 len -= 2;\n                    }\n                }\n      \
    \      }\n        }\n    };\n\n    using NTT1 = NTT<998244353u, 3u>;\n    using\
    \ NTT2 = NTT<1004535809u, 3u>;\n\n    inline const NTT1 &ntt1() {\n        static\
    \ const NTT1 value;\n        return value;\n    }\n\n    inline const NTT2 &ntt2()\
    \ {\n        static const NTT2 value;\n        return value;\n    }\n\n    inline\
    \ u64 combine_u64(u32 x1, u32 x2) {\n        static constexpr u64 m1 = 998244353ULL;\n\
    \        static constexpr u64 m2 = 1004535809ULL;\n        static const u64 m1_inv_m2\
    \ = ModInt<1004535809u, 3u>(m1).inv().val;\n        u64 t = (x2 + m2 - (x1 % m2))\
    \ % m2;\n        u64 k = t * m1_inv_m2 % m2;\n        return x1 + m1 * k;\n  \
    \  }\n\n    inline vector<u64> convolution_u64(const vector<u32> &a, const vector<u32>\
    \ &b) {\n        if (a.empty() || b.empty()) return {};\n        if ((int)min(a.size(),\
    \ b.size()) <= NAIVE_THRESHOLD) {\n            vector<u64> res(a.size() + b.size()\
    \ - 1, 0);\n            for (size_t i = 0; i < a.size(); ++i) {\n            \
    \    for (size_t j = 0; j < b.size(); ++j) {\n                    res[i + j] +=\
    \ (u64)a[i] * b[j];\n                }\n            }\n            return res;\n\
    \        }\n        int need = (int)a.size() + (int)b.size() - 1;\n        int\
    \ n = 1;\n        while (n < need) n <<= 1;\n\n        vector<typename NTT1::mint>\
    \ a1(n), b1(n);\n        vector<typename NTT2::mint> a2(n), b2(n);\n        for\
    \ (int i = 0; i < (int)a.size(); ++i) {\n            a1[i] = a[i];\n         \
    \   a2[i] = a[i];\n        }\n        for (int i = 0; i < (int)b.size(); ++i)\
    \ {\n            b1[i] = b[i];\n            b2[i] = b[i];\n        }\n       \
    \ ntt1().transform(a1, false);\n        ntt1().transform(b1, false);\n       \
    \ ntt2().transform(a2, false);\n        ntt2().transform(b2, false);\n       \
    \ for (int i = 0; i < n; ++i) {\n            a1[i] *= b1[i];\n            a2[i]\
    \ *= b2[i];\n        }\n        ntt1().transform(a1, true);\n        ntt2().transform(a2,\
    \ true);\n        typename NTT1::mint inv1 = ntt1().inv_size(n);\n        typename\
    \ NTT2::mint inv2 = ntt2().inv_size(n);\n        vector<u64> res(need);\n    \
    \    for (int i = 0; i < need; ++i) {\n            res[i] = combine_u64((a1[i]\
    \ * inv1).val, (a2[i] * inv2).val);\n        }\n        return res;\n    }\n}\n\
    \nstruct BigInteger {\n    using u32 = unsigned int;\n    using u64 = unsigned\
    \ long long;\n    using u128 = __uint128_t;\n\n    static constexpr u64 BASE =\
    \ 1ULL << 32;\n    static constexpr u32 BASE_MASK = 0xffffffffu;\n    static constexpr\
    \ u32 DEC_BLOCK = 1000000000u;\n    static constexpr int DEC_BLOCK_DIGITS = 9;\n\
    \    static constexpr u64 FAST_DEC_BASE = 10000000000000000ULL;\n    static constexpr\
    \ int FAST_DEC_BLOCK_DIGITS = 16;\n    static constexpr u32 FAST_DEC_META_BASE\
    \ = 10000u;\n    static constexpr int FAST_DEC_META_DIGITS = 4;\n    static constexpr\
    \ u32 DEC_CONV_BASE = 1000000u;\n    static constexpr int DEC_CONV_DIGITS = 6;\n\
    \    static constexpr int HEX_BLOCK_DIGITS = 8;\n    static constexpr int DEC_ASSIGN_LINEAR_BLOCK_THRESHOLD\
    \ = 256;\n    static constexpr int DEC_TO_STRING_LINEAR_LIMB_THRESHOLD = 256;\n\
    \    static constexpr int MUL_SCHOOLBOOK_LIMB_THRESHOLD = 32;\n    static constexpr\
    \ int MUL_SCHOOLBOOK_AREA_THRESHOLD = 262144;\n    static constexpr int BURNIKEL_ZIEGLER_THRESHOLD\
    \ = 64;\n    static constexpr int BURNIKEL_ZIEGLER_OFFSET = 32;\n\n    mutable\
    \ vector<u32> d;\n    int sign;\n    mutable string dec;\n    mutable bool binary_ready;\n\
    \    mutable bool decimal_ready;\n\n    BigInteger() : d(), sign(0), dec(), binary_ready(true),\
    \ decimal_ready(false) {}\n    BigInteger(long long x) { *this = x; }\n    BigInteger(const\
    \ string &s, int base = 10) { assign(s, base); }\n\n    BigInteger &operator=(long\
    \ long x) {\n        d.clear();\n        dec.clear();\n        decimal_ready =\
    \ false;\n        binary_ready = true;\n        if (x == 0) {\n            sign\
    \ = 0;\n            return *this;\n        }\n        sign = x < 0 ? -1 : 1;\n\
    \        u64 y;\n        if (x < 0) y = u64(-(x + 1)) + 1;\n        else y = u64(x);\n\
    \        while (y) {\n            d.push_back(u32(y & BASE_MASK));\n         \
    \   y >>= 32;\n        }\n        return *this;\n    }\n\n    static int digit_value(char\
    \ c) {\n        if ('0' <= c && c <= '9') return c - '0';\n        if ('a' <=\
    \ c && c <= 'z') return c - 'a' + 10;\n        if ('A' <= c && c <= 'Z') return\
    \ c - 'A' + 10;\n        return -1;\n    }\n\n    static char digit_char(int x)\
    \ {\n        return x < 10 ? char('0' + x) : char('a' + (x - 10));\n    }\n\n\
    \    void invalidate_decimal() {\n        dec.clear();\n        decimal_ready\
    \ = false;\n    }\n\n    static int compare_abs_decimal(const string &a, const\
    \ string &b) {\n        if (a.size() != b.size()) return a.size() < b.size() ?\
    \ -1 : 1;\n        if (a == b) return 0;\n        return a < b ? -1 : 1;\n   \
    \ }\n\n    static string add_abs_decimal(const string &a, const string &b) {\n\
    \        string res(max(a.size(), b.size()) + 1, '0');\n        int i = (int)a.size()\
    \ - 1;\n        int j = (int)b.size() - 1;\n        int k = (int)res.size() -\
    \ 1;\n        int carry = 0;\n        while (i >= 0 || j >= 0 || carry) {\n  \
    \          int x = carry;\n            if (i >= 0) x += a[i--] - '0';\n      \
    \      if (j >= 0) x += b[j--] - '0';\n            res[k--] = char('0' + (x %\
    \ 10));\n            carry = x / 10;\n        }\n        while (i >= 0) res[k--]\
    \ = a[i--];\n        while (j >= 0) res[k--] = b[j--];\n        return res.substr(k\
    \ + 1);\n    }\n\n    static string sub_abs_decimal(const string &a, const string\
    \ &b) {\n        string res(a.size(), '0');\n        int i = (int)a.size() - 1;\n\
    \        int j = (int)b.size() - 1;\n        int borrow = 0;\n        for (int\
    \ k = (int)res.size() - 1; k >= 0; --k, --i, --j) {\n            int x = (a[i]\
    \ - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);\n            if (x < 0) {\n   \
    \             x += 10;\n                borrow = 1;\n            } else {\n  \
    \              borrow = 0;\n            }\n            res[k] = char('0' + x);\n\
    \        }\n        int p = 0;\n        while (p + 1 < (int)res.size() && res[p]\
    \ == '0') ++p;\n        return res.substr(p);\n    }\n\n    static vector<u32>\
    \ split_decimal_blocks(const string &s) {\n        vector<u32> blocks;\n     \
    \   if (s.empty()) return blocks;\n        int block_count = ((int)s.size() +\
    \ DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;\n        blocks.reserve(block_count);\n\
    \        int first = (int)s.size() % DEC_BLOCK_DIGITS;\n        if (first == 0)\
    \ first = DEC_BLOCK_DIGITS;\n        for (int i = 0; i < (int)s.size(); ) {\n\
    \            int width = blocks.empty() ? first : DEC_BLOCK_DIGITS;\n        \
    \    int r = min((int)s.size(), i + width);\n            u32 x = 0;\n        \
    \    for (int j = i; j < r; ++j) x = x * 10 + u32(s[j] - '0');\n            blocks.push_back(x);\n\
    \            i = r;\n        }\n        return blocks;\n    }\n\n    static vector<u32>\
    \ split_decimal_blocks_le(const string &s, int block_digits) {\n        vector<u32>\
    \ blocks;\n        if (s.empty()) return blocks;\n        int block_count = ((int)s.size()\
    \ + block_digits - 1) / block_digits;\n        blocks.reserve(block_count);\n\
    \        for (int r = (int)s.size(); r > 0; r -= block_digits) {\n           \
    \ int l = max(0, r - block_digits);\n            u32 x = 0;\n            for (int\
    \ i = l; i < r; ++i) x = x * 10 + u32(s[i] - '0');\n            blocks.push_back(x);\n\
    \        }\n        return blocks;\n    }\n\n    static vector<u64> split_decimal_blocks_le_u64(const\
    \ string &s, int block_digits) {\n        vector<u64> blocks;\n        if (s.empty())\
    \ return blocks;\n        int block_count = ((int)s.size() + block_digits - 1)\
    \ / block_digits;\n        blocks.reserve(block_count);\n        for (int r =\
    \ (int)s.size(); r > 0; r -= block_digits) {\n            int l = max(0, r - block_digits);\n\
    \            u64 x = 0;\n            for (int i = l; i < r; ++i) x = x * 10 +\
    \ u64(s[i] - '0');\n            blocks.push_back(x);\n        }\n        return\
    \ blocks;\n    }\n\n    static void trim_decimal_blocks(vector<u32> &blocks) {\n\
    \        while (!blocks.empty() && blocks.back() == 0) blocks.pop_back();\n  \
    \  }\n\n    static void trim_decimal_blocks_u64(vector<u64> &blocks) {\n     \
    \   while (!blocks.empty() && blocks.back() == 0) blocks.pop_back();\n    }\n\n\
    \    static int compare_decimal_blocks(const vector<u32> &a, const vector<u32>\
    \ &b) {\n        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;\n\
    \        for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (a[i]\
    \ != b[i]) return a[i] < b[i] ? -1 : 1;\n        }\n        return 0;\n    }\n\
    \n    static int compare_decimal_blocks_u64(const vector<u64> &a, const vector<u64>\
    \ &b) {\n        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;\n\
    \        for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (a[i]\
    \ != b[i]) return a[i] < b[i] ? -1 : 1;\n        }\n        return 0;\n    }\n\
    \n    static vector<u32> mul_small_decimal_blocks(const vector<u32> &a, u32 m,\
    \ u32 base) {\n        if (a.empty() || m == 0) return {};\n        if (m == 1)\
    \ return a;\n        vector<u32> res;\n        res.reserve(a.size() + 1);\n  \
    \      u64 carry = 0;\n        for (u32 x : a) {\n            u64 cur = u64(x)\
    \ * m + carry;\n            res.push_back(u32(cur % base));\n            carry\
    \ = cur / base;\n        }\n        if (carry) res.push_back(u32(carry));\n  \
    \      trim_decimal_blocks(res);\n        return res;\n    }\n\n    static u32\
    \ div_small_decimal_blocks_assign(vector<u32> &a, u32 m, u32 base) {\n       \
    \ u64 rem = 0;\n        for (int i = (int)a.size() - 1; i >= 0; --i) {\n     \
    \       u64 cur = rem * base + a[i];\n            a[i] = u32(cur / m);\n     \
    \       rem = cur % m;\n        }\n        trim_decimal_blocks(a);\n        return\
    \ u32(rem);\n    }\n\n    template <class T>\n    static void ensure_pow_cache_size(vector<T>\
    \ &cache, vector<char> &ready, int n) {\n        if ((int)cache.size() > n) return;\n\
    \        cache.resize(n + 1);\n        ready.resize(n + 1, 0);\n    }\n\n    static\
    \ string build_decimal_string(const vector<u32> &parts, int block_digits, bool\
    \ negative) {\n        string res;\n        res.reserve((negative ? 1 : 0) + decimal_digits_u32(parts.back())\
    \ +\n                    max(0, (int)parts.size() - 1) * block_digits);\n    \
    \    if (negative) res.push_back('-');\n        append_u32_decimal(res, parts.back());\n\
    \        for (int i = (int)parts.size() - 2; i >= 0; --i) {\n            append_u32_decimal_padded(res,\
    \ parts[i], block_digits);\n        }\n        return res;\n    }\n\n    static\
    \ BigInteger from_decimal_blocks_abs(vector<u32> parts, int block_digits) {\n\
    \        trim_decimal_blocks(parts);\n        if (parts.empty()) return BigInteger();\n\
    \        BigInteger res;\n        res.sign = 1;\n        res.dec = build_decimal_string(parts,\
    \ block_digits, false);\n        res.binary_ready = false;\n        res.decimal_ready\
    \ = true;\n        return res;\n    }\n\n    void ensure_binary() const {\n  \
    \      if (binary_ready) return;\n        d.clear();\n        if (sign == 0) {\n\
    \            binary_ready = true;\n            return;\n        }\n        vector<u32>\
    \ blocks = split_decimal_blocks(dec);\n        int block_count = (int)blocks.size();\n\
    \        if (block_count <= DEC_ASSIGN_LINEAR_BLOCK_THRESHOLD) {\n           \
    \ BigInteger tmp;\n            tmp.sign = 1;\n            tmp.d.clear();\n   \
    \         tmp.binary_ready = true;\n            tmp.decimal_ready = false;\n \
    \           for (u32 x : blocks) {\n                tmp.mul_small_assign(DEC_BLOCK);\n\
    \                tmp.add_small_assign(x);\n            }\n            d = std::move(tmp.d);\n\
    \        } else {\n            BigInteger tmp = from_decimal_blocks(blocks, 0,\
    \ (int)blocks.size());\n            d = std::move(tmp.d);\n        }\n       \
    \ binary_ready = true;\n    }\n\n    bool is_zero() const { return sign == 0;\
    \ }\n\n    int bit_length() const {\n        if (is_zero()) return 0;\n      \
    \  ensure_binary();\n        return 32 * ((int)d.size() - 1) + 32 - __builtin_clz(d.back());\n\
    \    }\n\n    static vector<BigInteger> &decimal_pow_cache() {\n        static\
    \ vector<BigInteger> cache = [] {\n            vector<BigInteger> v(2);\n    \
    \        v[0] = BigInteger(1);\n            v[1] = BigInteger((long long)DEC_BLOCK);\n\
    \            return v;\n        }();\n        return cache;\n    }\n\n    static\
    \ vector<char> &decimal_pow_ready() {\n        static vector<char> ready = {1,\
    \ 1};\n        return ready;\n    }\n\n    static const BigInteger &decimal_pow_blocks(int\
    \ blocks) {\n        auto &cache = decimal_pow_cache();\n        auto &ready =\
    \ decimal_pow_ready();\n        ensure_pow_cache_size(cache, ready, blocks);\n\
    \        if (ready[blocks]) return cache[blocks];\n        int left = blocks >>\
    \ 1;\n        int right = blocks - left;\n        cache[blocks] = decimal_pow_blocks(left)\
    \ * decimal_pow_blocks(right);\n        ready[blocks] = 1;\n        return cache[blocks];\n\
    \    }\n\n    static BigInteger from_decimal_blocks(const vector<u32> &blocks,\
    \ int l, int r) {\n        if (l >= r) return BigInteger();\n        if (r - l\
    \ <= 32) {\n            BigInteger res;\n            for (int i = l; i < r; ++i)\
    \ {\n                res.mul_small_assign(DEC_BLOCK);\n                res.add_small_assign(blocks[i]);\n\
    \            }\n            return res;\n        }\n        int m = (l + r) >>\
    \ 1;\n        BigInteger left = from_decimal_blocks(blocks, l, m);\n        BigInteger\
    \ right = from_decimal_blocks(blocks, m, r);\n        if (!left.is_zero()) left\
    \ *= decimal_pow_blocks(r - m);\n        left += right;\n        return left;\n\
    \    }\n\n    static vector<u32> mul_decimal_vectors(const vector<u32> &a, const\
    \ vector<u32> &b) {\n        if (a.empty() || b.empty()) return {};\n        if\
    \ (min(a.size(), b.size()) <= 32 || a.size() * b.size() <= 4096) {\n         \
    \   vector<u32> res(a.size() + b.size(), 0);\n            for (size_t i = 0; i\
    \ < a.size(); ++i) {\n                u64 carry = 0;\n                size_t j\
    \ = 0;\n                for (; j < b.size(); ++j) {\n                    u128\
    \ cur = u128(a[i]) * b[j] + res[i + j] + carry;\n                    res[i + j]\
    \ = u32(cur % DEC_CONV_BASE);\n                    carry = u64(cur / DEC_CONV_BASE);\n\
    \                }\n                size_t pos = i + j;\n                while\
    \ (carry) {\n                    u64 cur = u64(res[pos]) + carry;\n          \
    \          res[pos] = u32(cur % DEC_CONV_BASE);\n                    carry = cur\
    \ / DEC_CONV_BASE;\n                    ++pos;\n                }\n          \
    \  }\n            while (!res.empty() && res.back() == 0) res.pop_back();\n  \
    \          return res;\n        }\n        auto conv = BigIntegerExactConvolution::convolution_u64(a,\
    \ b);\n        vector<u32> res;\n        res.reserve(conv.size() + 3);\n     \
    \   u64 carry = 0;\n        for (u64 v : conv) {\n            u64 cur = v + carry;\n\
    \            res.push_back(u32(cur % DEC_CONV_BASE));\n            carry = cur\
    \ / DEC_CONV_BASE;\n        }\n        while (carry) {\n            res.push_back(u32(carry\
    \ % DEC_CONV_BASE));\n            carry /= DEC_CONV_BASE;\n        }\n       \
    \ while (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n\
    \    }\n\n    static vector<u32> add_decimal_vectors(vector<u32> a, const vector<u32>\
    \ &b) {\n        if (a.size() < b.size()) a.resize(b.size(), 0);\n        u64\
    \ carry = 0;\n        size_t i = 0;\n        for (; i < b.size(); ++i) {\n   \
    \         u64 cur = u64(a[i]) + b[i] + carry;\n            a[i] = u32(cur % DEC_CONV_BASE);\n\
    \            carry = cur / DEC_CONV_BASE;\n        }\n        for (; i < a.size()\
    \ && carry; ++i) {\n            u64 cur = u64(a[i]) + carry;\n            a[i]\
    \ = u32(cur % DEC_CONV_BASE);\n            carry = cur / DEC_CONV_BASE;\n    \
    \    }\n        if (carry) a.push_back(u32(carry));\n        while (!a.empty()\
    \ && a.back() == 0) a.pop_back();\n        return a;\n    }\n\n    static vector<vector<u32>>\
    \ &binary_pow_decimal_cache() {\n        static vector<vector<u32>> cache = {{1},\
    \ {967296u, 4294u}};\n        return cache;\n    }\n\n    static vector<char>\
    \ &binary_pow_decimal_ready() {\n        static vector<char> ready = {1, 1};\n\
    \        return ready;\n    }\n\n    static const vector<u32> &binary_pow_decimal(int\
    \ limbs) {\n        auto &cache = binary_pow_decimal_cache();\n        auto &ready\
    \ = binary_pow_decimal_ready();\n        ensure_pow_cache_size(cache, ready, limbs);\n\
    \        if (ready[limbs]) return cache[limbs];\n        int left = limbs >> 1;\n\
    \        int right = limbs - left;\n        cache[limbs] = mul_decimal_vectors(binary_pow_decimal(left),\
    \ binary_pow_decimal(right));\n        ready[limbs] = 1;\n        return cache[limbs];\n\
    \    }\n\n    static vector<u32> small_limbs_to_decimal(const vector<u32> &limbs,\
    \ int l, int r) {\n        BigInteger tmp;\n        tmp.sign = 1;\n        tmp.d.assign(limbs.begin()\
    \ + l, limbs.begin() + r);\n        tmp.trim();\n        vector<u32> res;\n  \
    \      while (!tmp.is_zero()) res.push_back(tmp.div_small_assign(DEC_CONV_BASE));\n\
    \        return res;\n    }\n\n    static vector<u32> limbs_to_decimal(const vector<u32>\
    \ &limbs, int l, int r) {\n        while (l < r && limbs[r - 1] == 0) --r;\n \
    \       if (l >= r) return {};\n        if (r - l <= 32) return small_limbs_to_decimal(limbs,\
    \ l, r);\n        int m = (l + r) >> 1;\n        vector<u32> low = limbs_to_decimal(limbs,\
    \ l, m);\n        vector<u32> high = limbs_to_decimal(limbs, m, r);\n        if\
    \ (high.empty()) return low;\n        vector<u32> shifted = mul_decimal_vectors(high,\
    \ binary_pow_decimal(m - l));\n        if (low.empty()) return shifted;\n    \
    \    return add_decimal_vectors(std::move(low), shifted);\n    }\n\n    static\
    \ int decimal_digits_u32(u32 x) {\n        if (x >= 1000000000u) return 10;\n\
    \        if (x >= 100000000u) return 9;\n        if (x >= 10000000u) return 8;\n\
    \        if (x >= 1000000u) return 7;\n        if (x >= 100000u) return 6;\n \
    \       if (x >= 10000u) return 5;\n        if (x >= 1000u) return 4;\n      \
    \  if (x >= 100u) return 3;\n        if (x >= 10u) return 2;\n        return 1;\n\
    \    }\n\n    static void append_u32_decimal(string &res, u32 x) {\n        char\
    \ buf[10];\n        int pos = 10;\n        do {\n            buf[--pos] = char('0'\
    \ + (x % 10));\n            x /= 10;\n        } while (x);\n        res.append(buf\
    \ + pos, buf + 10);\n    }\n\n    static void append_u32_decimal_padded(string\
    \ &res, u32 x, int width) {\n        char buf[10];\n        for (int i = width\
    \ - 1; i >= 0; --i) {\n            buf[i] = char('0' + (x % 10));\n          \
    \  x /= 10;\n        }\n        res.append(buf, buf + width);\n    }\n\n    static\
    \ int decimal_digits_u64(u64 x) {\n        int digits = 1;\n        while (x >=\
    \ 10) {\n            x /= 10;\n            ++digits;\n        }\n        return\
    \ digits;\n    }\n\n    static void append_u64_decimal(string &res, u64 x) {\n\
    \        char buf[20];\n        int pos = 20;\n        do {\n            buf[--pos]\
    \ = char('0' + (x % 10));\n            x /= 10;\n        } while (x);\n      \
    \  res.append(buf + pos, buf + 20);\n    }\n\n    static void append_u64_decimal_padded(string\
    \ &res, u64 x, int width) {\n        char buf[20];\n        for (int i = width\
    \ - 1; i >= 0; --i) {\n            buf[i] = char('0' + (x % 10));\n          \
    \  x /= 10;\n        }\n        res.append(buf, buf + width);\n    }\n\n    static\
    \ string build_decimal_string_u64(const vector<u64> &parts, int block_digits,\
    \ bool negative) {\n        string res;\n        res.reserve((negative ? 1 : 0)\
    \ + decimal_digits_u64(parts.back()) +\n                    max(0, (int)parts.size()\
    \ - 1) * block_digits);\n        if (negative) res.push_back('-');\n        append_u64_decimal(res,\
    \ parts.back());\n        for (int i = (int)parts.size() - 2; i >= 0; --i) {\n\
    \            append_u64_decimal_padded(res, parts[i], block_digits);\n       \
    \ }\n        return res;\n    }\n\n    static BigInteger from_decimal_blocks_abs_u64(vector<u64>\
    \ parts, int block_digits) {\n        trim_decimal_blocks_u64(parts);\n      \
    \  if (parts.empty()) return BigInteger();\n        BigInteger res;\n        res.sign\
    \ = 1;\n        res.dec = build_decimal_string_u64(parts, block_digits, false);\n\
    \        res.binary_ready = false;\n        res.decimal_ready = true;\n      \
    \  return res;\n    }\n\n    struct FastDecBigint {\n        vector<u64> digits;\n\
    \        bool negative;\n\n        FastDecBigint() : digits(), negative(false)\
    \ {}\n        FastDecBigint(long long x) : digits(), negative(false) {\n     \
    \       if (x < 0) {\n                negative = true;\n                x = -x;\n\
    \            }\n            if (x) digits.push_back(u64(x));\n        }\n    \
    \    FastDecBigint(vector<u64> d, bool neg = false) : digits(std::move(d)), negative(neg)\
    \ { normalize(); }\n\n        FastDecBigint &normalize() {\n            trim_decimal_blocks_u64(digits);\n\
    \            if (digits.empty()) negative = false;\n            return *this;\n\
    \        }\n\n        bool is_zero() const { return digits.empty(); }\n\n    \
    \    static int compare_abs_digits(const vector<u64> &a, const vector<u64> &b)\
    \ {\n            return compare_decimal_blocks_u64(a, b);\n        }\n\n     \
    \   int compare(const FastDecBigint &other) const {\n            if (is_zero()\
    \ && other.is_zero()) return 0;\n            if (negative != other.negative) return\
    \ negative ? -1 : 1;\n            int c = compare_abs_digits(digits, other.digits);\n\
    \            return negative ? -c : c;\n        }\n\n        bool operator<(const\
    \ FastDecBigint &other) const { return compare(other) < 0; }\n        bool operator>=(const\
    \ FastDecBigint &other) const { return compare(other) >= 0; }\n\n        FastDecBigint\
    \ &pad_inplace(size_t to_add) {\n            if (to_add) digits.insert(digits.begin(),\
    \ to_add, 0);\n            return *this;\n        }\n\n        FastDecBigint &drop_inplace(size_t\
    \ to_drop) {\n            if (to_drop >= digits.size()) {\n                digits.clear();\n\
    \                negative = false;\n                return *this;\n          \
    \  }\n            digits.erase(digits.begin(), digits.begin() + (int)to_drop);\n\
    \            return normalize();\n        }\n\n        FastDecBigint pad(size_t\
    \ to_add) const {\n            FastDecBigint res = *this;\n            return\
    \ res.pad_inplace(to_add);\n        }\n\n        FastDecBigint drop(size_t to_drop)\
    \ const {\n            FastDecBigint res = *this;\n            return res.drop_inplace(to_drop);\n\
    \        }\n\n        FastDecBigint top(size_t to_keep) const {\n            if\
    \ (to_keep >= digits.size()) return pad(to_keep - digits.size());\n          \
    \  return drop(digits.size() - to_keep);\n        }\n\n        FastDecBigint &negate()\
    \ {\n            if (!is_zero()) negative = !negative;\n            return *this;\n\
    \        }\n\n        FastDecBigint operator-() const {\n            FastDecBigint\
    \ res = *this;\n            res.negate();\n            return res;\n        }\n\
    \n        static vector<u64> add_abs_digits(const vector<u64> &a, const vector<u64>\
    \ &b) {\n            vector<u64> res(max(a.size(), b.size()), 0);\n          \
    \  u64 carry = 0;\n            size_t i = 0;\n            for (; i < res.size();\
    \ ++i) {\n                u128 cur = carry;\n                if (i < a.size())\
    \ cur += a[i];\n                if (i < b.size()) cur += b[i];\n             \
    \   if (cur >= FAST_DEC_BASE) {\n                    res[i] = u64(cur - FAST_DEC_BASE);\n\
    \                    carry = 1;\n                } else {\n                  \
    \  res[i] = u64(cur);\n                    carry = 0;\n                }\n   \
    \         }\n            if (carry) res.push_back(carry);\n            trim_decimal_blocks_u64(res);\n\
    \            return res;\n        }\n\n        static void sub_abs_assign(vector<u64>\
    \ &a, const vector<u64> &b) {\n            u64 borrow = 0;\n            for (size_t\
    \ i = 0; i < a.size(); ++i) {\n                u128 rhs = borrow;\n          \
    \      if (i < b.size()) rhs += b[i];\n                if (u128(a[i]) < rhs) {\n\
    \                    a[i] = u64(u128(a[i]) + FAST_DEC_BASE - rhs);\n         \
    \           borrow = 1;\n                } else {\n                    a[i] =\
    \ u64(u128(a[i]) - rhs);\n                    borrow = 0;\n                }\n\
    \            }\n            trim_decimal_blocks_u64(a);\n        }\n\n       \
    \ FastDecBigint &operator+=(const FastDecBigint &other) {\n            if (other.is_zero())\
    \ return *this;\n            if (is_zero()) {\n                *this = other;\n\
    \                return *this;\n            }\n            if (negative == other.negative)\
    \ {\n                digits = add_abs_digits(digits, other.digits);\n        \
    \        return *this;\n            }\n            int cmp = compare_abs_digits(digits,\
    \ other.digits);\n            if (cmp == 0) {\n                digits.clear();\n\
    \                negative = false;\n                return *this;\n          \
    \  }\n            if (cmp > 0) {\n                sub_abs_assign(digits, other.digits);\n\
    \            } else {\n                vector<u64> res = other.digits;\n     \
    \           sub_abs_assign(res, digits);\n                digits = std::move(res);\n\
    \                negative = other.negative;\n            }\n            return\
    \ normalize();\n        }\n\n        FastDecBigint &operator-=(const FastDecBigint\
    \ &other) {\n            return *this += (-other);\n        }\n\n        FastDecBigint\
    \ operator+(const FastDecBigint &other) const {\n            FastDecBigint res\
    \ = *this;\n            res += other;\n            return res;\n        }\n\n\
    \        FastDecBigint operator-(const FastDecBigint &other) const {\n       \
    \     FastDecBigint res = *this;\n            res -= other;\n            return\
    \ res;\n        }\n\n        FastDecBigint &operator+=(long long other) {\n  \
    \          return *this += FastDecBigint(other);\n        }\n\n        FastDecBigint\
    \ &operator-=(long long other) {\n            return *this -= FastDecBigint(other);\n\
    \        }\n\n        FastDecBigint &operator*=(long long other) {\n         \
    \   if (is_zero() || other == 1) return *this;\n            if (other == 0) {\n\
    \                digits.clear();\n                negative = false;\n        \
    \        return *this;\n            }\n            if (other < 0) {\n        \
    \        negative = !negative;\n                other = -other;\n            }\n\
    \            u64 mul = u64(other);\n            u64 carry = 0;\n            for\
    \ (u64 &d : digits) {\n                u128 cur = u128(d) * mul + carry;\n   \
    \             d = u64(cur % FAST_DEC_BASE);\n                carry = u64(cur /\
    \ FAST_DEC_BASE);\n            }\n            while (carry) {\n              \
    \  digits.push_back(carry % FAST_DEC_BASE);\n                carry /= FAST_DEC_BASE;\n\
    \            }\n            return normalize();\n        }\n\n        static vector<u64>\
    \ mul_schoolbook_digits(const vector<u64> &a, const vector<u64> &b) {\n      \
    \      if (a.empty() || b.empty()) return {};\n            vector<u64> res(a.size()\
    \ + b.size(), 0);\n            for (size_t i = 0; i < a.size(); ++i) {\n     \
    \           u64 carry = 0;\n                for (size_t j = 0; j < b.size(); ++j)\
    \ {\n                    u128 cur = u128(a[i]) * b[j] + res[i + j] + carry;\n\
    \                    res[i + j] = u64(cur % FAST_DEC_BASE);\n                \
    \    carry = u64(cur / FAST_DEC_BASE);\n                }\n                size_t\
    \ pos = i + b.size();\n                while (carry) {\n                    u128\
    \ cur = u128(res[pos]) + carry;\n                    res[pos] = u64(cur % FAST_DEC_BASE);\n\
    \                    carry = u64(cur / FAST_DEC_BASE);\n                    ++pos;\n\
    \                }\n            }\n            trim_decimal_blocks_u64(res);\n\
    \            return res;\n        }\n\n        static vector<u32> to_metabase_digits(const\
    \ vector<u64> &src) {\n            vector<u32> res(src.size() * FAST_DEC_META_DIGITS);\n\
    \            for (size_t i = 0; i < src.size(); ++i) {\n                u64 cur\
    \ = src[i];\n                for (int k = 0; k < FAST_DEC_META_DIGITS; ++k) {\n\
    \                    res[i * FAST_DEC_META_DIGITS + k] = u32(cur % FAST_DEC_META_BASE);\n\
    \                    cur /= FAST_DEC_META_BASE;\n                }\n         \
    \   }\n            while (!res.empty() && res.back() == 0) res.pop_back();\n \
    \           return res;\n        }\n\n        static vector<u64> from_metabase_digits(const\
    \ vector<u32> &src) {\n            vector<u64> res;\n            res.reserve(src.size()\
    \ / FAST_DEC_META_DIGITS + 2);\n            u64 carry = 0;\n            for (size_t\
    \ i = 0; i < src.size(); i += FAST_DEC_META_DIGITS) {\n                u128 val\
    \ = carry;\n                for (int k = FAST_DEC_META_DIGITS - 1; k >= 0; --k)\
    \ {\n                    val *= FAST_DEC_META_BASE;\n                    size_t\
    \ idx = i + (size_t)k;\n                    if (idx < src.size()) val += src[idx];\n\
    \                }\n                res.push_back(u64(val % FAST_DEC_BASE));\n\
    \                carry = u64(val / FAST_DEC_BASE);\n            }\n          \
    \  while (carry) {\n                res.push_back(carry % FAST_DEC_BASE);\n  \
    \              carry /= FAST_DEC_BASE;\n            }\n            trim_decimal_blocks_u64(res);\n\
    \            return res;\n        }\n\n        static vector<u64> mul_digits(const\
    \ vector<u64> &a, const vector<u64> &b) {\n            if (a.empty() || b.empty())\
    \ return {};\n            if (min(a.size(), b.size()) <= 32 || a.size() * b.size()\
    \ <= 4096) {\n                return mul_schoolbook_digits(a, b);\n          \
    \  }\n            vector<u32> x = to_metabase_digits(a);\n            vector<u32>\
    \ y = to_metabase_digits(b);\n            auto conv = BigIntegerExactConvolution::convolution_u64(x,\
    \ y);\n            vector<u32> meta;\n            meta.reserve(conv.size() + 4);\n\
    \            u64 carry = 0;\n            for (u64 v : conv) {\n              \
    \  u64 cur = v + carry;\n                meta.push_back(u32(cur % FAST_DEC_META_BASE));\n\
    \                carry = cur / FAST_DEC_META_BASE;\n            }\n          \
    \  while (carry) {\n                meta.push_back(u32(carry % FAST_DEC_META_BASE));\n\
    \                carry /= FAST_DEC_META_BASE;\n            }\n            while\
    \ (!meta.empty() && meta.back() == 0) meta.pop_back();\n            return from_metabase_digits(meta);\n\
    \        }\n\n        FastDecBigint &mul_inplace(FastDecBigint other) {\n    \
    \        negative = negative != other.negative;\n            digits = mul_digits(digits,\
    \ other.digits);\n            return normalize();\n        }\n\n        FastDecBigint\
    \ &operator*=(const FastDecBigint &other) {\n            return mul_inplace(FastDecBigint(other));\n\
    \        }\n\n        FastDecBigint operator*(const FastDecBigint &other) const\
    \ {\n            FastDecBigint res = *this;\n            res *= other;\n     \
    \       return res;\n        }\n    };\n\n    struct FastDecimal {\n        FastDecBigint\
    \ value;\n        long long scale;\n\n        FastDecimal(long long v = 0, long\
    \ long s = 0) : value(v), scale(s) {}\n        FastDecimal(FastDecBigint v, long\
    \ long s = 0) : value(std::move(v)), scale(s) {}\n\n        FastDecimal &operator*=(const\
    \ FastDecimal &other) {\n            value *= other.value;\n            scale\
    \ += other.scale;\n            return *this;\n        }\n\n        FastDecimal\
    \ &operator+=(const FastDecimal &other) {\n            if (scale < other.scale)\
    \ {\n                value += other.value.pad((size_t)(other.scale - scale));\n\
    \            } else {\n                value.pad_inplace((size_t)(scale - other.scale));\n\
    \                value += other.value;\n                scale = other.scale;\n\
    \            }\n            return *this;\n        }\n\n        FastDecimal &operator-=(const\
    \ FastDecimal &other) {\n            if (scale < other.scale) {\n            \
    \    value -= other.value.pad((size_t)(other.scale - scale));\n            } else\
    \ {\n                value.pad_inplace((size_t)(scale - other.scale));\n     \
    \           value -= other.value;\n                scale = other.scale;\n    \
    \        }\n            return *this;\n        }\n\n        FastDecimal operator*(const\
    \ FastDecimal &other) const {\n            FastDecimal res = *this;\n        \
    \    res *= other;\n            return res;\n        }\n\n        FastDecimal\
    \ operator+(const FastDecimal &other) const {\n            FastDecimal res = *this;\n\
    \            res += other;\n            return res;\n        }\n\n        FastDecimal\
    \ operator-(const FastDecimal &other) const {\n            FastDecimal res = *this;\n\
    \            res -= other;\n            return res;\n        }\n\n        FastDecBigint\
    \ trunc() const {\n            if (scale >= 0) return value.pad((size_t)scale);\n\
    \            if (-scale >= (long long)value.digits.size()) return FastDecBigint();\n\
    \            return value.top(value.digits.size() - (size_t)(-scale));\n     \
    \   }\n\n        FastDecBigint round() const {\n            if (scale >= 0) return\
    \ value.pad((size_t)scale);\n            if (-scale > (long long)value.digits.size())\
    \ return FastDecBigint();\n            FastDecBigint res = value.top(value.digits.size()\
    \ - (size_t)(-scale));\n            if (value.digits[(size_t)(-scale - 1)] * 2\
    \ >= FAST_DEC_BASE) res += 1;\n            return res;\n        }\n\n        FastDecimal\
    \ trunc(size_t digits_to_keep) const {\n            digits_to_keep = min(digits_to_keep,\
    \ value.digits.size());\n            return FastDecimal(value.top(digits_to_keep),\
    \ scale + (long long)value.digits.size() - (long long)digits_to_keep);\n     \
    \   }\n\n        long long magnitude() const {\n            static constexpr long\
    \ long NEG_INF = -(1LL << 60);\n            if (value.digits.empty()) return NEG_INF;\n\
    \            return (long long)value.digits.size() + scale;\n        }\n\n   \
    \     FastDecimal inv(long long precision) const {\n            assert(precision\
    \ >= 0);\n            long long lead = (long long)((long double)FAST_DEC_BASE\
    \ / (long double)value.digits.back() + 0.5L);\n            FastDecimal d(FastDecBigint(lead),\
    \ -(long long)value.digits.size());\n            size_t cur = 2;\n           \
    \ FastDecimal amend = FastDecimal(1) - trunc(cur) * d;\n            while (-amend.magnitude()\
    \ < precision) {\n                d += d * amend;\n                cur = 2 * (size_t)(1\
    \ - amend.magnitude());\n                d = d.trunc(cur);\n                amend\
    \ = FastDecimal(1) - trunc(cur) * d;\n            }\n            return d;\n \
    \       }\n    };\n\n    void trim() {\n        while (!d.empty() && d.back()\
    \ == 0) d.pop_back();\n        if (d.empty()) sign = 0;\n    }\n\n    int compare_abs(const\
    \ BigInteger &other) const {\n        if (decimal_ready && other.decimal_ready)\
    \ return compare_abs_decimal(dec, other.dec);\n        ensure_binary();\n    \
    \    other.ensure_binary();\n        if (d.size() != other.d.size()) return d.size()\
    \ < other.d.size() ? -1 : 1;\n        for (int i = (int)d.size() - 1; i >= 0;\
    \ --i) {\n            if (d[i] != other.d[i]) return d[i] < other.d[i] ? -1 :\
    \ 1;\n        }\n        return 0;\n    }\n\n    static int compare(const BigInteger\
    \ &a, const BigInteger &b) {\n        if (a.sign != b.sign) return a.sign < b.sign\
    \ ? -1 : 1;\n        if (a.sign == 0) return 0;\n        int c = a.compare_abs(b);\n\
    \        return a.sign > 0 ? c : -c;\n    }\n\n    void add_abs(const BigInteger\
    \ &other) {\n        ensure_binary();\n        other.ensure_binary();\n      \
    \  invalidate_decimal();\n        if (other.is_zero()) return;\n        if (d.size()\
    \ < other.d.size()) d.resize(other.d.size(), 0);\n        u64 carry = 0;\n   \
    \     for (size_t i = 0; i < other.d.size(); ++i) {\n            u64 cur = carry\
    \ + u64(d[i]) + other.d[i];\n            d[i] = u32(cur);\n            carry =\
    \ cur >> 32;\n        }\n        for (size_t i = other.d.size(); carry && i <\
    \ d.size(); ++i) {\n            u64 cur = carry + u64(d[i]);\n            d[i]\
    \ = u32(cur);\n            carry = cur >> 32;\n        }\n        if (carry) d.push_back(u32(carry));\n\
    \        if (!d.empty()) sign = 1;\n    }\n\n    void sub_abs(const BigInteger\
    \ &other) {\n        ensure_binary();\n        other.ensure_binary();\n      \
    \  invalidate_decimal();\n        // assume |*this| >= |other|\n        u64 borrow\
    \ = 0;\n        for (size_t i = 0; i < other.d.size(); ++i) {\n            u64\
    \ cur = u64(d[i]);\n            u64 rhs = u64(other.d[i]) + borrow;\n        \
    \    if (cur < rhs) {\n                d[i] = u32((cur + BASE) - rhs);\n     \
    \           borrow = 1;\n            } else {\n                d[i] = u32(cur\
    \ - rhs);\n                borrow = 0;\n            }\n        }\n        for\
    \ (size_t i = other.d.size(); borrow && i < d.size(); ++i) {\n            u64\
    \ cur = u64(d[i]);\n            if (cur == 0) {\n                d[i] = BASE_MASK;\n\
    \                borrow = 1;\n            } else {\n                d[i] = u32(cur\
    \ - 1);\n                borrow = 0;\n            }\n        }\n        trim();\n\
    \    }\n\n    void mul_small_assign(u32 m) {\n        ensure_binary();\n     \
    \   invalidate_decimal();\n        if (is_zero() || m == 1) return;\n        if\
    \ (m == 0) {\n            d.clear();\n            sign = 0;\n            return;\n\
    \        }\n        u64 carry = 0;\n        for (size_t i = 0; i < d.size(); ++i)\
    \ {\n            u64 cur = u64(d[i]) * m + carry;\n            d[i] = u32(cur);\n\
    \            carry = cur >> 32;\n        }\n        if (carry) d.push_back(u32(carry));\n\
    \    }\n\n    void add_small_assign(u32 a) {\n        ensure_binary();\n     \
    \   invalidate_decimal();\n        if (a == 0) return;\n        if (is_zero())\
    \ {\n            sign = 1;\n            d.push_back(a);\n            return;\n\
    \        }\n        u64 carry = a;\n        for (size_t i = 0; i < d.size() &&\
    \ carry; ++i) {\n            u64 cur = u64(d[i]) + carry;\n            d[i] =\
    \ u32(cur);\n            carry = cur >> 32;\n        }\n        if (carry) d.push_back(u32(carry));\n\
    \    }\n\n    u32 div_small_assign(u32 m) {\n        ensure_binary();\n      \
    \  invalidate_decimal();\n        u64 rem = 0;\n        for (int i = (int)d.size()\
    \ - 1; i >= 0; --i) {\n            u64 cur = (rem << 32) | d[i];\n           \
    \ d[i] = u32(cur / m);\n            rem = cur % m;\n        }\n        trim();\n\
    \        return u32(rem);\n    }\n\n    void shift_left_bits_assign(int bits)\
    \ {\n        ensure_binary();\n        invalidate_decimal();\n        if (bits\
    \ < 0) {\n            shift_right_bits_assign(-bits);\n            return;\n \
    \       }\n        if (is_zero() || bits == 0) return;\n        int word = bits\
    \ >> 5;\n        int rem = bits & 31;\n        if (word) d.insert(d.begin(), (size_t)word,\
    \ 0);\n        if (rem == 0) return;\n        u64 carry = 0;\n        for (size_t\
    \ i = word; i < d.size(); ++i) {\n            u64 cur = (u64(d[i]) << rem) | carry;\n\
    \            d[i] = u32(cur);\n            carry = cur >> 32;\n        }\n   \
    \     if (carry) d.push_back(u32(carry));\n    }\n\n    void shift_right_bits_assign(int\
    \ bits) {\n        ensure_binary();\n        invalidate_decimal();\n        if\
    \ (bits < 0) {\n            shift_left_bits_assign(-bits);\n            return;\n\
    \        }\n        if (is_zero() || bits == 0) return;\n        int word = bits\
    \ >> 5;\n        int rem = bits & 31;\n        if (word >= (int)d.size()) {\n\
    \            d.clear();\n            sign = 0;\n            return;\n        }\n\
    \        if (word) d.erase(d.begin(), d.begin() + word);\n        if (rem == 0)\
    \ {\n            trim();\n            return;\n        }\n        u64 carry =\
    \ 0;\n        for (int i = (int)d.size() - 1; i >= 0; --i) {\n            u64\
    \ cur = d[i];\n            d[i] = u32((cur >> rem) | (carry << (32 - rem)));\n\
    \            carry = cur & ((1ULL << rem) - 1);\n        }\n        trim();\n\
    \    }\n\n    static BigInteger mul_schoolbook(const BigInteger &a, const BigInteger\
    \ &b) {\n        a.ensure_binary();\n        b.ensure_binary();\n        BigInteger\
    \ res;\n        if (a.is_zero() || b.is_zero()) return res;\n        res.sign\
    \ = 1;\n        res.d.assign(a.d.size() + b.d.size(), 0);\n        for (size_t\
    \ i = 0; i < a.d.size(); ++i) {\n            u64 carry = 0;\n            for (size_t\
    \ j = 0; j < b.d.size(); ++j) {\n                u64 cur = u64(res.d[i + j]) +\
    \ u64(a.d[i]) * b.d[j] + carry;\n                res.d[i + j] = u32(cur);\n  \
    \              carry = cur >> 32;\n            }\n            size_t pos = i +\
    \ b.d.size();\n            while (carry) {\n                u64 cur = u64(res.d[pos])\
    \ + carry;\n                res.d[pos] = u32(cur);\n                carry = cur\
    \ >> 32;\n                ++pos;\n            }\n        }\n        res.trim();\n\
    \        return res;\n    }\n\n    static BigInteger mul_convolution(const BigInteger\
    \ &a, const BigInteger &b) {\n        a.ensure_binary();\n        b.ensure_binary();\n\
    \        BigInteger res;\n        if (a.is_zero() || b.is_zero()) return res;\n\
    \        vector<u32> x;\n        vector<u32> y;\n        x.reserve(a.d.size()\
    \ * 2);\n        y.reserve(b.d.size() * 2);\n        for (u32 v : a.d) {\n   \
    \         x.push_back(v & 0xffffu);\n            x.push_back(v >> 16);\n     \
    \   }\n        for (u32 v : b.d) {\n            y.push_back(v & 0xffffu);\n  \
    \          y.push_back(v >> 16);\n        }\n        while (!x.empty() && x.back()\
    \ == 0) x.pop_back();\n        while (!y.empty() && y.back() == 0) y.pop_back();\n\
    \        if (x.empty() || y.empty()) return res;\n        auto conv = BigIntegerExactConvolution::convolution_u64(x,\
    \ y);\n        vector<u32> digits;\n        digits.reserve(conv.size() + 2);\n\
    \        u64 carry = 0;\n        for (u64 v : conv) {\n            u64 cur = v\
    \ + carry;\n            digits.push_back(u32(cur & 0xffffu));\n            carry\
    \ = cur >> 16;\n        }\n        while (carry) {\n            digits.push_back(u32(carry\
    \ & 0xffffu));\n            carry >>= 16;\n        }\n        while (!digits.empty()\
    \ && digits.back() == 0) digits.pop_back();\n        if (digits.empty()) return\
    \ res;\n        res.sign = 1;\n        res.d.reserve((digits.size() + 1) / 2);\n\
    \        for (size_t i = 0; i < digits.size(); i += 2) {\n            u32 lo =\
    \ digits[i];\n            u32 hi = i + 1 < digits.size() ? digits[i + 1] : 0;\n\
    \            res.d.push_back(lo | (hi << 16));\n        }\n        res.trim();\n\
    \        return res;\n    }\n\n    static BigInteger multiply(const BigInteger\
    \ &a, const BigInteger &b) {\n        if (a.decimal_ready && b.decimal_ready)\
    \ {\n            if (a.is_zero() || b.is_zero()) return BigInteger();\n      \
    \      vector<u32> x = split_decimal_blocks_le(a.dec, DEC_CONV_DIGITS);\n    \
    \        vector<u32> y = split_decimal_blocks_le(b.dec, DEC_CONV_DIGITS);\n  \
    \          vector<u32> parts = mul_decimal_vectors(x, y);\n            BigInteger\
    \ res;\n            if (parts.empty()) return res;\n            res.sign = a.sign\
    \ * b.sign;\n            res.dec = build_decimal_string(parts, DEC_CONV_DIGITS,\
    \ false);\n            res.binary_ready = false;\n            res.decimal_ready\
    \ = true;\n            return res;\n        }\n        a.ensure_binary();\n  \
    \      b.ensure_binary();\n        if (a.is_zero() || b.is_zero()) return BigInteger();\n\
    \        BigInteger res;\n        size_t n = a.d.size(), m = b.d.size();\n   \
    \     if (min(n, m) <= MUL_SCHOOLBOOK_LIMB_THRESHOLD || n * m <= MUL_SCHOOLBOOK_AREA_THRESHOLD)\
    \ {\n            res = mul_schoolbook(a, b);\n        }\n        else res = mul_convolution(a,\
    \ b);\n        res.sign = a.sign * b.sign;\n        if (res.is_zero()) res.sign\
    \ = 0;\n        return res;\n    }\n\n    static vector<u32> shift_left_copy_limbs(const\
    \ vector<u32> &src, int bits) {\n        if (src.empty()) return {};\n       \
    \ if (bits == 0) return src;\n        vector<u32> res(src.size() + 1, 0);\n  \
    \      u32 carry = 0;\n        for (size_t i = 0; i < src.size(); ++i) {\n   \
    \         u64 cur = (u64(src[i]) << bits) | carry;\n            res[i] = u32(cur);\n\
    \            carry = u32(cur >> 32);\n        }\n        res[src.size()] = carry;\n\
    \        if (res.back() == 0) res.pop_back();\n        return res;\n    }\n\n\
    \    static void shift_right_limbs_assign(vector<u32> &src, int bits) {\n    \
    \    if (src.empty() || bits == 0) return;\n        u32 carry = 0;\n        for\
    \ (int i = (int)src.size() - 1; i >= 0; --i) {\n            u32 cur = src[i];\n\
    \            src[i] = (cur >> bits) | (carry << (32 - bits));\n            carry\
    \ = cur & ((u32(1) << bits) - 1);\n        }\n        while (!src.empty() && src.back()\
    \ == 0) src.pop_back();\n    }\n\n    static BigInteger from_limbs(vector<u32>\
    \ limbs) {\n        BigInteger res;\n        res.d = std::move(limbs);\n     \
    \   while (!res.d.empty() && res.d.back() == 0) res.d.pop_back();\n        res.sign\
    \ = res.d.empty() ? 0 : 1;\n        res.binary_ready = true;\n        res.decimal_ready\
    \ = false;\n        return res;\n    }\n\n    static BigInteger from_limbs_range(const\
    \ vector<u32> &src, int l, int r) {\n        if (l >= r) return BigInteger();\n\
    \        BigInteger res;\n        res.d.assign(src.begin() + l, src.begin() +\
    \ r);\n        while (!res.d.empty() && res.d.back() == 0) res.d.pop_back();\n\
    \        res.sign = res.d.empty() ? 0 : 1;\n        res.binary_ready = true;\n\
    \        res.decimal_ready = false;\n        return res;\n    }\n\n    static\
    \ BigInteger merge_disjoint_range_high(const BigInteger &x, int l, int r,\n  \
    \                                              const BigInteger &high, int high_shift)\
    \ {\n        x.ensure_binary();\n        high.ensure_binary();\n        int xl\
    \ = max(0, l);\n        int xr = min((int)x.d.size(), r);\n        int low_len\
    \ = max(0, xr - xl);\n        if (high.is_zero()) return low_len ? from_limbs_range(x.d,\
    \ xl, xr) : BigInteger();\n        if (low_len == 0) return shift_left_limbs(high,\
    \ high_shift);\n        BigInteger res;\n        size_t need = max((size_t)low_len,\
    \ high.d.size() + (size_t)high_shift);\n        res.d.assign(need, 0);\n     \
    \   for (int i = 0; i < low_len; ++i) res.d[i] = x.d[xl + i];\n        for (size_t\
    \ i = 0; i < high.d.size(); ++i) res.d[i + high_shift] = high.d[i];\n        res.sign\
    \ = 1;\n        res.binary_ready = true;\n        res.decimal_ready = false;\n\
    \        res.trim();\n        return res;\n    }\n\n    static BigInteger merge_disjoint_abs(const\
    \ BigInteger &low, const BigInteger &high, int high_shift) {\n        low.ensure_binary();\n\
    \        return merge_disjoint_range_high(low, 0, (int)low.d.size(), high, high_shift);\n\
    \    }\n\n    static BigInteger lower_with_high(const BigInteger &x, int low_limbs,\
    \ const BigInteger &high) {\n        x.ensure_binary();\n        if (low_limbs\
    \ <= 0 || x.d.empty()) return shift_left_limbs(high, low_limbs);\n        int\
    \ len = min((int)x.d.size(), low_limbs);\n        return merge_disjoint_range_high(x,\
    \ 0, len, high, low_limbs);\n    }\n\n    static BigInteger block_with_high(const\
    \ BigInteger &x, int index, int num_blocks,\n                                \
    \      int block_length, const BigInteger &high) {\n        x.ensure_binary();\n\
    \        int block_start = index * block_length;\n        if (block_start >= (int)x.d.size())\
    \ return shift_left_limbs(high, block_length);\n        int block_end = index\
    \ == num_blocks - 1 ? (int)x.d.size() : (index + 1) * block_length;\n        if\
    \ (block_end > (int)x.d.size()) return shift_left_limbs(high, block_length);\n\
    \        return merge_disjoint_range_high(x, block_start, block_end, high, block_length);\n\
    \    }\n\n    static BigInteger lower_limbs(const BigInteger &x, int limbs) {\n\
    \        x.ensure_binary();\n        if (limbs <= 0 || x.d.empty()) return BigInteger();\n\
    \        int len = min((int)x.d.size(), limbs);\n        return from_limbs_range(x.d,\
    \ 0, len);\n    }\n\n    static BigInteger upper_limbs(const BigInteger &x, int\
    \ limbs) {\n        x.ensure_binary();\n        if (limbs <= 0) return x;\n  \
    \      if (limbs >= (int)x.d.size()) return BigInteger();\n        return from_limbs_range(x.d,\
    \ limbs, (int)x.d.size());\n    }\n\n    static BigInteger shift_left_limbs(const\
    \ BigInteger &x, int limbs) {\n        x.ensure_binary();\n        if (x.is_zero()\
    \ || limbs <= 0) return x;\n        vector<u32> res;\n        res.reserve((size_t)limbs\
    \ + x.d.size());\n        res.insert(res.end(), (size_t)limbs, 0);\n        res.insert(res.end(),\
    \ x.d.begin(), x.d.end());\n        return from_limbs(std::move(res));\n    }\n\
    \n    static BigInteger ones_limbs(int limbs) {\n        if (limbs <= 0) return\
    \ BigInteger();\n        return from_limbs(vector<u32>((size_t)limbs, BASE_MASK));\n\
    \    }\n\n    static BigInteger get_block(const BigInteger &x, int index, int\
    \ num_blocks, int block_length) {\n        x.ensure_binary();\n        int block_start\
    \ = index * block_length;\n        if (block_start >= (int)x.d.size()) return\
    \ BigInteger();\n        int block_end = index == num_blocks - 1 ? (int)x.d.size()\
    \ : (index + 1) * block_length;\n        if (block_end > (int)x.d.size()) return\
    \ BigInteger();\n        return from_limbs_range(x.d, block_start, block_end);\n\
    \    }\n\n    static void add_shifted_abs(BigInteger &dst, const BigInteger &src,\
    \ int limb_shift) {\n        dst.ensure_binary();\n        src.ensure_binary();\n\
    \        dst.invalidate_decimal();\n        if (src.is_zero()) return;\n     \
    \   size_t need = src.d.size() + (size_t)limb_shift;\n        if (dst.d.size()\
    \ < need) dst.d.resize(need, 0);\n        u64 carry = 0;\n        size_t i = 0;\n\
    \        for (; i < src.d.size(); ++i) {\n            u64 cur = u64(dst.d[i +\
    \ limb_shift]) + src.d[i] + carry;\n            dst.d[i + limb_shift] = u32(cur);\n\
    \            carry = cur >> 32;\n        }\n        size_t pos = i + limb_shift;\n\
    \        while (carry) {\n            if (pos == dst.d.size()) dst.d.push_back(0);\n\
    \            u64 cur = u64(dst.d[pos]) + carry;\n            dst.d[pos] = u32(cur);\n\
    \            carry = cur >> 32;\n            ++pos;\n        }\n        dst.sign\
    \ = 1;\n    }\n\n    static void add_disjoint_abs(BigInteger &dst, const BigInteger\
    \ &src, int limb_shift) {\n        dst.ensure_binary();\n        src.ensure_binary();\n\
    \        dst.invalidate_decimal();\n        if (src.is_zero()) return;\n     \
    \   size_t need = max(dst.d.size(), src.d.size() + (size_t)limb_shift);\n    \
    \    if (dst.d.size() < need) dst.d.resize(need, 0);\n        for (size_t i =\
    \ 0; i < src.d.size(); ++i) dst.d[i + limb_shift] = src.d[i];\n        dst.trim();\n\
    \        if (!dst.is_zero()) dst.sign = 1;\n    }\n\n    static void sub_one_abs(BigInteger\
    \ &x) {\n        x.ensure_binary();\n        x.invalidate_decimal();\n       \
    \ for (size_t i = 0; i < x.d.size(); ++i) {\n            if (x.d[i] != 0) {\n\
    \                --x.d[i];\n                break;\n            }\n          \
    \  x.d[i] = BASE_MASK;\n        }\n        x.trim();\n    }\n\n    static int\
    \ compare_shifted_abs(const BigInteger &a, const BigInteger &b, int limb_shift)\
    \ {\n        a.ensure_binary();\n        b.ensure_binary();\n        int as =\
    \ (int)a.d.size() - limb_shift;\n        int bs = (int)b.d.size();\n        if\
    \ (as != bs) return as < bs ? -1 : 1;\n        for (int i = as - 1; i >= 0; --i)\
    \ {\n            if (a.d[i + limb_shift] != b.d[i]) return a.d[i + limb_shift]\
    \ < b.d[i] ? -1 : 1;\n        }\n        return 0;\n    }\n\n    static void bz_split_divisor(vector<BigInteger>\
    \ &values, vector<int> &high, vector<int> &low,\n                            \
    \     vector<int> &knuth_shift, vector<vector<u32>> &knuth_norm,\n           \
    \                      vector<char> &corr_ready, vector<BigInteger> &shifted_high,\n\
    \                                 vector<BigInteger> &low_gap, int idx) {\n  \
    \      if (high[idx] != -1) return;\n        int half = (int)values[idx].d.size()\
    \ / 2;\n        high[idx] = (int)values.size();\n        values.push_back(upper_limbs(values[idx],\
    \ half));\n        high.push_back(-1);\n        low.push_back(-1);\n        knuth_shift.push_back(-1);\n\
    \        knuth_norm.emplace_back();\n        corr_ready.push_back(0);\n      \
    \  shifted_high.emplace_back();\n        low_gap.emplace_back();\n        low[idx]\
    \ = (int)values.size();\n        values.push_back(lower_limbs(values[idx], half));\n\
    \        high.push_back(-1);\n        low.push_back(-1);\n        knuth_shift.push_back(-1);\n\
    \        knuth_norm.emplace_back();\n        corr_ready.push_back(0);\n      \
    \  shifted_high.emplace_back();\n        low_gap.emplace_back();\n    }\n\n  \
    \  static void bz_prepare_knuth_divisor(const vector<BigInteger> &values, vector<int>\
    \ &knuth_shift,\n                                         vector<vector<u32>>\
    \ &knuth_norm, int idx) {\n        if (knuth_shift[idx] != -1) return;\n     \
    \   const BigInteger &v = values[idx];\n        int shift = __builtin_clz(v.d.back());\n\
    \        knuth_shift[idx] = shift;\n        knuth_norm[idx] = shift ? shift_left_copy_limbs(v.d,\
    \ shift) : v.d;\n    }\n\n    static void bz_prepare_divisor_corrections(vector<BigInteger>\
    \ &div_values, vector<int> &div_high,\n                                      \
    \         vector<int> &div_low, vector<int> &knuth_shift,\n                  \
    \                             vector<vector<u32>> &knuth_norm,\n             \
    \                                  vector<char> &corr_ready,\n               \
    \                                vector<BigInteger> &shifted_high,\n         \
    \                                      vector<BigInteger> &low_gap, int idx) {\n\
    \        if (corr_ready[idx]) return;\n        bz_split_divisor(div_values, div_high,\
    \ div_low, knuth_shift, knuth_norm,\n                         corr_ready, shifted_high,\
    \ low_gap, idx);\n        int n = (int)div_values[idx].d.size() / 2;\n       \
    \ const BigInteger &b1 = div_values[div_high[idx]];\n        const BigInteger\
    \ &b2 = div_values[div_low[idx]];\n        shifted_high[idx] = shift_left_limbs(b1,\
    \ n);\n        low_gap[idx] = shift_left_limbs(b2, n);\n        if (!b2.is_zero())\
    \ low_gap[idx].sub_abs(b2);\n        corr_ready[idx] = 1;\n    }\n\n    static\
    \ BigInteger divmod_knuth_abs(const BigInteger &u0, const BigInteger &v0, BigInteger\
    \ &rem) {\n        u0.ensure_binary();\n        v0.ensure_binary();\n        if\
    \ (v0.is_zero()) {\n            rem = BigInteger();\n            return BigInteger();\n\
    \        }\n        if (u0.compare_abs(v0) < 0) {\n            rem = u0;\n   \
    \         BigInteger q;\n            return q;\n        }\n        if (v0.d.size()\
    \ == 1) {\n            BigInteger q = u0;\n            u32 r = q.div_small_assign(v0.d[0]);\n\
    \            rem = BigInteger(r);\n            if (r == 0) rem.sign = 0;\n   \
    \         else rem.sign = 1;\n            q.sign = q.is_zero() ? 0 : 1;\n    \
    \        return q;\n        }\n\n        int shift = __builtin_clz(v0.d.back());\n\
    \        vector<u32> vn = shift ? shift_left_copy_limbs(v0.d, shift) : v0.d;\n\
    \        return divmod_knuth_abs_prepared(u0, v0, shift, vn, rem);\n    }\n\n\
    \    static BigInteger divmod_knuth_abs_prepared(const BigInteger &u0, const BigInteger\
    \ &v0, int shift,\n                                                const vector<u32>\
    \ &vn, BigInteger &rem) {\n        u0.ensure_binary();\n        v0.ensure_binary();\n\
    \        if (u0.compare_abs(v0) < 0) {\n            rem = u0;\n            return\
    \ BigInteger();\n        }\n        vector<u32> un = shift ? shift_left_copy_limbs(u0.d,\
    \ shift) : u0.d;\n        size_t n = vn.size();\n        size_t m = un.size()\
    \ - n;\n        un.push_back(0);\n\n        BigInteger q;\n        q.sign = 1;\n\
    \        q.d.assign(m + 1, 0);\n\n        for (size_t jj = m + 1; jj-- > 0; )\
    \ {\n            size_t j = jj;\n            u64 numerator = (u64(un[j + n]) <<\
    \ 32) | un[j + n - 1];\n            u64 qhat = numerator / vn[n - 1];\n      \
    \      u64 rhat = numerator % vn[n - 1];\n            if (qhat == BASE) {\n  \
    \              --qhat;\n                rhat += vn[n - 1];\n            }\n  \
    \          if (n >= 2 && rhat < BASE &&\n                qhat * vn[n - 2] > (rhat\
    \ << 32) + un[j + n - 2]) {\n                --qhat;\n                rhat +=\
    \ vn[n - 1];\n                if (rhat < BASE && qhat * vn[n - 2] > (rhat << 32)\
    \ + un[j + n - 2]) {\n                    --qhat;\n                    rhat +=\
    \ vn[n - 1];\n                }\n            }\n\n            u64 carry = 0;\n\
    \            u64 borrow = 0;\n            for (size_t i = 0; i < n; ++i) {\n \
    \               u64 prod = qhat * vn[i] + carry;\n                carry = prod\
    \ >> 32;\n                u64 sub = u64(u32(prod)) + borrow;\n               \
    \ if (u64(un[j + i]) < sub) {\n                    un[j + i] = u32(u64(un[j +\
    \ i]) + BASE - sub);\n                    borrow = 1;\n                } else\
    \ {\n                    un[j + i] = u32(u64(un[j + i]) - sub);\n            \
    \        borrow = 0;\n                }\n            }\n\n            u64 sub\
    \ = carry + borrow;\n            bool negative = false;\n            if (u64(un[j\
    \ + n]) < sub) {\n                un[j + n] = u32(u64(un[j + n]) + BASE - sub);\n\
    \                negative = true;\n            } else {\n                un[j\
    \ + n] = u32(u64(un[j + n]) - sub);\n            }\n\n            if (negative)\
    \ {\n                --qhat;\n                u64 add_carry = 0;\n           \
    \     for (size_t i = 0; i < n; ++i) {\n                    u64 cur = u64(un[j\
    \ + i]) + vn[i] + add_carry;\n                    un[j + i] = u32(cur);\n    \
    \                add_carry = cur >> 32;\n                }\n                un[j\
    \ + n] = u32(u64(un[j + n]) + add_carry);\n            }\n            q.d[j] =\
    \ u32(qhat);\n        }\n\n        q.trim();\n        rem.d.assign(un.begin(),\
    \ un.begin() + n);\n        rem.sign = rem.d.empty() ? 0 : 1;\n        if (shift)\
    \ shift_right_limbs_assign(rem.d, shift);\n        rem.trim();\n        return\
    \ q;\n    }\n\n    static pair<vector<u32>, vector<u32>> divmod_knuth_decimal_blocks(vector<u32>\
    \ u, vector<u32> v) {\n        trim_decimal_blocks(u);\n        trim_decimal_blocks(v);\n\
    \        if (v.empty()) return {{}, {}};\n        if (compare_decimal_blocks(u,\
    \ v) < 0) return {{}, std::move(u)};\n        if (v.size() == 1) {\n         \
    \   vector<u32> q = u;\n            u32 rem = div_small_decimal_blocks_assign(q,\
    \ v[0], DEC_BLOCK);\n            vector<u32> r;\n            if (rem) r.push_back(rem);\n\
    \            return {std::move(q), std::move(r)};\n        }\n\n        u32 norm\
    \ = DEC_BLOCK / (v.back() + 1);\n        vector<u32> un = norm == 1 ? std::move(u)\
    \ : mul_small_decimal_blocks(u, norm, DEC_BLOCK);\n        vector<u32> vn = norm\
    \ == 1 ? std::move(v) : mul_small_decimal_blocks(v, norm, DEC_BLOCK);\n      \
    \  size_t n = vn.size();\n        size_t m = un.size() - n;\n        un.push_back(0);\n\
    \n        vector<u32> q(m + 1, 0);\n        for (size_t jj = m + 1; jj-- > 0;\
    \ ) {\n            size_t j = jj;\n            u64 numerator = u64(un[j + n])\
    \ * DEC_BLOCK + un[j + n - 1];\n            u64 qhat = numerator / vn[n - 1];\n\
    \            u64 rhat = numerator % vn[n - 1];\n            if (qhat == DEC_BLOCK)\
    \ {\n                --qhat;\n                rhat += vn[n - 1];\n           \
    \ }\n            if (n >= 2) {\n                while (rhat < DEC_BLOCK &&\n \
    \                      qhat * vn[n - 2] > rhat * DEC_BLOCK + un[j + n - 2]) {\n\
    \                    --qhat;\n                    rhat += vn[n - 1];\n       \
    \         }\n            }\n\n            u64 carry = 0;\n            u64 borrow\
    \ = 0;\n            for (size_t i = 0; i < n; ++i) {\n                u64 prod\
    \ = qhat * vn[i] + carry;\n                carry = prod / DEC_BLOCK;\n       \
    \         u64 sub = prod % DEC_BLOCK + borrow;\n                if (u64(un[j +\
    \ i]) < sub) {\n                    un[j + i] = u32(u64(un[j + i]) + DEC_BLOCK\
    \ - sub);\n                    borrow = 1;\n                } else {\n       \
    \             un[j + i] = u32(u64(un[j + i]) - sub);\n                    borrow\
    \ = 0;\n                }\n            }\n\n            u64 sub = carry + borrow;\n\
    \            bool negative = false;\n            if (u64(un[j + n]) < sub) {\n\
    \                un[j + n] = u32(u64(un[j + n]) + DEC_BLOCK - sub);\n        \
    \        negative = true;\n            } else {\n                un[j + n] = u32(u64(un[j\
    \ + n]) - sub);\n            }\n\n            if (negative) {\n              \
    \  --qhat;\n                u64 add_carry = 0;\n                for (size_t i\
    \ = 0; i < n; ++i) {\n                    u64 cur = u64(un[j + i]) + vn[i] + add_carry;\n\
    \                    if (cur >= DEC_BLOCK) {\n                        un[j + i]\
    \ = u32(cur - DEC_BLOCK);\n                        add_carry = 1;\n          \
    \          } else {\n                        un[j + i] = u32(cur);\n         \
    \               add_carry = 0;\n                    }\n                }\n   \
    \             un[j + n] = u32(u64(un[j + n]) + add_carry);\n            }\n  \
    \          q[j] = u32(qhat);\n        }\n\n        trim_decimal_blocks(q);\n \
    \       vector<u32> r(un.begin(), un.begin() + n);\n        if (norm != 1) div_small_decimal_blocks_assign(r,\
    \ norm, DEC_BLOCK);\n        trim_decimal_blocks(r);\n        return {std::move(q),\
    \ std::move(r)};\n    }\n\n    static pair<BigInteger, BigInteger> divmod_decimal_abs(const\
    \ BigInteger &u, const BigInteger &v) {\n        if (compare_abs_decimal(u.dec,\
    \ v.dec) < 0) return {BigInteger(), u};\n        vector<u32> un = split_decimal_blocks_le(u.dec,\
    \ DEC_BLOCK_DIGITS);\n        vector<u32> vn = split_decimal_blocks_le(v.dec,\
    \ DEC_BLOCK_DIGITS);\n        auto qr = divmod_knuth_decimal_blocks(std::move(un),\
    \ std::move(vn));\n        return {\n            from_decimal_blocks_abs(std::move(qr.first),\
    \ DEC_BLOCK_DIGITS),\n            from_decimal_blocks_abs(std::move(qr.second),\
    \ DEC_BLOCK_DIGITS)\n        };\n    }\n\n    static bool divmod_decimal_reciprocal_abs(const\
    \ BigInteger &u, const BigInteger &v,\n                                      \
    \        BigInteger &quotient, BigInteger &rem) {\n        if (compare_abs_decimal(u.dec,\
    \ v.dec) < 0) {\n            quotient = BigInteger();\n            rem = u;\n\
    \            return true;\n        }\n        vector<u64> un = split_decimal_blocks_le_u64(u.dec,\
    \ FAST_DEC_BLOCK_DIGITS);\n        vector<u64> vn = split_decimal_blocks_le_u64(v.dec,\
    \ FAST_DEC_BLOCK_DIGITS);\n        FastDecBigint a(std::move(un));\n        FastDecBigint\
    \ b(std::move(vn));\n        if (b.is_zero()) return false;\n        if (b.digits.size()\
    \ == 1) {\n            vector<u64> q = a.digits;\n            u64 divisor = b.digits[0];\n\
    \            u64 carry = 0;\n            for (int i = (int)q.size() - 1; i >=\
    \ 0; --i) {\n                u128 cur = u128(carry) * FAST_DEC_BASE + q[i];\n\
    \                q[i] = u64(cur / divisor);\n                carry = u64(cur %\
    \ divisor);\n            }\n            quotient = from_decimal_blocks_abs_u64(std::move(q),\
    \ FAST_DEC_BLOCK_DIGITS);\n            if (carry == 0) rem = BigInteger();\n \
    \           else rem = from_decimal_blocks_abs_u64(vector<u64>{carry}, FAST_DEC_BLOCK_DIGITS);\n\
    \            return true;\n        }\n\n        FastDecimal A(a);\n        FastDecimal\
    \ B(b);\n        long long precision = A.magnitude() - B.magnitude() + 1;\n  \
    \      if (precision < 0) precision = 0;\n        FastDecBigint q = (A * B.inv(precision)).round();\n\
    \        FastDecBigint r = a - q * b;\n        int correction_steps = 0;\n   \
    \     while (!r.is_zero() && r.negative) {\n            --correction_steps;\n\
    \            if (correction_steps < -8) return false;\n            q -= 1;\n \
    \           r += b;\n        }\n        while (r.compare(b) >= 0) {\n        \
    \    ++correction_steps;\n            if (correction_steps > 8) return false;\n\
    \            q += 1;\n            r -= b;\n        }\n        if (q.negative ||\
    \ r.negative || r.compare(b) >= 0) return false;\n\n        quotient = from_decimal_blocks_abs_u64(std::move(q.digits),\
    \ FAST_DEC_BLOCK_DIGITS);\n        rem = from_decimal_blocks_abs_u64(std::move(r.digits),\
    \ FAST_DEC_BLOCK_DIGITS);\n        return true;\n    }\n\n    static bool should_use_decimal_division(const\
    \ BigInteger &u, const BigInteger &v) {\n        int u_blocks = ((int)u.dec.size()\
    \ + DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;\n        int v_blocks = ((int)v.dec.size()\
    \ + DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;\n        if (u_blocks < v_blocks)\
    \ return true;\n        if (u_blocks <= v_blocks + 2) return true;\n        if\
    \ (v_blocks <= 4) return true;\n        return false;\n    }\n\n    static bool\
    \ should_use_decimal_reciprocal_division(const BigInteger &u, const BigInteger\
    \ &v) {\n        int u_blocks = ((int)u.dec.size() + FAST_DEC_BLOCK_DIGITS - 1)\
    \ / FAST_DEC_BLOCK_DIGITS;\n        int v_blocks = ((int)v.dec.size() + FAST_DEC_BLOCK_DIGITS\
    \ - 1) / FAST_DEC_BLOCK_DIGITS;\n        if (u_blocks < v_blocks || v_blocks <=\
    \ 1) return false;\n        if (u_blocks <= v_blocks + 1) return false;\n    \
    \    return v_blocks >= 4;\n    }\n\n    static BigInteger divide3n2n_abs(const\
    \ BigInteger &a, vector<BigInteger> &div_values,\n                           \
    \          vector<int> &div_high, vector<int> &div_low,\n                    \
    \                 vector<int> &knuth_shift, vector<vector<u32>> &knuth_norm,\n\
    \                                     vector<char> &corr_ready,\n            \
    \                         vector<BigInteger> &shifted_high, vector<BigInteger>\
    \ &low_gap,\n                                     int b_idx, BigInteger &quotient)\
    \ {\n        const BigInteger &b = div_values[b_idx];\n        int n = (int)b.d.size()\
    \ / 2;\n        bz_split_divisor(div_values, div_high, div_low, knuth_shift, knuth_norm,\n\
    \                         corr_ready, shifted_high, low_gap, b_idx);\n       \
    \ const BigInteger &b1 = div_values[div_high[b_idx]];\n        const BigInteger\
    \ &b2 = div_values[div_low[b_idx]];\n        BigInteger a12 = upper_limbs(a, n);\n\
    \        BigInteger r, d;\n        if (compare_shifted_abs(a, b, n) < 0) {\n \
    \           r = divide2n1n_abs(a12, div_values, div_high, div_low,\n         \
    \                      knuth_shift, knuth_norm, corr_ready, shifted_high, low_gap,\n\
    \                               div_high[b_idx], quotient);\n            d = multiply(quotient,\
    \ b2);\n            d.sign = d.is_zero() ? 0 : 1;\n        } else {\n        \
    \    bz_prepare_divisor_corrections(div_values, div_high, div_low, knuth_shift,\
    \ knuth_norm,\n                                           corr_ready, shifted_high,\
    \ low_gap, b_idx);\n            quotient = ones_limbs(n);\n            a12.add_abs(b1);\n\
    \            a12.sub_abs(shifted_high[b_idx]);\n            r = a12;\n       \
    \     d = low_gap[b_idx];\n        }\n        r = lower_with_high(a, n, r);\n\
    \        while (r.compare_abs(d) < 0) {\n            r.add_abs(b);\n         \
    \   sub_one_abs(quotient);\n        }\n        r.sub_abs(d);\n        return r;\n\
    \    }\n\n    static BigInteger divide2n1n_abs(const BigInteger &a, vector<BigInteger>\
    \ &div_values,\n                                     vector<int> &div_high, vector<int>\
    \ &div_low,\n                                     vector<int> &knuth_shift, vector<vector<u32>>\
    \ &knuth_norm,\n                                     vector<char> &corr_ready,\n\
    \                                     vector<BigInteger> &shifted_high, vector<BigInteger>\
    \ &low_gap,\n                                     int b_idx, BigInteger &quotient)\
    \ {\n        const BigInteger &b = div_values[b_idx];\n        int n = (int)b.d.size();\n\
    \        if ((n & 1) || n < BURNIKEL_ZIEGLER_THRESHOLD) {\n            BigInteger\
    \ rem;\n            bz_prepare_knuth_divisor(div_values, knuth_shift, knuth_norm,\
    \ b_idx);\n            quotient = divmod_knuth_abs_prepared(a, b, knuth_shift[b_idx],\
    \ knuth_norm[b_idx], rem);\n            return rem;\n        }\n        int half\
    \ = n / 2;\n        bz_split_divisor(div_values, div_high, div_low, knuth_shift,\
    \ knuth_norm,\n                         corr_ready, shifted_high, low_gap, b_idx);\n\
    \        BigInteger a_upper = upper_limbs(a, half);\n        BigInteger q1;\n\
    \        BigInteger r1 = divide3n2n_abs(a_upper, div_values, div_high, div_low,\n\
    \                                       knuth_shift, knuth_norm, corr_ready, shifted_high,\
    \ low_gap,\n                                       b_idx, q1);\n        BigInteger\
    \ z = lower_with_high(a, half, r1);\n        BigInteger r2 = divide3n2n_abs(z,\
    \ div_values, div_high, div_low,\n                                       knuth_shift,\
    \ knuth_norm, corr_ready, shifted_high, low_gap,\n                           \
    \            b_idx, quotient);\n        quotient = merge_disjoint_abs(quotient,\
    \ q1, half);\n        return r2;\n    }\n\n    static BigInteger divmod_burnikel_ziegler_abs(const\
    \ BigInteger &u, const BigInteger &v, BigInteger &quotient) {\n        u.ensure_binary();\n\
    \        v.ensure_binary();\n        int r = (int)u.d.size();\n        int s =\
    \ (int)v.d.size();\n        quotient = BigInteger();\n        if (r < s) return\
    \ u;\n\n        int m = 1;\n        while ((long long)m * BURNIKEL_ZIEGLER_THRESHOLD\
    \ <= s) m <<= 1;\n        int j = (s + m - 1) / m;\n        int n = j * m;\n \
    \       long long n_bits = 32LL * n;\n        int sigma = max(0LL, n_bits - v.bit_length());\n\
    \        BigInteger b_shifted = v;\n        BigInteger a_shifted = u;\n      \
    \  if (sigma) {\n            b_shifted.shift_left_bits_assign(sigma);\n      \
    \      a_shifted.shift_left_bits_assign(sigma);\n        }\n        int t = (int)((a_shifted.bit_length()\
    \ + n_bits) / n_bits);\n        if (t < 2) t = 2;\n\n        vector<BigInteger>\
    \ div_values;\n        vector<int> div_high;\n        vector<int> div_low;\n \
    \       vector<int> knuth_shift;\n        vector<vector<u32>> knuth_norm;\n  \
    \      vector<char> corr_ready;\n        vector<BigInteger> shifted_high;\n  \
    \      vector<BigInteger> low_gap;\n        div_values.reserve(32);\n        div_high.reserve(32);\n\
    \        div_low.reserve(32);\n        knuth_shift.reserve(32);\n        knuth_norm.reserve(32);\n\
    \        corr_ready.reserve(32);\n        shifted_high.reserve(32);\n        low_gap.reserve(32);\n\
    \        div_values.push_back(b_shifted);\n        div_high.push_back(-1);\n \
    \       div_low.push_back(-1);\n        knuth_shift.push_back(-1);\n        knuth_norm.emplace_back();\n\
    \        corr_ready.push_back(0);\n        shifted_high.emplace_back();\n    \
    \    low_gap.emplace_back();\n        BigInteger a1 = get_block(a_shifted, t -\
    \ 1, t, n);\n        BigInteger z = block_with_high(a_shifted, t - 2, t, n, a1);\n\
    \        BigInteger qi, ri;\n        for (int i = t - 2; i > 0; --i) {\n     \
    \       ri = divide2n1n_abs(z, div_values, div_high, div_low, knuth_shift, knuth_norm,\n\
    \                                corr_ready, shifted_high, low_gap, 0, qi);\n\
    \            z = block_with_high(a_shifted, i - 1, t, n, ri);\n            add_shifted_abs(quotient,\
    \ qi, i * n);\n        }\n        ri = divide2n1n_abs(z, div_values, div_high,\
    \ div_low, knuth_shift, knuth_norm,\n                            corr_ready, shifted_high,\
    \ low_gap, 0, qi);\n        quotient.add_abs(qi);\n        quotient.sign = quotient.is_zero()\
    \ ? 0 : 1;\n        if (sigma) ri.shift_right_bits_assign(sigma);\n        ri.sign\
    \ = ri.is_zero() ? 0 : 1;\n        return ri;\n    }\n\n    static bool normalize_burnikel_ziegler_remainder(BigInteger\
    \ &quotient, BigInteger &rem,\n                                              \
    \       const BigInteger &divisor) {\n        for (int step = 0; step < 3 && rem.compare_abs(divisor)\
    \ >= 0; ++step) {\n            rem.sub_abs(divisor);\n            quotient.add_small_assign(1);\n\
    \        }\n        quotient.sign = quotient.is_zero() ? 0 : 1;\n        rem.sign\
    \ = rem.is_zero() ? 0 : 1;\n        return rem.compare_abs(divisor) < 0;\n   \
    \ }\n\n    static BigInteger divmod_abs(const BigInteger &u0, const BigInteger\
    \ &v0, BigInteger &rem) {\n        u0.ensure_binary();\n        v0.ensure_binary();\n\
    \        if (v0.is_zero()) {\n            rem = BigInteger();\n            return\
    \ BigInteger();\n        }\n        if (u0.compare_abs(v0) < 0) {\n          \
    \  rem = u0;\n            return BigInteger();\n        }\n        if (v0.d.size()\
    \ == 1) {\n            BigInteger q = u0;\n            u32 r = q.div_small_assign(v0.d[0]);\n\
    \            rem = BigInteger(r);\n            rem.sign = r == 0 ? 0 : 1;\n  \
    \          q.sign = q.is_zero() ? 0 : 1;\n            return q;\n        }\n \
    \       if ((int)v0.d.size() >= BURNIKEL_ZIEGLER_THRESHOLD &&\n            (int)u0.d.size()\
    \ - (int)v0.d.size() >= BURNIKEL_ZIEGLER_OFFSET) {\n            BigInteger q;\n\
    \            rem = divmod_burnikel_ziegler_abs(u0, v0, q);\n            if (normalize_burnikel_ziegler_remainder(q,\
    \ rem, v0)) {\n                return q;\n            }\n        }\n        return\
    \ divmod_knuth_abs(u0, v0, rem);\n    }\n\n    static pair<BigInteger, BigInteger>\
    \ divmod_abs(const BigInteger &u, const BigInteger &v) {\n        u.ensure_binary();\n\
    \        v.ensure_binary();\n        BigInteger r;\n        BigInteger q = divmod_abs(u,\
    \ v, r);\n        return {q, r};\n    }\n\n    static pair<BigInteger, BigInteger>\
    \ divmod(const BigInteger &a, const BigInteger &b) {\n        if (b.is_zero())\
    \ return {BigInteger(), BigInteger()};\n        if (a.is_zero()) return {BigInteger(),\
    \ BigInteger()};\n        if (a.decimal_ready && b.decimal_ready && should_use_decimal_division(a,\
    \ b)) {\n            BigInteger aa = a;\n            BigInteger bb = b;\n    \
    \        aa.sign = aa.is_zero() ? 0 : 1;\n            bb.sign = bb.is_zero() ?\
    \ 0 : 1;\n            auto qr = divmod_decimal_abs(aa, bb);\n            BigInteger\
    \ q = qr.first;\n            BigInteger r = qr.second;\n            if (a.sign\
    \ == b.sign) {\n                q.sign = q.is_zero() ? 0 : 1;\n              \
    \  if (!r.is_zero()) r.sign = b.sign;\n                return {q, r};\n      \
    \      }\n            if (r.is_zero()) {\n                q.sign = q.is_zero()\
    \ ? 0 : -1;\n                return {q, r};\n            }\n            BigInteger\
    \ one(\"1\");\n            q += one;\n            q.sign = -1;\n            r\
    \ = bb - r;\n            r.sign = b.sign;\n            if (q.is_zero()) q.sign\
    \ = 0;\n            return {q, r};\n        }\n        if (a.decimal_ready &&\
    \ b.decimal_ready && should_use_decimal_reciprocal_division(a, b)) {\n       \
    \     BigInteger aa = a;\n            BigInteger bb = b;\n            aa.sign\
    \ = aa.is_zero() ? 0 : 1;\n            bb.sign = bb.is_zero() ? 0 : 1;\n     \
    \       BigInteger q, r;\n            if (divmod_decimal_reciprocal_abs(aa, bb,\
    \ q, r)) {\n                if (a.sign == b.sign) {\n                    q.sign\
    \ = q.is_zero() ? 0 : 1;\n                    if (!r.is_zero()) r.sign = b.sign;\n\
    \                    return {q, r};\n                }\n                if (r.is_zero())\
    \ {\n                    q.sign = q.is_zero() ? 0 : -1;\n                    return\
    \ {q, r};\n                }\n                BigInteger one(\"1\");\n       \
    \         q += one;\n                q.sign = -1;\n                r = bb - r;\n\
    \                r.sign = b.sign;\n                if (q.is_zero()) q.sign = 0;\n\
    \                return {q, r};\n            }\n        }\n        a.ensure_binary();\n\
    \        b.ensure_binary();\n        BigInteger aa = a;\n        BigInteger bb\
    \ = b;\n        aa.sign = aa.is_zero() ? 0 : 1;\n        bb.sign = bb.is_zero()\
    \ ? 0 : 1;\n        auto qr = divmod_abs(aa, bb);\n        BigInteger q = qr.first;\n\
    \        BigInteger r = qr.second;\n        if (a.sign == b.sign) {\n        \
    \    q.sign = q.is_zero() ? 0 : 1;\n            if (!r.is_zero()) r.sign = b.sign;\n\
    \            return {q, r};\n        }\n        if (r.is_zero()) {\n         \
    \   q.sign = q.is_zero() ? 0 : -1;\n            return {q, r};\n        }\n  \
    \      BigInteger one = 1;\n        q += one;\n        q.sign = -1;\n        r\
    \ = bb - r;\n        r.sign = b.sign;\n        if (q.is_zero()) q.sign = 0;\n\
    \        return {q, r};\n    }\n\n    void assign(const string &s, int base =\
    \ 10) {\n        d.clear();\n        dec.clear();\n        binary_ready = true;\n\
    \        decimal_ready = false;\n        sign = 0;\n        int p = 0;\n     \
    \   bool neg = false;\n        if (p < (int)s.size() && (s[p] == '+' || s[p] ==\
    \ '-')) {\n            neg = s[p] == '-';\n            ++p;\n        }\n     \
    \   while (p < (int)s.size() && s[p] == '0') ++p;\n        if (p == (int)s.size())\
    \ return;\n        int q = p;\n        while (q < (int)s.size()) {\n         \
    \   int v = digit_value(s[q]);\n            if (v < 0 || v >= base) {\n      \
    \          d.clear();\n                sign = 0;\n                return;\n  \
    \          }\n            ++q;\n        }\n        if (base == 16) {\n       \
    \     for (int i = (int)s.size(); i > p; ) {\n                int l = max(p, i\
    \ - HEX_BLOCK_DIGITS);\n                u32 x = 0;\n                for (int j\
    \ = l; j < i; ++j) {\n                    int v = digit_value(s[j]);\n       \
    \             x = (x << 4) | u32(v);\n                }\n                d.push_back(x);\n\
    \                i = l;\n            }\n            sign = 1;\n            trim();\n\
    \            if (neg && !is_zero()) sign = -1;\n            return;\n        }\n\
    \        if (base == 10) {\n            dec.assign(s.begin() + p, s.end());\n\
    \            binary_ready = false;\n            decimal_ready = true;\n      \
    \      sign = 1;\n            if (neg && !is_zero()) sign = -1;\n            return;\n\
    \        }\n        for (; p < (int)s.size(); ++p) {\n            int v = digit_value(s[p]);\n\
    \            mul_small_assign((u32)base);\n            add_small_assign((u32)v);\n\
    \        }\n        sign = 1;\n        trim();\n        if (neg && !is_zero())\
    \ sign = -1;\n    }\n\n    string to_string(int base = 10) const {\n        if\
    \ (is_zero()) return \"0\";\n        if (base == 16) {\n            ensure_binary();\n\
    \            string res;\n            res.reserve((sign < 0 ? 1 : 0) + (int)d.size()\
    \ * HEX_BLOCK_DIGITS);\n            if (sign < 0) res.push_back('-');\n      \
    \      int i = (int)d.size() - 1;\n            auto append_hex32 = [&](u32 x,\
    \ bool leading) {\n                char buf[8];\n                for (int k =\
    \ 0; k < 8; ++k) {\n                    buf[7 - k] = digit_char((x >> (k * 4))\
    \ & 15);\n                }\n                int start = 0;\n                if\
    \ (leading) {\n                    while (start < 8 && buf[start] == '0') ++start;\n\
    \                }\n                res.append(buf + start, buf + 8);\n      \
    \      };\n            append_hex32(d[i], true);\n            for (--i; i >= 0;\
    \ --i) append_hex32(d[i], false);\n            return res;\n        }\n      \
    \  if (decimal_ready) {\n            string res;\n            res.reserve((sign\
    \ < 0 ? 1 : 0) + dec.size());\n            if (sign < 0) res.push_back('-');\n\
    \            res += dec;\n            return res;\n        }\n        if ((int)d.size()\
    \ <= DEC_TO_STRING_LINEAR_LIMB_THRESHOLD) {\n            BigInteger tmp;\n   \
    \         tmp.sign = 1;\n            tmp.d = d;\n            tmp.binary_ready\
    \ = true;\n            tmp.decimal_ready = false;\n            vector<u32> parts;\n\
    \            parts.reserve((bit_length() + 28) / 29);\n            while (!tmp.is_zero())\
    \ parts.push_back(tmp.div_small_assign(DEC_BLOCK));\n            return build_decimal_string(parts,\
    \ DEC_BLOCK_DIGITS, sign < 0);\n        }\n        vector<u32> parts = limbs_to_decimal(d,\
    \ 0, (int)d.size());\n        return build_decimal_string(parts, DEC_CONV_DIGITS,\
    \ sign < 0);\n    }\n\n    BigInteger operator+() const { return *this; }\n  \
    \  BigInteger operator-() const {\n        BigInteger res = *this;\n        if\
    \ (!res.is_zero()) res.sign = -res.sign;\n        return res;\n    }\n\n    BigInteger\
    \ &operator+=(const BigInteger &rhs) {\n        if (rhs.is_zero()) return *this;\n\
    \        if (this == &rhs) {\n            BigInteger tmp = rhs;\n            return\
    \ *this += tmp;\n        }\n        if (decimal_ready && rhs.decimal_ready) {\n\
    \            if (is_zero()) {\n                *this = rhs;\n                return\
    \ *this;\n            }\n            if (sign == rhs.sign) {\n               \
    \ dec = add_abs_decimal(dec, rhs.dec);\n            } else {\n               \
    \ int c = compare_abs_decimal(dec, rhs.dec);\n                if (c == 0) {\n\
    \                    dec.clear();\n                    decimal_ready = false;\n\
    \                    sign = 0;\n                    binary_ready = true;\n   \
    \                 d.clear();\n                    return *this;\n            \
    \    }\n                if (c > 0) {\n                    dec = sub_abs_decimal(dec,\
    \ rhs.dec);\n                } else {\n                    dec = sub_abs_decimal(rhs.dec,\
    \ dec);\n                    sign = rhs.sign;\n                }\n           \
    \ }\n            d.clear();\n            binary_ready = false;\n            decimal_ready\
    \ = true;\n            return *this;\n        }\n        ensure_binary();\n  \
    \      rhs.ensure_binary();\n        invalidate_decimal();\n        if (is_zero())\
    \ {\n            *this = rhs;\n            return *this;\n        }\n        if\
    \ (sign == rhs.sign) {\n            add_abs(rhs);\n            sign = rhs.sign;\n\
    \            return *this;\n        }\n        int c = compare_abs(rhs);\n   \
    \     if (c == 0) {\n            d.clear();\n            sign = 0;\n        }\
    \ else if (c > 0) {\n            sub_abs(rhs);\n        } else {\n           \
    \ BigInteger tmp = rhs;\n            tmp.sub_abs(*this);\n            *this =\
    \ tmp;\n        }\n        return *this;\n    }\n\n    BigInteger &operator-=(const\
    \ BigInteger &rhs) {\n        if (rhs.is_zero()) return *this;\n        BigInteger\
    \ tmp = rhs;\n        tmp.sign = -tmp.sign;\n        return *this += tmp;\n  \
    \  }\n\n    BigInteger &operator*=(const BigInteger &rhs) {\n        if (is_zero()\
    \ || rhs.is_zero()) {\n            d.clear();\n            dec.clear();\n    \
    \        binary_ready = true;\n            decimal_ready = false;\n          \
    \  sign = 0;\n            return *this;\n        }\n        BigInteger a = *this;\n\
    \        BigInteger b = rhs;\n        *this = multiply(a, b);\n        return\
    \ *this;\n    }\n\n    BigInteger &operator/=(const BigInteger &rhs) {\n     \
    \   ensure_binary();\n        rhs.ensure_binary();\n        invalidate_decimal();\n\
    \        *this = divmod(*this, rhs).first;\n        return *this;\n    }\n\n \
    \   BigInteger &operator%=(const BigInteger &rhs) {\n        ensure_binary();\n\
    \        rhs.ensure_binary();\n        invalidate_decimal();\n        *this =\
    \ divmod(*this, rhs).second;\n        return *this;\n    }\n\n    BigInteger &operator<<=(int\
    \ bits) {\n        ensure_binary();\n        invalidate_decimal();\n        if\
    \ (bits < 0) return *this >>= -bits;\n        if (is_zero()) return *this;\n \
    \       shift_left_bits_assign(bits);\n        return *this;\n    }\n\n    BigInteger\
    \ &operator>>=(int bits) {\n        ensure_binary();\n        invalidate_decimal();\n\
    \        if (bits < 0) return *this <<= -bits;\n        if (is_zero() || bits\
    \ == 0) return *this;\n        if (sign > 0) {\n            shift_right_bits_assign(bits);\n\
    \            return *this;\n        }\n        BigInteger p = 1;\n        p <<=\
    \ bits;\n        *this = divmod(*this, p).first;\n        return *this;\n    }\n\
    \n    friend BigInteger operator+(BigInteger lhs, const BigInteger &rhs) { return\
    \ lhs += rhs; }\n    friend BigInteger operator-(BigInteger lhs, const BigInteger\
    \ &rhs) { return lhs -= rhs; }\n    friend BigInteger operator*(BigInteger lhs,\
    \ const BigInteger &rhs) { return lhs *= rhs; }\n    friend BigInteger operator/(BigInteger\
    \ lhs, const BigInteger &rhs) { return lhs /= rhs; }\n    friend BigInteger operator%(BigInteger\
    \ lhs, const BigInteger &rhs) { return lhs %= rhs; }\n    friend BigInteger operator<<(BigInteger\
    \ lhs, int bits) { return lhs <<= bits; }\n    friend BigInteger operator>>(BigInteger\
    \ lhs, int bits) { return lhs >>= bits; }\n\n    friend bool operator==(const\
    \ BigInteger &a, const BigInteger &b) { return compare(a, b) == 0; }\n    friend\
    \ bool operator!=(const BigInteger &a, const BigInteger &b) { return compare(a,\
    \ b) != 0; }\n    friend bool operator<(const BigInteger &a, const BigInteger\
    \ &b) { return compare(a, b) < 0; }\n    friend bool operator<=(const BigInteger\
    \ &a, const BigInteger &b) { return compare(a, b) <= 0; }\n    friend bool operator>(const\
    \ BigInteger &a, const BigInteger &b) { return compare(a, b) > 0; }\n    friend\
    \ bool operator>=(const BigInteger &a, const BigInteger &b) { return compare(a,\
    \ b) >= 0; }\n};\n\n\n\n/**\n * @brief \u591A\u500D\u9577\u6574\u6570(BigInteger)\n\
    \ */\n"
  code: "#ifndef FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP\n#define FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP\n\
    \nnamespace BigIntegerExactConvolution {\n    using u32 = unsigned int;\n    using\
    \ u64 = unsigned long long;\n\n    constexpr int NAIVE_THRESHOLD = 128;\n\n  \
    \  template <u32 MOD, u32 PRIMITIVE_ROOT>\n    struct ModInt {\n        u32 val;\n\
    \        ModInt() : val(0) {}\n        template <class T>\n        ModInt(T v)\
    \ {\n            long long x = (long long)(v % (long long)MOD);\n            if\
    \ (x < 0) x += MOD;\n            val = (u32)x;\n        }\n        static ModInt\
    \ raw(u32 v) {\n            ModInt x;\n            x.val = v;\n            return\
    \ x;\n        }\n        ModInt &operator+=(const ModInt &rhs) {\n           \
    \ val += rhs.val;\n            if (val >= MOD) val -= MOD;\n            return\
    \ *this;\n        }\n        ModInt &operator-=(const ModInt &rhs) {\n       \
    \     val -= rhs.val;\n            if (val >= MOD) val += MOD;\n            return\
    \ *this;\n        }\n        ModInt &operator*=(const ModInt &rhs) {\n       \
    \     val = (u32)((u64)val * rhs.val % MOD);\n            return *this;\n    \
    \    }\n        ModInt pow(long long n) const {\n            ModInt x = *this,\
    \ r = 1;\n            while (n) {\n                if (n & 1) r *= x;\n      \
    \          x *= x;\n                n >>= 1;\n            }\n            return\
    \ r;\n        }\n        ModInt inv() const { return pow(MOD - 2); }\n       \
    \ friend ModInt operator+(ModInt lhs, const ModInt &rhs) { return lhs += rhs;\
    \ }\n        friend ModInt operator-(ModInt lhs, const ModInt &rhs) { return lhs\
    \ -= rhs; }\n        friend ModInt operator*(ModInt lhs, const ModInt &rhs) {\
    \ return lhs *= rhs; }\n    };\n\n    template <u32 MOD, u32 PRIMITIVE_ROOT>\n\
    \    struct NTT {\n        using mint = ModInt<MOD, PRIMITIVE_ROOT>;\n       \
    \ mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30], inv_pow2[30];\n\
    \        int max_base;\n\n        NTT() : max_base(__builtin_ctz(MOD - 1)) {\n\
    \            mint e = mint(PRIMITIVE_ROOT).pow((MOD - 1) >> max_base), ie = e.inv();\n\
    \            for (int i = max_base; i >= 0; --i) {\n                root[i] =\
    \ e;\n                iroot[i] = ie;\n                e *= e;\n              \
    \  ie *= ie;\n            }\n            mint prod = 1, iprod = 1;\n         \
    \   for (int i = 0; i <= max_base - 2; ++i) {\n                rate2[i] = root[i\
    \ + 2] * prod;\n                irate2[i] = iroot[i + 2] * iprod;\n          \
    \      prod *= iroot[i + 2];\n                iprod *= root[i + 2];\n        \
    \    }\n            prod = 1;\n            iprod = 1;\n            for (int i\
    \ = 0; i <= max_base - 3; ++i) {\n                rate3[i] = root[i + 3] * prod;\n\
    \                irate3[i] = iroot[i + 3] * iprod;\n                prod *= iroot[i\
    \ + 3];\n                iprod *= root[i + 3];\n            }\n            inv_pow2[0]\
    \ = 1;\n            mint inv2 = mint(2).inv();\n            for (int i = 1; i\
    \ < 30; ++i) inv_pow2[i] = inv_pow2[i - 1] * inv2;\n        }\n\n        mint\
    \ inv_size(int n) const {\n            return inv_pow2[__builtin_ctz((unsigned\
    \ int)n)];\n        }\n\n        void transform(vector<mint> &a, bool invert)\
    \ const {\n            int n = (int)a.size();\n            assert(n > 0);\n  \
    \          assert((n & (n - 1)) == 0);\n            assert(__builtin_ctz((unsigned\
    \ int)n) <= max_base);\n            int h = __builtin_ctz((unsigned int)n);\n\
    \            if (!invert) {\n                int len = 0;\n                while\
    \ (len < h) {\n                    if (h - len == 1) {\n                     \
    \   int p = 1 << (h - len - 1);\n                        mint rot = 1;\n     \
    \                   for (int s = 0; s < (1 << len); ++s) {\n                 \
    \           int offset = s << (h - len);\n                            for (int\
    \ i = 0; i < p; ++i) {\n                                mint l = a[i + offset];\n\
    \                                mint r = a[i + offset + p] * rot;\n         \
    \                       a[i + offset] = l + r;\n                             \
    \   a[i + offset + p] = l - r;\n                            }\n              \
    \              if (s + 1 != (1 << len)) {\n                                rot\
    \ *= rate2[__builtin_ctz(~(unsigned int)s)];\n                            }\n\
    \                        }\n                        ++len;\n                 \
    \   } else {\n                        int p = 1 << (h - len - 2);\n          \
    \              mint rot = 1, imag = root[2];\n                        u64 mod2\
    \ = (u64)MOD * MOD;\n                        for (int s = 0; s < (1 << len); ++s)\
    \ {\n                            mint rot2 = rot * rot;\n                    \
    \        mint rot3 = rot2 * rot;\n                            int offset = s <<\
    \ (h - len);\n                            for (int i = 0; i < p; ++i) {\n    \
    \                            u64 a0 = a[i + offset].val;\n                   \
    \             u64 a1 = (u64)a[i + offset + p].val * rot.val;\n               \
    \                 u64 a2 = (u64)a[i + offset + 2 * p].val * rot2.val;\n      \
    \                          u64 a3 = (u64)a[i + offset + 3 * p].val * rot3.val;\n\
    \                                u64 a1na3imag = (u64)mint(a1 + mod2 - a3).val\
    \ * imag.val;\n                                u64 na2 = mod2 - a2;\n        \
    \                        a[i + offset] = mint(a0 + a2 + a1 + a3);\n          \
    \                      a[i + offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));\n\
    \                                a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);\n\
    \                                a[i + offset + 3 * p] = mint(a0 + na2 + (mod2\
    \ - a1na3imag));\n                            }\n                            if\
    \ (s + 1 != (1 << len)) {\n                                rot *= rate3[__builtin_ctz(~(unsigned\
    \ int)s)];\n                            }\n                        }\n       \
    \                 len += 2;\n                    }\n                }\n      \
    \      } else {\n                int len = h;\n                while (len) {\n\
    \                    if (len == 1) {\n                        int p = 1 << (h\
    \ - len);\n                        mint irot = 1;\n                        for\
    \ (int s = 0; s < (1 << (len - 1)); ++s) {\n                            int offset\
    \ = s << (h - len + 1);\n                            for (int i = 0; i < p; ++i)\
    \ {\n                                mint l = a[i + offset];\n               \
    \                 mint r = a[i + offset + p];\n                              \
    \  a[i + offset] = l + r;\n                                a[i + offset + p] =\
    \ mint((u64)(MOD + l.val - r.val) * irot.val);\n                            }\n\
    \                            if (s + 1 != (1 << (len - 1))) {\n              \
    \                  irot *= irate2[__builtin_ctz(~(unsigned int)s)];\n        \
    \                    }\n                        }\n                        --len;\n\
    \                    } else {\n                        int p = 1 << (h - len);\n\
    \                        mint irot = 1, iimag = iroot[2];\n                  \
    \      for (int s = 0; s < (1 << (len - 2)); ++s) {\n                        \
    \    mint irot2 = irot * irot;\n                            mint irot3 = irot2\
    \ * irot;\n                            int offset = s << (h - len + 2);\n    \
    \                        for (int i = 0; i < p; ++i) {\n                     \
    \           u64 a0 = a[i + offset].val;\n                                u64 a1\
    \ = a[i + offset + p].val;\n                                u64 a2 = a[i + offset\
    \ + 2 * p].val;\n                                u64 a3 = a[i + offset + 3 * p].val;\n\
    \                                u64 a2na3iimag = (u64)mint((u64)(MOD + a2 - a3)\
    \ * iimag.val).val;\n                                a[i + offset] = mint(a0 +\
    \ a1 + a2 + a3);\n                                a[i + offset + p] = mint(a0\
    \ + (MOD - a1) + a2na3iimag) * irot;\n                                a[i + offset\
    \ + 2 * p] = mint(a0 + a1 + (MOD - a2) + (MOD - a3)) * irot2;\n              \
    \                  a[i + offset + 3 * p] = mint(a0 + (MOD - a1) + (MOD - a2na3iimag))\
    \ * irot3;\n                            }\n                            if (s +\
    \ 1 != (1 << (len - 2))) {\n                                irot *= irate3[__builtin_ctz(~(unsigned\
    \ int)s)];\n                            }\n                        }\n       \
    \                 len -= 2;\n                    }\n                }\n      \
    \      }\n        }\n    };\n\n    using NTT1 = NTT<998244353u, 3u>;\n    using\
    \ NTT2 = NTT<1004535809u, 3u>;\n\n    inline const NTT1 &ntt1() {\n        static\
    \ const NTT1 value;\n        return value;\n    }\n\n    inline const NTT2 &ntt2()\
    \ {\n        static const NTT2 value;\n        return value;\n    }\n\n    inline\
    \ u64 combine_u64(u32 x1, u32 x2) {\n        static constexpr u64 m1 = 998244353ULL;\n\
    \        static constexpr u64 m2 = 1004535809ULL;\n        static const u64 m1_inv_m2\
    \ = ModInt<1004535809u, 3u>(m1).inv().val;\n        u64 t = (x2 + m2 - (x1 % m2))\
    \ % m2;\n        u64 k = t * m1_inv_m2 % m2;\n        return x1 + m1 * k;\n  \
    \  }\n\n    inline vector<u64> convolution_u64(const vector<u32> &a, const vector<u32>\
    \ &b) {\n        if (a.empty() || b.empty()) return {};\n        if ((int)min(a.size(),\
    \ b.size()) <= NAIVE_THRESHOLD) {\n            vector<u64> res(a.size() + b.size()\
    \ - 1, 0);\n            for (size_t i = 0; i < a.size(); ++i) {\n            \
    \    for (size_t j = 0; j < b.size(); ++j) {\n                    res[i + j] +=\
    \ (u64)a[i] * b[j];\n                }\n            }\n            return res;\n\
    \        }\n        int need = (int)a.size() + (int)b.size() - 1;\n        int\
    \ n = 1;\n        while (n < need) n <<= 1;\n\n        vector<typename NTT1::mint>\
    \ a1(n), b1(n);\n        vector<typename NTT2::mint> a2(n), b2(n);\n        for\
    \ (int i = 0; i < (int)a.size(); ++i) {\n            a1[i] = a[i];\n         \
    \   a2[i] = a[i];\n        }\n        for (int i = 0; i < (int)b.size(); ++i)\
    \ {\n            b1[i] = b[i];\n            b2[i] = b[i];\n        }\n       \
    \ ntt1().transform(a1, false);\n        ntt1().transform(b1, false);\n       \
    \ ntt2().transform(a2, false);\n        ntt2().transform(b2, false);\n       \
    \ for (int i = 0; i < n; ++i) {\n            a1[i] *= b1[i];\n            a2[i]\
    \ *= b2[i];\n        }\n        ntt1().transform(a1, true);\n        ntt2().transform(a2,\
    \ true);\n        typename NTT1::mint inv1 = ntt1().inv_size(n);\n        typename\
    \ NTT2::mint inv2 = ntt2().inv_size(n);\n        vector<u64> res(need);\n    \
    \    for (int i = 0; i < need; ++i) {\n            res[i] = combine_u64((a1[i]\
    \ * inv1).val, (a2[i] * inv2).val);\n        }\n        return res;\n    }\n}\n\
    \nstruct BigInteger {\n    using u32 = unsigned int;\n    using u64 = unsigned\
    \ long long;\n    using u128 = __uint128_t;\n\n    static constexpr u64 BASE =\
    \ 1ULL << 32;\n    static constexpr u32 BASE_MASK = 0xffffffffu;\n    static constexpr\
    \ u32 DEC_BLOCK = 1000000000u;\n    static constexpr int DEC_BLOCK_DIGITS = 9;\n\
    \    static constexpr u64 FAST_DEC_BASE = 10000000000000000ULL;\n    static constexpr\
    \ int FAST_DEC_BLOCK_DIGITS = 16;\n    static constexpr u32 FAST_DEC_META_BASE\
    \ = 10000u;\n    static constexpr int FAST_DEC_META_DIGITS = 4;\n    static constexpr\
    \ u32 DEC_CONV_BASE = 1000000u;\n    static constexpr int DEC_CONV_DIGITS = 6;\n\
    \    static constexpr int HEX_BLOCK_DIGITS = 8;\n    static constexpr int DEC_ASSIGN_LINEAR_BLOCK_THRESHOLD\
    \ = 256;\n    static constexpr int DEC_TO_STRING_LINEAR_LIMB_THRESHOLD = 256;\n\
    \    static constexpr int MUL_SCHOOLBOOK_LIMB_THRESHOLD = 32;\n    static constexpr\
    \ int MUL_SCHOOLBOOK_AREA_THRESHOLD = 262144;\n    static constexpr int BURNIKEL_ZIEGLER_THRESHOLD\
    \ = 64;\n    static constexpr int BURNIKEL_ZIEGLER_OFFSET = 32;\n\n    mutable\
    \ vector<u32> d;\n    int sign;\n    mutable string dec;\n    mutable bool binary_ready;\n\
    \    mutable bool decimal_ready;\n\n    BigInteger() : d(), sign(0), dec(), binary_ready(true),\
    \ decimal_ready(false) {}\n    BigInteger(long long x) { *this = x; }\n    BigInteger(const\
    \ string &s, int base = 10) { assign(s, base); }\n\n    BigInteger &operator=(long\
    \ long x) {\n        d.clear();\n        dec.clear();\n        decimal_ready =\
    \ false;\n        binary_ready = true;\n        if (x == 0) {\n            sign\
    \ = 0;\n            return *this;\n        }\n        sign = x < 0 ? -1 : 1;\n\
    \        u64 y;\n        if (x < 0) y = u64(-(x + 1)) + 1;\n        else y = u64(x);\n\
    \        while (y) {\n            d.push_back(u32(y & BASE_MASK));\n         \
    \   y >>= 32;\n        }\n        return *this;\n    }\n\n    static int digit_value(char\
    \ c) {\n        if ('0' <= c && c <= '9') return c - '0';\n        if ('a' <=\
    \ c && c <= 'z') return c - 'a' + 10;\n        if ('A' <= c && c <= 'Z') return\
    \ c - 'A' + 10;\n        return -1;\n    }\n\n    static char digit_char(int x)\
    \ {\n        return x < 10 ? char('0' + x) : char('a' + (x - 10));\n    }\n\n\
    \    void invalidate_decimal() {\n        dec.clear();\n        decimal_ready\
    \ = false;\n    }\n\n    static int compare_abs_decimal(const string &a, const\
    \ string &b) {\n        if (a.size() != b.size()) return a.size() < b.size() ?\
    \ -1 : 1;\n        if (a == b) return 0;\n        return a < b ? -1 : 1;\n   \
    \ }\n\n    static string add_abs_decimal(const string &a, const string &b) {\n\
    \        string res(max(a.size(), b.size()) + 1, '0');\n        int i = (int)a.size()\
    \ - 1;\n        int j = (int)b.size() - 1;\n        int k = (int)res.size() -\
    \ 1;\n        int carry = 0;\n        while (i >= 0 || j >= 0 || carry) {\n  \
    \          int x = carry;\n            if (i >= 0) x += a[i--] - '0';\n      \
    \      if (j >= 0) x += b[j--] - '0';\n            res[k--] = char('0' + (x %\
    \ 10));\n            carry = x / 10;\n        }\n        while (i >= 0) res[k--]\
    \ = a[i--];\n        while (j >= 0) res[k--] = b[j--];\n        return res.substr(k\
    \ + 1);\n    }\n\n    static string sub_abs_decimal(const string &a, const string\
    \ &b) {\n        string res(a.size(), '0');\n        int i = (int)a.size() - 1;\n\
    \        int j = (int)b.size() - 1;\n        int borrow = 0;\n        for (int\
    \ k = (int)res.size() - 1; k >= 0; --k, --i, --j) {\n            int x = (a[i]\
    \ - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);\n            if (x < 0) {\n   \
    \             x += 10;\n                borrow = 1;\n            } else {\n  \
    \              borrow = 0;\n            }\n            res[k] = char('0' + x);\n\
    \        }\n        int p = 0;\n        while (p + 1 < (int)res.size() && res[p]\
    \ == '0') ++p;\n        return res.substr(p);\n    }\n\n    static vector<u32>\
    \ split_decimal_blocks(const string &s) {\n        vector<u32> blocks;\n     \
    \   if (s.empty()) return blocks;\n        int block_count = ((int)s.size() +\
    \ DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;\n        blocks.reserve(block_count);\n\
    \        int first = (int)s.size() % DEC_BLOCK_DIGITS;\n        if (first == 0)\
    \ first = DEC_BLOCK_DIGITS;\n        for (int i = 0; i < (int)s.size(); ) {\n\
    \            int width = blocks.empty() ? first : DEC_BLOCK_DIGITS;\n        \
    \    int r = min((int)s.size(), i + width);\n            u32 x = 0;\n        \
    \    for (int j = i; j < r; ++j) x = x * 10 + u32(s[j] - '0');\n            blocks.push_back(x);\n\
    \            i = r;\n        }\n        return blocks;\n    }\n\n    static vector<u32>\
    \ split_decimal_blocks_le(const string &s, int block_digits) {\n        vector<u32>\
    \ blocks;\n        if (s.empty()) return blocks;\n        int block_count = ((int)s.size()\
    \ + block_digits - 1) / block_digits;\n        blocks.reserve(block_count);\n\
    \        for (int r = (int)s.size(); r > 0; r -= block_digits) {\n           \
    \ int l = max(0, r - block_digits);\n            u32 x = 0;\n            for (int\
    \ i = l; i < r; ++i) x = x * 10 + u32(s[i] - '0');\n            blocks.push_back(x);\n\
    \        }\n        return blocks;\n    }\n\n    static vector<u64> split_decimal_blocks_le_u64(const\
    \ string &s, int block_digits) {\n        vector<u64> blocks;\n        if (s.empty())\
    \ return blocks;\n        int block_count = ((int)s.size() + block_digits - 1)\
    \ / block_digits;\n        blocks.reserve(block_count);\n        for (int r =\
    \ (int)s.size(); r > 0; r -= block_digits) {\n            int l = max(0, r - block_digits);\n\
    \            u64 x = 0;\n            for (int i = l; i < r; ++i) x = x * 10 +\
    \ u64(s[i] - '0');\n            blocks.push_back(x);\n        }\n        return\
    \ blocks;\n    }\n\n    static void trim_decimal_blocks(vector<u32> &blocks) {\n\
    \        while (!blocks.empty() && blocks.back() == 0) blocks.pop_back();\n  \
    \  }\n\n    static void trim_decimal_blocks_u64(vector<u64> &blocks) {\n     \
    \   while (!blocks.empty() && blocks.back() == 0) blocks.pop_back();\n    }\n\n\
    \    static int compare_decimal_blocks(const vector<u32> &a, const vector<u32>\
    \ &b) {\n        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;\n\
    \        for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (a[i]\
    \ != b[i]) return a[i] < b[i] ? -1 : 1;\n        }\n        return 0;\n    }\n\
    \n    static int compare_decimal_blocks_u64(const vector<u64> &a, const vector<u64>\
    \ &b) {\n        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;\n\
    \        for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (a[i]\
    \ != b[i]) return a[i] < b[i] ? -1 : 1;\n        }\n        return 0;\n    }\n\
    \n    static vector<u32> mul_small_decimal_blocks(const vector<u32> &a, u32 m,\
    \ u32 base) {\n        if (a.empty() || m == 0) return {};\n        if (m == 1)\
    \ return a;\n        vector<u32> res;\n        res.reserve(a.size() + 1);\n  \
    \      u64 carry = 0;\n        for (u32 x : a) {\n            u64 cur = u64(x)\
    \ * m + carry;\n            res.push_back(u32(cur % base));\n            carry\
    \ = cur / base;\n        }\n        if (carry) res.push_back(u32(carry));\n  \
    \      trim_decimal_blocks(res);\n        return res;\n    }\n\n    static u32\
    \ div_small_decimal_blocks_assign(vector<u32> &a, u32 m, u32 base) {\n       \
    \ u64 rem = 0;\n        for (int i = (int)a.size() - 1; i >= 0; --i) {\n     \
    \       u64 cur = rem * base + a[i];\n            a[i] = u32(cur / m);\n     \
    \       rem = cur % m;\n        }\n        trim_decimal_blocks(a);\n        return\
    \ u32(rem);\n    }\n\n    template <class T>\n    static void ensure_pow_cache_size(vector<T>\
    \ &cache, vector<char> &ready, int n) {\n        if ((int)cache.size() > n) return;\n\
    \        cache.resize(n + 1);\n        ready.resize(n + 1, 0);\n    }\n\n    static\
    \ string build_decimal_string(const vector<u32> &parts, int block_digits, bool\
    \ negative) {\n        string res;\n        res.reserve((negative ? 1 : 0) + decimal_digits_u32(parts.back())\
    \ +\n                    max(0, (int)parts.size() - 1) * block_digits);\n    \
    \    if (negative) res.push_back('-');\n        append_u32_decimal(res, parts.back());\n\
    \        for (int i = (int)parts.size() - 2; i >= 0; --i) {\n            append_u32_decimal_padded(res,\
    \ parts[i], block_digits);\n        }\n        return res;\n    }\n\n    static\
    \ BigInteger from_decimal_blocks_abs(vector<u32> parts, int block_digits) {\n\
    \        trim_decimal_blocks(parts);\n        if (parts.empty()) return BigInteger();\n\
    \        BigInteger res;\n        res.sign = 1;\n        res.dec = build_decimal_string(parts,\
    \ block_digits, false);\n        res.binary_ready = false;\n        res.decimal_ready\
    \ = true;\n        return res;\n    }\n\n    void ensure_binary() const {\n  \
    \      if (binary_ready) return;\n        d.clear();\n        if (sign == 0) {\n\
    \            binary_ready = true;\n            return;\n        }\n        vector<u32>\
    \ blocks = split_decimal_blocks(dec);\n        int block_count = (int)blocks.size();\n\
    \        if (block_count <= DEC_ASSIGN_LINEAR_BLOCK_THRESHOLD) {\n           \
    \ BigInteger tmp;\n            tmp.sign = 1;\n            tmp.d.clear();\n   \
    \         tmp.binary_ready = true;\n            tmp.decimal_ready = false;\n \
    \           for (u32 x : blocks) {\n                tmp.mul_small_assign(DEC_BLOCK);\n\
    \                tmp.add_small_assign(x);\n            }\n            d = std::move(tmp.d);\n\
    \        } else {\n            BigInteger tmp = from_decimal_blocks(blocks, 0,\
    \ (int)blocks.size());\n            d = std::move(tmp.d);\n        }\n       \
    \ binary_ready = true;\n    }\n\n    bool is_zero() const { return sign == 0;\
    \ }\n\n    int bit_length() const {\n        if (is_zero()) return 0;\n      \
    \  ensure_binary();\n        return 32 * ((int)d.size() - 1) + 32 - __builtin_clz(d.back());\n\
    \    }\n\n    static vector<BigInteger> &decimal_pow_cache() {\n        static\
    \ vector<BigInteger> cache = [] {\n            vector<BigInteger> v(2);\n    \
    \        v[0] = BigInteger(1);\n            v[1] = BigInteger((long long)DEC_BLOCK);\n\
    \            return v;\n        }();\n        return cache;\n    }\n\n    static\
    \ vector<char> &decimal_pow_ready() {\n        static vector<char> ready = {1,\
    \ 1};\n        return ready;\n    }\n\n    static const BigInteger &decimal_pow_blocks(int\
    \ blocks) {\n        auto &cache = decimal_pow_cache();\n        auto &ready =\
    \ decimal_pow_ready();\n        ensure_pow_cache_size(cache, ready, blocks);\n\
    \        if (ready[blocks]) return cache[blocks];\n        int left = blocks >>\
    \ 1;\n        int right = blocks - left;\n        cache[blocks] = decimal_pow_blocks(left)\
    \ * decimal_pow_blocks(right);\n        ready[blocks] = 1;\n        return cache[blocks];\n\
    \    }\n\n    static BigInteger from_decimal_blocks(const vector<u32> &blocks,\
    \ int l, int r) {\n        if (l >= r) return BigInteger();\n        if (r - l\
    \ <= 32) {\n            BigInteger res;\n            for (int i = l; i < r; ++i)\
    \ {\n                res.mul_small_assign(DEC_BLOCK);\n                res.add_small_assign(blocks[i]);\n\
    \            }\n            return res;\n        }\n        int m = (l + r) >>\
    \ 1;\n        BigInteger left = from_decimal_blocks(blocks, l, m);\n        BigInteger\
    \ right = from_decimal_blocks(blocks, m, r);\n        if (!left.is_zero()) left\
    \ *= decimal_pow_blocks(r - m);\n        left += right;\n        return left;\n\
    \    }\n\n    static vector<u32> mul_decimal_vectors(const vector<u32> &a, const\
    \ vector<u32> &b) {\n        if (a.empty() || b.empty()) return {};\n        if\
    \ (min(a.size(), b.size()) <= 32 || a.size() * b.size() <= 4096) {\n         \
    \   vector<u32> res(a.size() + b.size(), 0);\n            for (size_t i = 0; i\
    \ < a.size(); ++i) {\n                u64 carry = 0;\n                size_t j\
    \ = 0;\n                for (; j < b.size(); ++j) {\n                    u128\
    \ cur = u128(a[i]) * b[j] + res[i + j] + carry;\n                    res[i + j]\
    \ = u32(cur % DEC_CONV_BASE);\n                    carry = u64(cur / DEC_CONV_BASE);\n\
    \                }\n                size_t pos = i + j;\n                while\
    \ (carry) {\n                    u64 cur = u64(res[pos]) + carry;\n          \
    \          res[pos] = u32(cur % DEC_CONV_BASE);\n                    carry = cur\
    \ / DEC_CONV_BASE;\n                    ++pos;\n                }\n          \
    \  }\n            while (!res.empty() && res.back() == 0) res.pop_back();\n  \
    \          return res;\n        }\n        auto conv = BigIntegerExactConvolution::convolution_u64(a,\
    \ b);\n        vector<u32> res;\n        res.reserve(conv.size() + 3);\n     \
    \   u64 carry = 0;\n        for (u64 v : conv) {\n            u64 cur = v + carry;\n\
    \            res.push_back(u32(cur % DEC_CONV_BASE));\n            carry = cur\
    \ / DEC_CONV_BASE;\n        }\n        while (carry) {\n            res.push_back(u32(carry\
    \ % DEC_CONV_BASE));\n            carry /= DEC_CONV_BASE;\n        }\n       \
    \ while (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n\
    \    }\n\n    static vector<u32> add_decimal_vectors(vector<u32> a, const vector<u32>\
    \ &b) {\n        if (a.size() < b.size()) a.resize(b.size(), 0);\n        u64\
    \ carry = 0;\n        size_t i = 0;\n        for (; i < b.size(); ++i) {\n   \
    \         u64 cur = u64(a[i]) + b[i] + carry;\n            a[i] = u32(cur % DEC_CONV_BASE);\n\
    \            carry = cur / DEC_CONV_BASE;\n        }\n        for (; i < a.size()\
    \ && carry; ++i) {\n            u64 cur = u64(a[i]) + carry;\n            a[i]\
    \ = u32(cur % DEC_CONV_BASE);\n            carry = cur / DEC_CONV_BASE;\n    \
    \    }\n        if (carry) a.push_back(u32(carry));\n        while (!a.empty()\
    \ && a.back() == 0) a.pop_back();\n        return a;\n    }\n\n    static vector<vector<u32>>\
    \ &binary_pow_decimal_cache() {\n        static vector<vector<u32>> cache = {{1},\
    \ {967296u, 4294u}};\n        return cache;\n    }\n\n    static vector<char>\
    \ &binary_pow_decimal_ready() {\n        static vector<char> ready = {1, 1};\n\
    \        return ready;\n    }\n\n    static const vector<u32> &binary_pow_decimal(int\
    \ limbs) {\n        auto &cache = binary_pow_decimal_cache();\n        auto &ready\
    \ = binary_pow_decimal_ready();\n        ensure_pow_cache_size(cache, ready, limbs);\n\
    \        if (ready[limbs]) return cache[limbs];\n        int left = limbs >> 1;\n\
    \        int right = limbs - left;\n        cache[limbs] = mul_decimal_vectors(binary_pow_decimal(left),\
    \ binary_pow_decimal(right));\n        ready[limbs] = 1;\n        return cache[limbs];\n\
    \    }\n\n    static vector<u32> small_limbs_to_decimal(const vector<u32> &limbs,\
    \ int l, int r) {\n        BigInteger tmp;\n        tmp.sign = 1;\n        tmp.d.assign(limbs.begin()\
    \ + l, limbs.begin() + r);\n        tmp.trim();\n        vector<u32> res;\n  \
    \      while (!tmp.is_zero()) res.push_back(tmp.div_small_assign(DEC_CONV_BASE));\n\
    \        return res;\n    }\n\n    static vector<u32> limbs_to_decimal(const vector<u32>\
    \ &limbs, int l, int r) {\n        while (l < r && limbs[r - 1] == 0) --r;\n \
    \       if (l >= r) return {};\n        if (r - l <= 32) return small_limbs_to_decimal(limbs,\
    \ l, r);\n        int m = (l + r) >> 1;\n        vector<u32> low = limbs_to_decimal(limbs,\
    \ l, m);\n        vector<u32> high = limbs_to_decimal(limbs, m, r);\n        if\
    \ (high.empty()) return low;\n        vector<u32> shifted = mul_decimal_vectors(high,\
    \ binary_pow_decimal(m - l));\n        if (low.empty()) return shifted;\n    \
    \    return add_decimal_vectors(std::move(low), shifted);\n    }\n\n    static\
    \ int decimal_digits_u32(u32 x) {\n        if (x >= 1000000000u) return 10;\n\
    \        if (x >= 100000000u) return 9;\n        if (x >= 10000000u) return 8;\n\
    \        if (x >= 1000000u) return 7;\n        if (x >= 100000u) return 6;\n \
    \       if (x >= 10000u) return 5;\n        if (x >= 1000u) return 4;\n      \
    \  if (x >= 100u) return 3;\n        if (x >= 10u) return 2;\n        return 1;\n\
    \    }\n\n    static void append_u32_decimal(string &res, u32 x) {\n        char\
    \ buf[10];\n        int pos = 10;\n        do {\n            buf[--pos] = char('0'\
    \ + (x % 10));\n            x /= 10;\n        } while (x);\n        res.append(buf\
    \ + pos, buf + 10);\n    }\n\n    static void append_u32_decimal_padded(string\
    \ &res, u32 x, int width) {\n        char buf[10];\n        for (int i = width\
    \ - 1; i >= 0; --i) {\n            buf[i] = char('0' + (x % 10));\n          \
    \  x /= 10;\n        }\n        res.append(buf, buf + width);\n    }\n\n    static\
    \ int decimal_digits_u64(u64 x) {\n        int digits = 1;\n        while (x >=\
    \ 10) {\n            x /= 10;\n            ++digits;\n        }\n        return\
    \ digits;\n    }\n\n    static void append_u64_decimal(string &res, u64 x) {\n\
    \        char buf[20];\n        int pos = 20;\n        do {\n            buf[--pos]\
    \ = char('0' + (x % 10));\n            x /= 10;\n        } while (x);\n      \
    \  res.append(buf + pos, buf + 20);\n    }\n\n    static void append_u64_decimal_padded(string\
    \ &res, u64 x, int width) {\n        char buf[20];\n        for (int i = width\
    \ - 1; i >= 0; --i) {\n            buf[i] = char('0' + (x % 10));\n          \
    \  x /= 10;\n        }\n        res.append(buf, buf + width);\n    }\n\n    static\
    \ string build_decimal_string_u64(const vector<u64> &parts, int block_digits,\
    \ bool negative) {\n        string res;\n        res.reserve((negative ? 1 : 0)\
    \ + decimal_digits_u64(parts.back()) +\n                    max(0, (int)parts.size()\
    \ - 1) * block_digits);\n        if (negative) res.push_back('-');\n        append_u64_decimal(res,\
    \ parts.back());\n        for (int i = (int)parts.size() - 2; i >= 0; --i) {\n\
    \            append_u64_decimal_padded(res, parts[i], block_digits);\n       \
    \ }\n        return res;\n    }\n\n    static BigInteger from_decimal_blocks_abs_u64(vector<u64>\
    \ parts, int block_digits) {\n        trim_decimal_blocks_u64(parts);\n      \
    \  if (parts.empty()) return BigInteger();\n        BigInteger res;\n        res.sign\
    \ = 1;\n        res.dec = build_decimal_string_u64(parts, block_digits, false);\n\
    \        res.binary_ready = false;\n        res.decimal_ready = true;\n      \
    \  return res;\n    }\n\n    struct FastDecBigint {\n        vector<u64> digits;\n\
    \        bool negative;\n\n        FastDecBigint() : digits(), negative(false)\
    \ {}\n        FastDecBigint(long long x) : digits(), negative(false) {\n     \
    \       if (x < 0) {\n                negative = true;\n                x = -x;\n\
    \            }\n            if (x) digits.push_back(u64(x));\n        }\n    \
    \    FastDecBigint(vector<u64> d, bool neg = false) : digits(std::move(d)), negative(neg)\
    \ { normalize(); }\n\n        FastDecBigint &normalize() {\n            trim_decimal_blocks_u64(digits);\n\
    \            if (digits.empty()) negative = false;\n            return *this;\n\
    \        }\n\n        bool is_zero() const { return digits.empty(); }\n\n    \
    \    static int compare_abs_digits(const vector<u64> &a, const vector<u64> &b)\
    \ {\n            return compare_decimal_blocks_u64(a, b);\n        }\n\n     \
    \   int compare(const FastDecBigint &other) const {\n            if (is_zero()\
    \ && other.is_zero()) return 0;\n            if (negative != other.negative) return\
    \ negative ? -1 : 1;\n            int c = compare_abs_digits(digits, other.digits);\n\
    \            return negative ? -c : c;\n        }\n\n        bool operator<(const\
    \ FastDecBigint &other) const { return compare(other) < 0; }\n        bool operator>=(const\
    \ FastDecBigint &other) const { return compare(other) >= 0; }\n\n        FastDecBigint\
    \ &pad_inplace(size_t to_add) {\n            if (to_add) digits.insert(digits.begin(),\
    \ to_add, 0);\n            return *this;\n        }\n\n        FastDecBigint &drop_inplace(size_t\
    \ to_drop) {\n            if (to_drop >= digits.size()) {\n                digits.clear();\n\
    \                negative = false;\n                return *this;\n          \
    \  }\n            digits.erase(digits.begin(), digits.begin() + (int)to_drop);\n\
    \            return normalize();\n        }\n\n        FastDecBigint pad(size_t\
    \ to_add) const {\n            FastDecBigint res = *this;\n            return\
    \ res.pad_inplace(to_add);\n        }\n\n        FastDecBigint drop(size_t to_drop)\
    \ const {\n            FastDecBigint res = *this;\n            return res.drop_inplace(to_drop);\n\
    \        }\n\n        FastDecBigint top(size_t to_keep) const {\n            if\
    \ (to_keep >= digits.size()) return pad(to_keep - digits.size());\n          \
    \  return drop(digits.size() - to_keep);\n        }\n\n        FastDecBigint &negate()\
    \ {\n            if (!is_zero()) negative = !negative;\n            return *this;\n\
    \        }\n\n        FastDecBigint operator-() const {\n            FastDecBigint\
    \ res = *this;\n            res.negate();\n            return res;\n        }\n\
    \n        static vector<u64> add_abs_digits(const vector<u64> &a, const vector<u64>\
    \ &b) {\n            vector<u64> res(max(a.size(), b.size()), 0);\n          \
    \  u64 carry = 0;\n            size_t i = 0;\n            for (; i < res.size();\
    \ ++i) {\n                u128 cur = carry;\n                if (i < a.size())\
    \ cur += a[i];\n                if (i < b.size()) cur += b[i];\n             \
    \   if (cur >= FAST_DEC_BASE) {\n                    res[i] = u64(cur - FAST_DEC_BASE);\n\
    \                    carry = 1;\n                } else {\n                  \
    \  res[i] = u64(cur);\n                    carry = 0;\n                }\n   \
    \         }\n            if (carry) res.push_back(carry);\n            trim_decimal_blocks_u64(res);\n\
    \            return res;\n        }\n\n        static void sub_abs_assign(vector<u64>\
    \ &a, const vector<u64> &b) {\n            u64 borrow = 0;\n            for (size_t\
    \ i = 0; i < a.size(); ++i) {\n                u128 rhs = borrow;\n          \
    \      if (i < b.size()) rhs += b[i];\n                if (u128(a[i]) < rhs) {\n\
    \                    a[i] = u64(u128(a[i]) + FAST_DEC_BASE - rhs);\n         \
    \           borrow = 1;\n                } else {\n                    a[i] =\
    \ u64(u128(a[i]) - rhs);\n                    borrow = 0;\n                }\n\
    \            }\n            trim_decimal_blocks_u64(a);\n        }\n\n       \
    \ FastDecBigint &operator+=(const FastDecBigint &other) {\n            if (other.is_zero())\
    \ return *this;\n            if (is_zero()) {\n                *this = other;\n\
    \                return *this;\n            }\n            if (negative == other.negative)\
    \ {\n                digits = add_abs_digits(digits, other.digits);\n        \
    \        return *this;\n            }\n            int cmp = compare_abs_digits(digits,\
    \ other.digits);\n            if (cmp == 0) {\n                digits.clear();\n\
    \                negative = false;\n                return *this;\n          \
    \  }\n            if (cmp > 0) {\n                sub_abs_assign(digits, other.digits);\n\
    \            } else {\n                vector<u64> res = other.digits;\n     \
    \           sub_abs_assign(res, digits);\n                digits = std::move(res);\n\
    \                negative = other.negative;\n            }\n            return\
    \ normalize();\n        }\n\n        FastDecBigint &operator-=(const FastDecBigint\
    \ &other) {\n            return *this += (-other);\n        }\n\n        FastDecBigint\
    \ operator+(const FastDecBigint &other) const {\n            FastDecBigint res\
    \ = *this;\n            res += other;\n            return res;\n        }\n\n\
    \        FastDecBigint operator-(const FastDecBigint &other) const {\n       \
    \     FastDecBigint res = *this;\n            res -= other;\n            return\
    \ res;\n        }\n\n        FastDecBigint &operator+=(long long other) {\n  \
    \          return *this += FastDecBigint(other);\n        }\n\n        FastDecBigint\
    \ &operator-=(long long other) {\n            return *this -= FastDecBigint(other);\n\
    \        }\n\n        FastDecBigint &operator*=(long long other) {\n         \
    \   if (is_zero() || other == 1) return *this;\n            if (other == 0) {\n\
    \                digits.clear();\n                negative = false;\n        \
    \        return *this;\n            }\n            if (other < 0) {\n        \
    \        negative = !negative;\n                other = -other;\n            }\n\
    \            u64 mul = u64(other);\n            u64 carry = 0;\n            for\
    \ (u64 &d : digits) {\n                u128 cur = u128(d) * mul + carry;\n   \
    \             d = u64(cur % FAST_DEC_BASE);\n                carry = u64(cur /\
    \ FAST_DEC_BASE);\n            }\n            while (carry) {\n              \
    \  digits.push_back(carry % FAST_DEC_BASE);\n                carry /= FAST_DEC_BASE;\n\
    \            }\n            return normalize();\n        }\n\n        static vector<u64>\
    \ mul_schoolbook_digits(const vector<u64> &a, const vector<u64> &b) {\n      \
    \      if (a.empty() || b.empty()) return {};\n            vector<u64> res(a.size()\
    \ + b.size(), 0);\n            for (size_t i = 0; i < a.size(); ++i) {\n     \
    \           u64 carry = 0;\n                for (size_t j = 0; j < b.size(); ++j)\
    \ {\n                    u128 cur = u128(a[i]) * b[j] + res[i + j] + carry;\n\
    \                    res[i + j] = u64(cur % FAST_DEC_BASE);\n                \
    \    carry = u64(cur / FAST_DEC_BASE);\n                }\n                size_t\
    \ pos = i + b.size();\n                while (carry) {\n                    u128\
    \ cur = u128(res[pos]) + carry;\n                    res[pos] = u64(cur % FAST_DEC_BASE);\n\
    \                    carry = u64(cur / FAST_DEC_BASE);\n                    ++pos;\n\
    \                }\n            }\n            trim_decimal_blocks_u64(res);\n\
    \            return res;\n        }\n\n        static vector<u32> to_metabase_digits(const\
    \ vector<u64> &src) {\n            vector<u32> res(src.size() * FAST_DEC_META_DIGITS);\n\
    \            for (size_t i = 0; i < src.size(); ++i) {\n                u64 cur\
    \ = src[i];\n                for (int k = 0; k < FAST_DEC_META_DIGITS; ++k) {\n\
    \                    res[i * FAST_DEC_META_DIGITS + k] = u32(cur % FAST_DEC_META_BASE);\n\
    \                    cur /= FAST_DEC_META_BASE;\n                }\n         \
    \   }\n            while (!res.empty() && res.back() == 0) res.pop_back();\n \
    \           return res;\n        }\n\n        static vector<u64> from_metabase_digits(const\
    \ vector<u32> &src) {\n            vector<u64> res;\n            res.reserve(src.size()\
    \ / FAST_DEC_META_DIGITS + 2);\n            u64 carry = 0;\n            for (size_t\
    \ i = 0; i < src.size(); i += FAST_DEC_META_DIGITS) {\n                u128 val\
    \ = carry;\n                for (int k = FAST_DEC_META_DIGITS - 1; k >= 0; --k)\
    \ {\n                    val *= FAST_DEC_META_BASE;\n                    size_t\
    \ idx = i + (size_t)k;\n                    if (idx < src.size()) val += src[idx];\n\
    \                }\n                res.push_back(u64(val % FAST_DEC_BASE));\n\
    \                carry = u64(val / FAST_DEC_BASE);\n            }\n          \
    \  while (carry) {\n                res.push_back(carry % FAST_DEC_BASE);\n  \
    \              carry /= FAST_DEC_BASE;\n            }\n            trim_decimal_blocks_u64(res);\n\
    \            return res;\n        }\n\n        static vector<u64> mul_digits(const\
    \ vector<u64> &a, const vector<u64> &b) {\n            if (a.empty() || b.empty())\
    \ return {};\n            if (min(a.size(), b.size()) <= 32 || a.size() * b.size()\
    \ <= 4096) {\n                return mul_schoolbook_digits(a, b);\n          \
    \  }\n            vector<u32> x = to_metabase_digits(a);\n            vector<u32>\
    \ y = to_metabase_digits(b);\n            auto conv = BigIntegerExactConvolution::convolution_u64(x,\
    \ y);\n            vector<u32> meta;\n            meta.reserve(conv.size() + 4);\n\
    \            u64 carry = 0;\n            for (u64 v : conv) {\n              \
    \  u64 cur = v + carry;\n                meta.push_back(u32(cur % FAST_DEC_META_BASE));\n\
    \                carry = cur / FAST_DEC_META_BASE;\n            }\n          \
    \  while (carry) {\n                meta.push_back(u32(carry % FAST_DEC_META_BASE));\n\
    \                carry /= FAST_DEC_META_BASE;\n            }\n            while\
    \ (!meta.empty() && meta.back() == 0) meta.pop_back();\n            return from_metabase_digits(meta);\n\
    \        }\n\n        FastDecBigint &mul_inplace(FastDecBigint other) {\n    \
    \        negative = negative != other.negative;\n            digits = mul_digits(digits,\
    \ other.digits);\n            return normalize();\n        }\n\n        FastDecBigint\
    \ &operator*=(const FastDecBigint &other) {\n            return mul_inplace(FastDecBigint(other));\n\
    \        }\n\n        FastDecBigint operator*(const FastDecBigint &other) const\
    \ {\n            FastDecBigint res = *this;\n            res *= other;\n     \
    \       return res;\n        }\n    };\n\n    struct FastDecimal {\n        FastDecBigint\
    \ value;\n        long long scale;\n\n        FastDecimal(long long v = 0, long\
    \ long s = 0) : value(v), scale(s) {}\n        FastDecimal(FastDecBigint v, long\
    \ long s = 0) : value(std::move(v)), scale(s) {}\n\n        FastDecimal &operator*=(const\
    \ FastDecimal &other) {\n            value *= other.value;\n            scale\
    \ += other.scale;\n            return *this;\n        }\n\n        FastDecimal\
    \ &operator+=(const FastDecimal &other) {\n            if (scale < other.scale)\
    \ {\n                value += other.value.pad((size_t)(other.scale - scale));\n\
    \            } else {\n                value.pad_inplace((size_t)(scale - other.scale));\n\
    \                value += other.value;\n                scale = other.scale;\n\
    \            }\n            return *this;\n        }\n\n        FastDecimal &operator-=(const\
    \ FastDecimal &other) {\n            if (scale < other.scale) {\n            \
    \    value -= other.value.pad((size_t)(other.scale - scale));\n            } else\
    \ {\n                value.pad_inplace((size_t)(scale - other.scale));\n     \
    \           value -= other.value;\n                scale = other.scale;\n    \
    \        }\n            return *this;\n        }\n\n        FastDecimal operator*(const\
    \ FastDecimal &other) const {\n            FastDecimal res = *this;\n        \
    \    res *= other;\n            return res;\n        }\n\n        FastDecimal\
    \ operator+(const FastDecimal &other) const {\n            FastDecimal res = *this;\n\
    \            res += other;\n            return res;\n        }\n\n        FastDecimal\
    \ operator-(const FastDecimal &other) const {\n            FastDecimal res = *this;\n\
    \            res -= other;\n            return res;\n        }\n\n        FastDecBigint\
    \ trunc() const {\n            if (scale >= 0) return value.pad((size_t)scale);\n\
    \            if (-scale >= (long long)value.digits.size()) return FastDecBigint();\n\
    \            return value.top(value.digits.size() - (size_t)(-scale));\n     \
    \   }\n\n        FastDecBigint round() const {\n            if (scale >= 0) return\
    \ value.pad((size_t)scale);\n            if (-scale > (long long)value.digits.size())\
    \ return FastDecBigint();\n            FastDecBigint res = value.top(value.digits.size()\
    \ - (size_t)(-scale));\n            if (value.digits[(size_t)(-scale - 1)] * 2\
    \ >= FAST_DEC_BASE) res += 1;\n            return res;\n        }\n\n        FastDecimal\
    \ trunc(size_t digits_to_keep) const {\n            digits_to_keep = min(digits_to_keep,\
    \ value.digits.size());\n            return FastDecimal(value.top(digits_to_keep),\
    \ scale + (long long)value.digits.size() - (long long)digits_to_keep);\n     \
    \   }\n\n        long long magnitude() const {\n            static constexpr long\
    \ long NEG_INF = -(1LL << 60);\n            if (value.digits.empty()) return NEG_INF;\n\
    \            return (long long)value.digits.size() + scale;\n        }\n\n   \
    \     FastDecimal inv(long long precision) const {\n            assert(precision\
    \ >= 0);\n            long long lead = (long long)((long double)FAST_DEC_BASE\
    \ / (long double)value.digits.back() + 0.5L);\n            FastDecimal d(FastDecBigint(lead),\
    \ -(long long)value.digits.size());\n            size_t cur = 2;\n           \
    \ FastDecimal amend = FastDecimal(1) - trunc(cur) * d;\n            while (-amend.magnitude()\
    \ < precision) {\n                d += d * amend;\n                cur = 2 * (size_t)(1\
    \ - amend.magnitude());\n                d = d.trunc(cur);\n                amend\
    \ = FastDecimal(1) - trunc(cur) * d;\n            }\n            return d;\n \
    \       }\n    };\n\n    void trim() {\n        while (!d.empty() && d.back()\
    \ == 0) d.pop_back();\n        if (d.empty()) sign = 0;\n    }\n\n    int compare_abs(const\
    \ BigInteger &other) const {\n        if (decimal_ready && other.decimal_ready)\
    \ return compare_abs_decimal(dec, other.dec);\n        ensure_binary();\n    \
    \    other.ensure_binary();\n        if (d.size() != other.d.size()) return d.size()\
    \ < other.d.size() ? -1 : 1;\n        for (int i = (int)d.size() - 1; i >= 0;\
    \ --i) {\n            if (d[i] != other.d[i]) return d[i] < other.d[i] ? -1 :\
    \ 1;\n        }\n        return 0;\n    }\n\n    static int compare(const BigInteger\
    \ &a, const BigInteger &b) {\n        if (a.sign != b.sign) return a.sign < b.sign\
    \ ? -1 : 1;\n        if (a.sign == 0) return 0;\n        int c = a.compare_abs(b);\n\
    \        return a.sign > 0 ? c : -c;\n    }\n\n    void add_abs(const BigInteger\
    \ &other) {\n        ensure_binary();\n        other.ensure_binary();\n      \
    \  invalidate_decimal();\n        if (other.is_zero()) return;\n        if (d.size()\
    \ < other.d.size()) d.resize(other.d.size(), 0);\n        u64 carry = 0;\n   \
    \     for (size_t i = 0; i < other.d.size(); ++i) {\n            u64 cur = carry\
    \ + u64(d[i]) + other.d[i];\n            d[i] = u32(cur);\n            carry =\
    \ cur >> 32;\n        }\n        for (size_t i = other.d.size(); carry && i <\
    \ d.size(); ++i) {\n            u64 cur = carry + u64(d[i]);\n            d[i]\
    \ = u32(cur);\n            carry = cur >> 32;\n        }\n        if (carry) d.push_back(u32(carry));\n\
    \        if (!d.empty()) sign = 1;\n    }\n\n    void sub_abs(const BigInteger\
    \ &other) {\n        ensure_binary();\n        other.ensure_binary();\n      \
    \  invalidate_decimal();\n        // assume |*this| >= |other|\n        u64 borrow\
    \ = 0;\n        for (size_t i = 0; i < other.d.size(); ++i) {\n            u64\
    \ cur = u64(d[i]);\n            u64 rhs = u64(other.d[i]) + borrow;\n        \
    \    if (cur < rhs) {\n                d[i] = u32((cur + BASE) - rhs);\n     \
    \           borrow = 1;\n            } else {\n                d[i] = u32(cur\
    \ - rhs);\n                borrow = 0;\n            }\n        }\n        for\
    \ (size_t i = other.d.size(); borrow && i < d.size(); ++i) {\n            u64\
    \ cur = u64(d[i]);\n            if (cur == 0) {\n                d[i] = BASE_MASK;\n\
    \                borrow = 1;\n            } else {\n                d[i] = u32(cur\
    \ - 1);\n                borrow = 0;\n            }\n        }\n        trim();\n\
    \    }\n\n    void mul_small_assign(u32 m) {\n        ensure_binary();\n     \
    \   invalidate_decimal();\n        if (is_zero() || m == 1) return;\n        if\
    \ (m == 0) {\n            d.clear();\n            sign = 0;\n            return;\n\
    \        }\n        u64 carry = 0;\n        for (size_t i = 0; i < d.size(); ++i)\
    \ {\n            u64 cur = u64(d[i]) * m + carry;\n            d[i] = u32(cur);\n\
    \            carry = cur >> 32;\n        }\n        if (carry) d.push_back(u32(carry));\n\
    \    }\n\n    void add_small_assign(u32 a) {\n        ensure_binary();\n     \
    \   invalidate_decimal();\n        if (a == 0) return;\n        if (is_zero())\
    \ {\n            sign = 1;\n            d.push_back(a);\n            return;\n\
    \        }\n        u64 carry = a;\n        for (size_t i = 0; i < d.size() &&\
    \ carry; ++i) {\n            u64 cur = u64(d[i]) + carry;\n            d[i] =\
    \ u32(cur);\n            carry = cur >> 32;\n        }\n        if (carry) d.push_back(u32(carry));\n\
    \    }\n\n    u32 div_small_assign(u32 m) {\n        ensure_binary();\n      \
    \  invalidate_decimal();\n        u64 rem = 0;\n        for (int i = (int)d.size()\
    \ - 1; i >= 0; --i) {\n            u64 cur = (rem << 32) | d[i];\n           \
    \ d[i] = u32(cur / m);\n            rem = cur % m;\n        }\n        trim();\n\
    \        return u32(rem);\n    }\n\n    void shift_left_bits_assign(int bits)\
    \ {\n        ensure_binary();\n        invalidate_decimal();\n        if (bits\
    \ < 0) {\n            shift_right_bits_assign(-bits);\n            return;\n \
    \       }\n        if (is_zero() || bits == 0) return;\n        int word = bits\
    \ >> 5;\n        int rem = bits & 31;\n        if (word) d.insert(d.begin(), (size_t)word,\
    \ 0);\n        if (rem == 0) return;\n        u64 carry = 0;\n        for (size_t\
    \ i = word; i < d.size(); ++i) {\n            u64 cur = (u64(d[i]) << rem) | carry;\n\
    \            d[i] = u32(cur);\n            carry = cur >> 32;\n        }\n   \
    \     if (carry) d.push_back(u32(carry));\n    }\n\n    void shift_right_bits_assign(int\
    \ bits) {\n        ensure_binary();\n        invalidate_decimal();\n        if\
    \ (bits < 0) {\n            shift_left_bits_assign(-bits);\n            return;\n\
    \        }\n        if (is_zero() || bits == 0) return;\n        int word = bits\
    \ >> 5;\n        int rem = bits & 31;\n        if (word >= (int)d.size()) {\n\
    \            d.clear();\n            sign = 0;\n            return;\n        }\n\
    \        if (word) d.erase(d.begin(), d.begin() + word);\n        if (rem == 0)\
    \ {\n            trim();\n            return;\n        }\n        u64 carry =\
    \ 0;\n        for (int i = (int)d.size() - 1; i >= 0; --i) {\n            u64\
    \ cur = d[i];\n            d[i] = u32((cur >> rem) | (carry << (32 - rem)));\n\
    \            carry = cur & ((1ULL << rem) - 1);\n        }\n        trim();\n\
    \    }\n\n    static BigInteger mul_schoolbook(const BigInteger &a, const BigInteger\
    \ &b) {\n        a.ensure_binary();\n        b.ensure_binary();\n        BigInteger\
    \ res;\n        if (a.is_zero() || b.is_zero()) return res;\n        res.sign\
    \ = 1;\n        res.d.assign(a.d.size() + b.d.size(), 0);\n        for (size_t\
    \ i = 0; i < a.d.size(); ++i) {\n            u64 carry = 0;\n            for (size_t\
    \ j = 0; j < b.d.size(); ++j) {\n                u64 cur = u64(res.d[i + j]) +\
    \ u64(a.d[i]) * b.d[j] + carry;\n                res.d[i + j] = u32(cur);\n  \
    \              carry = cur >> 32;\n            }\n            size_t pos = i +\
    \ b.d.size();\n            while (carry) {\n                u64 cur = u64(res.d[pos])\
    \ + carry;\n                res.d[pos] = u32(cur);\n                carry = cur\
    \ >> 32;\n                ++pos;\n            }\n        }\n        res.trim();\n\
    \        return res;\n    }\n\n    static BigInteger mul_convolution(const BigInteger\
    \ &a, const BigInteger &b) {\n        a.ensure_binary();\n        b.ensure_binary();\n\
    \        BigInteger res;\n        if (a.is_zero() || b.is_zero()) return res;\n\
    \        vector<u32> x;\n        vector<u32> y;\n        x.reserve(a.d.size()\
    \ * 2);\n        y.reserve(b.d.size() * 2);\n        for (u32 v : a.d) {\n   \
    \         x.push_back(v & 0xffffu);\n            x.push_back(v >> 16);\n     \
    \   }\n        for (u32 v : b.d) {\n            y.push_back(v & 0xffffu);\n  \
    \          y.push_back(v >> 16);\n        }\n        while (!x.empty() && x.back()\
    \ == 0) x.pop_back();\n        while (!y.empty() && y.back() == 0) y.pop_back();\n\
    \        if (x.empty() || y.empty()) return res;\n        auto conv = BigIntegerExactConvolution::convolution_u64(x,\
    \ y);\n        vector<u32> digits;\n        digits.reserve(conv.size() + 2);\n\
    \        u64 carry = 0;\n        for (u64 v : conv) {\n            u64 cur = v\
    \ + carry;\n            digits.push_back(u32(cur & 0xffffu));\n            carry\
    \ = cur >> 16;\n        }\n        while (carry) {\n            digits.push_back(u32(carry\
    \ & 0xffffu));\n            carry >>= 16;\n        }\n        while (!digits.empty()\
    \ && digits.back() == 0) digits.pop_back();\n        if (digits.empty()) return\
    \ res;\n        res.sign = 1;\n        res.d.reserve((digits.size() + 1) / 2);\n\
    \        for (size_t i = 0; i < digits.size(); i += 2) {\n            u32 lo =\
    \ digits[i];\n            u32 hi = i + 1 < digits.size() ? digits[i + 1] : 0;\n\
    \            res.d.push_back(lo | (hi << 16));\n        }\n        res.trim();\n\
    \        return res;\n    }\n\n    static BigInteger multiply(const BigInteger\
    \ &a, const BigInteger &b) {\n        if (a.decimal_ready && b.decimal_ready)\
    \ {\n            if (a.is_zero() || b.is_zero()) return BigInteger();\n      \
    \      vector<u32> x = split_decimal_blocks_le(a.dec, DEC_CONV_DIGITS);\n    \
    \        vector<u32> y = split_decimal_blocks_le(b.dec, DEC_CONV_DIGITS);\n  \
    \          vector<u32> parts = mul_decimal_vectors(x, y);\n            BigInteger\
    \ res;\n            if (parts.empty()) return res;\n            res.sign = a.sign\
    \ * b.sign;\n            res.dec = build_decimal_string(parts, DEC_CONV_DIGITS,\
    \ false);\n            res.binary_ready = false;\n            res.decimal_ready\
    \ = true;\n            return res;\n        }\n        a.ensure_binary();\n  \
    \      b.ensure_binary();\n        if (a.is_zero() || b.is_zero()) return BigInteger();\n\
    \        BigInteger res;\n        size_t n = a.d.size(), m = b.d.size();\n   \
    \     if (min(n, m) <= MUL_SCHOOLBOOK_LIMB_THRESHOLD || n * m <= MUL_SCHOOLBOOK_AREA_THRESHOLD)\
    \ {\n            res = mul_schoolbook(a, b);\n        }\n        else res = mul_convolution(a,\
    \ b);\n        res.sign = a.sign * b.sign;\n        if (res.is_zero()) res.sign\
    \ = 0;\n        return res;\n    }\n\n    static vector<u32> shift_left_copy_limbs(const\
    \ vector<u32> &src, int bits) {\n        if (src.empty()) return {};\n       \
    \ if (bits == 0) return src;\n        vector<u32> res(src.size() + 1, 0);\n  \
    \      u32 carry = 0;\n        for (size_t i = 0; i < src.size(); ++i) {\n   \
    \         u64 cur = (u64(src[i]) << bits) | carry;\n            res[i] = u32(cur);\n\
    \            carry = u32(cur >> 32);\n        }\n        res[src.size()] = carry;\n\
    \        if (res.back() == 0) res.pop_back();\n        return res;\n    }\n\n\
    \    static void shift_right_limbs_assign(vector<u32> &src, int bits) {\n    \
    \    if (src.empty() || bits == 0) return;\n        u32 carry = 0;\n        for\
    \ (int i = (int)src.size() - 1; i >= 0; --i) {\n            u32 cur = src[i];\n\
    \            src[i] = (cur >> bits) | (carry << (32 - bits));\n            carry\
    \ = cur & ((u32(1) << bits) - 1);\n        }\n        while (!src.empty() && src.back()\
    \ == 0) src.pop_back();\n    }\n\n    static BigInteger from_limbs(vector<u32>\
    \ limbs) {\n        BigInteger res;\n        res.d = std::move(limbs);\n     \
    \   while (!res.d.empty() && res.d.back() == 0) res.d.pop_back();\n        res.sign\
    \ = res.d.empty() ? 0 : 1;\n        res.binary_ready = true;\n        res.decimal_ready\
    \ = false;\n        return res;\n    }\n\n    static BigInteger from_limbs_range(const\
    \ vector<u32> &src, int l, int r) {\n        if (l >= r) return BigInteger();\n\
    \        BigInteger res;\n        res.d.assign(src.begin() + l, src.begin() +\
    \ r);\n        while (!res.d.empty() && res.d.back() == 0) res.d.pop_back();\n\
    \        res.sign = res.d.empty() ? 0 : 1;\n        res.binary_ready = true;\n\
    \        res.decimal_ready = false;\n        return res;\n    }\n\n    static\
    \ BigInteger merge_disjoint_range_high(const BigInteger &x, int l, int r,\n  \
    \                                              const BigInteger &high, int high_shift)\
    \ {\n        x.ensure_binary();\n        high.ensure_binary();\n        int xl\
    \ = max(0, l);\n        int xr = min((int)x.d.size(), r);\n        int low_len\
    \ = max(0, xr - xl);\n        if (high.is_zero()) return low_len ? from_limbs_range(x.d,\
    \ xl, xr) : BigInteger();\n        if (low_len == 0) return shift_left_limbs(high,\
    \ high_shift);\n        BigInteger res;\n        size_t need = max((size_t)low_len,\
    \ high.d.size() + (size_t)high_shift);\n        res.d.assign(need, 0);\n     \
    \   for (int i = 0; i < low_len; ++i) res.d[i] = x.d[xl + i];\n        for (size_t\
    \ i = 0; i < high.d.size(); ++i) res.d[i + high_shift] = high.d[i];\n        res.sign\
    \ = 1;\n        res.binary_ready = true;\n        res.decimal_ready = false;\n\
    \        res.trim();\n        return res;\n    }\n\n    static BigInteger merge_disjoint_abs(const\
    \ BigInteger &low, const BigInteger &high, int high_shift) {\n        low.ensure_binary();\n\
    \        return merge_disjoint_range_high(low, 0, (int)low.d.size(), high, high_shift);\n\
    \    }\n\n    static BigInteger lower_with_high(const BigInteger &x, int low_limbs,\
    \ const BigInteger &high) {\n        x.ensure_binary();\n        if (low_limbs\
    \ <= 0 || x.d.empty()) return shift_left_limbs(high, low_limbs);\n        int\
    \ len = min((int)x.d.size(), low_limbs);\n        return merge_disjoint_range_high(x,\
    \ 0, len, high, low_limbs);\n    }\n\n    static BigInteger block_with_high(const\
    \ BigInteger &x, int index, int num_blocks,\n                                \
    \      int block_length, const BigInteger &high) {\n        x.ensure_binary();\n\
    \        int block_start = index * block_length;\n        if (block_start >= (int)x.d.size())\
    \ return shift_left_limbs(high, block_length);\n        int block_end = index\
    \ == num_blocks - 1 ? (int)x.d.size() : (index + 1) * block_length;\n        if\
    \ (block_end > (int)x.d.size()) return shift_left_limbs(high, block_length);\n\
    \        return merge_disjoint_range_high(x, block_start, block_end, high, block_length);\n\
    \    }\n\n    static BigInteger lower_limbs(const BigInteger &x, int limbs) {\n\
    \        x.ensure_binary();\n        if (limbs <= 0 || x.d.empty()) return BigInteger();\n\
    \        int len = min((int)x.d.size(), limbs);\n        return from_limbs_range(x.d,\
    \ 0, len);\n    }\n\n    static BigInteger upper_limbs(const BigInteger &x, int\
    \ limbs) {\n        x.ensure_binary();\n        if (limbs <= 0) return x;\n  \
    \      if (limbs >= (int)x.d.size()) return BigInteger();\n        return from_limbs_range(x.d,\
    \ limbs, (int)x.d.size());\n    }\n\n    static BigInteger shift_left_limbs(const\
    \ BigInteger &x, int limbs) {\n        x.ensure_binary();\n        if (x.is_zero()\
    \ || limbs <= 0) return x;\n        vector<u32> res;\n        res.reserve((size_t)limbs\
    \ + x.d.size());\n        res.insert(res.end(), (size_t)limbs, 0);\n        res.insert(res.end(),\
    \ x.d.begin(), x.d.end());\n        return from_limbs(std::move(res));\n    }\n\
    \n    static BigInteger ones_limbs(int limbs) {\n        if (limbs <= 0) return\
    \ BigInteger();\n        return from_limbs(vector<u32>((size_t)limbs, BASE_MASK));\n\
    \    }\n\n    static BigInteger get_block(const BigInteger &x, int index, int\
    \ num_blocks, int block_length) {\n        x.ensure_binary();\n        int block_start\
    \ = index * block_length;\n        if (block_start >= (int)x.d.size()) return\
    \ BigInteger();\n        int block_end = index == num_blocks - 1 ? (int)x.d.size()\
    \ : (index + 1) * block_length;\n        if (block_end > (int)x.d.size()) return\
    \ BigInteger();\n        return from_limbs_range(x.d, block_start, block_end);\n\
    \    }\n\n    static void add_shifted_abs(BigInteger &dst, const BigInteger &src,\
    \ int limb_shift) {\n        dst.ensure_binary();\n        src.ensure_binary();\n\
    \        dst.invalidate_decimal();\n        if (src.is_zero()) return;\n     \
    \   size_t need = src.d.size() + (size_t)limb_shift;\n        if (dst.d.size()\
    \ < need) dst.d.resize(need, 0);\n        u64 carry = 0;\n        size_t i = 0;\n\
    \        for (; i < src.d.size(); ++i) {\n            u64 cur = u64(dst.d[i +\
    \ limb_shift]) + src.d[i] + carry;\n            dst.d[i + limb_shift] = u32(cur);\n\
    \            carry = cur >> 32;\n        }\n        size_t pos = i + limb_shift;\n\
    \        while (carry) {\n            if (pos == dst.d.size()) dst.d.push_back(0);\n\
    \            u64 cur = u64(dst.d[pos]) + carry;\n            dst.d[pos] = u32(cur);\n\
    \            carry = cur >> 32;\n            ++pos;\n        }\n        dst.sign\
    \ = 1;\n    }\n\n    static void add_disjoint_abs(BigInteger &dst, const BigInteger\
    \ &src, int limb_shift) {\n        dst.ensure_binary();\n        src.ensure_binary();\n\
    \        dst.invalidate_decimal();\n        if (src.is_zero()) return;\n     \
    \   size_t need = max(dst.d.size(), src.d.size() + (size_t)limb_shift);\n    \
    \    if (dst.d.size() < need) dst.d.resize(need, 0);\n        for (size_t i =\
    \ 0; i < src.d.size(); ++i) dst.d[i + limb_shift] = src.d[i];\n        dst.trim();\n\
    \        if (!dst.is_zero()) dst.sign = 1;\n    }\n\n    static void sub_one_abs(BigInteger\
    \ &x) {\n        x.ensure_binary();\n        x.invalidate_decimal();\n       \
    \ for (size_t i = 0; i < x.d.size(); ++i) {\n            if (x.d[i] != 0) {\n\
    \                --x.d[i];\n                break;\n            }\n          \
    \  x.d[i] = BASE_MASK;\n        }\n        x.trim();\n    }\n\n    static int\
    \ compare_shifted_abs(const BigInteger &a, const BigInteger &b, int limb_shift)\
    \ {\n        a.ensure_binary();\n        b.ensure_binary();\n        int as =\
    \ (int)a.d.size() - limb_shift;\n        int bs = (int)b.d.size();\n        if\
    \ (as != bs) return as < bs ? -1 : 1;\n        for (int i = as - 1; i >= 0; --i)\
    \ {\n            if (a.d[i + limb_shift] != b.d[i]) return a.d[i + limb_shift]\
    \ < b.d[i] ? -1 : 1;\n        }\n        return 0;\n    }\n\n    static void bz_split_divisor(vector<BigInteger>\
    \ &values, vector<int> &high, vector<int> &low,\n                            \
    \     vector<int> &knuth_shift, vector<vector<u32>> &knuth_norm,\n           \
    \                      vector<char> &corr_ready, vector<BigInteger> &shifted_high,\n\
    \                                 vector<BigInteger> &low_gap, int idx) {\n  \
    \      if (high[idx] != -1) return;\n        int half = (int)values[idx].d.size()\
    \ / 2;\n        high[idx] = (int)values.size();\n        values.push_back(upper_limbs(values[idx],\
    \ half));\n        high.push_back(-1);\n        low.push_back(-1);\n        knuth_shift.push_back(-1);\n\
    \        knuth_norm.emplace_back();\n        corr_ready.push_back(0);\n      \
    \  shifted_high.emplace_back();\n        low_gap.emplace_back();\n        low[idx]\
    \ = (int)values.size();\n        values.push_back(lower_limbs(values[idx], half));\n\
    \        high.push_back(-1);\n        low.push_back(-1);\n        knuth_shift.push_back(-1);\n\
    \        knuth_norm.emplace_back();\n        corr_ready.push_back(0);\n      \
    \  shifted_high.emplace_back();\n        low_gap.emplace_back();\n    }\n\n  \
    \  static void bz_prepare_knuth_divisor(const vector<BigInteger> &values, vector<int>\
    \ &knuth_shift,\n                                         vector<vector<u32>>\
    \ &knuth_norm, int idx) {\n        if (knuth_shift[idx] != -1) return;\n     \
    \   const BigInteger &v = values[idx];\n        int shift = __builtin_clz(v.d.back());\n\
    \        knuth_shift[idx] = shift;\n        knuth_norm[idx] = shift ? shift_left_copy_limbs(v.d,\
    \ shift) : v.d;\n    }\n\n    static void bz_prepare_divisor_corrections(vector<BigInteger>\
    \ &div_values, vector<int> &div_high,\n                                      \
    \         vector<int> &div_low, vector<int> &knuth_shift,\n                  \
    \                             vector<vector<u32>> &knuth_norm,\n             \
    \                                  vector<char> &corr_ready,\n               \
    \                                vector<BigInteger> &shifted_high,\n         \
    \                                      vector<BigInteger> &low_gap, int idx) {\n\
    \        if (corr_ready[idx]) return;\n        bz_split_divisor(div_values, div_high,\
    \ div_low, knuth_shift, knuth_norm,\n                         corr_ready, shifted_high,\
    \ low_gap, idx);\n        int n = (int)div_values[idx].d.size() / 2;\n       \
    \ const BigInteger &b1 = div_values[div_high[idx]];\n        const BigInteger\
    \ &b2 = div_values[div_low[idx]];\n        shifted_high[idx] = shift_left_limbs(b1,\
    \ n);\n        low_gap[idx] = shift_left_limbs(b2, n);\n        if (!b2.is_zero())\
    \ low_gap[idx].sub_abs(b2);\n        corr_ready[idx] = 1;\n    }\n\n    static\
    \ BigInteger divmod_knuth_abs(const BigInteger &u0, const BigInteger &v0, BigInteger\
    \ &rem) {\n        u0.ensure_binary();\n        v0.ensure_binary();\n        if\
    \ (v0.is_zero()) {\n            rem = BigInteger();\n            return BigInteger();\n\
    \        }\n        if (u0.compare_abs(v0) < 0) {\n            rem = u0;\n   \
    \         BigInteger q;\n            return q;\n        }\n        if (v0.d.size()\
    \ == 1) {\n            BigInteger q = u0;\n            u32 r = q.div_small_assign(v0.d[0]);\n\
    \            rem = BigInteger(r);\n            if (r == 0) rem.sign = 0;\n   \
    \         else rem.sign = 1;\n            q.sign = q.is_zero() ? 0 : 1;\n    \
    \        return q;\n        }\n\n        int shift = __builtin_clz(v0.d.back());\n\
    \        vector<u32> vn = shift ? shift_left_copy_limbs(v0.d, shift) : v0.d;\n\
    \        return divmod_knuth_abs_prepared(u0, v0, shift, vn, rem);\n    }\n\n\
    \    static BigInteger divmod_knuth_abs_prepared(const BigInteger &u0, const BigInteger\
    \ &v0, int shift,\n                                                const vector<u32>\
    \ &vn, BigInteger &rem) {\n        u0.ensure_binary();\n        v0.ensure_binary();\n\
    \        if (u0.compare_abs(v0) < 0) {\n            rem = u0;\n            return\
    \ BigInteger();\n        }\n        vector<u32> un = shift ? shift_left_copy_limbs(u0.d,\
    \ shift) : u0.d;\n        size_t n = vn.size();\n        size_t m = un.size()\
    \ - n;\n        un.push_back(0);\n\n        BigInteger q;\n        q.sign = 1;\n\
    \        q.d.assign(m + 1, 0);\n\n        for (size_t jj = m + 1; jj-- > 0; )\
    \ {\n            size_t j = jj;\n            u64 numerator = (u64(un[j + n]) <<\
    \ 32) | un[j + n - 1];\n            u64 qhat = numerator / vn[n - 1];\n      \
    \      u64 rhat = numerator % vn[n - 1];\n            if (qhat == BASE) {\n  \
    \              --qhat;\n                rhat += vn[n - 1];\n            }\n  \
    \          if (n >= 2 && rhat < BASE &&\n                qhat * vn[n - 2] > (rhat\
    \ << 32) + un[j + n - 2]) {\n                --qhat;\n                rhat +=\
    \ vn[n - 1];\n                if (rhat < BASE && qhat * vn[n - 2] > (rhat << 32)\
    \ + un[j + n - 2]) {\n                    --qhat;\n                    rhat +=\
    \ vn[n - 1];\n                }\n            }\n\n            u64 carry = 0;\n\
    \            u64 borrow = 0;\n            for (size_t i = 0; i < n; ++i) {\n \
    \               u64 prod = qhat * vn[i] + carry;\n                carry = prod\
    \ >> 32;\n                u64 sub = u64(u32(prod)) + borrow;\n               \
    \ if (u64(un[j + i]) < sub) {\n                    un[j + i] = u32(u64(un[j +\
    \ i]) + BASE - sub);\n                    borrow = 1;\n                } else\
    \ {\n                    un[j + i] = u32(u64(un[j + i]) - sub);\n            \
    \        borrow = 0;\n                }\n            }\n\n            u64 sub\
    \ = carry + borrow;\n            bool negative = false;\n            if (u64(un[j\
    \ + n]) < sub) {\n                un[j + n] = u32(u64(un[j + n]) + BASE - sub);\n\
    \                negative = true;\n            } else {\n                un[j\
    \ + n] = u32(u64(un[j + n]) - sub);\n            }\n\n            if (negative)\
    \ {\n                --qhat;\n                u64 add_carry = 0;\n           \
    \     for (size_t i = 0; i < n; ++i) {\n                    u64 cur = u64(un[j\
    \ + i]) + vn[i] + add_carry;\n                    un[j + i] = u32(cur);\n    \
    \                add_carry = cur >> 32;\n                }\n                un[j\
    \ + n] = u32(u64(un[j + n]) + add_carry);\n            }\n            q.d[j] =\
    \ u32(qhat);\n        }\n\n        q.trim();\n        rem.d.assign(un.begin(),\
    \ un.begin() + n);\n        rem.sign = rem.d.empty() ? 0 : 1;\n        if (shift)\
    \ shift_right_limbs_assign(rem.d, shift);\n        rem.trim();\n        return\
    \ q;\n    }\n\n    static pair<vector<u32>, vector<u32>> divmod_knuth_decimal_blocks(vector<u32>\
    \ u, vector<u32> v) {\n        trim_decimal_blocks(u);\n        trim_decimal_blocks(v);\n\
    \        if (v.empty()) return {{}, {}};\n        if (compare_decimal_blocks(u,\
    \ v) < 0) return {{}, std::move(u)};\n        if (v.size() == 1) {\n         \
    \   vector<u32> q = u;\n            u32 rem = div_small_decimal_blocks_assign(q,\
    \ v[0], DEC_BLOCK);\n            vector<u32> r;\n            if (rem) r.push_back(rem);\n\
    \            return {std::move(q), std::move(r)};\n        }\n\n        u32 norm\
    \ = DEC_BLOCK / (v.back() + 1);\n        vector<u32> un = norm == 1 ? std::move(u)\
    \ : mul_small_decimal_blocks(u, norm, DEC_BLOCK);\n        vector<u32> vn = norm\
    \ == 1 ? std::move(v) : mul_small_decimal_blocks(v, norm, DEC_BLOCK);\n      \
    \  size_t n = vn.size();\n        size_t m = un.size() - n;\n        un.push_back(0);\n\
    \n        vector<u32> q(m + 1, 0);\n        for (size_t jj = m + 1; jj-- > 0;\
    \ ) {\n            size_t j = jj;\n            u64 numerator = u64(un[j + n])\
    \ * DEC_BLOCK + un[j + n - 1];\n            u64 qhat = numerator / vn[n - 1];\n\
    \            u64 rhat = numerator % vn[n - 1];\n            if (qhat == DEC_BLOCK)\
    \ {\n                --qhat;\n                rhat += vn[n - 1];\n           \
    \ }\n            if (n >= 2) {\n                while (rhat < DEC_BLOCK &&\n \
    \                      qhat * vn[n - 2] > rhat * DEC_BLOCK + un[j + n - 2]) {\n\
    \                    --qhat;\n                    rhat += vn[n - 1];\n       \
    \         }\n            }\n\n            u64 carry = 0;\n            u64 borrow\
    \ = 0;\n            for (size_t i = 0; i < n; ++i) {\n                u64 prod\
    \ = qhat * vn[i] + carry;\n                carry = prod / DEC_BLOCK;\n       \
    \         u64 sub = prod % DEC_BLOCK + borrow;\n                if (u64(un[j +\
    \ i]) < sub) {\n                    un[j + i] = u32(u64(un[j + i]) + DEC_BLOCK\
    \ - sub);\n                    borrow = 1;\n                } else {\n       \
    \             un[j + i] = u32(u64(un[j + i]) - sub);\n                    borrow\
    \ = 0;\n                }\n            }\n\n            u64 sub = carry + borrow;\n\
    \            bool negative = false;\n            if (u64(un[j + n]) < sub) {\n\
    \                un[j + n] = u32(u64(un[j + n]) + DEC_BLOCK - sub);\n        \
    \        negative = true;\n            } else {\n                un[j + n] = u32(u64(un[j\
    \ + n]) - sub);\n            }\n\n            if (negative) {\n              \
    \  --qhat;\n                u64 add_carry = 0;\n                for (size_t i\
    \ = 0; i < n; ++i) {\n                    u64 cur = u64(un[j + i]) + vn[i] + add_carry;\n\
    \                    if (cur >= DEC_BLOCK) {\n                        un[j + i]\
    \ = u32(cur - DEC_BLOCK);\n                        add_carry = 1;\n          \
    \          } else {\n                        un[j + i] = u32(cur);\n         \
    \               add_carry = 0;\n                    }\n                }\n   \
    \             un[j + n] = u32(u64(un[j + n]) + add_carry);\n            }\n  \
    \          q[j] = u32(qhat);\n        }\n\n        trim_decimal_blocks(q);\n \
    \       vector<u32> r(un.begin(), un.begin() + n);\n        if (norm != 1) div_small_decimal_blocks_assign(r,\
    \ norm, DEC_BLOCK);\n        trim_decimal_blocks(r);\n        return {std::move(q),\
    \ std::move(r)};\n    }\n\n    static pair<BigInteger, BigInteger> divmod_decimal_abs(const\
    \ BigInteger &u, const BigInteger &v) {\n        if (compare_abs_decimal(u.dec,\
    \ v.dec) < 0) return {BigInteger(), u};\n        vector<u32> un = split_decimal_blocks_le(u.dec,\
    \ DEC_BLOCK_DIGITS);\n        vector<u32> vn = split_decimal_blocks_le(v.dec,\
    \ DEC_BLOCK_DIGITS);\n        auto qr = divmod_knuth_decimal_blocks(std::move(un),\
    \ std::move(vn));\n        return {\n            from_decimal_blocks_abs(std::move(qr.first),\
    \ DEC_BLOCK_DIGITS),\n            from_decimal_blocks_abs(std::move(qr.second),\
    \ DEC_BLOCK_DIGITS)\n        };\n    }\n\n    static bool divmod_decimal_reciprocal_abs(const\
    \ BigInteger &u, const BigInteger &v,\n                                      \
    \        BigInteger &quotient, BigInteger &rem) {\n        if (compare_abs_decimal(u.dec,\
    \ v.dec) < 0) {\n            quotient = BigInteger();\n            rem = u;\n\
    \            return true;\n        }\n        vector<u64> un = split_decimal_blocks_le_u64(u.dec,\
    \ FAST_DEC_BLOCK_DIGITS);\n        vector<u64> vn = split_decimal_blocks_le_u64(v.dec,\
    \ FAST_DEC_BLOCK_DIGITS);\n        FastDecBigint a(std::move(un));\n        FastDecBigint\
    \ b(std::move(vn));\n        if (b.is_zero()) return false;\n        if (b.digits.size()\
    \ == 1) {\n            vector<u64> q = a.digits;\n            u64 divisor = b.digits[0];\n\
    \            u64 carry = 0;\n            for (int i = (int)q.size() - 1; i >=\
    \ 0; --i) {\n                u128 cur = u128(carry) * FAST_DEC_BASE + q[i];\n\
    \                q[i] = u64(cur / divisor);\n                carry = u64(cur %\
    \ divisor);\n            }\n            quotient = from_decimal_blocks_abs_u64(std::move(q),\
    \ FAST_DEC_BLOCK_DIGITS);\n            if (carry == 0) rem = BigInteger();\n \
    \           else rem = from_decimal_blocks_abs_u64(vector<u64>{carry}, FAST_DEC_BLOCK_DIGITS);\n\
    \            return true;\n        }\n\n        FastDecimal A(a);\n        FastDecimal\
    \ B(b);\n        long long precision = A.magnitude() - B.magnitude() + 1;\n  \
    \      if (precision < 0) precision = 0;\n        FastDecBigint q = (A * B.inv(precision)).round();\n\
    \        FastDecBigint r = a - q * b;\n        int correction_steps = 0;\n   \
    \     while (!r.is_zero() && r.negative) {\n            --correction_steps;\n\
    \            if (correction_steps < -8) return false;\n            q -= 1;\n \
    \           r += b;\n        }\n        while (r.compare(b) >= 0) {\n        \
    \    ++correction_steps;\n            if (correction_steps > 8) return false;\n\
    \            q += 1;\n            r -= b;\n        }\n        if (q.negative ||\
    \ r.negative || r.compare(b) >= 0) return false;\n\n        quotient = from_decimal_blocks_abs_u64(std::move(q.digits),\
    \ FAST_DEC_BLOCK_DIGITS);\n        rem = from_decimal_blocks_abs_u64(std::move(r.digits),\
    \ FAST_DEC_BLOCK_DIGITS);\n        return true;\n    }\n\n    static bool should_use_decimal_division(const\
    \ BigInteger &u, const BigInteger &v) {\n        int u_blocks = ((int)u.dec.size()\
    \ + DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;\n        int v_blocks = ((int)v.dec.size()\
    \ + DEC_BLOCK_DIGITS - 1) / DEC_BLOCK_DIGITS;\n        if (u_blocks < v_blocks)\
    \ return true;\n        if (u_blocks <= v_blocks + 2) return true;\n        if\
    \ (v_blocks <= 4) return true;\n        return false;\n    }\n\n    static bool\
    \ should_use_decimal_reciprocal_division(const BigInteger &u, const BigInteger\
    \ &v) {\n        int u_blocks = ((int)u.dec.size() + FAST_DEC_BLOCK_DIGITS - 1)\
    \ / FAST_DEC_BLOCK_DIGITS;\n        int v_blocks = ((int)v.dec.size() + FAST_DEC_BLOCK_DIGITS\
    \ - 1) / FAST_DEC_BLOCK_DIGITS;\n        if (u_blocks < v_blocks || v_blocks <=\
    \ 1) return false;\n        if (u_blocks <= v_blocks + 1) return false;\n    \
    \    return v_blocks >= 4;\n    }\n\n    static BigInteger divide3n2n_abs(const\
    \ BigInteger &a, vector<BigInteger> &div_values,\n                           \
    \          vector<int> &div_high, vector<int> &div_low,\n                    \
    \                 vector<int> &knuth_shift, vector<vector<u32>> &knuth_norm,\n\
    \                                     vector<char> &corr_ready,\n            \
    \                         vector<BigInteger> &shifted_high, vector<BigInteger>\
    \ &low_gap,\n                                     int b_idx, BigInteger &quotient)\
    \ {\n        const BigInteger &b = div_values[b_idx];\n        int n = (int)b.d.size()\
    \ / 2;\n        bz_split_divisor(div_values, div_high, div_low, knuth_shift, knuth_norm,\n\
    \                         corr_ready, shifted_high, low_gap, b_idx);\n       \
    \ const BigInteger &b1 = div_values[div_high[b_idx]];\n        const BigInteger\
    \ &b2 = div_values[div_low[b_idx]];\n        BigInteger a12 = upper_limbs(a, n);\n\
    \        BigInteger r, d;\n        if (compare_shifted_abs(a, b, n) < 0) {\n \
    \           r = divide2n1n_abs(a12, div_values, div_high, div_low,\n         \
    \                      knuth_shift, knuth_norm, corr_ready, shifted_high, low_gap,\n\
    \                               div_high[b_idx], quotient);\n            d = multiply(quotient,\
    \ b2);\n            d.sign = d.is_zero() ? 0 : 1;\n        } else {\n        \
    \    bz_prepare_divisor_corrections(div_values, div_high, div_low, knuth_shift,\
    \ knuth_norm,\n                                           corr_ready, shifted_high,\
    \ low_gap, b_idx);\n            quotient = ones_limbs(n);\n            a12.add_abs(b1);\n\
    \            a12.sub_abs(shifted_high[b_idx]);\n            r = a12;\n       \
    \     d = low_gap[b_idx];\n        }\n        r = lower_with_high(a, n, r);\n\
    \        while (r.compare_abs(d) < 0) {\n            r.add_abs(b);\n         \
    \   sub_one_abs(quotient);\n        }\n        r.sub_abs(d);\n        return r;\n\
    \    }\n\n    static BigInteger divide2n1n_abs(const BigInteger &a, vector<BigInteger>\
    \ &div_values,\n                                     vector<int> &div_high, vector<int>\
    \ &div_low,\n                                     vector<int> &knuth_shift, vector<vector<u32>>\
    \ &knuth_norm,\n                                     vector<char> &corr_ready,\n\
    \                                     vector<BigInteger> &shifted_high, vector<BigInteger>\
    \ &low_gap,\n                                     int b_idx, BigInteger &quotient)\
    \ {\n        const BigInteger &b = div_values[b_idx];\n        int n = (int)b.d.size();\n\
    \        if ((n & 1) || n < BURNIKEL_ZIEGLER_THRESHOLD) {\n            BigInteger\
    \ rem;\n            bz_prepare_knuth_divisor(div_values, knuth_shift, knuth_norm,\
    \ b_idx);\n            quotient = divmod_knuth_abs_prepared(a, b, knuth_shift[b_idx],\
    \ knuth_norm[b_idx], rem);\n            return rem;\n        }\n        int half\
    \ = n / 2;\n        bz_split_divisor(div_values, div_high, div_low, knuth_shift,\
    \ knuth_norm,\n                         corr_ready, shifted_high, low_gap, b_idx);\n\
    \        BigInteger a_upper = upper_limbs(a, half);\n        BigInteger q1;\n\
    \        BigInteger r1 = divide3n2n_abs(a_upper, div_values, div_high, div_low,\n\
    \                                       knuth_shift, knuth_norm, corr_ready, shifted_high,\
    \ low_gap,\n                                       b_idx, q1);\n        BigInteger\
    \ z = lower_with_high(a, half, r1);\n        BigInteger r2 = divide3n2n_abs(z,\
    \ div_values, div_high, div_low,\n                                       knuth_shift,\
    \ knuth_norm, corr_ready, shifted_high, low_gap,\n                           \
    \            b_idx, quotient);\n        quotient = merge_disjoint_abs(quotient,\
    \ q1, half);\n        return r2;\n    }\n\n    static BigInteger divmod_burnikel_ziegler_abs(const\
    \ BigInteger &u, const BigInteger &v, BigInteger &quotient) {\n        u.ensure_binary();\n\
    \        v.ensure_binary();\n        int r = (int)u.d.size();\n        int s =\
    \ (int)v.d.size();\n        quotient = BigInteger();\n        if (r < s) return\
    \ u;\n\n        int m = 1;\n        while ((long long)m * BURNIKEL_ZIEGLER_THRESHOLD\
    \ <= s) m <<= 1;\n        int j = (s + m - 1) / m;\n        int n = j * m;\n \
    \       long long n_bits = 32LL * n;\n        int sigma = max(0LL, n_bits - v.bit_length());\n\
    \        BigInteger b_shifted = v;\n        BigInteger a_shifted = u;\n      \
    \  if (sigma) {\n            b_shifted.shift_left_bits_assign(sigma);\n      \
    \      a_shifted.shift_left_bits_assign(sigma);\n        }\n        int t = (int)((a_shifted.bit_length()\
    \ + n_bits) / n_bits);\n        if (t < 2) t = 2;\n\n        vector<BigInteger>\
    \ div_values;\n        vector<int> div_high;\n        vector<int> div_low;\n \
    \       vector<int> knuth_shift;\n        vector<vector<u32>> knuth_norm;\n  \
    \      vector<char> corr_ready;\n        vector<BigInteger> shifted_high;\n  \
    \      vector<BigInteger> low_gap;\n        div_values.reserve(32);\n        div_high.reserve(32);\n\
    \        div_low.reserve(32);\n        knuth_shift.reserve(32);\n        knuth_norm.reserve(32);\n\
    \        corr_ready.reserve(32);\n        shifted_high.reserve(32);\n        low_gap.reserve(32);\n\
    \        div_values.push_back(b_shifted);\n        div_high.push_back(-1);\n \
    \       div_low.push_back(-1);\n        knuth_shift.push_back(-1);\n        knuth_norm.emplace_back();\n\
    \        corr_ready.push_back(0);\n        shifted_high.emplace_back();\n    \
    \    low_gap.emplace_back();\n        BigInteger a1 = get_block(a_shifted, t -\
    \ 1, t, n);\n        BigInteger z = block_with_high(a_shifted, t - 2, t, n, a1);\n\
    \        BigInteger qi, ri;\n        for (int i = t - 2; i > 0; --i) {\n     \
    \       ri = divide2n1n_abs(z, div_values, div_high, div_low, knuth_shift, knuth_norm,\n\
    \                                corr_ready, shifted_high, low_gap, 0, qi);\n\
    \            z = block_with_high(a_shifted, i - 1, t, n, ri);\n            add_shifted_abs(quotient,\
    \ qi, i * n);\n        }\n        ri = divide2n1n_abs(z, div_values, div_high,\
    \ div_low, knuth_shift, knuth_norm,\n                            corr_ready, shifted_high,\
    \ low_gap, 0, qi);\n        quotient.add_abs(qi);\n        quotient.sign = quotient.is_zero()\
    \ ? 0 : 1;\n        if (sigma) ri.shift_right_bits_assign(sigma);\n        ri.sign\
    \ = ri.is_zero() ? 0 : 1;\n        return ri;\n    }\n\n    static bool normalize_burnikel_ziegler_remainder(BigInteger\
    \ &quotient, BigInteger &rem,\n                                              \
    \       const BigInteger &divisor) {\n        for (int step = 0; step < 3 && rem.compare_abs(divisor)\
    \ >= 0; ++step) {\n            rem.sub_abs(divisor);\n            quotient.add_small_assign(1);\n\
    \        }\n        quotient.sign = quotient.is_zero() ? 0 : 1;\n        rem.sign\
    \ = rem.is_zero() ? 0 : 1;\n        return rem.compare_abs(divisor) < 0;\n   \
    \ }\n\n    static BigInteger divmod_abs(const BigInteger &u0, const BigInteger\
    \ &v0, BigInteger &rem) {\n        u0.ensure_binary();\n        v0.ensure_binary();\n\
    \        if (v0.is_zero()) {\n            rem = BigInteger();\n            return\
    \ BigInteger();\n        }\n        if (u0.compare_abs(v0) < 0) {\n          \
    \  rem = u0;\n            return BigInteger();\n        }\n        if (v0.d.size()\
    \ == 1) {\n            BigInteger q = u0;\n            u32 r = q.div_small_assign(v0.d[0]);\n\
    \            rem = BigInteger(r);\n            rem.sign = r == 0 ? 0 : 1;\n  \
    \          q.sign = q.is_zero() ? 0 : 1;\n            return q;\n        }\n \
    \       if ((int)v0.d.size() >= BURNIKEL_ZIEGLER_THRESHOLD &&\n            (int)u0.d.size()\
    \ - (int)v0.d.size() >= BURNIKEL_ZIEGLER_OFFSET) {\n            BigInteger q;\n\
    \            rem = divmod_burnikel_ziegler_abs(u0, v0, q);\n            if (normalize_burnikel_ziegler_remainder(q,\
    \ rem, v0)) {\n                return q;\n            }\n        }\n        return\
    \ divmod_knuth_abs(u0, v0, rem);\n    }\n\n    static pair<BigInteger, BigInteger>\
    \ divmod_abs(const BigInteger &u, const BigInteger &v) {\n        u.ensure_binary();\n\
    \        v.ensure_binary();\n        BigInteger r;\n        BigInteger q = divmod_abs(u,\
    \ v, r);\n        return {q, r};\n    }\n\n    static pair<BigInteger, BigInteger>\
    \ divmod(const BigInteger &a, const BigInteger &b) {\n        if (b.is_zero())\
    \ return {BigInteger(), BigInteger()};\n        if (a.is_zero()) return {BigInteger(),\
    \ BigInteger()};\n        if (a.decimal_ready && b.decimal_ready && should_use_decimal_division(a,\
    \ b)) {\n            BigInteger aa = a;\n            BigInteger bb = b;\n    \
    \        aa.sign = aa.is_zero() ? 0 : 1;\n            bb.sign = bb.is_zero() ?\
    \ 0 : 1;\n            auto qr = divmod_decimal_abs(aa, bb);\n            BigInteger\
    \ q = qr.first;\n            BigInteger r = qr.second;\n            if (a.sign\
    \ == b.sign) {\n                q.sign = q.is_zero() ? 0 : 1;\n              \
    \  if (!r.is_zero()) r.sign = b.sign;\n                return {q, r};\n      \
    \      }\n            if (r.is_zero()) {\n                q.sign = q.is_zero()\
    \ ? 0 : -1;\n                return {q, r};\n            }\n            BigInteger\
    \ one(\"1\");\n            q += one;\n            q.sign = -1;\n            r\
    \ = bb - r;\n            r.sign = b.sign;\n            if (q.is_zero()) q.sign\
    \ = 0;\n            return {q, r};\n        }\n        if (a.decimal_ready &&\
    \ b.decimal_ready && should_use_decimal_reciprocal_division(a, b)) {\n       \
    \     BigInteger aa = a;\n            BigInteger bb = b;\n            aa.sign\
    \ = aa.is_zero() ? 0 : 1;\n            bb.sign = bb.is_zero() ? 0 : 1;\n     \
    \       BigInteger q, r;\n            if (divmod_decimal_reciprocal_abs(aa, bb,\
    \ q, r)) {\n                if (a.sign == b.sign) {\n                    q.sign\
    \ = q.is_zero() ? 0 : 1;\n                    if (!r.is_zero()) r.sign = b.sign;\n\
    \                    return {q, r};\n                }\n                if (r.is_zero())\
    \ {\n                    q.sign = q.is_zero() ? 0 : -1;\n                    return\
    \ {q, r};\n                }\n                BigInteger one(\"1\");\n       \
    \         q += one;\n                q.sign = -1;\n                r = bb - r;\n\
    \                r.sign = b.sign;\n                if (q.is_zero()) q.sign = 0;\n\
    \                return {q, r};\n            }\n        }\n        a.ensure_binary();\n\
    \        b.ensure_binary();\n        BigInteger aa = a;\n        BigInteger bb\
    \ = b;\n        aa.sign = aa.is_zero() ? 0 : 1;\n        bb.sign = bb.is_zero()\
    \ ? 0 : 1;\n        auto qr = divmod_abs(aa, bb);\n        BigInteger q = qr.first;\n\
    \        BigInteger r = qr.second;\n        if (a.sign == b.sign) {\n        \
    \    q.sign = q.is_zero() ? 0 : 1;\n            if (!r.is_zero()) r.sign = b.sign;\n\
    \            return {q, r};\n        }\n        if (r.is_zero()) {\n         \
    \   q.sign = q.is_zero() ? 0 : -1;\n            return {q, r};\n        }\n  \
    \      BigInteger one = 1;\n        q += one;\n        q.sign = -1;\n        r\
    \ = bb - r;\n        r.sign = b.sign;\n        if (q.is_zero()) q.sign = 0;\n\
    \        return {q, r};\n    }\n\n    void assign(const string &s, int base =\
    \ 10) {\n        d.clear();\n        dec.clear();\n        binary_ready = true;\n\
    \        decimal_ready = false;\n        sign = 0;\n        int p = 0;\n     \
    \   bool neg = false;\n        if (p < (int)s.size() && (s[p] == '+' || s[p] ==\
    \ '-')) {\n            neg = s[p] == '-';\n            ++p;\n        }\n     \
    \   while (p < (int)s.size() && s[p] == '0') ++p;\n        if (p == (int)s.size())\
    \ return;\n        int q = p;\n        while (q < (int)s.size()) {\n         \
    \   int v = digit_value(s[q]);\n            if (v < 0 || v >= base) {\n      \
    \          d.clear();\n                sign = 0;\n                return;\n  \
    \          }\n            ++q;\n        }\n        if (base == 16) {\n       \
    \     for (int i = (int)s.size(); i > p; ) {\n                int l = max(p, i\
    \ - HEX_BLOCK_DIGITS);\n                u32 x = 0;\n                for (int j\
    \ = l; j < i; ++j) {\n                    int v = digit_value(s[j]);\n       \
    \             x = (x << 4) | u32(v);\n                }\n                d.push_back(x);\n\
    \                i = l;\n            }\n            sign = 1;\n            trim();\n\
    \            if (neg && !is_zero()) sign = -1;\n            return;\n        }\n\
    \        if (base == 10) {\n            dec.assign(s.begin() + p, s.end());\n\
    \            binary_ready = false;\n            decimal_ready = true;\n      \
    \      sign = 1;\n            if (neg && !is_zero()) sign = -1;\n            return;\n\
    \        }\n        for (; p < (int)s.size(); ++p) {\n            int v = digit_value(s[p]);\n\
    \            mul_small_assign((u32)base);\n            add_small_assign((u32)v);\n\
    \        }\n        sign = 1;\n        trim();\n        if (neg && !is_zero())\
    \ sign = -1;\n    }\n\n    string to_string(int base = 10) const {\n        if\
    \ (is_zero()) return \"0\";\n        if (base == 16) {\n            ensure_binary();\n\
    \            string res;\n            res.reserve((sign < 0 ? 1 : 0) + (int)d.size()\
    \ * HEX_BLOCK_DIGITS);\n            if (sign < 0) res.push_back('-');\n      \
    \      int i = (int)d.size() - 1;\n            auto append_hex32 = [&](u32 x,\
    \ bool leading) {\n                char buf[8];\n                for (int k =\
    \ 0; k < 8; ++k) {\n                    buf[7 - k] = digit_char((x >> (k * 4))\
    \ & 15);\n                }\n                int start = 0;\n                if\
    \ (leading) {\n                    while (start < 8 && buf[start] == '0') ++start;\n\
    \                }\n                res.append(buf + start, buf + 8);\n      \
    \      };\n            append_hex32(d[i], true);\n            for (--i; i >= 0;\
    \ --i) append_hex32(d[i], false);\n            return res;\n        }\n      \
    \  if (decimal_ready) {\n            string res;\n            res.reserve((sign\
    \ < 0 ? 1 : 0) + dec.size());\n            if (sign < 0) res.push_back('-');\n\
    \            res += dec;\n            return res;\n        }\n        if ((int)d.size()\
    \ <= DEC_TO_STRING_LINEAR_LIMB_THRESHOLD) {\n            BigInteger tmp;\n   \
    \         tmp.sign = 1;\n            tmp.d = d;\n            tmp.binary_ready\
    \ = true;\n            tmp.decimal_ready = false;\n            vector<u32> parts;\n\
    \            parts.reserve((bit_length() + 28) / 29);\n            while (!tmp.is_zero())\
    \ parts.push_back(tmp.div_small_assign(DEC_BLOCK));\n            return build_decimal_string(parts,\
    \ DEC_BLOCK_DIGITS, sign < 0);\n        }\n        vector<u32> parts = limbs_to_decimal(d,\
    \ 0, (int)d.size());\n        return build_decimal_string(parts, DEC_CONV_DIGITS,\
    \ sign < 0);\n    }\n\n    BigInteger operator+() const { return *this; }\n  \
    \  BigInteger operator-() const {\n        BigInteger res = *this;\n        if\
    \ (!res.is_zero()) res.sign = -res.sign;\n        return res;\n    }\n\n    BigInteger\
    \ &operator+=(const BigInteger &rhs) {\n        if (rhs.is_zero()) return *this;\n\
    \        if (this == &rhs) {\n            BigInteger tmp = rhs;\n            return\
    \ *this += tmp;\n        }\n        if (decimal_ready && rhs.decimal_ready) {\n\
    \            if (is_zero()) {\n                *this = rhs;\n                return\
    \ *this;\n            }\n            if (sign == rhs.sign) {\n               \
    \ dec = add_abs_decimal(dec, rhs.dec);\n            } else {\n               \
    \ int c = compare_abs_decimal(dec, rhs.dec);\n                if (c == 0) {\n\
    \                    dec.clear();\n                    decimal_ready = false;\n\
    \                    sign = 0;\n                    binary_ready = true;\n   \
    \                 d.clear();\n                    return *this;\n            \
    \    }\n                if (c > 0) {\n                    dec = sub_abs_decimal(dec,\
    \ rhs.dec);\n                } else {\n                    dec = sub_abs_decimal(rhs.dec,\
    \ dec);\n                    sign = rhs.sign;\n                }\n           \
    \ }\n            d.clear();\n            binary_ready = false;\n            decimal_ready\
    \ = true;\n            return *this;\n        }\n        ensure_binary();\n  \
    \      rhs.ensure_binary();\n        invalidate_decimal();\n        if (is_zero())\
    \ {\n            *this = rhs;\n            return *this;\n        }\n        if\
    \ (sign == rhs.sign) {\n            add_abs(rhs);\n            sign = rhs.sign;\n\
    \            return *this;\n        }\n        int c = compare_abs(rhs);\n   \
    \     if (c == 0) {\n            d.clear();\n            sign = 0;\n        }\
    \ else if (c > 0) {\n            sub_abs(rhs);\n        } else {\n           \
    \ BigInteger tmp = rhs;\n            tmp.sub_abs(*this);\n            *this =\
    \ tmp;\n        }\n        return *this;\n    }\n\n    BigInteger &operator-=(const\
    \ BigInteger &rhs) {\n        if (rhs.is_zero()) return *this;\n        BigInteger\
    \ tmp = rhs;\n        tmp.sign = -tmp.sign;\n        return *this += tmp;\n  \
    \  }\n\n    BigInteger &operator*=(const BigInteger &rhs) {\n        if (is_zero()\
    \ || rhs.is_zero()) {\n            d.clear();\n            dec.clear();\n    \
    \        binary_ready = true;\n            decimal_ready = false;\n          \
    \  sign = 0;\n            return *this;\n        }\n        BigInteger a = *this;\n\
    \        BigInteger b = rhs;\n        *this = multiply(a, b);\n        return\
    \ *this;\n    }\n\n    BigInteger &operator/=(const BigInteger &rhs) {\n     \
    \   ensure_binary();\n        rhs.ensure_binary();\n        invalidate_decimal();\n\
    \        *this = divmod(*this, rhs).first;\n        return *this;\n    }\n\n \
    \   BigInteger &operator%=(const BigInteger &rhs) {\n        ensure_binary();\n\
    \        rhs.ensure_binary();\n        invalidate_decimal();\n        *this =\
    \ divmod(*this, rhs).second;\n        return *this;\n    }\n\n    BigInteger &operator<<=(int\
    \ bits) {\n        ensure_binary();\n        invalidate_decimal();\n        if\
    \ (bits < 0) return *this >>= -bits;\n        if (is_zero()) return *this;\n \
    \       shift_left_bits_assign(bits);\n        return *this;\n    }\n\n    BigInteger\
    \ &operator>>=(int bits) {\n        ensure_binary();\n        invalidate_decimal();\n\
    \        if (bits < 0) return *this <<= -bits;\n        if (is_zero() || bits\
    \ == 0) return *this;\n        if (sign > 0) {\n            shift_right_bits_assign(bits);\n\
    \            return *this;\n        }\n        BigInteger p = 1;\n        p <<=\
    \ bits;\n        *this = divmod(*this, p).first;\n        return *this;\n    }\n\
    \n    friend BigInteger operator+(BigInteger lhs, const BigInteger &rhs) { return\
    \ lhs += rhs; }\n    friend BigInteger operator-(BigInteger lhs, const BigInteger\
    \ &rhs) { return lhs -= rhs; }\n    friend BigInteger operator*(BigInteger lhs,\
    \ const BigInteger &rhs) { return lhs *= rhs; }\n    friend BigInteger operator/(BigInteger\
    \ lhs, const BigInteger &rhs) { return lhs /= rhs; }\n    friend BigInteger operator%(BigInteger\
    \ lhs, const BigInteger &rhs) { return lhs %= rhs; }\n    friend BigInteger operator<<(BigInteger\
    \ lhs, int bits) { return lhs <<= bits; }\n    friend BigInteger operator>>(BigInteger\
    \ lhs, int bits) { return lhs >>= bits; }\n\n    friend bool operator==(const\
    \ BigInteger &a, const BigInteger &b) { return compare(a, b) == 0; }\n    friend\
    \ bool operator!=(const BigInteger &a, const BigInteger &b) { return compare(a,\
    \ b) != 0; }\n    friend bool operator<(const BigInteger &a, const BigInteger\
    \ &b) { return compare(a, b) < 0; }\n    friend bool operator<=(const BigInteger\
    \ &a, const BigInteger &b) { return compare(a, b) <= 0; }\n    friend bool operator>(const\
    \ BigInteger &a, const BigInteger &b) { return compare(a, b) > 0; }\n    friend\
    \ bool operator>=(const BigInteger &a, const BigInteger &b) { return compare(a,\
    \ b) >= 0; }\n};\n\n#endif\n\n/**\n * @brief \u591A\u500D\u9577\u6574\u6570(BigInteger)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/biginteger.cpp
  requiredBy: []
  timestamp: '2026-03-24 00:59:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_addition_of_big_integers.test.cpp
  - test/yosupo_division_of_big_integers.test.cpp
  - test/yosupo_addition_of_hex_big_integers.test.cpp
  - test/yosupo_multiplication_of_big_integers.test.cpp
  - test/yosupo_division_of_hex_big_integers.test.cpp
  - test/yosupo_multiplication_of_hex_big_integers.test.cpp
date: 2026-03-20
documentation_of: util/biginteger.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u591A\u500D\u9577\u6574\u6570(BigInteger)"
---

## 説明
符号付き多倍長整数を扱う。
内部表現は $2^{32}$ 基数の little endian limb 列で、加減算・比較・シフト・短整数演算・高速乗除算を持つ。
10 進入力同士では decimal cache を使い、近い長さの除算では基数変換を避ける

## できること
- `BigInteger()`
  `0` を作る
- `BigInteger(long long x)`
  `x` から作る
- `BigInteger(const string& s, int base = 10)`
  `s` から作る。`base` は `10` または `16` を想定する
- `x.is_zero()`
  `x == 0` なら `true`
- `x.to_string(int base = 10)`
  `base` 表記の文字列にする。`16` のときは小文字で返す
- `x += y`, `x -= y`, `x *= y`, `x /= y`, `x %= y`
  四則演算と余りを計算する。`/` は床除算、`%` は divisor と同符号の余りを返す
- `x << k`, `x >> k`
  2 の冪でのシフトを行う
- `x < y`, `x <= y`, `x > y`, `x >= y`, `x == y`, `x != y`
  比較する
- `divmod(x, y)`
  商と余りを同時に返す

## 使い方
`BigInteger a(s);` のように作って使う。
文字列入力が decimal ならそのまま、hex なら `BigInteger(s, 16)` と `to_string(16)` を使う。
