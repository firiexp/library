---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_line_add_get_min.test.cpp
    title: test/yosupo_line_add_get_min.test.cpp
  - icon: ':x:'
    path: test/yosupo_segment_add_get_min.test.cpp
    title: test/yosupo_segment_add_get_min.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/li_chao_tree.cpp\"\ntemplate<class T, bool\
    \ get_max = false>\nstruct LiChaoTree {\n    struct Line {\n        T a, b;\n\
    \        Line(T a = 0, T b = inf()) : a(a), b(b) {}\n        T get(T x) const\
    \ { return a * x + b; }\n    };\n\n    vector<T> xs;\n    vector<Line> seg;\n\
    \    int n;\n\n    explicit LiChaoTree(vector<T> xs) : xs(xs) {\n        sort(this->xs.begin(),\
    \ this->xs.end());\n        this->xs.erase(unique(this->xs.begin(), this->xs.end()),\
    \ this->xs.end());\n        n = (int)this->xs.size();\n        seg.assign(max(1,\
    \ 4 * n), Line());\n    }\n\n    void add_line(T a, T b) {\n        if (n == 0)\
    \ return;\n        if (get_max) a = -a, b = -b;\n        add_line_node(1, 0, n,\
    \ Line(a, b));\n    }\n\n    void add_segment(T a, T b, T l, T r) {\n        if\
    \ (n == 0 || l >= r) return;\n        if (get_max) a = -a, b = -b;\n        int\
    \ L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();\n        int R = lower_bound(xs.begin(),\
    \ xs.end(), r) - xs.begin();\n        if (L >= R) return;\n        add_segment_node(1,\
    \ 0, n, L, R, Line(a, b));\n    }\n\n    T query(T x) const {\n        if (n ==\
    \ 0) return get_max ? -inf() : inf();\n        int i = lower_bound(xs.begin(),\
    \ xs.end(), x) - xs.begin();\n        if (i == n || xs[i] != x) return get_max\
    \ ? -inf() : inf();\n        T ret = query_node(1, 0, n, i, x);\n        return\
    \ get_max ? -ret : ret;\n    }\n\nprivate:\n    static constexpr T inf() {\n \
    \       return numeric_limits<T>::max() / 4;\n    }\n\n    void add_line_node(int\
    \ k, int l, int r, Line x) {\n        int m = (l + r) / 2;\n        bool lef =\
    \ x.get(xs[l]) < seg[k].get(xs[l]);\n        bool mid = x.get(xs[m]) < seg[k].get(xs[m]);\n\
    \        if (mid) swap(seg[k], x);\n        if (r - l == 1) return;\n        if\
    \ (lef != mid) add_line_node(k * 2, l, m, x);\n        else add_line_node(k *\
    \ 2 + 1, m, r, x);\n    }\n\n    void add_segment_node(int k, int l, int r, int\
    \ a, int b, Line x) {\n        if (r <= a || b <= l) return;\n        if (a <=\
    \ l && r <= b) {\n            add_line_node(k, l, r, x);\n            return;\n\
    \        }\n        int m = (l + r) / 2;\n        add_segment_node(k * 2, l, m,\
    \ a, b, x);\n        add_segment_node(k * 2 + 1, m, r, a, b, x);\n    }\n\n  \
    \  T query_node(int k, int l, int r, int i, T x) const {\n        T ret = seg[k].get(x);\n\
    \        if (r - l == 1) return ret;\n        int m = (l + r) / 2;\n        if\
    \ (i < m) return min(ret, query_node(k * 2, l, m, i, x));\n        return min(ret,\
    \ query_node(k * 2 + 1, m, r, i, x));\n    }\n};\n\ntemplate<class T, bool get_max\
    \ = false>\nstruct OnlineLiChaoTree {\n    struct Line {\n        T a, b;\n  \
    \      Line(T a = 0, T b = inf()) : a(a), b(b) {}\n        T get(T x) const {\
    \ return a * x + b; }\n    };\n\n    struct Node {\n        Line line;\n     \
    \   int l, r;\n        explicit Node(const Line &line) : line(line), l(-1), r(-1)\
    \ {}\n    };\n\n    T low, high;\n    int root;\n    deque<Node> nodes;\n\n  \
    \  explicit OnlineLiChaoTree(T low, T high) : low(low), high(high), root(-1) {}\n\
    \n    void add_line(T a, T b) {\n        if (get_max) a = -a, b = -b;\n      \
    \  add_line(root, low, high, Line(a, b));\n    }\n\n    void add_segment(T a,\
    \ T b, T l, T r) {\n        if (l >= r) return;\n        if (get_max) a = -a,\
    \ b = -b;\n        add_segment(root, low, high, l, r, Line(a, b));\n    }\n\n\
    \    T query(T x) const {\n        T ret = query(root, low, high, x);\n      \
    \  return get_max ? -ret : ret;\n    }\n\nprivate:\n    static constexpr T inf()\
    \ {\n        return numeric_limits<T>::max() / 4;\n    }\n\n    int new_node(const\
    \ Line &line) {\n        nodes.emplace_back(line);\n        return (int)nodes.size()\
    \ - 1;\n    }\n\n    void add_line(int &t, T l, T r, Line x) {\n        if (t\
    \ == -1) {\n            t = new_node(x);\n            return;\n        }\n   \
    \     Node &node = nodes[t];\n        T m = l + (r - l) / 2;\n        bool lef\
    \ = x.get(l) < node.line.get(l);\n        bool mid = x.get(m) < node.line.get(m);\n\
    \        if (mid) swap(node.line, x);\n        if (r - l == 1) return;\n     \
    \   if (lef != mid) add_line(node.l, l, m, x);\n        else add_line(node.r,\
    \ m, r, x);\n    }\n\n    void add_segment(int &t, T l, T r, T a, T b, Line x)\
    \ {\n        if (r <= a || b <= l) return;\n        if (a <= l && r <= b) {\n\
    \            add_line(t, l, r, x);\n            return;\n        }\n        if\
    \ (t == -1) t = new_node(Line());\n        Node &node = nodes[t];\n        T m\
    \ = l + (r - l) / 2;\n        if (a < m) add_segment(node.l, l, m, a, b, x);\n\
    \        if (m < b) add_segment(node.r, m, r, a, b, x);\n    }\n\n    T query(int\
    \ t, T l, T r, T x) const {\n        T ret = inf();\n        while (t != -1) {\n\
    \            const Node &node = nodes[t];\n            ret = min(ret, node.line.get(x));\n\
    \            if (r - l == 1) break;\n            T m = l + (r - l) / 2;\n    \
    \        if (x < m) {\n                t = node.l;\n                r = m;\n \
    \           } else {\n                t = node.r;\n                l = m;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n"
  code: "template<class T, bool get_max = false>\nstruct LiChaoTree {\n    struct\
    \ Line {\n        T a, b;\n        Line(T a = 0, T b = inf()) : a(a), b(b) {}\n\
    \        T get(T x) const { return a * x + b; }\n    };\n\n    vector<T> xs;\n\
    \    vector<Line> seg;\n    int n;\n\n    explicit LiChaoTree(vector<T> xs) :\
    \ xs(xs) {\n        sort(this->xs.begin(), this->xs.end());\n        this->xs.erase(unique(this->xs.begin(),\
    \ this->xs.end()), this->xs.end());\n        n = (int)this->xs.size();\n     \
    \   seg.assign(max(1, 4 * n), Line());\n    }\n\n    void add_line(T a, T b) {\n\
    \        if (n == 0) return;\n        if (get_max) a = -a, b = -b;\n        add_line_node(1,\
    \ 0, n, Line(a, b));\n    }\n\n    void add_segment(T a, T b, T l, T r) {\n  \
    \      if (n == 0 || l >= r) return;\n        if (get_max) a = -a, b = -b;\n \
    \       int L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();\n        int\
    \ R = lower_bound(xs.begin(), xs.end(), r) - xs.begin();\n        if (L >= R)\
    \ return;\n        add_segment_node(1, 0, n, L, R, Line(a, b));\n    }\n\n   \
    \ T query(T x) const {\n        if (n == 0) return get_max ? -inf() : inf();\n\
    \        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();\n        if\
    \ (i == n || xs[i] != x) return get_max ? -inf() : inf();\n        T ret = query_node(1,\
    \ 0, n, i, x);\n        return get_max ? -ret : ret;\n    }\n\nprivate:\n    static\
    \ constexpr T inf() {\n        return numeric_limits<T>::max() / 4;\n    }\n\n\
    \    void add_line_node(int k, int l, int r, Line x) {\n        int m = (l + r)\
    \ / 2;\n        bool lef = x.get(xs[l]) < seg[k].get(xs[l]);\n        bool mid\
    \ = x.get(xs[m]) < seg[k].get(xs[m]);\n        if (mid) swap(seg[k], x);\n   \
    \     if (r - l == 1) return;\n        if (lef != mid) add_line_node(k * 2, l,\
    \ m, x);\n        else add_line_node(k * 2 + 1, m, r, x);\n    }\n\n    void add_segment_node(int\
    \ k, int l, int r, int a, int b, Line x) {\n        if (r <= a || b <= l) return;\n\
    \        if (a <= l && r <= b) {\n            add_line_node(k, l, r, x);\n   \
    \         return;\n        }\n        int m = (l + r) / 2;\n        add_segment_node(k\
    \ * 2, l, m, a, b, x);\n        add_segment_node(k * 2 + 1, m, r, a, b, x);\n\
    \    }\n\n    T query_node(int k, int l, int r, int i, T x) const {\n        T\
    \ ret = seg[k].get(x);\n        if (r - l == 1) return ret;\n        int m = (l\
    \ + r) / 2;\n        if (i < m) return min(ret, query_node(k * 2, l, m, i, x));\n\
    \        return min(ret, query_node(k * 2 + 1, m, r, i, x));\n    }\n};\n\ntemplate<class\
    \ T, bool get_max = false>\nstruct OnlineLiChaoTree {\n    struct Line {\n   \
    \     T a, b;\n        Line(T a = 0, T b = inf()) : a(a), b(b) {}\n        T get(T\
    \ x) const { return a * x + b; }\n    };\n\n    struct Node {\n        Line line;\n\
    \        int l, r;\n        explicit Node(const Line &line) : line(line), l(-1),\
    \ r(-1) {}\n    };\n\n    T low, high;\n    int root;\n    deque<Node> nodes;\n\
    \n    explicit OnlineLiChaoTree(T low, T high) : low(low), high(high), root(-1)\
    \ {}\n\n    void add_line(T a, T b) {\n        if (get_max) a = -a, b = -b;\n\
    \        add_line(root, low, high, Line(a, b));\n    }\n\n    void add_segment(T\
    \ a, T b, T l, T r) {\n        if (l >= r) return;\n        if (get_max) a = -a,\
    \ b = -b;\n        add_segment(root, low, high, l, r, Line(a, b));\n    }\n\n\
    \    T query(T x) const {\n        T ret = query(root, low, high, x);\n      \
    \  return get_max ? -ret : ret;\n    }\n\nprivate:\n    static constexpr T inf()\
    \ {\n        return numeric_limits<T>::max() / 4;\n    }\n\n    int new_node(const\
    \ Line &line) {\n        nodes.emplace_back(line);\n        return (int)nodes.size()\
    \ - 1;\n    }\n\n    void add_line(int &t, T l, T r, Line x) {\n        if (t\
    \ == -1) {\n            t = new_node(x);\n            return;\n        }\n   \
    \     Node &node = nodes[t];\n        T m = l + (r - l) / 2;\n        bool lef\
    \ = x.get(l) < node.line.get(l);\n        bool mid = x.get(m) < node.line.get(m);\n\
    \        if (mid) swap(node.line, x);\n        if (r - l == 1) return;\n     \
    \   if (lef != mid) add_line(node.l, l, m, x);\n        else add_line(node.r,\
    \ m, r, x);\n    }\n\n    void add_segment(int &t, T l, T r, T a, T b, Line x)\
    \ {\n        if (r <= a || b <= l) return;\n        if (a <= l && r <= b) {\n\
    \            add_line(t, l, r, x);\n            return;\n        }\n        if\
    \ (t == -1) t = new_node(Line());\n        Node &node = nodes[t];\n        T m\
    \ = l + (r - l) / 2;\n        if (a < m) add_segment(node.l, l, m, a, b, x);\n\
    \        if (m < b) add_segment(node.r, m, r, a, b, x);\n    }\n\n    T query(int\
    \ t, T l, T r, T x) const {\n        T ret = inf();\n        while (t != -1) {\n\
    \            const Node &node = nodes[t];\n            ret = min(ret, node.line.get(x));\n\
    \            if (r - l == 1) break;\n            T m = l + (r - l) / 2;\n    \
    \        if (x < m) {\n                t = node.l;\n                r = m;\n \
    \           } else {\n                t = node.r;\n                l = m;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/li_chao_tree.cpp
  requiredBy: []
  timestamp: '2026-03-07 18:39:01+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_line_add_get_min.test.cpp
  - test/yosupo_segment_add_get_min.test.cpp
documentation_of: datastructure/li_chao_tree.cpp
layout: document
redirect_from:
- /library/datastructure/li_chao_tree.cpp
- /library/datastructure/li_chao_tree.cpp.html
title: datastructure/li_chao_tree.cpp
---
