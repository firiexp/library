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


# :warning: flow/dinic.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#cff5497121104c2b8e0cb41ed2083a9b">flow</a>
* <a href="{{ site.github.repository_url }}/blob/master/flow/dinic.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, bool directed>
class Dinic {
    void bfs(int s){
        fill(level.begin(),level.end(), -1);
        queue<int> Q;
        level[s] = 0;
        Q.emplace(s);
        while(!Q.empty()){
            int v = Q.front(); Q.pop();
            for (auto &&e : G[v]){
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    Q.emplace(e.to);
                }
            }
        }
    }
 
    T dfs(int v, int t, T f){
        if(v == t) return f;
        for(int &i = iter[v]; i < G[v].size(); i++){
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]){
                T d = dfs(e.to, t, min(f,  e.cap));
                if(d == 0) continue;
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
public:
    struct edge {
        int to{}; T cap; int rev{};
        edge() = default;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
 
    vector<vector<edge>> G;
    vector<int> level, iter;
    Dinic() = default;
    explicit Dinic(int n) : G(n), level(n), iter(n) {}
 
    void add_edge(int from, int to, T cap){
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);
    }
 
 
    T flow(int s, int t, T lim = INF<T>){
        T ret = 0;
        while(true) {
            bfs(s);
            if(level[t] < 0 || lim == 0) break;
            fill(iter.begin(),iter.end(), 0);
            while(true){
                T f = dfs(s, t, lim);
                if(f == 0) break;
                ret += f;
                lim -= f;
            }
        }
        return ret;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "flow/dinic.cpp"
template<class T, bool directed>
class Dinic {
    void bfs(int s){
        fill(level.begin(),level.end(), -1);
        queue<int> Q;
        level[s] = 0;
        Q.emplace(s);
        while(!Q.empty()){
            int v = Q.front(); Q.pop();
            for (auto &&e : G[v]){
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    Q.emplace(e.to);
                }
            }
        }
    }
 
    T dfs(int v, int t, T f){
        if(v == t) return f;
        for(int &i = iter[v]; i < G[v].size(); i++){
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]){
                T d = dfs(e.to, t, min(f,  e.cap));
                if(d == 0) continue;
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
public:
    struct edge {
        int to{}; T cap; int rev{};
        edge() = default;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
 
    vector<vector<edge>> G;
    vector<int> level, iter;
    Dinic() = default;
    explicit Dinic(int n) : G(n), level(n), iter(n) {}
 
    void add_edge(int from, int to, T cap){
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);
    }
 
 
    T flow(int s, int t, T lim = INF<T>){
        T ret = 0;
        while(true) {
            bfs(s);
            if(level[t] < 0 || lim == 0) break;
            fill(iter.begin(),iter.end(), 0);
            while(true){
                T f = dfs(s, t, lim);
                if(f == 0) break;
                ret += f;
                lim -= f;
            }
        }
        return ret;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

