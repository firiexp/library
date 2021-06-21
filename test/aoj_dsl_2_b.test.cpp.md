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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
  bundledCode: "#line 1 \"test/aoj_dsl_2_b.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n#include <iostream>\n#include <algorithm>\n#include <iomanip>\n#include <map>\n\
    #include <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n#include\
    \ <bitset>\n#include <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll =\
    \ long long;\nusing uint = uint32_t;\nusing namespace std;\n\ntemplate<class T>\
    \ constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int n, m;\npublic:\n\
    \    BIT(int n): n(n), bit(n){\n        m = 1;\n        while(m < n) m <<= 1;\n\
    \    }\n\n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k\
    \ & -k)) ret += bit[k-1];\n        return ret;\n    }\n\n    void add(int k, T\
    \ x){\n        for (k++; k <= bit.size(); k  += (k & -k)) bit[k-1] += x;\n   \
    \ }\n\n    T lower_bound(T x){\n        int i = -1;\n        for (int j = m; j;\
    \ j >>= 1) {\n            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];\n\
    \        }\n        return i;\n    }\n};\n#line 21 \"test/aoj_dsl_2_b.test.cpp\"\
    \n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    BIT<int> s(n);\n    for\
    \ (int i = 0; i < q; ++i) {\n        int c, x, y;\n        scanf(\"%d %d %d\"\
    , &c, &x, &y);\n        x--;\n        if(c == 0) s.add(x, y);\n        else printf(\"\
    %d\\n\", s.sum(y) - s.sum(x));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n#include <iostream>\n#include <algorithm>\n#include <iomanip>\n#include <map>\n\
    #include <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n#include\
    \ <bitset>\n#include <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll =\
    \ long long;\nusing uint = uint32_t;\nusing namespace std;\n\ntemplate<class T>\
    \ constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../datastructure/binaryindexedtree.cpp\"\
    \n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    BIT<int> s(n);\n    for\
    \ (int i = 0; i < q; ++i) {\n        int c, x, y;\n        scanf(\"%d %d %d\"\
    , &c, &x, &y);\n        x--;\n        if(c == 0) s.add(x, y);\n        else printf(\"\
    %d\\n\", s.sum(y) - s.sum(x));\n    }\n    return 0;\n}"
  dependsOn:
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: true
  path: test/aoj_dsl_2_b.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_dsl_2_b.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_dsl_2_b.test.cpp
- /verify/test/aoj_dsl_2_b.test.cpp.html
title: test/aoj_dsl_2_b.test.cpp
---
