---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_suffix_automaton_kth.test.cpp
    title: test/yosupo_aplusb_suffix_automaton_kth.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_suffix_automaton_lcs.test.cpp
    title: test/yosupo_aplusb_suffix_automaton_lcs.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_suffix_automaton_occurrences.test.cpp
    title: test/yosupo_aplusb_suffix_automaton_occurrences.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_longest_common_substring.test.cpp
    title: test/yosupo_longest_common_substring.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
    title: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Suffix Automaton
    links: []
  bundledCode: "#line 1 \"string/suffix_automaton.cpp\"\ntemplate<int W, char start\
    \ = 'a'>\nstruct SuffixAutomaton {\n    struct Node {\n        int link;\n   \
    \     int len;\n        int occ;\n        int first_pos;\n        int next[W];\n\
    \        Node(int link = -1, int len = 0, int occ = 0): link(link), len(len),\
    \ occ(occ), first_pos(len - 1) {\n            fill(next, next + W, -1);\n    \
    \    }\n    };\n\n    vector<Node> nodes;\n    int last;\n\n    struct SubstringMatch\
    \ {\n        int s_l, s_r, t_l, t_r;\n    };\n\n    SuffixAutomaton(): nodes(1),\
    \ last(0) {}\n\n    template<class T>\n    explicit SuffixAutomaton(const T &s):\
    \ SuffixAutomaton() {\n        reserve(s.size());\n        for (auto &&c : s)\
    \ add(c);\n    }\n\n    void reserve(int n) {\n        nodes.reserve(2 * n + 1);\n\
    \    }\n\n    static int ord(char c) {\n        return c - start;\n    }\n\n \
    \   int add(char c) {\n        ways.clear();\n        int k = ord(c);\n      \
    \  int cur = nodes.size();\n        nodes.emplace_back(0, nodes[last].len + 1,\
    \ 1);\n        int p = last;\n        while (p != -1 && nodes[p].next[k] == -1)\
    \ {\n            nodes[p].next[k] = cur;\n            p = nodes[p].link;\n   \
    \     }\n        if (p == -1) {\n            nodes[cur].link = 0;\n          \
    \  last = cur;\n            return cur;\n        }\n        int q = nodes[p].next[k];\n\
    \        if (nodes[p].len + 1 == nodes[q].len) {\n            nodes[cur].link\
    \ = q;\n            last = cur;\n            return cur;\n        }\n        int\
    \ clone = nodes.size();\n        nodes.push_back(nodes[q]);\n        nodes[clone].len\
    \ = nodes[p].len + 1;\n        nodes[clone].occ = 0;\n        while (p != -1 &&\
    \ nodes[p].next[k] == q) {\n            nodes[p].next[k] = clone;\n          \
    \  p = nodes[p].link;\n        }\n        nodes[q].link = nodes[cur].link = clone;\n\
    \        last = cur;\n        return cur;\n    }\n\n    template<class T>\n  \
    \  void build(const T &s) {\n        reserve(s.size());\n        for (auto &&c\
    \ : s) add(c);\n    }\n\n    template<class T>\n    SubstringMatch longest_common_substring(const\
    \ T &t) const {\n        SubstringMatch result{0, 0, 0, 0};\n        int state\
    \ = 0, length = 0, index = 0;\n        for (auto c : t) {\n            int k =\
    \ ord(c);\n            if (k < 0 || k >= W) {\n                state = length\
    \ = 0;\n            } else {\n                while (state && nodes[state].next[k]\
    \ == -1) {\n                    state = nodes[state].link;\n                 \
    \   length = nodes[state].len;\n                }\n                if (nodes[state].next[k]\
    \ == -1) length = 0;\n                else {\n                    state = nodes[state].next[k];\n\
    \                    ++length;\n                }\n                if (length\
    \ > result.s_r - result.s_l) {\n                    int end = nodes[state].first_pos\
    \ + 1;\n                    result = {end - length, end, index + 1 - length, index\
    \ + 1};\n                }\n            }\n            ++index;\n        }\n \
    \       return result;\n    }\n\n    long long count_distinct_substrings() const\
    \ {\n        long long res = 0;\n        for (int i = 1; i < (int)nodes.size();\
    \ ++i) {\n            res += nodes[i].len - nodes[nodes[i].link].len;\n      \
    \  }\n        return res;\n    }\n\n    optional<pair<int, int>> kth_substring(long\
    \ long k) const {\n        if (k < 0) return nullopt;\n        if (ways.empty())\
    \ {\n            auto order = order_by_length();\n            ways.assign(nodes.size(),\
    \ 1);\n            for (int i = (int)order.size() - 1; i >= 0; --i) {\n      \
    \          int v = order[i];\n                for (int to : nodes[v].next) if\
    \ (to != -1) ways[v] += ways[to];\n            }\n        }\n        if (k >=\
    \ ways[0] - 1) return nullopt;\n        int v = 0, length = 0;\n        while\
    \ (true) {\n            for (int to : nodes[v].next) {\n                if (to\
    \ == -1) continue;\n                if (k >= ways[to]) {\n                   \
    \ k -= ways[to];\n                    continue;\n                }\n         \
    \       v = to;\n                ++length;\n                if (k == 0) {\n  \
    \                  int end = nodes[v].first_pos + 1;\n                    return\
    \ pair<int, int>{end - length, end};\n                }\n                --k;\n\
    \                break;\n            }\n        }\n    }\n\n    vector<int> order_by_length()\
    \ const {\n        int max_len = 0;\n        for (auto &&node : nodes) max_len\
    \ = max(max_len, node.len);\n        vector<int> cnt(max_len + 1);\n        for\
    \ (auto &&node : nodes) cnt[node.len]++;\n        for (int i = 1; i <= max_len;\
    \ ++i) cnt[i] += cnt[i - 1];\n        vector<int> ord(nodes.size());\n       \
    \ for (int i = (int)nodes.size() - 1; i >= 0; --i) {\n            ord[--cnt[nodes[i].len]]\
    \ = i;\n        }\n        return ord;\n    }\n\n    vector<int> substring_occurrences()\
    \ const {\n        vector<int> cnt(nodes.size());\n        for (int i = 0; i <\
    \ (int)nodes.size(); ++i) cnt[i] = nodes[i].occ;\n        auto ord = order_by_length();\n\
    \        for (int i = (int)ord.size() - 1; i >= 1; --i) {\n            int v =\
    \ ord[i];\n            cnt[nodes[v].link] += cnt[v];\n        }\n        return\
    \ cnt;\n    }\n\nprivate:\n    mutable vector<long long> ways;\n};\n/**\n * @brief\
    \ Suffix Automaton\n */\n"
  code: "template<int W, char start = 'a'>\nstruct SuffixAutomaton {\n    struct Node\
    \ {\n        int link;\n        int len;\n        int occ;\n        int first_pos;\n\
    \        int next[W];\n        Node(int link = -1, int len = 0, int occ = 0):\
    \ link(link), len(len), occ(occ), first_pos(len - 1) {\n            fill(next,\
    \ next + W, -1);\n        }\n    };\n\n    vector<Node> nodes;\n    int last;\n\
    \n    struct SubstringMatch {\n        int s_l, s_r, t_l, t_r;\n    };\n\n   \
    \ SuffixAutomaton(): nodes(1), last(0) {}\n\n    template<class T>\n    explicit\
    \ SuffixAutomaton(const T &s): SuffixAutomaton() {\n        reserve(s.size());\n\
    \        for (auto &&c : s) add(c);\n    }\n\n    void reserve(int n) {\n    \
    \    nodes.reserve(2 * n + 1);\n    }\n\n    static int ord(char c) {\n      \
    \  return c - start;\n    }\n\n    int add(char c) {\n        ways.clear();\n\
    \        int k = ord(c);\n        int cur = nodes.size();\n        nodes.emplace_back(0,\
    \ nodes[last].len + 1, 1);\n        int p = last;\n        while (p != -1 && nodes[p].next[k]\
    \ == -1) {\n            nodes[p].next[k] = cur;\n            p = nodes[p].link;\n\
    \        }\n        if (p == -1) {\n            nodes[cur].link = 0;\n       \
    \     last = cur;\n            return cur;\n        }\n        int q = nodes[p].next[k];\n\
    \        if (nodes[p].len + 1 == nodes[q].len) {\n            nodes[cur].link\
    \ = q;\n            last = cur;\n            return cur;\n        }\n        int\
    \ clone = nodes.size();\n        nodes.push_back(nodes[q]);\n        nodes[clone].len\
    \ = nodes[p].len + 1;\n        nodes[clone].occ = 0;\n        while (p != -1 &&\
    \ nodes[p].next[k] == q) {\n            nodes[p].next[k] = clone;\n          \
    \  p = nodes[p].link;\n        }\n        nodes[q].link = nodes[cur].link = clone;\n\
    \        last = cur;\n        return cur;\n    }\n\n    template<class T>\n  \
    \  void build(const T &s) {\n        reserve(s.size());\n        for (auto &&c\
    \ : s) add(c);\n    }\n\n    template<class T>\n    SubstringMatch longest_common_substring(const\
    \ T &t) const {\n        SubstringMatch result{0, 0, 0, 0};\n        int state\
    \ = 0, length = 0, index = 0;\n        for (auto c : t) {\n            int k =\
    \ ord(c);\n            if (k < 0 || k >= W) {\n                state = length\
    \ = 0;\n            } else {\n                while (state && nodes[state].next[k]\
    \ == -1) {\n                    state = nodes[state].link;\n                 \
    \   length = nodes[state].len;\n                }\n                if (nodes[state].next[k]\
    \ == -1) length = 0;\n                else {\n                    state = nodes[state].next[k];\n\
    \                    ++length;\n                }\n                if (length\
    \ > result.s_r - result.s_l) {\n                    int end = nodes[state].first_pos\
    \ + 1;\n                    result = {end - length, end, index + 1 - length, index\
    \ + 1};\n                }\n            }\n            ++index;\n        }\n \
    \       return result;\n    }\n\n    long long count_distinct_substrings() const\
    \ {\n        long long res = 0;\n        for (int i = 1; i < (int)nodes.size();\
    \ ++i) {\n            res += nodes[i].len - nodes[nodes[i].link].len;\n      \
    \  }\n        return res;\n    }\n\n    optional<pair<int, int>> kth_substring(long\
    \ long k) const {\n        if (k < 0) return nullopt;\n        if (ways.empty())\
    \ {\n            auto order = order_by_length();\n            ways.assign(nodes.size(),\
    \ 1);\n            for (int i = (int)order.size() - 1; i >= 0; --i) {\n      \
    \          int v = order[i];\n                for (int to : nodes[v].next) if\
    \ (to != -1) ways[v] += ways[to];\n            }\n        }\n        if (k >=\
    \ ways[0] - 1) return nullopt;\n        int v = 0, length = 0;\n        while\
    \ (true) {\n            for (int to : nodes[v].next) {\n                if (to\
    \ == -1) continue;\n                if (k >= ways[to]) {\n                   \
    \ k -= ways[to];\n                    continue;\n                }\n         \
    \       v = to;\n                ++length;\n                if (k == 0) {\n  \
    \                  int end = nodes[v].first_pos + 1;\n                    return\
    \ pair<int, int>{end - length, end};\n                }\n                --k;\n\
    \                break;\n            }\n        }\n    }\n\n    vector<int> order_by_length()\
    \ const {\n        int max_len = 0;\n        for (auto &&node : nodes) max_len\
    \ = max(max_len, node.len);\n        vector<int> cnt(max_len + 1);\n        for\
    \ (auto &&node : nodes) cnt[node.len]++;\n        for (int i = 1; i <= max_len;\
    \ ++i) cnt[i] += cnt[i - 1];\n        vector<int> ord(nodes.size());\n       \
    \ for (int i = (int)nodes.size() - 1; i >= 0; --i) {\n            ord[--cnt[nodes[i].len]]\
    \ = i;\n        }\n        return ord;\n    }\n\n    vector<int> substring_occurrences()\
    \ const {\n        vector<int> cnt(nodes.size());\n        for (int i = 0; i <\
    \ (int)nodes.size(); ++i) cnt[i] = nodes[i].occ;\n        auto ord = order_by_length();\n\
    \        for (int i = (int)ord.size() - 1; i >= 1; --i) {\n            int v =\
    \ ord[i];\n            cnt[nodes[v].link] += cnt[v];\n        }\n        return\
    \ cnt;\n    }\n\nprivate:\n    mutable vector<long long> ways;\n};\n/**\n * @brief\
    \ Suffix Automaton\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_automaton.cpp
  requiredBy: []
  timestamp: '2026-10-17 18:45:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_suffix_automaton_kth.test.cpp
  - test/yosupo_number_of_substrings_suffix_automaton.test.cpp
  - test/yosupo_aplusb_suffix_automaton_occurrences.test.cpp
  - test/yosupo_longest_common_substring.test.cpp
  - test/yosupo_aplusb_suffix_automaton_lcs.test.cpp
