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
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_totient_function
    links:
    - https://judge.yosupo.jp/problem/sum_of_totient_function
  bundledCode: "#line 1 \"test/yosupo_sum_of_totient.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/sum_of_totient_function\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 998244353;\nusing ll = long long;\nusing u32 = unsigned;\nusing u64\
    \ = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr T\
    \ INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#line 1 \"util/modint.cpp\"\
    \ntemplate <u32 M>\nstruct modint {\n    u32 val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = u32(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M); }\n\
    \    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n  \
    \  modint& operator--() { if (val == 0) val = M; val--; return *this; }\n    modint\
    \ operator++(int) { modint result = *this; ++*this; return result; }\n    modint\
    \ operator--(int) { modint result = *this; --*this; return result; }\n    modint&\
    \ operator+=(const modint& b) { val += b.val; if (val >= M) val -= M; return *this;\
    \ }\n    modint& operator-=(const modint& b) { val -= b.val; if (val >= M) val\
    \ += M; return *this; }\n    modint& operator*=(const modint& b) { u64 z = val;\
    \ z *= b.val; val = (u32)(z % M); return *this; }\n    modint& operator/=(const\
    \ modint& b) { return *this = *this * b.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(M-2); }\n    friend modint operator+(const modint& a, const modint& b) {\
    \ return modint(a) += b; }\n    friend modint operator-(const modint& a, const\
    \ modint& b) { return modint(a) -= b; }\n    friend modint operator*(const modint&\
    \ a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 21\
    \ \"test/yosupo_sum_of_totient.test.cpp\"\n\nint main() {\n    ll n;\n    cin\
    \ >> n;\n    const ll k = 20000000; // 20000000\n    vector<int> dp(k+1);\n  \
    \  iota(dp.begin(),dp.end(), 0);\n    for (int i = 2; i <= k; ++i) {\n       \
    \ if(dp[i] != i) continue;\n        for (int j = i; j <= k; j += i) {\n      \
    \      dp[j] = dp[j]/i*(i-1);\n        }\n    }\n    vector<mint> a(k+1);\n  \
    \  for (int i = 0; i < k; ++i) {\n        a[i+1] = a[i] + dp[i+1];\n    }\n  \
    \  vector<mint> memo(n/k+1);\n    vector<bool> calced(n/k+1);\n    mint pp = mint(2).inv();\n\
    \    auto rec = [&](ll x, auto &&f) -> mint {\n        if(x <= k) return a[x];\n\
    \        if(calced[n/x]) return memo[n/x];\n        auto res = mint(x)*mint(x+1)*pp;\n\
    \        for (ll i = 2; i <= x; ++i) {\n            ll j = x/i, newi = (i > j\
    \ ? x/j : i);\n            res -= mint(newi-i+1)*f(x/i, f);\n            i = newi;\n\
    \        }\n        return calced[n/x] = 1, memo[n/x] = res;\n    };\n    cout\
    \ << rec(n, rec).val << \"\\n\";\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_totient_function\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 998244353;\nusing ll = long long;\nusing u32\
    \ = unsigned;\nusing u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include\
    \ \"../util/modint.cpp\"\n\nint main() {\n    ll n;\n    cin >> n;\n    const\
    \ ll k = 20000000; // 20000000\n    vector<int> dp(k+1);\n    iota(dp.begin(),dp.end(),\
    \ 0);\n    for (int i = 2; i <= k; ++i) {\n        if(dp[i] != i) continue;\n\
    \        for (int j = i; j <= k; j += i) {\n            dp[j] = dp[j]/i*(i-1);\n\
    \        }\n    }\n    vector<mint> a(k+1);\n    for (int i = 0; i < k; ++i) {\n\
    \        a[i+1] = a[i] + dp[i+1];\n    }\n    vector<mint> memo(n/k+1);\n    vector<bool>\
    \ calced(n/k+1);\n    mint pp = mint(2).inv();\n    auto rec = [&](ll x, auto\
    \ &&f) -> mint {\n        if(x <= k) return a[x];\n        if(calced[n/x]) return\
    \ memo[n/x];\n        auto res = mint(x)*mint(x+1)*pp;\n        for (ll i = 2;\
    \ i <= x; ++i) {\n            ll j = x/i, newi = (i > j ? x/j : i);\n        \
    \    res -= mint(newi-i+1)*f(x/i, f);\n            i = newi;\n        }\n    \
    \    return calced[n/x] = 1, memo[n/x] = res;\n    };\n    cout << rec(n, rec).val\
    \ << \"\\n\";\n    return 0;\n}"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_sum_of_totient.test.cpp
  requiredBy: []
  timestamp: '2021-04-04 13:04:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_sum_of_totient.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_sum_of_totient.test.cpp
- /verify/test/yosupo_sum_of_totient.test.cpp.html
title: test/yosupo_sum_of_totient.test.cpp
---
