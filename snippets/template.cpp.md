---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"snippets/template.cpp\"\n#include <bits/stdc++.h>\nusing\
    \ namespace std; \nstatic const int MOD=998244353;\ntemplate<class T> constexpr\
    \ T INF=::numeric_limits<T>::max()/32*15+208;\nusing ll=long long; using uint=unsigned;\
    \ using ull=unsigned long long;\n\ntemplate<class T> using PQ=priority_queue<T,vector<T>,greater<T>>;\n\
    template<class T> using GPQ=priority_queue<T,vector<T>,greater<T>>;\nconstexpr\
    \ int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};\nconstexpr int dx8[8]={1,1,0,-1,-1,-1,0,1},dy8[8]={0,1,1,1,0,-1,-1,-1};\n\
    template<class T> T ifloor(T x,T y){return x/y-(x%y?(x<0)^(y<0):0);}\ntemplate<class\
    \ T> T iceil(T x,T y){return x/y+(x%y?(x>=0)^(y<0):0);}\ntemplate<class T> bool\
    \ chmax(T&a,T b){return a<b?(a=b,1):0;}\ntemplate<class T> bool chmin(T&a,T b){return\
    \ a>b?(a=b,1):0;}\ntemplate<class T> int lowerb(const vector<T>&a,const T&x){return\
    \ lower_bound(a.begin(),a.end(),x)-a.begin();}\ntemplate<class T> int upperb(const\
    \ vector<T>&a,const T&x){return upper_bound(a.begin(),a.end(),x)-a.begin();}\n\
    template<class T> void uniq(vector<T>&a){sort(a.begin(),a.end()); a.erase(unique(a.begin(),a.end()),a.end());}\n\
    \ntemplate<class T>\nvector<pair<T, int>> RLE(const vector<T> &a){\n    vector<pair<T,\
    \ int>> p; if(a.empty()) return p;\n    p.emplace_back(a[0], 1);\n    for (int\
    \ j = 1; j < (int)a.size(); ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n\
    \        else p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\nextern \"C\"\
    \ int fileno(FILE*),isatty(int); template<class T,class=void> struct R:false_type{};\n\
    template<class T> struct R<T,void_t<decltype(declval<T&>().begin()),decltype(declval<T&>().end())>>:true_type{};\n\
    template<class T> using I=enable_if_t<is_integral_v<T>,int>;\ntemplate<class T>\
    \ using N=enable_if_t<is_integral_v<T>&& !is_same_v<T,bool>,int>;\ntemplate<class\
    \ T> using G=enable_if_t<R<T>::value&&!is_same_v<decay_t<T>,string>,int>;\nstruct\
    \ Dtab{ char d[40000]; constexpr Dtab():d(){for(int i=0;i<10000;++i) for(int x=i,j=3;j>=0;--j)\
    \ d[i*4+j]=char('0'+x%10),x/=10;} }; \nstruct Scanner{ static constexpr int B=1<<17,O=64;\
    \ char a[B+1]; int p=0,n=0; bool t=isatty(fileno(stdin));\n    void l(){int k=n-p;\
    \ memmove(a,a+p,k); n=k+(t?(fgets(a+k,B+1-k,stdin)?(int)strlen(a+k):0):(int)fread(a+k,1,B-k,stdin));\
    \ p=0,a[n]=0;}\n    void g(){if(t?p==n:p+O>n) l();} char s(){g(); while(a[p]&&a[p]<='\
    \ ') ++p,g(); return a[p++]; }\n    template<class T,I<T> = 0> void read(T&x){\
    \ char c=s(); bool m=0; if constexpr(is_signed_v<T>) if(c=='-') m=1,g(),c=a[p++];\
    \ x=0; \n        while(c>='0') x=x*10+(c&15),g(),c=a[p++]; if constexpr(is_signed_v<T>)\
    \ if(m) x=-x; } \n    template<class H,class N,class... T> void read(H&h,N&nx,T&...t){read(h),read(nx,t...);}\n\
    \    template<class T,class U> void read(pair<T,U>&p){read(p.first,p.second);}\n\
    \    template<class T,G<T> = 0> void read(T&v){for(auto&x:v) read(x);} void read(char&c){c=s();}\n\
    \    void read(string&s){ s.clear(),g(); while(a[p]&&a[p]<=' ') ++p,g();  \n \
    \       while(1){int j=p; while(p<n&&a[p]>' ') ++p; s.append(a+j,p-j); if(p<n)\
    \ return void(++p); l(); if(!n) return;}\n    }\n} din; struct Printer{\n    static\
    \ constexpr int B=1<<17,O=64; char a[B]; int p=0; bool y=isatty(fileno(stdout));\
    \ inline static constexpr Dtab d{};\n    ~Printer(){f();} void f(){if(p) fwrite(a,1,p,stdout),p=0;}\
    \ void c(char x){if(p>B-O) f(); a[p++]=x; if(y&&x=='\\n') f();}\n    void write(const\
    \ char*s,size_t n){ for(size_t i=0;i<n;){if(p==B) f(); size_t m=min(n-i,(size_t)(B-p));\
    \ memcpy(a+p,s+i,m); p+=(int)m,i+=m;}\n    } void write(const char*s){write(s,strlen(s));}\
    \ void write(const string&s){write(s.data(),s.size());}\n    void write(char x){c(x);}\
    \ void write(bool x){c(char('0'+x));}\n    template<class T,N<T> = 0> void write(T\
    \ x){\n        if(p>B-100) f(); using U=make_unsigned_t<T>; U y; \n        if\
    \ constexpr(is_signed_v<T>) { if(x<0) a[p++]='-',y=U(0)-(U)x; else y=(U)x; } else\
    \ y=x;\n        if(!y) return void(a[p++]='0'); static constexpr int M=sizeof(U)*10/4;\
    \ char s[M]; int i=M;\n        while(y>=10000) i-=4,memcpy(s+i,d.d+(y%10000)*4,4),y/=10000;\n\
    \        if(y>=1000) memcpy(a+p,d.d+(y<<2),4),p+=4; else if(y>=100) memcpy(a+p,d.d+(y<<2)+1,3),p+=3;\n\
    \        else if(y>=10){unsigned q=(unsigned(y)*205)>>11; a[p]=char('0'+q); a[p+1]=char('0'+(unsigned(y)-q*10));\
    \ p+=2;}\n        else a[p++]=char('0'+y); memcpy(a+p,s+i,M-i),p+=M-i;\n    }\
    \ template<class T,G<T> = 0> void write(const T&v){bool f=0; for(auto&&x:v){if(f)\
    \ c(' '); f=1; write(x);}}\n    template<class T> void writeln(const T&x){write(x),c('\\\
    n');}\n    template<class H,class... T> void writeln(const H&h,const T&...t){write(h),((c('\
    \ '),write(t)),...),c('\\n');}\n    void writeln(){c('\\n');}} dout;\ntemplate<class\
    \ T> Scanner&operator>>(Scanner&in,T&x){in.read(x);return in;}\ntemplate<class\
    \ T> Printer&operator<<(Printer&out,const T&x){out.write(x);return out;} \n\n\
    int main(){\n    return 0;\n}\n"
  code: "#include <bits/stdc++.h>\nusing namespace std; \nstatic const int MOD=998244353;\n\
    template<class T> constexpr T INF=::numeric_limits<T>::max()/32*15+208;\nusing\
    \ ll=long long; using uint=unsigned; using ull=unsigned long long;\n\ntemplate<class\
    \ T> using PQ=priority_queue<T,vector<T>,greater<T>>;\ntemplate<class T> using\
    \ GPQ=priority_queue<T,vector<T>,greater<T>>;\nconstexpr int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};\n\
    constexpr int dx8[8]={1,1,0,-1,-1,-1,0,1},dy8[8]={0,1,1,1,0,-1,-1,-1};\ntemplate<class\
    \ T> T ifloor(T x,T y){return x/y-(x%y?(x<0)^(y<0):0);}\ntemplate<class T> T iceil(T\
    \ x,T y){return x/y+(x%y?(x>=0)^(y<0):0);}\ntemplate<class T> bool chmax(T&a,T\
    \ b){return a<b?(a=b,1):0;}\ntemplate<class T> bool chmin(T&a,T b){return a>b?(a=b,1):0;}\n\
    template<class T> int lowerb(const vector<T>&a,const T&x){return lower_bound(a.begin(),a.end(),x)-a.begin();}\n\
    template<class T> int upperb(const vector<T>&a,const T&x){return upper_bound(a.begin(),a.end(),x)-a.begin();}\n\
    template<class T> void uniq(vector<T>&a){sort(a.begin(),a.end()); a.erase(unique(a.begin(),a.end()),a.end());}\n\
    \ntemplate<class T>\nvector<pair<T, int>> RLE(const vector<T> &a){\n    vector<pair<T,\
    \ int>> p; if(a.empty()) return p;\n    p.emplace_back(a[0], 1);\n    for (int\
    \ j = 1; j < (int)a.size(); ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n\
    \        else p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\nextern \"C\"\
    \ int fileno(FILE*),isatty(int); template<class T,class=void> struct R:false_type{};\n\
    template<class T> struct R<T,void_t<decltype(declval<T&>().begin()),decltype(declval<T&>().end())>>:true_type{};\n\
    template<class T> using I=enable_if_t<is_integral_v<T>,int>;\ntemplate<class T>\
    \ using N=enable_if_t<is_integral_v<T>&& !is_same_v<T,bool>,int>;\ntemplate<class\
    \ T> using G=enable_if_t<R<T>::value&&!is_same_v<decay_t<T>,string>,int>;\nstruct\
    \ Dtab{ char d[40000]; constexpr Dtab():d(){for(int i=0;i<10000;++i) for(int x=i,j=3;j>=0;--j)\
    \ d[i*4+j]=char('0'+x%10),x/=10;} }; \nstruct Scanner{ static constexpr int B=1<<17,O=64;\
    \ char a[B+1]; int p=0,n=0; bool t=isatty(fileno(stdin));\n    void l(){int k=n-p;\
    \ memmove(a,a+p,k); n=k+(t?(fgets(a+k,B+1-k,stdin)?(int)strlen(a+k):0):(int)fread(a+k,1,B-k,stdin));\
    \ p=0,a[n]=0;}\n    void g(){if(t?p==n:p+O>n) l();} char s(){g(); while(a[p]&&a[p]<='\
    \ ') ++p,g(); return a[p++]; }\n    template<class T,I<T> = 0> void read(T&x){\
    \ char c=s(); bool m=0; if constexpr(is_signed_v<T>) if(c=='-') m=1,g(),c=a[p++];\
    \ x=0; \n        while(c>='0') x=x*10+(c&15),g(),c=a[p++]; if constexpr(is_signed_v<T>)\
    \ if(m) x=-x; } \n    template<class H,class N,class... T> void read(H&h,N&nx,T&...t){read(h),read(nx,t...);}\n\
    \    template<class T,class U> void read(pair<T,U>&p){read(p.first,p.second);}\n\
    \    template<class T,G<T> = 0> void read(T&v){for(auto&x:v) read(x);} void read(char&c){c=s();}\n\
    \    void read(string&s){ s.clear(),g(); while(a[p]&&a[p]<=' ') ++p,g();  \n \
    \       while(1){int j=p; while(p<n&&a[p]>' ') ++p; s.append(a+j,p-j); if(p<n)\
    \ return void(++p); l(); if(!n) return;}\n    }\n} din; struct Printer{\n    static\
    \ constexpr int B=1<<17,O=64; char a[B]; int p=0; bool y=isatty(fileno(stdout));\
    \ inline static constexpr Dtab d{};\n    ~Printer(){f();} void f(){if(p) fwrite(a,1,p,stdout),p=0;}\
    \ void c(char x){if(p>B-O) f(); a[p++]=x; if(y&&x=='\\n') f();}\n    void write(const\
    \ char*s,size_t n){ for(size_t i=0;i<n;){if(p==B) f(); size_t m=min(n-i,(size_t)(B-p));\
    \ memcpy(a+p,s+i,m); p+=(int)m,i+=m;}\n    } void write(const char*s){write(s,strlen(s));}\
    \ void write(const string&s){write(s.data(),s.size());}\n    void write(char x){c(x);}\
    \ void write(bool x){c(char('0'+x));}\n    template<class T,N<T> = 0> void write(T\
    \ x){\n        if(p>B-100) f(); using U=make_unsigned_t<T>; U y; \n        if\
    \ constexpr(is_signed_v<T>) { if(x<0) a[p++]='-',y=U(0)-(U)x; else y=(U)x; } else\
    \ y=x;\n        if(!y) return void(a[p++]='0'); static constexpr int M=sizeof(U)*10/4;\
    \ char s[M]; int i=M;\n        while(y>=10000) i-=4,memcpy(s+i,d.d+(y%10000)*4,4),y/=10000;\n\
    \        if(y>=1000) memcpy(a+p,d.d+(y<<2),4),p+=4; else if(y>=100) memcpy(a+p,d.d+(y<<2)+1,3),p+=3;\n\
    \        else if(y>=10){unsigned q=(unsigned(y)*205)>>11; a[p]=char('0'+q); a[p+1]=char('0'+(unsigned(y)-q*10));\
    \ p+=2;}\n        else a[p++]=char('0'+y); memcpy(a+p,s+i,M-i),p+=M-i;\n    }\
    \ template<class T,G<T> = 0> void write(const T&v){bool f=0; for(auto&&x:v){if(f)\
    \ c(' '); f=1; write(x);}}\n    template<class T> void writeln(const T&x){write(x),c('\\\
    n');}\n    template<class H,class... T> void writeln(const H&h,const T&...t){write(h),((c('\
    \ '),write(t)),...),c('\\n');}\n    void writeln(){c('\\n');}} dout;\ntemplate<class\
    \ T> Scanner&operator>>(Scanner&in,T&x){in.read(x);return in;}\ntemplate<class\
    \ T> Printer&operator<<(Printer&out,const T&x){out.write(x);return out;} \n\n\
    int main(){\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: snippets/template.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: snippets/template.cpp
layout: document
redirect_from:
- /library/snippets/template.cpp
- /library/snippets/template.cpp.html
title: snippets/template.cpp
---
