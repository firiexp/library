---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/wavelet_matrix.cpp
    title: Wavelet Matrix
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
  bundledCode: "#line 1 \"test/yosupo_static_range_frequency.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/static_range_frequency\"\n\n#include <algorithm>\n\
    #include <vector>\nusing namespace std;\n\n#line 1 \"datastructure/wavelet_matrix.cpp\"\
    \ntemplate <class T>\nstruct WaveletMatrix {\n    int n, lg;\n    vector<int>\
    \ mid;\n    vector<vector<int>> bit;\n    vector<T> vals;\n\n    WaveletMatrix()\
    \ : n(0), lg(0) {}\n    explicit WaveletMatrix(const vector<T> &v) { build(v);\
    \ }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n    \
    \    vals = v;\n        sort(vals.begin(), vals.end());\n        vals.erase(unique(vals.begin(),\
    \ vals.end()), vals.end());\n\n        if (vals.empty()) {\n            lg = 0;\n\
    \            mid.clear();\n            bit.clear();\n            return;\n   \
    \     }\n\n        int m = (int)vals.size();\n        lg = 0;\n        while ((1\
    \ << lg) < m) lg++;\n        if (lg == 0) lg = 1;\n\n        vector<int> cur(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            cur[i] = (int)(lower_bound(vals.begin(),\
    \ vals.end(), v[i]) - vals.begin());\n        }\n\n        mid.assign(lg, 0);\n\
    \        bit.assign(lg, vector<int>(n + 1, 0));\n\n        for (int d = 0; d <\
    \ lg; ++d) {\n            int shift = lg - 1 - d;\n            vector<int> zero,\
    \ one;\n            zero.reserve(n);\n            one.reserve(n);\n          \
    \  for (int i = 0; i < n; ++i) {\n                int b = (cur[i] >> shift) &\
    \ 1;\n                bit[d][i + 1] = bit[d][i] + b;\n                if (b) one.push_back(cur[i]);\n\
    \                else zero.push_back(cur[i]);\n            }\n            mid[d]\
    \ = (int)zero.size();\n            cur.clear();\n            cur.insert(cur.end(),\
    \ zero.begin(), zero.end());\n            cur.insert(cur.end(), one.begin(), one.end());\n\
    \        }\n    }\n\n    int rank0(int d, int r) const {\n        return r - bit[d][r];\n\
    \    }\n\n    int rank1(int d, int r) const {\n        return bit[d][r];\n   \
    \ }\n\n    int count_less_index(int l, int r, int xi) const {\n        if (xi\
    \ <= 0 || l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size()) return\
    \ r - l;\n\n        int res = 0;\n        for (int d = 0; d < lg; ++d) {\n   \
    \         int shift = lg - 1 - d;\n            int b = (xi >> shift) & 1;\n  \
    \          int l0 = rank0(d, l), r0 = rank0(d, r);\n            if (b) {\n   \
    \             res += r0 - l0;\n                l = mid[d] + rank1(d, l);\n   \
    \             r = mid[d] + rank1(d, r);\n            }\n            else {\n \
    \               l = l0;\n                r = r0;\n            }\n        }\n \
    \       return res;\n    }\n\n    int count_less(int l, int r, const T &x) const\
    \ {\n        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, xi);\n    }\n\n    int range_freq(int l,\
    \ int r, const T &lower, const T &upper) const {\n        if (lower >= upper ||\
    \ l >= r) return 0;\n        return count_less(l, r, upper) - count_less(l, r,\
    \ lower);\n    }\n\n    int freq(int l, int r, const T &x) const {\n        int\
    \ li = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n     \
    \   int ri = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, ri) - count_less_index(l, r, li);\n   \
    \ }\n\n    T kth_smallest(int l, int r, int k) const {\n        int idx = 0;\n\
    \        for (int d = 0; d < lg; ++d) {\n            int l0 = rank0(d, l), r0\
    \ = rank0(d, r);\n            int z = r0 - l0;\n            idx <<= 1;\n     \
    \       if (k < z) {\n                l = l0;\n                r = r0;\n     \
    \       }\n            else {\n                k -= z;\n                idx |=\
    \ 1;\n                l = mid[d] + rank1(d, l);\n                r = mid[d] +\
    \ rank1(d, r);\n            }\n        }\n        return vals[idx];\n    }\n\n\
    \    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        int cnt = count_less(l, r, upper);\n        if (cnt\
    \ == 0) return false;\n        res = kth_smallest(l, r, cnt - 1);\n        return\
    \ true;\n    }\n\n    bool next_value(int l, int r, const T &lower, T &res) const\
    \ {\n        int cnt = count_less(l, r, lower);\n        if (cnt == r - l) return\
    \ false;\n        res = kth_smallest(l, r, cnt);\n        return true;\n    }\n\
    };\n\n/**\n * @brief Wavelet Matrix\n */\n#line 1 \"util/fastio.cpp\"\n#include\
    \ <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\nusing\
    \ namespace std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr\
    \ FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000; ++i) {\n  \
    \          int x = i;\n            for (int j = 3; j >= 0; --j) {\n          \
    \      num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n      \
    \      }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE\
    \ = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n\
    \    int idx, size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load()\
    \ {\n        int len = size - idx;\n        memmove(buf, buf + idx, len);\n  \
    \      size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx\
    \ = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if\
    \ (idx + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
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
    \ 9 \"test/yosupo_static_range_frequency.test.cpp\"\n\nint main() {\n    Scanner\
    \ in;\n    Printer out;\n    int n, q;\n    in.read(n);\n    in.read(q);\n   \
    \ vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\n    WaveletMatrix<int>\
    \ wm(a);\n    while (q--) {\n        int l, r, x;\n        in.read(l);\n     \
    \   in.read(r);\n        in.read(x);\n        out.writeln(wm.freq(l, r, x));\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include <algorithm>\n#include <vector>\nusing namespace std;\n\n#include\
    \ \"../datastructure/wavelet_matrix.cpp\"\n#include \"../util/fastio.cpp\"\n\n\
    int main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n\
    \    in.read(q);\n    vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\
    \n    WaveletMatrix<int> wm(a);\n    while (q--) {\n        int l, r, x;\n   \
    \     in.read(l);\n        in.read(r);\n        in.read(x);\n        out.writeln(wm.freq(l,\
    \ r, x));\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/wavelet_matrix.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_static_range_frequency.test.cpp
- /verify/test/yosupo_static_range_frequency.test.cpp.html
title: test/yosupo_static_range_frequency.test.cpp
---
