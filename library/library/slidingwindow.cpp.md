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


# :warning: library/slidingwindow.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/slidingwindow.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, class F>
class sliding_window {
    vector<T> v;
    deque<T> Q;
    F f;
public:
    int l, r;
    explicit sliding_window(vector<T> &v, F f) : v(v), f(f), l(0), r(0) {};
    void set(vector<T> &u){
        v = u;
        Q.clear();
        l = 0; r = 0;
    }
    void reset(){
        Q.clear();
        l = 0, r = 0;
    }
    void slideL(){
        if(Q.front() == l++) Q.pop_front();
    }
    void slideR(){
        while(!Q.empty() && !f(v[Q.back()], v[r])) Q.pop_back();
        Q.push_back(r++);
    }
    T get_index()  {
        if(l == r) return 0;
        return Q.front();
    }
    T value()  {
        if(l == r) return 0;
        return v[Q.front()];
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/slidingwindow.cpp"
template<class T, class F>
class sliding_window {
    vector<T> v;
    deque<T> Q;
    F f;
public:
    int l, r;
    explicit sliding_window(vector<T> &v, F f) : v(v), f(f), l(0), r(0) {};
    void set(vector<T> &u){
        v = u;
        Q.clear();
        l = 0; r = 0;
    }
    void reset(){
        Q.clear();
        l = 0, r = 0;
    }
    void slideL(){
        if(Q.front() == l++) Q.pop_front();
    }
    void slideR(){
        while(!Q.empty() && !f(v[Q.back()], v[r])) Q.pop_back();
        Q.push_back(r++);
    }
    T get_index()  {
        if(l == r) return 0;
        return Q.front();
    }
    T value()  {
        if(l == r) return 0;
        return v[Q.front()];
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

