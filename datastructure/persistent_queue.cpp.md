---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_persistent_queue.test.cpp
    title: test/yosupo_aplusb_persistent_queue.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_persistent_queue.test.cpp
    title: test/yosupo_persistent_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6C38\u7D9A\u30AD\u30E5\u30FC"
    links: []
  bundledCode: "#line 1 \"datastructure/persistent_queue.cpp\"\ntemplate<class T>\n\
    class PersistentQueue {\n    struct Node {\n        T value;\n        int depth;\n\
    \        size_t offset;\n    };\n    struct Version {\n        int tail, length;\n\
    \    };\n\n    vector<Node> nodes;\n    vector<int> ancestors;\n    vector<Version>\
    \ versions{{-1, 0}};\n\npublic:\n    int push(int version, const T &value) {\n\
    \        assert(0 <= version && version < (int)versions.size());\n        auto\
    \ state = versions[version];\n        int depth = state.tail == -1 ? 1 : nodes[state.tail].depth\
    \ + 1;\n        size_t offset = ancestors.size();\n        ancestors.push_back(state.tail);\n\
    \        for (int bit = 1; (1LL << bit) < depth; ++bit) {\n            int half\
    \ = ancestors[offset + bit - 1];\n            ancestors.push_back(ancestors[nodes[half].offset\
    \ + bit - 1]);\n        }\n        int id = (int)nodes.size();\n        nodes.push_back({value,\
    \ depth, offset});\n        versions.push_back({id, state.length + 1});\n    \
    \    return (int)versions.size() - 1;\n    }\n\n    int pop(int version) {\n \
    \       assert(!empty(version));\n        auto state = versions[version];\n  \
    \      if (--state.length == 0) state.tail = -1;\n        versions.push_back(state);\n\
    \        return (int)versions.size() - 1;\n    }\n\n    T front(int version) const\
    \ {\n        assert(!empty(version));\n        int node = versions[version].tail;\n\
    \        int distance = versions[version].length - 1;\n        for (int bit =\
    \ 0; distance; ++bit, distance >>= 1)\n            if (distance & 1) node = ancestors[nodes[node].offset\
    \ + bit];\n        return nodes[node].value;\n    }\n\n    int size(int version)\
    \ const {\n        assert(0 <= version && version < (int)versions.size());\n \
    \       return versions[version].length;\n    }\n\n    bool empty(int version)\
    \ const { return size(version) == 0; }\n};\n\n/**\n * @brief \u6C38\u7D9A\u30AD\
    \u30E5\u30FC\n */\n"
  code: "template<class T>\nclass PersistentQueue {\n    struct Node {\n        T\
    \ value;\n        int depth;\n        size_t offset;\n    };\n    struct Version\
    \ {\n        int tail, length;\n    };\n\n    vector<Node> nodes;\n    vector<int>\
    \ ancestors;\n    vector<Version> versions{{-1, 0}};\n\npublic:\n    int push(int\
    \ version, const T &value) {\n        assert(0 <= version && version < (int)versions.size());\n\
    \        auto state = versions[version];\n        int depth = state.tail == -1\
    \ ? 1 : nodes[state.tail].depth + 1;\n        size_t offset = ancestors.size();\n\
    \        ancestors.push_back(state.tail);\n        for (int bit = 1; (1LL << bit)\
    \ < depth; ++bit) {\n            int half = ancestors[offset + bit - 1];\n   \
    \         ancestors.push_back(ancestors[nodes[half].offset + bit - 1]);\n    \
    \    }\n        int id = (int)nodes.size();\n        nodes.push_back({value, depth,\
    \ offset});\n        versions.push_back({id, state.length + 1});\n        return\
    \ (int)versions.size() - 1;\n    }\n\n    int pop(int version) {\n        assert(!empty(version));\n\
    \        auto state = versions[version];\n        if (--state.length == 0) state.tail\
    \ = -1;\n        versions.push_back(state);\n        return (int)versions.size()\
    \ - 1;\n    }\n\n    T front(int version) const {\n        assert(!empty(version));\n\
    \        int node = versions[version].tail;\n        int distance = versions[version].length\
    \ - 1;\n        for (int bit = 0; distance; ++bit, distance >>= 1)\n         \
    \   if (distance & 1) node = ancestors[nodes[node].offset + bit];\n        return\
    \ nodes[node].value;\n    }\n\n    int size(int version) const {\n        assert(0\
    \ <= version && version < (int)versions.size());\n        return versions[version].length;\n\
    \    }\n\n    bool empty(int version) const { return size(version) == 0; }\n};\n\
    \n/**\n * @brief \u6C38\u7D9A\u30AD\u30E5\u30FC\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/persistent_queue.cpp
  requiredBy: []
  timestamp: '2026-10-10 18:53:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_persistent_queue.test.cpp
  - test/yosupo_aplusb_persistent_queue.test.cpp
documentation_of: datastructure/persistent_queue.cpp
layout: document
title: "\u6C38\u7D9A\u30AD\u30E5\u30FC"
---

## 説明
過去の任意versionから末尾追加・先頭削除を分岐できるキュー。
version 0 は空であり、更新は元versionを変更せず新しいversion番号を返す。

## できること
- `PersistentQueue<T> q`：空のversion 0を作る
- `push(version, value)`：末尾に追加した新versionを返す
- `pop(version)`：先頭を削除した新versionを返す。空でないことが前提
- `front(version)`：先頭要素のコピーを返す。空でないことが前提
- `size(version)` / `empty(version)`：要素数 / 空かを返す

## 使い方
操作数の先読みやbuildは不要で、以前返されたversion番号をそのまま使う。

```cpp
PersistentQueue<int> q;
int a = q.push(0, 10);
int b = q.push(a, 20);
int c = q.pop(b);
int d = q.push(a, 30);
```

`b` は `{10,20}`、`c` は `{20}`、`d` は `{10,30}` を保持する。

## 実装上の補足
末尾nodeと長さをversionごとに保持し、先頭はpush履歴の祖先を倍増法で辿って求める。
空になったversionは末尾を切り離し、次のpushを新しい履歴の根にする。
祖先情報は1本の連続配列に格納し、nodeごとの小さな配列確保を行わない。

これまでの更新数を $Q$、push数を $P$ とし、要素コピーを $O(1)$ とすると、`front` は最悪 $O(\log(P+2))$、`size/empty` は最悪 $O(1)$。
`push` は償却 $O(\log(P+2))$、`pop` は償却 $O(1)$。償却は配列の幾何拡張に由来し、過去versionへの分岐回数によって崩れない。
総領域は $O(Q+P\log(P+2))$。
