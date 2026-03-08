---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.cpp
    title: math/stern_brocot_tree.cpp
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/stern_brocot_tree
    links:
    - https://judge.yosupo.jp/problem/stern_brocot_tree
  bundledCode: "#line 1 \"test/yosupo_stern_brocot_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n#line 1 \"util/fastio.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    using namespace std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n  \
    \  constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline char skip() {\n\
    \        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n          \
    \  ++idx;\n            ensure();\n        }\n        return buf[idx++];\n    }\n\
    \n    template<class T, typename enable_if<is_integral<T>::value, int>::type =\
    \ 0>\n    void read(T &x) {\n        char c = skip();\n        bool neg = false;\n\
    \        if constexpr (is_signed<T>::value) {\n            if (c == '-') {\n \
    \               neg = true;\n                c = buf[idx++];\n            }\n\
    \        }\n        x = 0;\n        while (c >= '0') {\n            x = x * 10\
    \ + (c & 15);\n            c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (buf[idx] > ' ') ++idx;\n            s.append(buf + start,\
    \ idx - start);\n            if (buf[idx] <= ' ') break;\n            load();\n\
    \        }\n        ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n    \
    \    if (idx) {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n\
    \        }\n    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE -\
    \ OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n    inline void write_range(const\
    \ char *s, size_t n) {\n        size_t pos = 0;\n        while (pos < n) {\n \
    \           if (idx == BUFSIZE) flush();\n            size_t chunk = min(n - pos,\
    \ (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s + pos, chunk);\n\
    \            idx += (int)chunk;\n            pos += chunk;\n        }\n    }\n\
    \n    void write(const char *s) {\n        write_range(s, strlen(s));\n    }\n\
    \n    void write(const string &s) {\n        write_range(s.data(), s.size());\n\
    \    }\n\n    void write(char c) {\n        pc(c);\n    }\n\n    void write(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void write(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
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
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T>\n    void writeln(const T\
    \ &x) {\n        write(x);\n        pc('\\n');\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void writeln(const Head &head, const Tail &...tail) {\n\
    \        write(head);\n        ((pc(' '), write(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n#line 1 \"\
    math/stern_brocot_tree.cpp\"\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\nusing namespace std;\n\nnamespace SternBrocotTree {\n\nusing ll =\
    \ long long;\n\nenum Direction {\n    Left,\n    Right\n};\n\nstruct Move {\n\
    \    Direction dir;\n    ll steps;\n};\n\nstruct Node {\n    ll p, q, r, s;\n\n\
    \    Node() : p(0), q(1), r(1), s(0) {}\n    Node(ll p, ll q, ll r, ll s) : p(p),\
    \ q(q), r(r), s(s) {}\n\n    ll num() const { return p + r; }\n    ll den() const\
    \ { return q + s; }\n};\n\nNode apply(Node node, Move move) {\n    if (move.steps\
    \ == 0) return node;\n    if (move.dir == Left) {\n        node.r += node.p *\
    \ move.steps;\n        node.s += node.q * move.steps;\n    } else {\n        node.p\
    \ += node.r * move.steps;\n        node.q += node.s * move.steps;\n    }\n   \
    \ return node;\n}\n\nNode decode_path(const vector<Move>& path) {\n    Node node;\n\
    \    for (auto move : path) node = apply(node, move);\n    return node;\n}\n\n\
    vector<Move> encode_path(ll a, ll b) {\n    assert(a > 0 && b > 0);\n    vector<Move>\
    \ path;\n    while (a != b) {\n        if (a < b) {\n            ll steps = (b\
    \ - 1) / a;\n            path.push_back({Left, steps});\n            b -= steps\
    \ * a;\n        } else {\n            ll steps = (a - 1) / b;\n            path.push_back({Right,\
    \ steps});\n            a -= steps * b;\n        }\n    }\n    return path;\n\
    }\n\nll depth(const vector<Move>& path) {\n    ll ret = 0;\n    for (auto move\
    \ : path) ret += move.steps;\n    return ret;\n}\n\nvector<Move> lca_path(const\
    \ vector<Move>& a, const vector<Move>& b) {\n    vector<Move> ret;\n    int i\
    \ = 0, j = 0;\n    ll sa = 0, sb = 0;\n    while (i < (int)a.size() && j < (int)b.size())\
    \ {\n        if (sa == 0) sa = a[i].steps;\n        if (sb == 0) sb = b[j].steps;\n\
    \        if (a[i].dir != b[j].dir) break;\n        ll steps = min(sa, sb);\n \
    \       ret.push_back({a[i].dir, steps});\n        sa -= steps;\n        sb -=\
    \ steps;\n        if (sa == 0) ++i;\n        if (sb == 0) ++j;\n    }\n    return\
    \ ret;\n}\n\nvector<Move> ancestor_path(const vector<Move>& path, ll k) {\n  \
    \  vector<Move> ret;\n    for (auto move : path) {\n        if (k == 0) break;\n\
    \        ll steps = min(move.steps, k);\n        ret.push_back({move.dir, steps});\n\
    \        k -= steps;\n    }\n    if (k != 0) return {};\n    return ret;\n}\n\n\
    Node range(ll a, ll b) {\n    return decode_path(encode_path(a, b));\n}\n\nNode\
    \ lca(ll a, ll b, ll c, ll d) {\n    return decode_path(lca_path(encode_path(a,\
    \ b), encode_path(c, d)));\n}\n\n}  // namespace SternBrocotTree\n#line 5 \"test/yosupo_stern_brocot_tree.test.cpp\"\
    \n\nint main() {\n    using namespace SternBrocotTree;\n\n    Scanner sc;\n  \
    \  Printer pr;\n    int q;\n    sc.read(q);\n    while (q--) {\n        string\
    \ op;\n        sc.read(op);\n        if (op == \"ENCODE_PATH\") {\n          \
    \  ll a, b;\n            sc.read(a, b);\n            auto path = encode_path(a,\
    \ b);\n            pr.write((int)path.size());\n            for (auto move : path)\
    \ {\n                pr.write(' ');\n                pr.write(move.dir == Left\
    \ ? 'L' : 'R');\n                pr.write(' ');\n                pr.write(move.steps);\n\
    \            }\n            pr.writeln();\n        } else if (op == \"DECODE_PATH\"\
    ) {\n            int k;\n            sc.read(k);\n            vector<Move> path(k);\n\
    \            for (int i = 0; i < k; ++i) {\n                char c;\n        \
    \        ll steps;\n                sc.read(c, steps);\n                path[i]\
    \ = {c == 'L' ? Left : Right, steps};\n            }\n            auto node =\
    \ decode_path(path);\n            pr.writeln(node.num(), node.den());\n      \
    \  } else if (op == \"LCA\") {\n            ll a, b, c, d;\n            sc.read(a,\
    \ b, c, d);\n            auto node = lca(a, b, c, d);\n            pr.writeln(node.num(),\
    \ node.den());\n        } else if (op == \"ANCESTOR\") {\n            ll k, a,\
    \ b;\n            sc.read(k, a, b);\n            auto path = encode_path(a, b);\n\
    \            if (k > depth(path)) {\n                pr.writeln(-1);\n       \
    \         continue;\n            }\n            auto node = decode_path(ancestor_path(path,\
    \ k));\n            pr.writeln(node.num(), node.den());\n        } else {\n  \
    \          ll a, b;\n            sc.read(a, b);\n            auto node = range(a,\
    \ b);\n            pr.writeln(node.p, node.q, node.r, node.s);\n        }\n  \
    \  }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n\
    #include \"../util/fastio.cpp\"\n#include \"../math/stern_brocot_tree.cpp\"\n\n\
    int main() {\n    using namespace SternBrocotTree;\n\n    Scanner sc;\n    Printer\
    \ pr;\n    int q;\n    sc.read(q);\n    while (q--) {\n        string op;\n  \
    \      sc.read(op);\n        if (op == \"ENCODE_PATH\") {\n            ll a, b;\n\
    \            sc.read(a, b);\n            auto path = encode_path(a, b);\n    \
    \        pr.write((int)path.size());\n            for (auto move : path) {\n \
    \               pr.write(' ');\n                pr.write(move.dir == Left ? 'L'\
    \ : 'R');\n                pr.write(' ');\n                pr.write(move.steps);\n\
    \            }\n            pr.writeln();\n        } else if (op == \"DECODE_PATH\"\
    ) {\n            int k;\n            sc.read(k);\n            vector<Move> path(k);\n\
    \            for (int i = 0; i < k; ++i) {\n                char c;\n        \
    \        ll steps;\n                sc.read(c, steps);\n                path[i]\
    \ = {c == 'L' ? Left : Right, steps};\n            }\n            auto node =\
    \ decode_path(path);\n            pr.writeln(node.num(), node.den());\n      \
    \  } else if (op == \"LCA\") {\n            ll a, b, c, d;\n            sc.read(a,\
    \ b, c, d);\n            auto node = lca(a, b, c, d);\n            pr.writeln(node.num(),\
    \ node.den());\n        } else if (op == \"ANCESTOR\") {\n            ll k, a,\
    \ b;\n            sc.read(k, a, b);\n            auto path = encode_path(a, b);\n\
    \            if (k > depth(path)) {\n                pr.writeln(-1);\n       \
    \         continue;\n            }\n            auto node = decode_path(ancestor_path(path,\
    \ k));\n            pr.writeln(node.num(), node.den());\n        } else {\n  \
    \          ll a, b;\n            sc.read(a, b);\n            auto node = range(a,\
    \ b);\n            pr.writeln(node.p, node.q, node.r, node.s);\n        }\n  \
    \  }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/stern_brocot_tree.cpp
  isVerificationFile: true
  path: test/yosupo_stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:57:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_stern_brocot_tree.test.cpp
- /verify/test/yosupo_stern_brocot_tree.test.cpp.html
title: test/yosupo_stern_brocot_tree.test.cpp
---
