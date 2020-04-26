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


# :warning: library/mo.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/mo.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
const int B = 400;

struct Query {
    int l, r, no;
    Query(int l, int r, int no) : l(l), r(r), no(no) {}
    Query() : l(0), r(0), no(0) {}
    bool operator<(const Query &a) const {
        int ablock = this->l / B, bblock = a.l / B;
        if(ablock != bblock) return ablock < bblock;
        if(ablock & 1) return this->r < a.r;
        else return this->r > a.r;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/mo.cpp"
const int B = 400;

struct Query {
    int l, r, no;
    Query(int l, int r, int no) : l(l), r(r), no(no) {}
    Query() : l(0), r(0), no(0) {}
    bool operator<(const Query &a) const {
        int ablock = this->l / B, bblock = a.l / B;
        if(ablock != bblock) return ablock < bblock;
        if(ablock & 1) return this->r < a.r;
        else return this->r > a.r;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

