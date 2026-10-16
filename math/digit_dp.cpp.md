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
    path: test/yosupo_aplusb_digit_dp.test.cpp
    title: test/yosupo_aplusb_digit_dp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki2867.test.cpp
    title: test/yuki2867.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\u6570\u3068\
      \u7DCF\u548C"
    links: []
  bundledCode: "#line 1 \"math/digit_dp.cpp\"\n\n\n\n#line 1 \"string/dfa.cpp\"\n\n\
    \n\ntemplate<int W>\nstruct DFA {\n    vector<array<int, W>> next;\n    vector<char>\
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
    \ 5 \"math/digit_dp.cpp\"\n\nnamespace digit_dp_detail {\n\ntemplate<class T,\
    \ bool Sum>\nauto run(const string& lower, const string& upper, const DFA<10>&\
    \ a) {\n    using Value = conditional_t<Sum, pair<T, T>, T>;\n    const Value\
    \ zero = []() -> Value {\n        if constexpr (Sum) return {T(0), T(0)};\n  \
    \      else return T(0);\n    }();\n    auto count = [](Value& x) -> T& {\n  \
    \      if constexpr (Sum) return x.first;\n        else return x;\n    };\n  \
    \  auto empty = [](const Value& x) {\n        if constexpr (Sum) return x.first\
    \ == T(0) && x.second == T(0);\n        else return x == T(0);\n    };\n    assert(!lower.empty()\
    \ && !upper.empty());\n    if (a.initial == -1) return zero;\n    if (none_of(a.accept.begin(),\
    \ a.accept.end(), [](char x) { return x; })) return zero;\n    string_view l(lower),\
    \ r(upper);\n    while (l.size() > 1 && l.front() == '0') l.remove_prefix(1);\n\
    \    while (r.size() > 1 && r.front() == '0') r.remove_prefix(1);\n    if (l.size()\
    \ > r.size() || (l.size() == r.size() && l > r)) return zero;\n    int s = (int)a.next.size();\n\
    \    vector<Value> dp(s, zero), next(s, zero);\n    array<Value, 4> border{zero,\
    \ zero, zero, zero};\n    array<int, 4> path{-1, -1, -1, s};\n    count(border[3])\
    \ = T(1);\n    bool loose = false;\n    vector<int> last;\n    if constexpr (Sum)\
    \ {\n        last.assign(s, -1);\n        for (int v = 0; v < s; ++v) {\n    \
    \        for (int d = 0; d < 10; ++d) if (a.next[v][d] != -1) last[v] = d;\n \
    \       }\n    }\n    for (size_t i = 0; i < r.size(); ++i) {\n        int ld\
    \ = i < r.size() - l.size() ? 0 : l[i - (r.size() - l.size())] - '0';\n      \
    \  int rd = r[i] - '0';\n        if (loose) fill(next.begin(), next.end(), zero);\n\
    \        for (int v = 0; loose && v < s; ++v) {\n            const auto& from\
    \ = dp[v];\n            if (empty(from)) continue;\n            if constexpr (Sum)\
    \ {\n                if (last[v] == -1) continue;\n                T sum = from.second\
    \ * T(10);\n                for (int d = 0; d <= last[v]; ++d) {\n           \
    \         int to = a.next[v][d];\n                    if (to != -1) {\n      \
    \                  next[to].first += from.first;\n                        next[to].second\
    \ += sum;\n                    }\n                    if (d != last[v]) sum +=\
    \ from.first;\n                }\n            } else {\n                for (int\
    \ to : a.next[v]) if (to != -1) next[to] += from;\n            }\n        }\n\
    \        array<Value, 4> next_border{zero, zero, zero, zero};\n        array<int,\
    \ 4> next_path{-1, -1, -1, -1};\n        for (int tight = 1; tight < 4; ++tight)\
    \ {\n            int v = path[tight];\n            if (v == -1) continue;\n  \
    \          int low = tight & 1 ? ld : 0;\n            int high = tight & 2 ? rd\
    \ : 9;\n            for (int d = low; d <= high; ++d) {\n                int to\
    \ = v == s && d == 0 ? s : a.next[v == s ? a.initial : v][d];\n              \
    \  if (to == -1) continue;\n                int flags = ((tight & 1) && d == ld)\
    \ | (((tight & 2) && d == rd) << 1);\n                Value value = border[tight];\n\
    \                if constexpr (Sum) value.second = value.second * T(10) + T(d);\n\
    \                if (flags) {\n                    next_path[flags] = to;\n  \
    \                  next_border[flags] = value;\n                } else {\n   \
    \                 assert(to != s);\n                    loose = true;\n      \
    \              count(next[to]) += count(value);\n                    if constexpr\
    \ (Sum) next[to].second += value.second;\n                }\n            }\n \
    \       }\n        dp.swap(next);\n        path = next_path;\n        border =\
    \ next_border;\n    }\n    Value result = zero;\n    int zero_state = a.next[a.initial][0];\n\
    \    for (int v = 0; v < s; ++v) if (a.accept[v]) {\n        count(result) +=\
    \ count(dp[v]);\n        if constexpr (Sum) result.second += dp[v].second;\n \
    \   }\n    for (int tight = 1; tight < 4; ++tight) {\n        int v = path[tight];\n\
    \        if (v == s) v = zero_state;\n        if (v == -1 || !a.accept[v]) continue;\n\
    \        count(result) += count(border[tight]);\n        if constexpr (Sum) result.second\
    \ += border[tight].second;\n    }\n    return result;\n}\n\n}\n\ntemplate<class\
    \ T>\nT digit_count(const string& lower, const string& upper, const DFA<10>& a)\
    \ {\n    return digit_dp_detail::run<T, false>(lower, upper, a);\n}\n\ntemplate<class\
    \ T>\npair<T, T> digit_count_sum(const string& lower, const string& upper, const\
    \ DFA<10>& a) {\n    return digit_dp_detail::run<T, true>(lower, upper, a);\n\
    }\n\n\n\n/**\n * @brief \u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\u6570\
    \u3068\u7DCF\u548C\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_DIGIT_DP_CPP\n#define FIRIEXP_LIBRARY_MATH_DIGIT_DP_CPP\n\
    \n#include \"../string/dfa.cpp\"\n\nnamespace digit_dp_detail {\n\ntemplate<class\
    \ T, bool Sum>\nauto run(const string& lower, const string& upper, const DFA<10>&\
    \ a) {\n    using Value = conditional_t<Sum, pair<T, T>, T>;\n    const Value\
    \ zero = []() -> Value {\n        if constexpr (Sum) return {T(0), T(0)};\n  \
    \      else return T(0);\n    }();\n    auto count = [](Value& x) -> T& {\n  \
    \      if constexpr (Sum) return x.first;\n        else return x;\n    };\n  \
    \  auto empty = [](const Value& x) {\n        if constexpr (Sum) return x.first\
    \ == T(0) && x.second == T(0);\n        else return x == T(0);\n    };\n    assert(!lower.empty()\
    \ && !upper.empty());\n    if (a.initial == -1) return zero;\n    if (none_of(a.accept.begin(),\
    \ a.accept.end(), [](char x) { return x; })) return zero;\n    string_view l(lower),\
    \ r(upper);\n    while (l.size() > 1 && l.front() == '0') l.remove_prefix(1);\n\
    \    while (r.size() > 1 && r.front() == '0') r.remove_prefix(1);\n    if (l.size()\
    \ > r.size() || (l.size() == r.size() && l > r)) return zero;\n    int s = (int)a.next.size();\n\
    \    vector<Value> dp(s, zero), next(s, zero);\n    array<Value, 4> border{zero,\
    \ zero, zero, zero};\n    array<int, 4> path{-1, -1, -1, s};\n    count(border[3])\
    \ = T(1);\n    bool loose = false;\n    vector<int> last;\n    if constexpr (Sum)\
    \ {\n        last.assign(s, -1);\n        for (int v = 0; v < s; ++v) {\n    \
    \        for (int d = 0; d < 10; ++d) if (a.next[v][d] != -1) last[v] = d;\n \
    \       }\n    }\n    for (size_t i = 0; i < r.size(); ++i) {\n        int ld\
    \ = i < r.size() - l.size() ? 0 : l[i - (r.size() - l.size())] - '0';\n      \
    \  int rd = r[i] - '0';\n        if (loose) fill(next.begin(), next.end(), zero);\n\
    \        for (int v = 0; loose && v < s; ++v) {\n            const auto& from\
    \ = dp[v];\n            if (empty(from)) continue;\n            if constexpr (Sum)\
    \ {\n                if (last[v] == -1) continue;\n                T sum = from.second\
    \ * T(10);\n                for (int d = 0; d <= last[v]; ++d) {\n           \
    \         int to = a.next[v][d];\n                    if (to != -1) {\n      \
    \                  next[to].first += from.first;\n                        next[to].second\
    \ += sum;\n                    }\n                    if (d != last[v]) sum +=\
    \ from.first;\n                }\n            } else {\n                for (int\
    \ to : a.next[v]) if (to != -1) next[to] += from;\n            }\n        }\n\
    \        array<Value, 4> next_border{zero, zero, zero, zero};\n        array<int,\
    \ 4> next_path{-1, -1, -1, -1};\n        for (int tight = 1; tight < 4; ++tight)\
    \ {\n            int v = path[tight];\n            if (v == -1) continue;\n  \
    \          int low = tight & 1 ? ld : 0;\n            int high = tight & 2 ? rd\
    \ : 9;\n            for (int d = low; d <= high; ++d) {\n                int to\
    \ = v == s && d == 0 ? s : a.next[v == s ? a.initial : v][d];\n              \
    \  if (to == -1) continue;\n                int flags = ((tight & 1) && d == ld)\
    \ | (((tight & 2) && d == rd) << 1);\n                Value value = border[tight];\n\
    \                if constexpr (Sum) value.second = value.second * T(10) + T(d);\n\
    \                if (flags) {\n                    next_path[flags] = to;\n  \
    \                  next_border[flags] = value;\n                } else {\n   \
    \                 assert(to != s);\n                    loose = true;\n      \
    \              count(next[to]) += count(value);\n                    if constexpr\
    \ (Sum) next[to].second += value.second;\n                }\n            }\n \
    \       }\n        dp.swap(next);\n        path = next_path;\n        border =\
    \ next_border;\n    }\n    Value result = zero;\n    int zero_state = a.next[a.initial][0];\n\
    \    for (int v = 0; v < s; ++v) if (a.accept[v]) {\n        count(result) +=\
    \ count(dp[v]);\n        if constexpr (Sum) result.second += dp[v].second;\n \
    \   }\n    for (int tight = 1; tight < 4; ++tight) {\n        int v = path[tight];\n\
    \        if (v == s) v = zero_state;\n        if (v == -1 || !a.accept[v]) continue;\n\
    \        count(result) += count(border[tight]);\n        if constexpr (Sum) result.second\
    \ += border[tight].second;\n    }\n    return result;\n}\n\n}\n\ntemplate<class\
    \ T>\nT digit_count(const string& lower, const string& upper, const DFA<10>& a)\
    \ {\n    return digit_dp_detail::run<T, false>(lower, upper, a);\n}\n\ntemplate<class\
    \ T>\npair<T, T> digit_count_sum(const string& lower, const string& upper, const\
    \ DFA<10>& a) {\n    return digit_dp_detail::run<T, true>(lower, upper, a);\n\
    }\n\n#endif\n\n/**\n * @brief \u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\
    \u6570\u3068\u7DCF\u548C\n */\n"
  dependsOn:
  - string/dfa.cpp
  isVerificationFile: false
  path: math/digit_dp.cpp
  requiredBy: []
  timestamp: '2026-10-16 22:44:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_digit_dp.test.cpp
  - test/yuki2867.test.cpp
