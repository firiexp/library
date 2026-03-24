---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/wavelet_matrix.cpp
    title: Wavelet Matrix
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
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
    \ntemplate <class T>\nstruct WaveletMatrix {\n    int n, lg, blocks;\n    vector<int>\
    \ mid;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<T>\
    \ vals;\n\n    WaveletMatrix() : n(0), lg(0), blocks(0) {}\n    explicit WaveletMatrix(const\
    \ vector<T> &v) { build(v); }\n\n    void build(const vector<T> &v) {\n      \
    \  n = (int)v.size();\n        vals = v;\n        sort(vals.begin(), vals.end());\n\
    \        vals.erase(unique(vals.begin(), vals.end()), vals.end());\n\n       \
    \ if (vals.empty()) {\n            lg = 0;\n            blocks = 0;\n        \
    \    mid.clear();\n            bit.clear();\n            pref.clear();\n     \
    \       return;\n        }\n\n        int m = (int)vals.size();\n        lg =\
    \ 0;\n        while ((1 << lg) < m) lg++;\n        if (lg == 0) lg = 1;\n    \
    \    blocks = (n + 63) >> 6;\n\n        vector<int> cur(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            cur[i] = (int)(lower_bound(vals.begin(), vals.end(),\
    \ v[i]) - vals.begin());\n        }\n\n        mid.assign(lg, 0);\n        bit.assign(lg\
    \ * blocks, 0);\n        pref.assign(lg * (blocks + 1), 0);\n        vector<int>\
    \ nxt(n);\n\n        for (int d = 0; d < lg; ++d) {\n            int shift = lg\
    \ - 1 - d;\n            auto *row = bit.data() + d * blocks;\n            auto\
    \ *row_pref = pref.data() + d * (blocks + 1);\n            int zero_cnt = 0;\n\
    \            for (int i = 0; i < n; ++i) {\n                int b = (cur[i] >>\
    \ shift) & 1;\n                if (b) row[i >> 6] |= 1ULL << (i & 63);\n     \
    \           else ++zero_cnt;\n            }\n            mid[d] = zero_cnt;\n\
    \            for (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] +\
    \ __builtin_popcountll(row[i]);\n\n            int zi = 0, oi = zero_cnt;\n  \
    \          for (int i = 0; i < n; ++i) {\n                int x = cur[i];\n  \
    \              if ((x >> shift) & 1) nxt[oi++] = x;\n                else nxt[zi++]\
    \ = x;\n            }\n            cur.swap(nxt);\n        }\n    }\n\n    int\
    \ rank1(int d, int r) const {\n        int base = d * blocks;\n        int pref_base\
    \ = d * (blocks + 1);\n        int block = r >> 6;\n        int ret = pref[pref_base\
    \ + block];\n        int rem = r & 63;\n        if (rem) ret += __builtin_popcountll(bit[base\
    \ + block] & ((1ULL << rem) - 1));\n        return ret;\n    }\n\n    int rank0(int\
    \ d, int r) const {\n        return r - rank1(d, r);\n    }\n\n    int count_less_index(int\
    \ l, int r, int xi) const {\n        if (xi <= 0 || l >= r || n == 0) return 0;\n\
    \        if (xi >= (int)vals.size()) return r - l;\n\n        int res = 0;\n \
    \       for (int d = 0; d < lg; ++d) {\n            int shift = lg - 1 - d;\n\
    \            int b = (xi >> shift) & 1;\n            int l0 = rank0(d, l), r0\
    \ = rank0(d, r);\n            if (b) {\n                res += r0 - l0;\n    \
    \            l = mid[d] + rank1(d, l);\n                r = mid[d] + rank1(d,\
    \ r);\n            }\n            else {\n                l = l0;\n          \
    \      r = r0;\n            }\n        }\n        return res;\n    }\n\n    int\
    \ count_less(int l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_less_index(l, r, xi);\n\
    \    }\n\n    int range_freq(int l, int r, const T &lower, const T &upper) const\
    \ {\n        if (lower >= upper || l >= r) return 0;\n        return count_less(l,\
    \ r, upper) - count_less(l, r, lower);\n    }\n\n    int freq(int l, int r, const\
    \ T &x) const {\n        int li = (int)(lower_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        int ri = (int)(upper_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        return count_less_index(l, r, ri) - count_less_index(l,\
    \ r, li);\n    }\n\n    T kth_smallest(int l, int r, int k) const {\n        int\
    \ idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int l0 = rank0(d,\
    \ l), r0 = rank0(d, r);\n            int z = r0 - l0;\n            idx <<= 1;\n\
    \            if (k < z) {\n                l = l0;\n                r = r0;\n\
    \            }\n            else {\n                k -= z;\n                idx\
    \ |= 1;\n                l = mid[d] + rank1(d, l);\n                r = mid[d]\
    \ + rank1(d, r);\n            }\n        }\n        return vals[idx];\n    }\n\
    \n    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        int cnt = count_less(l, r, upper);\n        if (cnt\
    \ == 0) return false;\n        res = kth_smallest(l, r, cnt - 1);\n        return\
    \ true;\n    }\n\n    bool next_value(int l, int r, const T &lower, T &res) const\
    \ {\n        int cnt = count_less(l, r, lower);\n        if (cnt == r - l) return\
    \ false;\n        res = kth_smallest(l, r, cnt);\n        return true;\n    }\n\
    };\n\n/**\n * @brief Wavelet Matrix\n */\n#line 8 \"test/yosupo_static_range_frequency.test.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value :\
    \ false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
    \n    constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0),\
    \ size(0), interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n\
    \        int len = size - idx;\n        memmove(buf, buf + idx, len);\n      \
    \  if (interactive) {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin))\
    \ size = len + (int)strlen(buf + len);\n            else size = len;\n       \
    \ } else {\n            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void\
    \ ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void\
    \ ensure_interactive() {\n        if (idx == size) load();\n    }\n\n    inline\
    \ char skip() {\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            return buf[idx++];\n\
    \        }\n        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n\
    \            ++idx;\n            ensure();\n        }\n        return buf[idx++];\n\
    \    }\n\n    template<class T, typename enable_if<is_integral<T>::value, int>::type\
    \ = 0>\n    void read(T &x) {\n        if (interactive) {\n            char c\
    \ = skip();\n            bool neg = false;\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    neg = true;\n      \
    \              ensure_interactive();\n                    c = buf[idx++];\n  \
    \              }\n            }\n            x = 0;\n            while (c >= '0')\
    \ {\n                x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class T, typename\
    \ enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>\n\
    \    void read(T &x) {\n        long long v;\n        read(v);\n        x = T(v);\n\
    \    }\n\n    template<class Head, class Next, class... Tail>\n    void read(Head\
    \ &head, Next &next, Tail &...tail) {\n        read(head);\n        read(next,\
    \ tail...);\n    }\n\n    template<class T, class U>\n    void read(pair<T, U>\
    \ &p) {\n        read(p.first, p.second);\n    }\n\n    template<class T, typename\
    \ enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value,\
    \ int>::type = 0>\n    void read(T &a) {\n        for (auto &x : a) read(x);\n\
    \    }\n\n    void read(char &c) {\n        c = skip();\n    }\n\n    void read(string\
    \ &s) {\n        s.clear();\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            while (true)\
    \ {\n                int start = idx;\n                while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n                s.append(buf + start, idx - start);\n       \
    \         if (idx < size) break;\n                load();\n                if\
    \ (size == 0) break;\n            }\n            if (idx < size) ++idx;\n    \
    \        return;\n        }\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    bool interactive;\n    inline static constexpr FastIoDigitTable table{};\n\
    \n    Printer() : idx(0), interactive(isatty(fileno(stdout))) {}\n    ~Printer()\
    \ { flush(); }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n        if (interactive && c == '\\n') flush();\n    }\n\n    inline void\
    \ print_range(const char *s, size_t n) {\n        size_t pos = 0;\n        while\
    \ (pos < n) {\n            if (idx == BUFSIZE) flush();\n            size_t chunk\
    \ = min(n - pos, (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s +\
    \ pos, chunk);\n            idx += (int)chunk;\n            pos += chunk;\n  \
    \      }\n    }\n\n    void print(const char *s) {\n        print_range(s, strlen(s));\n\
    \    }\n\n    void print(const string &s) {\n        print_range(s.data(), s.size());\n\
    \    }\n\n    void print(char c) {\n        pc(c);\n    }\n\n    void print(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void print(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
    \ U = typename make_unsigned<T>::type;\n        U y;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (x < 0) {\n                buf[idx++] = '-';\n           \
    \     y = U(0) - static_cast<U>(x);\n            } else {\n                y =\
    \ static_cast<U>(x);\n            }\n        } else {\n            y = x;\n  \
    \      }\n        if (y == 0) {\n            buf[idx++] = '0';\n            return;\n\
    \        }\n        static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n    \
    \    char tmp[TMP_SIZE];\n        int pos = TMP_SIZE;\n        while (y >= 10000)\
    \ {\n            pos -= 4;\n            memcpy(tmp + pos, table.num + (y % 10000)\
    \ * 4, 4);\n            y /= 10000;\n        }\n        if (y >= 1000) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2), 4);\n            idx += 4;\n\
    \        } else if (y >= 100) {\n            memcpy(buf + idx, table.num + (y\
    \ << 2) + 1, 3);\n            idx += 3;\n        } else if (y >= 10) {\n     \
    \       unsigned q = (unsigned(y) * 205) >> 11;\n            buf[idx] = char('0'\
    \ + q);\n            buf[idx + 1] = char('0' + (unsigned(y) - q * 10));\n    \
    \        idx += 2;\n        } else {\n            buf[idx++] = char('0' + y);\n\
    \        }\n        memcpy(buf + idx, tmp + pos, TMP_SIZE - pos);\n        idx\
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ print(const T &a) {\n        bool first = true;\n        for (auto &&x : a)\
    \ {\n            if (!first) pc(' ');\n            first = false;\n          \
    \  print(x);\n        }\n    }\n\n    template<class T>\n    void println(const\
    \ T &x) {\n        print(x);\n        pc('\\n');\n    }\n\n    template<class\
    \ Head, class... Tail>\n    void println(const Head &head, const Tail &...tail)\
    \ {\n        print(head);\n        ((pc(' '), print(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void println() {\n        pc('\\n');\n    }\n};\n\ntemplate<class\
    \ T>\nScanner &operator>>(Scanner &in, T &x) {\n    in.read(x);\n    return in;\n\
    }\n\ntemplate<class T>\nPrinter &operator<<(Printer &out, const T &x) {\n    out.print(x);\n\
    \    return out;\n}\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n\
    \ */\n#line 14 \"test/yosupo_static_range_frequency.test.cpp\"\n\nint main() {\n\
    \    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n    in.read(q);\n\
    \    vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\n   \
    \ WaveletMatrix<int> wm(a);\n    while (q--) {\n        int l, r, x;\n       \
    \ in.read(l);\n        in.read(r);\n        in.read(x);\n        out.println(wm.freq(l,\
    \ r, x));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include <algorithm>\n#include <vector>\nusing namespace std;\n\n#include\
    \ \"../datastructure/wavelet_matrix.cpp\"\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    \nint main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n\
    \    in.read(q);\n    vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\
    \n    WaveletMatrix<int> wm(a);\n    while (q--) {\n        int l, r, x;\n   \
    \     in.read(l);\n        in.read(r);\n        in.read(x);\n        out.println(wm.freq(l,\
    \ r, x));\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/wavelet_matrix.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_static_range_frequency.test.cpp
- /verify/test/yosupo_static_range_frequency.test.cpp.html
title: test/yosupo_static_range_frequency.test.cpp
---
