---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: datastructure/binaryindexedtree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/yosupo_point_add_range_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing\
    \ ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int n, m;\npublic:\n\
    \    BIT(int n): n(n), bit(n){\n        m = 1;\n        while(m < n) m <<= 1;\n\
    \    }\n\n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k\
    \ & -k)) ret += bit[k-1];\n        return ret;\n    }\n\n    void add(int k, T\
    \ x){\n        for (k++; k <= bit.size(); k  += (k & -k)) bit[k-1] += x;\n   \
    \ }\n\n    T lower_bound(T x){\n        int i = -1;\n        for (int j = m; j;\
    \ j >>= 1) {\n            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];\n\
    \        }\n        return i;\n    }\n};\n#line 22 \"test/yosupo_point_add_range_sum.test.cpp\"\
    \nint main() {\n    int n, q;\n    cin >> n >> q;\n    vector<int> v(n);\n   \
    \ for (auto &&i : v) scanf(\"%d\", &i);\n    BIT<ll> S(n);\n    for (int i = 0;\
    \ i < n; ++i) S.add(i, v[i]);\n\n    for (int i = 0; i < q; ++i) {\n        int\
    \ c, x, y;\n        scanf(\"%d %d %d\", &c, &x, &y);\n        if(c == 0) S.add(x,\
    \ y);\n        else printf(\"%lld\\n\", S.sum(y) - S.sum(x));\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #include \"../datastructure/binaryindexedtree.cpp\"\nint main() {\n    int n,\
    \ q;\n    cin >> n >> q;\n    vector<int> v(n);\n    for (auto &&i : v) scanf(\"\
    %d\", &i);\n    BIT<ll> S(n);\n    for (int i = 0; i < n; ++i) S.add(i, v[i]);\n\
    \n    for (int i = 0; i < q; ++i) {\n        int c, x, y;\n        scanf(\"%d\
    \ %d %d\", &c, &x, &y);\n        if(c == 0) S.add(x, y);\n        else printf(\"\
    %lld\\n\", S.sum(y) - S.sum(x));\n    }\n    return 0;\n}"
  dependsOn:
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: true
  path: test/yosupo_point_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_point_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_point_add_range_sum.test.cpp
- /verify/test/yosupo_point_add_range_sum.test.cpp.html
title: test/yosupo_point_add_range_sum.test.cpp
---
