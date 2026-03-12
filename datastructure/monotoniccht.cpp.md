---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/monotoniccht.cpp\"\ntemplate<class T, bool\
    \ get_max>\nclass CHT {\n    using P = pair<T, T>;\n    deque<P> lines;\npublic:\n\
    \    CHT() = default;\n    bool check(P l1, P l2, P l3){\n        if constexpr\
    \ (is_integral_v<T>) {\n            return (((__int128)l2.second - l1.second)\
    \ * ((__int128)l2.first - l3.first)\n                 >= ((__int128)l3.second\
    \ - l2.second) * ((__int128)l1.first - l2.first));\n        } else {\n       \
    \     return ((static_cast<long double>(l2.second) - l1.second) * (static_cast<long\
    \ double>(l2.first) - l3.first)\n                 >= (static_cast<long double>(l3.second)\
    \ - l2.second) * (static_cast<long double>(l1.first) - l2.first));\n        }\n\
    \    }\n\n    void add_line(T a, T b) { // add ax + b\n        if(get_max) a =\
    \ -a, b = -b;\n        P L(a, b);\n        if(lines.empty()){\n            lines.emplace_back(L);\n\
    \            return;\n        }\n        if(lines.front().first <= a){\n     \
    \       if(lines.front().first == a){\n                if(lines.front().second\
    \ <= b) return;\n                else lines.pop_front();\n            }\n    \
    \        while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();\n\
    \            lines.emplace_front(L);\n        }else {\n            if(lines.back().first\
    \ == a){\n                if(lines.back().second <= b) return;\n             \
    \   else lines.pop_back();\n            }\n            while(lines.size() >= 2\
    \ && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();\n      \
    \      lines.emplace_back(L);\n        }\n    }\n\n    T val(const P &L, const\
    \ T &x) { return L.first * x + L.second; }\n    T query(T x){\n        int l =\
    \ -1, r = lines.size() - 1;\n        while(r - l > 1){\n            int mid =\
    \ (l+r) >> 1;\n            if(val(lines[mid], x) >= val(lines[mid+1], x)) l =\
    \ mid;\n            else r = mid;\n        }\n        return get_max ? -val(lines[r],\
    \ x) : val(lines[r], x);\n    }\n\n    T query_increase(T x){\n        while(lines.size()\
    \ >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();\n    \
    \    return get_max ? -val(lines.front(), x) : val(lines.front(), x);\n    }\n\
    \n    T query_decrease(T x){\n        while(lines.size() >= 2 && val(lines.back(),\
    \ x) >= val(lines[lines.size() - 2], x)) lines.pop_back();\n        return get_max\
    \ ? -val(lines.back(), x) : val(lines.back(), x);\n    }\n};\n"
  code: "template<class T, bool get_max>\nclass CHT {\n    using P = pair<T, T>;\n\
    \    deque<P> lines;\npublic:\n    CHT() = default;\n    bool check(P l1, P l2,\
    \ P l3){\n        if constexpr (is_integral_v<T>) {\n            return (((__int128)l2.second\
    \ - l1.second) * ((__int128)l2.first - l3.first)\n                 >= ((__int128)l3.second\
    \ - l2.second) * ((__int128)l1.first - l2.first));\n        } else {\n       \
    \     return ((static_cast<long double>(l2.second) - l1.second) * (static_cast<long\
    \ double>(l2.first) - l3.first)\n                 >= (static_cast<long double>(l3.second)\
    \ - l2.second) * (static_cast<long double>(l1.first) - l2.first));\n        }\n\
    \    }\n\n    void add_line(T a, T b) { // add ax + b\n        if(get_max) a =\
    \ -a, b = -b;\n        P L(a, b);\n        if(lines.empty()){\n            lines.emplace_back(L);\n\
    \            return;\n        }\n        if(lines.front().first <= a){\n     \
    \       if(lines.front().first == a){\n                if(lines.front().second\
    \ <= b) return;\n                else lines.pop_front();\n            }\n    \
    \        while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();\n\
    \            lines.emplace_front(L);\n        }else {\n            if(lines.back().first\
    \ == a){\n                if(lines.back().second <= b) return;\n             \
    \   else lines.pop_back();\n            }\n            while(lines.size() >= 2\
    \ && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();\n      \
    \      lines.emplace_back(L);\n        }\n    }\n\n    T val(const P &L, const\
    \ T &x) { return L.first * x + L.second; }\n    T query(T x){\n        int l =\
    \ -1, r = lines.size() - 1;\n        while(r - l > 1){\n            int mid =\
    \ (l+r) >> 1;\n            if(val(lines[mid], x) >= val(lines[mid+1], x)) l =\
    \ mid;\n            else r = mid;\n        }\n        return get_max ? -val(lines[r],\
    \ x) : val(lines[r], x);\n    }\n\n    T query_increase(T x){\n        while(lines.size()\
    \ >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();\n    \
    \    return get_max ? -val(lines.front(), x) : val(lines.front(), x);\n    }\n\
    \n    T query_decrease(T x){\n        while(lines.size() >= 2 && val(lines.back(),\
    \ x) >= val(lines[lines.size() - 2], x)) lines.pop_back();\n        return get_max\
    \ ? -val(lines.back(), x) : val(lines.back(), x);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/monotoniccht.cpp
  requiredBy: []
  timestamp: '2026-03-12 19:34:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
date: 2018-04-28
documentation_of: datastructure/monotoniccht.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "Convex-Hull Trick (\u30AF\u30A8\u30EA\u5358\u8ABF)"
---

## 説明
傾き単調な直線追加と、`x` の単調クエリを高速に処理する Convex Hull Trick。
最小値版と最大値版を template 引数で切り替える。

## できること
- `CHT<T, false> cht`
  最小値を取る CHT を作る
- `CHT<T, true> cht`
  最大値を取る CHT を作る
- `void add_line(T a, T b)`
  直線 `y = ax + b` を追加する
- `T query(T x)`
  任意順クエリで最良値を返す
- `T query_increase(T x)`
  `x` が単調増加するときの最良値を返す
- `T query_decrease(T x)`
  `x` が単調減少するときの最良値を返す

## 使い方
追加する直線の傾きは単調である必要がある。
クエリだけ単調なら `query_increase` または `query_decrease` を使うと償却 $O(1)$、任意順なら `query` で $O(\log N)$。

## 実装上の補足
不要直線判定は、整数型なら `__int128` の交差積比較で処理する。
浮動小数点型では `long double` で比較する。
