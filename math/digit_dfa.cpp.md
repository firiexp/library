---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/dfa.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\
      \u5408\u6210"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_avoid_patterns.test.cpp
    title: test/yosupo_aplusb_avoid_patterns.test.cpp
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
    path: test/yosupo_aplusb_digit_dp.test.cpp
    title: test/yosupo_aplusb_digit_dp.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\u3059\u6709\u9650\
      \u30AA\u30FC\u30C8\u30DE\u30C8\u30F3"
    links: []
  bundledCode: "#line 1 \"math/digit_dfa.cpp\"\n\n\n\n#line 1 \"string/dfa.cpp\"\n\
    \n\n\ntemplate<int W>\nstruct DFA {\n    vector<array<int, W>> next;\n    vector<char>\
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
    \        }\n    }\n    return result;\n}\n\ntemplate<int W>\nDFA<W> unite(const\
    \ DFA<W>& a, const DFA<W>& b) {\n    if (a.initial == -1 && b.initial == -1) return\
    \ {};\n    size_t width = b.next.size() + 1;\n    assert(a.next.size() + 1 <=\
    \ vector<int>().max_size() / width);\n    vector<int> id((a.next.size() + 1) *\
    \ width, -1);\n    vector<pair<int, int>> states;\n    DFA<W> result;\n    auto\
    \ add = [&](int x, int y) {\n        if (x == -1 && y == -1) return -1;\n    \
    \    int& index = id[size_t(x + 1) * width + (y + 1)];\n        if (index == -1)\
    \ {\n            index = (int)states.size();\n            states.emplace_back(x,\
    \ y);\n            result.next.emplace_back();\n            result.accept.push_back((x\
    \ != -1 && a.accept[x]) || (y != -1 && b.accept[y]));\n        }\n        return\
    \ index;\n    };\n    result.initial = add(a.initial, b.initial);\n    for (int\
    \ i = 0; i < (int)states.size(); ++i) {\n        auto [x, y] = states[i];\n  \
    \      for (int c = 0; c < W; ++c) {\n            int nx = x == -1 ? -1 : a.next[x][c];\n\
    \            int ny = y == -1 ? -1 : b.next[y][c];\n            int to = add(nx,\
    \ ny);\n            result.next[i][c] = to;\n        }\n    }\n    return result;\n\
    }\n\ntemplate<int W>\nDFA<W> complement(const DFA<W>& a) {\n    if (a.initial\
    \ == -1) {\n        DFA<W> result{vector<array<int, W>>(1), {true}, 0};\n    \
    \    result.next[0].fill(0);\n        return result;\n    }\n    DFA<W> result\
    \ = a;\n    for (auto& accept : result.accept) accept = !accept;\n    int sink\
    \ = (int)result.next.size();\n    bool needed = false;\n    for (auto& row : result.next)\
    \ {\n        for (int& to : row) if (to == -1) {\n            to = sink;\n   \
    \         needed = true;\n        }\n    }\n    if (needed) {\n        result.next.emplace_back();\n\
    \        result.next.back().fill(sink);\n        result.accept.push_back(true);\n\
    \    }\n    return result;\n}\n\n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\
    \u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\u6210\n */\n#line 5 \"math/digit_dfa.cpp\"\
    \n\nDFA<10> digit_value_mod(int m, int r = 0) {\n    assert(m > 0 && 0 <= r &&\
    \ r < m);\n    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};\n   \
    \ a.accept[r] = true;\n    for (int v = 0; v < m; ++v) {\n        for (int d =\
    \ 0; d < 10; ++d) a.next[v][d] = (10LL * v + d) % m;\n    }\n    return a;\n}\n\
    \nDFA<10> digit_sum_mod(int m, int r = 0) {\n    assert(m > 0 && 0 <= r && r <\
    \ m);\n    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};\n    a.accept[r]\
    \ = true;\n    for (int v = 0; v < m; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = (v + (long long)d) % m;\n    }\n    return a;\n}\n\nDFA<10>\
    \ digit_sum_exact(int k) {\n    assert(0 <= k && k < numeric_limits<int>::max());\n\
    \    DFA<10> a{vector<array<int, 10>>(k + 1), vector<char>(k + 1), 0};\n    a.accept[k]\
    \ = true;\n    for (int v = 0; v <= k; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = d <= k - v ? v + d : -1;\n    }\n    return a;\n}\n\nDFA<10>\
    \ no_equal_adjacent() {\n    DFA<10> a{vector<array<int, 10>>(11), vector<char>(11,\
    \ true), 10};\n    for (int v = 0; v <= 10; ++v) {\n        for (int d = 0; d\
    \ < 10; ++d) a.next[v][d] = v == d ? -1 : d;\n    }\n    return a;\n}\n\nDFA<10>\
    \ required_digits(int mask) {\n    assert(0 <= mask && mask < (1 << 10));\n  \
    \  array<int, 10> bit{};\n    int n = 1;\n    for (int d = 0; d < 10; ++d) {\n\
    \        if (mask >> d & 1) bit[d] = n, n *= 2;\n    }\n    DFA<10> a{vector<array<int,\
    \ 10>>(n), vector<char>(n), 0};\n    a.accept[n - 1] = true;\n    for (int v =\
    \ 0; v < n; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = v | bit[d];\n\
    \    }\n    return a;\n}\n\n\n\n/**\n * @brief \u6570\u5B57\u5217\u306E\u6761\u4EF6\
    \u3092\u8868\u3059\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_DIGIT_DFA_CPP\n#define FIRIEXP_LIBRARY_MATH_DIGIT_DFA_CPP\n\
    \n#include \"../string/dfa.cpp\"\n\nDFA<10> digit_value_mod(int m, int r = 0)\
    \ {\n    assert(m > 0 && 0 <= r && r < m);\n    DFA<10> a{vector<array<int, 10>>(m),\
    \ vector<char>(m), 0};\n    a.accept[r] = true;\n    for (int v = 0; v < m; ++v)\
    \ {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = (10LL * v + d) % m;\n\
    \    }\n    return a;\n}\n\nDFA<10> digit_sum_mod(int m, int r = 0) {\n    assert(m\
    \ > 0 && 0 <= r && r < m);\n    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m),\
    \ 0};\n    a.accept[r] = true;\n    for (int v = 0; v < m; ++v) {\n        for\
    \ (int d = 0; d < 10; ++d) a.next[v][d] = (v + (long long)d) % m;\n    }\n   \
    \ return a;\n}\n\nDFA<10> digit_sum_exact(int k) {\n    assert(0 <= k && k < numeric_limits<int>::max());\n\
    \    DFA<10> a{vector<array<int, 10>>(k + 1), vector<char>(k + 1), 0};\n    a.accept[k]\
    \ = true;\n    for (int v = 0; v <= k; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = d <= k - v ? v + d : -1;\n    }\n    return a;\n}\n\nDFA<10>\
    \ no_equal_adjacent() {\n    DFA<10> a{vector<array<int, 10>>(11), vector<char>(11,\
    \ true), 10};\n    for (int v = 0; v <= 10; ++v) {\n        for (int d = 0; d\
    \ < 10; ++d) a.next[v][d] = v == d ? -1 : d;\n    }\n    return a;\n}\n\nDFA<10>\
    \ required_digits(int mask) {\n    assert(0 <= mask && mask < (1 << 10));\n  \
    \  array<int, 10> bit{};\n    int n = 1;\n    for (int d = 0; d < 10; ++d) {\n\
    \        if (mask >> d & 1) bit[d] = n, n *= 2;\n    }\n    DFA<10> a{vector<array<int,\
    \ 10>>(n), vector<char>(n), 0};\n    a.accept[n - 1] = true;\n    for (int v =\
    \ 0; v < n; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = v | bit[d];\n\
    \    }\n    return a;\n}\n\n#endif\n\n/**\n * @brief \u6570\u5B57\u5217\u306E\u6761\
    \u4EF6\u3092\u8868\u3059\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\n */\n"
  dependsOn:
  - string/dfa.cpp
  isVerificationFile: false
  path: math/digit_dfa.cpp
  requiredBy: []
  timestamp: '2026-10-17 19:15:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_dfa.test.cpp
  - test/yosupo_aplusb_dfa_minimize.test.cpp
  - test/yosupo_aplusb_count_words.test.cpp
  - test/yosupo_aplusb_avoid_patterns.test.cpp
