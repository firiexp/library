---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_eertree.test.cpp
    title: test/yosupo_eertree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/palindromic_tree.md
    document_title: "\u56DE\u6587\u6728(Palindromic Tree)"
    links: []
  bundledCode: "#line 1 \"string/palindromic_tree.cpp\"\ntemplate<int W, char start\
    \ = 'a'>\nstruct PalindromicTree {\n    struct Node {\n        int link;\n   \
    \     int len;\n        int first_pos;\n        int occ;\n        int next[W];\n\
    \n        Node(int link = 0, int len = 0, int first_pos = -1)\n            : link(link),\
    \ len(len), first_pos(first_pos), occ(0) {\n            fill(next, next + W, -1);\n\
    \        }\n    };\n\n    vector<Node> nodes;\n    vector<int> path;\n    string\
    \ s;\n    int last;\n\n    PalindromicTree(): nodes(), path(), s(), last(1) {\n\
    \        nodes.reserve(2);\n        nodes.emplace_back(0, -1, -1);\n        nodes.emplace_back(0,\
    \ 0, -1);\n    }\n\n    explicit PalindromicTree(const string &t): PalindromicTree()\
    \ {\n        reserve(t.size());\n        build(t);\n    }\n\n    void reserve(int\
    \ n) {\n        nodes.reserve(n + 2);\n        path.reserve(n);\n        s.reserve(n);\n\
    \    }\n\n    static int ord(char c) {\n        return c - start;\n    }\n\n \
    \   int suffix_link(int v, int pos, int c) const {\n        while (true) {\n \
    \           int j = pos - 1 - nodes[v].len;\n            if (j >= 0 && ord(s[j])\
    \ == c) return v;\n            v = nodes[v].link;\n        }\n    }\n\n    int\
    \ add(char ch) {\n        int c = ord(ch);\n        int pos = s.size();\n    \
    \    s.push_back(ch);\n\n        int p = suffix_link(last, pos, c);\n        if\
    \ (nodes[p].next[c] != -1) {\n            last = nodes[p].next[c];\n         \
    \   ++nodes[last].occ;\n            path.push_back(last);\n            return\
    \ last;\n        }\n\n        int cur = nodes.size();\n        nodes.emplace_back(0,\
    \ nodes[p].len + 2, pos);\n        nodes[p].next[c] = cur;\n        if (nodes[cur].len\
    \ == 1) {\n            nodes[cur].link = 1;\n        } else {\n            int\
    \ q = suffix_link(nodes[p].link, pos, c);\n            nodes[cur].link = nodes[q].next[c];\n\
    \        }\n        last = cur;\n        ++nodes[last].occ;\n        path.push_back(last);\n\
    \        return last;\n    }\n\n    void build(const string &t) {\n        for\
    \ (auto &&c : t) add(c);\n    }\n\n    vector<int> count() const {\n        vector<int>\
    \ res(nodes.size());\n        for (int i = 0; i < (int)nodes.size(); ++i) res[i]\
    \ = nodes[i].occ;\n        vector<int> ord(nodes.size());\n        iota(ord.begin(),\
    \ ord.end(), 0);\n        sort(ord.begin(), ord.end(), [&](int a, int b) { return\
    \ nodes[a].len > nodes[b].len; });\n        for (auto &&v : ord) {\n         \
    \   if (v >= 2) res[nodes[v].link] += res[v];\n        }\n        return res;\n\
    \    }\n};\n\n/**\n * @brief \u56DE\u6587\u6728(Palindromic Tree)\n * @docs _md/palindromic_tree.md\n\
    \ */\n"
  code: "template<int W, char start = 'a'>\nstruct PalindromicTree {\n    struct Node\
    \ {\n        int link;\n        int len;\n        int first_pos;\n        int\
    \ occ;\n        int next[W];\n\n        Node(int link = 0, int len = 0, int first_pos\
    \ = -1)\n            : link(link), len(len), first_pos(first_pos), occ(0) {\n\
    \            fill(next, next + W, -1);\n        }\n    };\n\n    vector<Node>\
    \ nodes;\n    vector<int> path;\n    string s;\n    int last;\n\n    PalindromicTree():\
    \ nodes(), path(), s(), last(1) {\n        nodes.reserve(2);\n        nodes.emplace_back(0,\
    \ -1, -1);\n        nodes.emplace_back(0, 0, -1);\n    }\n\n    explicit PalindromicTree(const\
    \ string &t): PalindromicTree() {\n        reserve(t.size());\n        build(t);\n\
    \    }\n\n    void reserve(int n) {\n        nodes.reserve(n + 2);\n        path.reserve(n);\n\
    \        s.reserve(n);\n    }\n\n    static int ord(char c) {\n        return\
    \ c - start;\n    }\n\n    int suffix_link(int v, int pos, int c) const {\n  \
    \      while (true) {\n            int j = pos - 1 - nodes[v].len;\n         \
    \   if (j >= 0 && ord(s[j]) == c) return v;\n            v = nodes[v].link;\n\
    \        }\n    }\n\n    int add(char ch) {\n        int c = ord(ch);\n      \
    \  int pos = s.size();\n        s.push_back(ch);\n\n        int p = suffix_link(last,\
    \ pos, c);\n        if (nodes[p].next[c] != -1) {\n            last = nodes[p].next[c];\n\
    \            ++nodes[last].occ;\n            path.push_back(last);\n         \
    \   return last;\n        }\n\n        int cur = nodes.size();\n        nodes.emplace_back(0,\
    \ nodes[p].len + 2, pos);\n        nodes[p].next[c] = cur;\n        if (nodes[cur].len\
    \ == 1) {\n            nodes[cur].link = 1;\n        } else {\n            int\
    \ q = suffix_link(nodes[p].link, pos, c);\n            nodes[cur].link = nodes[q].next[c];\n\
    \        }\n        last = cur;\n        ++nodes[last].occ;\n        path.push_back(last);\n\
    \        return last;\n    }\n\n    void build(const string &t) {\n        for\
    \ (auto &&c : t) add(c);\n    }\n\n    vector<int> count() const {\n        vector<int>\
    \ res(nodes.size());\n        for (int i = 0; i < (int)nodes.size(); ++i) res[i]\
    \ = nodes[i].occ;\n        vector<int> ord(nodes.size());\n        iota(ord.begin(),\
    \ ord.end(), 0);\n        sort(ord.begin(), ord.end(), [&](int a, int b) { return\
    \ nodes[a].len > nodes[b].len; });\n        for (auto &&v : ord) {\n         \
    \   if (v >= 2) res[nodes[v].link] += res[v];\n        }\n        return res;\n\
    \    }\n};\n\n/**\n * @brief \u56DE\u6587\u6728(Palindromic Tree)\n * @docs _md/palindromic_tree.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/palindromic_tree.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_eertree.test.cpp
