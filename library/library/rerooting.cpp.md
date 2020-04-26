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


# :warning: library/rerooting.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/rerooting.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename M>
class ReRooting {
public:
    using T = typename M::T;
    using U = typename M::U;
    struct Node {
        int to, rev;
        U val;
        Node(int u, int v, U val) : to(u), rev(v), val(val) {};
    };
    int n;
    vector<vector<Node>> G;
    vector<vector<T>> dpl, dpr;
    vector<int> l, r;

    explicit ReRooting(int n) : n(n), G(n), dpl(n), dpr(n), l(n), r(n) {};

    void add_edge(int u, int v, const U &x) {
        G[u].emplace_back(v, G[v].size(), x);
        G[v].emplace_back(u, G[u].size()-1, x);
    }
    void add_edge(int u, int v, const U &x, const U &y) {
        G[u].emplace_back(v, G[v].size(), x);
        G[v].emplace_back(u, G[u].size()-1, y);
    }

    T dfs(int i, int par){
        while(l[i] != par && l[i] < G[i].size()){
            auto &e = G[i][l[i]];
            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]], M::g(dfs(e.to, e.rev), e.val));
            ++l[i];
        }
        while(r[i] != par && r[i] >= 0){
            auto &e = G[i][r[i]];
            dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));
            --r[i];
        }
        if(par < 0) return dpr[i].front();
        return M::f(dpl[i][par], dpr[i][par+1]);
    }

    vector<T> solve(){
        for (int i = 0; i < n; ++i) {
            dpl[i].assign(G[i].size()+1, M::e());
            dpr[i].assign(G[i].size()+1, M::e());
            l[i] = 0;
            r[i] = (int)G[i].size() - 1;
        }
        vector<T> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = dfs(i, -1);
        }
        return ans;
    }
};

struct M {
    using T = mint;
    using U = mint;
    static T f(T a, T b) { return a*b; }
    static T g(T a, U b) {
        return a+b;
    }
    static T e() { return {1}; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/rerooting.cpp"
template<typename M>
class ReRooting {
public:
    using T = typename M::T;
    using U = typename M::U;
    struct Node {
        int to, rev;
        U val;
        Node(int u, int v, U val) : to(u), rev(v), val(val) {};
    };
    int n;
    vector<vector<Node>> G;
    vector<vector<T>> dpl, dpr;
    vector<int> l, r;

    explicit ReRooting(int n) : n(n), G(n), dpl(n), dpr(n), l(n), r(n) {};

    void add_edge(int u, int v, const U &x) {
        G[u].emplace_back(v, G[v].size(), x);
        G[v].emplace_back(u, G[u].size()-1, x);
    }
    void add_edge(int u, int v, const U &x, const U &y) {
        G[u].emplace_back(v, G[v].size(), x);
        G[v].emplace_back(u, G[u].size()-1, y);
    }

    T dfs(int i, int par){
        while(l[i] != par && l[i] < G[i].size()){
            auto &e = G[i][l[i]];
            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]], M::g(dfs(e.to, e.rev), e.val));
            ++l[i];
        }
        while(r[i] != par && r[i] >= 0){
            auto &e = G[i][r[i]];
            dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));
            --r[i];
        }
        if(par < 0) return dpr[i].front();
        return M::f(dpl[i][par], dpr[i][par+1]);
    }

    vector<T> solve(){
        for (int i = 0; i < n; ++i) {
            dpl[i].assign(G[i].size()+1, M::e());
            dpr[i].assign(G[i].size()+1, M::e());
            l[i] = 0;
            r[i] = (int)G[i].size() - 1;
        }
        vector<T> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = dfs(i, -1);
        }
        return ans;
    }
};

struct M {
    using T = mint;
    using U = mint;
    static T f(T a, T b) { return a*b; }
    static T g(T a, U b) {
        return a+b;
    }
    static T e() { return {1}; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

