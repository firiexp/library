---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/unionfind.cpp
    title: "UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/yosupo_unionfind.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#include <iostream>\n#include <algorithm>\n#include <iomanip>\n#include <map>\n\
    #include <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n#include\
    \ <bitset>\n#include <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll =\
    \ long long;\nusing uint = uint32_t;\nusing namespace std;\n\ntemplate<class T>\
    \ constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"datastructure/unionfind.cpp\"\
    \nclass UnionFind {\n    int n;\n    vector<int> uni;\n    int forest_size;\n\
    public:\n    explicit UnionFind(int n) : n(n), uni(static_cast<uint>(n), -1),\
    \ forest_size(n) {};\n\n    int root(int a){\n        if (uni[a] < 0) return a;\n\
    \        else return (uni[a] = root(uni[a]));\n    }\n\n    bool unite(int a,\
    \ int b) {\n        a = root(a);\n        b = root(b);\n        if(a == b) return\
    \ false;\n        if(uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n\
    \        uni[b] = a;\n        forest_size--;\n        return true;\n    }\n  \
    \  int size(){ return forest_size; }\n    int size(int i){ return -uni[root(i)];\
    \ }\n    bool same(int a, int b) { return root(a) == root(b); }\n};\n\n/**\n *\
    \ @brief UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)\n * @docs\
    \ _md/unionfind.md\n */\n#line 22 \"test/yosupo_unionfind.test.cpp\"\n\nint main()\
    \ {\n    int n, q;\n    cin >> n >> q;\n    UnionFind uf(n);\n    for (int i =\
    \ 0; i < q; ++i) {\n        int t, u, v;\n        scanf(\"%d %d %d\", &t, &u,\
    \ &v);\n        if(t) printf(\"%d\\n\", uf.same(u, v));\n        else uf.unite(u,\
    \ v);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <iostream>\n#include <algorithm>\n#include <iomanip>\n#include <map>\n#include\
    \ <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n\
    #include <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\n\
    using uint = uint32_t;\nusing namespace std;\n\ntemplate<class T> constexpr T\
    \ INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../datastructure/unionfind.cpp\"\
    \n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    UnionFind uf(n);\n  \
    \  for (int i = 0; i < q; ++i) {\n        int t, u, v;\n        scanf(\"%d %d\
    \ %d\", &t, &u, &v);\n        if(t) printf(\"%d\\n\", uf.same(u, v));\n      \
    \  else uf.unite(u, v);\n    }\n    return 0;\n}"
  dependsOn:
  - datastructure/unionfind.cpp
  isVerificationFile: true
  path: test/yosupo_unionfind.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_unionfind.test.cpp
- /verify/test/yosupo_unionfind.test.cpp.html
title: test/yosupo_unionfind.test.cpp
---
