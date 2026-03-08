---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/dynamic_bitset.cpp
    title: Dynamic Bitset
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_dynamic_bitset.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <algorithm>\n\
    #include <random>\n#include <vector>\nusing namespace std;\n\n#line 1 \"util/fastio.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    using namespace std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n  \
    \  constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline char skip() {\n\
    \        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n          \
    \  ++idx;\n            ensure();\n        }\n        return buf[idx++];\n    }\n\
    \n    template<class T, typename enable_if<is_integral<T>::value, int>::type =\
    \ 0>\n    void read(T &x) {\n        char c = skip();\n        bool neg = false;\n\
    \        if constexpr (is_signed<T>::value) {\n            if (c == '-') {\n \
    \               neg = true;\n                c = buf[idx++];\n            }\n\
    \        }\n        x = 0;\n        while (c >= '0') {\n            x = x * 10\
    \ + (c & 15);\n            c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
    \        write_range(s.data(), s.size());\n    }\n\n    void write(char c) {\n\
    \        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void write(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line\
    \ 1 \"datastructure/dynamic_bitset.cpp\"\nclass DynamicBitset {\n    using ull\
    \ = unsigned long long;\n    static constexpr int B = 64;\n\n    int n;\n    vector<ull>\
    \ a;\n\n    static int popcount(ull x) {\n        return __builtin_popcountll(x);\n\
    \    }\n    static int ctz(ull x) {\n        return __builtin_ctzll(x);\n    }\n\
    \n    ull tail_mask() const {\n        int rem = n & (B - 1);\n        return\
    \ rem ? ((1ULL << rem) - 1) : ~0ULL;\n    }\n\n    void normalize() {\n      \
    \  if (!a.empty()) a.back() &= tail_mask();\n    }\n\npublic:\n    DynamicBitset()\
    \ : n(0) {}\n    explicit DynamicBitset(int n, bool x = false) : n(n), a((n +\
    \ B - 1) >> 6, x ? ~0ULL : 0ULL) {\n        normalize();\n    }\n\n    int size()\
    \ const { return n; }\n    bool empty() const { return n == 0; }\n\n    void reset()\
    \ {\n        fill(a.begin(), a.end(), 0);\n    }\n    void set() {\n        fill(a.begin(),\
    \ a.end(), ~0ULL);\n        normalize();\n    }\n    void flip() {\n        for\
    \ (auto &x : a) x = ~x;\n        normalize();\n    }\n\n    bool test(int k) const\
    \ {\n        return (a[k >> 6] >> (k & 63)) & 1ULL;\n    }\n    void set(int k)\
    \ {\n        a[k >> 6] |= 1ULL << (k & 63);\n    }\n    void reset(int k) {\n\
    \        a[k >> 6] &= ~(1ULL << (k & 63));\n    }\n    void flip(int k) {\n  \
    \      a[k >> 6] ^= 1ULL << (k & 63);\n    }\n    void assign(int k, bool x) {\n\
    \        if (x) set(k);\n        else reset(k);\n    }\n\n    bool any() const\
    \ {\n        for (auto x : a) if (x) return true;\n        return false;\n   \
    \ }\n    bool none() const { return !any(); }\n    bool all() const {\n      \
    \  if (a.empty()) return true;\n        for (int i = 0; i + 1 < (int)a.size();\
    \ ++i) {\n            if (a[i] != ~0ULL) return false;\n        }\n        return\
    \ a.back() == tail_mask();\n    }\n    int count() const {\n        int res =\
    \ 0;\n        for (auto x : a) res += popcount(x);\n        return res;\n    }\n\
    \n    int find_first() const {\n        for (int i = 0; i < (int)a.size(); ++i)\
    \ {\n            if (a[i]) return (i << 6) + ctz(a[i]);\n        }\n        return\
    \ -1;\n    }\n    int find_next(int k) const {\n        ++k;\n        if (k >=\
    \ n) return -1;\n        int i = k >> 6;\n        ull x = a[i] & (~0ULL << (k\
    \ & 63));\n        if (x) return (i << 6) + ctz(x);\n        for (++i; i < (int)a.size();\
    \ ++i) {\n            if (a[i]) return (i << 6) + ctz(a[i]);\n        }\n    \
    \    return -1;\n    }\n\n    DynamicBitset& operator&=(const DynamicBitset &r)\
    \ {\n        for (int i = 0; i < (int)a.size(); ++i) a[i] &= r.a[i];\n       \
    \ return *this;\n    }\n    DynamicBitset& operator|=(const DynamicBitset &r)\
    \ {\n        for (int i = 0; i < (int)a.size(); ++i) a[i] |= r.a[i];\n       \
    \ return *this;\n    }\n    DynamicBitset& operator^=(const DynamicBitset &r)\
    \ {\n        for (int i = 0; i < (int)a.size(); ++i) a[i] ^= r.a[i];\n       \
    \ normalize();\n        return *this;\n    }\n\n    friend DynamicBitset operator&(DynamicBitset\
    \ l, const DynamicBitset &r) { return l &= r; }\n    friend DynamicBitset operator|(DynamicBitset\
    \ l, const DynamicBitset &r) { return l |= r; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { return l ^= r; }\n\n    DynamicBitset& operator<<=(int\
    \ s) {\n        if (s <= 0) return *this;\n        if (s >= n) {\n           \
    \ reset();\n            return *this;\n        }\n        int block = s >> 6,\
    \ rem = s & 63;\n        vector<ull> b(a.size(), 0);\n        for (int i = (int)a.size()\
    \ - 1; i >= block; --i) {\n            b[i] |= a[i - block] << rem;\n        \
    \    if (rem && i - block - 1 >= 0) b[i] |= a[i - block - 1] >> (B - rem);\n \
    \       }\n        a.swap(b);\n        normalize();\n        return *this;\n \
    \   }\n    DynamicBitset& operator>>=(int s) {\n        if (s <= 0) return *this;\n\
    \        if (s >= n) {\n            reset();\n            return *this;\n    \
    \    }\n        int block = s >> 6, rem = s & 63;\n        vector<ull> b(a.size(),\
    \ 0);\n        for (int i = 0; i + block < (int)a.size(); ++i) {\n           \
    \ b[i] |= a[i + block] >> rem;\n            if (rem && i + block + 1 < (int)a.size())\
    \ b[i] |= a[i + block + 1] << (B - rem);\n        }\n        a.swap(b);\n    \
    \    normalize();\n        return *this;\n    }\n\n    friend DynamicBitset operator<<(DynamicBitset\
    \ l, int s) { return l <<= s; }\n    friend DynamicBitset operator>>(DynamicBitset\
    \ l, int s) { return l >>= s; }\n};\n\n/**\n * @brief \u52D5\u7684bitset(Dynamic\
    \ Bitset)\n */\n#line 10 \"test/yosupo_many_aplusb_dynamic_bitset.test.cpp\"\n\
    \nint brute_find_first(const vector<int> &v) {\n    for (int i = 0; i < (int)v.size();\
    \ ++i) if (v[i]) return i;\n    return -1;\n}\n\nint brute_find_next(const vector<int>\
    \ &v, int k) {\n    for (int i = k + 1; i < (int)v.size(); ++i) if (v[i]) return\
    \ i;\n    return -1;\n}\n\nint brute_count(const vector<int> &v) {\n    int res\
    \ = 0;\n    for (int x : v) res += x;\n    return res;\n}\n\nvector<int> brute_shift_left(const\
    \ vector<int> &v, int s) {\n    vector<int> res(v.size());\n    for (int i = 0;\
    \ i < (int)v.size(); ++i) {\n        if (i - s >= 0) res[i] = v[i - s];\n    }\n\
    \    return res;\n}\n\nvector<int> brute_shift_right(const vector<int> &v, int\
    \ s) {\n    vector<int> res(v.size());\n    for (int i = 0; i < (int)v.size();\
    \ ++i) {\n        if (i + s < (int)v.size()) res[i] = v[i + s];\n    }\n    return\
    \ res;\n}\n\nbool same(const DynamicBitset &bs, const vector<int> &v) {\n    if\
    \ (bs.size() != (int)v.size()) return false;\n    for (int i = 0; i < (int)v.size();\
    \ ++i) {\n        if (bs.test(i) != (bool)v[i]) return false;\n    }\n    if (bs.count()\
    \ != brute_count(v)) return false;\n    if (bs.any() != (brute_count(v) > 0))\
    \ return false;\n    if (bs.none() != (brute_count(v) == 0)) return false;\n \
    \   if (bs.all() != (brute_count(v) == (int)v.size())) return false;\n    if (bs.find_first()\
    \ != brute_find_first(v)) return false;\n    int cur = bs.find_first();\n    int\
    \ want = brute_find_first(v);\n    if (cur != want) return false;\n    while (cur\
    \ != -1) {\n        cur = bs.find_next(cur);\n        want = brute_find_next(v,\
    \ want);\n        if (cur != want) return false;\n    }\n    return true;\n}\n\
    \nint main() {\n    {\n        mt19937 rng(123456789);\n        for (int n = 0;\
    \ n <= 130; ++n) {\n            for (int trial = 0; trial < 200; ++trial) {\n\
    \                DynamicBitset bs(n);\n                vector<int> v(n, 0);\n\
    \                for (int step = 0; step < 200; ++step) {\n                  \
    \  int op = uniform_int_distribution<int>(0, 12)(rng);\n                    int\
    \ k = n == 0 ? 0 : uniform_int_distribution<int>(0, n - 1)(rng);\n           \
    \         int s = n == 0 ? 0 : uniform_int_distribution<int>(0, n + 5)(rng);\n\
    \                    if (op == 0 && n) {\n                        bs.set(k);\n\
    \                        v[k] = 1;\n                    } else if (op == 1 &&\
    \ n) {\n                        bs.reset(k);\n                        v[k] = 0;\n\
    \                    } else if (op == 2 && n) {\n                        bs.flip(k);\n\
    \                        v[k] ^= 1;\n                    } else if (op == 3 &&\
    \ n) {\n                        int x = uniform_int_distribution<int>(0, 1)(rng);\n\
    \                        bs.assign(k, x);\n                        v[k] = x;\n\
    \                    } else if (op == 4) {\n                        bs.set();\n\
    \                        fill(v.begin(), v.end(), 1);\n                    } else\
    \ if (op == 5) {\n                        bs.reset();\n                      \
    \  fill(v.begin(), v.end(), 0);\n                    } else if (op == 6) {\n \
    \                       bs.flip();\n                        for (int &x : v) x\
    \ ^= 1;\n                    } else if (op == 7) {\n                        bs\
    \ <<= s;\n                        v = brute_shift_left(v, s);\n              \
    \      } else if (op == 8) {\n                        bs >>= s;\n            \
    \            v = brute_shift_right(v, s);\n                    } else {\n    \
    \                    DynamicBitset other(n);\n                        vector<int>\
    \ w(n);\n                        for (int i = 0; i < n; ++i) {\n             \
    \               w[i] = uniform_int_distribution<int>(0, 1)(rng);\n           \
    \                 if (w[i]) other.set(i);\n                        }\n       \
    \                 if (op == 9) {\n                            bs &= other;\n \
    \                           for (int i = 0; i < n; ++i) v[i] &= w[i];\n      \
    \                  } else if (op == 10) {\n                            bs |= other;\n\
    \                            for (int i = 0; i < n; ++i) v[i] |= w[i];\n     \
    \                   } else if (op == 11) {\n                            bs ^=\
    \ other;\n                            for (int i = 0; i < n; ++i) v[i] ^= w[i];\n\
    \                        } else {\n                            if ((bs << s).count()\
    \ != brute_count(brute_shift_left(v, s))) return 1;\n                        \
    \    if ((bs >> s).count() != brute_count(brute_shift_right(v, s))) return 1;\n\
    \                        }\n                    }\n                    if (!same(bs,\
    \ v)) return 1;\n                }\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <algorithm>\n#include <random>\n#include <vector>\nusing namespace std;\n\n\
    #include \"../util/fastio.cpp\"\n#include \"../datastructure/dynamic_bitset.cpp\"\
    \n\nint brute_find_first(const vector<int> &v) {\n    for (int i = 0; i < (int)v.size();\
    \ ++i) if (v[i]) return i;\n    return -1;\n}\n\nint brute_find_next(const vector<int>\
    \ &v, int k) {\n    for (int i = k + 1; i < (int)v.size(); ++i) if (v[i]) return\
    \ i;\n    return -1;\n}\n\nint brute_count(const vector<int> &v) {\n    int res\
    \ = 0;\n    for (int x : v) res += x;\n    return res;\n}\n\nvector<int> brute_shift_left(const\
    \ vector<int> &v, int s) {\n    vector<int> res(v.size());\n    for (int i = 0;\
    \ i < (int)v.size(); ++i) {\n        if (i - s >= 0) res[i] = v[i - s];\n    }\n\
    \    return res;\n}\n\nvector<int> brute_shift_right(const vector<int> &v, int\
    \ s) {\n    vector<int> res(v.size());\n    for (int i = 0; i < (int)v.size();\
    \ ++i) {\n        if (i + s < (int)v.size()) res[i] = v[i + s];\n    }\n    return\
    \ res;\n}\n\nbool same(const DynamicBitset &bs, const vector<int> &v) {\n    if\
    \ (bs.size() != (int)v.size()) return false;\n    for (int i = 0; i < (int)v.size();\
    \ ++i) {\n        if (bs.test(i) != (bool)v[i]) return false;\n    }\n    if (bs.count()\
    \ != brute_count(v)) return false;\n    if (bs.any() != (brute_count(v) > 0))\
    \ return false;\n    if (bs.none() != (brute_count(v) == 0)) return false;\n \
    \   if (bs.all() != (brute_count(v) == (int)v.size())) return false;\n    if (bs.find_first()\
    \ != brute_find_first(v)) return false;\n    int cur = bs.find_first();\n    int\
    \ want = brute_find_first(v);\n    if (cur != want) return false;\n    while (cur\
    \ != -1) {\n        cur = bs.find_next(cur);\n        want = brute_find_next(v,\
    \ want);\n        if (cur != want) return false;\n    }\n    return true;\n}\n\
    \nint main() {\n    {\n        mt19937 rng(123456789);\n        for (int n = 0;\
    \ n <= 130; ++n) {\n            for (int trial = 0; trial < 200; ++trial) {\n\
    \                DynamicBitset bs(n);\n                vector<int> v(n, 0);\n\
    \                for (int step = 0; step < 200; ++step) {\n                  \
    \  int op = uniform_int_distribution<int>(0, 12)(rng);\n                    int\
    \ k = n == 0 ? 0 : uniform_int_distribution<int>(0, n - 1)(rng);\n           \
    \         int s = n == 0 ? 0 : uniform_int_distribution<int>(0, n + 5)(rng);\n\
    \                    if (op == 0 && n) {\n                        bs.set(k);\n\
    \                        v[k] = 1;\n                    } else if (op == 1 &&\
    \ n) {\n                        bs.reset(k);\n                        v[k] = 0;\n\
    \                    } else if (op == 2 && n) {\n                        bs.flip(k);\n\
    \                        v[k] ^= 1;\n                    } else if (op == 3 &&\
    \ n) {\n                        int x = uniform_int_distribution<int>(0, 1)(rng);\n\
    \                        bs.assign(k, x);\n                        v[k] = x;\n\
    \                    } else if (op == 4) {\n                        bs.set();\n\
    \                        fill(v.begin(), v.end(), 1);\n                    } else\
    \ if (op == 5) {\n                        bs.reset();\n                      \
    \  fill(v.begin(), v.end(), 0);\n                    } else if (op == 6) {\n \
    \                       bs.flip();\n                        for (int &x : v) x\
    \ ^= 1;\n                    } else if (op == 7) {\n                        bs\
    \ <<= s;\n                        v = brute_shift_left(v, s);\n              \
    \      } else if (op == 8) {\n                        bs >>= s;\n            \
    \            v = brute_shift_right(v, s);\n                    } else {\n    \
    \                    DynamicBitset other(n);\n                        vector<int>\
    \ w(n);\n                        for (int i = 0; i < n; ++i) {\n             \
    \               w[i] = uniform_int_distribution<int>(0, 1)(rng);\n           \
    \                 if (w[i]) other.set(i);\n                        }\n       \
    \                 if (op == 9) {\n                            bs &= other;\n \
    \                           for (int i = 0; i < n; ++i) v[i] &= w[i];\n      \
    \                  } else if (op == 10) {\n                            bs |= other;\n\
    \                            for (int i = 0; i < n; ++i) v[i] |= w[i];\n     \
    \                   } else if (op == 11) {\n                            bs ^=\
    \ other;\n                            for (int i = 0; i < n; ++i) v[i] ^= w[i];\n\
    \                        } else {\n                            if ((bs << s).count()\
    \ != brute_count(brute_shift_left(v, s))) return 1;\n                        \
    \    if ((bs >> s).count() != brute_count(brute_shift_right(v, s))) return 1;\n\
    \                        }\n                    }\n                    if (!same(bs,\
    \ v)) return 1;\n                }\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   long long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n\
    \    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/dynamic_bitset.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_dynamic_bitset.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_dynamic_bitset.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_dynamic_bitset.test.cpp
- /verify/test/yosupo_many_aplusb_dynamic_bitset.test.cpp.html
title: test/yosupo_many_aplusb_dynamic_bitset.test.cpp
---
