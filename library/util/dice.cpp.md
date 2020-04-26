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


# :warning: util/dice.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05c7e24700502a079cdd88012b5a76d3">util</a>
* <a href="{{ site.github.repository_url }}/blob/master/util/dice.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct dice {
    int u, d, l, r, f, b;
 
    void spinl(){ // f -> l
        int tmp = f; f = r; r = b; b = l; l = tmp;
    }
    void spinr(){
        for (int i = 0; i < 3; ++i) spinl();
    }
 
    void gof(){
        int tmp = f; f = u; u = b; b = d; d = tmp;
    }
 
    void gob(){
        for (int i = 0; i < 3; ++i) gof();
    }
 
    void gor(){
        int tmp = u; u = l; l = d; d = r; r = tmp;
    }
 
    void gol(){
        for (int i = 0; i < 3; ++i) gor();
    }
 
    dice(int a, int x) {
        u = 1, d = 6, f = 2, b = 5, l = 4, r = 3;
        if(a == 2) gob();
        else if(a == 3) gol();
        else if(a == 4) gor();
        else if(a == 5) gof();
        else if(a == 6) gof(), gof();
        while(f != x) spinl();
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "util/dice.cpp"
struct dice {
    int u, d, l, r, f, b;
 
    void spinl(){ // f -> l
        int tmp = f; f = r; r = b; b = l; l = tmp;
    }
    void spinr(){
        for (int i = 0; i < 3; ++i) spinl();
    }
 
    void gof(){
        int tmp = f; f = u; u = b; b = d; d = tmp;
    }
 
    void gob(){
        for (int i = 0; i < 3; ++i) gof();
    }
 
    void gor(){
        int tmp = u; u = l; l = d; d = r; r = tmp;
    }
 
    void gol(){
        for (int i = 0; i < 3; ++i) gor();
    }
 
    dice(int a, int x) {
        u = 1, d = 6, f = 2, b = 5, l = 4, r = 3;
        if(a == 2) gob();
        else if(a == 3) gol();
        else if(a == 4) gor();
        else if(a == 5) gof();
        else if(a == 6) gof(), gof();
        while(f != x) spinl();
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

