---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/berlekamp_massey.cpp
    title: Berlekamp-Massey
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
    PROBLEM: https://judge.yosupo.jp/problem/find_linear_recurrence
    links:
    - https://judge.yosupo.jp/problem/find_linear_recurrence
  bundledCode: "#line 1 \"test/yosupo_find_linear_recurrence.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\n\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr T\
    \ INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#line 1 \"util/modint.cpp\"\
    \n\n\n\ntemplate <uint M>\nstruct modint {\n    uint val;\npublic:\n    static\
    \ modint raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0)\
    \ {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x\
    \ < 0) x += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
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
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n */\n\n\n#line 1 \"math/berlekamp_massey.cpp\"\
    \ntemplate<class T>\nvector<T> berlekamp_massey(const vector<T> &s) {\n    vector<T>\
    \ c(1, T(1)), b(1, T(1));\n    int l = 0, m = 1;\n    T y = T(1);\n    for (int\
    \ n = 0; n < (int)s.size(); ++n) {\n        T d = T(0);\n        for (int i =\
    \ 0; i <= l; ++i) d += c[i] * s[n - i];\n        if (d == T(0)) {\n          \
    \  ++m;\n            continue;\n        }\n        auto t = c;\n        T coef\
    \ = d / y;\n        if ((int)c.size() < (int)b.size() + m) c.resize((int)b.size()\
    \ + m, T(0));\n        for (int i = 0; i < (int)b.size(); ++i) c[i + m] -= coef\
    \ * b[i];\n        if (2 * l <= n) {\n            l = n + 1 - l;\n           \
    \ b = t;\n            y = d;\n            m = 1;\n        } else {\n         \
    \   ++m;\n        }\n    }\n    c.erase(c.begin());\n    for (auto &x : c) x =\
    \ -x;\n    return c;\n}\n\n/**\n * @brief Berlekamp-Massey\u6CD5\n */\n#line 23\
    \ \"test/yosupo_find_linear_recurrence.test.cpp\"\n\nint main() {\n    int n;\n\
    \    cin >> n;\n    vector<mint> a(n);\n    for (int i = 0; i < n; ++i) {\n  \
    \      int x;\n        scanf(\"%d\", &x);\n        a[i] = x;\n    }\n    auto\
    \ c = berlekamp_massey(a);\n    printf(\"%d\\n\", (int)c.size());\n    for (int\
    \ i = 0; i < (int)c.size(); ++i) {\n        if (i) printf(\" \");\n        printf(\"\
    %u\", c[i].val);\n    }\n    puts(\"\");\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n\n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 998244353;\nusing ll = long long;\nusing uint\
    \ = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include\
    \ \"../util/modint.cpp\"\n#include \"../math/berlekamp_massey.cpp\"\n\nint main()\
    \ {\n    int n;\n    cin >> n;\n    vector<mint> a(n);\n    for (int i = 0; i\
    \ < n; ++i) {\n        int x;\n        scanf(\"%d\", &x);\n        a[i] = x;\n\
    \    }\n    auto c = berlekamp_massey(a);\n    printf(\"%d\\n\", (int)c.size());\n\
    \    for (int i = 0; i < (int)c.size(); ++i) {\n        if (i) printf(\" \");\n\
    \        printf(\"%u\", c[i].val);\n    }\n    puts(\"\");\n    return 0;\n}\n"
  dependsOn:
  - util/modint.cpp
  - math/berlekamp_massey.cpp
  isVerificationFile: true
  path: test/yosupo_find_linear_recurrence.test.cpp
  requiredBy: []
  timestamp: '2026-03-11 00:57:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_find_linear_recurrence.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_find_linear_recurrence.test.cpp
- /verify/test/yosupo_find_linear_recurrence.test.cpp.html
title: test/yosupo_find_linear_recurrence.test.cpp
---
