---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/top_kth.cpp
    title: "\u4E0A\u4F4DK\u500B\u3092\u7BA1\u7406\u3059\u308B\u30C7\u30FC\u30BF\u69CB\
      \u9020 (Treap)"
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_top_kth.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <numeric>\n#include <random>\n#include <vector>\nusing namespace std;\n\
    \nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    extern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value\
    \ : false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
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
    \ */\n#line 1 \"datastructure/top_kth.cpp\"\ntemplate<class T, class SumT = long\
    \ long, bool Largest = true>\nclass TopKTreap {\nprivate:\n    struct Node {\n\
    \        T key;\n        int cnt;\n        int sz;\n        uint32_t pri;\n  \
    \      SumT sum;\n        int l;\n        int r;\n\n        Node(const T& key_,\
    \ uint32_t pri_)\n            : key(key_), cnt(1), sz(1), pri(pri_), sum((SumT)key_),\
    \ l(-1), r(-1) {}\n    };\n\n    int root_ = -1;\n    int K_ = 0;\n    uint32_t\
    \ rng_ = 2463534242u;\n    vector<Node> nodes_;\n    vector<int> free_nodes_;\n\
    \n    static bool goes_left(const T& x, const T& key) {\n        if constexpr\
    \ (Largest) return x < key;\n        else return x > key;\n    }\n\n    int size(int\
    \ t) const {\n        return t == -1 ? 0 : nodes_[t].sz;\n    }\n\n    SumT subtree_sum(int\
    \ t) const {\n        return t == -1 ? SumT(0) : nodes_[t].sum;\n    }\n\n   \
    \ void pull(int t) {\n        if (t == -1) return;\n        Node& node = nodes_[t];\n\
    \        node.sz = node.cnt + size(node.l) + size(node.r);\n        node.sum =\
    \ subtree_sum(node.l) + subtree_sum(node.r) + (SumT)node.key * node.cnt;\n   \
    \ }\n\n    uint32_t next_rand() {\n        uint32_t x = rng_;\n        x ^= x\
    \ << 13;\n        x ^= x >> 17;\n        x ^= x << 5;\n        rng_ = x;\n   \
    \     return x;\n    }\n\n    int make_node(const T& x) {\n        uint32_t pri\
    \ = next_rand();\n        if (!free_nodes_.empty()) {\n            int idx = free_nodes_.back();\n\
    \            free_nodes_.pop_back();\n            nodes_[idx] = Node(x, pri);\n\
    \            return idx;\n        }\n        nodes_.emplace_back(x, pri);\n  \
    \      return (int)nodes_.size() - 1;\n    }\n\n    void recycle_node(int t) {\n\
    \        if (t != -1) free_nodes_.push_back(t);\n    }\n\n    void rotate_left(int&\
    \ t) {\n        int r = nodes_[t].r;\n        nodes_[t].r = nodes_[r].l;\n   \
    \     nodes_[r].l = t;\n        pull(t);\n        pull(r);\n        t = r;\n \
    \   }\n\n    void rotate_right(int& t) {\n        int l = nodes_[t].l;\n     \
    \   nodes_[t].l = nodes_[l].r;\n        nodes_[l].r = t;\n        pull(t);\n \
    \       pull(l);\n        t = l;\n    }\n\n    void insert(int& t, const T& x)\
    \ {\n        if (t == -1) {\n            t = make_node(x);\n            return;\n\
    \        }\n\n        if (x == nodes_[t].key) {\n            ++nodes_[t].cnt;\n\
    \            pull(t);\n            return;\n        }\n\n        if (goes_left(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            insert(child,\
    \ x);\n            nodes_[t].l = child;\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[t].pri) rotate_right(t);\n        } else {\n            int child =\
    \ nodes_[t].r;\n            insert(child, x);\n            nodes_[t].r = child;\n\
    \            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);\n  \
    \      }\n        pull(t);\n    }\n\n    bool erase_one(int& t, const T& x) {\n\
    \        if (t == -1) return false;\n        bool ok = false;\n        if (goes_left(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].l = child;\n        } else if (goes_left(nodes_[t].key,\
    \ x)) {\n            int child = nodes_[t].r;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].r = child;\n        } else {\n            ok = true;\n\
    \            if (nodes_[t].cnt > 1) {\n                --nodes_[t].cnt;\n    \
    \            pull(t);\n                return true;\n            }\n         \
    \   if (nodes_[t].l == -1 || nodes_[t].r == -1) {\n                int old = t;\n\
    \                t = (nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r);\n\
    \                recycle_node(old);\n                return true;\n          \
    \  }\n            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {\n \
    \               rotate_right(t);\n                int child = nodes_[t].r;\n \
    \               ok = erase_one(child, x);\n                nodes_[t].r = child;\n\
    \            } else {\n                rotate_left(t);\n                int child\
    \ = nodes_[t].l;\n                ok = erase_one(child, x);\n                nodes_[t].l\
    \ = child;\n            }\n        }\n\n        if (t != -1) pull(t);\n      \
    \  return ok;\n    }\n\npublic:\n    explicit TopKTreap(int K = 0, uint32_t seed\
    \ = 2463534242u)\n        : root_(-1), K_(K), rng_(seed) {\n        assert(K >=\
    \ 0);\n        if (rng_ == 0) rng_ = 2463534242u;\n    }\n\n    TopKTreap(const\
    \ TopKTreap&) = delete;\n    TopKTreap& operator=(const TopKTreap&) = delete;\n\
    \n    void reserve(int capacity) {\n        assert(capacity >= 0);\n        nodes_.reserve(capacity);\n\
    \        free_nodes_.reserve(capacity);\n    }\n\n    int k() const {\n      \
    \  return K_;\n    }\n\n    void set_k(int new_k) {\n        assert(new_k >= 0);\n\
    \        K_ = new_k;\n    }\n\n    int size() const {\n        return size(root_);\n\
    \    }\n\n    bool empty() const {\n        return root_ == -1;\n    }\n\n   \
    \ SumT total_sum() const {\n        return subtree_sum(root_);\n    }\n\n    void\
    \ insert(const T& x) {\n        insert(root_, x);\n    }\n\n    bool erase_one(const\
    \ T& x) {\n        return erase_one(root_, x);\n    }\n\n    int count(const T&\
    \ x) const {\n        int t = root_;\n        while (t != -1) {\n            const\
    \ Node& node = nodes_[t];\n            if (x == node.key) return node.cnt;\n \
    \           t = goes_left(x, node.key) ? node.l : node.r;\n        }\n       \
    \ return 0;\n    }\n\n    bool contains(const T& x) const {\n        return count(x)\
    \ > 0;\n    }\n\n    T kth(int kth) const {\n        assert(1 <= kth && kth <=\
    \ size());\n\n        int t = root_;\n        while (t != -1) {\n            const\
    \ Node& node = nodes_[t];\n            int preferred_sz = size(node.r);\n    \
    \        if (kth <= preferred_sz) {\n                t = node.r;\n           \
    \ } else if (kth <= preferred_sz + node.cnt) {\n                return node.key;\n\
    \            } else {\n                kth -= preferred_sz + node.cnt;\n     \
    \           t = node.l;\n            }\n        }\n\n        assert(false);\n\
    \        return T();\n    }\n\n    bool has_kth() const {\n        return 1 <=\
    \ K_ && K_ <= size();\n    }\n\n    T kth() const {\n        assert(has_kth());\n\
    \        return kth(K_);\n    }\n\n    SumT sum_k(int k) const {\n        if (k\
    \ <= 0 || root_ == -1) return SumT(0);\n        if (k >= size()) return total_sum();\n\
    \        SumT res = 0;\n        int t = root_;\n        while (t != -1 && k >\
    \ 0) {\n            const Node& node = nodes_[t];\n            int preferred =\
    \ node.r;\n            int other = node.l;\n            int preferred_sz = size(preferred);\n\
    \            if (k <= preferred_sz) {\n                t = preferred;\n      \
    \          continue;\n            }\n            res += subtree_sum(preferred);\n\
    \            k -= preferred_sz;\n            int take = std::min(k, node.cnt);\n\
    \            res += (SumT)node.key * take;\n            k -= take;\n         \
    \   if (k == 0) break;\n            t = other;\n        }\n        return res;\n\
    \    }\n\n    SumT sum_topk() const {\n        return sum_k(K_);\n    }\n};\n\n\
    /**\n * @brief \u4E0A\u4F4DK\u500B\u3092\u7BA1\u7406\u3059\u308BTreap\n */\n#line\
    \ 19 \"test/yosupo_aplusb_top_kth.test.cpp\"\n\ntemplate<bool Largest>\nll brute_sum_k(const\
    \ vector<ll>& a, int k) {\n    if (k <= 0) return 0;\n    vector<ll> b = a;\n\
    \    sort(b.begin(), b.end());\n    if constexpr (Largest) reverse(b.begin(),\
    \ b.end());\n    k = min(k, (int)b.size());\n    return accumulate(b.begin(),\
    \ b.begin() + k, 0LL);\n}\n\ntemplate<bool Largest>\nll brute_kth(const vector<ll>&\
    \ a, int k) {\n    vector<ll> b = a;\n    sort(b.begin(), b.end());\n    if constexpr\
    \ (Largest) reverse(b.begin(), b.end());\n    return b[k - 1];\n}\n\ntemplate<bool\
    \ Largest>\nvoid verify_one(const vector<ll>& cur, const TopKTreap<ll, ll, Largest>&\
    \ ds) {\n    assert(ds.size() == (int)cur.size());\n    assert(ds.empty() == cur.empty());\n\
    \    assert(ds.total_sum() == accumulate(cur.begin(), cur.end(), 0LL));\n    for\
    \ (ll x = -8; x <= 8; ++x) {\n        int cnt = 0;\n        for (ll y : cur) cnt\
    \ += x == y;\n        assert(ds.count(x) == cnt);\n        assert(ds.contains(x)\
    \ == (cnt > 0));\n    }\n    for (int k = 0; k <= (int)cur.size() + 2; ++k) {\n\
    \        assert(ds.sum_k(k) == brute_sum_k<Largest>(cur, k));\n    }\n    if (!cur.empty())\
    \ {\n        for (int k = 1; k <= (int)cur.size(); ++k) {\n            assert(ds.kth(k)\
    \ == brute_kth<Largest>(cur, k));\n        }\n    }\n    if (ds.has_kth()) {\n\
    \        assert(ds.kth() == brute_kth<Largest>(cur, ds.k()));\n    } else {\n\
    \        assert(ds.k() <= 0 || ds.k() > (int)cur.size());\n    }\n    assert(ds.sum_topk()\
    \ == brute_sum_k<Largest>(cur, ds.k()));\n}\n\nvoid self_check() {\n    mt19937\
    \ rng(0);\n    for (int tc = 0; tc < 300; ++tc) {\n        TopKTreap<ll, ll, true>\
    \ largest(0, rng());\n        TopKTreap<ll, ll, false> smallest(0, rng());\n \
    \       largest.reserve(256);\n        smallest.reserve(256);\n        vector<ll>\
    \ cur;\n\n        for (int step = 0; step < 200; ++step) {\n            int op\
    \ = rng() % 4;\n            if (op <= 1) {\n                ll x = (int)(rng()\
    \ % 17) - 8;\n                largest.insert(x);\n                smallest.insert(x);\n\
    \                cur.push_back(x);\n            } else if (op == 2) {\n      \
    \          ll x = (int)(rng() % 17) - 8;\n                bool ok1 = largest.erase_one(x);\n\
    \                bool ok2 = smallest.erase_one(x);\n                auto it =\
    \ find(cur.begin(), cur.end(), x);\n                bool ok3 = it != cur.end();\n\
    \                if (ok3) cur.erase(it);\n                assert(ok1 == ok2);\n\
    \                assert(ok2 == ok3);\n            } else {\n                int\
    \ new_k = rng() % 12;\n                largest.set_k(new_k);\n               \
    \ smallest.set_k(new_k);\n            }\n            verify_one<true>(cur, largest);\n\
    \            verify_one<false>(cur, smallest);\n        }\n    }\n}\n\nint main()\
    \ {\n    self_check();\n\n    Scanner sc;\n    Printer pr;\n    ll a, b;\n   \
    \ sc.read(a, b);\n    pr.println(a + b);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <random>\n#include <vector>\n\
    using namespace std;\n\nusing ll = long long;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/top_kth.cpp\"\n\ntemplate<bool Largest>\nll brute_sum_k(const\
    \ vector<ll>& a, int k) {\n    if (k <= 0) return 0;\n    vector<ll> b = a;\n\
    \    sort(b.begin(), b.end());\n    if constexpr (Largest) reverse(b.begin(),\
    \ b.end());\n    k = min(k, (int)b.size());\n    return accumulate(b.begin(),\
    \ b.begin() + k, 0LL);\n}\n\ntemplate<bool Largest>\nll brute_kth(const vector<ll>&\
    \ a, int k) {\n    vector<ll> b = a;\n    sort(b.begin(), b.end());\n    if constexpr\
    \ (Largest) reverse(b.begin(), b.end());\n    return b[k - 1];\n}\n\ntemplate<bool\
    \ Largest>\nvoid verify_one(const vector<ll>& cur, const TopKTreap<ll, ll, Largest>&\
    \ ds) {\n    assert(ds.size() == (int)cur.size());\n    assert(ds.empty() == cur.empty());\n\
    \    assert(ds.total_sum() == accumulate(cur.begin(), cur.end(), 0LL));\n    for\
    \ (ll x = -8; x <= 8; ++x) {\n        int cnt = 0;\n        for (ll y : cur) cnt\
    \ += x == y;\n        assert(ds.count(x) == cnt);\n        assert(ds.contains(x)\
    \ == (cnt > 0));\n    }\n    for (int k = 0; k <= (int)cur.size() + 2; ++k) {\n\
    \        assert(ds.sum_k(k) == brute_sum_k<Largest>(cur, k));\n    }\n    if (!cur.empty())\
    \ {\n        for (int k = 1; k <= (int)cur.size(); ++k) {\n            assert(ds.kth(k)\
    \ == brute_kth<Largest>(cur, k));\n        }\n    }\n    if (ds.has_kth()) {\n\
    \        assert(ds.kth() == brute_kth<Largest>(cur, ds.k()));\n    } else {\n\
    \        assert(ds.k() <= 0 || ds.k() > (int)cur.size());\n    }\n    assert(ds.sum_topk()\
    \ == brute_sum_k<Largest>(cur, ds.k()));\n}\n\nvoid self_check() {\n    mt19937\
    \ rng(0);\n    for (int tc = 0; tc < 300; ++tc) {\n        TopKTreap<ll, ll, true>\
    \ largest(0, rng());\n        TopKTreap<ll, ll, false> smallest(0, rng());\n \
    \       largest.reserve(256);\n        smallest.reserve(256);\n        vector<ll>\
    \ cur;\n\n        for (int step = 0; step < 200; ++step) {\n            int op\
    \ = rng() % 4;\n            if (op <= 1) {\n                ll x = (int)(rng()\
    \ % 17) - 8;\n                largest.insert(x);\n                smallest.insert(x);\n\
    \                cur.push_back(x);\n            } else if (op == 2) {\n      \
    \          ll x = (int)(rng() % 17) - 8;\n                bool ok1 = largest.erase_one(x);\n\
    \                bool ok2 = smallest.erase_one(x);\n                auto it =\
    \ find(cur.begin(), cur.end(), x);\n                bool ok3 = it != cur.end();\n\
    \                if (ok3) cur.erase(it);\n                assert(ok1 == ok2);\n\
    \                assert(ok2 == ok3);\n            } else {\n                int\
    \ new_k = rng() % 12;\n                largest.set_k(new_k);\n               \
    \ smallest.set_k(new_k);\n            }\n            verify_one<true>(cur, largest);\n\
    \            verify_one<false>(cur, smallest);\n        }\n    }\n}\n\nint main()\
    \ {\n    self_check();\n\n    Scanner sc;\n    Printer pr;\n    ll a, b;\n   \
    \ sc.read(a, b);\n    pr.println(a + b);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/top_kth.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_top_kth.test.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_top_kth.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_top_kth.test.cpp
- /verify/test/yosupo_aplusb_top_kth.test.cpp.html
title: test/yosupo_aplusb_top_kth.test.cpp
---