documentation_of: string/palindromic_tree.cpp
layout: document
redirect_from:
- /library/string/palindromic_tree.cpp
- /library/string/palindromic_tree.cpp.html
title: "\u56DE\u6587\u6728(Palindromic Tree)"
---
## 説明
文字列の異なる回文部分文字列を管理する eertree である。
1 文字ずつ追加しながら構築でき、全体 `O(NW)` ではなく遷移参照込みで `O(N)`、固定アルファベットなら実用上ほぼ線形で動く。

## できること
- `PalindromicTree<W, start> pt`
  空の palindromic tree を作る
- `PalindromicTree<W, start> pt(s)`
  文字列 `s` から構築する
- `void reserve(int n)`
  長さ `n` を見込んで領域を確保する
- `int add(char c)`
  末尾に文字 `c` を追加し、できた最長回文接尾辞のノード番号を返す
- `vector<int> count()`
  各ノードの出現回数を返す

## 使い方
根は 2 個あり、`0` が長さ `-1`、`1` が長さ `0` を表す。
通常の回文ノードは `2` 以降に追加される。
`path[i]` には prefix `s[0..i]` の最長回文接尾辞のノード番号が入る。

```cpp
PalindromicTree<26> pt;
for (char c : s) pt.add(c);

for (int v = 2; v < (int)pt.nodes.size(); ++v) {
    int len = pt.nodes[v].len;
    int link = pt.nodes[v].link;
}
```

## 実装上の補足
`W` はアルファベット数、`start` は最小文字である。
`PalindromicTree<26, 'a'>` なら小文字英字用になる。
