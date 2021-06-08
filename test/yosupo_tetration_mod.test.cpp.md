---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/tetration.cpp
    title: math/tetration.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tetration_mod
    links:
    - https://judge.yosupo.jp/problem/tetration_mod
  bundledCode: "#line 1 \"test/yosupo_tetration_mod.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/tetration_mod\"\n#include <iostream>\n#include\
    \ <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include <stack>\n\
    #include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const int MOD\
    \ = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\nusing u64 = unsigned\
    \ long long;\nusing namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#line 1 \"math/tetration.cpp\"\nll totient(ll n){\n    ll\
    \ res = n;\n    for (ll i = 2; i*i <= n; ++i) {\n        if(n%i == 0){\n     \
    \       res = res/i*(i-1);\n            while(n%i == 0) n /= i;\n        }\n \
    \   }\n    if(n > 1) res = res/n*(n-1);\n    return res;\n}\n\ntemplate <class\
    \ T>\nT pow_tetration(T x, T n, T M, bool &yojo){\n    uint64_t u = 1, xx = x;\n\
    \    if(x >= M) yojo = true;\n    while (n > 0){\n        if (n&1) {\n       \
    \     u = u * xx;  \n            if(u >= M) yojo = true, u %= M;\n        }\n\
    \        if(!(n >>= 1)) break;\n        xx = xx * xx;\n        if(xx >= M) yojo\
    \ = true, xx %= M;\n    }\n    return static_cast<T>(u);\n};\n\nll tetration(ll\
    \ a, ll n, const ll M, bool &yojo) {\n    if(a == 0) return !(n&1);\n    if(M\
    \ == 1) return yojo = true, 1;\n    if(a == 1 || n == 0) return 1;\n    ll expo\
    \ = tetration(a, n-1, totient(M), yojo);\n    ll res = pow_tetration(a, expo,\
    \ M, yojo);\n    return res + (yojo ? M : 0);\n}\n\nll tetration(ll a, ll n, const\
    \ ll M){\n    bool yojo = false;\n    return tetration(a, n, M, yojo)%M;\n}\n\
    #line 21 \"test/yosupo_tetration_mod.test.cpp\"\nint main() {\n    int t;\n  \
    \  cin >> t;\n    while(t--){\n        int a, b, m;\n        scanf(\"%d %d %d\"\
    , &a, &b, &m);\n        printf(\"%lld\\n\", tetration(a, b, m));\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tetration_mod\"\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\n\
    using u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include \"../math/tetration.cpp\"\
    \nint main() {\n    int t;\n    cin >> t;\n    while(t--){\n        int a, b,\
    \ m;\n        scanf(\"%d %d %d\", &a, &b, &m);\n        printf(\"%lld\\n\", tetration(a,\
    \ b, m));\n    }\n    return 0;\n}"
  dependsOn:
  - math/tetration.cpp
  isVerificationFile: true
  path: test/yosupo_tetration_mod.test.cpp
  requiredBy: []
  timestamp: '2021-06-09 00:29:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_tetration_mod.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_tetration_mod.test.cpp
- /verify/test/yosupo_tetration_mod.test.cpp.html
title: test/yosupo_tetration_mod.test.cpp
---
