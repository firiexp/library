---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj2907_prefix_suffix_search.test.cpp
    title: test/aoj2907_prefix_suffix_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_trie_prefix_intervals.test.cpp
    title: test/yosupo_aplusb_trie_prefix_intervals.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Trie \u6728"
    links: []
  bundledCode: "#line 1 \"datastructure/trie.cpp\"\ntemplate<int W, class F> // W\
    \ -> word size\nstruct Trie {\n    struct Node {\n        char c;\n        array<int,\
    \ W> nxt;\n        vector<int> idxs;\n        int id;\n        explicit Node(char\
    \ c): c(c), id(-1){\n            fill(nxt.begin(),nxt.end(), -1);\n        }\n\
    \    };\n    vector<Node> v;\n    F f;\n    explicit Trie(F f, char c = '$') :\
    \ f(f) {\n        v.emplace_back(c);\n    }\n    void add(const string &s, int\
    \ x){\n        int cur = 0;\n        for (auto &&i : s) {\n            int k =\
    \ f(i);\n            if(~v[cur].nxt[k]){\n                cur = v[cur].nxt[k];\n\
    \                continue;\n            }\n            int npos = v.size();\n\
    \            v[cur].nxt[k] = npos;\n            v.emplace_back(i);\n         \
    \   cur = npos;\n        }\n        v[cur].id = x;\n        v[cur].idxs.emplace_back(x);\n\
    \    }\n\n    int find(const string &s){\n        int cur = 0;\n        for (auto\
    \ &&i : s) {\n            int k = f(i);\n            if(v[cur].nxt[k] < 0) return\
    \ -1;\n            cur = v[cur].nxt[k];\n        }\n        return cur;\n    }\n\
    \    int find(int cur, char c) {return v[cur].nxt[f(c)]; }\n    int id(int cur)\
    \ { return cur < 0 ? -1 : v[cur].id;}\n\n    vector<int> idxs(int cur) { return\
    \ cur < 0 ? vector<int>() : v[cur].idxs; }\n\n    struct PrefixIntervals {\n \
    \       vector<int> order;\n        vector<pair<int, int>> range;\n    };\n\n\
    \    PrefixIntervals prefix_intervals() const {\n        PrefixIntervals result;\n\
    \        result.range.resize(v.size());\n        vector<pair<int, int>> stack{{0,\
    \ 0}};\n        while (!stack.empty()) {\n            int node = stack.back().first;\n\
    \            int& next = stack.back().second;\n            if (next == 0) {\n\
    \                result.range[node].first = result.order.size();\n           \
    \     result.order.insert(result.order.end(), v[node].idxs.begin(), v[node].idxs.end());\n\
    \            }\n            while (next < W && v[node].nxt[next] == -1) ++next;\n\
    \            if (next == W) {\n                result.range[node].second = result.order.size();\n\
    \                stack.pop_back();\n            } else {\n                int\
    \ child = v[node].nxt[next++];\n                stack.emplace_back(child, 0);\n\
    \            }\n        }\n        return result;\n    }\n};\n\n/**\n * @brief\
    \ Trie \u6728\n */\n"
  code: "template<int W, class F> // W -> word size\nstruct Trie {\n    struct Node\
    \ {\n        char c;\n        array<int, W> nxt;\n        vector<int> idxs;\n\
    \        int id;\n        explicit Node(char c): c(c), id(-1){\n            fill(nxt.begin(),nxt.end(),\
    \ -1);\n        }\n    };\n    vector<Node> v;\n    F f;\n    explicit Trie(F\
    \ f, char c = '$') : f(f) {\n        v.emplace_back(c);\n    }\n    void add(const\
    \ string &s, int x){\n        int cur = 0;\n        for (auto &&i : s) {\n   \
    \         int k = f(i);\n            if(~v[cur].nxt[k]){\n                cur\
    \ = v[cur].nxt[k];\n                continue;\n            }\n            int\
    \ npos = v.size();\n            v[cur].nxt[k] = npos;\n            v.emplace_back(i);\n\
    \            cur = npos;\n        }\n        v[cur].id = x;\n        v[cur].idxs.emplace_back(x);\n\
    \    }\n\n    int find(const string &s){\n        int cur = 0;\n        for (auto\
    \ &&i : s) {\n            int k = f(i);\n            if(v[cur].nxt[k] < 0) return\
    \ -1;\n            cur = v[cur].nxt[k];\n        }\n        return cur;\n    }\n\
    \    int find(int cur, char c) {return v[cur].nxt[f(c)]; }\n    int id(int cur)\
    \ { return cur < 0 ? -1 : v[cur].id;}\n\n    vector<int> idxs(int cur) { return\
    \ cur < 0 ? vector<int>() : v[cur].idxs; }\n\n    struct PrefixIntervals {\n \
    \       vector<int> order;\n        vector<pair<int, int>> range;\n    };\n\n\
    \    PrefixIntervals prefix_intervals() const {\n        PrefixIntervals result;\n\
    \        result.range.resize(v.size());\n        vector<pair<int, int>> stack{{0,\
    \ 0}};\n        while (!stack.empty()) {\n            int node = stack.back().first;\n\
    \            int& next = stack.back().second;\n            if (next == 0) {\n\
    \                result.range[node].first = result.order.size();\n           \
    \     result.order.insert(result.order.end(), v[node].idxs.begin(), v[node].idxs.end());\n\
    \            }\n            while (next < W && v[node].nxt[next] == -1) ++next;\n\
    \            if (next == W) {\n                result.range[node].second = result.order.size();\n\
    \                stack.pop_back();\n            } else {\n                int\
    \ child = v[node].nxt[next++];\n                stack.emplace_back(child, 0);\n\
    \            }\n        }\n        return result;\n    }\n};\n\n/**\n * @brief\
    \ Trie \u6728\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/trie.cpp
  requiredBy: []
  timestamp: '2026-10-11 15:44:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj2907_prefix_suffix_search.test.cpp
  - test/yosupo_aplusb_trie_prefix_intervals.test.cpp
