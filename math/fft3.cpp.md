---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fft3.cpp\"\ntemplate<u32 M = 1000000007>\nstruct modint{\n\
    \    u32 val;\n    modint(): val(0){}\n    template<typename T>\n    modint(T\
    \ t){t %= (T)M; if(t < 0) t += (T)M; val = t;}\n\n    modint pow(ll k) const {\n\
    \        modint res(1), x(val);\n        while(k){\n            if(k&1) res *=\
    \ x;\n            x *= x;\n            k >>= 1;\n        }\n        return res;\n\
    \    }\n    template<typename T>\n    modint& operator=(T t){t %= (T)M; if(t <\
    \ 0) t += (T)M; val = t; return *this; }\n    modint inv() const {return pow(M-2);}\n\
    \    modint& operator+=(modint a){ val += a.val; if(val >= M) val -= M; return\
    \ *this;}\n    modint& operator-=(modint a){ if(val < a.val) val += M-a.val; else\
    \ val -= a.val; return *this;}\n    modint& operator*=(modint a){ val = (u64)val*a.val%M;\
    \ return *this;}\n    modint& operator/=(modint a){ return (*this) *= a.inv();}\n\
    \    modint operator+(modint a) const {return modint(val) +=a;}\n    modint operator-(modint\
    \ a) const {return modint(val) -=a;}\n    modint operator*(modint a) const {return\
    \ modint(val) *=a;}\n    modint operator/(modint a) const {return modint(val)\
    \ /=a;}\n    modint operator-(){ return modint(M-val);}\n    bool operator==(const\
    \ modint a) const {return val == a.val;}\n    bool operator!=(const modint a)\
    \ const {return val != a.val;}\n    bool operator<(const modint a) const {return\
    \ val < a.val;}\n};\n\nusing mint = modint<>;\n\nnamespace FFT {\n    const int\
    \ max_base = 20, maxN = 1 << max_base; // N <= 5e5\n    const double PI = acos(-1);\n\
    \    struct num {\n        double x{}, y{};\n        num() = default;\n      \
    \  num(double x, double y): x(x), y(y) {}\n        explicit num(double r): x(cos(r)),\
    \ y(sin(r)) {}\n    };\n    num operator+(num a, num b) { return {a.x + b.x, a.y\
    \ + b.y}; }\n    num operator-(num a, num b) { return {a.x - b.x, a.y - b.y};\
    \ }\n    num operator*(num a, num b) { return {a.x * b.x - a.y * b.y, a.x * b.y\
    \ + a.y * b.x}; }\n    num conj(num a) {return {a.x, -a.y}; }\n    num root[maxN];\n\
    \    int rev[maxN];\n    bool is_root_prepared = false;\n\n    void prepare_root(){\n\
    \        if(is_root_prepared) return;\n        is_root_prepared = true;\n    \
    \    root[1] = num(1, 0);\n        for (int i = 1; i < max_base; ++i) {\n    \
    \        num x(2*PI / (1LL << (i+1)));\n            for (ll j = (1LL << (i-1));\
    \ j < (1LL << (i)); ++j) {\n                root[2*j] = root[j];\n           \
    \     root[2*j+1] = root[j]*x;\n            }\n        }\n    }\n\n    int base,\
    \ N;\n    int lastN = -1;\n\n    void prepare_rev(){\n        if(lastN == N) return;\n\
    \        lastN = N;\n        for (int i = 0; i < N; ++i) rev[i] = (rev[i >> 1]\
    \ >> 1) + ((i & 1) << (base - 1));\n    }\n\n    void fft(num *a, num *f){\n \
    \       for (int i = 0; i < N; ++i) f[i] = a[rev[i]];\n        for (int k = 1;\
    \ k < N; k <<= 1) {\n            for (int i = 0; i < N; i += 2*k) {\n        \
    \        for (int j = 0; j < k; ++j) {\n                    num z = f[i+j+k]*\
    \ root[j+k];\n                    f[i+j+k] = f[i+j] - z;\n                   \
    \ f[i+j] = f[i+j] + z;\n                }\n            }\n        }\n    }\n \
    \   num a[maxN], b[maxN], c[maxN], f1[maxN], f2[maxN], f3[maxN];\n    ll A[maxN],\
    \ B[maxN], C[maxN];\n    constexpr ll mask1 = (1LL << 11)-1, mask2 = (1LL << 22)-(1LL\
    \ << 11), mask3 = (1LL << 33) - (1LL << 22);\n    void multi_mod(){\n        for\
    \ (int i = 0; i < N; ++i) {\n            a[i] = num( A[i] & mask1,  (A[i] & mask2)\
    \ >> 11);\n        }\n        for (int i = 0; i < N; ++i) {\n            b[i]\
    \ = num( B[i] & mask1,  (B[i] & mask2) >> 11);\n        }\n        for (int i\
    \ = 0; i < N; ++i) {\n            c[i] = num((A[i] & mask3) >> 22, (B[i] & mask3)\
    \ >> 22);\n        }\n        fft(a, f1);\n        fft(b, f2);\n        fft(c,\
    \ f3);\n        for (int i = 0; i < N; ++i) {\n            int j = (N-i)&(N-1);\n\
    \            num a1 = (f1[i] + conj(f1[j])) * num(0.5, 0);\n            num a2\
    \ = (f1[i] - conj(f1[j])) * num(0, -0.5);\n            num a3 = (f3[i] + conj(f3[j]))\
    \ * num(0.5, 0);\n            num b1 = (f2[i] + conj(f2[j])) * num(0.5/N, 0);\n\
    \            num b2 = (f2[i] - conj(f2[j])) * num(0, -0.5/N);\n            num\
    \ b3 = (f3[i] - conj(f3[j])) * num(0, -0.5/N);\n            a[j] = a1*b1 + (a1*b2\
    \ + a2*b1) * num(0, 1);\n            b[j] = (a1*b3 + a2*b2 + a3*b1) + (a2*b3 +\
    \ a3*b2) * num(0, 1);\n            c[j] = a3*b3;\n        }\n        fft(a, f1);\n\
    \        fft(b, f2);\n        fft(c, f3);\n        for (int i = 0; i < N; ++i)\
    \ {\n            ll k1 = f1[i].x + 0.5;\n            ll k2 = f1[i].y + 0.5;\n\
    \            ll k3 = f2[i].x + 0.5;\n            ll k4 = f2[i].y + 0.5;\n    \
    \        ll k5 = f3[i].x + 0.5;\n            C[i] = (k1 + ((k2 + ((k3 + ((k4 +\
    \ (k5 << 11) % MOD) << 11) % MOD) << 11) % MOD) << 11)) % MOD;\n        }\n  \
    \  }\n\n    void prepare_AB(int n1, int n2){\n        base = 1;\n        N = 2;\n\
    \        while(N < n1+n2) base++, N <<= 1;\n        for (int i = n1; i < N; ++i)\
    \ A[i] = 0;\n        for (int i = n2; i < N; ++i) B[i] = 0;\n        prepare_root();\n\
    \        prepare_rev();\n    }\n\n    void multi_mod(int n1, int n2){\n      \
    \  prepare_AB(n1, n2);\n        multi_mod();\n    }\n}\n\nstruct poly {\n    vector<mint>\
    \ v;\n    poly() = default;\n    explicit poly(int n) : v(n) {};\n    explicit\
    \ poly(vector<mint> vv) : v(std::move(vv)) {};\n    int size() const {return (int)v.size();\
    \ }\n    poly cut(int len){\n        if(len < v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly& operator-=(const poly &a) {\n       \
    \ this->v.resize(max(size(), a.size()));\n        for (int i = 0; i < a.size();\
    \ ++i) this->v[i] -= a.v[i];\n        return *this;\n    }\n\n    poly& operator*=(poly\
    \ a) {\n        for (int i = 0; i < size(); ++i) FFT::A[i] = this->v[i].val;\n\
    \        for (int i = 0; i < a.size(); ++i) FFT::B[i] = a.v[i].val;\n        FFT::multi_mod(size(),\
    \ a.size());\n        this->v.resize(size() + a.size()-1);\n        for (int i\
    \ = 0; i < size(); ++i) this->v[i] = FFT::C[i];\n        return *this;\n    }\n\
    \    poly& operator/=(const poly &a){ return (*this *= a.inv()); }\n    poly operator+(const\
    \ poly &a) const { return poly(*this) += a; }\n    poly operator-(const poly &a)\
    \ const { return poly(*this) -= a; }\n    poly operator*(const poly &a) const\
    \ { return poly(*this) *= a; }\n\n    poly inv() const {\n        int n = size();\n\
    \        poly r(1);\n        r[0] = (this->v[0]).inv();\n        int k = 1;\n\
    \        while(k < n){\n            k *= 2;\n            poly ff(k);\n       \
    \     for (int i = 0; i < min(k, n); ++i) {\n                ff[i] = this->v[i];\n\
    \            }\n            poly nr = (r*r*ff).cut(k);\n            for (int i\
    \ = 0; i < k/2; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n         \
    \       nr[i+k/2] = -nr[i+k/2];\n            }\n            r = nr;\n        }\n\
    \        r.v.resize(n);\n        return r;\n    }\n};\n"
  code: "template<u32 M = 1000000007>\nstruct modint{\n    u32 val;\n    modint():\
    \ val(0){}\n    template<typename T>\n    modint(T t){t %= (T)M; if(t < 0) t +=\
    \ (T)M; val = t;}\n\n    modint pow(ll k) const {\n        modint res(1), x(val);\n\
    \        while(k){\n            if(k&1) res *= x;\n            x *= x;\n     \
    \       k >>= 1;\n        }\n        return res;\n    }\n    template<typename\
    \ T>\n    modint& operator=(T t){t %= (T)M; if(t < 0) t += (T)M; val = t; return\
    \ *this; }\n    modint inv() const {return pow(M-2);}\n    modint& operator+=(modint\
    \ a){ val += a.val; if(val >= M) val -= M; return *this;}\n    modint& operator-=(modint\
    \ a){ if(val < a.val) val += M-a.val; else val -= a.val; return *this;}\n    modint&\
    \ operator*=(modint a){ val = (u64)val*a.val%M; return *this;}\n    modint& operator/=(modint\
    \ a){ return (*this) *= a.inv();}\n    modint operator+(modint a) const {return\
    \ modint(val) +=a;}\n    modint operator-(modint a) const {return modint(val)\
    \ -=a;}\n    modint operator*(modint a) const {return modint(val) *=a;}\n    modint\
    \ operator/(modint a) const {return modint(val) /=a;}\n    modint operator-(){\
    \ return modint(M-val);}\n    bool operator==(const modint a) const {return val\
    \ == a.val;}\n    bool operator!=(const modint a) const {return val != a.val;}\n\
    \    bool operator<(const modint a) const {return val < a.val;}\n};\n\nusing mint\
    \ = modint<>;\n\nnamespace FFT {\n    const int max_base = 20, maxN = 1 << max_base;\
    \ // N <= 5e5\n    const double PI = acos(-1);\n    struct num {\n        double\
    \ x{}, y{};\n        num() = default;\n        num(double x, double y): x(x),\
    \ y(y) {}\n        explicit num(double r): x(cos(r)), y(sin(r)) {}\n    };\n \
    \   num operator+(num a, num b) { return {a.x + b.x, a.y + b.y}; }\n    num operator-(num\
    \ a, num b) { return {a.x - b.x, a.y - b.y}; }\n    num operator*(num a, num b)\
    \ { return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }\n    num conj(num\
    \ a) {return {a.x, -a.y}; }\n    num root[maxN];\n    int rev[maxN];\n    bool\
    \ is_root_prepared = false;\n\n    void prepare_root(){\n        if(is_root_prepared)\
    \ return;\n        is_root_prepared = true;\n        root[1] = num(1, 0);\n  \
    \      for (int i = 1; i < max_base; ++i) {\n            num x(2*PI / (1LL <<\
    \ (i+1)));\n            for (ll j = (1LL << (i-1)); j < (1LL << (i)); ++j) {\n\
    \                root[2*j] = root[j];\n                root[2*j+1] = root[j]*x;\n\
    \            }\n        }\n    }\n\n    int base, N;\n    int lastN = -1;\n\n\
    \    void prepare_rev(){\n        if(lastN == N) return;\n        lastN = N;\n\
    \        for (int i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) <<\
    \ (base - 1));\n    }\n\n    void fft(num *a, num *f){\n        for (int i = 0;\
    \ i < N; ++i) f[i] = a[rev[i]];\n        for (int k = 1; k < N; k <<= 1) {\n \
    \           for (int i = 0; i < N; i += 2*k) {\n                for (int j = 0;\
    \ j < k; ++j) {\n                    num z = f[i+j+k]* root[j+k];\n          \
    \          f[i+j+k] = f[i+j] - z;\n                    f[i+j] = f[i+j] + z;\n\
    \                }\n            }\n        }\n    }\n    num a[maxN], b[maxN],\
    \ c[maxN], f1[maxN], f2[maxN], f3[maxN];\n    ll A[maxN], B[maxN], C[maxN];\n\
    \    constexpr ll mask1 = (1LL << 11)-1, mask2 = (1LL << 22)-(1LL << 11), mask3\
    \ = (1LL << 33) - (1LL << 22);\n    void multi_mod(){\n        for (int i = 0;\
    \ i < N; ++i) {\n            a[i] = num( A[i] & mask1,  (A[i] & mask2) >> 11);\n\
    \        }\n        for (int i = 0; i < N; ++i) {\n            b[i] = num( B[i]\
    \ & mask1,  (B[i] & mask2) >> 11);\n        }\n        for (int i = 0; i < N;\
    \ ++i) {\n            c[i] = num((A[i] & mask3) >> 22, (B[i] & mask3) >> 22);\n\
    \        }\n        fft(a, f1);\n        fft(b, f2);\n        fft(c, f3);\n  \
    \      for (int i = 0; i < N; ++i) {\n            int j = (N-i)&(N-1);\n     \
    \       num a1 = (f1[i] + conj(f1[j])) * num(0.5, 0);\n            num a2 = (f1[i]\
    \ - conj(f1[j])) * num(0, -0.5);\n            num a3 = (f3[i] + conj(f3[j])) *\
    \ num(0.5, 0);\n            num b1 = (f2[i] + conj(f2[j])) * num(0.5/N, 0);\n\
    \            num b2 = (f2[i] - conj(f2[j])) * num(0, -0.5/N);\n            num\
    \ b3 = (f3[i] - conj(f3[j])) * num(0, -0.5/N);\n            a[j] = a1*b1 + (a1*b2\
    \ + a2*b1) * num(0, 1);\n            b[j] = (a1*b3 + a2*b2 + a3*b1) + (a2*b3 +\
    \ a3*b2) * num(0, 1);\n            c[j] = a3*b3;\n        }\n        fft(a, f1);\n\
    \        fft(b, f2);\n        fft(c, f3);\n        for (int i = 0; i < N; ++i)\
    \ {\n            ll k1 = f1[i].x + 0.5;\n            ll k2 = f1[i].y + 0.5;\n\
    \            ll k3 = f2[i].x + 0.5;\n            ll k4 = f2[i].y + 0.5;\n    \
    \        ll k5 = f3[i].x + 0.5;\n            C[i] = (k1 + ((k2 + ((k3 + ((k4 +\
    \ (k5 << 11) % MOD) << 11) % MOD) << 11) % MOD) << 11)) % MOD;\n        }\n  \
    \  }\n\n    void prepare_AB(int n1, int n2){\n        base = 1;\n        N = 2;\n\
    \        while(N < n1+n2) base++, N <<= 1;\n        for (int i = n1; i < N; ++i)\
    \ A[i] = 0;\n        for (int i = n2; i < N; ++i) B[i] = 0;\n        prepare_root();\n\
    \        prepare_rev();\n    }\n\n    void multi_mod(int n1, int n2){\n      \
    \  prepare_AB(n1, n2);\n        multi_mod();\n    }\n}\n\nstruct poly {\n    vector<mint>\
    \ v;\n    poly() = default;\n    explicit poly(int n) : v(n) {};\n    explicit\
    \ poly(vector<mint> vv) : v(std::move(vv)) {};\n    int size() const {return (int)v.size();\
    \ }\n    poly cut(int len){\n        if(len < v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly& operator-=(const poly &a) {\n       \
    \ this->v.resize(max(size(), a.size()));\n        for (int i = 0; i < a.size();\
    \ ++i) this->v[i] -= a.v[i];\n        return *this;\n    }\n\n    poly& operator*=(poly\
    \ a) {\n        for (int i = 0; i < size(); ++i) FFT::A[i] = this->v[i].val;\n\
    \        for (int i = 0; i < a.size(); ++i) FFT::B[i] = a.v[i].val;\n        FFT::multi_mod(size(),\
    \ a.size());\n        this->v.resize(size() + a.size()-1);\n        for (int i\
    \ = 0; i < size(); ++i) this->v[i] = FFT::C[i];\n        return *this;\n    }\n\
    \    poly& operator/=(const poly &a){ return (*this *= a.inv()); }\n    poly operator+(const\
    \ poly &a) const { return poly(*this) += a; }\n    poly operator-(const poly &a)\
    \ const { return poly(*this) -= a; }\n    poly operator*(const poly &a) const\
    \ { return poly(*this) *= a; }\n\n    poly inv() const {\n        int n = size();\n\
    \        poly r(1);\n        r[0] = (this->v[0]).inv();\n        int k = 1;\n\
    \        while(k < n){\n            k *= 2;\n            poly ff(k);\n       \
    \     for (int i = 0; i < min(k, n); ++i) {\n                ff[i] = this->v[i];\n\
    \            }\n            poly nr = (r*r*ff).cut(k);\n            for (int i\
    \ = 0; i < k/2; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n         \
    \       nr[i+k/2] = -nr[i+k/2];\n            }\n            r = nr;\n        }\n\
    \        r.v.resize(n);\n        return r;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/fft3.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/fft3.cpp
layout: document
redirect_from:
- /library/math/fft3.cpp
- /library/math/fft3.cpp.html
title: math/fft3.cpp
---
