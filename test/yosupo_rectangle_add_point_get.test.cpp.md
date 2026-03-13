---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/rectangle_add_point_get.cpp
    title: "\u9577\u65B9\u5F62\u52A0\u7B97\u70B9\u53D6\u5F97(Rectangle Add Point Get)"
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
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_add_point_get
    links:
    - https://judge.yosupo.jp/problem/rectangle_add_point_get
  bundledCode: "#line 1 \"test/yosupo_rectangle_add_point_get.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/rectangle_add_point_get\"\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace\
    \ std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
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
    \ 1 \"datastructure/rectangle_add_point_get.cpp\"\nusing namespace std;\n\ntemplate<class\
    \ T>\nstruct RectangleAddPointGet {\n    struct Operation {\n        int type;\n\
    \        int l, d, r, u;\n        T w;\n    };\n\n    vector<Operation> ops;\n\
    \    vector<int> xs;\n\n    void add_rectangle(int l, int d, int r, int u, T w)\
    \ {\n        ops.push_back({0, l, d, r, u, w});\n        xs.push_back(l);\n  \
    \      xs.push_back(r);\n    }\n\n    void add_query(int x, int y) {\n       \
    \ ops.push_back({1, x, y, 0, 0, 0});\n    }\n\n    vector<T> solve() const {\n\
    \        struct RectInfo {\n            int start[4];\n        };\n        vector<int>\
    \ ord_x = xs;\n        ord_x.reserve(ord_x.size() + ops.size());\n        for\
    \ (auto &&op : ops) {\n            if (op.type == 1) ord_x.push_back(op.l);\n\
    \        }\n        sort(ord_x.begin(), ord_x.end());\n        ord_x.erase(unique(ord_x.begin(),\
    \ ord_x.end()), ord_x.end());\n\n        int m = (int)ord_x.size();\n        vector<int>\
    \ x_index_lower(ops.size());\n        vector<int> x_index_upper(ops.size());\n\
    \        for (int idx = 0; idx < (int)ops.size(); ++idx) {\n            x_index_lower[idx]\
    \ = (int)(lower_bound(ord_x.begin(), ord_x.end(), ops[idx].l) - ord_x.begin())\
    \ + 1;\n            if (ops[idx].type == 1) {\n                x_index_upper[idx]\
    \ = (int)(upper_bound(ord_x.begin(), ord_x.end(), ops[idx].l) - ord_x.begin());\n\
    \            } else {\n                x_index_upper[idx] = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), ops[idx].r) - ord_x.begin()) + 1;\n            }\n        }\n \
    \       vector<int> cnt(m + 1);\n        auto count_point = [&](int xi) {\n  \
    \          for (int i = xi; i <= m; i += i & -i) ++cnt[i];\n        };\n     \
    \   for (int idx = 0; idx < (int)ops.size(); ++idx) {\n            if (ops[idx].type\
    \ == 1) continue;\n            count_point(x_index_lower[idx]);\n            count_point(x_index_lower[idx]);\n\
    \            count_point(x_index_upper[idx]);\n            count_point(x_index_upper[idx]);\n\
    \        }\n        vector<vector<int>> ys(m + 1);\n        for (int i = 1; i\
    \ <= m; ++i) ys[i].reserve(cnt[i]);\n        auto reserve_point = [&](int xi,\
    \ int y) {\n            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);\n\
    \        };\n        for (int idx = 0; idx < (int)ops.size(); ++idx) {\n     \
    \       auto &&op = ops[idx];\n            if (op.type == 0) {\n             \
    \   reserve_point(x_index_lower[idx], op.d);\n                reserve_point(x_index_lower[idx],\
    \ op.u);\n                reserve_point(x_index_upper[idx], op.d);\n         \
    \       reserve_point(x_index_upper[idx], op.u);\n            }\n        }\n \
    \       for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(), ys[i].end());\n\
    \            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n \
    \       }\n\n        vector<int> offset(m + 2, 0);\n        for (int i = 1; i\
    \ <= m; ++i) offset[i + 1] = offset[i] + (int)ys[i].size();\n        vector<T>\
    \ bit(offset[m + 1], 0);\n        auto path_len_add = [&](int xi) {\n        \
    \    int len = 0;\n            for (int i = xi; i <= m; i += i & -i) ++len;\n\
    \            return len;\n        };\n        auto path_len_sum = [&](int xi)\
    \ {\n            int len = 0;\n            for (int i = xi; i > 0; i -= i & -i)\
    \ ++len;\n            return len;\n        };\n        vector<RectInfo> rect_info(ops.size());\n\
    \        vector<int> query_start(ops.size(), -1);\n        int total_add_visits\
    \ = 0, total_sum_visits = 0;\n        for (int idx = 0; idx < (int)ops.size();\
    \ ++idx) {\n            if (ops[idx].type == 0) {\n                total_add_visits\
    \ += path_len_add(x_index_lower[idx]) * 2;\n                total_add_visits +=\
    \ path_len_add(x_index_upper[idx]) * 2;\n            } else {\n              \
    \  total_sum_visits += path_len_sum(x_index_upper[idx]);\n            }\n    \
    \    }\n        vector<int> add_yi(total_add_visits);\n        vector<int> sum_yi(total_sum_visits);\n\
    \        int add_ptr = 0, sum_ptr = 0;\n        auto encode_add = [&](int xi,\
    \ int y) {\n            int start = add_ptr;\n            for (int i = xi; i <=\
    \ m; i += i & -i) {\n                add_yi[add_ptr++] = (int)(lower_bound(ys[i].begin(),\
    \ ys[i].end(), y) - ys[i].begin()) + 1;\n            }\n            return start;\n\
    \        };\n        auto encode_sum = [&](int xi, int y) {\n            int start\
    \ = sum_ptr;\n            for (int i = xi; i > 0; i -= i & -i) {\n           \
    \     sum_yi[sum_ptr++] = (int)(upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n\
    \            }\n            return start;\n        };\n        for (int idx =\
    \ 0; idx < (int)ops.size(); ++idx) {\n            auto &&op = ops[idx];\n    \
    \        if (op.type == 0) {\n                rect_info[idx].start[0] = encode_add(x_index_lower[idx],\
    \ op.d);\n                rect_info[idx].start[1] = encode_add(x_index_lower[idx],\
    \ op.u);\n                rect_info[idx].start[2] = encode_add(x_index_upper[idx],\
    \ op.d);\n                rect_info[idx].start[3] = encode_add(x_index_upper[idx],\
    \ op.u);\n            } else {\n                query_start[idx] = encode_sum(x_index_upper[idx],\
    \ op.d);\n            }\n        }\n\n        auto add_point = [&](int xi, int\
    \ start, T w) {\n            int ptr = start;\n            for (int i = xi; i\
    \ <= m; i += i & -i) {\n                int yi = add_yi[ptr++];\n            \
    \    int sz = (int)ys[i].size();\n                int base = offset[i];\n    \
    \            for (; yi <= sz; yi += yi & -yi) bit[base + yi - 1] += w;\n     \
    \       }\n        };\n        auto prefix_sum = [&](int xi, int start) {\n  \
    \          T ret = 0;\n            int ptr = start;\n            for (int i =\
    \ xi; i > 0; i -= i & -i) {\n                int yi = sum_yi[ptr++];\n       \
    \         int base = offset[i];\n                for (; yi > 0; yi -= yi & -yi)\
    \ ret += bit[base + yi - 1];\n            }\n            return ret;\n       \
    \ };\n\n        vector<T> ans;\n        for (int idx = 0; idx < (int)ops.size();\
    \ ++idx) {\n            auto &&op = ops[idx];\n            if (op.type == 0) {\n\
    \                add_point(x_index_lower[idx], rect_info[idx].start[0], op.w);\n\
    \                add_point(x_index_lower[idx], rect_info[idx].start[1], -op.w);\n\
    \                add_point(x_index_upper[idx], rect_info[idx].start[2], -op.w);\n\
    \                add_point(x_index_upper[idx], rect_info[idx].start[3], op.w);\n\
    \            } else {\n                ans.push_back(prefix_sum(x_index_upper[idx],\
    \ query_start[idx]));\n            }\n        }\n        return ans;\n    }\n\
    };\n\n/**\n * @brief \u9577\u65B9\u5F62\u52A0\u7B97\u70B9\u53D6\u5F97(Rectangle\
    \ Add Point Get)\n */\n#line 13 \"test/yosupo_rectangle_add_point_get.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n,\
    \ q);\n\n    RectangleAddPointGet<long long> solver;\n    for (int i = 0; i <\
    \ n; ++i) {\n        int l, d, r, u;\n        long long w;\n        sc.read(l,\
    \ d, r, u, w);\n        solver.add_rectangle(l, d, r, u, w);\n    }\n    for (int\
    \ i = 0; i < q; ++i) {\n        int t;\n        sc.read(t);\n        if (t ==\
    \ 0) {\n            int l, d, r, u;\n            long long w;\n            sc.read(l,\
    \ d, r, u, w);\n            solver.add_rectangle(l, d, r, u, w);\n        } else\
    \ {\n            int x, y;\n            sc.read(x, y);\n            solver.add_query(x,\
    \ y);\n        }\n    }\n\n    auto ans = solver.solve();\n    for (auto &&x :\
    \ ans) pr.writeln(x);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_add_point_get\"\
    \n\n#include <algorithm>\n#include <vector>\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/rectangle_add_point_get.cpp\"\n\nint main() {\n  \
    \  Scanner sc;\n    Printer pr;\n    int n, q;\n    sc.read(n, q);\n\n    RectangleAddPointGet<long\
    \ long> solver;\n    for (int i = 0; i < n; ++i) {\n        int l, d, r, u;\n\
    \        long long w;\n        sc.read(l, d, r, u, w);\n        solver.add_rectangle(l,\
    \ d, r, u, w);\n    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n   \
    \     sc.read(t);\n        if (t == 0) {\n            int l, d, r, u;\n      \
    \      long long w;\n            sc.read(l, d, r, u, w);\n            solver.add_rectangle(l,\
    \ d, r, u, w);\n        } else {\n            int x, y;\n            sc.read(x,\
    \ y);\n            solver.add_query(x, y);\n        }\n    }\n\n    auto ans =\
    \ solver.solve();\n    for (auto &&x : ans) pr.writeln(x);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/rectangle_add_point_get.cpp
  isVerificationFile: true
  path: test/yosupo_rectangle_add_point_get.test.cpp
  requiredBy: []
  timestamp: '2026-03-13 22:39:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_rectangle_add_point_get.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_rectangle_add_point_get.test.cpp
- /verify/test/yosupo_rectangle_add_point_get.test.cpp.html
title: test/yosupo_rectangle_add_point_get.test.cpp
---
