---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_lis_indices.test.cpp
    title: test/yosupo_aplusb_lis_indices.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_longest_increasing_subsequence.test.cpp
    title: test/yosupo_longest_increasing_subsequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u5FA9\u5143"
    links: []
  bundledCode: "#line 1 \"util/lis.cpp\"\ntemplate<class T>\nvector<int> lis_indices(const\
    \ vector<T> &a, bool strict = true) {\n    vector<int> tails, previous(a.size(),\
    \ -1);\n    for (int i = 0; i < (int)a.size(); ++i) {\n        int l = 0, r =\
    \ tails.size();\n        while (l < r) {\n            int m = l + (r - l) / 2;\n\
    \            if (strict ? a[tails[m]] < a[i] : !(a[i] < a[tails[m]])) l = m +\
    \ 1;\n            else r = m;\n        }\n        if (l) previous[i] = tails[l\
    \ - 1];\n        if (l == (int)tails.size()) tails.push_back(i);\n        else\
    \ tails[l] = i;\n    }\n    vector<int> result(tails.size());\n    int v = tails.empty()\
    \ ? -1 : tails.back();\n    for (int i = (int)result.size() - 1; i >= 0; --i)\
    \ {\n        result[i] = v;\n        v = previous[v];\n    }\n    return result;\n\
    }\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u5FA9\u5143\
    \n */\n"
  code: "template<class T>\nvector<int> lis_indices(const vector<T> &a, bool strict\
    \ = true) {\n    vector<int> tails, previous(a.size(), -1);\n    for (int i =\
    \ 0; i < (int)a.size(); ++i) {\n        int l = 0, r = tails.size();\n       \
    \ while (l < r) {\n            int m = l + (r - l) / 2;\n            if (strict\
    \ ? a[tails[m]] < a[i] : !(a[i] < a[tails[m]])) l = m + 1;\n            else r\
    \ = m;\n        }\n        if (l) previous[i] = tails[l - 1];\n        if (l ==\
    \ (int)tails.size()) tails.push_back(i);\n        else tails[l] = i;\n    }\n\
    \    vector<int> result(tails.size());\n    int v = tails.empty() ? -1 : tails.back();\n\
    \    for (int i = (int)result.size() - 1; i >= 0; --i) {\n        result[i] =\
    \ v;\n        v = previous[v];\n    }\n    return result;\n}\n\n/**\n * @brief\
    \ \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u5FA9\u5143\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/lis.cpp
  requiredBy: []
  timestamp: '2026-10-07 22:12:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_longest_increasing_subsequence.test.cpp
  - test/yosupo_aplusb_lis_indices.test.cpp
documentation_of: util/lis.cpp
layout: document
title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u5FA9\u5143"
---

## 説明
最長増加部分列を元の配列の添字列として復元する。
時間 $O(N\log N)$、追加領域 $O(N)$。

## できること
- `lis_indices(a, strict = true)` : 狭義単調増加な最長部分列の添字を昇順で返す。`false` なら非減少部分列を返す
- 空配列には空列を返す。最適解が複数ある場合は任意の1つを返す

## 使い方
`auto indices = lis_indices(a);` とし、`a[indices[i]]` で各要素を取得する。
長さは `indices.size()` で得られる。
要素型には大小比較 `<` だけを使い、数値の番兵や座標圧縮は不要。
