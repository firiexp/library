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


# :warning: library/twosat.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/twosat.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct SCC {
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n), cmp(n) {}

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G_r[b].emplace_back(a);
    }

    void dfs(int v){
        used[v] = 1;
        for (auto &&u : G[v]) if(!used[u]) dfs(u);
        vs.emplace_back(v);
    }

    void dfs_r(int v, int k){
        used[v] = 1;
        cmp[v] = k;
        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);
    }

    int build() {
        int n = G.size();
        for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);
        fill(used.begin(),used.end(), 0);
        int k = 0;
        for (int i = n - 1; i >= 0; --i) {
            if(!used[vs[i]]){
                dfs_r(vs[i], k++);
            }
        }
        G_out.resize(k);
        for (int i = 0; i < n; ++i) {
            for (auto &&j : G[i]) {
                if(cmp[i] != cmp[j]){
                    G_out[cmp[i]].emplace_back(cmp[j]);
                }
            }
        }
        for (int i = 0; i < k; ++i) {
            sort(G_out.begin(), G_out.end());
            G_out.erase(unique(G_out.begin(), G_out.end()), G_out.end());
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};

struct TwoSAT {
    int n;
    SCC scc;
    explicit TwoSAT(int n) : n(n), scc(n*2) {};
    int negate(int v){
        int ret = n+v;
        if(ret >= n*2) ret -= n*2;
        return ret;
    }

    vector<int> build() {
        scc.build();
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            if(scc[i] == scc[n+i]) return {};
            res[i] = scc[i] > scc[n+i];
        }
        return res;
    }

    void add_if(int u, int v){ // u -> v
        scc.add_edge(u, v);
        scc.add_edge(negate(v), negate(u));
    }

    void add_or(int u, int v){ // u || v
        add_if(negate(u), v);
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/twosat.cpp"
struct SCC {
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n), cmp(n) {}

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G_r[b].emplace_back(a);
    }

    void dfs(int v){
        used[v] = 1;
        for (auto &&u : G[v]) if(!used[u]) dfs(u);
        vs.emplace_back(v);
    }

    void dfs_r(int v, int k){
        used[v] = 1;
        cmp[v] = k;
        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);
    }

    int build() {
        int n = G.size();
        for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);
        fill(used.begin(),used.end(), 0);
        int k = 0;
        for (int i = n - 1; i >= 0; --i) {
            if(!used[vs[i]]){
                dfs_r(vs[i], k++);
            }
        }
        G_out.resize(k);
        for (int i = 0; i < n; ++i) {
            for (auto &&j : G[i]) {
                if(cmp[i] != cmp[j]){
                    G_out[cmp[i]].emplace_back(cmp[j]);
                }
            }
        }
        for (int i = 0; i < k; ++i) {
            sort(G_out.begin(), G_out.end());
            G_out.erase(unique(G_out.begin(), G_out.end()), G_out.end());
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};

struct TwoSAT {
    int n;
    SCC scc;
    explicit TwoSAT(int n) : n(n), scc(n*2) {};
    int negate(int v){
        int ret = n+v;
        if(ret >= n*2) ret -= n*2;
        return ret;
    }

    vector<int> build() {
        scc.build();
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            if(scc[i] == scc[n+i]) return {};
            res[i] = scc[i] > scc[n+i];
        }
        return res;
    }

    void add_if(int u, int v){ // u -> v
        scc.add_edge(u, v);
        scc.add_edge(negate(v), negate(u));
    }

    void add_or(int u, int v){ // u || v
        add_if(negate(u), v);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

