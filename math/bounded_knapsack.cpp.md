---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_dpl_1_g_bounded_knapsack.test.cpp
    title: test/aoj_dpl_1_g_bounded_knapsack.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_bounded_knapsack.test.cpp
    title: test/yosupo_aplusb_bounded_knapsack.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u500B\u6570\u5236\u9650\u4ED8\u304D\u30CA\u30C3\u30D7\u30B5\u30C3\
      \u30AF"
    links: []
  bundledCode: "#line 1 \"math/bounded_knapsack.cpp\"\nstruct BoundedKnapsackItem\
    \ {\n    int weight;\n    long long value, count;\n};\n\nvector<long long> bounded_knapsack(const\
    \ vector<BoundedKnapsackItem>& items, int capacity) {\n    const long long unreachable\
    \ = -INF<ll>;\n    vector<long long> dp(capacity + 1, unreachable);\n    unique_ptr<long\
    \ long[]> values;\n    unique_ptr<int[]> indices;\n    dp[0] = 0;\n    for (auto\
    \ [weight, value, count] : items) {\n        int limit = capacity / weight;\n\
    \        int copies = (int)min(count, (long long)limit);\n        if (copies ==\
    \ 0) continue;\n        if (copies == limit) {\n            for (int w = weight;\
    \ w <= capacity; ++w) {\n                if (dp[w - weight] != unreachable)\n\
    \                    dp[w] = max(dp[w], dp[w - weight] + value);\n           \
    \ }\n        } else if (copies <= 32) {\n            for (int step = 1; copies\
    \ > 0; step <<= 1) {\n                int take = min(step, copies);\n        \
    \        int total_weight = take * weight;\n                long long total_value\
    \ = take * value;\n                for (int w = capacity; w >= total_weight; --w)\
    \ {\n                    if (dp[w - total_weight] != unreachable)\n          \
    \              dp[w] = max(dp[w], dp[w - total_weight] + total_value);\n     \
    \           }\n                copies -= take;\n            }\n        } else\
    \ {\n            if (!indices) {\n                indices.reset(new int[capacity\
    \ + 1]);\n                values.reset(new long long[capacity + 1]);\n       \
    \     }\n            for (int r = 0; r < weight; ++r) {\n                int head\
    \ = 0, tail = 0;\n                for (int j = 0; j <= (capacity - r) / weight;\
    \ ++j) {\n                    int w = r + j * weight;\n                    long\
    \ long offset = j * value;\n                    while (head < tail && indices[head]\
    \ < j - copies) ++head;\n                    if (dp[w] != unreachable) {\n   \
    \                     long long candidate = dp[w] - offset;\n                \
    \        while (head < tail && values[tail - 1] <= candidate) --tail;\n      \
    \                  indices[tail] = j;\n                        values[tail++]\
    \ = candidate;\n                    }\n                    dp[w] = head < tail\
    \ ? values[head] + offset : unreachable;\n                }\n            }\n \
    \       }\n    }\n    return dp;\n}\n\n/**\n * @brief \u500B\u6570\u5236\u9650\
    \u4ED8\u304D\u30CA\u30C3\u30D7\u30B5\u30C3\u30AF\n */\n"
  code: "struct BoundedKnapsackItem {\n    int weight;\n    long long value, count;\n\
    };\n\nvector<long long> bounded_knapsack(const vector<BoundedKnapsackItem>& items,\
    \ int capacity) {\n    const long long unreachable = -INF<ll>;\n    vector<long\
    \ long> dp(capacity + 1, unreachable);\n    unique_ptr<long long[]> values;\n\
    \    unique_ptr<int[]> indices;\n    dp[0] = 0;\n    for (auto [weight, value,\
    \ count] : items) {\n        int limit = capacity / weight;\n        int copies\
    \ = (int)min(count, (long long)limit);\n        if (copies == 0) continue;\n \
    \       if (copies == limit) {\n            for (int w = weight; w <= capacity;\
    \ ++w) {\n                if (dp[w - weight] != unreachable)\n               \
    \     dp[w] = max(dp[w], dp[w - weight] + value);\n            }\n        } else\
    \ if (copies <= 32) {\n            for (int step = 1; copies > 0; step <<= 1)\
    \ {\n                int take = min(step, copies);\n                int total_weight\
    \ = take * weight;\n                long long total_value = take * value;\n  \
    \              for (int w = capacity; w >= total_weight; --w) {\n            \
    \        if (dp[w - total_weight] != unreachable)\n                        dp[w]\
    \ = max(dp[w], dp[w - total_weight] + total_value);\n                }\n     \
    \           copies -= take;\n            }\n        } else {\n            if (!indices)\
    \ {\n                indices.reset(new int[capacity + 1]);\n                values.reset(new\
    \ long long[capacity + 1]);\n            }\n            for (int r = 0; r < weight;\
    \ ++r) {\n                int head = 0, tail = 0;\n                for (int j\
    \ = 0; j <= (capacity - r) / weight; ++j) {\n                    int w = r + j\
    \ * weight;\n                    long long offset = j * value;\n             \
    \       while (head < tail && indices[head] < j - copies) ++head;\n          \
    \          if (dp[w] != unreachable) {\n                        long long candidate\
    \ = dp[w] - offset;\n                        while (head < tail && values[tail\
    \ - 1] <= candidate) --tail;\n                        indices[tail] = j;\n   \
    \                     values[tail++] = candidate;\n                    }\n   \
    \                 dp[w] = head < tail ? values[head] + offset : unreachable;\n\
    \                }\n            }\n        }\n    }\n    return dp;\n}\n\n/**\n\
    \ * @brief \u500B\u6570\u5236\u9650\u4ED8\u304D\u30CA\u30C3\u30D7\u30B5\u30C3\u30AF\
    \n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/bounded_knapsack.cpp
  requiredBy: []
  timestamp: '2026-10-12 17:52:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_bounded_knapsack.test.cpp
  - test/aoj_dpl_1_g_bounded_knapsack.test.cpp
