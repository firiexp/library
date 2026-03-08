---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_static_rectangle_sum.test.cpp
    title: test/yosupo_static_rectangle_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/static_rectangle_sum.md
    document_title: "\u9759\u7684\u9577\u65B9\u5F62\u548C(Static Rectangle Sum)"
    links: []
  bundledCode: "#line 1 \"datastructure/static_rectangle_sum.cpp\"\n#include <algorithm>\n\
    #include <vector>\nusing namespace std;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k))\
    \ ret += bit[k - 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n\
    \        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T\
    \ x) {\n        if (x <= 0) return 0;\n        int i = 0;\n        for (int j\
    \ = m; j; j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i\
    \ + j - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n\
    \ * @brief Binary Indexed Tree(BIT)\n * @docs _md/binaryindexedtree.md\n */\n\
    #line 6 \"datastructure/static_rectangle_sum.cpp\"\n\ntemplate<class T>\nstruct\
    \ StaticRectangleSum {\n    struct Point {\n        int x, y;\n        T w;\n\
    \    };\n\n    struct Event {\n        int x, d, u, id, sign;\n\n        bool\
    \ operator<(const Event& other) const {\n            return x < other.x;\n   \
    \     }\n    };\n\n    vector<Point> points;\n    vector<Event> events;\n    vector<int>\
    \ ys;\n\n    void add_point(int x, int y, T w) {\n        points.push_back({x,\
    \ y, w});\n        ys.push_back(y);\n    }\n\n    void add_query(int l, int d,\
    \ int r, int u) {\n        int id = (int)events.size() / 2;\n        events.push_back({r,\
    \ d, u, id, 1});\n        events.push_back({l, d, u, id, -1});\n        ys.push_back(d);\n\
    \        ys.push_back(u);\n    }\n\n    vector<T> solve() {\n        vector<int>\
    \ ord_y = ys;\n        sort(ord_y.begin(), ord_y.end());\n        ord_y.erase(unique(ord_y.begin(),\
    \ ord_y.end()), ord_y.end());\n\n        auto get_y = [&](int y) {\n         \
    \   return (int)(lower_bound(ord_y.begin(), ord_y.end(), y) - ord_y.begin());\n\
    \        };\n\n        vector<Point> ps = points;\n        for (auto& p : ps)\
    \ p.y = get_y(p.y);\n        for (auto& e : events) {\n            e.d = get_y(e.d);\n\
    \            e.u = get_y(e.u);\n        }\n\n        sort(ps.begin(), ps.end(),\
    \ [](const Point& a, const Point& b) {\n            return a.x < b.x;\n      \
    \  });\n        sort(events.begin(), events.end());\n\n        int q = (int)events.size()\
    \ / 2;\n        vector<T> ans(q, 0);\n        BIT<T> bit((int)ord_y.size());\n\
    \        int i = 0;\n        for (auto e : events) {\n            while (i < (int)ps.size()\
    \ && ps[i].x < e.x) {\n                bit.add(ps[i].y, ps[i].w);\n          \
    \      ++i;\n            }\n            ans[e.id] += (bit.sum(e.u) - bit.sum(e.d))\
    \ * e.sign;\n        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u9759\
    \u7684\u9577\u65B9\u5F62\u548C(Static Rectangle Sum)\n * @docs _md/static_rectangle_sum.md\n\
    \ */\n"
  code: "#include <algorithm>\n#include <vector>\nusing namespace std;\n\n#include\
    \ \"binaryindexedtree.cpp\"\n\ntemplate<class T>\nstruct StaticRectangleSum {\n\
    \    struct Point {\n        int x, y;\n        T w;\n    };\n\n    struct Event\
    \ {\n        int x, d, u, id, sign;\n\n        bool operator<(const Event& other)\
    \ const {\n            return x < other.x;\n        }\n    };\n\n    vector<Point>\
    \ points;\n    vector<Event> events;\n    vector<int> ys;\n\n    void add_point(int\
    \ x, int y, T w) {\n        points.push_back({x, y, w});\n        ys.push_back(y);\n\
    \    }\n\n    void add_query(int l, int d, int r, int u) {\n        int id = (int)events.size()\
    \ / 2;\n        events.push_back({r, d, u, id, 1});\n        events.push_back({l,\
    \ d, u, id, -1});\n        ys.push_back(d);\n        ys.push_back(u);\n    }\n\
    \n    vector<T> solve() {\n        vector<int> ord_y = ys;\n        sort(ord_y.begin(),\
    \ ord_y.end());\n        ord_y.erase(unique(ord_y.begin(), ord_y.end()), ord_y.end());\n\
    \n        auto get_y = [&](int y) {\n            return (int)(lower_bound(ord_y.begin(),\
    \ ord_y.end(), y) - ord_y.begin());\n        };\n\n        vector<Point> ps =\
    \ points;\n        for (auto& p : ps) p.y = get_y(p.y);\n        for (auto& e\
    \ : events) {\n            e.d = get_y(e.d);\n            e.u = get_y(e.u);\n\
    \        }\n\n        sort(ps.begin(), ps.end(), [](const Point& a, const Point&\
    \ b) {\n            return a.x < b.x;\n        });\n        sort(events.begin(),\
    \ events.end());\n\n        int q = (int)events.size() / 2;\n        vector<T>\
    \ ans(q, 0);\n        BIT<T> bit((int)ord_y.size());\n        int i = 0;\n   \
    \     for (auto e : events) {\n            while (i < (int)ps.size() && ps[i].x\
    \ < e.x) {\n                bit.add(ps[i].y, ps[i].w);\n                ++i;\n\
    \            }\n            ans[e.id] += (bit.sum(e.u) - bit.sum(e.d)) * e.sign;\n\
    \        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u9759\u7684\u9577\
    \u65B9\u5F62\u548C(Static Rectangle Sum)\n * @docs _md/static_rectangle_sum.md\n\
    \ */\n"
  dependsOn:
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: false
  path: datastructure/static_rectangle_sum.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_static_rectangle_sum.test.cpp
documentation_of: datastructure/static_rectangle_sum.cpp
layout: document
redirect_from:
- /library/datastructure/static_rectangle_sum.cpp
- /library/datastructure/static_rectangle_sum.cpp.html
title: "\u9759\u7684\u9577\u65B9\u5F62\u548C(Static Rectangle Sum)"
---
---
layout: post
title: Static Rectangle Sum
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
静的な重み付き点集合に対して、長方形内の重み和をまとめて処理する。
`x` 方向の sweep と `y` 上の BIT を使う。

## できること
- `StaticRectangleSum<T> solver`
  空の solver を作る
- `void add_point(int x, int y, T w)`
  点 `(x, y)` に重み `w` を追加する
- `void add_query(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` のクエリを追加する
- `vector<T> solve()`
  追加順に各クエリの重み和を返す

## 使い方
先に点とクエリを全部追加してから `solve()` を呼ぶ。
`y` 座標は内部で座圧し、各クエリを `x < r` と `x < l` の差に分解して処理する。