documentation_of: math/digit_dfa.cpp
layout: document
title: "\u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\u3059\u6709\u9650\u30AA\u30FC\
  \u30C8\u30DE\u30C8\u30F3"
---

## 説明
数字 `0` から `9` の列に対する条件を、構築済みの `DFA<10>` で返す。

## できること
文字種数を $W$ とする。本実装は $W=10$。

- `digit_value_mod(m, r=0)` : 整数値の剰余が `r`。$m$ 状態、構築 $O(Wm)$
- `digit_sum_mod(m, r=0)` : 桁和の剰余が `r`。$m$ 状態、構築 $O(Wm)$
- `digit_sum_exact(k)` : 桁和が `k`。超過は拒否。$k+1$ 状態、構築 $O(W(k+1))$
- `no_equal_adjacent()` : 同じ数字が隣接しない。11 状態
- `required_digits(mask)` : bit が立つ数字をすべて含む。指定数字数を $k$ として $2^k$ 状態、構築 $O(W2^k)$

## 使い方
`m > 0`、`0 <= r < m`、`0 <= k < INT_MAX`、`0 <= mask < 1024` とする。
状態数は `int` に収まり、遷移表を確保できる範囲で使う。
`intersect(a, b)` で複数の条件を合成できる。

```cpp
auto a = intersect(digit_value_mod(7), required_digits((1 << 0) | (1 << 3)));
```

与えた数字は先頭 0 も含めてすべて読む。数値の正規表記は桁 DP 側で扱う。
空列の値と桁和は 0 とする。空列に隣接違反はなく、指定数字を含む条件は `mask == 0` のときだけ満たす。
