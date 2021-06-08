---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: datastructure/swag.cpp
    title: datastructure/swag.cpp
  - icon: ':question:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"test/yosupo_queue_operate_all_composite.test.cpp\"\n#include\
    \ <iostream>\n#include <algorithm>\n#include <iomanip>\n#include <map>\n#include\
    \ <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n\
    #include <cmath>\n\nstatic const int MOD = 998244353;\nusing ll = long long;\n\
    using u32 = unsigned;\nusing u64 = unsigned long long;\nusing namespace std;\n\
    \ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #line 1 \"util/modint.cpp\"\ntemplate <u32 M>\nstruct modint {\n    u32 val;\n\
    public:\n    static modint raw(int v) { modint x; x.val = v; return x; }\n   \
    \ modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = u32(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -=\
    \ M; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ b) { u64 z = val; z *= b.val; val = (u32)(z % M); return *this; }\n    modint&\
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
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 21\
    \ \"test/yosupo_queue_operate_all_composite.test.cpp\"\n\n#line 1 \"datastructure/swag.cpp\"\
    \ntemplate<class G>\nclass SWAG {\n    using T = typename G::T;\n    vector<T>\
    \ in, out, insum, outsum;\npublic:\n    SWAG() : in(0), out(0), insum(1, G::e()),\
    \ outsum(1, G::e()) {}\n\n    void push(const T& v){\n        insum.push_back(G::f(insum.back(),\
    \ v));\n        in.push_back(v);\n    }\n\n    void pop(){\n        if(out.empty()){\n\
    \            do {\n                out.emplace_back(in.back());\n            \
    \    outsum.emplace_back(G::f(in.back(), outsum.back()));\n                in.pop_back();\
    \ insum.pop_back();\n            }while(!in.empty());\n        }\n        out.pop_back();\
    \ outsum.pop_back();\n    }\n\n    T fold(){\n        return G::f(outsum.back(),\
    \ insum.back());\n    }\n};\n/*\nstruct Monoid {\n    using T = int;\n    static\
    \ T f(T a, T b) { return a+b; }\n    static T e() { return 0; }\n};\n*/\n#line\
    \ 23 \"test/yosupo_queue_operate_all_composite.test.cpp\"\n\nstruct SemiGroup\
    \ {\n    using T = pair<mint, mint>;\n    static T f(T a, T b) { return {a.first*b.first,\
    \ a.second*b.first + b.second}; }\n    static T e() { return {1, 0}; }\n};\n\n\
    int main() {\n    int q;\n    cin >> q;\n    SWAG<SemiGroup> Q;\n    while(q--){\n\
    \        int no; scanf(\"%d\", &no);\n        if(no == 0){\n            int a,\
    \ b; scanf(\"%d %d\", &a, &b);\n            Q.push(make_pair(mint(a), mint(b)));\n\
    \        }else if(no == 1){\n            Q.pop();\n        }else {\n         \
    \   int x; scanf(\"%d\", &x);\n            auto ret = Q.fold();\n            printf(\"\
    %d\\n\", (ret.first*mint(x) + ret.second).val);\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#include <iostream>\n#include <algorithm>\n#include <iomanip>\n#include <map>\n\
    #include <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n#include\
    \ <bitset>\n#include <cmath>\n\nstatic const int MOD = 998244353;\nusing ll =\
    \ long long;\nusing u32 = unsigned;\nusing u64 = unsigned long long;\nusing namespace\
    \ std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\
    \n#include \"../util/modint.cpp\"\n\n#include \"../datastructure/swag.cpp\"\n\n\
    struct SemiGroup {\n    using T = pair<mint, mint>;\n    static T f(T a, T b)\
    \ { return {a.first*b.first, a.second*b.first + b.second}; }\n    static T e()\
    \ { return {1, 0}; }\n};\n\nint main() {\n    int q;\n    cin >> q;\n    SWAG<SemiGroup>\
    \ Q;\n    while(q--){\n        int no; scanf(\"%d\", &no);\n        if(no == 0){\n\
    \            int a, b; scanf(\"%d %d\", &a, &b);\n            Q.push(make_pair(mint(a),\
    \ mint(b)));\n        }else if(no == 1){\n            Q.pop();\n        }else\
    \ {\n            int x; scanf(\"%d\", &x);\n            auto ret = Q.fold();\n\
    \            printf(\"%d\\n\", (ret.first*mint(x) + ret.second).val);\n      \
    \  }\n    }\n    return 0;\n}"
  dependsOn:
  - util/modint.cpp
  - datastructure/swag.cpp
  isVerificationFile: true
  path: test/yosupo_queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2021-06-09 00:15:20+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_queue_operate_all_composite.test.cpp
- /verify/test/yosupo_queue_operate_all_composite.test.cpp.html
title: test/yosupo_queue_operate_all_composite.test.cpp
---
