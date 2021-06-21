---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/floor_sum.cpp
    title: math/floor_sum.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_floor_of_linear
    links:
    - https://judge.yosupo.jp/problem/sum_of_floor_of_linear
  bundledCode: "#line 1 \"test/yosupo_sum_of_floor_of_linear.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing\
    \ ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"math/floor_sum.cpp\"\
    \nll floor_sum(ll n, ll m, ll a, ll b){\n    ll ans = 0;\n    if(a >= m) {\n \
    \       ans += (n-1)*n/2*(a/m);\n        a %= m;\n    }\n    if (b >= m){\n  \
    \      ans += n*(b/m);\n        b %= m;\n    }\n    ll y = (a*n+b)/m, x = (y*m\
    \ - b);\n    if(!y) return ans;\n    ans += (n-(x+a-1)/a)*y;\n    ans += floor_sum(y,\
    \ a, m, (a - x%a)%a);\n    return ans;\n}\n#line 21 \"test/yosupo_sum_of_floor_of_linear.test.cpp\"\
    \n\nint main() {\n    int t;\n    cin >> t;\n    while(t--) {\n        ll n, m,\
    \ a, b;\n        scanf(\"%lld %lld %lld %lld\", &n, &m, &a, &b);\n        printf(\"\
    %lld\\n\", floor_sum(n, m, a, b));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #include \"../math/floor_sum.cpp\"\n\nint main() {\n    int t;\n    cin >> t;\n\
    \    while(t--) {\n        ll n, m, a, b;\n        scanf(\"%lld %lld %lld %lld\"\
    , &n, &m, &a, &b);\n        printf(\"%lld\\n\", floor_sum(n, m, a, b));\n    }\n\
    \    return 0;\n}"
  dependsOn:
  - math/floor_sum.cpp
  isVerificationFile: true
  path: test/yosupo_sum_of_floor_of_linear.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_sum_of_floor_of_linear.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_sum_of_floor_of_linear.test.cpp
- /verify/test/yosupo_sum_of_floor_of_linear.test.cpp.html
title: test/yosupo_sum_of_floor_of_linear.test.cpp
---
