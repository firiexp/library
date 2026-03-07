---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/linear_recurrence.cpp
    title: linear recurrence
  - icon: ':heavy_check_mark:'
    path: fps/nth_term.cpp
    title: fps/nth_term.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0452.test.cpp
    title: test/aoj0452.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_convolution.test.cpp
    title: test/yosupo_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_exp_of_formal_power_series.test.cpp
    title: test/yosupo_exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_log_of_formal_power_series.test.cpp
    title: test/yosupo_log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_pow_of_formal_power_series.test.cpp
    title: test/yosupo_pow_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sqrt_of_formal_power_series.test.cpp
    title: test/yosupo_sqrt_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/ntt.cpp\"\n#include <cassert>\n\nconstexpr int ntt_mod\
    \ = 998244353, ntt_root = 3;\n#ifndef NTT_NAIVE_MUL_THRESHOLD\n#define NTT_NAIVE_MUL_THRESHOLD\
    \ 3072\n#endif\n#ifndef NTT_NAIVE_MUL_MIN_DIM\n#define NTT_NAIVE_MUL_MIN_DIM 48\n\
    #endif\n// 1012924417 -> 5, 924844033 -> 5\n// 998244353  -> 3, 897581057 -> 3\n\
    // 645922817  -> 3;\ntemplate <uint M>\nstruct modint {\n    uint val;\npublic:\n\
    \    static modint raw(int v) { modint x; x.val = v; return x; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val\
    \ -= M; return *this; }\n    modint& operator-=(const modint& rhs) { val -= rhs.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ rhs) { ull z = val; z *= rhs.val; val = (uint)(z % M); return *this; }\n   \
    \ modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }\n    friend modint\
    \ operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs;\
    \ }\n    friend modint operator*(const modint& lhs, const modint& rhs) { return\
    \ modint(lhs) *= rhs; }\n    friend modint operator/(const modint& lhs, const\
    \ modint& rhs) { return modint(lhs) /= rhs; }\n    friend bool operator==(const\
    \ modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }\n    friend bool\
    \ operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val;\
    \ }\n};\nusing mint = modint<998244353>;\n\nclass NTT {\n    static constexpr\
    \ int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2\n    mint sum_e[30],\
    \ sum_ie[30];\npublic:\n    mint es[30], ies[30];\n    NTT() {\n        int cnt2\
    \ = __builtin_ctz(ntt_mod-1);\n        mint e = mint(ntt_root).pow((ntt_mod-1)\
    \ >> cnt2), ie = e.inv();\n        for (int i = cnt2; i >= 0; i--){\n        \
    \    es[i] = e; ies[i] = ie;\n            e *= e; ie *= ie;\n        }\n     \
    \   mint now = 1, nowi = 1;\n        for (int i = 0; i < cnt2 - 2; i++) {\n  \
    \          sum_e[i] = es[i+2] * now; now *= ies[i+2];\n            sum_ie[i] =\
    \ ies[i+2] * nowi; nowi *= es[i+2];\n        }\n    }\n\n    void transform(vector<mint>\
    \ &a, int sign){\n        const int n = a.size();\n        int h = 0;\n      \
    \  while ((1U << h) < (unsigned int)(n)) h++;\n        if(!sign){ // fft\n   \
    \         for (int ph = 1; ph <= h; ph++) {\n                int w = 1 << (ph-1),\
    \ p = 1 << (h-ph);\n                mint now = 1;\n                for (int s\
    \ = 0; s < w; s++) {\n                    int offset = s << (h-ph+1);\n      \
    \              for (int i = 0; i < p; i++) {\n                        auto l =\
    \ a[i+offset], r = a[i+offset+p]*now;\n                        a[i+offset] = l+r,\
    \ a[i+offset+p] = l-r;\n                    }\n                    now *= sum_e[__builtin_ctz(~(unsigned\
    \ int)(s))];\n                }\n            }\n        }else { // ifft\n    \
    \        for (int ph = h; ph >= 1; ph--) {\n                int w = 1 << (ph-1),\
    \ p = 1 << (h-ph);\n                mint inow = 1;\n                for (int s\
    \ = 0; s < w; s++) {\n                    int offset = s << (h-ph+1);\n      \
    \              for (int i = 0; i < p; i++) {\n                        auto l =\
    \ a[i+offset], r = a[i+offset+p];\n                        a[i+offset] = l+r,\
    \ a[i+offset+p] = (l-r)*inow;\n                    }\n                    inow\
    \ *= sum_ie[__builtin_ctz(~(unsigned int)(s))];\n                }\n         \
    \   }\n        }\n    }\n};\n\nNTT ntt;\n\nbool mod_sqrt(mint a, mint &x) {\n\
    \    if (a == mint(0)) {\n        x = mint(0);\n        return true;\n    }\n\
    \    if (a.pow((ntt_mod - 1) >> 1) != mint(1)) return false;\n    if (ntt_mod\
    \ % 4 == 3) {\n        x = a.pow((ntt_mod + 1) >> 2);\n        return true;\n\
    \    }\n    int s = 0;\n    int q = ntt_mod - 1;\n    while ((q & 1) == 0) {\n\
    \        ++s;\n        q >>= 1;\n    }\n    mint z = 2;\n    while (z.pow((ntt_mod\
    \ - 1) >> 1) == mint(1)) ++z;\n    mint c = z.pow(q);\n    mint t = a.pow(q);\n\
    \    mint r = a.pow((q + 1) >> 1);\n    int m = s;\n    while (t != mint(1)) {\n\
    \        int i = 1;\n        mint tt = t * t;\n        while (i < m && tt != mint(1))\
    \ {\n            tt *= tt;\n            ++i;\n        }\n        mint b = c.pow(1LL\
    \ << (m - i - 1));\n        r *= b;\n        c = b * b;\n        t *= c;\n   \
    \     m = i;\n    }\n    x = r;\n    return true;\n}\n\nstruct poly {\n    vector<mint>\
    \ v;\n    poly() = default;\n    explicit poly(int n) : v(n) {};\n    explicit\
    \ poly(vector<mint> vv) : v(std::move(vv)) {};\n    int size() const {return (int)v.size();\
    \ }\n    poly cut(int len){\n        if(len < v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly &operator+=(const mint &r) {\n       \
    \ if (v.empty()) v.resize(1);\n        v[0] += r;\n        return *this;\n   \
    \ }\n    poly& operator-=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];\n\
    \        return *this;\n    }\n    poly& operator*=(const poly &a) {\n       \
    \ const int n = size();\n        const int m = a.size();\n        if (n == 0 ||\
    \ m == 0) {\n            v.clear();\n            return *this;\n        }\n  \
    \      if (1LL * n * m <= NTT_NAIVE_MUL_THRESHOLD && min(n, m) <= NTT_NAIVE_MUL_MIN_DIM)\
    \ {\n            vector<mint> res(n + m - 1);\n            for (int i = 0; i <\
    \ n; ++i) {\n                for (int j = 0; j < m; ++j) {\n                 \
    \   res[i + j] += v[i] * a.v[j];\n                }\n            }\n         \
    \   v = std::move(res);\n            return *this;\n        }\n        int N =\
    \ n + m - 1;\n        int sz = 1;\n        while(sz < N) sz <<= 1;\n        this->v.resize(sz);\n\
    \        ntt.transform(this->v, 0);\n        if (this == &a) {\n            for\
    \ (int i = 0; i < sz; ++i) this->v[i] *= this->v[i];\n        } else {\n     \
    \       vector<mint> b = a.v;\n            b.resize(sz);\n            ntt.transform(b,\
    \ 0);\n            for(int i = 0; i < sz; ++i) this->v[i] *= b[i];\n        }\n\
    \        ntt.transform(this->v, 1);\n        this->v.resize(N);\n        static\
    \ vector<mint> inv_pow2 = []() {\n            vector<mint> t(31, mint(1));\n \
    \           mint inv2 = mint(2).inv();\n            for (int i = 1; i < (int)t.size();\
    \ ++i) t[i] = t[i - 1] * inv2;\n            return t;\n        }();\n        mint\
    \ iz = inv_pow2[__builtin_ctz((unsigned)sz)];\n        for (int i = 0; i < N;\
    \ i++) this->v[i] *= iz;\n        return *this;\n    }\n    poly& operator/=(const\
    \ poly &a){ return (*this *= a.inv()); }\n    poly operator+(const poly &a) const\
    \ { return poly(*this) += a; }\n    poly operator+(const mint &v) const { return\
    \ poly(*this) += v; }\n    poly operator-(const poly &a) const { return poly(*this)\
    \ -= a; }\n    poly operator*(const poly &a) const { return poly(*this) *= a;\
    \ }\n\n    poly pre(int sz) const {\n        poly ret(sz);\n        for (int i\
    \ = 0; i < min<int>(sz, v.size()); ++i) {\n            ret[i] = v[i];\n      \
    \  }\n        return ret;\n    }\n\n    poly diff() const {\n        const int\
    \ n = (int)this->size();\n        poly ret(max(0, n - 1));\n        mint one(1),\
    \ coeff(1);\n        for (int i = 1; i < n; i++) {\n            ret[i - 1] = v[i]\
    \ * coeff;\n            coeff += one;\n        }\n        return ret;\n    }\n\
    \n    poly integral() const {\n        const int n = (int)this->size();\n    \
    \    poly ret(n + 1);\n        ret[0] = mint(0);\n        static vector<mint>\
    \ invs = {mint(0), mint(1)};\n        if ((int)invs.size() <= n) {\n         \
    \   int old = (int)invs.size();\n            invs.resize(n + 1);\n           \
    \ for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod - ntt_mod / i) * invs[ntt_mod\
    \ % i];\n        }\n        for (int i = 0; i < n; i++) ret[i + 1] = v[i] * invs[i\
    \ + 1];\n        return ret;\n    }\n\n    poly inv(int deg = -1) const {\n  \
    \      int n = size();\n        if(deg == -1) deg = v.size();\n        poly r(1);\n\
    \        r[0] = (this->v[0]).inv();\n        for (int k = 1; k < deg; k <<= 1)\
    \ {\n            poly ff(2*k);\n            for (int i = 0; i < min(k*2, n); ++i)\
    \ ff[i] = this->v[i];\n            poly nr = (r*r*ff).cut(k*2);\n            for\
    \ (int i = 0; i < k; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n    \
    \            nr[i+k] = -nr[i+k];\n            }\n            r = nr;\n       \
    \ }\n        return r.pre(deg);\n    }\n\n    poly log(int deg = -1) const {\n\
    \        assert(!v.empty() && v[0] == mint(1));\n        if (deg == -1) deg =\
    \ (int)this->size();\n        return (this->diff() * this->inv(deg)).pre(deg -\
    \ 1).integral();\n    }\n\n    poly exp(int deg = -1) const {\n        assert(v.size()\
    \ == 0 || v[0] == mint(0));\n        if (deg == -1) deg = v.size();\n        poly\
    \ ret(1); ret[0] = 1;\n        for (int i = 1; i < deg; i <<= 1) {\n         \
    \   ret = (ret * (pre(i << 1) + mint(1) - ret.log(i << 1))).pre(i << 1);\n   \
    \     }\n        return ret.pre(deg);\n    }\n\n    poly pow(long long k, int\
    \ deg = -1) const {\n        if (deg == -1) deg = size();\n        poly ret(max(0,\
    \ deg));\n        if (deg <= 0) return ret;\n        if (k == 0) {\n         \
    \   ret[0] = 1;\n            return ret;\n        }\n        if (0 < k && k <=\
    \ 64) {\n            poly base = pre(deg);\n            poly ans(1);\n       \
    \     ans[0] = 1;\n            long long e = k;\n            while (e > 0) {\n\
    \                if (e & 1) {\n                    ans *= base;\n            \
    \        ans = ans.pre(deg);\n                }\n                e >>= 1;\n  \
    \              if (e == 0) break;\n                base *= base;\n           \
    \     base = base.pre(deg);\n            }\n            ans = ans.pre(deg);\n\
    \            if (ans.size() < deg) ans.v.resize(deg);\n            return ans;\n\
    \        }\n        int lead = 0;\n        while (lead < size() && v[lead] ==\
    \ mint(0)) lead++;\n        if (lead == size()) return ret;\n        long long\
    \ shift_ll = 0;\n        if (lead > 0) {\n            if (k > (deg - 1) / lead)\
    \ return ret;\n            shift_ll = 1LL * lead * k;\n        }\n        poly\
    \ f(size() - lead);\n        mint inv_lead = v[lead].inv();\n        for (int\
    \ i = lead; i < size(); ++i) f[i - lead] = v[i] * inv_lead;\n        int shift\
    \ = static_cast<int>(shift_ll);\n        int rem_deg = deg - shift;\n        poly\
    \ g = f.log(rem_deg);\n        mint k_mint = mint(k);\n        for (int i = 0;\
    \ i < g.size(); ++i) g[i] *= k_mint;\n        g = g.exp(rem_deg);\n        mint\
    \ coeff = v[lead].pow(k);\n        for (int i = 0; i < g.size(); ++i) g[i] *=\
    \ coeff;\n        for (int i = 0; i < g.size(); ++i) ret[i + shift] = g[i];\n\
    \        return ret;\n    }\n\n    poly sqrt(int deg = -1) const {\n        if\
    \ (deg == -1) deg = size();\n        poly ret(max(0, deg));\n        if (deg <=\
    \ 0) return ret;\n        int lead = 0;\n        while (lead < size() && v[lead]\
    \ == mint(0)) lead++;\n        if (lead == size()) return ret;\n        if (lead\
    \ & 1) return poly();\n        mint sq0;\n        if (!mod_sqrt(v[lead], sq0))\
    \ return poly();\n        int shift = lead >> 1;\n        if (shift >= deg) return\
    \ ret;\n        int rem_deg = deg - shift;\n        poly f(size() - lead);\n \
    \       mint inv_lead = v[lead].inv();\n        for (int i = lead; i < size();\
    \ ++i) f[i - lead] = v[i] * inv_lead;\n        poly s(1);\n        s[0] = 1;\n\
    \        mint inv2 = mint(2).inv();\n        for (int k = 1; k < rem_deg; k <<=\
    \ 1) {\n            poly ns = (s + (f.pre(k << 1) * s.inv(k << 1)).pre(k << 1)).pre(k\
    \ << 1);\n            for (int i = 0; i < ns.size(); ++i) ns[i] *= inv2;\n   \
    \         s = ns;\n        }\n        s = s.pre(rem_deg);\n        for (int i\
    \ = 0; i < s.size(); ++i) ret[i + shift] = s[i] * sq0;\n        return ret;\n\
    \    }\n};\n"
  code: "#include <cassert>\n\nconstexpr int ntt_mod = 998244353, ntt_root = 3;\n\
    #ifndef NTT_NAIVE_MUL_THRESHOLD\n#define NTT_NAIVE_MUL_THRESHOLD 3072\n#endif\n\
    #ifndef NTT_NAIVE_MUL_MIN_DIM\n#define NTT_NAIVE_MUL_MIN_DIM 48\n#endif\n// 1012924417\
    \ -> 5, 924844033 -> 5\n// 998244353  -> 3, 897581057 -> 3\n// 645922817  -> 3;\n\
    template <uint M>\nstruct modint {\n    uint val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M);\
    \ }\n    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n\
    \    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n  \
    \  modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val\
    \ -= M; return *this; }\n    modint& operator-=(const modint& rhs) { val -= rhs.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ rhs) { ull z = val; z *= rhs.val; val = (uint)(z % M); return *this; }\n   \
    \ modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }\n    friend modint\
    \ operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs;\
    \ }\n    friend modint operator*(const modint& lhs, const modint& rhs) { return\
    \ modint(lhs) *= rhs; }\n    friend modint operator/(const modint& lhs, const\
    \ modint& rhs) { return modint(lhs) /= rhs; }\n    friend bool operator==(const\
    \ modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }\n    friend bool\
    \ operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val;\
    \ }\n};\nusing mint = modint<998244353>;\n\nclass NTT {\n    static constexpr\
    \ int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2\n    mint sum_e[30],\
    \ sum_ie[30];\npublic:\n    mint es[30], ies[30];\n    NTT() {\n        int cnt2\
    \ = __builtin_ctz(ntt_mod-1);\n        mint e = mint(ntt_root).pow((ntt_mod-1)\
    \ >> cnt2), ie = e.inv();\n        for (int i = cnt2; i >= 0; i--){\n        \
    \    es[i] = e; ies[i] = ie;\n            e *= e; ie *= ie;\n        }\n     \
    \   mint now = 1, nowi = 1;\n        for (int i = 0; i < cnt2 - 2; i++) {\n  \
    \          sum_e[i] = es[i+2] * now; now *= ies[i+2];\n            sum_ie[i] =\
    \ ies[i+2] * nowi; nowi *= es[i+2];\n        }\n    }\n\n    void transform(vector<mint>\
    \ &a, int sign){\n        const int n = a.size();\n        int h = 0;\n      \
    \  while ((1U << h) < (unsigned int)(n)) h++;\n        if(!sign){ // fft\n   \
    \         for (int ph = 1; ph <= h; ph++) {\n                int w = 1 << (ph-1),\
    \ p = 1 << (h-ph);\n                mint now = 1;\n                for (int s\
    \ = 0; s < w; s++) {\n                    int offset = s << (h-ph+1);\n      \
    \              for (int i = 0; i < p; i++) {\n                        auto l =\
    \ a[i+offset], r = a[i+offset+p]*now;\n                        a[i+offset] = l+r,\
    \ a[i+offset+p] = l-r;\n                    }\n                    now *= sum_e[__builtin_ctz(~(unsigned\
    \ int)(s))];\n                }\n            }\n        }else { // ifft\n    \
    \        for (int ph = h; ph >= 1; ph--) {\n                int w = 1 << (ph-1),\
    \ p = 1 << (h-ph);\n                mint inow = 1;\n                for (int s\
    \ = 0; s < w; s++) {\n                    int offset = s << (h-ph+1);\n      \
    \              for (int i = 0; i < p; i++) {\n                        auto l =\
    \ a[i+offset], r = a[i+offset+p];\n                        a[i+offset] = l+r,\
    \ a[i+offset+p] = (l-r)*inow;\n                    }\n                    inow\
    \ *= sum_ie[__builtin_ctz(~(unsigned int)(s))];\n                }\n         \
    \   }\n        }\n    }\n};\n\nNTT ntt;\n\nbool mod_sqrt(mint a, mint &x) {\n\
    \    if (a == mint(0)) {\n        x = mint(0);\n        return true;\n    }\n\
    \    if (a.pow((ntt_mod - 1) >> 1) != mint(1)) return false;\n    if (ntt_mod\
    \ % 4 == 3) {\n        x = a.pow((ntt_mod + 1) >> 2);\n        return true;\n\
    \    }\n    int s = 0;\n    int q = ntt_mod - 1;\n    while ((q & 1) == 0) {\n\
    \        ++s;\n        q >>= 1;\n    }\n    mint z = 2;\n    while (z.pow((ntt_mod\
    \ - 1) >> 1) == mint(1)) ++z;\n    mint c = z.pow(q);\n    mint t = a.pow(q);\n\
    \    mint r = a.pow((q + 1) >> 1);\n    int m = s;\n    while (t != mint(1)) {\n\
    \        int i = 1;\n        mint tt = t * t;\n        while (i < m && tt != mint(1))\
    \ {\n            tt *= tt;\n            ++i;\n        }\n        mint b = c.pow(1LL\
    \ << (m - i - 1));\n        r *= b;\n        c = b * b;\n        t *= c;\n   \
    \     m = i;\n    }\n    x = r;\n    return true;\n}\n\nstruct poly {\n    vector<mint>\
    \ v;\n    poly() = default;\n    explicit poly(int n) : v(n) {};\n    explicit\
    \ poly(vector<mint> vv) : v(std::move(vv)) {};\n    int size() const {return (int)v.size();\
    \ }\n    poly cut(int len){\n        if(len < v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly &operator+=(const mint &r) {\n       \
    \ if (v.empty()) v.resize(1);\n        v[0] += r;\n        return *this;\n   \
    \ }\n    poly& operator-=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];\n\
    \        return *this;\n    }\n    poly& operator*=(const poly &a) {\n       \
    \ const int n = size();\n        const int m = a.size();\n        if (n == 0 ||\
    \ m == 0) {\n            v.clear();\n            return *this;\n        }\n  \
    \      if (1LL * n * m <= NTT_NAIVE_MUL_THRESHOLD && min(n, m) <= NTT_NAIVE_MUL_MIN_DIM)\
    \ {\n            vector<mint> res(n + m - 1);\n            for (int i = 0; i <\
    \ n; ++i) {\n                for (int j = 0; j < m; ++j) {\n                 \
    \   res[i + j] += v[i] * a.v[j];\n                }\n            }\n         \
    \   v = std::move(res);\n            return *this;\n        }\n        int N =\
    \ n + m - 1;\n        int sz = 1;\n        while(sz < N) sz <<= 1;\n        this->v.resize(sz);\n\
    \        ntt.transform(this->v, 0);\n        if (this == &a) {\n            for\
    \ (int i = 0; i < sz; ++i) this->v[i] *= this->v[i];\n        } else {\n     \
    \       vector<mint> b = a.v;\n            b.resize(sz);\n            ntt.transform(b,\
    \ 0);\n            for(int i = 0; i < sz; ++i) this->v[i] *= b[i];\n        }\n\
    \        ntt.transform(this->v, 1);\n        this->v.resize(N);\n        static\
    \ vector<mint> inv_pow2 = []() {\n            vector<mint> t(31, mint(1));\n \
    \           mint inv2 = mint(2).inv();\n            for (int i = 1; i < (int)t.size();\
    \ ++i) t[i] = t[i - 1] * inv2;\n            return t;\n        }();\n        mint\
    \ iz = inv_pow2[__builtin_ctz((unsigned)sz)];\n        for (int i = 0; i < N;\
    \ i++) this->v[i] *= iz;\n        return *this;\n    }\n    poly& operator/=(const\
    \ poly &a){ return (*this *= a.inv()); }\n    poly operator+(const poly &a) const\
    \ { return poly(*this) += a; }\n    poly operator+(const mint &v) const { return\
    \ poly(*this) += v; }\n    poly operator-(const poly &a) const { return poly(*this)\
    \ -= a; }\n    poly operator*(const poly &a) const { return poly(*this) *= a;\
    \ }\n\n    poly pre(int sz) const {\n        poly ret(sz);\n        for (int i\
    \ = 0; i < min<int>(sz, v.size()); ++i) {\n            ret[i] = v[i];\n      \
    \  }\n        return ret;\n    }\n\n    poly diff() const {\n        const int\
    \ n = (int)this->size();\n        poly ret(max(0, n - 1));\n        mint one(1),\
    \ coeff(1);\n        for (int i = 1; i < n; i++) {\n            ret[i - 1] = v[i]\
    \ * coeff;\n            coeff += one;\n        }\n        return ret;\n    }\n\
    \n    poly integral() const {\n        const int n = (int)this->size();\n    \
    \    poly ret(n + 1);\n        ret[0] = mint(0);\n        static vector<mint>\
    \ invs = {mint(0), mint(1)};\n        if ((int)invs.size() <= n) {\n         \
    \   int old = (int)invs.size();\n            invs.resize(n + 1);\n           \
    \ for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod - ntt_mod / i) * invs[ntt_mod\
    \ % i];\n        }\n        for (int i = 0; i < n; i++) ret[i + 1] = v[i] * invs[i\
    \ + 1];\n        return ret;\n    }\n\n    poly inv(int deg = -1) const {\n  \
    \      int n = size();\n        if(deg == -1) deg = v.size();\n        poly r(1);\n\
    \        r[0] = (this->v[0]).inv();\n        for (int k = 1; k < deg; k <<= 1)\
    \ {\n            poly ff(2*k);\n            for (int i = 0; i < min(k*2, n); ++i)\
    \ ff[i] = this->v[i];\n            poly nr = (r*r*ff).cut(k*2);\n            for\
    \ (int i = 0; i < k; ++i) {\n                nr[i] = (r[i]+r[i]-nr[i]);\n    \
    \            nr[i+k] = -nr[i+k];\n            }\n            r = nr;\n       \
    \ }\n        return r.pre(deg);\n    }\n\n    poly log(int deg = -1) const {\n\
    \        assert(!v.empty() && v[0] == mint(1));\n        if (deg == -1) deg =\
    \ (int)this->size();\n        return (this->diff() * this->inv(deg)).pre(deg -\
    \ 1).integral();\n    }\n\n    poly exp(int deg = -1) const {\n        assert(v.size()\
    \ == 0 || v[0] == mint(0));\n        if (deg == -1) deg = v.size();\n        poly\
    \ ret(1); ret[0] = 1;\n        for (int i = 1; i < deg; i <<= 1) {\n         \
    \   ret = (ret * (pre(i << 1) + mint(1) - ret.log(i << 1))).pre(i << 1);\n   \
    \     }\n        return ret.pre(deg);\n    }\n\n    poly pow(long long k, int\
    \ deg = -1) const {\n        if (deg == -1) deg = size();\n        poly ret(max(0,\
    \ deg));\n        if (deg <= 0) return ret;\n        if (k == 0) {\n         \
    \   ret[0] = 1;\n            return ret;\n        }\n        if (0 < k && k <=\
    \ 64) {\n            poly base = pre(deg);\n            poly ans(1);\n       \
    \     ans[0] = 1;\n            long long e = k;\n            while (e > 0) {\n\
    \                if (e & 1) {\n                    ans *= base;\n            \
    \        ans = ans.pre(deg);\n                }\n                e >>= 1;\n  \
    \              if (e == 0) break;\n                base *= base;\n           \
    \     base = base.pre(deg);\n            }\n            ans = ans.pre(deg);\n\
    \            if (ans.size() < deg) ans.v.resize(deg);\n            return ans;\n\
    \        }\n        int lead = 0;\n        while (lead < size() && v[lead] ==\
    \ mint(0)) lead++;\n        if (lead == size()) return ret;\n        long long\
    \ shift_ll = 0;\n        if (lead > 0) {\n            if (k > (deg - 1) / lead)\
    \ return ret;\n            shift_ll = 1LL * lead * k;\n        }\n        poly\
    \ f(size() - lead);\n        mint inv_lead = v[lead].inv();\n        for (int\
    \ i = lead; i < size(); ++i) f[i - lead] = v[i] * inv_lead;\n        int shift\
    \ = static_cast<int>(shift_ll);\n        int rem_deg = deg - shift;\n        poly\
    \ g = f.log(rem_deg);\n        mint k_mint = mint(k);\n        for (int i = 0;\
    \ i < g.size(); ++i) g[i] *= k_mint;\n        g = g.exp(rem_deg);\n        mint\
    \ coeff = v[lead].pow(k);\n        for (int i = 0; i < g.size(); ++i) g[i] *=\
    \ coeff;\n        for (int i = 0; i < g.size(); ++i) ret[i + shift] = g[i];\n\
    \        return ret;\n    }\n\n    poly sqrt(int deg = -1) const {\n        if\
    \ (deg == -1) deg = size();\n        poly ret(max(0, deg));\n        if (deg <=\
    \ 0) return ret;\n        int lead = 0;\n        while (lead < size() && v[lead]\
    \ == mint(0)) lead++;\n        if (lead == size()) return ret;\n        if (lead\
    \ & 1) return poly();\n        mint sq0;\n        if (!mod_sqrt(v[lead], sq0))\
    \ return poly();\n        int shift = lead >> 1;\n        if (shift >= deg) return\
    \ ret;\n        int rem_deg = deg - shift;\n        poly f(size() - lead);\n \
    \       mint inv_lead = v[lead].inv();\n        for (int i = lead; i < size();\
    \ ++i) f[i - lead] = v[i] * inv_lead;\n        poly s(1);\n        s[0] = 1;\n\
    \        mint inv2 = mint(2).inv();\n        for (int k = 1; k < rem_deg; k <<=\
    \ 1) {\n            poly ns = (s + (f.pre(k << 1) * s.inv(k << 1)).pre(k << 1)).pre(k\
    \ << 1);\n            for (int i = 0; i < ns.size(); ++i) ns[i] *= inv2;\n   \
    \         s = ns;\n        }\n        s = s.pre(rem_deg);\n        for (int i\
    \ = 0; i < s.size(); ++i) ret[i + shift] = s[i] * sq0;\n        return ret;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/ntt.cpp
  requiredBy:
  - fps/linear_recurrence.cpp
  - fps/nth_term.cpp
  timestamp: '2026-03-08 00:47:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_log_of_formal_power_series.test.cpp
  - test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
  - test/yosupo_exp_of_formal_power_series.test.cpp
  - test/yosupo_sqrt_of_formal_power_series.test.cpp
  - test/yosupo_pow_of_formal_power_series.test.cpp
  - test/aoj0452.test.cpp
  - test/yosupo_convolution.test.cpp
documentation_of: math/ntt.cpp
layout: document
redirect_from:
- /library/math/ntt.cpp
- /library/math/ntt.cpp.html
title: math/ntt.cpp
---
