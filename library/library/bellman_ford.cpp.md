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


# :warning: library/bellman_ford.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/bellman_ford.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct edge {
    int from, to;
    T cost;

    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}

    explicit operator int() const {return to;}
};

template <typename T>
vector<T> bellman_ford(int s, int V,vector<edge<T> > &G){
    const T INF = numeric_limits<T>::max();
    vector<T> d(V, INF);
    d[s] = 0;
    for (int i = 0; i < V - 1; ++i) {
        for (auto &&e : G) {
            if (d[e.from] == INF) continue;
            d[e.to] = min(d[e.to], d[e.from] + e.cost);
        }
    }
    for (auto &&e : G) {
        if(d[e.from] == INF) continue;
        if(d[e.from] + e.cost < d[e.to]) return vector<T> ();
    }
    return d;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/bellman_ford.cpp"
template <typename T>
struct edge {
    int from, to;
    T cost;

    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}

    explicit operator int() const {return to;}
};

template <typename T>
vector<T> bellman_ford(int s, int V,vector<edge<T> > &G){
    const T INF = numeric_limits<T>::max();
    vector<T> d(V, INF);
    d[s] = 0;
    for (int i = 0; i < V - 1; ++i) {
        for (auto &&e : G) {
            if (d[e.from] == INF) continue;
            d[e.to] = min(d[e.to], d[e.from] + e.cost);
        }
    }
    for (auto &&e : G) {
        if(d[e.from] == INF) continue;
        if(d[e.from] + e.cost < d[e.to]) return vector<T> ();
    }
    return d;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

