---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/ahocorasick.cpp
    title: "Aho-Corasick\u6CD5"
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
    path: test/yosupo_aplusb_dfa_minimize.test.cpp
    title: test/yosupo_aplusb_dfa_minimize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_digit_dp.test.cpp
    title: test/yosupo_aplusb_digit_dp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki2867.test.cpp
    title: test/yuki2867.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7981\u6B62\u90E8\u5206\u6587\u5B57\u5217\u3092\u907F\u3051\u308B\
      \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3"
    links: []
  bundledCode: "#line 1 \"string/avoid_patterns.cpp\"\n\n\n\n#line 1 \"string/dfa.cpp\"\
    \n\n\n\ntemplate<int W>\nstruct DFA {\n    vector<array<int, W>> next;\n    vector<char>\
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
    \u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\u6210\n */\n#line 1 \"datastructure/ahocorasick.cpp\"\
    \n\n\n\ntemplate<int W, int start>\nclass AhoCorasick {\npublic:\n    struct Node\
    \ {\n        array<int, W> to;\n        int fail;\n        int val;\n    };\n\
    \    explicit AhoCorasick() : v(1) {}\n    vector<Node> v;\n    vector<int> ord;\n\
    \    int add(const string &s, int cur = 0){\n        for (auto &&i : s) {\n  \
    \          if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();\n\
    \            cur = v[cur].to[i-start];\n        }\n        return cur;\n    }\n\
    \n    void build() {\n        v[0].fail = -1;\n        int l = 0, r = 1;\n   \
    \     ord.clear();\n        ord.reserve(v.size());\n        ord.emplace_back(0);\n\
    \        while(l < r){\n            int i = ord[l]; l++;\n            for (int\
    \ c = 0; c < W; ++c) {\n                if(!v[i].to[c]) continue;\n          \
    \      int to = v[i].to[c];\n                v[to].fail = (v[i].fail == -1 ? 0\
    \ : v[v[i].fail].to[c]);\n                ord.emplace_back(to);\n            \
    \    r++;\n            }\n            if(i != 0){\n                for (int c\
    \ = 0; c < W; ++c) {\n                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];\n\
    \                }\n            }\n        }\n    }\n    inline int next(int x,\
    \ char c){ return v[x].to[c-start]; }\n\n    vector<long long> occurrence_counts(const\
    \ string &text) const {\n        vector<long long> counts(v.size());\n       \
    \ counts[0] = 1;\n        int state = 0;\n        for (char c : text) {\n    \
    \        state = v[state].to[c - start];\n            ++counts[state];\n     \
    \   }\n        for (int i = (int)ord.size() - 1; i > 0; --i) {\n            int\
    \ state = ord[i];\n            counts[v[state].fail] += counts[state];\n     \
    \   }\n        return counts;\n    }\n};\n\n\n\n/**\n * @brief Aho-Corasick\u6CD5\
    \n */\n#line 6 \"string/avoid_patterns.cpp\"\n\ntemplate<int W, int start>\nDFA<W>\
    \ avoid_patterns(const vector<string>& patterns) {\n    AhoCorasick<W, start>\
    \ ac;\n    for (const string& s : patterns) {\n        if (s.empty()) return {};\n\
    \        int v = ac.add(s);\n        ac.v[v].val = 1;\n    }\n    ac.build();\n\
    \    for (int v : ac.ord) {\n        if (v != 0) ac.v[v].val |= ac.v[ac.v[v].fail].val;\n\
    \    }\n    vector<int> id(ac.v.size(), -1), states{0};\n    id[0] = 0;\n    DFA<W>\
    \ result{vector<array<int, W>>(1), vector<char>(1, true), 0};\n    for (int i\
    \ = 0; i < (int)states.size(); ++i) {\n        int v = states[i];\n        for\
    \ (int c = 0; c < W; ++c) {\n            int to = ac.v[v].to[c];\n           \
    \ if (ac.v[to].val) {\n                result.next[i][c] = -1;\n             \
    \   continue;\n            }\n            if (id[to] == -1) {\n              \
    \  id[to] = (int)states.size();\n                states.push_back(to);\n     \
    \           result.next.emplace_back();\n                result.accept.push_back(true);\n\
    \            }\n            result.next[i][c] = id[to];\n        }\n    }\n  \
    \  return result;\n}\n\n\n\n/**\n * @brief \u7981\u6B62\u90E8\u5206\u6587\u5B57\
    \u5217\u3092\u907F\u3051\u308B\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\
    \n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_STRING_AVOID_PATTERNS_CPP\n#define FIRIEXP_LIBRARY_STRING_AVOID_PATTERNS_CPP\n\
    \n#include \"dfa.cpp\"\n#include \"../datastructure/ahocorasick.cpp\"\n\ntemplate<int\
    \ W, int start>\nDFA<W> avoid_patterns(const vector<string>& patterns) {\n   \
    \ AhoCorasick<W, start> ac;\n    for (const string& s : patterns) {\n        if\
    \ (s.empty()) return {};\n        int v = ac.add(s);\n        ac.v[v].val = 1;\n\
    \    }\n    ac.build();\n    for (int v : ac.ord) {\n        if (v != 0) ac.v[v].val\
    \ |= ac.v[ac.v[v].fail].val;\n    }\n    vector<int> id(ac.v.size(), -1), states{0};\n\
    \    id[0] = 0;\n    DFA<W> result{vector<array<int, W>>(1), vector<char>(1, true),\
    \ 0};\n    for (int i = 0; i < (int)states.size(); ++i) {\n        int v = states[i];\n\
    \        for (int c = 0; c < W; ++c) {\n            int to = ac.v[v].to[c];\n\
    \            if (ac.v[to].val) {\n                result.next[i][c] = -1;\n  \
    \              continue;\n            }\n            if (id[to] == -1) {\n   \
    \             id[to] = (int)states.size();\n                states.push_back(to);\n\
    \                result.next.emplace_back();\n                result.accept.push_back(true);\n\
    \            }\n            result.next[i][c] = id[to];\n        }\n    }\n  \
    \  return result;\n}\n\n#endif\n\n/**\n * @brief \u7981\u6B62\u90E8\u5206\u6587\
    \u5B57\u5217\u3092\u907F\u3051\u308B\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\
    \u30F3\n */\n"
  dependsOn:
  - string/dfa.cpp
  - datastructure/ahocorasick.cpp
  isVerificationFile: false
  path: string/avoid_patterns.cpp
  requiredBy: []
  timestamp: '2026-10-17 19:15:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_dfa_minimize.test.cpp
  - test/yuki2867.test.cpp
  - test/yosupo_aplusb_count_words.test.cpp
  - test/yosupo_aplusb_avoid_patterns.test.cpp
