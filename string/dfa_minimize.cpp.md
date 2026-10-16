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
    path: test/yosupo_aplusb_count_words.test.cpp
    title: test/yosupo_aplusb_count_words.test.cpp
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
    document_title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\u6700\u5C0F\
      \u5316"
    links: []
  bundledCode: "#line 1 \"string/dfa_minimize.cpp\"\n\n\n\n#line 1 \"string/dfa.cpp\"\
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
    \        }\n    }\n    return result;\n}\n\n\n\n/**\n * @brief \u6709\u9650\u30AA\
    \u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\u5408\u6210\n */\n#line\
    \ 5 \"string/dfa_minimize.cpp\"\n\ntemplate<int W>\nDFA<W> minimize(const DFA<W>&\
    \ a) {\n    if (a.initial == -1) return {};\n    vector<int> index(a.next.size(),\
    \ -1), states{a.initial};\n    index[a.initial] = 0;\n    for (size_t i = 0; i\
    \ < states.size(); ++i) {\n        for (int to : a.next[states[i]]) {\n      \
    \      if (to != -1 && index[to] == -1) {\n                index[to] = (int)states.size();\n\
    \                states.push_back(to);\n            }\n        }\n    }\n    int\
    \ sink = (int)states.size();\n    assert(sink < numeric_limits<int>::max());\n\
    \    int n = sink + 1;\n    vector<int> order;\n    order.reserve(n);\n    for\
    \ (int v = 0; v < sink; ++v) if (a.accept[states[v]]) order.push_back(v);\n  \
    \  int accepted = (int)order.size();\n    if (accepted == 0) return {};\n    for\
    \ (int v = 0; v < sink; ++v) if (!a.accept[states[v]]) order.push_back(v);\n \
    \   order.push_back(sink);\n    vector<array<int, W>> head(n), link(n);\n    for\
    \ (auto& row : head) row.fill(-1);\n    for (int v = 0; v < n; ++v) {\n      \
    \  for (int c = 0; c < W; ++c) {\n            int to = v == sink ? -1 : a.next[states[v]][c];\n\
    \            to = to == -1 ? sink : index[to];\n            link[v][c] = head[to][c];\n\
    \            head[to][c] = v;\n        }\n    }\n    vector<int> group(n), position(n),\
    \ begin{0, accepted}, end{accepted, n}, marked{0, accepted};\n    for (int i =\
    \ 0; i < n; ++i) group[order[i]] = i >= accepted, position[order[i]] = i;\n  \
    \  vector<int> pending{accepted <= n - accepted ? 0 : 1}, splitter, touched;\n\
    \    while (!pending.empty()) {\n        int block = pending.back();\n       \
    \ pending.pop_back();\n        splitter.assign(order.begin() + begin[block], order.begin()\
    \ + end[block]);\n        for (int c = 0; c < W; ++c) {\n            touched.clear();\n\
    \            for (int to : splitter) {\n                for (int v = head[to][c];\
    \ v != -1; v = link[v][c]) {\n                    int b = group[v];\n        \
    \            if (marked[b] == begin[b]) touched.push_back(b);\n              \
    \      int i = position[v], j = marked[b]++;\n                    swap(order[i],\
    \ order[j]);\n                    position[order[i]] = i;\n                  \
    \  position[order[j]] = j;\n                }\n            }\n            for\
    \ (int b : touched) {\n                int mid = marked[b], l = begin[b], r =\
    \ end[b];\n                if (mid != r) {\n                    int id = (int)begin.size();\n\
    \                    if (mid - l <= r - mid) {\n                        begin.push_back(l);\n\
    \                        end.push_back(mid);\n                        begin[b]\
    \ = mid;\n                    } else {\n                        begin.push_back(mid);\n\
    \                        end.push_back(r);\n                        end[b] = mid;\n\
    \                    }\n                    marked.push_back(begin[id]);\n   \
    \                 for (int i = begin[id]; i < end[id]; ++i) group[order[i]] =\
    \ id;\n                    pending.push_back(id);\n                }\n       \
    \         marked[b] = begin[b];\n            }\n        }\n    }\n    int dead\
    \ = group[sink];\n    if (group[0] == dead) return {};\n    vector<int> id(begin.size(),\
    \ -1), queue{group[0]};\n    id[group[0]] = 0;\n    DFA<W> result;\n    result.initial\
    \ = 0;\n    for (size_t i = 0; i < queue.size(); ++i) {\n        int v = states[order[begin[queue[i]]]];\n\
    \        array<int, W> row;\n        for (int c = 0; c < W; ++c) {\n         \
    \   int to = a.next[v][c];\n            int b = to == -1 ? dead : group[index[to]];\n\
    \            if (b == dead) row[c] = -1;\n            else {\n               \
    \ if (id[b] == -1) {\n                    id[b] = (int)queue.size();\n       \
    \             queue.push_back(b);\n                }\n                row[c] =\
    \ id[b];\n            }\n        }\n        result.next.push_back(row);\n    \
    \    result.accept.push_back(bool(a.accept[v]));\n    }\n    return result;\n\
    }\n\n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\
    \u6700\u5C0F\u5316\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_STRING_DFA_MINIMIZE_CPP\n#define FIRIEXP_LIBRARY_STRING_DFA_MINIMIZE_CPP\n\
    \n#include \"dfa.cpp\"\n\ntemplate<int W>\nDFA<W> minimize(const DFA<W>& a) {\n\
    \    if (a.initial == -1) return {};\n    vector<int> index(a.next.size(), -1),\
    \ states{a.initial};\n    index[a.initial] = 0;\n    for (size_t i = 0; i < states.size();\
    \ ++i) {\n        for (int to : a.next[states[i]]) {\n            if (to != -1\
    \ && index[to] == -1) {\n                index[to] = (int)states.size();\n   \
    \             states.push_back(to);\n            }\n        }\n    }\n    int\
    \ sink = (int)states.size();\n    assert(sink < numeric_limits<int>::max());\n\
    \    int n = sink + 1;\n    vector<int> order;\n    order.reserve(n);\n    for\
    \ (int v = 0; v < sink; ++v) if (a.accept[states[v]]) order.push_back(v);\n  \
    \  int accepted = (int)order.size();\n    if (accepted == 0) return {};\n    for\
    \ (int v = 0; v < sink; ++v) if (!a.accept[states[v]]) order.push_back(v);\n \
    \   order.push_back(sink);\n    vector<array<int, W>> head(n), link(n);\n    for\
    \ (auto& row : head) row.fill(-1);\n    for (int v = 0; v < n; ++v) {\n      \
    \  for (int c = 0; c < W; ++c) {\n            int to = v == sink ? -1 : a.next[states[v]][c];\n\
    \            to = to == -1 ? sink : index[to];\n            link[v][c] = head[to][c];\n\
    \            head[to][c] = v;\n        }\n    }\n    vector<int> group(n), position(n),\
    \ begin{0, accepted}, end{accepted, n}, marked{0, accepted};\n    for (int i =\
    \ 0; i < n; ++i) group[order[i]] = i >= accepted, position[order[i]] = i;\n  \
    \  vector<int> pending{accepted <= n - accepted ? 0 : 1}, splitter, touched;\n\
    \    while (!pending.empty()) {\n        int block = pending.back();\n       \
    \ pending.pop_back();\n        splitter.assign(order.begin() + begin[block], order.begin()\
    \ + end[block]);\n        for (int c = 0; c < W; ++c) {\n            touched.clear();\n\
    \            for (int to : splitter) {\n                for (int v = head[to][c];\
    \ v != -1; v = link[v][c]) {\n                    int b = group[v];\n        \
    \            if (marked[b] == begin[b]) touched.push_back(b);\n              \
    \      int i = position[v], j = marked[b]++;\n                    swap(order[i],\
    \ order[j]);\n                    position[order[i]] = i;\n                  \
    \  position[order[j]] = j;\n                }\n            }\n            for\
    \ (int b : touched) {\n                int mid = marked[b], l = begin[b], r =\
    \ end[b];\n                if (mid != r) {\n                    int id = (int)begin.size();\n\
    \                    if (mid - l <= r - mid) {\n                        begin.push_back(l);\n\
    \                        end.push_back(mid);\n                        begin[b]\
    \ = mid;\n                    } else {\n                        begin.push_back(mid);\n\
    \                        end.push_back(r);\n                        end[b] = mid;\n\
    \                    }\n                    marked.push_back(begin[id]);\n   \
    \                 for (int i = begin[id]; i < end[id]; ++i) group[order[i]] =\
    \ id;\n                    pending.push_back(id);\n                }\n       \
    \         marked[b] = begin[b];\n            }\n        }\n    }\n    int dead\
    \ = group[sink];\n    if (group[0] == dead) return {};\n    vector<int> id(begin.size(),\
    \ -1), queue{group[0]};\n    id[group[0]] = 0;\n    DFA<W> result;\n    result.initial\
    \ = 0;\n    for (size_t i = 0; i < queue.size(); ++i) {\n        int v = states[order[begin[queue[i]]]];\n\
    \        array<int, W> row;\n        for (int c = 0; c < W; ++c) {\n         \
    \   int to = a.next[v][c];\n            int b = to == -1 ? dead : group[index[to]];\n\
    \            if (b == dead) row[c] = -1;\n            else {\n               \
    \ if (id[b] == -1) {\n                    id[b] = (int)queue.size();\n       \
    \             queue.push_back(b);\n                }\n                row[c] =\
    \ id[b];\n            }\n        }\n        result.next.push_back(row);\n    \
    \    result.accept.push_back(bool(a.accept[v]));\n    }\n    return result;\n\
    }\n\n#endif\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\
    \u306E\u6700\u5C0F\u5316\n */\n"
  dependsOn:
  - string/dfa.cpp
  isVerificationFile: false
  path: string/dfa_minimize.cpp
  requiredBy: []
  timestamp: '2026-10-16 22:43:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yosupo_aplusb_dfa_minimize.test.cpp
  - test/yosupo_aplusb_count_words.test.cpp
