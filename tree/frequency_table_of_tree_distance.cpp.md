---
category: "\u6728"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft.cpp
    title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_frequency_table_of_tree_distance.test.cpp
    title: test/yosupo_frequency_table_of_tree_distance.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Frequency Table of Tree Distance
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fft.cpp: line 346: found codes out of include guard\n"
  code: "#define FIRIEXP_LIBRARY_FFT_EXACT_ONLY\n#include \"../math/fft.cpp\"\n#undef\
    \ FIRIEXP_LIBRARY_FFT_EXACT_ONLY\n\nvector<long long> frequency_table_of_tree_distance(const\
    \ vector<vector<int>> &g) {\n    using ArbitraryConvolution::square_u64;\n\n \
    \   int n = (int)g.size();\n    if (n == 0) return {};\n\n    vector<int> sz(n);\n\
    \    vector<char> used(n, 0);\n    vector<long long> ordered(n);\n\n    auto dfs_size\
    \ = [&](auto &&self, int v, int p) -> int {\n        sz[v] = 1;\n        for (auto\
    \ &&to : g[v]) {\n            if (to == p || used[to]) continue;\n           \
    \ sz[v] += self(self, to, v);\n        }\n        return sz[v];\n    };\n\n  \
    \  auto find_centroid = [&](auto &&self, int v, int p, int half) -> int {\n  \
    \      for (auto &&to : g[v]) {\n            if (to == p || used[to]) continue;\n\
    \            if (sz[to] > half) return self(self, to, v, half);\n        }\n \
    \       return v;\n    };\n\n    auto collect = [&](auto &&self, int v, int p,\
    \ int d, vector<unsigned int> &cnt) -> void {\n        if ((int)cnt.size() <=\
    \ d) cnt.resize(d + 1);\n        ++cnt[d];\n        for (auto &&to : g[v]) {\n\
    \            if (to == p || used[to]) continue;\n            self(self, to, v,\
    \ d + 1, cnt);\n        }\n    };\n\n    auto add_convolution = [&](const vector<unsigned\
    \ long long> &conv, int sign) {\n        int lim = min(n, (int)conv.size());\n\
    \        for (int d = 0; d < lim; ++d) {\n            ordered[d] += sign * (long\
    \ long)conv[d];\n        }\n    };\n\n    auto solve = [&](auto &&self, int start)\
    \ -> void {\n        int centroid = find_centroid(find_centroid, start, -1, dfs_size(dfs_size,\
    \ start, -1) / 2);\n        used[centroid] = 1;\n\n        vector<unsigned int>\
    \ total(1, 1);\n        for (auto &&to : g[centroid]) {\n            if (used[to])\
    \ continue;\n            vector<unsigned int> cnt(1, 0);\n            collect(collect,\
    \ to, centroid, 1, cnt);\n            add_convolution(square_u64(cnt), -1);\n\
    \            if (total.size() < cnt.size()) total.resize(cnt.size());\n      \
    \      for (int d = 1; d < (int)cnt.size(); ++d) total[d] += cnt[d];\n       \
    \ }\n        add_convolution(square_u64(total), 1);\n\n        for (auto &&to\
    \ : g[centroid]) {\n            if (!used[to]) self(self, to);\n        }\n  \
    \  };\n\n    solve(solve, 0);\n\n    vector<long long> ans(n);\n    for (int d\
    \ = 1; d < n; ++d) ans[d] = ordered[d] / 2;\n    return ans;\n}\n\n/**\n * @brief\
    \ Frequency Table of Tree Distance\n */\n"
  dependsOn:
  - math/fft.cpp
  isVerificationFile: false
  path: tree/frequency_table_of_tree_distance.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_frequency_table_of_tree_distance.test.cpp
date: 2026-03-15
documentation_of: tree/frequency_table_of_tree_distance.cpp
layout: document
tags: "\u6728"
title: "\u6728\u8DDD\u96E2\u983B\u5EA6\u8868(Frequency Table of Tree Distance)"
---

## 説明
木上の距離ごとの頂点対数を求める。
`res[d]` に距離 `d` の unordered pair 数を入れて返す。
計算量は $O(N \log^2 N)$。

## できること
- `vector<long long> frequency_table_of_tree_distance(const vector<vector<int>>& g)`
  距離頻度表を返す。`res[0] = 0`、`res[d]` は距離 `d` の頂点対数

## 使い方
隣接リストを渡して呼ぶ。

## 実装上の補足
- 重心分解で各重心を通る頂点対だけを数える
- 深さ頻度の畳み込みを使い、同一子部分木内の対を引いて重複を除く