documentation_of: math/digit_dp.cpp
layout: document
title: "\u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\u6570\u3068\u7DCF\u548C"
---

## 説明
非負整数の閉区間 $[L,R]$ で、十進表記が `DFA<10>` に受理される整数の個数・総和を求める。
上下限は文字列のまま扱い、`L-1` や機械語整数への変換は不要。

## できること
- `digit_count<T>(lower, upper, a)` : 個数を返す。総和用の乗算は行わない
- `digit_count_sum<T>(lower, upper, a)` : `{count, sum}` を `pair<T,T>` で返す
- 入力の先頭 0 は無視する。`lower > upper` や全拒否の DFA では 0 件・総和 0

## 使い方
上下限は空でない十進数字列とする。DFA は直接与えても、条件の factory から作ってもよい。
数値の余分な先頭 0 は DFA に渡さず、数値 0 だけは一文字 `"0"` を渡して判定する。
空列の受理とは異なり、0 を含む条件や禁止語にもこの規則を適用する。

```cpp
auto a = no_equal_adjacent();
auto count = digit_count<long long>("123", "321", a);
auto b = required_digits((1 << 0) | (1 << 1));
auto [number, sum] = digit_count_sum<mint>("1", "104", b);
```

数字条件には `math/digit_dfa.cpp`、禁止語には `string/avoid_patterns.cpp` を追加で include する。
`T` は `T(0)`、`T(1)`、`+=`、零との `==` を持つ型とする。
総和版はさらに `T(d)`、`T(10)`、加算・乗算を使う。
整数型では途中結果も型に収め、巨大な上限には modint 等を指定する。

## 実装上の補足
上限の正規化後の桁数を $D$、状態数を $S$、文字種数を $W$ とすると、DP は $O(WD(S+1))$ 時間、作業領域 $O(S+1)$。本実装は $W=10$。
入力の先頭 0 の読み飛ばしには入力長に比例する時間を使うが、上下限のコピーは作らない。
上下限の内側に入った接頭辞だけを2層の配列で管理する。
上下限と一致する経路は各1本なので、状態と接頭辞の値を別に持つ。未開始状態もこの経路で扱う。
総和版の遷移は `new_sum += 10 * sum + digit * count`。
`10 * sum` は状態ごとに1回だけ計算し、数字を増やすごとに `count` を加える。
剰余上で個数が 0 でも総和が非零になりうるため、総和版では両方が 0 のときだけ遷移を省く。
同じ条件で長い上限を扱う場合は、`string/dfa_minimize.cpp` の `minimize(a)` で前もって状態を減らせる。