documentation_of: string/dfa_minimize.cpp
layout: document
title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\u6700\u5C0F\u5316"
---

## 説明
同じ文字列を受理する最小の `DFA<W>` を作る。
到達不能状態を除き、後ろに付けるどの文字列に対しても受理結果が同じ状態をまとめる。

## できること
- `minimize(a)` : 最小化した DFA を返す。全拒否なら空の表と `initial == -1`、それ以外は `initial == 0`
- 受理状態へ到達できない状態は表に残さず、その状態への遷移を `-1` にする
- 空列の受理、文字ごとの遷移、拒否遷移を保つ。状態番号は振り直す

## 使い方
```cpp
auto a = minimize(digit_value_mod(100));
auto answer = digit_count<mint>("1", upper, a);
```

数字条件と桁 DP の include は別途行う。
`intersect` や禁止語から作った DFA、手書きの表にも使える。
前計算を繰り返さないよう、同じ条件の DP には返却した DFA を再利用する。
factory や DP は自動では最小化しない。

## 実装上の補足
[Hopcroft の分割法](https://www.cs.cmu.edu/~cdm/resources/Hopcroft1971.pdf)を使い、分割で小さくなった側を次の処理対象に追加する。
入力状態数を $S$、到達状態数を $R$、文字種数を $W$ とすると、時間 $O(S+W(R+1)\log(R+2))$、作業領域 $O(S+W(R+1))$。
内部で拒否状態を1つ追加するため、$R < \mathrm{INT\_MAX}$ とする。
最小化後の状態数を $M$ とすると返却表は $O(WM)$ 領域。
文字の違いを保存する最小化であり、文字列の個数だけを保存する重み付き DP への圧縮は行わない。
