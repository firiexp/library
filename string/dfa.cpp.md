---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/digit_dfa.cpp
    title: "\u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\u3059\u6709\u9650\u30AA\
      \u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: math/digit_dp.cpp
    title: "\u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\u6570\u3068\u7DCF\u548C"
  - icon: ':heavy_check_mark:'
    path: string/avoid_patterns.cpp
    title: "\u7981\u6B62\u90E8\u5206\u6587\u5B57\u5217\u3092\u907F\u3051\u308B\u6709\
      \u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: string/count_words.cpp
    title: "\u6709\u9650\u72B6\u614BDP\u306E\u9577\u3055N\u306E\u6587\u5B57\u5217\u6570"
  - icon: ':heavy_check_mark:'
    path: string/dfa_minimize.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\u6700\u5C0F\u5316"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_avoid_patterns.test.cpp
    title: test/yosupo_aplusb_avoid_patterns.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_avoid_patterns.test.cpp
    title: test/yosupo_aplusb_avoid_patterns.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_count_words.test.cpp
    title: test/yosupo_aplusb_count_words.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_count_words.test.cpp
    title: test/yosupo_aplusb_count_words.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dfa.test.cpp
    title: test/yosupo_aplusb_dfa.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dfa_minimize.test.cpp
    title: test/yosupo_aplusb_dfa_minimize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dfa_minimize.test.cpp
    title: test/yosupo_aplusb_dfa_minimize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_digit_dp.test.cpp
    title: test/yosupo_aplusb_digit_dp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_digit_dp.test.cpp
    title: test/yosupo_aplusb_digit_dp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki2867.test.cpp
    title: test/yuki2867.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki2867.test.cpp
    title: test/yuki2867.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\
      \u306E\u5408\u6210"
    links: []
  bundledCode: "#line 1 \"string/dfa.cpp\"\n\n\n\ntemplate<int W>\nstruct DFA {\n\
    \    vector<array<int, W>> next;\n    vector<char> accept;\n    int initial =\
    \ -1;\n};\n\ntemplate<int W>\nDFA<W> intersect(const DFA<W>& a, const DFA<W>&\
    \ b) {\n    if (a.initial == -1 || b.initial == -1) return {};\n    size_t width\
    \ = b.next.size();\n    assert(a.next.size() <= vector<int>().max_size() / width);\n\
    \    vector<int> id(a.next.size() * width, -1);\n    vector<pair<int, int>> states;\n\
    \    DFA<W> result;\n    auto add = [&](int x, int y) {\n        int& index =\
    \ id[size_t(x) * width + y];\n        if (index == -1) {\n            index =\
    \ (int)states.size();\n            states.emplace_back(x, y);\n            result.next.emplace_back();\n\
    \            result.accept.push_back(a.accept[x] && b.accept[y]);\n        }\n\
    \        return index;\n    };\n    result.initial = add(a.initial, b.initial);\n\
    \    for (int i = 0; i < (int)states.size(); ++i) {\n        auto [x, y] = states[i];\n\
    \        for (int c = 0; c < W; ++c) {\n            int nx = a.next[x][c], ny\
    \ = b.next[y][c];\n            int to = nx == -1 || ny == -1 ? -1 : add(nx, ny);\n\
    \            result.next[i][c] = to;\n        }\n    }\n    return result;\n}\n\
    \n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\
    \u4EF6\u306E\u5408\u6210\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_STRING_DFA_CPP\n#define FIRIEXP_LIBRARY_STRING_DFA_CPP\n\
    \ntemplate<int W>\nstruct DFA {\n    vector<array<int, W>> next;\n    vector<char>\
    \ accept;\n    int initial = -1;\n};\n\ntemplate<int W>\nDFA<W> intersect(const\
    \ DFA<W>& a, const DFA<W>& b) {\n    if (a.initial == -1 || b.initial == -1) return\
    \ {};\n    size_t width = b.next.size();\n    assert(a.next.size() <= vector<int>().max_size()\
    \ / width);\n    vector<int> id(a.next.size() * width, -1);\n    vector<pair<int,\
    \ int>> states;\n    DFA<W> result;\n    auto add = [&](int x, int y) {\n    \
    \    int& index = id[size_t(x) * width + y];\n        if (index == -1) {\n   \
    \         index = (int)states.size();\n            states.emplace_back(x, y);\n\
    \            result.next.emplace_back();\n            result.accept.push_back(a.accept[x]\
    \ && b.accept[y]);\n        }\n        return index;\n    };\n    result.initial\
    \ = add(a.initial, b.initial);\n    for (int i = 0; i < (int)states.size(); ++i)\
    \ {\n        auto [x, y] = states[i];\n        for (int c = 0; c < W; ++c) {\n\
    \            int nx = a.next[x][c], ny = b.next[y][c];\n            int to = nx\
    \ == -1 || ny == -1 ? -1 : add(nx, ny);\n            result.next[i][c] = to;\n\
    \        }\n    }\n    return result;\n}\n\n#endif\n\n/**\n * @brief \u6709\u9650\
    \u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\u6210\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/dfa.cpp
  requiredBy:
  - math/digit_dp.cpp
  - math/digit_dfa.cpp
  - string/count_words.cpp
  - string/avoid_patterns.cpp
  - string/dfa_minimize.cpp
  timestamp: '2026-10-16 22:08:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_dfa.test.cpp
  - test/yosupo_aplusb_dfa_minimize.test.cpp
  - test/yosupo_aplusb_dfa_minimize.test.cpp
  - test/yuki2867.test.cpp
  - test/yuki2867.test.cpp
  - test/yosupo_aplusb_count_words.test.cpp
  - test/yosupo_aplusb_count_words.test.cpp
  - test/yosupo_aplusb_avoid_patterns.test.cpp
  - test/yosupo_aplusb_avoid_patterns.test.cpp
documentation_of: string/dfa.cpp
layout: document
title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\
  \u6210"
---

## 説明
文字を `0` から `W-1` で表す決定性有限オートマトン。条件を AND 合成できる。

## できること
- `DFA<W>{next, accept, initial}` : 遷移表、受理フラグ、初期状態から直接作る
- `intersect(a, b)` : 両方が受理する列を受理する DFA を返す。初期状態対から到達できる状態だけを持つ

## 使い方
`next` は `vector<array<int, W>>`、`accept` は状態数と同じ長さの `vector<char>`。
状態番号は `int` に収まる非負整数とし、`next[v][c] == -1` は拒否遷移を表す。
拒否した列は以後も拒否する。`initial == -1` は空列も含めた全拒否で、既定構築はこの形になる。
それ以外の遷移先と初期状態は有効な状態番号とする。
空列の受理は初期状態のフラグで決まる。受理しない状態から受理状態へ遷移してもよい。

```cpp
auto a = intersect(digit_sum_exact(12), digit_value_mod(12));
```

数字の条件には `math/digit_dfa.cpp` を include する。表は固定長の文字列 DP にも使える。
先頭 0 や数値の上下限はこの表では扱わない。

## 実装上の補足
入力状態数を $S_1,S_2$、到達状態対数を $R$ とすると、合成は最悪 $O(S_1S_2+WR)$ 時間。
状態対の ID 配列に $O(S_1S_2)$、返却表に $O(WR)$ の領域を使う。
状態数の積が確保可能で、返却状態数が `int` に収まる範囲で使う。
`intersect` は最小化を行わない。必要なら `string/dfa_minimize.cpp` の `minimize(a)` を使う。
