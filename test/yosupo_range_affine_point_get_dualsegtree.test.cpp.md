---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/dualsegtree.cpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Dual Segment Tree)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_point_get
    links:
    - https://judge.yosupo.jp/problem/range_affine_point_get
  bundledCode: "#line 1 \"test/yosupo_range_affine_point_get_dualsegtree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\n\
    \n#include <vector>\nusing namespace std;\n\nstatic const int MOD = 998244353;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr\
    \ FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000; ++i) {\n  \
    \          int x = i;\n            for (int j = 3; j >= 0; --j) {\n          \
    \      num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n      \
    \      }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE\
    \ = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n\
    \    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0),\
    \ interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n        int\
    \ len = size - idx;\n        memmove(buf, buf + idx, len);\n        if (interactive)\
    \ {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin)) size = len +\
    \ (int)strlen(buf + len);\n            else size = len;\n        } else {\n  \
    \          size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n    \
    \    }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure()\
    \ {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
    \ {\n        if (idx == size) load();\n    }\n\n    inline char skip() {\n   \
    \     if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            return buf[idx++];\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        if (interactive) {\n            char c = skip();\n          \
    \  bool neg = false;\n            if constexpr (is_signed<T>::value) {\n     \
    \           if (c == '-') {\n                    neg = true;\n               \
    \     ensure_interactive();\n                    c = buf[idx++];\n           \
    \     }\n            }\n            x = 0;\n            while (c >= '0') {\n \
    \               x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class Next, class... Tail>\n    void read(Head &head, Next &next, Tail &...tail)\
    \ {\n        read(head);\n        read(next, tail...);\n    }\n\n    template<class\
    \ T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void write_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n \
    \       write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
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
    \ T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type,\
    \ string>::value, int>::type = 0>\n    void write(const T &a) {\n        bool\
    \ first = true;\n        for (auto &&x : a) {\n            if (!first) pc(' ');\n\
    \            first = false;\n            write(x);\n        }\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner &in, T &x) {\n  \
    \  in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter &operator<<(Printer\
    \ &out, const T &x) {\n    out.write(x);\n    return out;\n}\n\n/**\n * @brief\
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"util/modint.cpp\"\n\n\
    \n\ntemplate <uint Mod>\nstruct modint {\n    uint val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    static constexpr uint get_mod()\
    \ { return Mod; }\n    static constexpr uint M() { return Mod; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod));\
    \ if (x < 0) x += Mod; val = uint(x); }\n    modint(bool v) { val = ((unsigned\
    \ int)(v) % Mod); }\n    uint &value() noexcept { return val; }\n    const uint\
    \ &value() const noexcept { return val; }\n    modint& operator++() { val++; if\
    \ (val == Mod) val = 0; return *this; }\n    modint& operator--() { if (val ==\
    \ 0) val = Mod; val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint& operator+=(const modint& b)\
    \ { val += b.val; if (val >= Mod) val -= Mod; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= Mod) val += Mod; return *this; }\n   \
    \ modint& operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z\
    \ % Mod); return *this; }\n    modint& operator/=(const modint& b) { return *this\
    \ = *this * b.inv(); }\n    modint operator+() const { return *this; }\n    modint\
    \ operator-() const { return modint() - *this; }\n    modint pow(long long n)\
    \ const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>=\
    \ 1; } return r; }\n    modint inv() const { return pow(Mod - 2); }\n    friend\
    \ modint operator+(const modint& a, const modint& b) { return modint(a) += b;\
    \ }\n    friend modint operator-(const modint& a, const modint& b) { return modint(a)\
    \ -= b; }\n    friend modint operator*(const modint& a, const modint& b) { return\
    \ modint(a) *= b; }\n    friend modint operator/(const modint& a, const modint&\
    \ b) { return modint(a) /= b; }\n    friend bool operator==(const modint& a, const\
    \ modint& b) { return a.val == b.val; }\n    friend bool operator!=(const modint&\
    \ a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 1 \"datastructure/dualsegtree.cpp\"\ntemplate <class M>\n\
    struct DualSegmentTree{\n    using T = typename M::T;\n    int sz, height{};\n\
    \    vector<T> lazy;\n    explicit DualSegmentTree(int n) {\n        sz = 1; while(sz\
    \ < n) sz <<= 1, height++;\n        lazy.assign(2*sz, M::e());\n    }\n\n    void\
    \ eval(int k){\n        if(lazy[k] == M::e()) return;\n        lazy[(k<<1)|0]\
    \ = M::f(lazy[(k<<1)|0], lazy[k]);\n        lazy[(k<<1)|1] = M::f(lazy[(k<<1)|1],\
    \ lazy[k]);\n        lazy[k] = M::e();\n    }\n    void thrust(int k){ for (int\
    \ i = height; i; --i) eval(k>>i); }\n    void update(int a, int b, const T &x){\n\
    \        thrust(a += sz); thrust(b += sz-1);\n        for (int l = a, r = b+1;l\
    \ < r; l >>=1, r >>= 1) {\n            if(l&1) lazy[l] = M::f(lazy[l], x), l++;\n\
    \            if(r&1) --r, lazy[r] = M::f(lazy[r], x);\n        }\n    }\n\n  \
    \  T operator[](int k){\n        thrust(k += sz);\n        return lazy[k];\n \
    \   }\n};\n/*\nstruct Monoid{\n    using T = ll;\n    static T f(T a, T b) { return\
    \ a+b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n * @brief \u53CC\u5BFE\
    \u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Dual Segment Tree)\n */\n#line 19 \"test/yosupo_range_affine_point_get_dualsegtree.test.cpp\"\
    \n\nstruct Monoid {\n    using T = pair<mint, mint>;\n    static T f(T a, T b)\
    \ {\n        return {b.first * a.first, b.first * a.second + b.second};\n    }\n\
    \    static T e() { return {1, 0}; }\n};\n\nint main() {\n    Scanner sc;\n  \
    \  Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<mint> a(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        int x;\n        sc.read(x);\n    \
    \    a[i] = x;\n    }\n\n    DualSegmentTree<Monoid> seg(n);\n    while (q--)\
    \ {\n        int t;\n        sc.read(t);\n        if (t == 0) {\n            int\
    \ l, r, b, c;\n            sc.read(l, r, b, c);\n            seg.update(l, r,\
    \ {b, c});\n        } else {\n            int i;\n            sc.read(i);\n  \
    \          auto [mul, add] = seg[i];\n            pr.writeln((mul * a[i] + add).val);\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\
    \n\n#include <vector>\nusing namespace std;\n\nstatic const int MOD = 998244353;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../util/modint.cpp\"\n#include \"\
    ../datastructure/dualsegtree.cpp\"\n\nstruct Monoid {\n    using T = pair<mint,\
    \ mint>;\n    static T f(T a, T b) {\n        return {b.first * a.first, b.first\
    \ * a.second + b.second};\n    }\n    static T e() { return {1, 0}; }\n};\n\n\
    int main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, q;\n    sc.read(n,\
    \ q);\n    vector<mint> a(n);\n    for (int i = 0; i < n; ++i) {\n        int\
    \ x;\n        sc.read(x);\n        a[i] = x;\n    }\n\n    DualSegmentTree<Monoid>\
    \ seg(n);\n    while (q--) {\n        int t;\n        sc.read(t);\n        if\
    \ (t == 0) {\n            int l, r, b, c;\n            sc.read(l, r, b, c);\n\
    \            seg.update(l, r, {b, c});\n        } else {\n            int i;\n\
    \            sc.read(i);\n            auto [mul, add] = seg[i];\n            pr.writeln((mul\
    \ * a[i] + add).val);\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - datastructure/dualsegtree.cpp
  isVerificationFile: true
  path: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 20:56:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_range_affine_point_get_dualsegtree.test.cpp
- /verify/test/yosupo_range_affine_point_get_dualsegtree.test.cpp.html
title: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
---
