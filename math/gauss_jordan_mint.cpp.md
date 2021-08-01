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
    \ \"math/gauss_jordan_mint.cpp\"\n\nint gauss_jordan(vector<vector<mint>> &A,\
    \ bool is_extended = false) {\n    int m = A.size(), n = A[0].size();\n    int\
    \ rank = 0;\n    for (int col = 0; col < n; ++col) {\n        if (is_extended\
    \ && col == n-1) break;\n        int pivot = -1;\n        for (int row = rank;\
    \ row < m; ++row) {\n            if (A[row][col].val) {\n                pivot\
    \ = row;\n                break;\n            }\n        }\n        if (pivot\
    \ == -1) continue;\n        swap(A[pivot], A[rank]);\n        auto d = A[rank][col].inv();\n\
    \        for (int col2 = 0; col2 < n; ++col2) A[rank][col2] *= d;\n        for\
    \ (int row = 0; row < m; ++row) {\n            if (row != rank && A[row][col].val)\
    \ {\n                auto fac = A[row][col];\n                for (int col2 =\
    \ 0; col2 < n; ++col2) {\n                    A[row][col2] -= A[rank][col2] *\
    \ fac;\n                }\n            }\n        }\n        ++rank;\n    }\n\
    \    return rank;\n}\n"
  code: "#include \"../util/modint.cpp\"\n\nint gauss_jordan(vector<vector<mint>>\
    \ &A, bool is_extended = false) {\n    int m = A.size(), n = A[0].size();\n  \
    \  int rank = 0;\n    for (int col = 0; col < n; ++col) {\n        if (is_extended\
    \ && col == n-1) break;\n        int pivot = -1;\n        for (int row = rank;\
    \ row < m; ++row) {\n            if (A[row][col].val) {\n                pivot\
    \ = row;\n                break;\n            }\n        }\n        if (pivot\
    \ == -1) continue;\n        swap(A[pivot], A[rank]);\n        auto d = A[rank][col].inv();\n\
    \        for (int col2 = 0; col2 < n; ++col2) A[rank][col2] *= d;\n        for\
    \ (int row = 0; row < m; ++row) {\n            if (row != rank && A[row][col].val)\
    \ {\n                auto fac = A[row][col];\n                for (int col2 =\
    \ 0; col2 < n; ++col2) {\n                    A[row][col2] -= A[rank][col2] *\
    \ fac;\n                }\n            }\n        }\n        ++rank;\n    }\n\
    \    return rank;\n}"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/gauss_jordan_mint.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/gauss_jordan_mint.cpp
layout: document
redirect_from:
- /library/math/gauss_jordan_mint.cpp
- /library/math/gauss_jordan_mint.cpp.html
title: math/gauss_jordan_mint.cpp
---
