---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: datastructure/binaryindexedtree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_rectangle_sum.test.cpp
    title: test/yosupo_point_add_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/point_add_rectangle_sum.cpp\"\n#include <algorithm>\n\
    #include <vector>\nusing namespace std;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k))\
    \ ret += bit[k - 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n\
    \        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T\
    \ x) {\n        if (x <= 0) return 0;\n        int i = 0;\n        for (int j\
    \ = m; j; j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i\
    \ + j - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n#line\
    \ 6 \"datastructure/point_add_rectangle_sum.cpp\"\n\ntemplate<class T>\nstruct\
    \ PointAddRectangleSum {\n    struct Operation {\n        int type;\n        int\
    \ x, y, z;\n        T w;\n    };\n\n    vector<Operation> ops;\n    vector<int>\
    \ xs;\n\n    void add_point(int x, int y, T w) {\n        ops.push_back({0, x,\
    \ y, 0, w});\n        xs.push_back(x);\n    }\n\n    void add_query(int l, int\
    \ d, int r, int u) {\n        ops.push_back({1, l, d, r, u});\n    }\n\n    vector<T>\
    \ solve() const {\n        vector<int> ord_x = xs;\n        sort(ord_x.begin(),\
    \ ord_x.end());\n        ord_x.erase(unique(ord_x.begin(), ord_x.end()), ord_x.end());\n\
    \n        int m = (int)ord_x.size();\n        vector<vector<int>> ys(m + 1);\n\
    \        for (auto op : ops) {\n            if (op.type != 0) continue;\n    \
    \        int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), op.x) - ord_x.begin())\
    \ + 1;\n            for (int x = xi; x <= m; x += x & -x) ys[x].push_back(op.y);\n\
    \        }\n        for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(),\
    \ ys[i].end());\n            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n\
    \        }\n\n        vector<BIT<T>> bit;\n        bit.reserve(m + 1);\n     \
    \   bit.emplace_back(0);\n        for (int i = 1; i <= m; ++i) bit.emplace_back((int)ys[i].size());\n\
    \n        auto add = [&](int x, int y, T w) {\n            int xi = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), x) - ord_x.begin()) + 1;\n            for (int i = xi; i <= m;\
    \ i += i & -i) {\n                int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(),\
    \ y) - ys[i].begin());\n                bit[i].add(yi, w);\n            }\n  \
    \      };\n        auto sum = [&](int x, int y) {\n            T ret = 0;\n  \
    \          int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), x) - ord_x.begin());\n\
    \            for (int i = xi; i > 0; i -= i & -i) {\n                int yi =\
    \ (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n       \
    \         ret += bit[i].sum(yi);\n            }\n            return ret;\n   \
    \     };\n\n        vector<T> ans;\n        for (auto op : ops) {\n          \
    \  if (op.type == 0) {\n                add(op.x, op.y, (T)op.w);\n          \
    \  } else {\n                ans.push_back(sum(op.z, op.w) - sum(op.z, op.y) -\
    \ sum(op.x, op.w) + sum(op.x, op.y));\n            }\n        }\n        return\
    \ ans;\n    }\n};\n"
  code: "#include <algorithm>\n#include <vector>\nusing namespace std;\n\n#include\
    \ \"binaryindexedtree.cpp\"\n\ntemplate<class T>\nstruct PointAddRectangleSum\
    \ {\n    struct Operation {\n        int type;\n        int x, y, z;\n       \
    \ T w;\n    };\n\n    vector<Operation> ops;\n    vector<int> xs;\n\n    void\
    \ add_point(int x, int y, T w) {\n        ops.push_back({0, x, y, 0, w});\n  \
    \      xs.push_back(x);\n    }\n\n    void add_query(int l, int d, int r, int\
    \ u) {\n        ops.push_back({1, l, d, r, u});\n    }\n\n    vector<T> solve()\
    \ const {\n        vector<int> ord_x = xs;\n        sort(ord_x.begin(), ord_x.end());\n\
    \        ord_x.erase(unique(ord_x.begin(), ord_x.end()), ord_x.end());\n\n   \
    \     int m = (int)ord_x.size();\n        vector<vector<int>> ys(m + 1);\n   \
    \     for (auto op : ops) {\n            if (op.type != 0) continue;\n       \
    \     int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), op.x) - ord_x.begin())\
    \ + 1;\n            for (int x = xi; x <= m; x += x & -x) ys[x].push_back(op.y);\n\
    \        }\n        for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(),\
    \ ys[i].end());\n            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n\
    \        }\n\n        vector<BIT<T>> bit;\n        bit.reserve(m + 1);\n     \
    \   bit.emplace_back(0);\n        for (int i = 1; i <= m; ++i) bit.emplace_back((int)ys[i].size());\n\
    \n        auto add = [&](int x, int y, T w) {\n            int xi = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), x) - ord_x.begin()) + 1;\n            for (int i = xi; i <= m;\
    \ i += i & -i) {\n                int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(),\
    \ y) - ys[i].begin());\n                bit[i].add(yi, w);\n            }\n  \
    \      };\n        auto sum = [&](int x, int y) {\n            T ret = 0;\n  \
    \          int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), x) - ord_x.begin());\n\
    \            for (int i = xi; i > 0; i -= i & -i) {\n                int yi =\
    \ (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n       \
    \         ret += bit[i].sum(yi);\n            }\n            return ret;\n   \
    \     };\n\n        vector<T> ans;\n        for (auto op : ops) {\n          \
    \  if (op.type == 0) {\n                add(op.x, op.y, (T)op.w);\n          \
    \  } else {\n                ans.push_back(sum(op.z, op.w) - sum(op.z, op.y) -\
    \ sum(op.x, op.w) + sum(op.x, op.y));\n            }\n        }\n        return\
    \ ans;\n    }\n};\n"
  dependsOn:
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: false
  path: datastructure/point_add_rectangle_sum.cpp
  requiredBy: []
  timestamp: '2026-03-08 18:50:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_add_rectangle_sum.test.cpp
documentation_of: datastructure/point_add_rectangle_sum.cpp
layout: document
redirect_from:
- /library/datastructure/point_add_rectangle_sum.cpp
- /library/datastructure/point_add_rectangle_sum.cpp.html
title: datastructure/point_add_rectangle_sum.cpp
---
