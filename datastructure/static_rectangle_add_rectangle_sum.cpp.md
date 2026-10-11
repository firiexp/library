---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_static_rectangle_add_rectangle_sum.test.cpp
    title: test/yosupo_aplusb_static_rectangle_add_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_rectangle_add_rectangle_sum.test.cpp
    title: test/yosupo_static_rectangle_add_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9759\u7684\u306A\u9577\u65B9\u5F62\u52A0\u7B97\u30FB\u9577\u65B9\
      \u5F62\u548C"
    links: []
  bundledCode: "#line 1 \"datastructure/binaryindexedtree.cpp\"\n\n\n\ntemplate<class\
    \ T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n):\
    \ bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    explicit\
    \ BIT(const vector<T> &values): bit(values), m(1), n(values.size()) {\n      \
    \  while (m < n) m <<= 1;\n        for (int i = 1; i <= n; ++i) {\n          \
    \  int parent = i + (i & -i);\n            if (parent <= n) bit[parent - 1] +=\
    \ bit[i - 1];\n        }\n    }\n\n    T sum(int k){\n        T ret = 0;\n   \
    \     for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n        return ret;\n \
    \   }\n\n    void add(int k, T x){\n        for (k++; k <= n; k += (k & -k)) bit[k\
    \ - 1] += x;\n    }\n\n    int lower_bound(T x) {\n        if (x <= 0) return\
    \ 0;\n        int i = 0;\n        for (int j = m; j; j >>= 1) {\n            if\
    \ (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j - 1], i += j;\n        }\n\
    \        return min(i + 1, n);\n    }\n};\n\n/**\n * @brief Binary Indexed Tree(BIT)\n\
    \ */\n\n\n#line 2 \"datastructure/static_rectangle_add_rectangle_sum.cpp\"\n\n\
    template<class T>\nclass StaticRectangleAddRectangleSum {\n    struct Point {\n\
    \        int x, y;\n        T w;\n    };\n    struct Event {\n        int x, y,\
    \ id, sign;\n    };\n    struct Coefficients {\n        T w, xw, yw, xyw;\n  \
    \      Coefficients(int value = 0) : w(value), xw(value), yw(value), xyw(value)\
    \ {}\n        Coefficients& operator+=(const Coefficients& other) {\n        \
    \    w += other.w;\n            xw += other.xw;\n            yw += other.yw;\n\
    \            xyw += other.xyw;\n            return *this;\n        }\n    };\n\
    \n    vector<Point> points;\n    vector<Event> events;\n    int query_count =\
    \ 0;\n\npublic:\n    void add_rectangle(int l, int d, int r, int u, T w) {\n \
    \       if (l == r || d == u) return;\n        points.push_back({l, d, w});\n\
    \        points.push_back({l, u, -w});\n        points.push_back({r, d, -w});\n\
    \        points.push_back({r, u, w});\n    }\n\n    void add_query(int l, int\
    \ d, int r, int u) {\n        int id = query_count++;\n        if (l == r || d\
    \ == u) return;\n        events.push_back({r, u, id, 1});\n        events.push_back({l,\
    \ u, id, -1});\n        events.push_back({r, d, id, -1});\n        events.push_back({l,\
    \ d, id, 1});\n    }\n\n    vector<T> solve() const {\n        vector<T> ans(query_count,\
    \ T(0));\n        if (points.empty() || events.empty()) return ans;\n        auto\
    \ ps = points;\n        auto es = events;\n        vector<int> ys;\n        ys.reserve(ps.size());\n\
    \        for (const auto& p : ps) ys.push_back(p.y);\n        sort(ys.begin(),\
    \ ys.end());\n        ys.erase(unique(ys.begin(), ys.end()), ys.end());\n    \
    \    auto get_y = [&](int y) {\n            return (int)(lower_bound(ys.begin(),\
    \ ys.end(), y) - ys.begin());\n        };\n        sort(ps.begin(), ps.end(),\
    \ [](const Point& a, const Point& b) { return a.x < b.x; });\n        sort(es.begin(),\
    \ es.end(), [](const Event& a, const Event& b) { return a.x < b.x; });\n     \
    \   BIT<Coefficients> bit((int)ys.size());\n        int i = 0;\n        for (const\
    \ auto& e : es) {\n            while (i < (int)ps.size() && ps[i].x < e.x) {\n\
    \                const auto& p = ps[i++];\n                Coefficients c;\n \
    \               c.w = p.w;\n                c.xw = T(p.x) * p.w;\n           \
    \     c.yw = T(p.y) * p.w;\n                c.xyw = T(p.x) * c.yw;\n         \
    \       bit.add(get_y(p.y), c);\n            }\n            auto c = bit.sum(get_y(e.y));\n\
    \            T x = T(e.x), y = T(e.y);\n            T value = x * y * c.w - y\
    \ * c.xw - x * c.yw + c.xyw;\n            if (e.sign == 1) ans[e.id] += value;\n\
    \            else ans[e.id] -= value;\n        }\n        return ans;\n    }\n\
    };\n\n/**\n * @brief \u9759\u7684\u306A\u9577\u65B9\u5F62\u52A0\u7B97\u30FB\u9577\
    \u65B9\u5F62\u548C\n */\n"
  code: "#include \"binaryindexedtree.cpp\"\n\ntemplate<class T>\nclass StaticRectangleAddRectangleSum\
    \ {\n    struct Point {\n        int x, y;\n        T w;\n    };\n    struct Event\
    \ {\n        int x, y, id, sign;\n    };\n    struct Coefficients {\n        T\
    \ w, xw, yw, xyw;\n        Coefficients(int value = 0) : w(value), xw(value),\
    \ yw(value), xyw(value) {}\n        Coefficients& operator+=(const Coefficients&\
    \ other) {\n            w += other.w;\n            xw += other.xw;\n         \
    \   yw += other.yw;\n            xyw += other.xyw;\n            return *this;\n\
    \        }\n    };\n\n    vector<Point> points;\n    vector<Event> events;\n \
    \   int query_count = 0;\n\npublic:\n    void add_rectangle(int l, int d, int\
    \ r, int u, T w) {\n        if (l == r || d == u) return;\n        points.push_back({l,\
    \ d, w});\n        points.push_back({l, u, -w});\n        points.push_back({r,\
    \ d, -w});\n        points.push_back({r, u, w});\n    }\n\n    void add_query(int\
    \ l, int d, int r, int u) {\n        int id = query_count++;\n        if (l ==\
    \ r || d == u) return;\n        events.push_back({r, u, id, 1});\n        events.push_back({l,\
    \ u, id, -1});\n        events.push_back({r, d, id, -1});\n        events.push_back({l,\
    \ d, id, 1});\n    }\n\n    vector<T> solve() const {\n        vector<T> ans(query_count,\
    \ T(0));\n        if (points.empty() || events.empty()) return ans;\n        auto\
    \ ps = points;\n        auto es = events;\n        vector<int> ys;\n        ys.reserve(ps.size());\n\
    \        for (const auto& p : ps) ys.push_back(p.y);\n        sort(ys.begin(),\
    \ ys.end());\n        ys.erase(unique(ys.begin(), ys.end()), ys.end());\n    \
    \    auto get_y = [&](int y) {\n            return (int)(lower_bound(ys.begin(),\
    \ ys.end(), y) - ys.begin());\n        };\n        sort(ps.begin(), ps.end(),\
    \ [](const Point& a, const Point& b) { return a.x < b.x; });\n        sort(es.begin(),\
    \ es.end(), [](const Event& a, const Event& b) { return a.x < b.x; });\n     \
    \   BIT<Coefficients> bit((int)ys.size());\n        int i = 0;\n        for (const\
    \ auto& e : es) {\n            while (i < (int)ps.size() && ps[i].x < e.x) {\n\
    \                const auto& p = ps[i++];\n                Coefficients c;\n \
    \               c.w = p.w;\n                c.xw = T(p.x) * p.w;\n           \
    \     c.yw = T(p.y) * p.w;\n                c.xyw = T(p.x) * c.yw;\n         \
    \       bit.add(get_y(p.y), c);\n            }\n            auto c = bit.sum(get_y(e.y));\n\
    \            T x = T(e.x), y = T(e.y);\n            T value = x * y * c.w - y\
    \ * c.xw - x * c.yw + c.xyw;\n            if (e.sign == 1) ans[e.id] += value;\n\
    \            else ans[e.id] -= value;\n        }\n        return ans;\n    }\n\
    };\n\n/**\n * @brief \u9759\u7684\u306A\u9577\u65B9\u5F62\u52A0\u7B97\u30FB\u9577\
    \u65B9\u5F62\u548C\n */\n"
  dependsOn:
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: false
  path: datastructure/static_rectangle_add_rectangle_sum.cpp
  requiredBy: []
  timestamp: '2026-10-11 20:43:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_static_rectangle_add_rectangle_sum.test.cpp
  - test/yosupo_static_rectangle_add_rectangle_sum.test.cpp
