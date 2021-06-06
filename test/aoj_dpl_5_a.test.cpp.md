---
data:
  _extendedDependsOn:
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A
  bundledCode: "#line 1 \"test/aoj_dpl_5_a.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ u32 = unsigned;\nusing u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"util/modint.cpp\"\
    \ntemplate <u32 M>\nstruct modint {\n    u32 val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = u32(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M); }\n\
    \    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n  \
    \  modint& operator--() { if (val == 0) val = M; val--; return *this; }\n    modint\
    \ operator++(int) { modint result = *this; ++*this; return result; }\n    modint\
    \ operator--(int) { modint result = *this; --*this; return result; }\n    modint&\
    \ operator+=(const modint& b) { val += b.val; if (val >= M) val -= M; return *this;\
    \ }\n    modint& operator-=(const modint& b) { val -= b.val; if (val >= M) val\
    \ += M; return *this; }\n    modint& operator*=(const modint& b) { u64 z = val;\
    \ z *= b.val; val = (u32)(z % M); return *this; }\n    modint& operator/=(const\
    \ modint& b) { return *this = *this * b.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(M-2); }\n    friend modint operator+(const modint& a, const modint& b) {\
    \ return modint(a) += b; }\n    friend modint operator-(const modint& a, const\
    \ modint& b) { return modint(a) -= b; }\n    friend modint operator*(const modint&\
    \ a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 21\
    \ \"test/aoj_dpl_5_a.test.cpp\"\nint main() {\n    int n, k;\n    cin >> n >>\
    \ k;\n    cout << mint(k).pow(n).val << \"\\n\";\n    return 0;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ u32 = unsigned;\nusing u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../util/modint.cpp\"\
    \nint main() {\n    int n, k;\n    cin >> n >> k;\n    cout << mint(k).pow(n).val\
    \ << \"\\n\";\n    return 0;\n}"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: true
  path: test/aoj_dpl_5_a.test.cpp
  requiredBy: []
  timestamp: '2020-09-10 16:12:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_dpl_5_a.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_dpl_5_a.test.cpp
- /verify/test/aoj_dpl_5_a.test.cpp.html
title: test/aoj_dpl_5_a.test.cpp
---