date: 2018-04-28
documentation_of: datastructure/trie.cpp
layout: document
tags: "\u6587\u5B57\u5217"
title: "Trie \u6728"
---

## 説明
文字列を prefix ごとにまとめる木。文字列挿入、完全一致検索、prefix からの遷移を $O(|S|)$ で扱う。
固定文字種 `W` と文字変換関数 `F` を前提にした実装である。

## できること
- `Trie<W, F> trie(f, c = '$')`
  文字変換関数 `f` を使って Trie を作る。`c` は根ノードの表示用文字
- `add(s, x)`
  文字列 `s` を id `x` で挿入する。終端ノードに `x` を記録する
- `find(s)`
  文字列 `s` の終端ノード番号を返す。見つからなければ `-1`
- `find(cur, c)`
  ノード `cur` から文字 `c` で遷移した先を返す。無ければ `-1`
- `id(cur)`
  ノード `cur` に対応する終端 id を返す。終端でなければ `-1`
- `idxs(cur)`
  ノード `cur` に対応する id 一覧を返す。無ければ空
- `PrefixIntervals prefix_intervals() const`
  単語IDの列 `order` と、各ノードに対応する半開区間 `range` を返す。ノード数を $V$、登録した単語数を $K$ として $O(WV+K)$ 時間、$O(V+K)$ 領域

## 使い方
`F` は文字を `0` 以上 `W-1` 以下に写す関数として用意する。
`find` で prefix の終端ノードを取り、そのノードの `id` や `idxs` を参照する。

```cpp
auto f = [](char c) { return c - 'a'; };
Trie<26, decltype(f)> trie(f);
trie.add("apple", 0);
int node = trie.find("app");
auto index = trie.prefix_intervals();
auto [l, r] = index.range[node];
```

`index.order[l..r)` は、`"app"` を prefix に持つ登録単語のID列となる。
`find` が `-1` を返した場合、その prefix を持つ単語はない。
`order` は文字変換関数 `f` の順に並び、同じ終端のIDは挿入順を保つ。
空文字や同じIDの複数登録も含まれる。単語を追加した後は `prefix_intervals()` を呼び直す。

## 実装上の補足
- 同じ文字列を複数回挿入すると `idxs(cur)` に id が追加される。`id(cur)` は最後に入れた値になる
- `find(cur, c)` は `cur < 0` を自動では防がないので、呼び出し側で確認する
