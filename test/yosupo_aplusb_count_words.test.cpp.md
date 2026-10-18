---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/ahocorasick.cpp
    title: "Aho-Corasick\u6CD5"
  - icon: ':heavy_check_mark:'
    path: fps/linear_recurrence.cpp
    title: "\u7DDA\u5F62\u6F38\u5316\u5F0F(Linear Recurrence)"
  - icon: ':heavy_check_mark:'
    path: fps/nth_term.cpp
    title: "\u6709\u7406\u578B\u6BCD\u95A2\u6570\u306EN\u9805\u76EE"
  - icon: ':heavy_check_mark:'
    path: math/berlekamp_massey.cpp
    title: "Berlekamp-Massey\u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/digit_dfa.cpp
    title: "\u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\u3059\u6709\u9650\u30AA\
      \u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: math/ntt.cpp
    title: "NTT\u30FB\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570(NTT/FPS)"
  - icon: ':heavy_check_mark:'
    path: string/avoid_patterns.cpp
    title: "\u7981\u6B62\u90E8\u5206\u6587\u5B57\u5217\u3092\u907F\u3051\u308B\u6709\
      \u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: string/count_words.cpp
    title: "\u6709\u9650\u72B6\u614BDP\u306E\u9577\u3055N\u306E\u6587\u5B57\u5217\u6570"
  - icon: ':heavy_check_mark:'
    path: string/dfa.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\
      \u5408\u6210"
  - icon: ':heavy_check_mark:'
    path: string/dfa.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\
      \u5408\u6210"
  - icon: ':heavy_check_mark:'
    path: string/dfa_minimize.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\u6700\u5C0F\u5316"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':heavy_check_mark:'
    path: util/modint_base.cpp
    title: util/modint_base.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_count_words.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull = unsigned\
    \ long long;\n\n#line 1 \"string/count_words.cpp\"\n\n\n\n#line 1 \"string/dfa.cpp\"\
    \n\n\n\ntemplate<int W>\nstruct DFA {\n    vector<array<int, W>> next;\n    vector<char>\
    \ accept;\n    int initial = -1;\n};\n\ntemplate<int W>\nDFA<W> intersect(const\
    \ DFA<W>& a, const DFA<W>& b) {\n    if (a.initial == -1 || b.initial == -1) return\
    \ {};\n    size_t width = b.next.size();\n    assert(a.next.size() <= vector<int>().max_size()\
    \ / width);\n    vector<int> id(a.next.size() * width, -1);\n    vector<pair<int,\
    \ int>> states;\n    DFA<W> result;\n    auto add = [&](int x, int y) {\n    \
    \    int& index = id[size_t(x) * width + y];\n        if (index == -1) {\n   \
    \         index = (int)states.size();\n            states.emplace_back(x, y);\n\
    \            result.next.emplace_back();\n            result.accept.push_back(a.accept[x]\
    \ && b.accept[y]);\n        }\n        return index;\n    };\n    result.initial\
    \ = add(a.initial, b.initial);\n    for (int i = 0; i < (int)states.size(); ++i)\
    \ {\n        auto [x, y] = states[i];\n        for (int c = 0; c < W; ++c) {\n\
    \            int nx = a.next[x][c], ny = b.next[y][c];\n            int to = nx\
    \ == -1 || ny == -1 ? -1 : add(nx, ny);\n            result.next[i][c] = to;\n\
    \        }\n    }\n    return result;\n}\n\ntemplate<int W>\nDFA<W> unite(const\
    \ DFA<W>& a, const DFA<W>& b) {\n    if (a.initial == -1 && b.initial == -1) return\
    \ {};\n    size_t width = b.next.size() + 1;\n    assert(a.next.size() + 1 <=\
    \ vector<int>().max_size() / width);\n    vector<int> id((a.next.size() + 1) *\
    \ width, -1);\n    vector<pair<int, int>> states;\n    DFA<W> result;\n    auto\
    \ add = [&](int x, int y) {\n        if (x == -1 && y == -1) return -1;\n    \
    \    int& index = id[size_t(x + 1) * width + (y + 1)];\n        if (index == -1)\
    \ {\n            index = (int)states.size();\n            states.emplace_back(x,\
    \ y);\n            result.next.emplace_back();\n            result.accept.push_back((x\
    \ != -1 && a.accept[x]) || (y != -1 && b.accept[y]));\n        }\n        return\
    \ index;\n    };\n    result.initial = add(a.initial, b.initial);\n    for (int\
    \ i = 0; i < (int)states.size(); ++i) {\n        auto [x, y] = states[i];\n  \
    \      for (int c = 0; c < W; ++c) {\n            int nx = x == -1 ? -1 : a.next[x][c];\n\
    \            int ny = y == -1 ? -1 : b.next[y][c];\n            int to = add(nx,\
    \ ny);\n            result.next[i][c] = to;\n        }\n    }\n    return result;\n\
    }\n\ntemplate<int W>\nDFA<W> complement(const DFA<W>& a) {\n    if (a.initial\
    \ == -1) {\n        DFA<W> result{vector<array<int, W>>(1), {true}, 0};\n    \
    \    result.next[0].fill(0);\n        return result;\n    }\n    DFA<W> result\
    \ = a;\n    for (auto& accept : result.accept) accept = !accept;\n    int sink\
    \ = (int)result.next.size();\n    bool needed = false;\n    for (auto& row : result.next)\
    \ {\n        for (int& to : row) if (to == -1) {\n            to = sink;\n   \
    \         needed = true;\n        }\n    }\n    if (needed) {\n        result.next.emplace_back();\n\
    \        result.next.back().fill(sink);\n        result.accept.push_back(true);\n\
    \    }\n    return result;\n}\n\n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\
    \u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\u6210\n */\n#line 1 \"math/ntt.cpp\"\
    \n\n\n\n#line 1 \"util/modint_base.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    static constexpr uint get_mod() { return Mod; }\n    static\
    \ constexpr uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class\
    \ T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val =\
    \ uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint\
    \ &value() noexcept { return val; }\n    const uint &value() const noexcept {\
    \ return val; }\n    modint& operator++() { val++; if (val == Mod) val = 0; return\
    \ *this; }\n    modint& operator--() { if (val == 0) val = Mod; val--; return\
    \ *this; }\n    modint operator++(int) { modint result = *this; ++*this; return\
    \ result; }\n    modint operator--(int) { modint result = *this; --*this; return\
    \ result; }\n    modint& operator+=(const modint& b) { val += b.val; if (val >=\
    \ Mod) val -= Mod; return *this; }\n    modint& operator-=(const modint& b) {\
    \ val -= b.val; if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const\
    \ modint& b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n\
    \    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(Mod - 2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 5 \"math/ntt.cpp\"\
    \n\nconstexpr int ntt_mod = 998244353, ntt_root = 3;\n#ifndef NTT_NAIVE_MUL_THRESHOLD\n\
    #define NTT_NAIVE_MUL_THRESHOLD 3072\n#endif\n#ifndef NTT_NAIVE_MUL_MIN_DIM\n\
    #define NTT_NAIVE_MUL_MIN_DIM 48\n#endif\n#ifndef NTT_NAIVE_MUL_SHORT_DIM\n#define\
    \ NTT_NAIVE_MUL_SHORT_DIM 16\n#endif\n#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\
    using mint = modint<ntt_mod>;\n#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n#else\n\
    static_assert(mint::get_mod() == ntt_mod, \"NTT requires mint with MOD = 998244353\"\
    );\n#endif\n\n// 1012924417 -> 5, 924844033 -> 5\n// 998244353  -> 3, 897581057\
    \ -> 3\n// 645922817  -> 3;\n\nclass NTT {\n    static constexpr int max_base\
    \ = 23, maxN = 1 << max_base; // 998244353 supports up to 2^23-th roots\n    mint\
    \ root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30];\npublic:\n\
    \    NTT() {\n        int cnt2 = __builtin_ctz(ntt_mod-1);\n        mint e = mint(ntt_root).pow((ntt_mod-1)\
    \ >> cnt2), ie = e.inv();\n        for (int i = cnt2; i >= 0; i--){\n        \
    \    root[i] = e;\n            iroot[i] = ie;\n            e *= e; ie *= ie;\n\
    \        }\n        mint prod = 1, iprod = 1;\n        for (int i = 0; i <= cnt2\
    \ - 2; i++) {\n            rate2[i] = root[i + 2] * prod;\n            irate2[i]\
    \ = iroot[i + 2] * iprod;\n            prod *= iroot[i + 2];\n            iprod\
    \ *= root[i + 2];\n        }\n        prod = 1, iprod = 1;\n        for (int i\
    \ = 0; i <= cnt2 - 3; i++) {\n            rate3[i] = root[i + 3] * prod;\n   \
    \         irate3[i] = iroot[i + 3] * iprod;\n            prod *= iroot[i + 3];\n\
    \            iprod *= root[i + 3];\n        }\n    }\n\n    mint root_pow2(int\
    \ k) const { return root[k]; }\n    mint iroot_pow2(int k) const { return iroot[k];\
    \ }\n\n    void transform(vector<mint> &a, int sign){\n        const int n = a.size();\n\
    \        assert(n > 0);\n        assert((n & (n - 1)) == 0);\n        assert(n\
    \ <= maxN);\n        int h = 0;\n        while ((1U << h) < (unsigned int)(n))\
    \ h++;\n        if(!sign){ // fft\n            int len = 0;\n            while\
    \ (len < h) {\n                if (h - len == 1) {\n                    int p\
    \ = 1 << (h - len - 1);\n                    mint rot = 1;\n                 \
    \   for (int s = 0; s < (1 << len); s++) {\n                        int offset\
    \ = s << (h - len);\n                        for (int i = 0; i < p; i++) {\n \
    \                           auto l = a[i + offset];\n                        \
    \    auto r = a[i + offset + p] * rot;\n                            a[i + offset]\
    \ = l + r;\n                            a[i + offset + p] = l - r;\n         \
    \               }\n                        if (s + 1 != (1 << len)) {\n      \
    \                      rot *= rate2[__builtin_ctz(~(unsigned int)(s))];\n    \
    \                    }\n                    }\n                    len++;\n  \
    \              } else {\n                    int p = 1 << (h - len - 2);\n   \
    \                 mint rot = 1, imag = root[2];\n                    for (int\
    \ s = 0; s < (1 << len); s++) {\n                        mint rot2 = rot * rot;\n\
    \                        mint rot3 = rot2 * rot;\n                        int\
    \ offset = s << (h - len);\n                        for (int i = 0; i < p; i++)\
    \ {\n                            ull mod2 = 1ULL * ntt_mod * ntt_mod;\n      \
    \                      ull a0 = a[i + offset].val;\n                         \
    \   ull a1 = 1ULL * a[i + offset + p].val * rot.val;\n                       \
    \     ull a2 = 1ULL * a[i + offset + 2 * p].val * rot2.val;\n                \
    \            ull a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;\n         \
    \                   ull a1na3imag = 1ULL * mint(a1 + mod2 - a3).val * imag.val;\n\
    \                            ull na2 = mod2 - a2;\n                          \
    \  a[i + offset] = mint(a0 + a2 + a1 + a3);\n                            a[i +\
    \ offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));\n                    \
    \        a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);\n               \
    \             a[i + offset + 3 * p] = mint(a0 + na2 + (mod2 - a1na3imag));\n \
    \                       }\n                        if (s + 1 != (1 << len)) {\n\
    \                            rot *= rate3[__builtin_ctz(~(unsigned int)(s))];\n\
    \                        }\n                    }\n                    len +=\
    \ 2;\n                }\n            }\n        }else { // ifft\n            int\
    \ len = h;\n            while (len) {\n                if (len == 1) {\n     \
    \               int p = 1 << (h - len);\n                    mint irot = 1;\n\
    \                    for (int s = 0; s < (1 << (len - 1)); s++) {\n          \
    \              int offset = s << (h - len + 1);\n                        for (int\
    \ i = 0; i < p; i++) {\n                            auto l = a[i + offset];\n\
    \                            auto r = a[i + offset + p];\n                   \
    \         a[i + offset] = l + r;\n                            a[i + offset + p]\
    \ = mint(1ULL * (ntt_mod + l.val - r.val) * irot.val);\n                     \
    \   }\n                        if (s + 1 != (1 << (len - 1))) {\n            \
    \                irot *= irate2[__builtin_ctz(~(unsigned int)(s))];\n        \
    \                }\n                    }\n                    len--;\n      \
    \          } else {\n                    int p = 1 << (h - len);\n           \
    \         mint irot = 1, iimag = iroot[2];\n                    for (int s = 0;\
    \ s < (1 << (len - 2)); s++) {\n                        mint irot2 = irot * irot;\n\
    \                        mint irot3 = irot2 * irot;\n                        int\
    \ offset = s << (h - len + 2);\n                        for (int i = 0; i < p;\
    \ i++) {\n                            ull a0 = a[i + offset].val;\n          \
    \                  ull a1 = a[i + offset + p].val;\n                         \
    \   ull a2 = a[i + offset + 2 * p].val;\n                            ull a3 =\
    \ a[i + offset + 3 * p].val;\n                            ull a2na3iimag = 1ULL\
    \ * mint(1ULL * (ntt_mod + a2 - a3) * iimag.val).val;\n                      \
    \      a[i + offset] = mint(a0 + a1 + a2 + a3);\n                            a[i\
    \ + offset + p] = mint(a0 + (ntt_mod - a1) + a2na3iimag) * irot;\n           \
    \                 a[i + offset + 2 * p] = mint(a0 + a1 + (ntt_mod - a2) + (ntt_mod\
    \ - a3)) * irot2;\n                            a[i + offset + 3 * p] = mint(a0\
    \ + (ntt_mod - a1) + (ntt_mod - a2na3iimag)) * irot3;\n                      \
    \  }\n                        if (s + 1 != (1 << (len - 2))) {\n             \
    \               irot *= irate3[__builtin_ctz(~(unsigned int)(s))];\n         \
    \               }\n                    }\n                    len -= 2;\n    \
    \            }\n            }\n        }\n    }\n};\n\nNTT ntt;\n\nvoid ntt_ifft(vector<mint>&\
    \ a) {\n    ntt.transform(a, 1);\n    static vector<mint> inv_pow2 = []() {\n\
    \        vector<mint> t(31, mint(1));\n        mint inv2 = mint(2).inv();\n  \
    \      for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i - 1] * inv2;\n     \
    \   return t;\n    }();\n    mint iz = inv_pow2[__builtin_ctz((unsigned)a.size())];\n\
    \    for (auto& x : a) x *= iz;\n}\n\nmint ntt_inv_size(int n) {\n    static vector<mint>\
    \ inv_pow2 = []() {\n        vector<mint> t(31, mint(1));\n        mint inv2 =\
    \ mint(2).inv();\n        for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i -\
    \ 1] * inv2;\n        return t;\n    }();\n    return inv_pow2[__builtin_ctz((unsigned)n)];\n\
    }\n\nbool mod_sqrt(mint a, mint &x) {\n    if (a == mint(0)) {\n        x = mint(0);\n\
    \        return true;\n    }\n    if (a.pow((ntt_mod - 1) >> 1) != mint(1)) return\
    \ false;\n    if (ntt_mod % 4 == 3) {\n        x = a.pow((ntt_mod + 1) >> 2);\n\
    \        return true;\n    }\n    int s = 0;\n    int q = ntt_mod - 1;\n    while\
    \ ((q & 1) == 0) {\n        ++s;\n        q >>= 1;\n    }\n    mint z = 2;\n \
    \   while (z.pow((ntt_mod - 1) >> 1) == mint(1)) ++z;\n    mint c = z.pow(q);\n\
    \    mint t = a.pow(q);\n    mint r = a.pow((q + 1) >> 1);\n    int m = s;\n \
    \   while (t != mint(1)) {\n        int i = 1;\n        mint tt = t * t;\n   \
    \     while (i < m && tt != mint(1)) {\n            tt *= tt;\n            ++i;\n\
    \        }\n        mint b = c.pow(1LL << (m - i - 1));\n        r *= b;\n   \
    \     c = b * b;\n        t *= c;\n        m = i;\n    }\n    x = r;\n    return\
    \ true;\n}\n\nstruct poly {\n    vector<mint> v;\n    poly() = default;\n    explicit\
    \ poly(int n) : v(n) {};\n    explicit poly(vector<mint> vv) : v(std::move(vv))\
    \ {};\n    int size() const {return (int)v.size(); }\n    void shrink() {\n  \
    \      while (!v.empty() && v.back() == mint(0)) v.pop_back();\n    }\n    poly\
    \ cut(int len){\n        if (len < (int)v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    inline const mint& operator[] (int i) const {return\
    \ v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly &operator+=(const mint &r) {\n       \
    \ if (v.empty()) v.resize(1);\n        v[0] += r;\n        return *this;\n   \
    \ }\n    poly& operator-=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];\n\
    \        return *this;\n    }\n    poly& operator*=(const poly &a) {\n       \
    \ const int n = size();\n        const int m = a.size();\n        if (n == 0 ||\
    \ m == 0) {\n            v.clear();\n            return *this;\n        }\n  \
    \      if (n == 1 || m == 1) {\n            const mint scalar = n == 1 ? v[0]\
    \ : a.v[0];\n            if (n == 1) v = a.v;\n            for (auto &x : v) x\
    \ *= scalar;\n            return *this;\n        }\n        if (min(n, m) <= NTT_NAIVE_MUL_SHORT_DIM\
    \ ||\n            (1LL * n * m <= NTT_NAIVE_MUL_THRESHOLD && min(n, m) <= NTT_NAIVE_MUL_MIN_DIM))\
    \ {\n            vector<mint> res(n + m - 1);\n            for (int i = 0; i <\
    \ n; ++i) {\n                for (int j = 0; j < m; ++j) {\n                 \
    \   res[i + j] += v[i] * a.v[j];\n                }\n            }\n         \
    \   v = std::move(res);\n            return *this;\n        }\n        int N =\
    \ n + m - 1;\n        int sz = 1;\n        while(sz < N) sz <<= 1;\n        this->v.resize(sz);\n\
    \        ntt.transform(this->v, 0);\n        if (this == &a) {\n            for\
    \ (int i = 0; i < sz; ++i) this->v[i] *= this->v[i];\n        } else {\n     \
    \       static thread_local vector<mint> b;\n            b.assign(a.v.begin(),\
    \ a.v.end());\n            b.resize(sz);\n            ntt.transform(b, 0);\n \
    \           for(int i = 0; i < sz; ++i) this->v[i] *= b[i];\n        }\n     \
    \   ntt.transform(this->v, 1);\n        this->v.resize(N);\n        mint iz =\
    \ ntt_inv_size(sz);\n        for (int i = 0; i < N; i++) this->v[i] *= iz;\n \
    \       return *this;\n    }\n    poly& operator/=(const poly &a){ return (*this\
    \ *= a.inv()); }\n    poly operator+(const poly &a) const {\n        poly ret(*this);\n\
    \        ret += a;\n        return ret;\n    }\n    poly operator+(const mint\
    \ &v) const {\n        poly ret(*this);\n        ret += v;\n        return ret;\n\
    \    }\n    poly operator-(const poly &a) const {\n        poly ret(*this);\n\
    \        ret -= a;\n        return ret;\n    }\n    poly operator*(const poly\
    \ &a) const {\n        poly ret(*this);\n        ret *= (this == &a ? ret : a);\n\
    \        return ret;\n    }\n    poly rev(int deg = -1) const {\n        poly\
    \ ret(*this);\n        if (deg != -1) ret.v.resize(deg);\n        reverse(ret.v.begin(),\
    \ ret.v.end());\n        return ret;\n    }\n\n    pair<poly, poly> divmod(const\
    \ poly &a) const {\n        poly f(*this), g(a);\n        f.shrink();\n      \
    \  g.shrink();\n        assert(!g.v.empty());\n        if (f.size() < g.size())\
    \ return {poly(), f};\n        int need = f.size() - g.size() + 1;\n        if\
    \ (min(g.size(), need) <= 16 || 1LL * g.size() * need <= 4096) {\n           \
    \ poly q(need);\n            mint inv_lead = g.v.back() == mint(1) ? mint(1) :\
    \ g.v.back().inv();\n            for (int i = need - 1; i >= 0; --i) {\n     \
    \           mint c = f[i + g.size() - 1] * inv_lead;\n                q[i] = c;\n\
    \                for (int j = 0; j + 1 < g.size(); ++j) f[i + j] -= c * g[j];\n\
    \            }\n            f.v.resize(g.size() - 1);\n            f.shrink();\n\
    \            return {std::move(q), std::move(f)};\n        }\n        poly q =\
    \ (f.rev().pre(need) * g.rev().inv(need)).pre(need).rev();\n        poly r = f\
    \ - g * q;\n        r = r.pre(g.size() - 1);\n        r.shrink();\n        return\
    \ {q, r};\n    }\n\n    poly mod(const poly &a) const {\n        return divmod(a).second;\n\
    \    }\n\n    mint eval(mint x) const {\n        mint y = 0;\n        for (int\
    \ i = size() - 1; i >= 0; --i) y = y * x + v[i];\n        return y;\n    }\n\n\
    \    poly pre(int sz) const {\n        poly ret(sz);\n        for (int i = 0;\
    \ i < min<int>(sz, v.size()); ++i) {\n            ret[i] = v[i];\n        }\n\
    \        return ret;\n    }\n\n    poly diff() const {\n        const int n =\
    \ (int)this->size();\n        poly ret(max(0, n - 1));\n        mint one(1), coeff(1);\n\
    \        for (int i = 1; i < n; i++) {\n            ret[i - 1] = v[i] * coeff;\n\
    \            coeff += one;\n        }\n        return ret;\n    }\n\n    poly\
    \ integral() const {\n        const int n = (int)this->size();\n        poly ret(n\
    \ + 1);\n        ret[0] = mint(0);\n        static vector<mint> invs = {mint(0),\
    \ mint(1)};\n        if ((int)invs.size() <= n) {\n            int old = (int)invs.size();\n\
    \            invs.resize(n + 1);\n            for (int i = old; i <= n; ++i) invs[i]\
    \ = mint(ntt_mod - ntt_mod / i) * invs[ntt_mod % i];\n        }\n        for (int\
    \ i = 0; i < n; i++) ret[i + 1] = v[i] * invs[i + 1];\n        return ret;\n \
    \   }\n\n    poly inv(int deg = -1) const {\n        assert(!v.empty() && v[0]\
    \ != mint(0));\n        if (deg == -1) deg = size();\n        if (deg == 0) return\
    \ poly();\n        poly res(deg);\n        res[0] = v[0].inv();\n        for (int\
    \ d = 1; d < deg; d <<= 1) {\n            vector<mint> f(2 * d), g(2 * d);\n \
    \           for (int i = 0; i < min(size(), 2 * d); ++i) f[i] = v[i];\n      \
    \      for (int i = 0; i < d; ++i) g[i] = res[i];\n            ntt.transform(f,\
    \ 0);\n            ntt.transform(g, 0);\n            for (int i = 0; i < 2 * d;\
    \ ++i) f[i] *= g[i];\n            ntt_ifft(f);\n            fill(f.begin(), f.begin()\
    \ + d, mint(0));\n            ntt.transform(f, 0);\n            for (int i = 0;\
    \ i < 2 * d; ++i) f[i] *= g[i];\n            ntt_ifft(f);\n            for (int\
    \ i = d; i < min(2 * d, deg); ++i) res[i] = -f[i];\n        }\n        return\
    \ res.pre(deg);\n    }\n\n    poly log(int deg = -1) const {\n        assert(!v.empty()\
    \ && v[0] == mint(1));\n        if (deg == -1) deg = (int)this->size();\n    \
    \    if (deg == 0) return poly();\n        return (pre(min(size(), deg)).diff()\
    \ * inv(deg)).pre(deg - 1).integral();\n    }\n\n    poly exp(int deg = -1) const\
    \ {\n        assert(v.size() == 0 || v[0] == mint(0));\n        if (deg == -1)\
    \ deg = v.size();\n        static vector<mint> invs = {mint(0), mint(1)};\n  \
    \      auto ensure_invs = [&](int n) {\n            if ((int)invs.size() <= n)\
    \ {\n                int old = (int)invs.size();\n                invs.resize(n\
    \ + 1);\n                for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod\
    \ - ntt_mod / i) * invs[ntt_mod % i];\n            }\n        };\n        auto\
    \ inplace_integral = [&](poly& f) {\n            int n = f.size();\n         \
    \   ensure_invs(n);\n            f.v.insert(f.v.begin(), mint(0));\n         \
    \   for (int i = 1; i <= n; ++i) f[i] *= invs[i];\n        };\n        poly b(vector<mint>{mint(1),\
    \ (1 < size() ? v[1] : mint(0))});\n        poly c(vector<mint>{mint(1)}), z1,\
    \ z2(vector<mint>{mint(1), mint(1)});\n        for (int m = 2; m < deg; m <<=\
    \ 1) {\n            poly y = b;\n            y.v.resize(2 * m);\n            ntt.transform(y.v,\
    \ 0);\n            z1 = z2;\n            poly z(m);\n            for (int i =\
    \ 0; i < m; ++i) z[i] = y[i] * z1[i];\n            ntt_ifft(z.v);\n          \
    \  fill(z.v.begin(), z.v.begin() + m / 2, mint(0));\n            ntt.transform(z.v,\
    \ 0);\n            for (int i = 0; i < m; ++i) z[i] *= -z1[i];\n            ntt_ifft(z.v);\n\
    \            c.v.insert(c.v.end(), z.v.begin() + m / 2, z.v.end());\n        \
    \    z2 = c;\n            z2.v.resize(2 * m);\n            ntt.transform(z2.v,\
    \ 0);\n\n            poly x(m);\n            for (int i = 0; i + 1 < m && i +\
    \ 1 < size(); ++i) x[i] = v[i + 1] * mint(i + 1);\n            x[m - 1] = mint(0);\n\
    \            ntt.transform(x.v, 0);\n            for (int i = 0; i < m; ++i) x[i]\
    \ *= y[i];\n            ntt_ifft(x.v);\n            for (int i = 0; i + 1 < m;\
    \ ++i) x[i] -= b[i + 1] * mint(i + 1);\n            x.v.resize(2 * m);\n     \
    \       for (int i = 0; i + 1 < m; ++i) {\n                x[m + i] = x[i];\n\
    \                x[i] = mint(0);\n            }\n            ntt.transform(x.v,\
    \ 0);\n            for (int i = 0; i < 2 * m; ++i) x[i] *= z2[i];\n          \
    \  ntt_ifft(x.v);\n            x.v.pop_back();\n            inplace_integral(x);\n\
    \            for (int i = m; i < min(size(), 2 * m); ++i) x[i] += v[i];\n    \
    \        fill(x.v.begin(), x.v.begin() + m, mint(0));\n            ntt.transform(x.v,\
    \ 0);\n            for (int i = 0; i < 2 * m; ++i) x[i] *= y[i];\n           \
    \ ntt_ifft(x.v);\n            b.v.insert(b.v.end(), x.v.begin() + m, x.v.end());\n\
    \        }\n        return b.pre(deg);\n    }\n\n    poly pow(long long k, int\
    \ deg = -1) const {\n        if (deg == -1) deg = size();\n        if (deg <=\
    \ 0) return poly();\n        if (k == 1) return pre(deg);\n        poly ret(deg);\n\
    \        if (k == 0) {\n            ret[0] = 1;\n            return ret;\n   \
    \     }\n        int lead = 0;\n        while (lead < min(size(), deg) && v[lead]\
    \ == mint(0)) lead++;\n        if (lead == min(size(), deg)) return ret;\n   \
    \     if (lead > 0 && k > (deg - 1) / lead) return ret;\n        int shift = static_cast<int>(1LL\
    \ * lead * k);\n        int rem_deg = deg - shift;\n        if (0 < k && k <=\
    \ 64) {\n            int end = lead + min(size() - lead, rem_deg);\n         \
    \   while (end > lead && v[end - 1] == mint(0)) end--;\n            poly base(vector<mint>(v.begin()\
    \ + lead, v.begin() + end));\n            poly ans(1);\n            ans[0] = 1;\n\
    \            long long e = k;\n            while (e > 0) {\n                if\
    \ (e & 1) {\n                    ans *= base;\n                    if (ans.size()\
    \ > rem_deg) ans.v.resize(rem_deg);\n                }\n                e >>=\
    \ 1;\n                if (e == 0) break;\n                base *= base;\n    \
    \            if (base.size() > rem_deg) base.v.resize(rem_deg);\n            }\n\
    \            for (int i = 0; i < ans.size(); ++i) ret[i + shift] = ans[i];\n \
    \           return ret;\n        }\n        poly f(min(size() - lead, rem_deg));\n\
    \        mint inv_lead = v[lead].inv();\n        for (int i = 0; i < f.size();\
    \ ++i) f[i] = v[i + lead] * inv_lead;\n        poly g = f.log(rem_deg);\n    \
    \    mint k_mint = mint(k);\n        for (int i = 0; i < g.size(); ++i) g[i] *=\
    \ k_mint;\n        g = g.exp(rem_deg);\n        mint coeff = v[lead].pow(k);\n\
    \        for (int i = 0; i < g.size(); ++i) g[i] *= coeff;\n        for (int i\
    \ = 0; i < g.size(); ++i) ret[i + shift] = g[i];\n        return ret;\n    }\n\
    \n    poly sqrt(int deg = -1) const {\n        if (deg == -1) deg = size();\n\
    \        poly ret(max(0, deg));\n        if (deg <= 0) return ret;\n        int\
    \ lead = 0;\n        while (lead < size() && v[lead] == mint(0)) lead++;\n   \
    \     if (lead == size()) return ret;\n        if (lead & 1) return poly();\n\
    \        mint sq0;\n        if (!mod_sqrt(v[lead], sq0)) return poly();\n    \
    \    int shift = lead >> 1;\n        if (shift >= deg) return ret;\n        int\
    \ rem_deg = deg - shift;\n        poly f(size() - lead);\n        mint inv_lead\
    \ = v[lead].inv();\n        for (int i = lead; i < size(); ++i) f[i - lead] =\
    \ v[i] * inv_lead;\n        poly s(1);\n        s[0] = 1;\n        mint inv2 =\
    \ mint(2).inv();\n        for (int k = 1; k < rem_deg; k <<= 1) {\n          \
    \  poly ns = (s + (f.pre(k << 1) * s.inv(k << 1)).pre(k << 1)).pre(k << 1);\n\
    \            for (int i = 0; i < ns.size(); ++i) ns[i] *= inv2;\n            s\
    \ = ns;\n        }\n        s = s.pre(rem_deg);\n        for (int i = 0; i < s.size();\
    \ ++i) ret[i + shift] = s[i] * sq0;\n        return ret;\n    }\n\n    vector<mint>\
    \ multipoint_eval(const vector<mint> &xs) const;\n};\n\n/**\n * @brief NTT\u30FB\
    \u5F62\u5F0F\u7684\u51AA\u7D1A\u6570(NTT/FPS)\n */\n\n\n#line 2 \"fps/nth_term.cpp\"\
    \nmint nth_term(const poly &p_input, const poly &q_input, ll n){\n    assert(n\
    \ >= 0 && q_input.size() > 0 && q_input[0] != mint(0));\n    if(p_input.size()\
    \ == 0) return 0;\n    if(q_input.size() == 1) return n < p_input.size() ? p_input[n]/q_input[0]\
    \ : mint(0);\n    if(!n) return p_input[0]/q_input[0];\n    int p_size = n < p_input.size()\
    \ ? static_cast<int>(n) + 1 : p_input.size();\n    int q_size = n < q_input.size()\
    \ ? static_cast<int>(n) + 1 : q_input.size();\n    poly p(vector<mint>(p_input.v.begin(),\
    \ p_input.v.begin() + p_size));\n    poly q(vector<mint>(q_input.v.begin(), q_input.v.begin()\
    \ + q_size));\n    if(q[0] != mint(1)) {\n        mint inv = q[0].inv();\n   \
    \     for(auto &v : p.v) v *= inv;\n        for(auto &v : q.v) v *= inv;\n   \
    \ }\n    int sz = 1, h = 0;\n    int k = max(p.size(), q.size());\n    while(sz\
    \ < 2*k-1) sz <<= 1, h++;\n    p.v.resize(sz); q.v.resize(sz);\n    mint x = mint(sz>>1).inv();\n\
    \    vector<mint> y(sz>>1, 0);\n    for (int j = sz>>2, i = h; j; j >>= 1, i--)\
    \ y[j] = ntt.iroot_pow2(i);\n    y[0] = 1;\n    for (int i = 2; i < sz>>1; i <<=\
    \ 1) {\n        for (int j = i+1; j < 2*i; ++j) {\n            y[j] = y[j-i]*y[i];\n\
    \        }\n    }\n    ntt.transform(p.v, 0);\n    ntt.transform(q.v, 0);\n  \
    \  poly tmp(sz>>1);\n    auto up = [&](poly &A){\n        for (int i = 0; i <\
    \ sz>>1; ++i) tmp[i] = A[i];\n        ntt.transform(tmp.v, 1);\n        mint now\
    \ = x;\n        for (int i = 0; i < sz>>1; ++i) tmp[i] *= now, now *= ntt.root_pow2(h);\n\
    \        ntt.transform(tmp.v, 0);\n        for (int i = 0; i < sz>>1; ++i) A[i|(sz>>1)]\
    \ = tmp[i];\n    };\n    int ika = h;\n    while(n){\n        for (int i = 0;\
    \ i < sz; ++i) p[i] *= q[i^1];\n        if(n&1) for (int i = 0; i < sz>>1; ++i)\
    \ p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];\n        else for (int i = 0; i < sz>>1;\
    \ ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);\n        ika++;\n        if(n == 1) break;\n\
    \        up(p);\n        for (int i = 0; i < sz>>1; ++i) q[i] = q[i<<1]*q[(i<<1)|1];\n\
    \        up(q);\n        n >>= 1;\n    }\n    for (int i = 0; i < sz>>1; ++i)\
    \ tmp[i] = p[i];\n    ntt.transform(tmp.v, 1);\n    return mint(2).pow(ntt_mod-ika)*tmp[0];\n\
    }\n\n/**\n * @brief \u6709\u7406\u578B\u6BCD\u95A2\u6570\u306EN\u9805\u76EE\n\
    \ */\n#line 1 \"math/berlekamp_massey.cpp\"\ntemplate<class T>\nvector<T> berlekamp_massey(const\
    \ vector<T> &s) {\n    vector<T> c(1, T(1)), b(1, T(1));\n    int l = 0, m = 1;\n\
    \    T y = T(1);\n    for (int n = 0; n < (int)s.size(); ++n) {\n        T d =\
    \ T(0);\n        for (int i = 0; i <= l; ++i) d += c[i] * s[n - i];\n        if\
    \ (d == T(0)) {\n            ++m;\n            continue;\n        }\n        vector<T>\
    \ t;\n        if (2 * l <= n) t = c;\n        T coef = d / y;\n        if ((int)c.size()\
    \ < (int)b.size() + m) c.resize((int)b.size() + m, T(0));\n        for (int i\
    \ = 0; i < (int)b.size(); ++i) c[i + m] -= coef * b[i];\n        if (2 * l <=\
    \ n) {\n            l = n + 1 - l;\n            b = std::move(t);\n          \
    \  y = d;\n            m = 1;\n        } else {\n            ++m;\n        }\n\
    \    }\n    c.erase(c.begin());\n    for (auto &x : c) x = -x;\n    return c;\n\
    }\n\n/**\n * @brief Berlekamp-Massey\u6CD5\n */\n#line 3 \"fps/linear_recurrence.cpp\"\
    \n\nmint linear_recurrence(const vector<mint> &a, const vector<mint> &c, ll n)\
    \ {\n    if (n < (ll)a.size()) return a[(int)n];\n    int k = (int)c.size();\n\
    \    if (k == 0) return mint(0);\n    poly q(k + 1);\n    q[0] = 1;\n    for (int\
    \ i = 0; i < k; ++i) q[i + 1] = -c[i];\n    vector<mint> aa(k, mint(0));\n   \
    \ for (int i = 0; i < min(k, (int)a.size()); ++i) aa[i] = a[i];\n    poly p =\
    \ (poly(aa) * q).cut(k);\n    return nth_term(p, q, n);\n}\n\nmint linear_recurrence(const\
    \ vector<mint> &a, ll n) {\n    if (n < (ll)a.size()) return a[(int)n];\n    return\
    \ linear_recurrence(a, berlekamp_massey(a), n);\n}\n\n/**\n * @brief \u7DDA\u5F62\
    \u6F38\u5316\u5F0F(Linear Recurrence)\n */\n#line 6 \"string/count_words.cpp\"\
    \n\ntemplate<int W>\nmint count_words(const DFA<W>& a, ll n) {\n    assert(n >=\
    \ 0);\n    if (a.initial == -1) return mint(0);\n    if (n == 0) return mint(bool(a.accept[a.initial]));\n\
    \    if (none_of(a.accept.begin(), a.accept.end(), [](char x) { return x; }))\
    \ return mint(0);\n    int s = (int)a.next.size();\n    if (s == 1) {\n      \
    \  if (!a.accept[0]) return mint(0);\n        int degree = 0;\n        for (int\
    \ to : a.next[0]) degree += to != -1;\n        return mint(degree).pow(n);\n \
    \   }\n    ll terms = min(n, 2LL * s - 1) + 1;\n    vector<unsigned> dp(s);\n\
    \    vector<unsigned long long> next(s);\n    vector<mint> sequence;\n    vector<int>\
    \ active{a.initial}, touched;\n    sequence.reserve(terms);\n    dp[a.initial]\
    \ = 1;\n    unsigned long long total = bool(a.accept[a.initial]);\n    int width\
    \ = min<unsigned long long>(W, numeric_limits<unsigned long long>::max() / (ntt_mod\
    \ - 1) / (s + 1ULL));\n    for (ll len = 0; len < terms; ++len) {\n        sequence.push_back(mint::raw(total\
    \ % ntt_mod));\n        if (len == n) return sequence.back();\n        if (active.empty())\
    \ return mint(0);\n        if (len + 1 == terms) break;\n        bool sparse =\
    \ active.size() < size_t(s) / 4 && width == W;\n        touched.clear();\n   \
    \     if (sparse) {\n            for (int v : active) {\n                for (int\
    \ to : a.next[v]) if (to != -1) {\n                    if (next[to] == 0) touched.push_back(to);\n\
    \                    next[to] += dp[v];\n                }\n                dp[v]\
    \ = 0;\n            }\n        } else if (width == W) {\n            for (int\
    \ v : active) {\n                for (int to : a.next[v]) if (to != -1) next[to]\
    \ += dp[v];\n            }\n        } else {\n            for (int first = 0;\
    \ first < W;) {\n                int last = first + min(width, W - first);\n \
    \               for (int v : active) {\n                    for (int c = first;\
    \ c < last; ++c) {\n                        int to = a.next[v][c];\n         \
    \               if (to != -1) next[to] += dp[v];\n                    }\n    \
    \            }\n                first = last;\n                if (first != W)\
    \ for (auto& value : next) value %= ntt_mod;\n            }\n        }\n     \
    \   active.clear();\n        total = 0;\n        auto finish = [&](int v) {\n\
    \            dp[v] = next[v] % ntt_mod;\n            next[v] = 0;\n          \
    \  if (dp[v]) active.push_back(v);\n            if (a.accept[v]) total += dp[v];\n\
    \        };\n        if (sparse) {\n            for (int v : touched) finish(v);\n\
    \        } else {\n            for (int v = 0; v < s; ++v) finish(v);\n      \
    \  }\n    }\n    return linear_recurrence(sequence, n);\n}\n\n\n\n/**\n * @brief\
    \ \u6709\u9650\u72B6\u614BDP\u306E\u9577\u3055N\u306E\u6587\u5B57\u5217\u6570\n\
    \ */\n#line 1 \"string/avoid_patterns.cpp\"\n\n\n\n#line 1 \"datastructure/ahocorasick.cpp\"\
    \n\n\n\ntemplate<int W, int start>\nclass AhoCorasick {\npublic:\n    struct Node\
    \ {\n        array<int, W> to;\n        int fail;\n        int val;\n    };\n\
    \    explicit AhoCorasick() : v(1) {}\n    vector<Node> v;\n    vector<int> ord;\n\
    \    int add(const string &s, int cur = 0){\n        for (auto &&i : s) {\n  \
    \          if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();\n\
    \            cur = v[cur].to[i-start];\n        }\n        return cur;\n    }\n\
    \n    void build() {\n        v[0].fail = -1;\n        int l = 0, r = 1;\n   \
    \     ord.clear();\n        ord.reserve(v.size());\n        ord.emplace_back(0);\n\
    \        while(l < r){\n            int i = ord[l]; l++;\n            for (int\
    \ c = 0; c < W; ++c) {\n                if(!v[i].to[c]) continue;\n          \
    \      int to = v[i].to[c];\n                v[to].fail = (v[i].fail == -1 ? 0\
    \ : v[v[i].fail].to[c]);\n                ord.emplace_back(to);\n            \
    \    r++;\n            }\n            if(i != 0){\n                for (int c\
    \ = 0; c < W; ++c) {\n                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];\n\
    \                }\n            }\n        }\n    }\n    inline int next(int x,\
    \ char c){ return v[x].to[c-start]; }\n\n    vector<long long> occurrence_counts(const\
    \ string &text) const {\n        vector<long long> counts(v.size());\n       \
    \ counts[0] = 1;\n        int state = 0;\n        for (char c : text) {\n    \
    \        state = v[state].to[c - start];\n            ++counts[state];\n     \
    \   }\n        for (int i = (int)ord.size() - 1; i > 0; --i) {\n            int\
    \ state = ord[i];\n            counts[v[state].fail] += counts[state];\n     \
    \   }\n        return counts;\n    }\n};\n\n\n\n/**\n * @brief Aho-Corasick\u6CD5\
    \n */\n#line 6 \"string/avoid_patterns.cpp\"\n\ntemplate<int W, int start>\nDFA<W>\
    \ avoid_patterns(const vector<string>& patterns) {\n    AhoCorasick<W, start>\
    \ ac;\n    for (const string& s : patterns) {\n        if (s.empty()) return {};\n\
    \        int v = ac.add(s);\n        ac.v[v].val = 1;\n    }\n    ac.build();\n\
    \    for (int v : ac.ord) {\n        if (v != 0) ac.v[v].val |= ac.v[ac.v[v].fail].val;\n\
    \    }\n    vector<int> id(ac.v.size(), -1), states{0};\n    id[0] = 0;\n    DFA<W>\
    \ result{vector<array<int, W>>(1), vector<char>(1, true), 0};\n    for (int i\
    \ = 0; i < (int)states.size(); ++i) {\n        int v = states[i];\n        for\
    \ (int c = 0; c < W; ++c) {\n            int to = ac.v[v].to[c];\n           \
    \ if (ac.v[to].val) {\n                result.next[i][c] = -1;\n             \
    \   continue;\n            }\n            if (id[to] == -1) {\n              \
    \  id[to] = (int)states.size();\n                states.push_back(to);\n     \
    \           result.next.emplace_back();\n                result.accept.push_back(true);\n\
    \            }\n            result.next[i][c] = id[to];\n        }\n    }\n  \
    \  return result;\n}\n\n\n\n/**\n * @brief \u7981\u6B62\u90E8\u5206\u6587\u5B57\
    \u5217\u3092\u907F\u3051\u308B\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\
    \n */\n#line 1 \"math/digit_dfa.cpp\"\n\n\n\n#line 5 \"math/digit_dfa.cpp\"\n\n\
    DFA<10> digit_value_mod(int m, int r = 0) {\n    assert(m > 0 && 0 <= r && r <\
    \ m);\n    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};\n    a.accept[r]\
    \ = true;\n    for (int v = 0; v < m; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = (10LL * v + d) % m;\n    }\n    return a;\n}\n\nDFA<10>\
    \ digit_sum_mod(int m, int r = 0) {\n    assert(m > 0 && 0 <= r && r < m);\n \
    \   DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};\n    a.accept[r]\
    \ = true;\n    for (int v = 0; v < m; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = (v + (long long)d) % m;\n    }\n    return a;\n}\n\nDFA<10>\
    \ digit_sum_exact(int k) {\n    assert(0 <= k && k < numeric_limits<int>::max());\n\
    \    DFA<10> a{vector<array<int, 10>>(k + 1), vector<char>(k + 1), 0};\n    a.accept[k]\
    \ = true;\n    for (int v = 0; v <= k; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = d <= k - v ? v + d : -1;\n    }\n    return a;\n}\n\nDFA<10>\
    \ no_equal_adjacent() {\n    DFA<10> a{vector<array<int, 10>>(11), vector<char>(11,\
    \ true), 10};\n    for (int v = 0; v <= 10; ++v) {\n        for (int d = 0; d\
    \ < 10; ++d) a.next[v][d] = v == d ? -1 : d;\n    }\n    return a;\n}\n\nDFA<10>\
    \ required_digits(int mask) {\n    assert(0 <= mask && mask < (1 << 10));\n  \
    \  array<int, 10> bit{};\n    int n = 1;\n    for (int d = 0; d < 10; ++d) {\n\
    \        if (mask >> d & 1) bit[d] = n, n *= 2;\n    }\n    DFA<10> a{vector<array<int,\
    \ 10>>(n), vector<char>(n), 0};\n    a.accept[n - 1] = true;\n    for (int v =\
    \ 0; v < n; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = v | bit[d];\n\
    \    }\n    return a;\n}\n\n\n\n/**\n * @brief \u6570\u5B57\u5217\u306E\u6761\u4EF6\
    \u3092\u8868\u3059\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\n */\n#line\
    \ 1 \"string/dfa_minimize.cpp\"\n\n\n\n#line 5 \"string/dfa_minimize.cpp\"\n\n\
    template<int W>\nDFA<W> minimize(const DFA<W>& a) {\n    if (a.initial == -1)\
    \ return {};\n    vector<int> index(a.next.size(), -1), states{a.initial};\n \
    \   index[a.initial] = 0;\n    for (size_t i = 0; i < states.size(); ++i) {\n\
    \        for (int to : a.next[states[i]]) {\n            if (to != -1 && index[to]\
    \ == -1) {\n                index[to] = (int)states.size();\n                states.push_back(to);\n\
    \            }\n        }\n    }\n    int sink = (int)states.size();\n    assert(sink\
    \ < numeric_limits<int>::max());\n    int n = sink + 1;\n    vector<int> order;\n\
    \    order.reserve(n);\n    for (int v = 0; v < sink; ++v) if (a.accept[states[v]])\
    \ order.push_back(v);\n    int accepted = (int)order.size();\n    if (accepted\
    \ == 0) return {};\n    for (int v = 0; v < sink; ++v) if (!a.accept[states[v]])\
    \ order.push_back(v);\n    order.push_back(sink);\n    vector<array<int, W>> head(n),\
    \ link(n);\n    for (auto& row : head) row.fill(-1);\n    for (int v = 0; v <\
    \ n; ++v) {\n        for (int c = 0; c < W; ++c) {\n            int to = v ==\
    \ sink ? -1 : a.next[states[v]][c];\n            to = to == -1 ? sink : index[to];\n\
    \            link[v][c] = head[to][c];\n            head[to][c] = v;\n       \
    \ }\n    }\n    vector<int> group(n), position(n), begin{0, accepted}, end{accepted,\
    \ n}, marked{0, accepted};\n    for (int i = 0; i < n; ++i) group[order[i]] =\
    \ i >= accepted, position[order[i]] = i;\n    vector<int> pending{accepted <=\
    \ n - accepted ? 0 : 1}, splitter, touched;\n    while (!pending.empty()) {\n\
    \        int block = pending.back();\n        pending.pop_back();\n        splitter.assign(order.begin()\
    \ + begin[block], order.begin() + end[block]);\n        for (int c = 0; c < W;\
    \ ++c) {\n            touched.clear();\n            for (int to : splitter) {\n\
    \                for (int v = head[to][c]; v != -1; v = link[v][c]) {\n      \
    \              int b = group[v];\n                    if (marked[b] == begin[b])\
    \ touched.push_back(b);\n                    int i = position[v], j = marked[b]++;\n\
    \                    swap(order[i], order[j]);\n                    position[order[i]]\
    \ = i;\n                    position[order[j]] = j;\n                }\n     \
    \       }\n            for (int b : touched) {\n                int mid = marked[b],\
    \ l = begin[b], r = end[b];\n                if (mid != r) {\n               \
    \     int id = (int)begin.size();\n                    if (mid - l <= r - mid)\
    \ {\n                        begin.push_back(l);\n                        end.push_back(mid);\n\
    \                        begin[b] = mid;\n                    } else {\n     \
    \                   begin.push_back(mid);\n                        end.push_back(r);\n\
    \                        end[b] = mid;\n                    }\n              \
    \      marked.push_back(begin[id]);\n                    for (int i = begin[id];\
    \ i < end[id]; ++i) group[order[i]] = id;\n                    pending.push_back(id);\n\
    \                }\n                marked[b] = begin[b];\n            }\n   \
    \     }\n    }\n    int dead = group[sink];\n    if (group[0] == dead) return\
    \ {};\n    vector<int> id(begin.size(), -1), queue{group[0]};\n    id[group[0]]\
    \ = 0;\n    DFA<W> result;\n    result.initial = 0;\n    for (size_t i = 0; i\
    \ < queue.size(); ++i) {\n        int v = states[order[begin[queue[i]]]];\n  \
    \      array<int, W> row;\n        for (int c = 0; c < W; ++c) {\n           \
    \ int to = a.next[v][c];\n            int b = to == -1 ? dead : group[index[to]];\n\
    \            if (b == dead) row[c] = -1;\n            else {\n               \
    \ if (id[b] == -1) {\n                    id[b] = (int)queue.size();\n       \
    \             queue.push_back(b);\n                }\n                row[c] =\
    \ id[b];\n            }\n        }\n        result.next.push_back(row);\n    \
    \    result.accept.push_back(bool(a.accept[v]));\n    }\n    return result;\n\
    }\n\n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\
    \u6700\u5C0F\u5316\n */\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    extern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value\
    \ : false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct\
    \ has_fastio_assign_string : false_type {};\n\ntemplate<class T>\nstruct has_fastio_assign_string<T,\
    \ void_t<decltype(declval<T &>().assign(declval<const string &>()))>> : true_type\
    \ {};\n\ntemplate<class T, class = void>\nstruct has_fastio_to_string : false_type\
    \ {};\n\ntemplate<class T>\nstruct has_fastio_to_string<T, void_t<decltype(declval<const\
    \ T &>().to_string())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char\
    \ num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for (int\
    \ i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int j = 3;\
    \ j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n     \
    \           x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner {\n\
    \    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    static constexpr int LONG_TOKEN_SAMPLE_SIZE = 1024;\n    static constexpr\
    \ int LONG_TOKEN_MIN_DIGITS = 16;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\
    \    bool interactive, long_tokens;\n    string number_token;\n\n    Scanner()\
    \ : idx(0), size(0), interactive(isatty(fileno(stdin))), long_tokens(false) {}\n\
    \n    __attribute__((always_inline))\n    static inline unsigned parse_eight_digits(const\
    \ char *p) {\n        unsigned long long value;\n        memcpy(&value, p, 8);\n\
    #if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__\n      \
    \  value = __builtin_bswap64(value);\n#endif\n        value -= 0x3030303030303030ULL;\n\
    \        value = (value * 10 + (value >> 8)) & 0x00ff00ff00ff00ffULL;\n      \
    \  value = (value * 100 + (value >> 16)) & 0x0000ffff0000ffffULL;\n        value\
    \ = (value * 10000 + (value >> 32)) & 0x00000000ffffffffULL;\n        return (unsigned)value;\n\
    \    }\n\n    __attribute__((always_inline))\n    static inline bool are_eight_digits(const\
    \ char *p) {\n        unsigned long long value;\n        memcpy(&value, p, 8);\n\
    \        return (((value + 0x4646464646464646ULL) | (value - 0x3030303030303030ULL))\
    \ & 0x8080808080808080ULL) == 0;\n    }\n\n    template<class U>\n    __attribute__((noinline))\n\
    \    U read_long_digits(char c) {\n        const char *p = buf + idx - 1;\n  \
    \      const char *end = buf + size;\n        U value = 0;\n        if (c >= '0'\
    \ && end - p >= 16 && p[15] >= '0' && are_eight_digits(p) && are_eight_digits(p\
    \ + 8)) {\n            value = (U)parse_eight_digits(p) * 100000000 + parse_eight_digits(p\
    \ + 8);\n            p += 16;\n            while (*p >= '0') {\n             \
    \   value = value * 10 + (*p & 15);\n                ++p;\n            }\n   \
    \         idx = (int)(p - buf) + 1;\n            return value;\n        }\n  \
    \      while (c >= '0') {\n            value = value * 10 + (c & 15);\n      \
    \      c = buf[idx++];\n        }\n        return value;\n    }\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        if (interactive) {\n            if (fgets(buf + len, BUFSIZE\
    \ + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n            else size\
    \ = len;\n        } else {\n            size = len + (int)fread(buf + len, 1,\
    \ BUFSIZE - len, stdin);\n            int sample_size = min(size, LONG_TOKEN_SAMPLE_SIZE);\n\
    \            int separators = 0;\n            int minus_signs = 0;\n         \
    \   for (int i = 0; i < sample_size; ++i) {\n                separators += buf[i]\
    \ <= ' ';\n                minus_signs += buf[i] == '-';\n            }\n    \
    \        // Select once per buffer so ordinary short integers avoid the\n    \
    \        // checks and call overhead of the 16-digit SWAR path.\n            long_tokens\
    \ = separators * LONG_TOKEN_MIN_DIGITS < sample_size - minus_signs;\n        }\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
    \ {\n        if (idx == size) load();\n    }\n\n    inline char skip() {\n   \
    \     if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            return buf[idx++];\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        using Base = typename conditional<is_same<T, bool>::value, unsigned,\
    \ T>::type;\n        using U = typename make_unsigned<Base>::type;\n        //\
    \ The unsigned magnitude and -(y - 1) - 1 below also cover min(T).\n        if\
    \ (interactive) {\n            char c = skip();\n            bool neg = false;\n\
    \            if constexpr (is_signed<T>::value) {\n                if (c == '-')\
    \ {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       U y = 0;\n            while (c >= '0') {\n                y = y * 10 +\
    \ (c & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg && y) {\n                    x = -static_cast<T>(y - 1);\n     \
    \               --x;\n                    return;\n                }\n       \
    \     }\n            x = static_cast<T>(y);\n            return;\n        }\n\
    \        char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        U y;\n        if (__builtin_expect(long_tokens,\
    \ false)) {\n            y = read_long_digits<U>(c);\n        } else {\n     \
    \       y = 0;\n            while (c >= '0') {\n                y = y * 10 + (c\
    \ & 15);\n                c = buf[idx++];\n            }\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg && y) {\n           \
    \     x = -static_cast<T>(y - 1);\n                --x;\n                return;\n\
    \            }\n        }\n        x = static_cast<T>(y);\n    }\n\n    void read(double\
    \ &x) {\n        read(number_token);\n        const char *first = number_token.data();\n\
    \        const char *last = first + number_token.size();\n        auto result\
    \ = from_chars(first, last, x);\n        if (result.ec != errc{} || result.ptr\
    \ != last) __builtin_trap();\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value\
    \ && has_fastio_assign_string<T>::value, int>::type = 0>\n    void read(T &x)\
    \ {\n        string s;\n        read(s);\n        bool ok = x.assign(s);\n   \
    \     if (!ok) __builtin_trap();\n    }\n\n    template<class Head, class Next,\
    \ class... Tail>\n    void read(Head &head, Next &next, Tail &...tail) {\n   \
    \     read(head);\n        read(next, tail...);\n    }\n\n    template<class T,\
    \ class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \            if (size == 0) break;\n        }\n        if (idx < size) ++idx;\n\
    \    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1 << 17;\n\
    \    static constexpr int OFFSET = 64;\n    static constexpr int DEFAULT_DOUBLE_PRECISION\
    \ = 15;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    string\
    \ number_buf;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0), interactive(isatty(fileno(stdout))) {}\n    ~Printer() { flush();\
    \ }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n        if (interactive && c == '\\n') flush();\n    }\n\n    inline void\
    \ print_range(const char *s, size_t n) {\n        if (interactive) {\n       \
    \     for (size_t i = 0; i < n; ++i) pc(s[i]);\n            return;\n        }\n\
    \        size_t pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE)\
    \ flush();\n            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n\
    \            memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n\
    \            pos += chunk;\n        }\n    }\n\n    void print(const char *s)\
    \ {\n        print_range(s, strlen(s));\n    }\n\n    void print(const string\
    \ &s) {\n        print_range(s.data(), s.size());\n    }\n\n    void print(char\
    \ c) {\n        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0'\
    \ + (b ? 1 : 0)));\n    }\n\n    inline char *write_top(char *out, unsigned x)\
    \ {\n        if (x >= 1000) {\n            memcpy(out, table.num + (x << 2), 4);\n\
    \            return out + 4;\n        }\n        if (x >= 100) {\n           \
    \ memcpy(out, table.num + (x << 2) + 1, 3);\n            return out + 3;\n   \
    \     }\n        if (x >= 10) {\n            unsigned q = (x * 205) >> 11;\n \
    \           out[0] = char('0' + q);\n            out[1] = char('0' + (x - q *\
    \ 10));\n            return out + 2;\n        }\n        *out = char('0' + x);\n\
    \        return out + 1;\n    }\n\n    inline void write_four(char *out, unsigned\
    \ x) {\n        memcpy(out, table.num + (x << 2), 4);\n    }\n\n    inline void\
    \ write_eight(char *out, unsigned x) {\n        unsigned hi = x / 10000;\n   \
    \     unsigned lo = x - hi * 10000;\n        write_four(out, hi);\n        write_four(out\
    \ + 4, lo);\n    }\n\n    inline char *write_u32(char *out, unsigned x) {\n  \
    \      if (x >= 100000000) {\n            unsigned hi = x / 100000000;\n     \
    \       unsigned lo = x - hi * 100000000;\n            out = write_top(out, hi);\n\
    \            write_eight(out, lo);\n            return out + 8;\n        }\n \
    \       if (x >= 10000) {\n            unsigned hi = x / 10000;\n            unsigned\
    \ lo = x - hi * 10000;\n            out = write_top(out, hi);\n            write_four(out,\
    \ lo);\n            return out + 4;\n        }\n        return write_top(out,\
    \ x);\n    }\n\n    __attribute__((noinline))\n    inline char *write_u64(char\
    \ *out, unsigned long long x) {\n        if (x <= 0xffffffffULL) return write_u32(out,\
    \ (unsigned)x);\n        unsigned long long hi = x / 100000000;\n        unsigned\
    \ lo = (unsigned)(x - hi * 100000000);\n        if (hi <= 0xffffffffULL) {\n \
    \           out = write_u32(out, (unsigned)hi);\n            write_eight(out,\
    \ lo);\n            return out + 8;\n        }\n        unsigned top = (unsigned)(hi\
    \ / 100000000);\n        unsigned mid = (unsigned)(hi - (unsigned long long)top\
    \ * 100000000);\n        out = write_u32(out, top);\n        write_eight(out,\
    \ mid);\n        write_eight(out + 8, lo);\n        return out + 16;\n    }\n\n\
    \    template<class T, typename enable_if<is_integral<T>::value && !is_same<T,\
    \ bool>::value, int>::type = 0>\n    void print(T x) {\n        if (idx > BUFSIZE\
    \ - 100) flush();\n        using U = typename make_unsigned<T>::type;\n      \
    \  U y;\n        if constexpr (is_signed<T>::value) {\n            if (x < 0)\
    \ {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        char *out;\n\
    \        if constexpr (sizeof(U) <= 4) {\n            out = write_u32(buf + idx,\
    \ (unsigned)y);\n        } else if constexpr (sizeof(U) <= 8) {\n            out\
    \ = write_u64(buf + idx, (unsigned long long)y);\n        } else {\n         \
    \   static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n            char tmp[TMP_SIZE];\n\
    \            int pos = TMP_SIZE;\n            while (y >= 10000) {\n         \
    \       pos -= 4;\n                memcpy(tmp + pos, table.num + (y % 10000) *\
    \ 4, 4);\n                y /= 10000;\n            }\n            out = write_top(buf\
    \ + idx, (unsigned)y);\n            memcpy(out, tmp + pos, TMP_SIZE - pos);\n\
    \            out += TMP_SIZE - pos;\n        }\n        idx = (int)(out - buf);\n\
    \    }\n\n    void print_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION)\
    \ {\n        if (precision < 0) __builtin_trap();\n        size_t required = (size_t)precision\
    \ + 512;\n        if (number_buf.size() < required) number_buf.resize(required);\n\
    \        while (true) {\n            char *first = number_buf.data();\n      \
    \      char *last = first + number_buf.size();\n            auto result = to_chars(first,\
    \ last, x, chars_format::fixed, precision);\n            if (result.ec == errc{})\
    \ {\n                print_range(first, result.ptr - first);\n               \
    \ return;\n            }\n            if (result.ec != errc::value_too_large)\
    \ __builtin_trap();\n            size_t next_size = number_buf.size() * 2;\n \
    \           if (next_size <= number_buf.size()) __builtin_trap();\n          \
    \  number_buf.resize(next_size);\n        }\n    }\n\n    void print(double x)\
    \ {\n        print_fixed(x);\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && !has_fastio_value<T>::value && has_fastio_to_string<T>::value, int>::type\
    \ = 0>\n    void print(const T &x) {\n        print(x.to_string());\n    }\n\n\
    \    template<class T, typename enable_if<is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value, int>::type = 0>\n    void print(const T &a)\
    \ {\n        bool first = true;\n        for (auto &&x : a) {\n            if\
    \ (!first) pc(' ');\n            first = false;\n            print(x);\n     \
    \   }\n    }\n\n    template<class T>\n    void println(const T &x) {\n      \
    \  print(x);\n        pc('\\n');\n    }\n\n    template<class Head, class... Tail>\n\
    \    void println(const Head &head, const Tail &...tail) {\n        print(head);\n\
    \        ((pc(' '), print(tail)), ...);\n        pc('\\n');\n    }\n\n    void\
    \ println_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION) {\n      \
    \  print_fixed(x, precision);\n        pc('\\n');\n    }\n\n    void println()\
    \ {\n        pc('\\n');\n    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner\
    \ &in, T &x) {\n    in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter\
    \ &operator<<(Printer &out, const T &x) {\n    out.print(x);\n    return out;\n\
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 13 \"\
    test/yosupo_aplusb_count_words.test.cpp\"\n\ntemplate<int W>\nvector<mint> direct(const\
    \ DFA<W>& a, int length) {\n    vector<mint> result(length + 1), dp(a.next.size());\n\
    \    if (a.initial == -1) return result;\n    dp[a.initial] = 1;\n    for (int\
    \ n = 0; n <= length; ++n) {\n        vector<mint> next(dp.size());\n        for\
    \ (int v = 0; v < (int)dp.size(); ++v) {\n            if (a.accept[v]) result[n]\
    \ += dp[v];\n            for (int to : a.next[v]) if (to != -1) next[to] += dp[v];\n\
    \        }\n        dp.swap(next);\n    }\n    return result;\n}\n\ntemplate<int\
    \ W>\nmint dense(const DFA<W>& a, ll n) {\n    if (a.initial == -1) return 0;\n\
    \    int s = a.next.size();\n    vector<vector<mint>> mat(s, vector<mint>(s));\n\
    \    for (int v = 0; v < s; ++v) for (int to : a.next[v]) if (to != -1) mat[v][to]\
    \ += 1;\n    vector<mint> dp(s);\n    dp[a.initial] = 1;\n    while (n) {\n  \
    \      if (n & 1) {\n            vector<mint> next(s);\n            for (int v\
    \ = 0; v < s; ++v) {\n                for (int to = 0; to < s; ++to) next[to]\
    \ += dp[v] * mat[v][to];\n            }\n            dp.swap(next);\n        }\n\
    \        n >>= 1;\n        if (!n) break;\n        vector<vector<mint>> next(s,\
    \ vector<mint>(s));\n        for (int i = 0; i < s; ++i) {\n            for (int\
    \ k = 0; k < s; ++k) {\n                for (int j = 0; j < s; ++j) next[i][j]\
    \ += mat[i][k] * mat[k][j];\n            }\n        }\n        mat.swap(next);\n\
    \    }\n    mint result = 0;\n    for (int v = 0; v < s; ++v) if (a.accept[v])\
    \ result += dp[v];\n    return result;\n}\n\nvoid self_check() {\n    mt19937\
    \ rng(151);\n    const ll largest = numeric_limits<ll>::max();\n    DFA<2> only_a{{{0,\
    \ -1}}, {true}, 0};\n    DFA<2> only_b{{{-1, 0}}, {true}, 0};\n    auto either\
    \ = unite(only_a, only_b);\n    auto neither = complement(either);\n    for (ll\
    \ n : {0LL, 1LL, 2LL, 8LL, 97LL, 1000000000000000000LL, largest}) {\n        mint\
    \ expected = n == 0 ? mint(1) : mint(2);\n        assert(count_words(either, n)\
    \ == expected);\n        assert(count_words(neither, n) == mint(2).pow(n) - expected);\n\
    \        assert(count_words(minimize(either), n) == expected);\n        assert(count_words(minimize(neither),\
    \ n) == mint(2).pow(n) - expected);\n    }\n    for (int tc = 0; tc < 500; ++tc)\
    \ {\n        int s = 1 + rng() % 12;\n        DFA<3> a{vector<array<int, 3>>(s),\
    \ vector<char>(s), int(rng() % (s + 1)) - 1};\n        for (int v = 0; v < s;\
    \ ++v) {\n            a.accept[v] = rng() % 2;\n            for (int& to : a.next[v])\
    \ to = int(rng() % (s + 1)) - 1;\n        }\n        auto expected = direct(a,\
    \ 97);\n        for (int n : {0, 1, 2 * s - 1, 2 * s, 2 * s + 1, 97}) {\n    \
    \        assert(count_words(a, n) == expected[n]);\n        }\n        ll n =\
    \ tc % 7 == 0 ? largest : 1000000000000000000LL - rng();\n        assert(count_words(a,\
    \ n) == dense(a, n));\n    }\n    assert(count_words(DFA<2>{}, 0) == mint(0));\n\
    \    assert(count_words(DFA<2>{}, largest) == mint(0));\n    DFA<2> empty_only{vector<array<int,\
    \ 2>>(1), {true}, 0};\n    empty_only.next[0].fill(-1);\n    assert(count_words(empty_only,\
    \ 0) == mint(1));\n    assert(count_words(empty_only, 1) == mint(0));\n    assert(count_words(empty_only,\
    \ largest) == mint(0));\n    DFA<2> chain{vector<array<int, 2>>(64), vector<char>(64),\
    \ 0};\n    chain.accept.back() = true;\n    for (int v = 0; v < 64; ++v) chain.next[v].fill(v\
    \ == 63 ? -1 : v + 1);\n    for (ll n : {0LL, 62LL, 63LL, 64LL, 127LL, 128LL,\
    \ largest}) {\n        assert(count_words(chain, n) == (n == 63 ? mint(2).pow(63)\
    \ : mint(0)));\n    }\n    for (ll n : {0LL, 1LL, 2LL, 97LL, largest}) {\n   \
    \     assert(count_words(required_digits(0), n) == mint(10).pow(n));\n    }\n\
    \    auto reject = required_digits(0);\n    reject.accept[0] = false;\n    assert(count_words(reject,\
    \ largest) == mint(0));\n    for (int tc = 0; tc < 100; ++tc) {\n        int s\
    \ = 20 + rng() % 80;\n        DFA<32> a{vector<array<int, 32>>(s), vector<char>(s),\
    \ int(rng() % s)};\n        for (int v = 0; v < s; ++v) {\n            a.accept[v]\
    \ = rng() % 2;\n            for (int& to : a.next[v]) to = rng() % 5 == 0 ? -1\
    \ : int(rng() % s);\n        }\n        auto expected = direct(a, 2 * s + 10);\n\
    \        for (int n : {1, 2, s, 2 * s + 10}) assert(count_words(a, n) == expected[n]);\n\
    \    }\n    DFA<2> wide{vector<array<int, 2>>(511), vector<char>(511, true), 0};\n\
    \    for (int v = 0; v < 511; ++v) {\n        wide.next[v] = {v < 255 ? 2 * v\
    \ + 1 : 0, v < 255 ? 2 * v + 2 : 0};\n    }\n    for (int n : {7, 8, 9, 15, 16,\
    \ 17, 1022, 1023}) assert(count_words(wide, n) == mint(2).pow(n));\n    auto compact\
    \ = minimize(digit_value_mod(100));\n    for (ll n : {1LL, 2LL, 3LL, 100LL, largest})\
    \ {\n        mint expected = n < 2 ? mint(1) : mint(10).pow(n - 2);\n        assert(count_words(compact,\
    \ n) == expected);\n    }\n    auto combined = intersect(no_equal_adjacent(),\
    \ digit_value_mod(7));\n    auto expected = direct(combined, 200);\n    for (int\
    \ n : {0, 1, 2, 19, 200}) assert(count_words(combined, n) == expected[n]);\n \
    \   for (int tc = 0; tc < 100; ++tc) {\n        vector<string> patterns;\n   \
    \     int k = rng() % 5;\n        while (k--) {\n            string pattern(rng()\
    \ % 6, 'a');\n            for (char& c : pattern) c += rng() % 2;\n          \
    \  patterns.push_back(pattern);\n        }\n        auto a = avoid_patterns<2,\
    \ 'a'>(patterns);\n        for (int n = 0; n <= 10; ++n) {\n            int expected\
    \ = 0;\n            for (int mask = 0; mask < (1 << n); ++mask) {\n          \
    \      string s(n, 'a');\n                for (int i = 0; i < n; ++i) s[i] +=\
    \ mask >> i & 1;\n                bool ok = true;\n                for (const\
    \ auto& pattern : patterns) ok &= s.find(pattern) == string::npos;\n         \
    \       expected += ok;\n            }\n            assert(count_words(a, n) ==\
    \ mint(expected));\n        }\n    }\n}\n\nint main() {\n    self_check();\n \
    \   Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\n\n#include \"../string/count_words.cpp\"\n#include \"\
    ../string/avoid_patterns.cpp\"\n#include \"../math/digit_dfa.cpp\"\n#include \"\
    ../string/dfa_minimize.cpp\"\n#include \"../util/fastio.cpp\"\n\ntemplate<int\
    \ W>\nvector<mint> direct(const DFA<W>& a, int length) {\n    vector<mint> result(length\
    \ + 1), dp(a.next.size());\n    if (a.initial == -1) return result;\n    dp[a.initial]\
    \ = 1;\n    for (int n = 0; n <= length; ++n) {\n        vector<mint> next(dp.size());\n\
    \        for (int v = 0; v < (int)dp.size(); ++v) {\n            if (a.accept[v])\
    \ result[n] += dp[v];\n            for (int to : a.next[v]) if (to != -1) next[to]\
    \ += dp[v];\n        }\n        dp.swap(next);\n    }\n    return result;\n}\n\
    \ntemplate<int W>\nmint dense(const DFA<W>& a, ll n) {\n    if (a.initial == -1)\
    \ return 0;\n    int s = a.next.size();\n    vector<vector<mint>> mat(s, vector<mint>(s));\n\
    \    for (int v = 0; v < s; ++v) for (int to : a.next[v]) if (to != -1) mat[v][to]\
    \ += 1;\n    vector<mint> dp(s);\n    dp[a.initial] = 1;\n    while (n) {\n  \
    \      if (n & 1) {\n            vector<mint> next(s);\n            for (int v\
    \ = 0; v < s; ++v) {\n                for (int to = 0; to < s; ++to) next[to]\
    \ += dp[v] * mat[v][to];\n            }\n            dp.swap(next);\n        }\n\
    \        n >>= 1;\n        if (!n) break;\n        vector<vector<mint>> next(s,\
    \ vector<mint>(s));\n        for (int i = 0; i < s; ++i) {\n            for (int\
    \ k = 0; k < s; ++k) {\n                for (int j = 0; j < s; ++j) next[i][j]\
    \ += mat[i][k] * mat[k][j];\n            }\n        }\n        mat.swap(next);\n\
    \    }\n    mint result = 0;\n    for (int v = 0; v < s; ++v) if (a.accept[v])\
    \ result += dp[v];\n    return result;\n}\n\nvoid self_check() {\n    mt19937\
    \ rng(151);\n    const ll largest = numeric_limits<ll>::max();\n    DFA<2> only_a{{{0,\
    \ -1}}, {true}, 0};\n    DFA<2> only_b{{{-1, 0}}, {true}, 0};\n    auto either\
    \ = unite(only_a, only_b);\n    auto neither = complement(either);\n    for (ll\
    \ n : {0LL, 1LL, 2LL, 8LL, 97LL, 1000000000000000000LL, largest}) {\n        mint\
    \ expected = n == 0 ? mint(1) : mint(2);\n        assert(count_words(either, n)\
    \ == expected);\n        assert(count_words(neither, n) == mint(2).pow(n) - expected);\n\
    \        assert(count_words(minimize(either), n) == expected);\n        assert(count_words(minimize(neither),\
    \ n) == mint(2).pow(n) - expected);\n    }\n    for (int tc = 0; tc < 500; ++tc)\
    \ {\n        int s = 1 + rng() % 12;\n        DFA<3> a{vector<array<int, 3>>(s),\
    \ vector<char>(s), int(rng() % (s + 1)) - 1};\n        for (int v = 0; v < s;\
    \ ++v) {\n            a.accept[v] = rng() % 2;\n            for (int& to : a.next[v])\
    \ to = int(rng() % (s + 1)) - 1;\n        }\n        auto expected = direct(a,\
    \ 97);\n        for (int n : {0, 1, 2 * s - 1, 2 * s, 2 * s + 1, 97}) {\n    \
    \        assert(count_words(a, n) == expected[n]);\n        }\n        ll n =\
    \ tc % 7 == 0 ? largest : 1000000000000000000LL - rng();\n        assert(count_words(a,\
    \ n) == dense(a, n));\n    }\n    assert(count_words(DFA<2>{}, 0) == mint(0));\n\
    \    assert(count_words(DFA<2>{}, largest) == mint(0));\n    DFA<2> empty_only{vector<array<int,\
    \ 2>>(1), {true}, 0};\n    empty_only.next[0].fill(-1);\n    assert(count_words(empty_only,\
    \ 0) == mint(1));\n    assert(count_words(empty_only, 1) == mint(0));\n    assert(count_words(empty_only,\
    \ largest) == mint(0));\n    DFA<2> chain{vector<array<int, 2>>(64), vector<char>(64),\
    \ 0};\n    chain.accept.back() = true;\n    for (int v = 0; v < 64; ++v) chain.next[v].fill(v\
    \ == 63 ? -1 : v + 1);\n    for (ll n : {0LL, 62LL, 63LL, 64LL, 127LL, 128LL,\
    \ largest}) {\n        assert(count_words(chain, n) == (n == 63 ? mint(2).pow(63)\
    \ : mint(0)));\n    }\n    for (ll n : {0LL, 1LL, 2LL, 97LL, largest}) {\n   \
    \     assert(count_words(required_digits(0), n) == mint(10).pow(n));\n    }\n\
    \    auto reject = required_digits(0);\n    reject.accept[0] = false;\n    assert(count_words(reject,\
    \ largest) == mint(0));\n    for (int tc = 0; tc < 100; ++tc) {\n        int s\
    \ = 20 + rng() % 80;\n        DFA<32> a{vector<array<int, 32>>(s), vector<char>(s),\
    \ int(rng() % s)};\n        for (int v = 0; v < s; ++v) {\n            a.accept[v]\
    \ = rng() % 2;\n            for (int& to : a.next[v]) to = rng() % 5 == 0 ? -1\
    \ : int(rng() % s);\n        }\n        auto expected = direct(a, 2 * s + 10);\n\
    \        for (int n : {1, 2, s, 2 * s + 10}) assert(count_words(a, n) == expected[n]);\n\
    \    }\n    DFA<2> wide{vector<array<int, 2>>(511), vector<char>(511, true), 0};\n\
    \    for (int v = 0; v < 511; ++v) {\n        wide.next[v] = {v < 255 ? 2 * v\
    \ + 1 : 0, v < 255 ? 2 * v + 2 : 0};\n    }\n    for (int n : {7, 8, 9, 15, 16,\
    \ 17, 1022, 1023}) assert(count_words(wide, n) == mint(2).pow(n));\n    auto compact\
    \ = minimize(digit_value_mod(100));\n    for (ll n : {1LL, 2LL, 3LL, 100LL, largest})\
    \ {\n        mint expected = n < 2 ? mint(1) : mint(10).pow(n - 2);\n        assert(count_words(compact,\
    \ n) == expected);\n    }\n    auto combined = intersect(no_equal_adjacent(),\
    \ digit_value_mod(7));\n    auto expected = direct(combined, 200);\n    for (int\
    \ n : {0, 1, 2, 19, 200}) assert(count_words(combined, n) == expected[n]);\n \
    \   for (int tc = 0; tc < 100; ++tc) {\n        vector<string> patterns;\n   \
    \     int k = rng() % 5;\n        while (k--) {\n            string pattern(rng()\
    \ % 6, 'a');\n            for (char& c : pattern) c += rng() % 2;\n          \
    \  patterns.push_back(pattern);\n        }\n        auto a = avoid_patterns<2,\
    \ 'a'>(patterns);\n        for (int n = 0; n <= 10; ++n) {\n            int expected\
    \ = 0;\n            for (int mask = 0; mask < (1 << n); ++mask) {\n          \
    \      string s(n, 'a');\n                for (int i = 0; i < n; ++i) s[i] +=\
    \ mask >> i & 1;\n                bool ok = true;\n                for (const\
    \ auto& pattern : patterns) ok &= s.find(pattern) == string::npos;\n         \
    \       expected += ok;\n            }\n            assert(count_words(a, n) ==\
    \ mint(expected));\n        }\n    }\n}\n\nint main() {\n    self_check();\n \
    \   Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n}\n"
  dependsOn:
  - string/count_words.cpp
  - string/dfa.cpp
  - fps/linear_recurrence.cpp
  - fps/nth_term.cpp
  - math/ntt.cpp
  - util/modint_base.cpp
  - math/berlekamp_massey.cpp
  - string/avoid_patterns.cpp
  - datastructure/ahocorasick.cpp
  - math/digit_dfa.cpp
  - string/dfa.cpp
  - string/dfa_minimize.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_count_words.test.cpp
  requiredBy: []
  timestamp: '2026-10-18 01:13:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_count_words.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_count_words.test.cpp
- /verify/test/yosupo_aplusb_count_words.test.cpp.html
title: test/yosupo_aplusb_count_words.test.cpp
---
