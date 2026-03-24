---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.cpp
    title: Suffix Automaton
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"test/yosupo_number_of_substrings_suffix_automaton.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"string/suffix_automaton.cpp\"\
    \ntemplate<int W, char start = 'a'>\nstruct SuffixAutomaton {\n    struct Node\
    \ {\n        int link;\n        int len;\n        int occ;\n        int next[W];\n\
    \        Node(int link = -1, int len = 0, int occ = 0): link(link), len(len),\
    \ occ(occ) {\n            fill(next, next + W, -1);\n        }\n    };\n\n   \
    \ vector<Node> nodes;\n    int last;\n\n    SuffixAutomaton(): nodes(1), last(0)\
    \ {}\n\n    template<class Container>\n    explicit SuffixAutomaton(const Container\
    \ &s): SuffixAutomaton() {\n        reserve(s.size());\n        for (auto &&c\
    \ : s) add(c);\n    }\n\n    void reserve(int n) {\n        nodes.reserve(2 *\
    \ n + 1);\n    }\n\n    static int ord(char c) {\n        return c - start;\n\
    \    }\n\n    int add(char c) {\n        int k = ord(c);\n        int cur = nodes.size();\n\
    \        nodes.emplace_back(0, nodes[last].len + 1, 1);\n        int p = last;\n\
    \        while (p != -1 && nodes[p].next[k] == -1) {\n            nodes[p].next[k]\
    \ = cur;\n            p = nodes[p].link;\n        }\n        if (p == -1) {\n\
    \            nodes[cur].link = 0;\n            last = cur;\n            return\
    \ cur;\n        }\n        int q = nodes[p].next[k];\n        if (nodes[p].len\
    \ + 1 == nodes[q].len) {\n            nodes[cur].link = q;\n            last =\
    \ cur;\n            return cur;\n        }\n        int clone = nodes.size();\n\
    \        nodes.push_back(nodes[q]);\n        nodes[clone].len = nodes[p].len +\
    \ 1;\n        nodes[clone].occ = 0;\n        while (p != -1 && nodes[p].next[k]\
    \ == q) {\n            nodes[p].next[k] = clone;\n            p = nodes[p].link;\n\
    \        }\n        nodes[q].link = nodes[cur].link = clone;\n        last = cur;\n\
    \        return cur;\n    }\n\n    template<class Container>\n    void build(const\
    \ Container &s) {\n        reserve(s.size());\n        for (auto &&c : s) add(c);\n\
    \    }\n\n    long long count_distinct_substrings() const {\n        long long\
    \ res = 0;\n        for (int i = 1; i < (int)nodes.size(); ++i) {\n          \
    \  res += nodes[i].len - nodes[nodes[i].link].len;\n        }\n        return\
    \ res;\n    }\n\n    vector<int> order_by_length() const {\n        int max_len\
    \ = 0;\n        for (auto &&node : nodes) max_len = max(max_len, node.len);\n\
    \        vector<int> cnt(max_len + 1);\n        for (auto &&node : nodes) cnt[node.len]++;\n\
    \        for (int i = 1; i <= max_len; ++i) cnt[i] += cnt[i - 1];\n        vector<int>\
    \ ord(nodes.size());\n        for (int i = (int)nodes.size() - 1; i >= 0; --i)\
    \ {\n            ord[--cnt[nodes[i].len]] = i;\n        }\n        return ord;\n\
    \    }\n\n    vector<int> substring_occurrences() const {\n        auto cnt =\
    \ nodes;\n        auto ord = order_by_length();\n        for (int i = (int)ord.size()\
    \ - 1; i >= 1; --i) {\n            int v = ord[i];\n            cnt[cnt[v].link].occ\
    \ += cnt[v].occ;\n        }\n        vector<int> res(nodes.size());\n        for\
    \ (int i = 0; i < (int)nodes.size(); ++i) res[i] = cnt[i].occ;\n        return\
    \ res;\n    }\n};\n/**\n * @brief Suffix Automaton\n */\n#line 21 \"test/yosupo_number_of_substrings_suffix_automaton.test.cpp\"\
    \n\nint main() {\n    string s;\n    cin >> s;\n    SuffixAutomaton<26> sam(s);\n\
    \    cout << sam.count_distinct_substrings() << \"\\n\";\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    #include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include\
    \ <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\
    \nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../string/suffix_automaton.cpp\"\
    \n\nint main() {\n    string s;\n    cin >> s;\n    SuffixAutomaton<26> sam(s);\n\
    \    cout << sam.count_distinct_substrings() << \"\\n\";\n    return 0;\n}\n"
  dependsOn:
  - string/suffix_automaton.cpp
  isVerificationFile: true
  path: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_number_of_substrings_suffix_automaton.test.cpp
- /verify/test/yosupo_number_of_substrings_suffix_automaton.test.cpp.html
title: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
---
