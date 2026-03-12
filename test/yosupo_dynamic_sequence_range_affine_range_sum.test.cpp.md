---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/implicit_treap.cpp
    title: Implicit Treap
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <random>\n\
    #include <string>\n#include <tuple>\n#include <utility>\n#include <vector>\nusing\
    \ namespace std;\n\nstatic const int MOD = 998244353;\nusing ll = long long;\n\
    using uint = unsigned;\nusing ull = unsigned long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#line 21 \"test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\
    \nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
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
    \ 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint M>\nstruct modint {\n    uint val;\n\
    public:\n    static modint raw(int v) { modint x; x.val = v; return x; }\n   \
    \ static constexpr uint get_mod() { return M; }\n    modint() : val(0) {}\n  \
    \  template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x\
    \ += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % M);\
    \ }\n    modint& operator++() { val++; if (val == M) val = 0; return *this; }\n\
    \    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n  \
    \  modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -=\
    \ M; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % M); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(M-2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 1 \"datastructure/implicit_treap.cpp\"\ntemplate <class M>\n\
    struct ImplicitTreap {\n    using T = typename M::T;\n    using L = typename M::L;\n\
    \n    struct Node {\n        int l, r, sz;\n        unsigned pri;\n        bool\
    \ rev, has_lazy;\n        T val, sum, rsum;\n        L lazy;\n\n        Node(unsigned\
    \ pri, const T &val)\n            : l(-1), r(-1), sz(1), pri(pri), rev(false),\
    \ has_lazy(false),\n              val(val), sum(val), rsum(val), lazy(M::l())\
    \ {}\n    };\n\n    int root;\n    vector<Node> nodes;\n    vector<int> free_nodes;\n\
    \    unsigned long long rng_state;\n\n    ImplicitTreap() : root(-1), rng_state(0x123456789abcdef0ull)\
    \ {}\n\n    explicit ImplicitTreap(const vector<T> &v) : ImplicitTreap() {\n \
    \       reserve((int)v.size());\n        build_linear(v);\n    }\n\n    int size()\
    \ const {\n        return subtree_size(root);\n    }\n\n    bool empty() const\
    \ {\n        return root == -1;\n    }\n\n    void reserve(int capacity) {\n \
    \       nodes.reserve(capacity);\n        free_nodes.reserve(capacity);\n    }\n\
    \n    T all_fold() const {\n        return root == -1 ? M::e() : nodes[root].sum;\n\
    \    }\n\n    void insert(int k, const T &x) {\n        auto [a, b] = split(root,\
    \ k);\n        root = merge(merge(a, new_node(x)), b);\n    }\n\n    void push_front(const\
    \ T &x) {\n        insert(0, x);\n    }\n\n    void push_back(const T &x) {\n\
    \        insert(size(), x);\n    }\n\n    T erase(int k) {\n        auto [a, bc]\
    \ = split(root, k);\n        auto [b, c] = split(bc, 1);\n        T res = nodes[b].val;\n\
    \        recycle_node(b);\n        root = merge(a, c);\n        return res;\n\
    \    }\n\n    T pop_front() {\n        return erase(0);\n    }\n\n    T pop_back()\
    \ {\n        return erase(size() - 1);\n    }\n\n    T get(int k) {\n        auto\
    \ [a, bc] = split(root, k);\n        auto [b, c] = split(bc, 1);\n        T res\
    \ = nodes[b].val;\n        root = merge(merge(a, b), c);\n        return res;\n\
    \    }\n\n    void set(int k, const T &x) {\n        auto [a, bc] = split(root,\
    \ k);\n        auto [b, c] = split(bc, 1);\n        nodes[b].val = x;\n      \
    \  nodes[b].sum = x;\n        nodes[b].rsum = x;\n        nodes[b].rev = false;\n\
    \        nodes[b].has_lazy = false;\n        nodes[b].lazy = M::l();\n       \
    \ pull(b);\n        root = merge(merge(a, b), c);\n    }\n\n    void apply(int\
    \ l, int r, const L &x) {\n        auto [a, b, c] = split3(root, l, r);\n    \
    \    apply_node(b, x);\n        root = merge(merge(a, b), c);\n    }\n\n    void\
    \ reverse(int l, int r) {\n        auto [a, b, c] = split3(root, l, r);\n    \
    \    toggle(b);\n        root = merge(merge(a, b), c);\n    }\n\n    T fold(int\
    \ l, int r) {\n        auto [a, b, c] = split3(root, l, r);\n        T res = b\
    \ == -1 ? M::e() : nodes[b].sum;\n        root = merge(merge(a, b), c);\n    \
    \    return res;\n    }\n\nprivate:\n    int subtree_size(int x) const {\n   \
    \     return x == -1 ? 0 : nodes[x].sz;\n    }\n\n    unsigned next_rand() {\n\
    \        rng_state ^= rng_state << 7;\n        rng_state ^= rng_state >> 9;\n\
    \        return static_cast<unsigned>(rng_state);\n    }\n\n    int new_node(const\
    \ T &x) {\n        unsigned pri = next_rand();\n        if (!free_nodes.empty())\
    \ {\n            int idx = free_nodes.back();\n            free_nodes.pop_back();\n\
    \            nodes[idx] = Node(pri, x);\n            return idx;\n        }\n\
    \        nodes.emplace_back(pri, x);\n        return (int)nodes.size() - 1;\n\
    \    }\n\n    void recycle_node(int x) {\n        if (x != -1) free_nodes.push_back(x);\n\
    \    }\n\n    void build_linear(const vector<T> &v) {\n        if (v.empty())\
    \ return;\n        vector<int> ids(v.size());\n        for (int i = 0; i < (int)v.size();\
    \ ++i) ids[i] = new_node(v[i]);\n\n        vector<int> st;\n        st.reserve(v.size());\n\
    \        for (int cur : ids) {\n            int last = -1;\n            while\
    \ (!st.empty() && nodes[st.back()].pri > nodes[cur].pri) {\n                last\
    \ = st.back();\n                st.pop_back();\n            }\n            nodes[cur].l\
    \ = last;\n            if (!st.empty()) nodes[st.back()].r = cur;\n          \
    \  st.push_back(cur);\n        }\n        root = st.front();\n\n        vector<int>\
    \ ord;\n        ord.reserve(v.size());\n        st.assign(1, root);\n        while\
    \ (!st.empty()) {\n            int x = st.back();\n            st.pop_back();\n\
    \            ord.push_back(x);\n            if (nodes[x].l != -1) st.push_back(nodes[x].l);\n\
    \            if (nodes[x].r != -1) st.push_back(nodes[x].r);\n        }\n    \
    \    for (int i = (int)ord.size() - 1; i >= 0; --i) pull(ord[i]);\n    }\n\n \
    \   void apply_node(int x, const L &lazy) {\n        if (x == -1) return;\n  \
    \      nodes[x].val = M::g(nodes[x].val, lazy);\n        nodes[x].sum = M::g(nodes[x].sum,\
    \ lazy);\n        nodes[x].rsum = M::g(nodes[x].rsum, lazy);\n        if (nodes[x].has_lazy)\
    \ nodes[x].lazy = M::h(nodes[x].lazy, lazy);\n        else {\n            nodes[x].lazy\
    \ = lazy;\n            nodes[x].has_lazy = true;\n        }\n    }\n\n    void\
    \ toggle(int x) {\n        if (x == -1) return;\n        swap(nodes[x].l, nodes[x].r);\n\
    \        swap(nodes[x].sum, nodes[x].rsum);\n        nodes[x].rev ^= 1;\n    }\n\
    \n    void push(int x) {\n        if (x == -1) return;\n        if (nodes[x].rev)\
    \ {\n            toggle(nodes[x].l);\n            toggle(nodes[x].r);\n      \
    \      nodes[x].rev = false;\n        }\n        if (nodes[x].has_lazy) {\n  \
    \          apply_node(nodes[x].l, nodes[x].lazy);\n            apply_node(nodes[x].r,\
    \ nodes[x].lazy);\n            nodes[x].has_lazy = false;\n            nodes[x].lazy\
    \ = M::l();\n        }\n    }\n\n    void pull(int x) {\n        nodes[x].sz =\
    \ 1;\n        nodes[x].sum = nodes[x].val;\n        nodes[x].rsum = nodes[x].val;\n\
    \        if (nodes[x].l != -1) {\n            int y = nodes[x].l;\n          \
    \  nodes[x].sz += nodes[y].sz;\n            nodes[x].sum = M::f(nodes[y].sum,\
    \ nodes[x].sum);\n            nodes[x].rsum = M::f(nodes[x].rsum, nodes[y].rsum);\n\
    \        }\n        if (nodes[x].r != -1) {\n            int y = nodes[x].r;\n\
    \            nodes[x].sz += nodes[y].sz;\n            nodes[x].sum = M::f(nodes[x].sum,\
    \ nodes[y].sum);\n            nodes[x].rsum = M::f(nodes[y].rsum, nodes[x].rsum);\n\
    \        }\n    }\n\n    int merge(int a, int b) {\n        if (a == -1 || b ==\
    \ -1) return a == -1 ? b : a;\n        if (nodes[a].pri < nodes[b].pri) {\n  \
    \          push(a);\n            nodes[a].r = merge(nodes[a].r, b);\n        \
    \    pull(a);\n            return a;\n        }\n        push(b);\n        nodes[b].l\
    \ = merge(a, nodes[b].l);\n        pull(b);\n        return b;\n    }\n\n    pair<int,\
    \ int> split(int x, int k) {\n        if (x == -1) return {-1, -1};\n        push(x);\n\
    \        if (k <= subtree_size(nodes[x].l)) {\n            auto [a, b] = split(nodes[x].l,\
    \ k);\n            nodes[x].l = b;\n            pull(x);\n            return {a,\
    \ x};\n        }\n        auto [a, b] = split(nodes[x].r, k - subtree_size(nodes[x].l)\
    \ - 1);\n        nodes[x].r = a;\n        pull(x);\n        return {x, b};\n \
    \   }\n\n    tuple<int, int, int> split3(int x, int l, int r) {\n        auto\
    \ [a, bc] = split(x, l);\n        auto [b, c] = split(bc, r - l);\n        return\
    \ {a, b, c};\n    }\n};\n\n/**\n * @brief Implicit Treap\n */\n#line 26 \"test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n\nstruct AffineSumMonoid {\n    using T = array<mint, 2>;\n    using L = array<mint,\
    \ 2>;\n    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }\n    static\
    \ T g(T a, L b) { return {a[0] * b[0] + a[1] * b[1], a[1]}; }\n    static L h(L\
    \ a, L b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return\
    \ {0, 0}; }\n    static L l() { return {1, 0}; }\n};\n\nstruct RangeAddSumMonoid\
    \ {\n    using T = array<ll, 2>;\n    using L = ll;\n    static T f(T a, T b)\
    \ { return {a[0] + b[0], a[1] + b[1]}; }\n    static T g(T a, L b) { return {a[0]\
    \ + a[1] * b, a[1]}; }\n    static L h(L a, L b) { return a + b; }\n    static\
    \ T e() { return {0, 0}; }\n    static L l() { return 0; }\n};\n\nstruct StringMonoid\
    \ {\n    using T = string;\n    using L = int;\n    static T f(const T &a, const\
    \ T &b) { return a + b; }\n    static T g(const T &a, L) { return a; }\n    static\
    \ L h(L, L) { return 0; }\n    static T e() { return \"\"; }\n    static L l()\
    \ { return 0; }\n};\n\nvoid self_check_sum() {\n    mt19937 rng(0);\n    for (int\
    \ tc = 0; tc < 200; ++tc) {\n        vector<ll> brute;\n        ImplicitTreap<RangeAddSumMonoid>\
    \ tr;\n        int init_n = rng() % 8;\n        for (int i = 0; i < init_n; ++i)\
    \ {\n            ll x = (int)(rng() % 21) - 10;\n            brute.push_back(x);\n\
    \            tr.push_back({x, 1});\n        }\n        for (int step = 0; step\
    \ < 200; ++step) {\n            int op = rng() % 7;\n            if (brute.empty())\
    \ op = 0;\n            if (op == 0) {\n                int pos = rng() % (brute.size()\
    \ + 1);\n                ll x = (int)(rng() % 21) - 10;\n                brute.insert(brute.begin()\
    \ + pos, x);\n                tr.insert(pos, {x, 1});\n            } else if (op\
    \ == 1) {\n                int pos = rng() % brute.size();\n                ll\
    \ got = tr.erase(pos)[0];\n                assert(got == brute[pos]);\n      \
    \          brute.erase(brute.begin() + pos);\n            } else if (op == 2)\
    \ {\n                int pos = rng() % brute.size();\n                ll x = (int)(rng()\
    \ % 21) - 10;\n                brute[pos] = x;\n                tr.set(pos, {x,\
    \ 1});\n            } else if (op == 3) {\n                int l = rng() % brute.size();\n\
    \                int r = rng() % brute.size();\n                if (l > r) swap(l,\
    \ r);\n                ++r;\n                ll add = (int)(rng() % 21) - 10;\n\
    \                for (int i = l; i < r; ++i) brute[i] += add;\n              \
    \  tr.apply(l, r, add);\n            } else if (op == 4) {\n                int\
    \ l = rng() % brute.size();\n                int r = rng() % brute.size();\n \
    \               if (l > r) swap(l, r);\n                ++r;\n               \
    \ reverse(brute.begin() + l, brute.begin() + r);\n                tr.reverse(l,\
    \ r);\n            } else if (op == 5) {\n                int l = rng() % brute.size();\n\
    \                int r = rng() % brute.size();\n                if (l > r) swap(l,\
    \ r);\n                ++r;\n                ll sum = 0;\n                for\
    \ (int i = l; i < r; ++i) sum += brute[i];\n                assert(tr.fold(l,\
    \ r)[0] == sum);\n            } else {\n                int pos = rng() % brute.size();\n\
    \                assert(tr.get(pos)[0] == brute[pos]);\n            }\n      \
    \      assert(tr.size() == (int)brute.size());\n            ll total = 0;\n  \
    \          for (ll x : brute) total += x;\n            assert(tr.all_fold()[0]\
    \ == total);\n        }\n    }\n}\n\nvoid self_check_order() {\n    mt19937 rng(1);\n\
    \    for (int tc = 0; tc < 200; ++tc) {\n        vector<string> brute;\n     \
    \   ImplicitTreap<StringMonoid> tr;\n        int init_n = rng() % 8;\n       \
    \ for (int i = 0; i < init_n; ++i) {\n            string s(1, char('a' + rng()\
    \ % 3));\n            brute.push_back(s);\n            tr.push_back(s);\n    \
    \    }\n        for (int step = 0; step < 200; ++step) {\n            int op =\
    \ rng() % 6;\n            if (brute.empty()) op = 0;\n            if (op == 0)\
    \ {\n                int pos = rng() % (brute.size() + 1);\n                string\
    \ s(1, char('a' + rng() % 3));\n                brute.insert(brute.begin() + pos,\
    \ s);\n                tr.insert(pos, s);\n            } else if (op == 1) {\n\
    \                int pos = rng() % brute.size();\n                assert(tr.erase(pos)\
    \ == brute[pos]);\n                brute.erase(brute.begin() + pos);\n       \
    \     } else if (op == 2) {\n                int pos = rng() % brute.size();\n\
    \                string s(1, char('a' + rng() % 3));\n                brute[pos]\
    \ = s;\n                tr.set(pos, s);\n            } else if (op == 3) {\n \
    \               int l = rng() % brute.size();\n                int r = rng() %\
    \ brute.size();\n                if (l > r) swap(l, r);\n                ++r;\n\
    \                reverse(brute.begin() + l, brute.begin() + r);\n            \
    \    tr.reverse(l, r);\n            } else if (op == 4) {\n                int\
    \ l = rng() % brute.size();\n                int r = rng() % brute.size();\n \
    \               if (l > r) swap(l, r);\n                ++r;\n               \
    \ string s;\n                for (int i = l; i < r; ++i) s += brute[i];\n    \
    \            assert(tr.fold(l, r) == s);\n            } else {\n             \
    \   int pos = rng() % brute.size();\n                assert(tr.get(pos) == brute[pos]);\n\
    \            }\n            string all;\n            for (const auto &s : brute)\
    \ all += s;\n            assert(tr.all_fold() == all);\n        }\n    }\n}\n\n\
    int main() {\n    self_check_sum();\n    self_check_order();\n\n    Scanner sc;\n\
    \    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<array<mint,\
    \ 2>> init(n);\n    for (int i = 0; i < n; ++i) {\n        int a;\n        sc.read(a);\n\
    \        init[i] = {a, 1};\n    }\n\n    ImplicitTreap<AffineSumMonoid> tr(init);\n\
    \    while (q--) {\n        int t;\n        sc.read(t);\n        if (t == 0) {\n\
    \            int pos, x;\n            sc.read(pos, x);\n            tr.insert(pos,\
    \ {x, 1});\n        } else if (t == 1) {\n            int pos;\n            sc.read(pos);\n\
    \            tr.erase(pos);\n        } else if (t == 2) {\n            int l,\
    \ r;\n            sc.read(l, r);\n            tr.reverse(l, r);\n        } else\
    \ if (t == 3) {\n            int l, r, b, c;\n            sc.read(l, r, b, c);\n\
    \            tr.apply(l, r, {b, c});\n        } else {\n            int l, r;\n\
    \            sc.read(l, r);\n            pr.writeln(tr.fold(l, r)[0].val);\n \
    \       }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <random>\n\
    #include <string>\n#include <tuple>\n#include <utility>\n#include <vector>\nusing\
    \ namespace std;\n\nstatic const int MOD = 998244353;\nusing ll = long long;\n\
    using uint = unsigned;\nusing ull = unsigned long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../util/modint.cpp\"\n#include \"../datastructure/implicit_treap.cpp\"\
    \n\nstruct AffineSumMonoid {\n    using T = array<mint, 2>;\n    using L = array<mint,\
    \ 2>;\n    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }\n    static\
    \ T g(T a, L b) { return {a[0] * b[0] + a[1] * b[1], a[1]}; }\n    static L h(L\
    \ a, L b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }\n    static T e() { return\
    \ {0, 0}; }\n    static L l() { return {1, 0}; }\n};\n\nstruct RangeAddSumMonoid\
    \ {\n    using T = array<ll, 2>;\n    using L = ll;\n    static T f(T a, T b)\
    \ { return {a[0] + b[0], a[1] + b[1]}; }\n    static T g(T a, L b) { return {a[0]\
    \ + a[1] * b, a[1]}; }\n    static L h(L a, L b) { return a + b; }\n    static\
    \ T e() { return {0, 0}; }\n    static L l() { return 0; }\n};\n\nstruct StringMonoid\
    \ {\n    using T = string;\n    using L = int;\n    static T f(const T &a, const\
    \ T &b) { return a + b; }\n    static T g(const T &a, L) { return a; }\n    static\
    \ L h(L, L) { return 0; }\n    static T e() { return \"\"; }\n    static L l()\
    \ { return 0; }\n};\n\nvoid self_check_sum() {\n    mt19937 rng(0);\n    for (int\
    \ tc = 0; tc < 200; ++tc) {\n        vector<ll> brute;\n        ImplicitTreap<RangeAddSumMonoid>\
    \ tr;\n        int init_n = rng() % 8;\n        for (int i = 0; i < init_n; ++i)\
    \ {\n            ll x = (int)(rng() % 21) - 10;\n            brute.push_back(x);\n\
    \            tr.push_back({x, 1});\n        }\n        for (int step = 0; step\
    \ < 200; ++step) {\n            int op = rng() % 7;\n            if (brute.empty())\
    \ op = 0;\n            if (op == 0) {\n                int pos = rng() % (brute.size()\
    \ + 1);\n                ll x = (int)(rng() % 21) - 10;\n                brute.insert(brute.begin()\
    \ + pos, x);\n                tr.insert(pos, {x, 1});\n            } else if (op\
    \ == 1) {\n                int pos = rng() % brute.size();\n                ll\
    \ got = tr.erase(pos)[0];\n                assert(got == brute[pos]);\n      \
    \          brute.erase(brute.begin() + pos);\n            } else if (op == 2)\
    \ {\n                int pos = rng() % brute.size();\n                ll x = (int)(rng()\
    \ % 21) - 10;\n                brute[pos] = x;\n                tr.set(pos, {x,\
    \ 1});\n            } else if (op == 3) {\n                int l = rng() % brute.size();\n\
    \                int r = rng() % brute.size();\n                if (l > r) swap(l,\
    \ r);\n                ++r;\n                ll add = (int)(rng() % 21) - 10;\n\
    \                for (int i = l; i < r; ++i) brute[i] += add;\n              \
    \  tr.apply(l, r, add);\n            } else if (op == 4) {\n                int\
    \ l = rng() % brute.size();\n                int r = rng() % brute.size();\n \
    \               if (l > r) swap(l, r);\n                ++r;\n               \
    \ reverse(brute.begin() + l, brute.begin() + r);\n                tr.reverse(l,\
    \ r);\n            } else if (op == 5) {\n                int l = rng() % brute.size();\n\
    \                int r = rng() % brute.size();\n                if (l > r) swap(l,\
    \ r);\n                ++r;\n                ll sum = 0;\n                for\
    \ (int i = l; i < r; ++i) sum += brute[i];\n                assert(tr.fold(l,\
    \ r)[0] == sum);\n            } else {\n                int pos = rng() % brute.size();\n\
    \                assert(tr.get(pos)[0] == brute[pos]);\n            }\n      \
    \      assert(tr.size() == (int)brute.size());\n            ll total = 0;\n  \
    \          for (ll x : brute) total += x;\n            assert(tr.all_fold()[0]\
    \ == total);\n        }\n    }\n}\n\nvoid self_check_order() {\n    mt19937 rng(1);\n\
    \    for (int tc = 0; tc < 200; ++tc) {\n        vector<string> brute;\n     \
    \   ImplicitTreap<StringMonoid> tr;\n        int init_n = rng() % 8;\n       \
    \ for (int i = 0; i < init_n; ++i) {\n            string s(1, char('a' + rng()\
    \ % 3));\n            brute.push_back(s);\n            tr.push_back(s);\n    \
    \    }\n        for (int step = 0; step < 200; ++step) {\n            int op =\
    \ rng() % 6;\n            if (brute.empty()) op = 0;\n            if (op == 0)\
    \ {\n                int pos = rng() % (brute.size() + 1);\n                string\
    \ s(1, char('a' + rng() % 3));\n                brute.insert(brute.begin() + pos,\
    \ s);\n                tr.insert(pos, s);\n            } else if (op == 1) {\n\
    \                int pos = rng() % brute.size();\n                assert(tr.erase(pos)\
    \ == brute[pos]);\n                brute.erase(brute.begin() + pos);\n       \
    \     } else if (op == 2) {\n                int pos = rng() % brute.size();\n\
    \                string s(1, char('a' + rng() % 3));\n                brute[pos]\
    \ = s;\n                tr.set(pos, s);\n            } else if (op == 3) {\n \
    \               int l = rng() % brute.size();\n                int r = rng() %\
    \ brute.size();\n                if (l > r) swap(l, r);\n                ++r;\n\
    \                reverse(brute.begin() + l, brute.begin() + r);\n            \
    \    tr.reverse(l, r);\n            } else if (op == 4) {\n                int\
    \ l = rng() % brute.size();\n                int r = rng() % brute.size();\n \
    \               if (l > r) swap(l, r);\n                ++r;\n               \
    \ string s;\n                for (int i = l; i < r; ++i) s += brute[i];\n    \
    \            assert(tr.fold(l, r) == s);\n            } else {\n             \
    \   int pos = rng() % brute.size();\n                assert(tr.get(pos) == brute[pos]);\n\
    \            }\n            string all;\n            for (const auto &s : brute)\
    \ all += s;\n            assert(tr.all_fold() == all);\n        }\n    }\n}\n\n\
    int main() {\n    self_check_sum();\n    self_check_order();\n\n    Scanner sc;\n\
    \    Printer pr;\n\n    int n, q;\n    sc.read(n, q);\n    vector<array<mint,\
    \ 2>> init(n);\n    for (int i = 0; i < n; ++i) {\n        int a;\n        sc.read(a);\n\
    \        init[i] = {a, 1};\n    }\n\n    ImplicitTreap<AffineSumMonoid> tr(init);\n\
    \    while (q--) {\n        int t;\n        sc.read(t);\n        if (t == 0) {\n\
    \            int pos, x;\n            sc.read(pos, x);\n            tr.insert(pos,\
    \ {x, 1});\n        } else if (t == 1) {\n            int pos;\n            sc.read(pos);\n\
    \            tr.erase(pos);\n        } else if (t == 2) {\n            int l,\
    \ r;\n            sc.read(l, r);\n            tr.reverse(l, r);\n        } else\
    \ if (t == 3) {\n            int l, r, b, c;\n            sc.read(l, r, b, c);\n\
    \            tr.apply(l, r, {b, c});\n        } else {\n            int l, r;\n\
    \            sc.read(l, r);\n            pr.writeln(tr.fold(l, r)[0].val);\n \
    \       }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - datastructure/implicit_treap.cpp
  isVerificationFile: true
  path: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2026-03-12 19:34:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
- /verify/test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp.html
title: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
---
