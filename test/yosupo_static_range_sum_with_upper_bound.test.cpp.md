---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/weighted_wavelet_matrix.cpp
    title: "\u91CD\u307F\u4ED8\u304DWavelet Matrix(Weighted Wavelet Matrix)"
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound
    links:
    - https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound
  bundledCode: "#line 1 \"test/yosupo_static_range_sum_with_upper_bound.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound\"\
    \n\n#include <algorithm>\n#include <type_traits>\n#include <vector>\nusing namespace\
    \ std;\n\n#line 1 \"datastructure/weighted_wavelet_matrix.cpp\"\ntemplate <class\
    \ T, class U>\nstruct WeightedWaveletMatrix {\n    struct CountSum {\n       \
    \ int count;\n        U sum;\n    };\n\n    int n, lg, blocks;\n    vector<int>\
    \ mid;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<U>\
    \ zero_sum;\n    vector<U> base_sum;\n    vector<T> vals;\n\n    WeightedWaveletMatrix()\
    \ : n(0), lg(0), blocks(0) {}\n    WeightedWaveletMatrix(const vector<T> &v, const\
    \ vector<U> &w) { build(v, w); }\n\n    static inline void rank1_pair(const unsigned\
    \ long long *row, const int *row_pref, int l, int r, int &l1, int &r1) {\n   \
    \     int l_block = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem\
    \ = l & 63;\n        if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL\
    \ << l_rem) - 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n\
    \        int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class X>\n    static auto\
    \ encode_key(X x) -> typename make_unsigned<X>::type {\n        using Key = typename\
    \ make_unsigned<X>::type;\n        Key key = static_cast<Key>(x);\n        if\
    \ constexpr (is_signed<X>::value) key ^= (Key(1) << (sizeof(X) * 8 - 1));\n  \
    \      return key;\n    }\n\n    void compress_generic(const vector<T> &v, vector<int>\
    \ &cur) {\n        vector<pair<T, int>> ord(n);\n        for (int i = 0; i < n;\
    \ ++i) ord[i] = {v[i], i};\n        sort(ord.begin(), ord.end(), [](const pair<T,\
    \ int> &a, const pair<T, int> &b) {\n            return a.first < b.first;\n \
    \       });\n        vals.clear();\n        vals.reserve(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            if (vals.empty() || vals.back() < ord[i].first\
    \ || ord[i].first < vals.back()) {\n                vals.push_back(ord[i].first);\n\
    \            }\n            cur[ord[i].second] = (int)vals.size() - 1;\n     \
    \   }\n    }\n\n    void compress_integral(const vector<T> &v, vector<int> &cur)\
    \ {\n        using Key = typename make_unsigned<T>::type;\n        vector<Key>\
    \ keys(n);\n        vector<int> ord(n), buf(n);\n        for (int i = 0; i < n;\
    \ ++i) {\n            keys[i] = encode_key(v[i]);\n            ord[i] = i;\n \
    \       }\n\n        const int B = 16;\n        const int MASK = (1 << B) - 1;\n\
    \        const int bucket_count = 1 << B;\n        const int passes = (int)(sizeof(Key)\
    \ * 8 + B - 1) / B;\n        vector<int> cnt(bucket_count), pos(bucket_count);\n\
    \        for (int pass = 0; pass < passes; ++pass) {\n            fill(cnt.begin(),\
    \ cnt.end(), 0);\n            int shift = pass * B;\n            for (int i =\
    \ 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];\n            pos[0] =\
    \ 0;\n            for (int i = 0; i + 1 < bucket_count; ++i) pos[i + 1] = pos[i]\
    \ + cnt[i];\n            for (int i = 0; i < n; ++i) {\n                int id\
    \ = ord[i];\n                buf[pos[(keys[id] >> shift) & MASK]++] = id;\n  \
    \          }\n            ord.swap(buf);\n        }\n\n        vals.clear();\n\
    \        vals.reserve(n);\n        bool has_prev = false;\n        Key prev =\
    \ 0;\n        for (int i = 0; i < n; ++i) {\n            int id = ord[i];\n  \
    \          if (!has_prev || keys[id] != prev) {\n                vals.push_back(v[id]);\n\
    \                prev = keys[id];\n                has_prev = true;\n        \
    \    }\n            cur[id] = (int)vals.size() - 1;\n        }\n    }\n\n    void\
    \ compress_values(const vector<T> &v, vector<int> &cur) {\n        if constexpr\
    \ (is_integral<T>::value && sizeof(T) <= 8) compress_integral(v, cur);\n     \
    \   else compress_generic(v, cur);\n    }\n\n    void build_from_index_internal(vector<int>\
    \ cur, const vector<U> &w) {\n        n = (int)cur.size();\n        base_sum.assign(n\
    \ + 1, U());\n        for (int i = 0; i < n; ++i) base_sum[i + 1] = base_sum[i]\
    \ + w[i];\n\n        if (n == 0) {\n            lg = 0;\n            blocks =\
    \ 0;\n            mid.clear();\n            bit.clear();\n            pref.clear();\n\
    \            zero_sum.clear();\n            return;\n        }\n\n        int\
    \ m = (int)vals.size();\n        lg = 0;\n        while ((1LL << lg) < m) ++lg;\n\
    \        if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n        vector<U>\
    \ cur_w = w;\n\n        mid.assign(lg, 0);\n        bit.assign(lg * blocks, 0);\n\
    \        pref.assign(lg * (blocks + 1), 0);\n        zero_sum.assign(lg * (n +\
    \ 1), U());\n        vector<int> nxt(n);\n        vector<U> nxt_w(n);\n\n    \
    \    for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            auto\
    \ *row = bit.data() + d * blocks;\n            auto *row_pref = pref.data() +\
    \ d * (blocks + 1);\n            auto *row_zero_sum = zero_sum.data() + d * (n\
    \ + 1);\n            int zero_cnt = 0;\n            for (int i = 0; i < n; ++i)\
    \ {\n                int x = cur[i];\n                int b = (x >> shift) & 1;\n\
    \                if (b) row[i >> 6] |= 1ULL << (i & 63);\n                else\
    \ ++zero_cnt;\n                row_zero_sum[i + 1] = row_zero_sum[i] + (b ? U()\
    \ : cur_w[i]);\n            }\n            mid[d] = zero_cnt;\n            for\
    \ (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);\n\
    \n            int zi = 0, oi = zero_cnt;\n            for (int i = 0; i < n; ++i)\
    \ {\n                int x = cur[i];\n                if ((x >> shift) & 1) {\n\
    \                    nxt[oi] = x;\n                    nxt_w[oi++] = cur_w[i];\n\
    \                }\n                else {\n                    nxt[zi] = x;\n\
    \                    nxt_w[zi++] = cur_w[i];\n                }\n            }\n\
    \            cur.swap(nxt);\n            cur_w.swap(nxt_w);\n        }\n    }\n\
    \n    void build(const vector<T> &v, const vector<U> &w) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            zero_sum.clear();\n            base_sum.assign(1,\
    \ U());\n            return;\n        }\n\n        vector<int> cur(n);\n     \
    \   compress_values(v, cur);\n        build_from_index_internal(move(cur), w);\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals,\
    \ const vector<U> &w) {\n        vals = sorted_vals;\n        build_from_index_internal(idx,\
    \ w);\n    }\n\n    CountSum count_sum_less_index(int l, int r, int xi) const\
    \ {\n        if (xi <= 0 || l >= r || n == 0) return {0, U()};\n        if (xi\
    \ >= (int)vals.size()) return {r - l, base_sum[r] - base_sum[l]};\n\n        const\
    \ int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n  \
    \      const int *pref_data = pref.data();\n        const U *zero_sum_data = zero_sum.data();\n\
    \        CountSum res{0, U()};\n        for (int d = 0, shift = lg - 1; d < lg;\
    \ ++d, --shift) {\n            int l1, r1;\n            rank1_pair(bit_data, pref_data,\
    \ l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n            if ((xi\
    \ >> shift) & 1) {\n                res.count += r0 - l0;\n                res.sum\
    \ += zero_sum_data[r] - zero_sum_data[l];\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n            zero_sum_data\
    \ += n + 1;\n        }\n        return res;\n    }\n\n    CountSum count_sum_less(int\
    \ l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_sum_less_index(l, r, xi);\n\
    \    }\n\n    CountSum count_sum_less_equal(int l, int r, const T &x) const {\n\
    \        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_sum_less_index(l, r, xi);\n    }\n\n    int count_less(int\
    \ l, int r, const T &x) const {\n        return count_sum_less(l, r, x).count;\n\
    \    }\n\n    int count_less_equal(int l, int r, const T &x) const {\n       \
    \ return count_sum_less_equal(l, r, x).count;\n    }\n\n    U sum_less(int l,\
    \ int r, const T &x) const {\n        return count_sum_less(l, r, x).sum;\n  \
    \  }\n\n    U sum_less_equal(int l, int r, const T &x) const {\n        return\
    \ count_sum_less_equal(l, r, x).sum;\n    }\n};\n\n/**\n * @brief \u91CD\u307F\
    \u4ED8\u304DWavelet Matrix(Weighted Wavelet Matrix)\n */\n#line 9 \"test/yosupo_static_range_sum_with_upper_bound.test.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin)))\
    \ {}\n\n    inline void load() {\n        int len = size - idx;\n        memmove(buf,\
    \ buf + idx, len);\n        if (interactive) {\n            if (fgets(buf + len,\
    \ BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n          \
    \  else size = len;\n        } else {\n            size = len + (int)fread(buf\
    \ + len, 1, BUFSIZE - len, stdin);\n        }\n        idx = 0;\n        buf[size]\
    \ = 0;\n    }\n\n    inline void ensure() {\n        if (idx + OFFSET > size)\
    \ load();\n    }\n\n    inline void ensure_interactive() {\n        if (idx ==\
    \ size) load();\n    }\n\n    inline char skip() {\n        if (interactive) {\n\
    \            ensure_interactive();\n            while (buf[idx] && buf[idx] <=\
    \ ' ') {\n                ++idx;\n                ensure_interactive();\n    \
    \        }\n            return buf[idx++];\n        }\n        ensure();\n   \
    \     while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n\
    \        }\n        return buf[idx++];\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T &x) {\n  \
    \      if (interactive) {\n            char c = skip();\n            bool neg\
    \ = false;\n            if constexpr (is_signed<T>::value) {\n               \
    \ if (c == '-') {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       x = 0;\n            while (c >= '0') {\n                x = x * 10 + (c\
    \ & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg) x = -x;\n            }\n            return;\n        }\n      \
    \  char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        x = 0;\n        while (c\
    \ >= '0') {\n            x = x * 10 + (c & 15);\n            c = buf[idx++];\n\
    \        }\n        if constexpr (is_signed<T>::value) {\n            if (neg)\
    \ x = -x;\n        }\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ Head, class Next, class... Tail>\n    void read(Head &head, Next &next, Tail\
    \ &...tail) {\n        read(head);\n        read(next, tail...);\n    }\n\n  \
    \  template<class T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first,\
    \ p.second);\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void print(T x) {\n      \
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
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value,\
    \ int>::type = 0>\n    void print(const T &x) {\n        print(x.value());\n \
    \   }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \ */\n#line 14 \"test/yosupo_static_range_sum_with_upper_bound.test.cpp\"\n\n\
    int main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n\
    \    in.read(q);\n    vector<long long> a(n);\n    for (int i = 0; i < n; ++i)\
    \ in.read(a[i]);\n\n    vector<long long> vals = a;\n    sort(vals.begin(), vals.end());\n\
    \    vals.erase(unique(vals.begin(), vals.end()), vals.end());\n    vector<int>\
    \ idx(n);\n    for (int i = 0; i < n; ++i) idx[i] = (int)(lower_bound(vals.begin(),\
    \ vals.end(), a[i]) - vals.begin());\n\n    WeightedWaveletMatrix<long long, long\
    \ long> wm;\n    wm.build_from_index(idx, vals, a);\n    while (q--) {\n     \
    \   int l, r;\n        long long x;\n        in.read(l);\n        in.read(r);\n\
    \        in.read(x);\n        int xi = (int)(upper_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        auto res = wm.count_sum_less_index(l, r, xi);\n\
    \        out.println(res.count, res.sum);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound\"\
    \n\n#include <algorithm>\n#include <type_traits>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../datastructure/weighted_wavelet_matrix.cpp\"\n#include\
    \ <cstdio>\n#include <cstring>\n#include <string>\n\n#include \"../util/fastio.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n\
    \    in.read(q);\n    vector<long long> a(n);\n    for (int i = 0; i < n; ++i)\
    \ in.read(a[i]);\n\n    vector<long long> vals = a;\n    sort(vals.begin(), vals.end());\n\
    \    vals.erase(unique(vals.begin(), vals.end()), vals.end());\n    vector<int>\
    \ idx(n);\n    for (int i = 0; i < n; ++i) idx[i] = (int)(lower_bound(vals.begin(),\
    \ vals.end(), a[i]) - vals.begin());\n\n    WeightedWaveletMatrix<long long, long\
    \ long> wm;\n    wm.build_from_index(idx, vals, a);\n    while (q--) {\n     \
    \   int l, r;\n        long long x;\n        in.read(l);\n        in.read(r);\n\
    \        in.read(x);\n        int xi = (int)(upper_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        auto res = wm.count_sum_less_index(l, r, xi);\n\
    \        out.println(res.count, res.sum);\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/weighted_wavelet_matrix.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_static_range_sum_with_upper_bound.test.cpp
  requiredBy: []
  timestamp: '2026-03-26 00:19:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_static_range_sum_with_upper_bound.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_static_range_sum_with_upper_bound.test.cpp
- /verify/test/yosupo_static_range_sum_with_upper_bound.test.cpp.html
title: test/yosupo_static_range_sum_with_upper_bound.test.cpp
---