documentation_of: math/bounded_knapsack.cpp
layout: document
title: "\u500B\u6570\u5236\u9650\u4ED8\u304D\u30CA\u30C3\u30D7\u30B5\u30C3\u30AF"
---

## 説明
重さ・価値・個数制限が指定された品物について、重さごとの最大価値を求める。
品物の種類数を $N$、容量を $W$ として、時間 $O(NW)$、補助領域 $O(W)$。

## できること
- `BoundedKnapsackItem { int weight; long long value, count; }`
  品物1個の重さ・価値と、使える個数を指定する
- `vector<long long> bounded_knapsack(const vector<BoundedKnapsackItem>& items, int capacity)`
  重さが $0,1,\ldots,\mathrm{capacity}$ になる品物の選び方について、最大価値を返す。作れない重さの値は `-INF<ll>`

## 使い方
重さは正、個数と容量は非負とする。価値には負の値も使える。
容量以下の最大価値は、返された配列の最大値で求める。

```cpp
vector<BoundedKnapsackItem> items = { {3, 4, 2}, {1, 2, 1} };
auto dp = bounded_knapsack(items, 7);
long long best = *max_element(dp.begin(), dp.end());
```

テンプレートの `-INF<ll>` は、各段階の到達可能な DP 値より小さく設定する。
個数と価値の積や、単調キュー内で使う `dp[r + j * weight] - j * value` を含め、途中の計算も `long long` に収まる必要がある。

## 実装上の補足
重さの剰余ごとに単調キューで最大値を管理する。
実効個数が少ない品物には二進分割を使い、容量内で個数制限に達しない品物には無制限ナップサックの更新を使う。
単調キューの作業配列は初めて必要になったときに確保し、品物間で再利用する。書き込んだ範囲だけを参照するため、作業配列の初期値は設定しない。
