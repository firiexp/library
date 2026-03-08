---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':x:'
    path: util/parse.cpp
    title: "\u5F0F\u30D1\u30FC\u30B5(Parse)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_parse.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <cctype>\n#include\
    \ <random>\n#include <stack>\n#include <string>\n#include <vector>\nusing namespace\
    \ std;\n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n\
    #line 4 \"util/fastio.cpp\"\n#include <type_traits>\nusing namespace std;\n\n\
    struct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 1 \"util/parse.cpp\"\nusing state = string::const_iterator;\n \nint num(state\
    \ &cur);\nint factor(state &cur);\nint muldiv(state &cur);\nint addsub(state &cur);\n\
    int expr(state &cur);\n \nint factor(state &cur) {\n    if(isdigit(*cur)) return\
    \ num(cur);\n    cur++;\n    int ans = addsub(cur);\n    cur++;\n    return ans;\n\
    }\n \nint num(state &cur) {\n    int ans = *cur -'0';\n    while(isdigit(*++cur))\
    \ ans = ans*10 + (*cur-'0');\n    return ans;\n}\n \nint muldiv(state &cur) {\n\
    \    int ans = factor(cur);\n    while(true){\n        if(*cur == '*'){\n    \
    \        cur++;\n            ans *= factor(cur);\n        }else if(*cur == '/'){\n\
    \            cur++;\n            ans /= factor(cur);\n        }else break;\n \
    \   }\n    return ans;\n}\n \nint addsub(state &cur){\n    int ans = muldiv(cur);\n\
    \    while(true){\n        if(*cur == '+'){\n            cur++;\n            ans\
    \ += muldiv(cur);\n        }else if(*cur == '-'){\n            cur++;\n      \
    \      ans -= muldiv(cur);\n        }else break;\n    }\n    return ans;\n}\n\
    \ \nint expr(state &cur){\n    return addsub(cur);\n}\n\n/**\n * @brief \u5F0F\
    \u30D1\u30FC\u30B5(Parse)\n * @docs _md/parse.md\n */\n#line 12 \"test/yosupo_many_aplusb_parse.test.cpp\"\
    \n\nnamespace {\n\nint precedence(char op) {\n    if (op == '+' || op == '-')\
    \ return 1;\n    if (op == '*' || op == '/') return 2;\n    return -1;\n}\n\n\
    bool apply_top(stack<int> &values, stack<char> &ops) {\n    if (values.size()\
    \ < 2 || ops.empty()) return false;\n    int rhs = values.top();\n    values.pop();\n\
    \    int lhs = values.top();\n    values.pop();\n    char op = ops.top();\n  \
    \  ops.pop();\n    if (op == '+') values.push(lhs + rhs);\n    else if (op ==\
    \ '-') values.push(lhs - rhs);\n    else if (op == '*') values.push(lhs * rhs);\n\
    \    else {\n        if (rhs == 0) return false;\n        values.push(lhs / rhs);\n\
    \    }\n    return true;\n}\n\nbool eval_bruteforce(const string &s, int &res)\
    \ {\n    stack<int> values;\n    stack<char> ops;\n    int n = (int)s.size();\n\
    \    for (int i = 0; i < n; ) {\n        if (isdigit(s[i])) {\n            int\
    \ x = 0;\n            while (i < n && isdigit(s[i])) {\n                x = x\
    \ * 10 + (s[i] - '0');\n                ++i;\n            }\n            values.push(x);\n\
    \            continue;\n        }\n        if (s[i] == '(') {\n            ops.push(s[i]);\n\
    \            ++i;\n            continue;\n        }\n        if (s[i] == ')')\
    \ {\n            while (!ops.empty() && ops.top() != '(') {\n                if\
    \ (!apply_top(values, ops)) return false;\n            }\n            if (ops.empty()\
    \ || ops.top() != '(') return false;\n            ops.pop();\n            ++i;\n\
    \            continue;\n        }\n        while (!ops.empty() && precedence(ops.top())\
    \ >= precedence(s[i])) {\n            if (!apply_top(values, ops)) return false;\n\
    \        }\n        ops.push(s[i]);\n        ++i;\n    }\n    while (!ops.empty())\
    \ {\n        if (ops.top() == '(') return false;\n        if (!apply_top(values,\
    \ ops)) return false;\n    }\n    if (values.size() != 1) return false;\n    res\
    \ = values.top();\n    return true;\n}\n\nstring gen_expr(mt19937 &rng, int depth);\n\
    \nstring gen_number(mt19937 &rng) {\n    return to_string(uniform_int_distribution<int>(0,\
    \ 30)(rng));\n}\n\nstring gen_factor(mt19937 &rng, int depth) {\n    if (depth\
    \ == 0 || uniform_int_distribution<int>(0, 3)(rng) == 0) {\n        return gen_number(rng);\n\
    \    }\n    return \"(\" + gen_expr(rng, depth - 1) + \")\";\n}\n\nstring gen_muldiv(mt19937\
    \ &rng, int depth) {\n    int cnt = uniform_int_distribution<int>(1, 3)(rng);\n\
    \    string s = gen_factor(rng, depth);\n    for (int i = 1; i < cnt; ++i) {\n\
    \        char op = uniform_int_distribution<int>(0, 1)(rng) ? '*' : '/';\n   \
    \     s += op;\n        s += gen_factor(rng, depth);\n    }\n    return s;\n}\n\
    \nstring gen_expr(mt19937 &rng, int depth) {\n    int cnt = uniform_int_distribution<int>(1,\
    \ 3)(rng);\n    string s = gen_muldiv(rng, depth);\n    for (int i = 1; i < cnt;\
    \ ++i) {\n        char op = uniform_int_distribution<int>(0, 1)(rng) ? '+' : '-';\n\
    \        s += op;\n        s += gen_muldiv(rng, depth);\n    }\n    return s;\n\
    }\n\nbool check_parse(const string &s) {\n    int expected;\n    if (!eval_bruteforce(s,\
    \ expected)) return true;\n    string t = s;\n    t.push_back('\\0');\n    state\
    \ cur = t.begin();\n    int actual = expr(cur);\n    return actual == expected\
    \ && *cur == '\\0';\n}\n\n}  // namespace\n\nint main() {\n    {\n        mt19937\
    \ rng(123456789);\n        vector<string> samples = {\n            \"0\",\n  \
    \          \"1+2*3\",\n            \"(1+2)*3\",\n            \"8/3\",\n      \
    \      \"18/(2+1)\",\n            \"30-4*5+6\",\n            \"2*(3+(4*5))\",\n\
    \            \"24/(3*2)-7\"\n        };\n        for (const string &s : samples)\
    \ {\n            if (!check_parse(s)) return 1;\n        }\n        for (int depth\
    \ = 0; depth <= 4; ++depth) {\n            for (int trial = 0; trial < 600; ++trial)\
    \ {\n                string s = gen_expr(rng, depth);\n                if (!check_parse(s))\
    \ return 1;\n            }\n        }\n    }\n\n    Scanner sc;\n    Printer pr;\n\
    \    int t;\n    sc.read(t);\n    while (t--) {\n        long long a, b;\n   \
    \     sc.read(a, b);\n        pr.writeln(a + b);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <cctype>\n#include <random>\n#include <stack>\n#include <string>\n#include <vector>\n\
    using namespace std;\n\n#include \"../util/fastio.cpp\"\n#include \"../util/parse.cpp\"\
    \n\nnamespace {\n\nint precedence(char op) {\n    if (op == '+' || op == '-')\
    \ return 1;\n    if (op == '*' || op == '/') return 2;\n    return -1;\n}\n\n\
    bool apply_top(stack<int> &values, stack<char> &ops) {\n    if (values.size()\
    \ < 2 || ops.empty()) return false;\n    int rhs = values.top();\n    values.pop();\n\
    \    int lhs = values.top();\n    values.pop();\n    char op = ops.top();\n  \
    \  ops.pop();\n    if (op == '+') values.push(lhs + rhs);\n    else if (op ==\
    \ '-') values.push(lhs - rhs);\n    else if (op == '*') values.push(lhs * rhs);\n\
    \    else {\n        if (rhs == 0) return false;\n        values.push(lhs / rhs);\n\
    \    }\n    return true;\n}\n\nbool eval_bruteforce(const string &s, int &res)\
    \ {\n    stack<int> values;\n    stack<char> ops;\n    int n = (int)s.size();\n\
    \    for (int i = 0; i < n; ) {\n        if (isdigit(s[i])) {\n            int\
    \ x = 0;\n            while (i < n && isdigit(s[i])) {\n                x = x\
    \ * 10 + (s[i] - '0');\n                ++i;\n            }\n            values.push(x);\n\
    \            continue;\n        }\n        if (s[i] == '(') {\n            ops.push(s[i]);\n\
    \            ++i;\n            continue;\n        }\n        if (s[i] == ')')\
    \ {\n            while (!ops.empty() && ops.top() != '(') {\n                if\
    \ (!apply_top(values, ops)) return false;\n            }\n            if (ops.empty()\
    \ || ops.top() != '(') return false;\n            ops.pop();\n            ++i;\n\
    \            continue;\n        }\n        while (!ops.empty() && precedence(ops.top())\
    \ >= precedence(s[i])) {\n            if (!apply_top(values, ops)) return false;\n\
    \        }\n        ops.push(s[i]);\n        ++i;\n    }\n    while (!ops.empty())\
    \ {\n        if (ops.top() == '(') return false;\n        if (!apply_top(values,\
    \ ops)) return false;\n    }\n    if (values.size() != 1) return false;\n    res\
    \ = values.top();\n    return true;\n}\n\nstring gen_expr(mt19937 &rng, int depth);\n\
    \nstring gen_number(mt19937 &rng) {\n    return to_string(uniform_int_distribution<int>(0,\
    \ 30)(rng));\n}\n\nstring gen_factor(mt19937 &rng, int depth) {\n    if (depth\
    \ == 0 || uniform_int_distribution<int>(0, 3)(rng) == 0) {\n        return gen_number(rng);\n\
    \    }\n    return \"(\" + gen_expr(rng, depth - 1) + \")\";\n}\n\nstring gen_muldiv(mt19937\
    \ &rng, int depth) {\n    int cnt = uniform_int_distribution<int>(1, 3)(rng);\n\
    \    string s = gen_factor(rng, depth);\n    for (int i = 1; i < cnt; ++i) {\n\
    \        char op = uniform_int_distribution<int>(0, 1)(rng) ? '*' : '/';\n   \
    \     s += op;\n        s += gen_factor(rng, depth);\n    }\n    return s;\n}\n\
    \nstring gen_expr(mt19937 &rng, int depth) {\n    int cnt = uniform_int_distribution<int>(1,\
    \ 3)(rng);\n    string s = gen_muldiv(rng, depth);\n    for (int i = 1; i < cnt;\
    \ ++i) {\n        char op = uniform_int_distribution<int>(0, 1)(rng) ? '+' : '-';\n\
    \        s += op;\n        s += gen_muldiv(rng, depth);\n    }\n    return s;\n\
    }\n\nbool check_parse(const string &s) {\n    int expected;\n    if (!eval_bruteforce(s,\
    \ expected)) return true;\n    string t = s;\n    t.push_back('\\0');\n    state\
    \ cur = t.begin();\n    int actual = expr(cur);\n    return actual == expected\
    \ && *cur == '\\0';\n}\n\n}  // namespace\n\nint main() {\n    {\n        mt19937\
    \ rng(123456789);\n        vector<string> samples = {\n            \"0\",\n  \
    \          \"1+2*3\",\n            \"(1+2)*3\",\n            \"8/3\",\n      \
    \      \"18/(2+1)\",\n            \"30-4*5+6\",\n            \"2*(3+(4*5))\",\n\
    \            \"24/(3*2)-7\"\n        };\n        for (const string &s : samples)\
    \ {\n            if (!check_parse(s)) return 1;\n        }\n        for (int depth\
    \ = 0; depth <= 4; ++depth) {\n            for (int trial = 0; trial < 600; ++trial)\
    \ {\n                string s = gen_expr(rng, depth);\n                if (!check_parse(s))\
    \ return 1;\n            }\n        }\n    }\n\n    Scanner sc;\n    Printer pr;\n\
    \    int t;\n    sc.read(t);\n    while (t--) {\n        long long a, b;\n   \
    \     sc.read(a, b);\n        pr.writeln(a + b);\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/parse.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_parse.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_parse.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_parse.test.cpp
- /verify/test/yosupo_many_aplusb_parse.test.cpp.html
title: test/yosupo_many_aplusb_parse.test.cpp
---
