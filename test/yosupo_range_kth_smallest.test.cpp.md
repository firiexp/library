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
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/yosupo_range_kth_smallest.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#include <algorithm>\n\
    #include <type_traits>\n#include <vector>\nusing namespace std;\n\n#line 1 \"\
    datastructure/wavelet_matrix.cpp\"\ntemplate <class T>\nstruct WaveletMatrix {\n\
    \    int n, lg, blocks;\n    vector<int> mid;\n    vector<unsigned long long>\
    \ bit;\n    vector<int> pref;\n    vector<T> vals;\n\n    WaveletMatrix() : n(0),\
    \ lg(0), blocks(0) {}\n    explicit WaveletMatrix(const vector<T> &v) { build(v);\
    \ }\n\n    static inline void rank1_pair(const unsigned long long *row, const\
    \ int *row_pref, int l, int r, int &l1, int &r1) {\n        int l_block = l >>\
    \ 6;\n        l1 = row_pref[l_block];\n        int l_rem = l & 63;\n        if\
    \ (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) - 1));\n\n\
    \        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n        int r_rem\
    \ = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block] & ((1ULL\
    \ << r_rem) - 1));\n    }\n\n    template <class U>\n    static auto encode_key(U\
    \ x) -> typename make_unsigned<U>::type {\n        using Key = typename make_unsigned<U>::type;\n\
    \        Key key = static_cast<Key>(x);\n        if constexpr (is_signed<U>::value)\
    \ key ^= (Key(1) << (sizeof(U) * 8 - 1));\n        return key;\n    }\n\n    void\
    \ compress_generic(const vector<T> &v, vector<int> &cur) {\n        vector<pair<T,\
    \ int>> ord(n);\n        for (int i = 0; i < n; ++i) ord[i] = {v[i], i};\n   \
    \     sort(ord.begin(), ord.end(), [](const pair<T, int> &a, const pair<T, int>\
    \ &b) {\n            return a.first < b.first;\n        });\n        vals.clear();\n\
    \        vals.reserve(n);\n        for (int i = 0; i < n; ++i) {\n           \
    \ if (vals.empty() || vals.back() < ord[i].first || ord[i].first < vals.back())\
    \ {\n                vals.push_back(ord[i].first);\n            }\n          \
    \  cur[ord[i].second] = (int)vals.size() - 1;\n        }\n    }\n\n    void compress_integral(const\
    \ vector<T> &v, vector<int> &cur) {\n        using Key = typename make_unsigned<T>::type;\n\
    \        vector<Key> keys(n);\n        vector<int> ord(n), buf(n);\n        for\
    \ (int i = 0; i < n; ++i) {\n            keys[i] = encode_key(v[i]);\n       \
    \     ord[i] = i;\n        }\n\n        const int B = 16;\n        const int MASK\
    \ = (1 << B) - 1;\n        const int bucket_count = 1 << B;\n        const int\
    \ passes = (int)(sizeof(Key) * 8 + B - 1) / B;\n        vector<int> cnt(bucket_count),\
    \ pos(bucket_count);\n        for (int pass = 0; pass < passes; ++pass) {\n  \
    \          fill(cnt.begin(), cnt.end(), 0);\n            int shift = pass * B;\n\
    \            for (int i = 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];\n\
    \            pos[0] = 0;\n            for (int i = 0; i + 1 < bucket_count; ++i)\
    \ pos[i + 1] = pos[i] + cnt[i];\n            for (int i = 0; i < n; ++i) {\n \
    \               int id = ord[i];\n                buf[pos[(keys[id] >> shift)\
    \ & MASK]++] = id;\n            }\n            ord.swap(buf);\n        }\n\n \
    \       vals.clear();\n        vals.reserve(n);\n        bool has_prev = false;\n\
    \        Key prev = 0;\n        for (int i = 0; i < n; ++i) {\n            int\
    \ id = ord[i];\n            if (!has_prev || keys[id] != prev) {\n           \
    \     vals.push_back(v[id]);\n                prev = keys[id];\n             \
    \   has_prev = true;\n            }\n            cur[id] = (int)vals.size() -\
    \ 1;\n        }\n    }\n\n    void compress_values(const vector<T> &v, vector<int>\
    \ &cur) {\n        if constexpr (is_integral<T>::value && sizeof(T) <= 8) compress_integral(v,\
    \ cur);\n        else compress_generic(v, cur);\n    }\n\n    void build_from_index_internal(vector<int>\
    \ cur) {\n        n = (int)cur.size();\n        if (n == 0) {\n            lg\
    \ = 0;\n            blocks = 0;\n            mid.clear();\n            bit.clear();\n\
    \            pref.clear();\n            return;\n        }\n\n        int m =\
    \ (int)vals.size();\n        lg = 0;\n        while ((1LL << lg) < m) ++lg;\n\
    \        if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n\n        mid.assign(lg,\
    \ 0);\n        bit.assign(lg * blocks, 0);\n        pref.assign(lg * (blocks +\
    \ 1), 0);\n        vector<int> nxt(n);\n\n        for (int d = 0, shift = lg -\
    \ 1; d < lg; ++d, --shift) {\n            auto *row = bit.data() + d * blocks;\n\
    \            auto *row_pref = pref.data() + d * (blocks + 1);\n            int\
    \ zero_cnt = 0;\n            for (int i = 0; i < n; ++i) {\n                int\
    \ x = cur[i];\n                int b = (x >> shift) & 1;\n                if (b)\
    \ row[i >> 6] |= 1ULL << (i & 63);\n                else ++zero_cnt;\n       \
    \     }\n            mid[d] = zero_cnt;\n            for (int i = 0; i < blocks;\
    \ ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);\n\n     \
    \       int zi = 0, oi = zero_cnt;\n            for (int i = 0; i < n; ++i) {\n\
    \                int x = cur[i];\n                if ((x >> shift) & 1) nxt[oi++]\
    \ = x;\n                else nxt[zi++] = x;\n            }\n            cur.swap(nxt);\n\
    \        }\n    }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            return;\n        }\n\n        vector<int>\
    \ cur(n);\n        compress_values(v, cur);\n        build_from_index_internal(move(cur));\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals)\
    \ {\n        vals = sorted_vals;\n        build_from_index_internal(idx);\n  \
    \  }\n\n    int count_less_index(int l, int r, int xi) const {\n        if (xi\
    \ <= 0 || l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size()) return\
    \ r - l;\n\n        const int *mid_data = mid.data();\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        int res\
    \ = 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n    \
    \        int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1)\
    \ {\n                res += r0 - l0;\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ res;\n    }\n\n    int count_less(int l, int r, const T &x) const {\n      \
    \  int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, xi);\n    }\n\n    int count_equal_index(int\
    \ l, int r, int xi) const {\n        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size())\
    \ return 0;\n\n        const int *mid_data = mid.data();\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n  \
    \          rank1_pair(bit_data, pref_data, l, r, l1, r1);\n            int l0\
    \ = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n             \
    \   l = mid_data[d] + l1;\n                r = mid_data[d] + r1;\n           \
    \ }\n            else {\n                l = l0;\n                r = r0;\n  \
    \          }\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return r - l;\n    }\n\n    vector<pair<int, int>>\
    \ top_k_freq_index(int l, int r, int k) const {\n        if (k <= 0 || l >= r\
    \ || n == 0) return {};\n\n        struct Node {\n            int l, r, d, idx;\n\
    \            long long lower;\n        };\n        struct Item {\n           \
    \ int freq, idx;\n        };\n\n        auto item_better = [](const Item &a, const\
    \ Item &b) {\n            if (a.freq != b.freq) return a.freq > b.freq;\n    \
    \        return a.idx < b.idx;\n        };\n        auto node_worse = [](const\
    \ Node &a, const Node &b) {\n            int ca = a.r - a.l;\n            int\
    \ cb = b.r - b.l;\n            if (ca != cb) return ca < cb;\n            if (a.lower\
    \ != b.lower) return a.lower > b.lower;\n            return a.d < b.d;\n     \
    \   };\n\n        vector<Node> heap;\n        heap.push_back({l, r, 0, 0, 0});\n\
    \        vector<Item> best;\n        best.reserve(min(k, r - l));\n\n        while\
    \ (!heap.empty()) {\n            if ((int)best.size() == k) {\n              \
    \  const Node &cur = heap.front();\n                const Item &cut = best.front();\n\
    \                int freq = cur.r - cur.l;\n                if (freq < cut.freq)\
    \ break;\n                if (freq == cut.freq && cur.lower >= cut.idx) break;\n\
    \            }\n\n            pop_heap(heap.begin(), heap.end(), node_worse);\n\
    \            Node cur = heap.back();\n            heap.pop_back();\n\n       \
    \     if (cur.d == lg) {\n                Item item{cur.r - cur.l, cur.idx};\n\
    \                if ((int)best.size() < k) {\n                    best.push_back(item);\n\
    \                    push_heap(best.begin(), best.end(), item_better);\n     \
    \           }\n                else if (item_better(item, best.front())) {\n \
    \                   pop_heap(best.begin(), best.end(), item_better);\n       \
    \             best.back() = item;\n                    push_heap(best.begin(),\
    \ best.end(), item_better);\n                }\n                continue;\n  \
    \          }\n\n            const auto *row = bit.data() + cur.d * blocks;\n \
    \           const int *row_pref = pref.data() + cur.d * (blocks + 1);\n      \
    \      int l1, r1;\n            rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);\n\
    \            int l0 = cur.l - l1, r0 = cur.r - r1;\n            int shift = lg\
    \ - cur.d - 1;\n            if (l0 < r0) {\n                heap.push_back({l0,\
    \ r0, cur.d + 1, cur.idx << 1, cur.lower});\n                push_heap(heap.begin(),\
    \ heap.end(), node_worse);\n            }\n            if (l1 < r1) {\n      \
    \          heap.push_back({\n                    mid[cur.d] + l1,\n          \
    \          mid[cur.d] + r1,\n                    cur.d + 1,\n                \
    \    cur.idx << 1 | 1,\n                    cur.lower + (1LL << shift)\n     \
    \           });\n                push_heap(heap.begin(), heap.end(), node_worse);\n\
    \            }\n        }\n\n        sort(best.begin(), best.end(), item_better);\n\
    \        vector<pair<int, int>> res;\n        res.reserve(best.size());\n    \
    \    for (const auto &item : best) res.push_back({item.freq, item.idx});\n   \
    \     return res;\n    }\n\n    vector<pair<int, T>> top_k_freq(int l, int r,\
    \ int k) const {\n        auto idx_res = top_k_freq_index(l, r, k);\n        vector<pair<int,\
    \ T>> res;\n        res.reserve(idx_res.size());\n        for (const auto &p :\
    \ idx_res) res.push_back({p.first, vals[p.second]});\n        return res;\n  \
    \  }\n\n    int range_freq(int l, int r, const T &lower, const T &upper) const\
    \ {\n        if (lower >= upper || l >= r) return 0;\n        return count_less(l,\
    \ r, upper) - count_less(l, r, lower);\n    }\n\n    int freq(int l, int r, const\
    \ T &x) const {\n        int xi = (int)(lower_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        if (xi == (int)vals.size() || vals[xi] != x) return\
    \ 0;\n        return count_equal_index(l, r, xi);\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        const int *mid_data = mid.data();\n      \
    \  const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int\
    \ l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n      \
    \      int l0 = l - l1, r0 = r - r1;\n            int z = r0 - l0;\n         \
    \   idx <<= 1;\n            if (k < z) {\n                l = l0;\n          \
    \      r = r0;\n            }\n            else {\n                k -= z;\n \
    \               idx |= 1;\n                l = mid_data[d] + l1;\n           \
    \     r = mid_data[d] + r1;\n            }\n            bit_data += blocks;\n\
    \            pref_data += blocks + 1;\n        }\n        return vals[idx];\n\
    \    }\n\n    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        int cnt = count_less(l, r, upper);\n        if (cnt\
    \ == 0) return false;\n        res = kth_smallest(l, r, cnt - 1);\n        return\
    \ true;\n    }\n\n    bool next_value(int l, int r, const T &lower, T &res) const\
    \ {\n        int cnt = count_less(l, r, lower);\n        if (cnt == r - l) return\
    \ false;\n        res = kth_smallest(l, r, cnt);\n        return true;\n    }\n\
    };\n\n/**\n * @brief Wavelet Matrix\n */\n#line 9 \"test/yosupo_range_kth_smallest.test.cpp\"\
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
    \ */\n#line 14 \"test/yosupo_range_kth_smallest.test.cpp\"\n\nint main() {\n \
    \   Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n    in.read(q);\n\
    \    vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\n   \
    \ WaveletMatrix<int> wm(a);\n    while (q--) {\n        int l, r, k;\n       \
    \ in.read(l);\n        in.read(r);\n        in.read(k);\n        out.println(wm.kth_smallest(l,\
    \ r, k));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include <algorithm>\n#include <type_traits>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../datastructure/wavelet_matrix.cpp\"\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n\n#include \"../util/fastio.cpp\"\n\nint\
    \ main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n\
    \    in.read(q);\n    vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\
    \n    WaveletMatrix<int> wm(a);\n    while (q--) {\n        int l, r, k;\n   \
    \     in.read(l);\n        in.read(r);\n        in.read(k);\n        out.println(wm.kth_smallest(l,\
    \ r, k));\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/wavelet_matrix.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2026-04-18 23:59:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_range_kth_smallest.test.cpp
- /verify/test/yosupo_range_kth_smallest.test.cpp.html
title: test/yosupo_range_kth_smallest.test.cpp
---
