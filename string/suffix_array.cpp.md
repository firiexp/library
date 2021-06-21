---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_number_of_substrings.test.cpp
    title: test/yosupo_number_of_substrings.test.cpp
  - icon: ':x:'
    path: test/yosupo_suffix_array.test.cpp
    title: test/yosupo_suffix_array.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/suffix_array.cpp\"\nvector<int> convert(string const&\
    \ s){\n    int n = s.size();\n    std::vector<int> s2(n);\n    for (int i = 0;\
    \ i < n; i++) s2[i] = s[i];\n    return s2;\n}\n\nvector<int> suffix_array(const\
    \ vector<int> &s, int upper){\n    int n = s.size();\n    if (n <= 1) return vector<int>(n,\
    \ 0);\n    if (n == 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1,\
    \ 0};\n    vector<int> sa(n);\n    vector<bool> ls(n);\n    for (int i = n-2;\
    \ i >= 0; --i) ls[i] = (s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);\n    vector<int>\
    \ sum_l(upper+1), sum_s(upper+1);\n    for (int i = 0; i < n; ++i) (ls[i] ? sum_l[s[i]+1]\
    \ : sum_s[s[i]])++;\n    for (int i = 0; i <= upper; ++i) {\n        sum_s[i]\
    \ += sum_l[i];\n        if(i < upper) sum_l[i+1] += sum_s[i];\n    }\n\n    auto\
    \ induce = [&](vector<int> const& lms){\n        fill(sa.begin(),sa.end(), -1);\n\
    \        vector<int> buf(upper+1);\n        copy(sum_s.begin(),sum_s.end(), buf.begin());\n\
    \        for (auto &&i : lms) if(i != n) sa[buf[s[i]]++] = i;\n        copy(sum_l.begin(),sum_l.end(),\
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
    \ s.size();\n    vector<int> sa_inv(n);\n    for (int i = 0; i < n; ++i) sa_inv[sa[i]]\
    \ = i;\n    vector<int> lcp(n-1);\n    int h = 0;\n    for (int i = 0; i < n;\
    \ ++i) {\n        if(h > 0) h--;\n        if(!sa_inv[i]) continue;\n        int\
    \ j = sa[sa_inv[i]-1];\n        while(j+h < n && i+h < n && s[j+h] == s[i+h])\
    \ h++;\n        lcp[sa_inv[i]-1] = h;\n    }\n    return lcp;\n}\n\nvector<int>\
    \ lcp(string const& s, vector<int> const& sa){\n    return lcp(convert(s), sa);\n\
    }\n"
  code: "vector<int> convert(string const& s){\n    int n = s.size();\n    std::vector<int>\
    \ s2(n);\n    for (int i = 0; i < n; i++) s2[i] = s[i];\n    return s2;\n}\n\n\
    vector<int> suffix_array(const vector<int> &s, int upper){\n    int n = s.size();\n\
    \    if (n <= 1) return vector<int>(n, 0);\n    if (n == 2) return s[0] < s[1]\
    \ ? vector<int>{0, 1} : vector<int>{1, 0};\n    vector<int> sa(n);\n    vector<bool>\
    \ ls(n);\n    for (int i = n-2; i >= 0; --i) ls[i] = (s[i] == s[i+1]) ? ls[i+1]\
    \ : (s[i] < s[i+1]);\n    vector<int> sum_l(upper+1), sum_s(upper+1);\n    for\
    \ (int i = 0; i < n; ++i) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;\n    for (int\
    \ i = 0; i <= upper; ++i) {\n        sum_s[i] += sum_l[i];\n        if(i < upper)\
    \ sum_l[i+1] += sum_s[i];\n    }\n\n    auto induce = [&](vector<int> const& lms){\n\
    \        fill(sa.begin(),sa.end(), -1);\n        vector<int> buf(upper+1);\n \
    \       copy(sum_s.begin(),sum_s.end(), buf.begin());\n        for (auto &&i :\
    \ lms) if(i != n) sa[buf[s[i]]++] = i;\n        copy(sum_l.begin(),sum_l.end(),\
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
    \ s.size();\n    vector<int> sa_inv(n);\n    for (int i = 0; i < n; ++i) sa_inv[sa[i]]\
    \ = i;\n    vector<int> lcp(n-1);\n    int h = 0;\n    for (int i = 0; i < n;\
    \ ++i) {\n        if(h > 0) h--;\n        if(!sa_inv[i]) continue;\n        int\
    \ j = sa[sa_inv[i]-1];\n        while(j+h < n && i+h < n && s[j+h] == s[i+h])\
    \ h++;\n        lcp[sa_inv[i]-1] = h;\n    }\n    return lcp;\n}\n\nvector<int>\
    \ lcp(string const& s, vector<int> const& sa){\n    return lcp(convert(s), sa);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_array.cpp
  requiredBy: []
  timestamp: '2020-09-13 18:15:01+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_number_of_substrings.test.cpp
  - test/yosupo_suffix_array.test.cpp
documentation_of: string/suffix_array.cpp
layout: document
redirect_from:
- /library/string/suffix_array.cpp
- /library/string/suffix_array.cpp.html
title: string/suffix_array.cpp
---
