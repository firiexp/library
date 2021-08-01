---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\ntemplate <uint M>\nstruct modint {\n\
    \    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll\
    \ x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }\n    modint(bool v)\
    \ { val = ((unsigned int)(v) % M); }\n    modint& operator++() { val++; if (val\
    \ == M) val = 0; return *this; }\n    modint& operator--() { if (val == 0) val\
    \ = M; val--; return *this; }\n    modint operator++(int) { modint result = *this;\
    \ ++*this; return result; }\n    modint operator--(int) { modint result = *this;\
    \ --*this; return result; }\n    modint& operator+=(const modint& b) { val +=\
    \ b.val; if (val >= M) val -= M; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= M) val += M; return *this; }\n    modint&\
    \ operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z % M);\
    \ return *this; }\n    modint& operator/=(const modint& b) { return *this = *this\
    \ * b.inv(); }\n    modint operator+() const { return *this; }\n    modint operator-()\
    \ const { return modint() - *this; }\n    modint pow(long long n) const { modint\
    \ x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r;\
    \ }\n    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 2\
    \ \"math/factorial.cpp\"\n\nclass Factorial {\n    vector<mint> facts, factinv;\n\
    public:\n    explicit Factorial(int n) : facts(n+1), factinv(n+1) {\n        facts[0]\
    \ = 1;\n        for (int i = 1; i < n+1; ++i) facts[i] = facts[i-1] * mint(i);\n\
    \        factinv[n] = facts[n].inv();\n        for (int i = n-1; i >= 0; --i)\
    \ factinv[i] = factinv[i+1] * mint(i+1);\n    }\n    mint fact(int k) const {\n\
    \        if(k >= 0) return facts[k]; else return factinv[-k];\n    }\n    mint\
    \ operator[](const int &k) const {\n        if(k >= 0) return facts[k]; else return\
    \ factinv[-k];\n    }\n    mint C(int p, int q) const {\n        if(q < 0 || p\
    \ < q) return 0;\n        return facts[p] * factinv[q] * factinv[p-q];\n    }\n\
    \    mint P(int p, int q) const {\n        if(q < 0 || p < q) return 0;\n    \
    \    return facts[p] * factinv[p-q];\n    }\n    mint H(int p, int q) const {\n\
    \        if(p < 0 || q < 0) return 0;\n        return q == 0 ? 1 : C(p+q-1, q);\n\
    \    }\n};\n"
  code: "#include \"../util/modint.cpp\"\n\nclass Factorial {\n    vector<mint> facts,\
    \ factinv;\npublic:\n    explicit Factorial(int n) : facts(n+1), factinv(n+1)\
    \ {\n        facts[0] = 1;\n        for (int i = 1; i < n+1; ++i) facts[i] = facts[i-1]\
    \ * mint(i);\n        factinv[n] = facts[n].inv();\n        for (int i = n-1;\
    \ i >= 0; --i) factinv[i] = factinv[i+1] * mint(i+1);\n    }\n    mint fact(int\
    \ k) const {\n        if(k >= 0) return facts[k]; else return factinv[-k];\n \
    \   }\n    mint operator[](const int &k) const {\n        if(k >= 0) return facts[k];\
    \ else return factinv[-k];\n    }\n    mint C(int p, int q) const {\n        if(q\
    \ < 0 || p < q) return 0;\n        return facts[p] * factinv[q] * factinv[p-q];\n\
    \    }\n    mint P(int p, int q) const {\n        if(q < 0 || p < q) return 0;\n\
    \        return facts[p] * factinv[p-q];\n    }\n    mint H(int p, int q) const\
    \ {\n        if(p < 0 || q < 0) return 0;\n        return q == 0 ? 1 : C(p+q-1,\
    \ q);\n    }\n};"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/factorial.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/factorial.cpp
layout: document
redirect_from:
- /library/math/factorial.cpp
- /library/math/factorial.cpp.html
title: math/factorial.cpp
---
