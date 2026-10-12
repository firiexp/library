---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.cpp
    title: Suffix Array
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/enumerate_runs.cpp
    title: "\u6587\u5B57\u5217\u306Erun\u5217\u6319"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_enumerate_runs.test.cpp
    title: test/yosupo_aplusb_enumerate_runs.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_suffix_array_query.test.cpp
    title: test/yosupo_aplusb_suffix_array_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_runenumerate.test.cpp
    title: test/yosupo_runenumerate.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_suffix_array_query.test.cpp
    title: test/yosupo_suffix_array_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_zalgorithm_suffix_array_query.test.cpp
    title: test/yosupo_zalgorithm_suffix_array_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u30FB\u90E8\u5206\u6587\
      \u5B57\u5217\u306E\u8F9E\u66F8\u9806\u6BD4\u8F03"
    links: []
  bundledCode: "#line 1 \"string/suffix_array_query.cpp\"\n\n\n\n#line 1 \"string/suffix_array.cpp\"\
    \n\n\n\nvector<int> convert(string const& s){\n    int n = s.size();\n    std::vector<int>\
    \ s2(n);\n    for (int i = 0; i < n; i++) s2[i] = static_cast<unsigned char>(s[i]);\n\
    \    return s2;\n}\n\nvector<int> suffix_array(const vector<int> &s, int upper){\n\
    \    int n = s.size();\n    if (n <= 1) return vector<int>(n, 0);\n    if (n ==\
    \ 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};\n    vector<int>\
    \ sa(n);\n    vector<bool> ls(n);\n    for (int i = n-2; i >= 0; --i) ls[i] =\
    \ (s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);\n    vector<int> sum_l(upper+1),\
    \ sum_s(upper+1);\n    for (int i = 0; i < n; ++i) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;\n\
    \    for (int i = 0; i <= upper; ++i) {\n        sum_s[i] += sum_l[i];\n     \
    \   if(i < upper) sum_l[i+1] += sum_s[i];\n    }\n\n    auto induce = [&](vector<int>\
    \ const& lms){\n        fill(sa.begin(),sa.end(), -1);\n        vector<int> buf(upper+1);\n\
    \        copy(sum_s.begin(),sum_s.end(), buf.begin());\n        for (auto &&i\
    \ : lms) if(i != n) sa[buf[s[i]]++] = i;\n        copy(sum_l.begin(),sum_l.end(),\
    \ buf.begin());\n        sa[buf[s.back()]++] = n-1;\n        for (int i = 0; i\
    \ < n; ++i) {\n            int v = sa[i];\n            if(v >= 1 && !ls[v-1])\
    \ sa[buf[s[v-1]]++] = v-1;\n        }\n        copy(sum_l.begin(),sum_l.end(),\
    \ buf.begin());\n        for (int i = n - 1; i >= 0; --i) {\n            int v\
    \ = sa[i];\n            if(v >= 1 && ls[v-1]) sa[--buf[s[v-1]+1]] = v-1;\n   \
    \     }\n    };\n    vector<int> lms_map(n+1, -1);\n    int m = 0;\n    for (int\
    \ i = 1; i < n; ++i) if(!ls[i-1] && ls[i]) lms_map[i] = m++;\n    vector<int>\
    \ lms;\n    lms.reserve(m);\n    for (int i = 1; i < n; ++i) if(!ls[i-1] && ls[i])\
    \ lms.emplace_back(i);\n    induce(lms);\n    if(m){\n        vector<int> sorted_lms;\n\
    \        sorted_lms.reserve(m);\n        for (auto &&i : sa) if(~lms_map[i]) sorted_lms.emplace_back(i);\n\
    \        vector<int> rec_s(m);\n        int rec_upper = 0;\n        rec_s[lms_map[sorted_lms.front()]]\
    \ = 0;\n        for (int i = 1; i < m; ++i) {\n            int l = sorted_lms[i-1],\
    \ r = sorted_lms[i];\n            int end_l = (lms_map[l]+1) < m ? lms[lms_map[l]+1]\
    \ : n;\n            int end_r = (lms_map[r]+1) < m ? lms[lms_map[r]+1] : n;\n\
    \            bool same = true;\n            if(end_l-l != end_r-r) same = false;\n\
    \            else {\n                while(l < end_l && s[l] == s[r]) l++, r++;\n\
    \                if(l == n || s[l] != s[r]) same = false;\n            }\n   \
    \         rec_upper += !same;\n            rec_s[lms_map[sorted_lms[i]]] = rec_upper;\n\
    \        }\n        auto rec_sa = suffix_array(rec_s, rec_upper);\n        for\
    \ (int i = 0; i < m; ++i) sorted_lms[i] = lms[rec_sa[i]];\n        induce(sorted_lms);\n\
    \    }\n    return sa;\n}\n\ntemplate<class T> vector<int> suffix_array(vector<T>\
    \ const& s){\n    int n = s.size();\n    vector<int> idx(n);\n    iota(idx.begin(),idx.end(),\
    \ 0);\n    sort(idx.begin(),idx.end(), [&](int l, int r){ return s[l] < s[r];\
    \ });\n    vector<int> z(n);\n    int now = 0;\n    for (int i = 0; i < n; ++i)\
    \ {\n        if(i && s[idx[i-1]] != s[idx[i]]) now++;\n        z[idx[i]] = now;\n\
    \    }\n    return suffix_array(z, now);\n}\n\nvector<int> suffix_array(const\
    \ string& s){\n    return suffix_array(convert(s), 255);\n}\n\ntemplate<class\
    \ T>\nvector<int> lcp(const vector<T> &s, const vector<int> &sa){\n    int n =\
    \ s.size();\n    if (n <= 1) return {};\n    vector<int> sa_inv(n);\n    for (int\
    \ i = 0; i < n; ++i) sa_inv[sa[i]] = i;\n    vector<int> lcp(n-1);\n    int h\
    \ = 0;\n    for (int i = 0; i < n; ++i) {\n        if(h > 0) h--;\n        if(!sa_inv[i])\
    \ continue;\n        int j = sa[sa_inv[i]-1];\n        while(j+h < n && i+h <\
    \ n && s[j+h] == s[i+h]) h++;\n        lcp[sa_inv[i]-1] = h;\n    }\n    return\
    \ lcp;\n}\n\nvector<int> lcp(string const& s, vector<int> const& sa){\n    return\
    \ lcp(convert(s), sa);\n}\n\n/**\n * @brief Suffix Array\n */\n\n\n#line 1 \"\
    datastructure/sparsetable.cpp\"\n\n\n\ntemplate <class F>\nstruct SparseTable\
    \ {\n    using T = typename F::T;\n    vector<vector<T>> table;\n    vector<int>\
    \ u;\n    SparseTable() = default;\n    explicit SparseTable(const vector<T> &v){\
    \ build(v); }\n \n    void build(const vector<T> &v){\n        int n = v.size(),\
    \ m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m, vector<T>(n));\n\
    \        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i) {\n         \
    \   u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n; ++i) {\n  \
    \          table[0][i] = v[i];\n        }\n        for (int i = 1; i < m; ++i)\
    \ {\n            int x = (1<<(i-1));\n            for (int j = 0; j < n; ++j)\
    \ {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x, n-1)]);\n\
    \            }\n        }\n    }\n \n    T query(int a, int b) const {\n     \
    \   int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n\n\n#line 6 \"string/suffix_array_query.cpp\"\
    \n\nclass SuffixArrayQuery {\n    struct Minimum {\n        using T = int;\n \
    \       static int f(int a, int b) { return min(a, b); }\n    };\n    int n;\n\
    \    vector<int> rank;\n    SparseTable<Minimum> rmq;\n\n    template<class Sequence>\n\
    \    void initialize(const Sequence& s) {\n        n = (int)s.size();\n      \
    \  auto sa = suffix_array(s);\n        rank.resize(n);\n        for (int i = 0;\
    \ i < n; ++i) rank[sa[i]] = i;\n        rmq.build(lcp(s, sa));\n    }\n\npublic:\n\
    \    explicit SuffixArrayQuery(const string& s) { initialize(s); }\n\n    template<class\
    \ T>\n    explicit SuffixArrayQuery(const vector<T>& s) { initialize(s); }\n\n\
    \    int suffix_rank(int i) const { return rank[i]; }\n\n    int lce(int i, int\
    \ j) const {\n        if (i == j) return n - i;\n        if (i == n || j == n)\
    \ return 0;\n        int a = rank[i], b = rank[j];\n        if (a > b) swap(a,\
    \ b);\n        return rmq.query(a, b);\n    }\n\n    int compare(int l1, int r1,\
    \ int l2, int r2) const {\n        int len1 = r1 - l1, len2 = r2 - l2;\n     \
    \   if (lce(l1, l2) >= min(len1, len2))\n            return (len1 > len2) - (len1\
    \ < len2);\n        return rank[l1] < rank[l2] ? -1 : 1;\n    }\n};\n\n\n\n/**\n\
    \ * @brief \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u30FB\u90E8\u5206\u6587\u5B57\
    \u5217\u306E\u8F9E\u66F8\u9806\u6BD4\u8F03\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_STRING_SUFFIX_ARRAY_QUERY_CPP\n#define FIRIEXP_LIBRARY_STRING_SUFFIX_ARRAY_QUERY_CPP\n\
    \n#include \"suffix_array.cpp\"\n#include \"../datastructure/sparsetable.cpp\"\
    \n\nclass SuffixArrayQuery {\n    struct Minimum {\n        using T = int;\n \
    \       static int f(int a, int b) { return min(a, b); }\n    };\n    int n;\n\
    \    vector<int> rank;\n    SparseTable<Minimum> rmq;\n\n    template<class Sequence>\n\
    \    void initialize(const Sequence& s) {\n        n = (int)s.size();\n      \
    \  auto sa = suffix_array(s);\n        rank.resize(n);\n        for (int i = 0;\
    \ i < n; ++i) rank[sa[i]] = i;\n        rmq.build(lcp(s, sa));\n    }\n\npublic:\n\
    \    explicit SuffixArrayQuery(const string& s) { initialize(s); }\n\n    template<class\
    \ T>\n    explicit SuffixArrayQuery(const vector<T>& s) { initialize(s); }\n\n\
    \    int suffix_rank(int i) const { return rank[i]; }\n\n    int lce(int i, int\
    \ j) const {\n        if (i == j) return n - i;\n        if (i == n || j == n)\
    \ return 0;\n        int a = rank[i], b = rank[j];\n        if (a > b) swap(a,\
    \ b);\n        return rmq.query(a, b);\n    }\n\n    int compare(int l1, int r1,\
    \ int l2, int r2) const {\n        int len1 = r1 - l1, len2 = r2 - l2;\n     \
    \   if (lce(l1, l2) >= min(len1, len2))\n            return (len1 > len2) - (len1\
    \ < len2);\n        return rank[l1] < rank[l2] ? -1 : 1;\n    }\n};\n\n#endif\n\
    \n/**\n * @brief \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u30FB\u90E8\u5206\u6587\
    \u5B57\u5217\u306E\u8F9E\u66F8\u9806\u6BD4\u8F03\n */\n"
  dependsOn:
  - string/suffix_array.cpp
  - datastructure/sparsetable.cpp
  isVerificationFile: false
  path: string/suffix_array_query.cpp
  requiredBy:
  - string/enumerate_runs.cpp
  timestamp: '2026-10-12 10:35:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_suffix_array_query.test.cpp
  - test/yosupo_zalgorithm_suffix_array_query.test.cpp
  - test/yosupo_aplusb_enumerate_runs.test.cpp
  - test/yosupo_runenumerate.test.cpp
  - test/yosupo_aplusb_suffix_array_query.test.cpp