documentation_of: datastructure/static_rectangle_add_rectangle_sum.cpp
layout: document
title: "\u9759\u7684\u306A\u9577\u65B9\u5F62\u52A0\u7B97\u30FB\u9577\u65B9\u5F62\u548C"
---

## 説明
長方形範囲に値を加算した後、指定した長方形内の総和をまとめて求める。
各更新では、範囲内のすべての単位セルに `w` ずつ加算する。

## できること
- `StaticRectangleAddRectangleSum<T> solver`
  加算する値と結果の型を `T` とする計算器を作る
- `void add_rectangle(int l, int d, int r, int u, T w)`
  半開長方形 $[l,r)\times[d,u)$ 内のすべての単位セルに `w` を加算する
- `void add_query(int l, int d, int r, int u)`
  半開長方形 $[l,r)\times[d,u)$ の総和を求めるクエリを登録する
- `vector<T> solve() const`
  登録されたすべての更新を反映し、クエリの登録順に答えを返す。更新数 $N$、クエリ数 $Q$ として時間 $O((N+Q)\log(N+Q+1))$、補助領域 $O(N+Q)$

## 使い方
`l <= r`、`d <= u` とする。座標と加算する値は負でもよい。
更新とクエリを登録してから `solve()` を呼ぶ。面積が $0$ の更新は影響せず、面積が $0$ のクエリの答えは `0` になる。

```cpp
StaticRectangleAddRectangleSum<long long> solver;
solver.add_rectangle(0, 0, 2, 3, 5);
solver.add_query(0, 0, 2, 3);
solver.add_query(1, 1, 3, 4);
auto ans = solver.solve();
```

この例の答えは `30, 10` となる。
`T` には `long long`、`__int128`、`modint` などを使える。座標と加算する値の積や総和を含め、途中の計算も表現できる型を選ぶ。

## 実装上の補足
更新の4隅を符号付きの点に分解し、$x$ 座標の順に走査する。
各点 $(a,b,w)$ の係数 $(w,wa,wb,wab)$ を BIT にまとめて持ち、長方形の総和を求める。
