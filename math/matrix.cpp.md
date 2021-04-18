---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix.cpp\"\ntemplate<class H>\nstruct matrix {\n\
    \    using T = typename H::T;\n    vector<vector<T>> A;\n    matrix() = default;\n\
    \    matrix(size_t n, size_t m) : A(n, vector<T>(m)) {}\n    explicit matrix(size_t\
    \ n) : A(n, vector<T> (n)) {};\n    size_t height() const { return (A.size());\
    \ }\n    size_t width() const { return (A[0].size()); }\n\n    const vector<T>\
    \ &operator [] (int k) const { return A[k]; }\n    vector<T> &operator[] (int\
    \ k) { return A[k]; }\n\n    static matrix I(size_t n){\n        matrix mat(n);\n\
    \        for (int i = 0; i < n; ++i) mat[i][i] = 1;\n        return mat;\n   \
    \ }\n\n    matrix &operator+= (const matrix &B){\n        size_t h = height(),\
    \ w = width();\n        for (int i = 0; i < h; ++i) {\n            for (int j\
    \ = 0; j < w; ++j) {\n                add((*this)[i][j], B[i][j]);\n         \
    \   }\n        }\n    }\n\n    matrix &operator-= (const matrix &B){\n       \
    \ size_t h = height(), w = width();\n        for (int i = 0; i < h; ++i) {\n \
    \           for (int j = 0; j < w; ++j) {\n                add((*this)[i][j],\
    \ -B[i][j]);\n            }\n        }\n    }\n\n    matrix &operator*=(const\
    \ matrix &B) {\n        size_t n = height(), m = B.width(), p = width();\n   \
    \     matrix C(n, m);\n        for (int i = 0; i < n; ++i) {\n            for\
    \ (int j = 0; j < m; ++j) {\n                for (int k = 0; k < p; ++k) {\n \
    \                   add(C[i][j], mul((*this)[i][k],B[k][j]));\n              \
    \  }\n            }\n        }\n        A.swap(C.A);\n        return (*this);\n\
    \    }\n\n    matrix pow(ll n) const {\n        matrix a = (*this), res = I(height());\n\
    \        while(n > 0){\n            if(n & 1) mul(res, a);\n            mul(a,\
    \ a);\n            n >>= 1;\n        }\n        return res;\n    }\n    matrix\
    \ operator+(const matrix &B) const {return matrix(*this) += B;}\n    matrix operator-(const\
    \ matrix &B) const {return matrix(*this) -= B;}\n    matrix operator*(const matrix\
    \ &B) const {return matrix(*this) *= B;}\n\n    mint detarminant(){\n        mint\
    \ res = 1;\n        int rank = 0;\n        for (int c = 0; c < width(); ++c) {\n\
    \            int k = -1;\n            for (int i = rank; i < height(); ++i) {\n\
    \                if(A[i][c] != H::zero()){\n                    k = i;\n     \
    \               break;\n                }\n            }\n            if(!~k)\
    \ continue;\n            swap(A[k], A[rank]);\n            res *= A[rank][c];\n\
    \            T x = T(1)/A[rank][c];\n            for (int j = 0; j < width();\
    \ ++j) A[rank][j] *= x;\n            for (int i = 0; i < height(); ++i) {\n  \
    \              if(i != rank && A[i][c] != H::zero()){\n                    T coeff\
    \ = A[i][c];\n                    for (int j = 0; j < width(); ++j) {\n      \
    \                  A[i][j] -= A[rank][j]*coeff;\n                    }\n     \
    \           }\n            }\n            rank++;\n        }\n        for (int\
    \ i = 0; i < min(width(), height()); ++i) {\n            res *= A[i][i];\n   \
    \     }\n        return res;\n    }\n};\n\nstruct SemiRing {\n    using T = mint;\n\
    \    static inline T mul(T x, T y){ return x * y; }\n    static inline void add(T\
    \ &x, T y){ x += y; }\n    static inline T one(){ return 1; }\n    static inline\
    \ T zero(){ return 0; }\n};\n"
  code: "template<class H>\nstruct matrix {\n    using T = typename H::T;\n    vector<vector<T>>\
    \ A;\n    matrix() = default;\n    matrix(size_t n, size_t m) : A(n, vector<T>(m))\
    \ {}\n    explicit matrix(size_t n) : A(n, vector<T> (n)) {};\n    size_t height()\
    \ const { return (A.size()); }\n    size_t width() const { return (A[0].size());\
    \ }\n\n    const vector<T> &operator [] (int k) const { return A[k]; }\n    vector<T>\
    \ &operator[] (int k) { return A[k]; }\n\n    static matrix I(size_t n){\n   \
    \     matrix mat(n);\n        for (int i = 0; i < n; ++i) mat[i][i] = 1;\n   \
    \     return mat;\n    }\n\n    matrix &operator+= (const matrix &B){\n      \
    \  size_t h = height(), w = width();\n        for (int i = 0; i < h; ++i) {\n\
    \            for (int j = 0; j < w; ++j) {\n                add((*this)[i][j],\
    \ B[i][j]);\n            }\n        }\n    }\n\n    matrix &operator-= (const\
    \ matrix &B){\n        size_t h = height(), w = width();\n        for (int i =\
    \ 0; i < h; ++i) {\n            for (int j = 0; j < w; ++j) {\n              \
    \  add((*this)[i][j], -B[i][j]);\n            }\n        }\n    }\n\n    matrix\
    \ &operator*=(const matrix &B) {\n        size_t n = height(), m = B.width(),\
    \ p = width();\n        matrix C(n, m);\n        for (int i = 0; i < n; ++i) {\n\
    \            for (int j = 0; j < m; ++j) {\n                for (int k = 0; k\
    \ < p; ++k) {\n                    add(C[i][j], mul((*this)[i][k],B[k][j]));\n\
    \                }\n            }\n        }\n        A.swap(C.A);\n        return\
    \ (*this);\n    }\n\n    matrix pow(ll n) const {\n        matrix a = (*this),\
    \ res = I(height());\n        while(n > 0){\n            if(n & 1) mul(res, a);\n\
    \            mul(a, a);\n            n >>= 1;\n        }\n        return res;\n\
    \    }\n    matrix operator+(const matrix &B) const {return matrix(*this) += B;}\n\
    \    matrix operator-(const matrix &B) const {return matrix(*this) -= B;}\n  \
    \  matrix operator*(const matrix &B) const {return matrix(*this) *= B;}\n\n  \
    \  mint detarminant(){\n        mint res = 1;\n        int rank = 0;\n       \
    \ for (int c = 0; c < width(); ++c) {\n            int k = -1;\n            for\
    \ (int i = rank; i < height(); ++i) {\n                if(A[i][c] != H::zero()){\n\
    \                    k = i;\n                    break;\n                }\n \
    \           }\n            if(!~k) continue;\n            swap(A[k], A[rank]);\n\
    \            res *= A[rank][c];\n            T x = T(1)/A[rank][c];\n        \
    \    for (int j = 0; j < width(); ++j) A[rank][j] *= x;\n            for (int\
    \ i = 0; i < height(); ++i) {\n                if(i != rank && A[i][c] != H::zero()){\n\
    \                    T coeff = A[i][c];\n                    for (int j = 0; j\
    \ < width(); ++j) {\n                        A[i][j] -= A[rank][j]*coeff;\n  \
    \                  }\n                }\n            }\n            rank++;\n\
    \        }\n        for (int i = 0; i < min(width(), height()); ++i) {\n     \
    \       res *= A[i][i];\n        }\n        return res;\n    }\n};\n\nstruct SemiRing\
    \ {\n    using T = mint;\n    static inline T mul(T x, T y){ return x * y; }\n\
    \    static inline void add(T &x, T y){ x += y; }\n    static inline T one(){\
    \ return 1; }\n    static inline T zero(){ return 0; }\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix.cpp
  requiredBy: []
  timestamp: '2021-04-18 09:38:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/matrix.cpp
layout: document
redirect_from:
- /library/math/matrix.cpp
- /library/math/matrix.cpp.html
title: math/matrix.cpp
---