date: 2026-03-08
documentation_of: string/suffix_automaton.cpp
layout: document
tags: "\u6587\u5B57\u5217"
title: Suffix Automaton
---

## 説明

文字列から Suffix Automaton を構築し、異なる部分文字列の個数や辞書順 k 番目を求める。
各状態の出現回数の集計や、別文字列との最長共通部分文字列の検索にも使える。

## できること

元の文字列 `s` の長さを $N$、状態数を $V$ とする。文字種数 `W` は定数として扱う。

- `SuffixAutomaton<W, start> sam` : 空文字列から $O(1)$ で構築する
- `SuffixAutomaton<W, start> sam(s)` : 文字列 `s` から $O(N)$ で構築する
- `reserve(n)` : 長さ `n` を見込んで状態の領域を確保する。$O(n)$
- `add(c)` : 末尾に文字 `c` を追加し、追加後の文字列全体に対応する状態番号を返す。償却 $O(1)$
- `build(t)` : 末尾に文字列 `t` を追加する。償却 $O(|t|)$
- `count_distinct_substrings()` : 異なる部分文字列数を返す。$O(V)$
- `kth_substring(k)` : 異なる非空部分文字列を辞書順に並べたときの `k` 番目を返す。`k` は0-indexed。返り値は元文字列上の半開区間 `[l,r)` を表す `optional<pair<int,int>>` で、負数・範囲外は `nullopt`
- `substring_occurrences()` : 各状態の出現回数を状態番号順の `vector<int>` で返す。$O(V+N)$
- `order_by_length()` : 各状態が表す最大長の昇順に状態番号を返す。$O(V+N)$
- `longest_common_substring(t)` : `s` と `t` の最長共通部分文字列の位置を `SubstringMatch` で返す。時間 $O(|t|)$、返却値以外の追加領域 $O(1)$

