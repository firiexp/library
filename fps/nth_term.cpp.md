---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/ntt.cpp
    title: math/ntt.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
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
    \       r.v.resize(n);\n        return r;\n    }\n};\n#line 2 \"fps/nth_term.cpp\"\
    \nmint nth_term(poly p, poly q, ll n){\n    if(!n) return p[0]/q[0];\n    int\
    \ sz = 1, h = 0;\n    int k = max(p.size(), q.size());\n    while(sz < 2*k-1)\
    \ sz <<= 1, h++;\n    p.v.resize(sz); q.v.resize(sz);\n    mint x = mint(sz>>1).inv();\n\
    \    vector<mint> y(sz>>1, 0);\n    for (int j = sz>>2, i = h; j; j >>= 1, i--)\
    \ y[j] = ntt.ies[i];\n    y[0] = 1;\n    for (int i = 2; i < sz>>1; i <<= 1) {\n\
    \        for (int j = i+1; j < 2*i; ++j) {\n            y[j] = y[j-i]*y[i];\n\
    \        }\n    }\n    ntt.transform(p.v, 0);\n    ntt.transform(q.v, 0);\n  \
    \  poly tmp(sz>>1);\n    auto up = [&](poly &A){\n        for (int i = 0; i <\
    \ sz>>1; ++i) tmp[i] = A[i];\n        ntt.transform(tmp.v, 1);\n        mint now\
    \ = x;\n        for (int i = 0; i < sz>>1; ++i) tmp[i] *= now, now *= ntt.es[h];\n\
    \        ntt.transform(tmp.v, 0);\n        for (int i = 0; i < sz>>1; ++i) A[i|(sz>>1)]\
    \ = tmp[i];\n    };\n    int ika = h;\n    while(n){\n        for (int i = 0;\
    \ i < sz; ++i) p[i] *= q[i^1];\n        if(n&1) for (int i = 0; i < sz>>1; ++i)\
    \ p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];\n        else for (int i = 0; i < sz>>1;\
    \ ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);\n        ika++;\n        if(n == 1) break;\n\
    \        up(p);\n        for (int i = 0; i < sz>>1; ++i) q[i] = q[i<<1]*q[(i<<1)|1];\n\
    \        up(q);\n        n >>= 1;\n    }\n    for (int i = 0; i < sz>>1; ++i)\
    \ tmp[i] = p[i];\n    ntt.transform(tmp.v, 1);\n    return mint(2).pow(ntt_mod-ika)*tmp[0];\n\
    }\n"
  code: "#include \"../math/ntt.cpp\"\nmint nth_term(poly p, poly q, ll n){\n    if(!n)\
    \ return p[0]/q[0];\n    int sz = 1, h = 0;\n    int k = max(p.size(), q.size());\n\
    \    while(sz < 2*k-1) sz <<= 1, h++;\n    p.v.resize(sz); q.v.resize(sz);\n \
    \   mint x = mint(sz>>1).inv();\n    vector<mint> y(sz>>1, 0);\n    for (int j\
    \ = sz>>2, i = h; j; j >>= 1, i--) y[j] = ntt.ies[i];\n    y[0] = 1;\n    for\
    \ (int i = 2; i < sz>>1; i <<= 1) {\n        for (int j = i+1; j < 2*i; ++j) {\n\
    \            y[j] = y[j-i]*y[i];\n        }\n    }\n    ntt.transform(p.v, 0);\n\
    \    ntt.transform(q.v, 0);\n    poly tmp(sz>>1);\n    auto up = [&](poly &A){\n\
    \        for (int i = 0; i < sz>>1; ++i) tmp[i] = A[i];\n        ntt.transform(tmp.v,\
    \ 1);\n        mint now = x;\n        for (int i = 0; i < sz>>1; ++i) tmp[i] *=\
    \ now, now *= ntt.es[h];\n        ntt.transform(tmp.v, 0);\n        for (int i\
    \ = 0; i < sz>>1; ++i) A[i|(sz>>1)] = tmp[i];\n    };\n    int ika = h;\n    while(n){\n\
    \        for (int i = 0; i < sz; ++i) p[i] *= q[i^1];\n        if(n&1) for (int\
    \ i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];\n        else for\
    \ (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);\n        ika++;\n\
    \        if(n == 1) break;\n        up(p);\n        for (int i = 0; i < sz>>1;\
    \ ++i) q[i] = q[i<<1]*q[(i<<1)|1];\n        up(q);\n        n >>= 1;\n    }\n\
    \    for (int i = 0; i < sz>>1; ++i) tmp[i] = p[i];\n    ntt.transform(tmp.v,\
    \ 1);\n    return mint(2).pow(ntt_mod-ika)*tmp[0];\n}"
  dependsOn:
  - math/ntt.cpp
  isVerificationFile: false
  path: fps/nth_term.cpp
  requiredBy: []
  timestamp: '2020-11-24 21:58:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/nth_term.cpp
layout: document
redirect_from:
- /library/fps/nth_term.cpp
- /library/fps/nth_term.cpp.html
title: fps/nth_term.cpp
---