documentation_of: string/avoid_patterns.cpp
layout: document
title: "\u7981\u6B62\u90E8\u5206\u6587\u5B57\u5217\u3092\u907F\u3051\u308B\u6709\u9650\
  \u30AA\u30FC\u30C8\u30DE\u30C8\u30F3"
---

## 説明
指定したパターンを部分文字列として含まない列を受理する `DFA<W>` を作る。
Aho-Corasick の failure 先から禁止判定を伝播し、禁止状態を通らず到達できる状態だけを返す。

## できること
- `avoid_patterns<W, start>(patterns)` : `const vector<string>&` から構築済みの遷移表を返す
- 空のパターン群は全列を受理する。空パターンを含むと空列も含めて全拒否となり、`initial == -1` を返す
- 重複パターンや、一方が他方を含むパターン群も扱う

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aab", "bbab", "abab"});
auto b = avoid_patterns<10, '0'>({"4", "9"});
```

パターンの各文字 `c` は既存の Aho-Corasick と同じく `start <= c < start + W` を満たす前提。
返却表の文字番号は `c - start` となる。禁止語を完成させる遷移は `-1`、残る全状態は受理状態。
数値の先頭 0 は扱わず、桁 DP 側で制御する。

## 実装上の補足
パターン数を $K$、総長を $P$、Trie ノード数を $V$ とすると、構築は $O(K+P+WV)$ 時間、$O(WV)$ 領域。
空パターンがあればその場で終了する。パターン数分の終端 ID 配列は保持しない。
返却状態数を $R$ とすると返却表は $O(WR)$ 領域。状態数は `int` に収まる範囲で使う。
