---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix.cpp\"\ntemplate<class T>\nstruct matrix {\n\
    \    vector<vector<T>> A;\n    matrix() = default;\n    matrix(size_t n, size_t\
    \ m) : A(n, vector<T>(m)) {}\n    explicit matrix(size_t n) : A(n, vector<T> (n))\
    \ {};\n    size_t height() const { return (A.size()); }\n    size_t width() const\
    \ { return (A[0].size()); }\n\n    const vector<T> &operator [] (int k) const\
    \ { return A[k]; }\n    vector<T> &operator[] (int k) { return A[k]; }\n\n   \
    \ static matrix I(size_t n){\n        matrix mat(n);\n        for (int i = 0;\
    \ i < n; ++i) mat[i][i] = 1;\n        return mat;\n    }\n\n    matrix &operator+=\
    \ (const matrix &B){\n        size_t h = height(), w = width();\n        for (int\
    \ i = 0; i < h; ++i) {\n            for (int j = 0; j < w; ++j) {\n          \
    \      (*this)[i][j] += B[i][j];\n            }\n        }\n    }\n\n    matrix\
    \ &operator-= (const matrix &B){\n        size_t h = height(), w = width();\n\
    \        for (int i = 0; i < h; ++i) {\n            for (int j = 0; j < w; ++j)\
    \ {\n                (*this)[i][j] -= B[i][j];\n            }\n        }\n   \
    \ }\n\n    matrix &operator*=(const matrix &B)\n    {\n        size_t n = height(),\
    \ m = B.width(), p = width();\n        matrix C (n, m);\n        for (int i =\
    \ 0; i < n; ++i) {\n            for (int j = 0; j < m; ++j) {\n              \
    \  for (int k = 0; k < p; ++k) {\n                    C[i][j] = (C[i][j] + (*this)[i][k]\
    \ * B[k][j]);\n                }\n            }\n        }\n        A.swap(C.A);\n\
    \        return (*this);\n    }\n\n    template <class U>\n    matrix &operator%=\
    \ (const U &m){\n        for (int i = 0; i < height(); ++i) {\n            for\
    \ (int j = 0; j < width(); ++j) {\n                (*this)[i][j] %= m;\n     \
    \       }\n        }\n    }\n\n    matrix pow(ll n) const {\n        matrix a\
    \ = (*this), res = I(height());\n        while(n > 0){\n            if(n & 1)\
    \ res *= a;\n            a *= a;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n    matrix operator+(const matrix &A) const {return matrix(*this)\
    \ += A;}\n    matrix operator-(const matrix &A) const {return matrix(*this) -=\
    \ A;}\n    matrix operator*(const matrix &A) const {return matrix(*this) *= A;}\n\
    \    template <class U>\n    matrix operator%(const U &m) const {return matrix(*this)\
    \ %= m;}\n\n};\n"
  code: "template<class T>\nstruct matrix {\n    vector<vector<T>> A;\n    matrix()\
    \ = default;\n    matrix(size_t n, size_t m) : A(n, vector<T>(m)) {}\n    explicit\
    \ matrix(size_t n) : A(n, vector<T> (n)) {};\n    size_t height() const { return\
    \ (A.size()); }\n    size_t width() const { return (A[0].size()); }\n\n    const\
    \ vector<T> &operator [] (int k) const { return A[k]; }\n    vector<T> &operator[]\
    \ (int k) { return A[k]; }\n\n    static matrix I(size_t n){\n        matrix mat(n);\n\
    \        for (int i = 0; i < n; ++i) mat[i][i] = 1;\n        return mat;\n   \
    \ }\n\n    matrix &operator+= (const matrix &B){\n        size_t h = height(),\
    \ w = width();\n        for (int i = 0; i < h; ++i) {\n            for (int j\
    \ = 0; j < w; ++j) {\n                (*this)[i][j] += B[i][j];\n            }\n\
    \        }\n    }\n\n    matrix &operator-= (const matrix &B){\n        size_t\
    \ h = height(), w = width();\n        for (int i = 0; i < h; ++i) {\n        \
    \    for (int j = 0; j < w; ++j) {\n                (*this)[i][j] -= B[i][j];\n\
    \            }\n        }\n    }\n\n    matrix &operator*=(const matrix &B)\n\
    \    {\n        size_t n = height(), m = B.width(), p = width();\n        matrix\
    \ C (n, m);\n        for (int i = 0; i < n; ++i) {\n            for (int j = 0;\
    \ j < m; ++j) {\n                for (int k = 0; k < p; ++k) {\n             \
    \       C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);\n                }\n  \
    \          }\n        }\n        A.swap(C.A);\n        return (*this);\n    }\n\
    \n    template <class U>\n    matrix &operator%= (const U &m){\n        for (int\
    \ i = 0; i < height(); ++i) {\n            for (int j = 0; j < width(); ++j) {\n\
    \                (*this)[i][j] %= m;\n            }\n        }\n    }\n\n    matrix\
    \ pow(ll n) const {\n        matrix a = (*this), res = I(height());\n        while(n\
    \ > 0){\n            if(n & 1) res *= a;\n            a *= a;\n            n >>=\
    \ 1;\n        }\n        return res;\n    }\n    matrix operator+(const matrix\
    \ &A) const {return matrix(*this) += A;}\n    matrix operator-(const matrix &A)\
    \ const {return matrix(*this) -= A;}\n    matrix operator*(const matrix &A) const\
    \ {return matrix(*this) *= A;}\n    template <class U>\n    matrix operator%(const\
    \ U &m) const {return matrix(*this) %= m;}\n\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/matrix.cpp
layout: document
redirect_from:
- /library/math/matrix.cpp
- /library/math/matrix.cpp.html
title: math/matrix.cpp
---
