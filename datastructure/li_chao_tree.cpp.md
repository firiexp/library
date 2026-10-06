---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_li_chao_tree.test.cpp
    title: test/yosupo_aplusb_li_chao_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_line_add_get_min.test.cpp
    title: test/yosupo_line_add_get_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_line_add_get_min_online.test.cpp
    title: test/yosupo_line_add_get_min_online.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_segment_add_get_min.test.cpp
    title: test/yosupo_segment_add_get_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_segment_add_get_min_online.test.cpp
    title: test/yosupo_segment_add_get_min_online.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Li Chao Tree
    links: []
  bundledCode: "#line 1 \"datastructure/li_chao_tree.cpp\"\ntemplate<class T, bool\
    \ get_max = false>\nstruct LiChaoTree {\n    struct Line {\n        T a, b;\n\
    \        int id;\n        Line(T a = 0, T b = inf(), int id = -1) : a(a), b(b),\
    \ id(id) {}\n        T get(T x) const { return a * x + b; }\n        bool better(const\
    \ Line &other, T x) const {\n            return make_pair(get(x), id) < make_pair(other.get(x),\
    \ other.id);\n        }\n    };\n\n    vector<T> xs;\n    vector<Line> seg;\n\
    \    int n;\n    int next_id = 0;\n\n    explicit LiChaoTree(vector<T> xs) : xs(xs)\
    \ {\n        sort(this->xs.begin(), this->xs.end());\n        this->xs.erase(unique(this->xs.begin(),\
    \ this->xs.end()), this->xs.end());\n        n = (int)this->xs.size();\n     \
    \   seg.assign(max(1, 4 * n), Line());\n    }\n\n    int add_line(T a, T b) {\n\
    \        int id = next_id++;\n        if (n == 0) return id;\n        if (get_max)\
    \ a = -a, b = -b;\n        add_line_node(1, 0, n, Line(a, b, id));\n        return\
    \ id;\n    }\n\n    int add_segment(T a, T b, T l, T r) {\n        int id = next_id++;\n\
    \        if (n == 0 || l >= r) return id;\n        if (get_max) a = -a, b = -b;\n\
    \        int L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();\n        int\
    \ R = lower_bound(xs.begin(), xs.end(), r) - xs.begin();\n        if (L >= R)\
    \ return id;\n        add_segment_node(1, 0, n, L, R, Line(a, b, id));\n     \
    \   return id;\n    }\n\n    T query(T x) const {\n        auto ret = query_with_id(x);\n\
    \        return ret ? ret->first : (get_max ? -inf() : inf());\n    }\n\n    optional<pair<T,\
    \ int>> query_with_id(T x) const {\n        if (n == 0) return nullopt;\n    \
    \    int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();\n        if (i\
    \ == n || xs[i] != x) return nullopt;\n        auto ret = query_node(1, 0, n,\
    \ i, x);\n        if (ret && get_max) ret->first = -ret->first;\n        return\
    \ ret;\n    }\n\nprivate:\n    static constexpr T inf() {\n        return numeric_limits<T>::max()\
    \ / 4;\n    }\n\n    void add_line_node(int k, int l, int r, Line x) {\n     \
    \   if (seg[k].id == -1) {\n            seg[k] = x;\n            return;\n   \
    \     }\n        int m = (l + r) / 2;\n        bool lef = x.better(seg[k], xs[l]);\n\
    \        bool mid = x.better(seg[k], xs[m]);\n        if (mid) swap(seg[k], x);\n\
    \        if (r - l == 1) return;\n        if (lef != mid) add_line_node(k * 2,\
    \ l, m, x);\n        else add_line_node(k * 2 + 1, m, r, x);\n    }\n\n    void\
    \ add_segment_node(int k, int l, int r, int a, int b, Line x) {\n        if (r\
    \ <= a || b <= l) return;\n        if (a <= l && r <= b) {\n            add_line_node(k,\
    \ l, r, x);\n            return;\n        }\n        int m = (l + r) / 2;\n  \
    \      add_segment_node(k * 2, l, m, a, b, x);\n        add_segment_node(k * 2\
    \ + 1, m, r, a, b, x);\n    }\n\n    optional<pair<T, int>> query_node(int k,\
    \ int l, int r, int i, T x) const {\n        optional<pair<T, int>> ret;\n   \
    \     if (seg[k].id != -1) ret = make_pair(seg[k].get(x), seg[k].id);\n      \
    \  if (r - l == 1) return ret;\n        int m = (l + r) / 2;\n        auto child\
    \ = i < m ? query_node(k * 2, l, m, i, x)\n                          : query_node(k\
    \ * 2 + 1, m, r, i, x);\n        if (child && (!ret || *child < *ret)) ret = child;\n\
    \        return ret;\n    }\n};\n\ntemplate<class T, bool get_max = false>\nstruct\
    \ OnlineLiChaoTree {\n    struct Line {\n        T a, b;\n        int id;\n  \
    \      Line(T a = 0, T b = inf(), int id = -1) : a(a), b(b), id(id) {}\n     \
    \   T get(T x) const { return a * x + b; }\n        bool better(const Line &other,\
    \ T x) const {\n            return make_pair(get(x), id) < make_pair(other.get(x),\
    \ other.id);\n        }\n    };\n\n    struct Node {\n        Line line;\n   \
    \     int l, r;\n        explicit Node(const Line &line) : line(line), l(-1),\
    \ r(-1) {}\n    };\n\n    T low, high;\n    int root;\n    int next_id = 0;\n\
    \    deque<Node> nodes;\n\n    explicit OnlineLiChaoTree(T low, T high) : low(low),\
    \ high(high), root(-1) {}\n\n    int add_line(T a, T b) {\n        int id = next_id++;\n\
    \        if (get_max) a = -a, b = -b;\n        add_line(root, low, high, Line(a,\
    \ b, id));\n        return id;\n    }\n\n    int add_segment(T a, T b, T l, T\
    \ r) {\n        int id = next_id++;\n        if (l >= r) return id;\n        if\
    \ (get_max) a = -a, b = -b;\n        add_segment(root, low, high, l, r, Line(a,\
    \ b, id));\n        return id;\n    }\n\n    T query(T x) const {\n        auto\
    \ ret = query_with_id(x);\n        return ret ? ret->first : (get_max ? -inf()\
    \ : inf());\n    }\n\n    optional<pair<T, int>> query_with_id(T x) const {\n\
    \        auto ret = query(root, low, high, x);\n        if (ret && get_max) ret->first\
    \ = -ret->first;\n        return ret;\n    }\n\nprivate:\n    static constexpr\
    \ T inf() {\n        return numeric_limits<T>::max() / 4;\n    }\n\n    int new_node(const\
    \ Line &line) {\n        nodes.emplace_back(line);\n        return (int)nodes.size()\
    \ - 1;\n    }\n\n    void add_line(int &t, T l, T r, Line x) {\n        if (t\
    \ == -1) {\n            t = new_node(x);\n            return;\n        }\n   \
    \     Node &node = nodes[t];\n        if (node.line.id == -1) {\n            node.line\
    \ = x;\n            return;\n        }\n        T m = l + (r - l) / 2;\n     \
    \   bool lef = x.better(node.line, l);\n        bool mid = x.better(node.line,\
    \ m);\n        if (mid) swap(node.line, x);\n        if (r - l == 1) return;\n\
    \        if (lef != mid) add_line(node.l, l, m, x);\n        else if (x.better(node.line,\
    \ r - 1)) add_line(node.r, m, r, x);\n    }\n\n    void add_segment(int &t, T\
    \ l, T r, T a, T b, Line x) {\n        if (r <= a || b <= l) return;\n       \
    \ if (a <= l && r <= b) {\n            add_line(t, l, r, x);\n            return;\n\
    \        }\n        if (t == -1) t = new_node(Line());\n        Node &node = nodes[t];\n\
    \        T m = l + (r - l) / 2;\n        if (a < m) add_segment(node.l, l, m,\
    \ a, b, x);\n        if (m < b) add_segment(node.r, m, r, a, b, x);\n    }\n\n\
    \    optional<pair<T, int>> query(int t, T l, T r, T x) const {\n        optional<pair<T,\
    \ int>> ret;\n        while (t != -1) {\n            const Node &node = nodes[t];\n\
    \            if (node.line.id != -1) {\n                auto value = make_pair(node.line.get(x),\
    \ node.line.id);\n                if (!ret || value < *ret) ret = value;\n   \
    \         }\n            if (r - l == 1) break;\n            T m = l + (r - l)\
    \ / 2;\n            if (x < m) {\n                t = node.l;\n              \
    \  r = m;\n            } else {\n                t = node.r;\n               \
    \ l = m;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n *\
    \ @brief Li Chao Tree\n */\n"
  code: "template<class T, bool get_max = false>\nstruct LiChaoTree {\n    struct\
    \ Line {\n        T a, b;\n        int id;\n        Line(T a = 0, T b = inf(),\
    \ int id = -1) : a(a), b(b), id(id) {}\n        T get(T x) const { return a *\
    \ x + b; }\n        bool better(const Line &other, T x) const {\n            return\
    \ make_pair(get(x), id) < make_pair(other.get(x), other.id);\n        }\n    };\n\
    \n    vector<T> xs;\n    vector<Line> seg;\n    int n;\n    int next_id = 0;\n\
    \n    explicit LiChaoTree(vector<T> xs) : xs(xs) {\n        sort(this->xs.begin(),\
    \ this->xs.end());\n        this->xs.erase(unique(this->xs.begin(), this->xs.end()),\
    \ this->xs.end());\n        n = (int)this->xs.size();\n        seg.assign(max(1,\
    \ 4 * n), Line());\n    }\n\n    int add_line(T a, T b) {\n        int id = next_id++;\n\
    \        if (n == 0) return id;\n        if (get_max) a = -a, b = -b;\n      \
    \  add_line_node(1, 0, n, Line(a, b, id));\n        return id;\n    }\n\n    int\
    \ add_segment(T a, T b, T l, T r) {\n        int id = next_id++;\n        if (n\
    \ == 0 || l >= r) return id;\n        if (get_max) a = -a, b = -b;\n        int\
    \ L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();\n        int R = lower_bound(xs.begin(),\
    \ xs.end(), r) - xs.begin();\n        if (L >= R) return id;\n        add_segment_node(1,\
    \ 0, n, L, R, Line(a, b, id));\n        return id;\n    }\n\n    T query(T x)\
    \ const {\n        auto ret = query_with_id(x);\n        return ret ? ret->first\
    \ : (get_max ? -inf() : inf());\n    }\n\n    optional<pair<T, int>> query_with_id(T\
    \ x) const {\n        if (n == 0) return nullopt;\n        int i = lower_bound(xs.begin(),\
    \ xs.end(), x) - xs.begin();\n        if (i == n || xs[i] != x) return nullopt;\n\
    \        auto ret = query_node(1, 0, n, i, x);\n        if (ret && get_max) ret->first\
    \ = -ret->first;\n        return ret;\n    }\n\nprivate:\n    static constexpr\
    \ T inf() {\n        return numeric_limits<T>::max() / 4;\n    }\n\n    void add_line_node(int\
    \ k, int l, int r, Line x) {\n        if (seg[k].id == -1) {\n            seg[k]\
    \ = x;\n            return;\n        }\n        int m = (l + r) / 2;\n       \
    \ bool lef = x.better(seg[k], xs[l]);\n        bool mid = x.better(seg[k], xs[m]);\n\
    \        if (mid) swap(seg[k], x);\n        if (r - l == 1) return;\n        if\
    \ (lef != mid) add_line_node(k * 2, l, m, x);\n        else add_line_node(k *\
    \ 2 + 1, m, r, x);\n    }\n\n    void add_segment_node(int k, int l, int r, int\
    \ a, int b, Line x) {\n        if (r <= a || b <= l) return;\n        if (a <=\
    \ l && r <= b) {\n            add_line_node(k, l, r, x);\n            return;\n\
    \        }\n        int m = (l + r) / 2;\n        add_segment_node(k * 2, l, m,\
    \ a, b, x);\n        add_segment_node(k * 2 + 1, m, r, a, b, x);\n    }\n\n  \
    \  optional<pair<T, int>> query_node(int k, int l, int r, int i, T x) const {\n\
    \        optional<pair<T, int>> ret;\n        if (seg[k].id != -1) ret = make_pair(seg[k].get(x),\
    \ seg[k].id);\n        if (r - l == 1) return ret;\n        int m = (l + r) /\
    \ 2;\n        auto child = i < m ? query_node(k * 2, l, m, i, x)\n           \
    \               : query_node(k * 2 + 1, m, r, i, x);\n        if (child && (!ret\
    \ || *child < *ret)) ret = child;\n        return ret;\n    }\n};\n\ntemplate<class\
    \ T, bool get_max = false>\nstruct OnlineLiChaoTree {\n    struct Line {\n   \
    \     T a, b;\n        int id;\n        Line(T a = 0, T b = inf(), int id = -1)\
    \ : a(a), b(b), id(id) {}\n        T get(T x) const { return a * x + b; }\n  \
    \      bool better(const Line &other, T x) const {\n            return make_pair(get(x),\
    \ id) < make_pair(other.get(x), other.id);\n        }\n    };\n\n    struct Node\
    \ {\n        Line line;\n        int l, r;\n        explicit Node(const Line &line)\
    \ : line(line), l(-1), r(-1) {}\n    };\n\n    T low, high;\n    int root;\n \
    \   int next_id = 0;\n    deque<Node> nodes;\n\n    explicit OnlineLiChaoTree(T\
    \ low, T high) : low(low), high(high), root(-1) {}\n\n    int add_line(T a, T\
    \ b) {\n        int id = next_id++;\n        if (get_max) a = -a, b = -b;\n  \
    \      add_line(root, low, high, Line(a, b, id));\n        return id;\n    }\n\
    \n    int add_segment(T a, T b, T l, T r) {\n        int id = next_id++;\n   \
    \     if (l >= r) return id;\n        if (get_max) a = -a, b = -b;\n        add_segment(root,\
    \ low, high, l, r, Line(a, b, id));\n        return id;\n    }\n\n    T query(T\
    \ x) const {\n        auto ret = query_with_id(x);\n        return ret ? ret->first\
    \ : (get_max ? -inf() : inf());\n    }\n\n    optional<pair<T, int>> query_with_id(T\
    \ x) const {\n        auto ret = query(root, low, high, x);\n        if (ret &&\
    \ get_max) ret->first = -ret->first;\n        return ret;\n    }\n\nprivate:\n\
    \    static constexpr T inf() {\n        return numeric_limits<T>::max() / 4;\n\
    \    }\n\n    int new_node(const Line &line) {\n        nodes.emplace_back(line);\n\
    \        return (int)nodes.size() - 1;\n    }\n\n    void add_line(int &t, T l,\
    \ T r, Line x) {\n        if (t == -1) {\n            t = new_node(x);\n     \
    \       return;\n        }\n        Node &node = nodes[t];\n        if (node.line.id\
    \ == -1) {\n            node.line = x;\n            return;\n        }\n     \
    \   T m = l + (r - l) / 2;\n        bool lef = x.better(node.line, l);\n     \
    \   bool mid = x.better(node.line, m);\n        if (mid) swap(node.line, x);\n\
    \        if (r - l == 1) return;\n        if (lef != mid) add_line(node.l, l,\
    \ m, x);\n        else if (x.better(node.line, r - 1)) add_line(node.r, m, r,\
    \ x);\n    }\n\n    void add_segment(int &t, T l, T r, T a, T b, Line x) {\n \
    \       if (r <= a || b <= l) return;\n        if (a <= l && r <= b) {\n     \
    \       add_line(t, l, r, x);\n            return;\n        }\n        if (t ==\
    \ -1) t = new_node(Line());\n        Node &node = nodes[t];\n        T m = l +\
    \ (r - l) / 2;\n        if (a < m) add_segment(node.l, l, m, a, b, x);\n     \
    \   if (m < b) add_segment(node.r, m, r, a, b, x);\n    }\n\n    optional<pair<T,\
    \ int>> query(int t, T l, T r, T x) const {\n        optional<pair<T, int>> ret;\n\
    \        while (t != -1) {\n            const Node &node = nodes[t];\n       \
    \     if (node.line.id != -1) {\n                auto value = make_pair(node.line.get(x),\
    \ node.line.id);\n                if (!ret || value < *ret) ret = value;\n   \
    \         }\n            if (r - l == 1) break;\n            T m = l + (r - l)\
    \ / 2;\n            if (x < m) {\n                t = node.l;\n              \
    \  r = m;\n            } else {\n                t = node.r;\n               \
    \ l = m;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n *\
    \ @brief Li Chao Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/li_chao_tree.cpp
  requiredBy: []
  timestamp: '2026-10-06 23:51:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_segment_add_get_min.test.cpp
  - test/yosupo_line_add_get_min.test.cpp
  - test/yosupo_line_add_get_min_online.test.cpp
  - test/yosupo_segment_add_get_min_online.test.cpp
  - test/yosupo_aplusb_li_chao_tree.test.cpp
