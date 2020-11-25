---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: fps/nth_term.cpp
    title: fps/nth_term.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0452.test.cpp
    title: test/aoj0452.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_convolution.test.cpp
    title: test/yosupo_convolution.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/ntt.cpp\"\nconstexpr int ntt_mod = 998244353, ntt_root\
    \ = 3;\n// 1012924417 -> 5, 924844033 -> 5\n// 998244353  -> 3, 897581057 -> 3\n\
    // 645922817  -> 3;\ntemplate <u32 M>\nstruct modint {\n    u32 val;\npublic:\n\
    \    static modint raw(int v) { modint x; x.val = v; return x; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = u32(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val\
    \ -= M; return *this; }\n    modint& operator-=(const modint& rhs) { val -= rhs.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ rhs) { u64 z = val; z *= rhs.val; val = (u32)(z % M); return *this; }\n    modint&\
    \ operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(M-2); }\n    friend modint operator+(const modint& lhs, const modint&\
    \ rhs) { return modint(lhs) += rhs; }\n    friend modint operator-(const modint&\
    \ lhs, const modint& rhs) { return modint(lhs) -= rhs; }\n    friend modint operator*(const\
    \ modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }\n    friend modint\
    \ operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs;\
    \ }\n    friend bool operator==(const modint& lhs, const modint& rhs) { return\
    \ lhs.val == rhs.val; }\n    friend bool operator!=(const modint& lhs, const modint&\
    \ rhs) { return lhs.val != rhs.val; }\n};\nusing mint = modint<998244353>;\n\n\
    class NTT {\n    static constexpr int max_base = 20, maxN = 1 << max_base; //\
    \ N <= 524288 * 2\n    mint sum_e[30], sum_ie[30];\npublic:\n    mint es[30],\
    \ ies[30];\n    NTT() {\n        int cnt2 = __builtin_ctz(ntt_mod-1);\n      \
    \  mint e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();\n        for\
    \ (int i = cnt2; i >= 0; i--){\n            es[i] = e; ies[i] = ie;\n        \
    \    e *= e; ie *= ie;\n        }\n        mint now = 1, nowi = 1;\n        for\
    \ (int i = 0; i < cnt2 - 2; i++) {\n            sum_e[i] = es[i+2] * now; now\
    \ *= ies[i+2];\n            sum_ie[i] = ies[i+2] * nowi; nowi *= es[i+2];\n  \
    \      }\n    }\n\n    void transform(vector<mint> &a, int sign){\n        const\
    \ int n = a.size();\n        int h = 0;\n        while ((1U << h) < (unsigned\
    \ int)(n)) h++;\n        if(!sign){ // fft\n            for (int ph = 1; ph <=\
    \ h; ph++) {\n                int w = 1 << (ph-1), p = 1 << (h-ph);\n        \
    \        mint now = 1;\n                for (int s = 0; s < w; s++) {\n      \
    \              int offset = s << (h-ph+1);\n                    for (int i = 0;\
    \ i < p; i++) {\n                        auto l = a[i+offset], r = a[i+offset+p]*now;\n\
    \                        a[i+offset] = l+r, a[i+offset+p] = l-r;\n           \
    \         }\n                    now *= sum_e[__builtin_ctz(~(unsigned int)(s))];\n\
    \                }\n            }\n        }else { // ifft\n            for (int\
    \ ph = h; ph >= 1; ph--) {\n                int w = 1 << (ph-1), p = 1 << (h-ph);\n\
    \                mint inow = 1;\n                for (int s = 0; s < w; s++) {\n\
    \                    int offset = s << (h-ph+1);\n                    for (int\
    \ i = 0; i < p; i++) {\n                        auto l = a[i+offset], r = a[i+offset+p];\n\
    \                        a[i+offset] = l+r, a[i+offset+p] = (l-r)*inow;\n    \
    \                }\n                    inow *= sum_ie[__builtin_ctz(~(unsigned\
    \ int)(s))];\n                }\n            }\n        }\n    }\n};\n\nNTT ntt;\n\
    \nstruct poly {\n    vector<mint> v;\n    poly() = default;\n    explicit poly(int\
    \ n) : v(n) {};\n    explicit poly(vector<mint> vv) : v(std::move(vv)) {};\n \
    \   int size() const {return (int)v.size(); }\n    poly cut(int len){\n      \
    \  if(len < v.size()) v.resize(static_cast<unsigned long>(len));\n        return\
    \ *this;\n    }\n    inline mint& operator[] (int i) {return v[i]; }\n    poly&\
    \ operator+=(const poly &a) {\n        this->v.resize(max(size(), a.size()));\n\
    \        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n        return\
    \ *this;\n    }\n    poly& operator-=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];\n\
    \        return *this;\n    }\n    poly& operator*=(poly a) {\n        int N =\
    \ size()+a.size()-1;\n        int sz = 1;\n        while(sz < N) sz <<= 1;\n \
    \       this->v.resize(sz); a.v.resize(sz);\n        ntt.transform(this->v, 0);\
    \ ntt.transform(a.v, 0);\n        for(int i = 0; i < sz; ++i) this->v[i] *= a.v[i];\n\
    \        ntt.transform(this->v, 1);\n        this->v.resize(N);\n        mint\
    \ iz = mint(sz).inv();\n        for (int i = 0; i < N; i++) this->v[i] *= iz;\n\
    \        return *this;\n    }\n    poly& operator/=(const poly &a){ return (*this\
    \ *= a.inv()); }\n    poly operator+(const poly &a) const { return poly(*this)\
    \ += a; }\n    poly operator-(const poly &a) const { return poly(*this) -= a;\
    \ }\n    poly operator*(const poly &a) const { return poly(*this) *= a; }\n\n\
    \    poly inv() const {\n        int n = size();\n        poly r(1);\n       \
    \ r[0] = (this->v[0]).inv();\n        for (int k = 1; k < n; k <<= 1) {\n    \
    \        poly ff(2*k);\n            for (int i = 0; i < min(k*2, n); ++i) ff[i]\
    \ = this->v[i];\n            poly nr = (r*r*ff).cut(k*2);\n            for (int\
    \ i = 0; i < k; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n         \
    \       nr[i+k] = -nr[i+k];\n            }\n            r = nr;\n        }\n \
    \       r.v.resize(n);\n        return r;\n    }\n};\n"
  code: "constexpr int ntt_mod = 998244353, ntt_root = 3;\n// 1012924417 -> 5, 924844033\
    \ -> 5\n// 998244353  -> 3, 897581057 -> 3\n// 645922817  -> 3;\ntemplate <u32\
    \ M>\nstruct modint {\n    u32 val;\npublic:\n    static modint raw(int v) { modint\
    \ x; x.val = v; return x; }\n    modint() : val(0) {}\n    template <class T>\n\
    \    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = u32(x); }\n\
    \    modint(bool v) { val = ((unsigned int)(v) % M); }\n    modint& operator++()\
    \ { val++; if (val == M) val = 0; return *this; }\n    modint& operator--() {\
    \ if (val == 0) val = M; val--; return *this; }\n    modint operator++(int) {\
    \ modint result = *this; ++*this; return result; }\n    modint operator--(int)\
    \ { modint result = *this; --*this; return result; }\n    modint& operator+=(const\
    \ modint& rhs) { val += rhs.val; if (val >= M) val -= M; return *this; }\n   \
    \ modint& operator-=(const modint& rhs) { val -= rhs.val; if (val >= M) val +=\
    \ M; return *this; }\n    modint& operator*=(const modint& rhs) { u64 z = val;\
    \ z *= rhs.val; val = (u32)(z % M); return *this; }\n    modint& operator/=(const\
    \ modint& rhs) { return *this = *this * rhs.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(M-2); }\n    friend modint operator+(const modint& lhs, const modint& rhs)\
    \ { return modint(lhs) += rhs; }\n    friend modint operator-(const modint& lhs,\
    \ const modint& rhs) { return modint(lhs) -= rhs; }\n    friend modint operator*(const\
    \ modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }\n    friend modint\
    \ operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs;\
    \ }\n    friend bool operator==(const modint& lhs, const modint& rhs) { return\
    \ lhs.val == rhs.val; }\n    friend bool operator!=(const modint& lhs, const modint&\
    \ rhs) { return lhs.val != rhs.val; }\n};\nusing mint = modint<998244353>;\n\n\
    class NTT {\n    static constexpr int max_base = 20, maxN = 1 << max_base; //\
    \ N <= 524288 * 2\n    mint sum_e[30], sum_ie[30];\npublic:\n    mint es[30],\
    \ ies[30];\n    NTT() {\n        int cnt2 = __builtin_ctz(ntt_mod-1);\n      \
    \  mint e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();\n        for\
    \ (int i = cnt2; i >= 0; i--){\n            es[i] = e; ies[i] = ie;\n        \
    \    e *= e; ie *= ie;\n        }\n        mint now = 1, nowi = 1;\n        for\
    \ (int i = 0; i < cnt2 - 2; i++) {\n            sum_e[i] = es[i+2] * now; now\
    \ *= ies[i+2];\n            sum_ie[i] = ies[i+2] * nowi; nowi *= es[i+2];\n  \
    \      }\n    }\n\n    void transform(vector<mint> &a, int sign){\n        const\
    \ int n = a.size();\n        int h = 0;\n        while ((1U << h) < (unsigned\
    \ int)(n)) h++;\n        if(!sign){ // fft\n            for (int ph = 1; ph <=\
    \ h; ph++) {\n                int w = 1 << (ph-1), p = 1 << (h-ph);\n        \
    \        mint now = 1;\n                for (int s = 0; s < w; s++) {\n      \
    \              int offset = s << (h-ph+1);\n                    for (int i = 0;\
    \ i < p; i++) {\n                        auto l = a[i+offset], r = a[i+offset+p]*now;\n\
    \                        a[i+offset] = l+r, a[i+offset+p] = l-r;\n           \
    \         }\n                    now *= sum_e[__builtin_ctz(~(unsigned int)(s))];\n\
    \                }\n            }\n        }else { // ifft\n            for (int\
    \ ph = h; ph >= 1; ph--) {\n                int w = 1 << (ph-1), p = 1 << (h-ph);\n\
    \                mint inow = 1;\n                for (int s = 0; s < w; s++) {\n\
    \                    int offset = s << (h-ph+1);\n                    for (int\
    \ i = 0; i < p; i++) {\n                        auto l = a[i+offset], r = a[i+offset+p];\n\
    \                        a[i+offset] = l+r, a[i+offset+p] = (l-r)*inow;\n    \
    \                }\n                    inow *= sum_ie[__builtin_ctz(~(unsigned\
    \ int)(s))];\n                }\n            }\n        }\n    }\n};\n\nNTT ntt;\n\
    \nstruct poly {\n    vector<mint> v;\n    poly() = default;\n    explicit poly(int\
    \ n) : v(n) {};\n    explicit poly(vector<mint> vv) : v(std::move(vv)) {};\n \
    \   int size() const {return (int)v.size(); }\n    poly cut(int len){\n      \
    \  if(len < v.size()) v.resize(static_cast<unsigned long>(len));\n        return\
    \ *this;\n    }\n    inline mint& operator[] (int i) {return v[i]; }\n    poly&\
    \ operator+=(const poly &a) {\n        this->v.resize(max(size(), a.size()));\n\
    \        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n        return\
    \ *this;\n    }\n    poly& operator-=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];\n\
    \        return *this;\n    }\n    poly& operator*=(poly a) {\n        int N =\
    \ size()+a.size()-1;\n        int sz = 1;\n        while(sz < N) sz <<= 1;\n \
    \       this->v.resize(sz); a.v.resize(sz);\n        ntt.transform(this->v, 0);\
    \ ntt.transform(a.v, 0);\n        for(int i = 0; i < sz; ++i) this->v[i] *= a.v[i];\n\
    \        ntt.transform(this->v, 1);\n        this->v.resize(N);\n        mint\
    \ iz = mint(sz).inv();\n        for (int i = 0; i < N; i++) this->v[i] *= iz;\n\
    \        return *this;\n    }\n    poly& operator/=(const poly &a){ return (*this\
    \ *= a.inv()); }\n    poly operator+(const poly &a) const { return poly(*this)\
    \ += a; }\n    poly operator-(const poly &a) const { return poly(*this) -= a;\
    \ }\n    poly operator*(const poly &a) const { return poly(*this) *= a; }\n\n\
    \    poly inv() const {\n        int n = size();\n        poly r(1);\n       \
    \ r[0] = (this->v[0]).inv();\n        for (int k = 1; k < n; k <<= 1) {\n    \
    \        poly ff(2*k);\n            for (int i = 0; i < min(k*2, n); ++i) ff[i]\
    \ = this->v[i];\n            poly nr = (r*r*ff).cut(k*2);\n            for (int\
    \ i = 0; i < k; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n         \
    \       nr[i+k] = -nr[i+k];\n            }\n            r = nr;\n        }\n \
    \       r.v.resize(n);\n        return r;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/ntt.cpp
  requiredBy:
  - fps/nth_term.cpp
  timestamp: '2020-11-24 21:58:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0452.test.cpp
  - test/yosupo_convolution.test.cpp
documentation_of: math/ntt.cpp
layout: document
redirect_from:
- /library/math/ntt.cpp
- /library/math/ntt.cpp.html
title: math/ntt.cpp
---
