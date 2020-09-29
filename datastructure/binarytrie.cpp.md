---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/binarytrie.cpp\"\nstruct Node {\n    int val;\n\
    \    Node *nxt[2];\n    Node() : val(0), nxt{nullptr, nullptr} {}\n    static\
    \ int cnt;\n    void *operator new(size_t){\n        static Node pool[3000000];\n\
    \        return pool + cnt++;\n    }\n};\nint Node::cnt = 0;\n\ntemplate<class\
    \ T, size_t X>\nstruct Binarytrie {\n    Node *root;\n    Binarytrie() { root\
    \ = new Node; }\n\n    void add(const T b, T x = 1){\n        Node *p = root;\n\
    \        for (int i = X-1; i >= 0; --i) {\n            bool f = (b >> i) & 1;\n\
    \            if(!p->nxt[f]) p->nxt[f] = new Node;\n            p = p->nxt[f];\n\
    \        }\n        p->val += x;\n    }\n\n    T xor_min(Node* t, const T &x,\
    \ int dep = X-1){\n        if(dep < 0) return 0;\n        T f = (x >> dep) & 1U;\
    \ f ^= !t->nxt[f];\n        return xor_min(t->nxt[f], x, dep-1) | (f << dep);\n\
    \    }\n    T max_element(T x = 0) {\n        return xor_min(root, ~x);\n    }\n\
    \    T min_element(T x = 0){\n        return xor_min(root, x);\n    }\n};\n"
  code: "struct Node {\n    int val;\n    Node *nxt[2];\n    Node() : val(0), nxt{nullptr,\
    \ nullptr} {}\n    static int cnt;\n    void *operator new(size_t){\n        static\
    \ Node pool[3000000];\n        return pool + cnt++;\n    }\n};\nint Node::cnt\
    \ = 0;\n\ntemplate<class T, size_t X>\nstruct Binarytrie {\n    Node *root;\n\
    \    Binarytrie() { root = new Node; }\n\n    void add(const T b, T x = 1){\n\
    \        Node *p = root;\n        for (int i = X-1; i >= 0; --i) {\n         \
    \   bool f = (b >> i) & 1;\n            if(!p->nxt[f]) p->nxt[f] = new Node;\n\
    \            p = p->nxt[f];\n        }\n        p->val += x;\n    }\n\n    T xor_min(Node*\
    \ t, const T &x, int dep = X-1){\n        if(dep < 0) return 0;\n        T f =\
    \ (x >> dep) & 1U; f ^= !t->nxt[f];\n        return xor_min(t->nxt[f], x, dep-1)\
    \ | (f << dep);\n    }\n    T max_element(T x = 0) {\n        return xor_min(root,\
    \ ~x);\n    }\n    T min_element(T x = 0){\n        return xor_min(root, x);\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binarytrie.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/binarytrie.cpp
layout: document
redirect_from:
- /library/datastructure/binarytrie.cpp
- /library/datastructure/binarytrie.cpp.html
title: datastructure/binarytrie.cpp
---
