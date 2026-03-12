---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/closest_pair.cpp
    title: Closest Pair
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/closest_pair
    links:
    - https://judge.yosupo.jp/problem/closest_pair
  bundledCode: "#line 1 \"test/yosupo_closest_pair.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/closest_pair\"\n\n#include <bits/stdc++.h>\n\n\
    using namespace std;\n\n#line 10 \"test/yosupo_closest_pair.test.cpp\"\n#include\
    \ <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nstruct\
    \ FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load() {\n  \
    \      int len = size - idx;\n        memmove(buf, buf + idx, len);\n        size\
    \ = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n\
    \        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if (idx\
    \ + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
    \        write_range(s.data(), s.size());\n    }\n\n    void write(char c) {\n\
    \        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void write(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line\
    \ 1 \"geometry/closest_pair.cpp\"\npair<int, int> closest_pair(const vector<pair<long\
    \ long, long long>> &points) {\n    using Dist = __int128_t;\n    struct P {\n\
    \        long long x;\n        long long y;\n        int idx;\n    };\n\n    int\
    \ n = points.size();\n    assert(n >= 2);\n    vector<P> ps(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        ps[i] = {points[i].first, points[i].second, i};\n\
    \    }\n    sort(ps.begin(), ps.end(), [](const P &a, const P &b) {\n        if\
    \ (a.x != b.x) return a.x < b.x;\n        if (a.y != b.y) return a.y < b.y;\n\
    \        return a.idx < b.idx;\n    });\n\n    Dist best = -1;\n    pair<int,\
    \ int> ans = {-1, -1};\n    auto update = [&](const P &a, const P &b) {\n    \
    \    Dist dx = Dist(a.x) - Dist(b.x);\n        Dist dy = Dist(a.y) - Dist(b.y);\n\
    \        Dist d = dx * dx + dy * dy;\n        pair<int, int> cand = {a.idx, b.idx};\n\
    \        if (best == -1 || d < best) {\n            best = d;\n            ans\
    \ = cand;\n        }\n    };\n    update(ps[0], ps[1]);\n\n    auto dfs = [&](auto\
    \ &&self, int l, int r) -> vector<int> {\n        if (r - l == 1) return {l};\n\
    \        int m = (l + r) >> 1;\n        long long mx = ps[m].x;\n        vector<int>\
    \ left = self(self, l, m);\n        vector<int> right = self(self, m, r);\n  \
    \      vector<int> ord;\n        vector<int> near;\n        ord.reserve(r - l);\n\
    \        near.reserve(r - l);\n        int i = 0, j = 0;\n        while (i < (int)left.size()\
    \ || j < (int)right.size()) {\n            int idx;\n            if (j == (int)right.size()\
    \ || (i < (int)left.size() && ps[left[i]].y < ps[right[j]].y)) {\n           \
    \     idx = left[i++];\n            } else {\n                idx = right[j++];\n\
    \            }\n            ord.push_back(idx);\n            Dist dx = Dist(ps[idx].x)\
    \ - Dist(mx);\n            if (dx * dx > best) continue;\n            for (int\
    \ k = (int)near.size() - 1; k >= 0; --k) {\n                int idy = near[k];\n\
    \                Dist dy = Dist(ps[idx].y) - Dist(ps[idy].y);\n              \
    \  if (best == 0 || dy * dy > best) break;\n                update(ps[idx], ps[idy]);\n\
    \            }\n            near.push_back(idx);\n        }\n        return ord;\n\
    \    };\n    dfs(dfs, 0, n);\n    return ans;\n}\n\n/**\n * @brief Closest Pair\n\
    \ */\n#line 14 \"test/yosupo_closest_pair.test.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    int t;\n    sc.read(t);\n    while (t--) {\n   \
    \     int n;\n        sc.read(n);\n        vector<pair<long long, long long>>\
    \ ps(n);\n        for (int i = 0; i < n; ++i) {\n            sc.read(ps[i].first,\
    \ ps[i].second);\n        }\n        auto [a, b] = closest_pair(ps);\n       \
    \ pr.writeln(a, b);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/closest_pair\"\n\n#include\
    \ <bits/stdc++.h>\n\nusing namespace std;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../geometry/closest_pair.cpp\"\n\nint main() {\n    Scanner sc;\n \
    \   Printer pr;\n\n    int t;\n    sc.read(t);\n    while (t--) {\n        int\
    \ n;\n        sc.read(n);\n        vector<pair<long long, long long>> ps(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            sc.read(ps[i].first, ps[i].second);\n\
    \        }\n        auto [a, b] = closest_pair(ps);\n        pr.writeln(a, b);\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - geometry/closest_pair.cpp
  isVerificationFile: true
  path: test/yosupo_closest_pair.test.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_closest_pair.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_closest_pair.test.cpp
- /verify/test/yosupo_closest_pair.test.cpp.html
title: test/yosupo_closest_pair.test.cpp
---