documentation_of: string/suffix_array_query.cpp
layout: document
title: "\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u30FB\u90E8\u5206\u6587\u5B57\u5217\
  \u306E\u8F9E\u66F8\u9806\u6BD4\u8F03"
---

## 説明
与えられた文字列や配列を前処理し、指定した2つの位置からの最長共通接頭辞の長さを求める。
部分文字列の辞書順比較にも対応する。
長さを $N$ として、構築は $O(N\log(N+1))$ 時間・領域、各クエリは $O(1)$ 時間。

## できること
- `SuffixArrayQuery q(s)`
  `string` または `vector<T>` から構築する。入力は変更しない
- `int suffix_rank(int i) const`
  `s[i..N)` の辞書順の順位を $0$ 以上 $N$ 未満で返す。$0\le i<N$ が必要
- `int lce(int i, int j) const`
  `s[i..N)` と `s[j..N)` の最長共通接頭辞の長さを返す
- `int compare(int l1, int r1, int l2, int r2) const`
  `s[l1..r1)` と `s[l2..r2)` を辞書順で比較し、小さい・等しい・大きい場合にそれぞれ `-1`・`0`・`1` を返す

## 使い方
`lce` と `compare` の添字は $0$ 以上 $N$ 以下、区間は半開区間で指定する。空区間や末尾 $N$ も指定できる。
文字列は符号なし byte 順で比較する。`vector<T>` では `<` と `==`・`!=` が整合することを前提とする。

```cpp
SuffixArrayQuery q(string("banana"));
int common = q.lce(1, 3);
int order = q.compare(1, 4, 3, 6);
```

この例では `common` は `3`、`order` は `0` となる。

## 実装上の補足
Suffix Array の逆順列を使い、指定された2つの位置を suffix の順位に変換する。
隣り合う suffix の最長共通接頭辞長を配列に持ち、その区間最小値を Sparse Table で $O(1)$ 時間で求める。
比較のたびに部分文字列をコピーする必要はない。