date: 2026-03-07
documentation_of: datastructure/li_chao_tree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Li Chao Tree
---

## 説明
直線集合に対して、1点での最小値(または最大値)クエリを処理する。
最適な直線の ID も取得できる。同じ評価値なら、先に追加した直線を選ぶ。

登録座標数を $N$、オンライン版の整数区間長を $C$ とする。
直線追加・クエリはオフライン版で $O(\log N)$、オンライン版で $O(\log C)$。
区間直線追加はそれぞれ $O(\log^2 N)$、$O(\log^2 C)$。

## できること
- `LiChaoTree<T, false>(xs)` : オフライン版（`xs` に含まれる座標でのみクエリ可能）
- `OnlineLiChaoTree<T, false>(low, high)` : オンライン版（区間 `[low, high)`）
- `int add_line(a, b)` : 直線 `y = ax + b` を追加し、その ID を返す
- `int add_segment(a, b, l, r)` : 区間 `[l, r)` のみ有効な直線 `y = ax + b` を追加し、その ID を返す
- `query(x)` : 座標 `x` での最小値を返す。有効な直線がない場合は `numeric_limits<T>::max() / 4`、最大値版ではその符号を反転した値を返す
- `optional<pair<T, int>> query_with_id(x)` : 最適な「評価値, ID」を返す。有効な直線がない場合は `nullopt`。同値なら小さい ID を返す

`LiChaoTree<T, true>` / `OnlineLiChaoTree<T, true>` を使うと最大値クエリになる。
ID は両方の追加操作を通して 0 から順に発行する。空区間や登録座標を含まない区間への追加でも ID を発行する。
オフライン版の未登録座標では `query_with_id` は `nullopt`、`query` は空集合の番兵を返す。

## 使い方
追加時に返る ID と遷移元の状態を対応付けると、最適値とともに遷移元を復元できる。

```cpp
LiChaoTree<long long> tree({0, 2, 5});
vector<int> source;
int id = tree.add_line(3, 1);
source.resize(id + 1);
source[id] = 7;
auto result = tree.query_with_id(2);
if (result) {
    auto [value, line_id] = *result;
    int parent = source[line_id];
}
```

## 実装上の補足
直線の評価に必要な乗算・加算と、最大値版の係数・評価値の符号反転は `T` に収まる必要がある。
オンライン版は整数区間を扱い、`low < high`、`high - low` が `T` に収まることを前提とする。クエリは `[low, high)` 内で行う。
有効な直線の評価値には、空集合を表す番兵による上限・下限はない。
各直線に `int` の ID を持つ。`T` のアラインメントにより、ID のサイズ以上に保持領域が増える場合がある。
