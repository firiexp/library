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


# :warning: library/bellman_ford_negative_loop.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/bellman_ford_negative_loop.cpp">View this file on GitHub</a>
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
vector<T> bellman_ford(int s, int N,vector<edge<T> > &G){
    vector<T> dist(N, INF<T>);
    vector<bool> negative(N);
    dist[s] = 0;
    for (int i = 0; i < N - 1; ++ i) {
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from]+ e.cost){
                dist[e.to] = dist[e.from]+ e.cost;
            }
        }
    }
 
    ll ans = dist[N - 1];
 
    for (int i = 0; i < N ; ++i) {
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from] + e.cost){
                dist[e.to] = dist[e.from] + e.cost;
                negative[e.to] = true;
            }
            if(negative[e.from]) negative[e.to] = true;
        }
    }
    for (int i = 0; i < N; ++i) {
        if(negative[i]) dist[i] = -INF<T>;
    }
    return dist;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/bellman_ford_negative_loop.cpp"
template <typename T>
struct edge {
    int from, to;
    T cost;
 
    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
 
    explicit operator int() const {return to;}
};
 
template <typename T>
vector<T> bellman_ford(int s, int N,vector<edge<T> > &G){
    vector<T> dist(N, INF<T>);
    vector<bool> negative(N);
    dist[s] = 0;
    for (int i = 0; i < N - 1; ++ i) {
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from]+ e.cost){
                dist[e.to] = dist[e.from]+ e.cost;
            }
        }
    }
 
    ll ans = dist[N - 1];
 
    for (int i = 0; i < N ; ++i) {
        for (auto &&e : G) {
            if(dist[e.from] == INF<T>) continue;
            if(dist[e.to] > dist[e.from] + e.cost){
                dist[e.to] = dist[e.from] + e.cost;
                negative[e.to] = true;
            }
            if(negative[e.from]) negative[e.to] = true;
        }
    }
    for (int i = 0; i < N; ++i) {
        if(negative[i]) dist[i] = -INF<T>;
    }
    return dist;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

