---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: util/parse.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05c7e24700502a079cdd88012b5a76d3">util</a>
* <a href="{{ site.github.repository_url }}/blob/master/util/parse.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
using state = string::const_iterator;
 
int num(state &cur);
int factor(state &cur);
int muldiv(state &cur);
int addsub(state &cur);
int expr(state &cur);
 
int factor(state &cur) {
    if(isdigit(*cur)) return num(cur);
    cur++;
    int ans = addsub(cur);
    cur++;
    return ans;
}
 
int num(state &cur) {
    int ans = *cur -'0';
    while(isdigit(*++cur)) ans = ans*10 + (*cur-'0');
    return ans;
}
 
int muldiv(state &cur) {
    int ans = factor(cur);
    while(true){
        if(*cur == '*'){
            cur++;
            ans *= factor(cur);
        }else if(*cur == '/'){
            cur++;
            ans /= factor(cur);
        }else break;
    }
    return ans;
}
 
int addsub(state &cur){
    int ans = muldiv(cur);
    while(true){
        if(*cur == '+'){
            cur++;
            ans += muldiv(cur);
        }else if(*cur == '-'){
            cur++;
            ans -= muldiv(cur);
        }else break;
    }
    return ans;
}
 
int expr(state &cur){
    return addsub(cur);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "util/parse.cpp"
using state = string::const_iterator;
 
int num(state &cur);
int factor(state &cur);
int muldiv(state &cur);
int addsub(state &cur);
int expr(state &cur);
 
int factor(state &cur) {
    if(isdigit(*cur)) return num(cur);
    cur++;
    int ans = addsub(cur);
    cur++;
    return ans;
}
 
int num(state &cur) {
    int ans = *cur -'0';
    while(isdigit(*++cur)) ans = ans*10 + (*cur-'0');
    return ans;
}
 
int muldiv(state &cur) {
    int ans = factor(cur);
    while(true){
        if(*cur == '*'){
            cur++;
            ans *= factor(cur);
        }else if(*cur == '/'){
            cur++;
            ans /= factor(cur);
        }else break;
    }
    return ans;
}
 
int addsub(state &cur){
    int ans = muldiv(cur);
    while(true){
        if(*cur == '+'){
            cur++;
            ans += muldiv(cur);
        }else if(*cur == '-'){
            cur++;
            ans -= muldiv(cur);
        }else break;
    }
    return ans;
}
 
int expr(state &cur){
    return addsub(cur);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

