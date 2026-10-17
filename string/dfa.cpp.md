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
    \ntemplate<int W>\nDFA<W> unite(const DFA<W>& a, const DFA<W>& b) {\n    if (a.initial\
    \ == -1 && b.initial == -1) return {};\n    size_t width = b.next.size() + 1;\n\
    \    assert(a.next.size() + 1 <= vector<int>().max_size() / width);\n    vector<int>\
    \ id((a.next.size() + 1) * width, -1);\n    vector<pair<int, int>> states;\n \
    \   DFA<W> result;\n    auto add = [&](int x, int y) {\n        if (x == -1 &&\
    \ y == -1) return -1;\n        int& index = id[size_t(x + 1) * width + (y + 1)];\n\
    \        if (index == -1) {\n            index = (int)states.size();\n       \
    \     states.emplace_back(x, y);\n            result.next.emplace_back();\n  \
    \          result.accept.push_back((x != -1 && a.accept[x]) || (y != -1 && b.accept[y]));\n\
    \        }\n        return index;\n    };\n    result.initial = add(a.initial,\
    \ b.initial);\n    for (int i = 0; i < (int)states.size(); ++i) {\n        auto\
    \ [x, y] = states[i];\n        for (int c = 0; c < W; ++c) {\n            int\
    \ nx = x == -1 ? -1 : a.next[x][c];\n            int ny = y == -1 ? -1 : b.next[y][c];\n\
    \            int to = add(nx, ny);\n            result.next[i][c] = to;\n    \
    \    }\n    }\n    return result;\n}\n\ntemplate<int W>\nDFA<W> complement(const\
    \ DFA<W>& a) {\n    if (a.initial == -1) {\n        DFA<W> result{vector<array<int,\
    \ W>>(1), {true}, 0};\n        result.next[0].fill(0);\n        return result;\n\
    \    }\n    DFA<W> result = a;\n    for (auto& accept : result.accept) accept\
    \ = !accept;\n    int sink = (int)result.next.size();\n    bool needed = false;\n\
    \    for (auto& row : result.next) {\n        for (int& to : row) if (to == -1)\
    \ {\n            to = sink;\n            needed = true;\n        }\n    }\n  \
    \  if (needed) {\n        result.next.emplace_back();\n        result.next.back().fill(sink);\n\
    \        result.accept.push_back(true);\n    }\n    return result;\n}\n\n\n\n\
    /**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\
    \u306E\u5408\u6210\n */\n"
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
    \    }\n    return result;\n}\n\n#endif\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\
    \u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\u6210\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/dfa.cpp
  requiredBy:
  - math/digit_dp.cpp
  - math/digit_dfa.cpp
  - string/count_words.cpp
  - string/avoid_patterns.cpp
  - string/dfa_minimize.cpp
  timestamp: '2026-10-17 19:15:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_dfa.test.cpp
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
文字を `0` から `W-1` で表す決定性有限オートマトン。条件を AND・OR・NOT で合成できる。

## できること
- `DFA<W>{next, accept, initial}` : 遷移表、受理フラグ、初期状態から直接作る
- `intersect(a, b)` : 両方が受理する列を受理する DFA を返す。初期状態対から到達できる状態だけを持つ
- `unite(a, b)` : 少なくとも片方が受理する列を受理する DFA を返す。片方が拒否遷移に入っても他方の遷移を続ける
- `complement(a)` : `0..W-1` 上の有限列全体に対する補集合を返す。空列を含め、元の DFA が拒否する列だけを受理する

## 使い方
`next` は `vector<array<int, W>>`、`accept` は状態数と同じ長さの `vector<char>`。
状態番号は `int` に収まる非負整数とし、`next[v][c] == -1` は拒否遷移を表す。
拒否した列は以後も拒否する。`initial == -1` は空列も含めた全拒否で、既定構築はこの形になる。
それ以外の遷移先と初期状態は有効な状態番号とする。
空列の受理は初期状態のフラグで決まる。受理しない状態から受理状態へ遷移してもよい。

```cpp
auto a = intersect(digit_sum_exact(12), digit_value_mod(12));
auto b = unite(digit_value_mod(3), digit_value_mod(5));
auto c = complement(b);
```

`b` は十進表記の値が3または5で割り切れる列、`c` はどちらでも割り切れない列を受理する。
数字の条件には `math/digit_dfa.cpp` を include する。表は固定長の文字列 DP にも使える。
先頭 0 や数値の上下限はこの表では扱わない。

```cpp
long long count = digit_count<long long>("1", "100", b);
```

`math/digit_dp.cpp` を include すれば、1以上100以下で3または5で割り切れる整数の個数 `47` が得られる。

## 実装上の補足
入力状態数を $S_1,S_2$、到達状態対数を $R$ とする。

- `intersect` は $O(S_1S_2+WR)$ 時間、$O(S_1S_2+WR)$ 領域
- `unite` は拒否状態も状態対に含め、$O((S_1+1)(S_2+1)+WR)$ 時間・領域。到達できる状態対だけを返し、両方が拒否した遷移は `-1` にする
- `complement` は入力状態数を $S$ として $O(W(S+1))$ 時間・領域。拒否遷移があれば、以後の全列を受理する状態を1つ足す。`initial == -1` の補集合は全列を受理する1状態となる

AND・OR の状態対の ID 配列は、未到達の組も含めて確保する。この配列が確保可能で、返却状態数が `int` に収まる範囲で使う。
最小化は行わない。必要なら `string/dfa_minimize.cpp` の `minimize(a)` を使う。
