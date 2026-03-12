---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/swag_deque.cpp
    title: SWAG Deque
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
    PROBLEM: https://judge.yosupo.jp/problem/deque_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/deque_operate_all_composite
  bundledCode: "#line 1 \"test/yosupo_deque_operate_all_composite.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\n\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\nstatic const int\
    \ MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\nusing ull =\
    \ unsigned long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    struct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load() {\n  \
    \      int len = size - idx;\n        memmove(buf, buf + idx, len);\n        size\
    \ = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n\
    \        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if (idx\
    \ + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
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
    \ 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint M>\nstruct modint {\n    uint val;\n\
    public:\n    static modint raw(int v) { modint x; x.val = v; return x; }\n   \
    \ static constexpr uint get_mod() { return M; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M);\
    \ }\n    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n\
    \    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n  \
    \  modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -=\
    \ M; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % M); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(M-2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 1 \"datastructure/swag_deque.cpp\"\ntemplate<class G>\nclass\
    \ TwoStackDeque {\n    using T = typename G::T;\n    vector<T> l, r, lsum, rsum;\n\
    \    void rebuild_left_sum() {\n        lsum.assign(1, G::e());\n        for (int\
    \ i = 0; i < (int)l.size(); ++i) {\n            lsum.push_back(G::f(l[i], lsum.back()));\n\
    \        }\n    }\n\n    void rebuild_right_sum() {\n        rsum.assign(1, G::e());\n\
    \        for (int i = 0; i < (int)r.size(); ++i) {\n            rsum.push_back(G::f(rsum.back(),\
    \ r[i]));\n        }\n    }\n\n    void rebalance_from_right() {\n        int\
    \ lsize = ((int)r.size() + 1) / 2;\n        int rsize = (int)r.size() - lsize;\n\
    \        l.resize(lsize);\n        for (int i = 0; i < lsize; ++i) l[i] = r[lsize\
    \ - i - 1];\n        for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize];\n  \
    \      r.resize(rsize);\n        rebuild_left_sum();\n        rebuild_right_sum();\n\
    \    }\n\n    void rebalance_from_left() {\n        int rsize = ((int)l.size()\
    \ + 1) / 2;\n        int lsize = (int)l.size() - rsize;\n        r.resize(rsize);\n\
    \        for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1];\n        for\
    \ (int i = 0; i < lsize; ++i) l[i] = l[i + rsize];\n        l.resize(lsize);\n\
    \        rebuild_left_sum();\n        rebuild_right_sum();\n    }\npublic:\n \
    \   TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}\n\n    void\
    \ push_front(const T& v){\n        lsum.push_back(G::f(v, lsum.back()));\n   \
    \     l.push_back(v);\n    }\n\n    void push_back(const T& v){\n        rsum.push_back(G::f(rsum.back(),\
    \ v));\n        r.push_back(v);\n    }\n\n    void pop_front(){\n        if(l.empty()){\n\
    \            if(r.empty()) return;\n            rebalance_from_right();\n    \
    \    }\n        l.pop_back(); lsum.pop_back();\n    }\n\n    void pop_back(){\n\
    \        if(r.empty()){\n            if(l.empty()) return;\n            rebalance_from_left();\n\
    \        }\n        r.pop_back(); rsum.pop_back();\n    }\n\n    T fold(){\n \
    \       return G::f(lsum.back(), rsum.back());\n    }\n};\n/*\nstruct Monoid {\n\
    \    using T = int;\n    static T f(T a, T b) { return a+b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief SWAG Deque\n */\n#line 20 \"test/yosupo_deque_operate_all_composite.test.cpp\"\
    \n\nstruct Monoid {\n    using T = pair<mint, mint>;\n    static T f(T a, T b)\
    \ {\n        return {a.first * b.first, a.second * b.first + b.second};\n    }\n\
    \    static T e() { return {1, 0}; }\n};\n\nint main() {\n    Scanner sc;\n  \
    \  Printer pr;\n\n    int q;\n    sc.read(q);\n    TwoStackDeque<Monoid> deq;\n\
    \    while (q--) {\n        int t;\n        sc.read(t);\n        if (t == 0) {\n\
    \            int a, b;\n            sc.read(a, b);\n            deq.push_front({a,\
    \ b});\n        } else if (t == 1) {\n            int a, b;\n            sc.read(a,\
    \ b);\n            deq.push_back({a, b});\n        } else if (t == 2) {\n    \
    \        deq.pop_front();\n        } else if (t == 3) {\n            deq.pop_back();\n\
    \        } else {\n            int x;\n            sc.read(x);\n            auto\
    \ [a, b] = deq.fold();\n            pr.writeln((a * x + b).val);\n        }\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/deque_operate_all_composite\"\
    \n\n#include <utility>\n#include <vector>\nusing namespace std;\n\nstatic const\
    \ int MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#include \"../util/fastio.cpp\"\n#include \"../util/modint.cpp\"\
    \n#include \"../datastructure/swag_deque.cpp\"\n\nstruct Monoid {\n    using T\
    \ = pair<mint, mint>;\n    static T f(T a, T b) {\n        return {a.first * b.first,\
    \ a.second * b.first + b.second};\n    }\n    static T e() { return {1, 0}; }\n\
    };\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int q;\n    sc.read(q);\n\
    \    TwoStackDeque<Monoid> deq;\n    while (q--) {\n        int t;\n        sc.read(t);\n\
    \        if (t == 0) {\n            int a, b;\n            sc.read(a, b);\n  \
    \          deq.push_front({a, b});\n        } else if (t == 1) {\n           \
    \ int a, b;\n            sc.read(a, b);\n            deq.push_back({a, b});\n\
    \        } else if (t == 2) {\n            deq.pop_front();\n        } else if\
    \ (t == 3) {\n            deq.pop_back();\n        } else {\n            int x;\n\
    \            sc.read(x);\n            auto [a, b] = deq.fold();\n            pr.writeln((a\
    \ * x + b).val);\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - datastructure/swag_deque.cpp
  isVerificationFile: true
  path: test/yosupo_deque_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_deque_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_deque_operate_all_composite.test.cpp
- /verify/test/yosupo_deque_operate_all_composite.test.cpp.html
title: test/yosupo_deque_operate_all_composite.test.cpp
---
