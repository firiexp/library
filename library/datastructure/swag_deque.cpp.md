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


# :warning: datastructure/swag_deque.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/swag_deque.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class G>
class TwoStackDeque {
    using T = typename G::T;
    vector<T> l, r, lsum, rsum;
public:
    TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}

    void push_front(const T& v){
        lsum.push_back(G::f(lsum.back(), v));
        l.push_back(v);
    }

    void push_back(const T& v){
        rsum.push_back(G::f(v, rsum.back()));
        r.push_back(v);
    }

    void pop_front(){
        if(l.empty()){
            if(r.empty()) r.pop_back();
            int lsize = (r.size() + 1) / 2, rsize = r.size() - lsize;
            l.resize(lsize); lsum.resize(lsize + 1);
            for (int i = 0; i < lsize; ++i) l[i] = r[lsize - i - 1], lsum[i+1] = G::f(l[i], lsum[i]);
            for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize], rsum[i+1] = G::f(rsum[i], r[i]);
            r.resize(rsize); rsum.resize(rsize + 1);
        }
        l.pop_back(); lsum.pop_back();
    }

    void pop_back(){
        if(r.empty()){
            if(l.empty()) l.pop_back();
            int rsize = (l.size() + 1) / 2, lsize = l.size() - rsize;
            r.resize(rsize); rsum.resize(rsize + 1);
            for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1], rsum[i+1] = G::f(rsum[i], r[i]);
            for (int i = 0; i < lsize; ++i) l[i] = l[i + rsize], lsum[i+1] = G::f(l[i], lsum[i]);
            l.resize(lsize); lsum.resize(lsize + 1);
        }
        r.pop_back(); rsum.pop_back();
    }

    T fold(){
        return G::f(lsum.back(), rsum.back());
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
#line 1 "datastructure/swag_deque.cpp"
template<class G>
class TwoStackDeque {
    using T = typename G::T;
    vector<T> l, r, lsum, rsum;
public:
    TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}

    void push_front(const T& v){
        lsum.push_back(G::f(lsum.back(), v));
        l.push_back(v);
    }

    void push_back(const T& v){
        rsum.push_back(G::f(v, rsum.back()));
        r.push_back(v);
    }

    void pop_front(){
        if(l.empty()){
            if(r.empty()) r.pop_back();
            int lsize = (r.size() + 1) / 2, rsize = r.size() - lsize;
            l.resize(lsize); lsum.resize(lsize + 1);
            for (int i = 0; i < lsize; ++i) l[i] = r[lsize - i - 1], lsum[i+1] = G::f(l[i], lsum[i]);
            for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize], rsum[i+1] = G::f(rsum[i], r[i]);
            r.resize(rsize); rsum.resize(rsize + 1);
        }
        l.pop_back(); lsum.pop_back();
    }

    void pop_back(){
        if(r.empty()){
            if(l.empty()) l.pop_back();
            int rsize = (l.size() + 1) / 2, lsize = l.size() - rsize;
            r.resize(rsize); rsum.resize(rsize + 1);
            for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1], rsum[i+1] = G::f(rsum[i], r[i]);
            for (int i = 0; i < lsize; ++i) l[i] = l[i + rsize], lsum[i+1] = G::f(l[i], lsum[i]);
            l.resize(lsize); lsum.resize(lsize + 1);
        }
        r.pop_back(); rsum.pop_back();
    }

    T fold(){
        return G::f(lsum.back(), rsum.back());
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

