---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/li_chao_tree.cpp
    title: datastructure/li_chao_tree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 1 \"test/yosupo_line_add_get_min.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n#include <vector>\n\
    \nusing ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    using namespace std;\n\n#line 1 \"datastructure/li_chao_tree.cpp\"\ntemplate<class\
    \ T, bool get_max = false>\nstruct LiChaoTree {\n    struct Line {\n        T\
    \ a, b;\n        Line(T a = 0, T b = inf()) : a(a), b(b) {}\n        T get(T x)\
    \ const { return a * x + b; }\n    };\n\n    vector<T> xs;\n    vector<Line> seg;\n\
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
    \          }\n        }\n        return ret;\n    }\n};\n#line 20 \"test/yosupo_line_add_get_min.test.cpp\"\
    \n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    vector<pair<ll, ll>>\
    \ init(n);\n    for (int i = 0; i < n; ++i) {\n        scanf(\"%lld %lld\", &init[i].first,\
    \ &init[i].second);\n    }\n\n    struct Query {\n        int t;\n        ll a,\
    \ b, p;\n    };\n    vector<Query> qs;\n    qs.reserve(q);\n    vector<ll> xs;\n\
    \    xs.reserve(q);\n\n    for (int i = 0; i < q; ++i) {\n        int t;\n   \
    \     scanf(\"%d\", &t);\n        if (!t) {\n            ll a, b;\n          \
    \  scanf(\"%lld %lld\", &a, &b);\n            qs.push_back({0, a, b, 0});\n  \
    \      } else {\n            ll p;\n            scanf(\"%lld\", &p);\n       \
    \     qs.push_back({1, 0, 0, p});\n            xs.push_back(p);\n        }\n \
    \   }\n\n    LiChaoTree<ll> li(xs);\n    for (auto [a, b] : init) li.add_line(a,\
    \ b);\n\n    for (auto qu : qs) {\n        if (qu.t == 0) li.add_line(qu.a, qu.b);\n\
    \        else printf(\"%lld\\n\", li.query(qu.p));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n\n\
    #include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include\
    \ <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\
    #include <vector>\n\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\nusing namespace std;\n\n#include \"../datastructure/li_chao_tree.cpp\"\
    \n\nint main() {\n    int n, q;\n    cin >> n >> q;\n    vector<pair<ll, ll>>\
    \ init(n);\n    for (int i = 0; i < n; ++i) {\n        scanf(\"%lld %lld\", &init[i].first,\
    \ &init[i].second);\n    }\n\n    struct Query {\n        int t;\n        ll a,\
    \ b, p;\n    };\n    vector<Query> qs;\n    qs.reserve(q);\n    vector<ll> xs;\n\
    \    xs.reserve(q);\n\n    for (int i = 0; i < q; ++i) {\n        int t;\n   \
    \     scanf(\"%d\", &t);\n        if (!t) {\n            ll a, b;\n          \
    \  scanf(\"%lld %lld\", &a, &b);\n            qs.push_back({0, a, b, 0});\n  \
    \      } else {\n            ll p;\n            scanf(\"%lld\", &p);\n       \
    \     qs.push_back({1, 0, 0, p});\n            xs.push_back(p);\n        }\n \
    \   }\n\n    LiChaoTree<ll> li(xs);\n    for (auto [a, b] : init) li.add_line(a,\
    \ b);\n\n    for (auto qu : qs) {\n        if (qu.t == 0) li.add_line(qu.a, qu.b);\n\
    \        else printf(\"%lld\\n\", li.query(qu.p));\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/li_chao_tree.cpp
  isVerificationFile: true
  path: test/yosupo_line_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2026-03-07 18:39:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_line_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_line_add_get_min.test.cpp
- /verify/test/yosupo_line_add_get_min.test.cpp.html
title: test/yosupo_line_add_get_min.test.cpp
---
