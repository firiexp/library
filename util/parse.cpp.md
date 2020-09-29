---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/parse.cpp\"\nusing state = string::const_iterator;\n\
    \ \nint num(state &cur);\nint factor(state &cur);\nint muldiv(state &cur);\nint\
    \ addsub(state &cur);\nint expr(state &cur);\n \nint factor(state &cur) {\n  \
    \  if(isdigit(*cur)) return num(cur);\n    cur++;\n    int ans = addsub(cur);\n\
    \    cur++;\n    return ans;\n}\n \nint num(state &cur) {\n    int ans = *cur\
    \ -'0';\n    while(isdigit(*++cur)) ans = ans*10 + (*cur-'0');\n    return ans;\n\
    }\n \nint muldiv(state &cur) {\n    int ans = factor(cur);\n    while(true){\n\
    \        if(*cur == '*'){\n            cur++;\n            ans *= factor(cur);\n\
    \        }else if(*cur == '/'){\n            cur++;\n            ans /= factor(cur);\n\
    \        }else break;\n    }\n    return ans;\n}\n \nint addsub(state &cur){\n\
    \    int ans = muldiv(cur);\n    while(true){\n        if(*cur == '+'){\n    \
    \        cur++;\n            ans += muldiv(cur);\n        }else if(*cur == '-'){\n\
    \            cur++;\n            ans -= muldiv(cur);\n        }else break;\n \
    \   }\n    return ans;\n}\n \nint expr(state &cur){\n    return addsub(cur);\n\
    }\n"
  code: "using state = string::const_iterator;\n \nint num(state &cur);\nint factor(state\
    \ &cur);\nint muldiv(state &cur);\nint addsub(state &cur);\nint expr(state &cur);\n\
    \ \nint factor(state &cur) {\n    if(isdigit(*cur)) return num(cur);\n    cur++;\n\
    \    int ans = addsub(cur);\n    cur++;\n    return ans;\n}\n \nint num(state\
    \ &cur) {\n    int ans = *cur -'0';\n    while(isdigit(*++cur)) ans = ans*10 +\
    \ (*cur-'0');\n    return ans;\n}\n \nint muldiv(state &cur) {\n    int ans =\
    \ factor(cur);\n    while(true){\n        if(*cur == '*'){\n            cur++;\n\
    \            ans *= factor(cur);\n        }else if(*cur == '/'){\n           \
    \ cur++;\n            ans /= factor(cur);\n        }else break;\n    }\n    return\
    \ ans;\n}\n \nint addsub(state &cur){\n    int ans = muldiv(cur);\n    while(true){\n\
    \        if(*cur == '+'){\n            cur++;\n            ans += muldiv(cur);\n\
    \        }else if(*cur == '-'){\n            cur++;\n            ans -= muldiv(cur);\n\
    \        }else break;\n    }\n    return ans;\n}\n \nint expr(state &cur){\n \
    \   return addsub(cur);\n}"
  dependsOn: []
  isVerificationFile: false
  path: util/parse.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/parse.cpp
layout: document
redirect_from:
- /library/util/parse.cpp
- /library/util/parse.cpp.html
title: util/parse.cpp
---
