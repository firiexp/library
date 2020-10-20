---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
    title: test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/segbeats.cpp\"\ntemplate<class T>\nclass SegmentTreeBeats\
    \ {\n    void add_(int x, T val){\n        if(!val) return;\n        auto& now\
    \ = seg[x];\n        now.sum += val*now.len;\n        now.mn += val; now.mx +=\
    \ val; now.add += val;\n        if(now.mn2 != INF<T>) now.mn2 += val;\n      \
    \  if(now.mx2 != -INF<T>) now.mx2 += val;\n    }\n    void chmin_(int x, T val){\n\
    \        if(val >= seg[x].mx) return;\n        auto& now = seg[x];\n        now.sum\
    \ += now.mxc*(val-now.mx);\n        if(now.mn == now.mx) now.mn = val;\n     \
    \   else if(now.mn2 == now.mx) now.mn2 = val;\n        now.mx = val;\n    }\n\
    \    void chmax_(int x, T val){\n        if(val <= seg[x].mn) return;\n      \
    \  auto& now = seg[x];\n        now.sum += now.mnc*(val-now.mn);\n        if(now.mx\
    \ == now.mn) now.mx = val;\n        else if(now.mx2 == now.mn) now.mx2 = val;\n\
    \        now.mn = val;\n    }\n    void get(int x){\n        M& now = seg[x],\
    \ &l = seg[(x<<1)|0], &r = seg[(x<<1)|1];\n        now.sum = l.sum + r.sum;\n\
    \        now.mn = min(l.mn, r.mn);\n        now.mx = max(l.mx, r.mx);\n      \
    \  now.len = l.len + r.len;\n        if(l.mn < r.mn) now.mnc = l.mnc, now.mn2\
    \ = min(l.mn2, r.mn);\n        else if(r.mn < l.mn) now.mnc = r.mnc, now.mn2 =\
    \ min(r.mn2, l.mn);\n        else now.mnc = l.mnc + r.mnc, now.mn2 = min(l.mn2,\
    \ r.mn2);\n        if(l.mx > r.mx) now.mxc = l.mxc, now.mx2 = max(l.mx2, r.mx);\n\
    \        else if(r.mx > l.mx) now.mxc = r.mxc, now.mx2 = max(r.mx2, l.mx);\n \
    \       else now.mxc = l.mxc + r.mxc, now.mx2 = max(l.mx2, r.mx2);\n    }\n  \
    \  void eval(int x){\n        auto &now = seg[x];\n        for (int i = 0; x <\
    \ n && i < 2; ++i) {\n            add_((x<<1)|i, now.add);\n            chmin_((x<<1)|i,\
    \ now.mx);\n            chmax_((x<<1)|i, now.mn);\n        }\n        now.add\
    \ = 0;\n    }\n    void thrust(int k){ for (int i = height-1; i >= 1; --i) eval(k>>i);\
    \ }\n    void recalc(int k) { k = k >> __builtin_ctz(k); while(k >>= 1) get(k);}\n\
    \n    void in_chmin(int x, T val) {\n        if(seg[x].mx2 < val) chmin_(x, val);\n\
    \        else {\n            eval(x);\n            in_chmin((x<<1)|0, val);\n\
    \            in_chmin((x<<1)|1, val);\n            get(x);\n        }\n    }\n\
    \    void in_chmax(int x, T val) {\n        if(seg[x].mn2 > val) chmax_(x, val);\n\
    \        else {\n            eval(x);\n            in_chmax((x<<1)|0, val);\n\
    \            in_chmax((x<<1)|1, val);\n            get(x);\n        }\n    }\n\
    public:\n#define RANGEX(NAME, INFUNC) \\\nvoid NAME(int a, int b, T val) { \\\n\
    \    thrust(a += n); \\\n    thrust(b += n); \\\n    for(int l = a, r = b; l <\
    \ r; l >>=1, r>>=1) { \\\n        if (l & 1) INFUNC(l++, val); \\\n        if\
    \ (r & 1) INFUNC(--r, val); \\\n    } \\\n    recalc(a); \\\n    recalc(b); \\\
    \n}\n    RANGEX(chmin, in_chmin)\n    RANGEX(chmax, in_chmax)\n    RANGEX(add,\
    \ add_)\n#undef RANGEX\n    T sum(int a, int b) {\n        thrust(a += n);\n \
    \       thrust(b += n);\n        T res = 0;\n        for(int l = a, r = b; l <\
    \ r; l >>=1, r>>=1) {\n            if (l & 1) res += seg[l++].sum;\n         \
    \   if (r & 1) res += seg[--r].sum;\n        }\n        return res;\n    }\n \
    \   struct M {\n        T sum, mx, mx2, mxc, mn, mn2, mnc, len, add;\n       \
    \ M() : mx2(-INF<T>), mxc(1), mn2(INF<T>), mnc(1), add(0) {};\n    };\n    vector<M>\
    \ seg;\n    int n, height;\n    SegmentTreeBeats() = default;\n    SegmentTreeBeats(const\
    \ vector<T>& v){\n        n = 1, height = 1;\n        while(n < v.size()) n <<=\
    \ 1, height++;\n        seg.resize(2*n);\n        for (int i = 0; i < v.size();\
    \ ++i) {\n            seg[i+n].sum = seg[i+n].mx = seg[i+n].mn = v[i];\n     \
    \       seg[i+n].len = 1;\n        }\n        for (int i = n-1; i >= 1; --i) get(i);\n\
    \    }\n};\n"
  code: "template<class T>\nclass SegmentTreeBeats {\n    void add_(int x, T val){\n\
    \        if(!val) return;\n        auto& now = seg[x];\n        now.sum += val*now.len;\n\
    \        now.mn += val; now.mx += val; now.add += val;\n        if(now.mn2 !=\
    \ INF<T>) now.mn2 += val;\n        if(now.mx2 != -INF<T>) now.mx2 += val;\n  \
    \  }\n    void chmin_(int x, T val){\n        if(val >= seg[x].mx) return;\n \
    \       auto& now = seg[x];\n        now.sum += now.mxc*(val-now.mx);\n      \
    \  if(now.mn == now.mx) now.mn = val;\n        else if(now.mn2 == now.mx) now.mn2\
    \ = val;\n        now.mx = val;\n    }\n    void chmax_(int x, T val){\n     \
    \   if(val <= seg[x].mn) return;\n        auto& now = seg[x];\n        now.sum\
    \ += now.mnc*(val-now.mn);\n        if(now.mx == now.mn) now.mx = val;\n     \
    \   else if(now.mx2 == now.mn) now.mx2 = val;\n        now.mn = val;\n    }\n\
    \    void get(int x){\n        M& now = seg[x], &l = seg[(x<<1)|0], &r = seg[(x<<1)|1];\n\
    \        now.sum = l.sum + r.sum;\n        now.mn = min(l.mn, r.mn);\n       \
    \ now.mx = max(l.mx, r.mx);\n        now.len = l.len + r.len;\n        if(l.mn\
    \ < r.mn) now.mnc = l.mnc, now.mn2 = min(l.mn2, r.mn);\n        else if(r.mn <\
    \ l.mn) now.mnc = r.mnc, now.mn2 = min(r.mn2, l.mn);\n        else now.mnc = l.mnc\
    \ + r.mnc, now.mn2 = min(l.mn2, r.mn2);\n        if(l.mx > r.mx) now.mxc = l.mxc,\
    \ now.mx2 = max(l.mx2, r.mx);\n        else if(r.mx > l.mx) now.mxc = r.mxc, now.mx2\
    \ = max(r.mx2, l.mx);\n        else now.mxc = l.mxc + r.mxc, now.mx2 = max(l.mx2,\
    \ r.mx2);\n    }\n    void eval(int x){\n        auto &now = seg[x];\n       \
    \ for (int i = 0; x < n && i < 2; ++i) {\n            add_((x<<1)|i, now.add);\n\
    \            chmin_((x<<1)|i, now.mx);\n            chmax_((x<<1)|i, now.mn);\n\
    \        }\n        now.add = 0;\n    }\n    void thrust(int k){ for (int i =\
    \ height-1; i >= 1; --i) eval(k>>i); }\n    void recalc(int k) { k = k >> __builtin_ctz(k);\
    \ while(k >>= 1) get(k);}\n\n    void in_chmin(int x, T val) {\n        if(seg[x].mx2\
    \ < val) chmin_(x, val);\n        else {\n            eval(x);\n            in_chmin((x<<1)|0,\
    \ val);\n            in_chmin((x<<1)|1, val);\n            get(x);\n        }\n\
    \    }\n    void in_chmax(int x, T val) {\n        if(seg[x].mn2 > val) chmax_(x,\
    \ val);\n        else {\n            eval(x);\n            in_chmax((x<<1)|0,\
    \ val);\n            in_chmax((x<<1)|1, val);\n            get(x);\n        }\n\
    \    }\npublic:\n#define RANGEX(NAME, INFUNC) \\\nvoid NAME(int a, int b, T val)\
    \ { \\\n    thrust(a += n); \\\n    thrust(b += n); \\\n    for(int l = a, r =\
    \ b; l < r; l >>=1, r>>=1) { \\\n        if (l & 1) INFUNC(l++, val); \\\n   \
    \     if (r & 1) INFUNC(--r, val); \\\n    } \\\n    recalc(a); \\\n    recalc(b);\
    \ \\\n}\n    RANGEX(chmin, in_chmin)\n    RANGEX(chmax, in_chmax)\n    RANGEX(add,\
    \ add_)\n#undef RANGEX\n    T sum(int a, int b) {\n        thrust(a += n);\n \
    \       thrust(b += n);\n        T res = 0;\n        for(int l = a, r = b; l <\
    \ r; l >>=1, r>>=1) {\n            if (l & 1) res += seg[l++].sum;\n         \
    \   if (r & 1) res += seg[--r].sum;\n        }\n        return res;\n    }\n \
    \   struct M {\n        T sum, mx, mx2, mxc, mn, mn2, mnc, len, add;\n       \
    \ M() : mx2(-INF<T>), mxc(1), mn2(INF<T>), mnc(1), add(0) {};\n    };\n    vector<M>\
    \ seg;\n    int n, height;\n    SegmentTreeBeats() = default;\n    SegmentTreeBeats(const\
    \ vector<T>& v){\n        n = 1, height = 1;\n        while(n < v.size()) n <<=\
    \ 1, height++;\n        seg.resize(2*n);\n        for (int i = 0; i < v.size();\
    \ ++i) {\n            seg[i+n].sum = seg[i+n].mx = seg[i+n].mn = v[i];\n     \
    \       seg[i+n].len = 1;\n        }\n        for (int i = n-1; i >= 1; --i) get(i);\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/segbeats.cpp
  requiredBy: []
  timestamp: '2020-10-20 21:27:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_range_chmin_chmax_add_range_sum.test.cpp
documentation_of: datastructure/segbeats.cpp
layout: document
redirect_from:
- /library/datastructure/segbeats.cpp
- /library/datastructure/segbeats.cpp.html
title: datastructure/segbeats.cpp
---
