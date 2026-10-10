---
category: "\u30AF\u30A8\u30EA"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_mo.test.cpp
    title: test/yosupo_aplusb_mo.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_range_inversions_query.test.cpp
    title: test/yosupo_static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Mo's Algorithm
    links: []
  bundledCode: "#line 1 \"util/mo.cpp\"\nstruct Query {\n    static inline int bucket_size\
    \ = 1;\n    static inline int &B = bucket_size;\n    int l, r, no;\n    Query(int\
    \ l, int r, int no) : l(l), r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n\
    \    bool operator<(const Query &a) const {\n        int ablock = this->l / bucket_size,\
    \ bblock = a.l / bucket_size;\n        if(ablock != bblock) return ablock < bblock;\n\
    \        if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};\n\ntemplate<class AddLeft, class AddRight, class EraseLeft, class EraseRight,\
    \ class Output>\nvoid mo_solve(int n, const vector<Query>& queries, AddLeft add_left,\
    \ AddRight add_right,\n              EraseLeft erase_left, EraseRight erase_right,\
    \ Output output, int bucket_size = 0) {\n    if (queries.empty()) return;\n  \
    \  if (bucket_size <= 0) bucket_size = max(1, (int)(n / sqrt((double)queries.size())));\n\
    \    vector<Query> qs = queries;\n    sort(qs.begin(), qs.end(), [&](const Query&\
    \ a, const Query& b) {\n        int ablock = a.l / bucket_size, bblock = b.l /\
    \ bucket_size;\n        if (ablock != bblock) return ablock < bblock;\n      \
    \  return ablock & 1 ? a.r < b.r : a.r > b.r;\n    });\n    int l = 0, r = 0;\n\
    \    for (const auto& q : qs) {\n        while (q.l < l) add_left(--l);\n    \
    \    while (r < q.r) add_right(r++);\n        while (l < q.l) erase_left(l++);\n\
    \        while (q.r < r) erase_right(--r);\n        output(q.no);\n    }\n}\n\n\
    /**\n * @brief Mo's Algorithm\n */\n"
  code: "struct Query {\n    static inline int bucket_size = 1;\n    static inline\
    \ int &B = bucket_size;\n    int l, r, no;\n    Query(int l, int r, int no) :\
    \ l(l), r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n    bool operator<(const\
    \ Query &a) const {\n        int ablock = this->l / bucket_size, bblock = a.l\
    \ / bucket_size;\n        if(ablock != bblock) return ablock < bblock;\n     \
    \   if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};\n\ntemplate<class AddLeft, class AddRight, class EraseLeft, class EraseRight,\
    \ class Output>\nvoid mo_solve(int n, const vector<Query>& queries, AddLeft add_left,\
    \ AddRight add_right,\n              EraseLeft erase_left, EraseRight erase_right,\
    \ Output output, int bucket_size = 0) {\n    if (queries.empty()) return;\n  \
    \  if (bucket_size <= 0) bucket_size = max(1, (int)(n / sqrt((double)queries.size())));\n\
    \    vector<Query> qs = queries;\n    sort(qs.begin(), qs.end(), [&](const Query&\
    \ a, const Query& b) {\n        int ablock = a.l / bucket_size, bblock = b.l /\
    \ bucket_size;\n        if (ablock != bblock) return ablock < bblock;\n      \
    \  return ablock & 1 ? a.r < b.r : a.r > b.r;\n    });\n    int l = 0, r = 0;\n\
    \    for (const auto& q : qs) {\n        while (q.l < l) add_left(--l);\n    \
    \    while (r < q.r) add_right(r++);\n        while (l < q.l) erase_left(l++);\n\
    \        while (q.r < r) erase_right(--r);\n        output(q.no);\n    }\n}\n\n\
    /**\n * @brief Mo's Algorithm\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/mo.cpp
  requiredBy: []
  timestamp: '2026-10-10 15:50:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_range_inversions_query.test.cpp
  - test/yosupo_aplusb_mo.test.cpp
date: 2026-03-25
documentation_of: util/mo.cpp
layout: document
tags: "\u30AF\u30A8\u30EA"
title: Mo's Algorithm
---

## 説明
区間のマージは高速にできないが、区間を 1 つ広げる/縮めることが $O(p(N))$ でできれば、$Q$ 個のクエリをまとめて処理できる。

## できること
- `Query(l, r, no)`
  半開区間 `[l, r)` のクエリを作る
- `mo_solve(n, queries, add_left, add_right, erase_left, erase_right, output, bucket_size = 0)`
  クエリを並べ替えて左右端を移動し、各回答時に `output(no)` を呼ぶ。各追加・削除 callback には要素の添字を渡す。入力クエリ列と `Query::bucket_size` は変更しない
- `Query::B`
  手動で `sort` するときのバケット幅。`Query::bucket_size` の別名
- `sort(qs.begin(), qs.end())`
  左端のブロック順、右端の蛇行順でクエリを並べる

## 使い方
`mo_solve` に渡すクエリは `0 <= l <= r <= n` を満たすものとし、callback 側の集計は空区間から始める。
左右の追加・削除を別々に指定できるため、転倒数など順序に依存する集計にも使える。
回答は元のクエリ ID で保存する。空クエリ列では callback を呼ばず、空区間のクエリにも対応する。
`bucket_size` が正なら指定値を使い、省略または `0` 以下なら $\max(1, \lfloor N/\sqrt{Q}\rfloor)$ を使う。
利用側では `<algorithm>`、`<cmath>`、`<vector>` を読み込む。

```cpp
mo_solve(n, qs, add_left, add_right, erase_left, erase_right,
         [&](int no) { ans[no] = current_answer; });
```

比較だけを使いたい場合は、従来どおり `Query::bucket_size` を設定して `sort(qs.begin(), qs.end())` を呼べる。

## 実装上の補足
- `mo_solve` のソートは $O(Q\log Q)$、作業領域はクエリ列のコピーに $O(Q)$
- 典型的な計算量評価は、左端の移動が $O(QB)$、右端の移動が $O(N^2 / B)$ なので、1 回の追加・削除が $O(p(N))$ なら合計は
$$
O\left(\left(QB + \frac{N^2}{B}\right) p(N)\right)
$$
  になる
- これを最小化する目安が
$$
B \approx \frac{N}{\sqrt{Q}}
$$
  なので、まずはこの値を目安に `Query::bucket_size` を決め、必要なら定数倍を見ながら手で調整するとよい
- `Q` と `N` が同程度なら $B \approx \sqrt{N}$ と見てよい
