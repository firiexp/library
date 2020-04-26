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


# :warning: library/swag.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/swag.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class G>
class SWAG {
    using T = typename G::T;
    vector<T> in, out, insum, outsum;
public:
    SWAG() : in(0), out(0), insum(1, G::e()), outsum(1, G::e()) {}

    void push(const T& v){
        insum.push_back(G::f(insum.back(), v));
        in.push_back(v);
    }

    void pop(){
        if(out.empty()){
            do {
                out.emplace_back(in.back());
                outsum.emplace_back(G::f(in.back(), outsum.back()));
                in.pop_back(); insum.pop_back();
            }while(!in.empty());
        }
        out.pop_back(); outsum.pop_back();
    }

    T fold(){
        return G::f(outsum.back(), insum.back());
    }
};

struct Monoid {
    using T = int;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/swag.cpp"
template<class G>
class SWAG {
    using T = typename G::T;
    vector<T> in, out, insum, outsum;
public:
    SWAG() : in(0), out(0), insum(1, G::e()), outsum(1, G::e()) {}

    void push(const T& v){
        insum.push_back(G::f(insum.back(), v));
        in.push_back(v);
    }

    void pop(){
        if(out.empty()){
            do {
                out.emplace_back(in.back());
                outsum.emplace_back(G::f(in.back(), outsum.back()));
                in.pop_back(); insum.pop_back();
            }while(!in.empty());
        }
        out.pop_back(); outsum.pop_back();
    }

    T fold(){
        return G::f(outsum.back(), insum.back());
    }
};

struct Monoid {
    using T = int;
    static T f(T a, T b) { return a+b; }
    static T e() { return 0; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