`kth_substring` は初回の準備に $O(WV)$、各クエリに最悪 $O(WN)$ かかる。追加領域は $O(V)$。
文字を追加すると、次のクエリで準備をやり直す。

## 使い方

`SuffixAutomaton<26, 'a'> sam(s);` のように文字種数と開始文字を指定する。
構築時や `add(c)` で追加する文字は `start <= c < start + W` を満たす前提。

辞書順 k 番目の部分文字列は返された区間を使って取り出す。

```cpp
string s = "ababa";
SuffixAutomaton<26> sam(s);
if (auto range = sam.kth_substring(2)) {
    auto [l, r] = *range;
    cout << s.substr(l, r - l) << '\n';
}
```

この例では `"aba"` を出力する。
同じ部分文字列が複数の位置に現れても1種類として数え、出現位置は任意の1つを返す。
辞書順は `start` からの文字の順とする。空文字列から構築した場合は全ての `k` に対して `nullopt` を返す。

最長共通部分文字列は `auto match = sam.longest_common_substring(t);` で求める。
`[match.s_l, match.s_r)` が `s` 側、`[match.t_l, match.t_r)` が `t` 側の0-indexed半開区間を表す。
最長の答えが複数ある場合は任意の1組を返す。共通部分が空なら4つとも `0`。
集計・照合は構築済みオートマトンを変更せず、`add` の後も再構築せず繰り返せる。

## 実装上の補足

- `nodes[v].len` は状態 `v` が表す文字列の最大長。
- `nodes[v].link` は suffix link。
- `nodes[v].next` は遷移。
- `nodes[v].first_pos` は代表となる出現の末尾位置。clone は複製元の位置を引き継ぐ。
- `substring_occurrences()` は状態ごとに出現回数を集計する。クローン状態の出現回数は構築時に `0` とし、集計時に加算する。
- `kth_substring` に必要な部分文字列数は `long long` で保持する。初回クエリで集計して再利用し、`add` / `build` で文字を追加したら次のクエリで再計算する。クエリを呼ばない用途ではこの集計を行わない。
- `nodes` / `last` は参照用とし、直接の書き換えには対応しない。直接書き換えた場合はキャッシュとの整合性も保証されない。
