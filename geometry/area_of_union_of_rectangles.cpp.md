---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_area_of_union_of_rectangles.test.cpp
    title: test/yosupo_area_of_union_of_rectangles.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9577\u65B9\u5F62\u548C\u96C6\u5408\u9762\u7A4D(Area of Union\
      \ of Rectangles)"
    links: []
  bundledCode: "#line 1 \"geometry/area_of_union_of_rectangles.cpp\"\nusing namespace\
    \ std;\n\ntemplate<class Coord = long long, class Area = long long>\nstruct AreaOfUnionOfRectangles\
    \ {\n    struct Rectangle {\n        Coord l, d, r, u;\n    };\n\n    struct Event\
    \ {\n        Coord x;\n        int yl, yr;\n        int delta;\n\n        bool\
    \ operator<(const Event &other) const {\n            return x < other.x;\n   \
    \     }\n    };\n\n    struct SegmentTree {\n        int n, sz;\n        vector<int>\
    \ cnt;\n        vector<Area> len;\n        vector<Area> total;\n\n        explicit\
    \ SegmentTree(const vector<Coord> &ys) : n((int)ys.size() - 1), sz(1) {\n    \
    \        while (sz < n) sz <<= 1;\n            cnt.assign(sz << 1, 0);\n     \
    \       len.assign(sz << 1, 0);\n            total.assign(sz << 1, 0);\n     \
    \       for (int i = 0; i < n; ++i) {\n                total[sz + i] = Area(ys[i\
    \ + 1]) - Area(ys[i]);\n            }\n            for (int k = sz - 1; k > 0;\
    \ --k) total[k] = total[k << 1] + total[k << 1 | 1];\n        }\n\n        void\
    \ apply(int k, int x) {\n            cnt[k] += x;\n            pull(k);\n    \
    \    }\n\n        void pull(int k) {\n            if (cnt[k] > 0) {\n        \
    \        len[k] = total[k];\n            } else if (k < sz) {\n              \
    \  len[k] = len[k << 1] + len[k << 1 | 1];\n            } else {\n           \
    \     len[k] = 0;\n            }\n        }\n\n        void update(int a, int\
    \ b, int x) {\n            if (a >= b) return;\n            a += sz;\n       \
    \     b += sz;\n            int left = a;\n            int right = b - 1;\n  \
    \          for (; a < b; a >>= 1, b >>= 1) {\n                if (a & 1) apply(a++,\
    \ x);\n                if (b & 1) apply(--b, x);\n            }\n            while\
    \ (left >>= 1) pull(left);\n            while (right >>= 1) pull(right);\n   \
    \     }\n\n        Area covered_length() const {\n            return len[1];\n\
    \        }\n    };\n\n    vector<Rectangle> rects;\n    vector<Coord> ys;\n\n\
    \    void add_rectangle(Coord l, Coord d, Coord r, Coord u) {\n        if (l >=\
    \ r || d >= u) return;\n        rects.push_back({l, d, r, u});\n        ys.push_back(d);\n\
    \        ys.push_back(u);\n    }\n\n    Area solve() const {\n        if (rects.empty())\
    \ return 0;\n\n        vector<Coord> ord_y = ys;\n        sort(ord_y.begin(),\
    \ ord_y.end());\n        ord_y.erase(unique(ord_y.begin(), ord_y.end()), ord_y.end());\n\
    \        if ((int)ord_y.size() <= 1) return 0;\n\n        vector<Event> events;\n\
    \        events.reserve(rects.size() * 2);\n        for (auto &&rect : rects)\
    \ {\n            int d = (int)(lower_bound(ord_y.begin(), ord_y.end(), rect.d)\
    \ - ord_y.begin());\n            int u = (int)(lower_bound(ord_y.begin(), ord_y.end(),\
    \ rect.u) - ord_y.begin());\n            events.push_back({rect.l, d, u, 1});\n\
    \            events.push_back({rect.r, d, u, -1});\n        }\n        sort(events.begin(),\
    \ events.end());\n\n        SegmentTree seg(ord_y);\n        Area ans = 0;\n \
    \       Coord prev_x = events[0].x;\n        int i = 0;\n        while (i < (int)events.size())\
    \ {\n            Coord x = events[i].x;\n            ans += seg.covered_length()\
    \ * Area(x - prev_x);\n            while (i < (int)events.size() && events[i].x\
    \ == x) {\n                seg.update(events[i].yl, events[i].yr, events[i].delta);\n\
    \                ++i;\n            }\n            prev_x = x;\n        }\n   \
    \     return ans;\n    }\n};\n\n/**\n * @brief \u9577\u65B9\u5F62\u548C\u96C6\u5408\
    \u9762\u7A4D(Area of Union of Rectangles)\n */\n"
  code: "using namespace std;\n\ntemplate<class Coord = long long, class Area = long\
    \ long>\nstruct AreaOfUnionOfRectangles {\n    struct Rectangle {\n        Coord\
    \ l, d, r, u;\n    };\n\n    struct Event {\n        Coord x;\n        int yl,\
    \ yr;\n        int delta;\n\n        bool operator<(const Event &other) const\
    \ {\n            return x < other.x;\n        }\n    };\n\n    struct SegmentTree\
    \ {\n        int n, sz;\n        vector<int> cnt;\n        vector<Area> len;\n\
    \        vector<Area> total;\n\n        explicit SegmentTree(const vector<Coord>\
    \ &ys) : n((int)ys.size() - 1), sz(1) {\n            while (sz < n) sz <<= 1;\n\
    \            cnt.assign(sz << 1, 0);\n            len.assign(sz << 1, 0);\n  \
    \          total.assign(sz << 1, 0);\n            for (int i = 0; i < n; ++i)\
    \ {\n                total[sz + i] = Area(ys[i + 1]) - Area(ys[i]);\n        \
    \    }\n            for (int k = sz - 1; k > 0; --k) total[k] = total[k << 1]\
    \ + total[k << 1 | 1];\n        }\n\n        void apply(int k, int x) {\n    \
    \        cnt[k] += x;\n            pull(k);\n        }\n\n        void pull(int\
    \ k) {\n            if (cnt[k] > 0) {\n                len[k] = total[k];\n  \
    \          } else if (k < sz) {\n                len[k] = len[k << 1] + len[k\
    \ << 1 | 1];\n            } else {\n                len[k] = 0;\n            }\n\
    \        }\n\n        void update(int a, int b, int x) {\n            if (a >=\
    \ b) return;\n            a += sz;\n            b += sz;\n            int left\
    \ = a;\n            int right = b - 1;\n            for (; a < b; a >>= 1, b >>=\
    \ 1) {\n                if (a & 1) apply(a++, x);\n                if (b & 1)\
    \ apply(--b, x);\n            }\n            while (left >>= 1) pull(left);\n\
    \            while (right >>= 1) pull(right);\n        }\n\n        Area covered_length()\
    \ const {\n            return len[1];\n        }\n    };\n\n    vector<Rectangle>\
    \ rects;\n    vector<Coord> ys;\n\n    void add_rectangle(Coord l, Coord d, Coord\
    \ r, Coord u) {\n        if (l >= r || d >= u) return;\n        rects.push_back({l,\
    \ d, r, u});\n        ys.push_back(d);\n        ys.push_back(u);\n    }\n\n  \
    \  Area solve() const {\n        if (rects.empty()) return 0;\n\n        vector<Coord>\
    \ ord_y = ys;\n        sort(ord_y.begin(), ord_y.end());\n        ord_y.erase(unique(ord_y.begin(),\
    \ ord_y.end()), ord_y.end());\n        if ((int)ord_y.size() <= 1) return 0;\n\
    \n        vector<Event> events;\n        events.reserve(rects.size() * 2);\n \
    \       for (auto &&rect : rects) {\n            int d = (int)(lower_bound(ord_y.begin(),\
    \ ord_y.end(), rect.d) - ord_y.begin());\n            int u = (int)(lower_bound(ord_y.begin(),\
    \ ord_y.end(), rect.u) - ord_y.begin());\n            events.push_back({rect.l,\
    \ d, u, 1});\n            events.push_back({rect.r, d, u, -1});\n        }\n \
    \       sort(events.begin(), events.end());\n\n        SegmentTree seg(ord_y);\n\
    \        Area ans = 0;\n        Coord prev_x = events[0].x;\n        int i = 0;\n\
    \        while (i < (int)events.size()) {\n            Coord x = events[i].x;\n\
    \            ans += seg.covered_length() * Area(x - prev_x);\n            while\
    \ (i < (int)events.size() && events[i].x == x) {\n                seg.update(events[i].yl,\
    \ events[i].yr, events[i].delta);\n                ++i;\n            }\n     \
    \       prev_x = x;\n        }\n        return ans;\n    }\n};\n\n/**\n * @brief\
    \ \u9577\u65B9\u5F62\u548C\u96C6\u5408\u9762\u7A4D(Area of Union of Rectangles)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/area_of_union_of_rectangles.cpp
  requiredBy: []
  timestamp: '2026-03-15 00:59:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_area_of_union_of_rectangles.test.cpp
date: 2026-03-14
documentation_of: geometry/area_of_union_of_rectangles.cpp
layout: document
tags: "\u5E7E\u4F55, \u30C7\u30FC\u30BF\u69CB\u9020"
title: Area of Union of Rectangles
---

## 説明
長方形集合の和集合の面積を求める。
`x` 方向 sweep と、`y` 区間の被覆数と被覆長を持つ専用セグメント木を使う。
計算量は $O(N \log N)$。

## できること
- `AreaOfUnionOfRectangles<Coord, Area> solver`
  空の solver を作る
- `void add_rectangle(Coord l, Coord d, Coord r, Coord u)`
  半開長方形 `[l, r) x [d, u)` を追加する。空長方形は無視する
- `Area solve()`
  追加した長方形の和集合面積を返す

## 使い方
長方形を全部 `add_rectangle` してから `solve()` を呼ぶ。
`Coord` は座標型、`Area` は面積を保持する型で、既定は `long long` になる。
