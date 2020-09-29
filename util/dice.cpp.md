---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/dice.cpp\"\nstruct dice {\n    int u, d, l, r, f, b;\n\
    \ \n    void spinl(){ // f -> l\n        int tmp = f; f = r; r = b; b = l; l =\
    \ tmp;\n    }\n    void spinr(){\n        for (int i = 0; i < 3; ++i) spinl();\n\
    \    }\n \n    void gof(){\n        int tmp = f; f = u; u = b; b = d; d = tmp;\n\
    \    }\n \n    void gob(){\n        for (int i = 0; i < 3; ++i) gof();\n    }\n\
    \ \n    void gor(){\n        int tmp = u; u = l; l = d; d = r; r = tmp;\n    }\n\
    \ \n    void gol(){\n        for (int i = 0; i < 3; ++i) gor();\n    }\n \n  \
    \  dice(int a, int x) {\n        u = 1, d = 6, f = 2, b = 5, l = 4, r = 3;\n \
    \       if(a == 2) gob();\n        else if(a == 3) gol();\n        else if(a ==\
    \ 4) gor();\n        else if(a == 5) gof();\n        else if(a == 6) gof(), gof();\n\
    \        while(f != x) spinl();\n    }\n};\n"
  code: "struct dice {\n    int u, d, l, r, f, b;\n \n    void spinl(){ // f -> l\n\
    \        int tmp = f; f = r; r = b; b = l; l = tmp;\n    }\n    void spinr(){\n\
    \        for (int i = 0; i < 3; ++i) spinl();\n    }\n \n    void gof(){\n   \
    \     int tmp = f; f = u; u = b; b = d; d = tmp;\n    }\n \n    void gob(){\n\
    \        for (int i = 0; i < 3; ++i) gof();\n    }\n \n    void gor(){\n     \
    \   int tmp = u; u = l; l = d; d = r; r = tmp;\n    }\n \n    void gol(){\n  \
    \      for (int i = 0; i < 3; ++i) gor();\n    }\n \n    dice(int a, int x) {\n\
    \        u = 1, d = 6, f = 2, b = 5, l = 4, r = 3;\n        if(a == 2) gob();\n\
    \        else if(a == 3) gol();\n        else if(a == 4) gor();\n        else\
    \ if(a == 5) gof();\n        else if(a == 6) gof(), gof();\n        while(f !=\
    \ x) spinl();\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: util/dice.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/dice.cpp
layout: document
redirect_from:
- /library/util/dice.cpp
- /library/util/dice.cpp.html
title: util/dice.cpp
---
