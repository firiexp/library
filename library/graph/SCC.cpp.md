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


# :heavy_check_mark: graph/SCC.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/SCC.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 14:40:12+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj0349.test.cpp.html">test/aoj0349.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo_scc.test.cpp.html">test/yosupo_scc.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class SCC {
    void dfs(int v){
        used[v] = 1;
        for (auto &&u : G[v]) if(!used[u]) dfs(u);
        vs.emplace_back(v);
    }

    void dfs_r(int v, int k){
        used[v] = 1;
        cmp[v] = k;
        sz[k]++;
        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);
    }
public:
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp, sz;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n), cmp(n), sz(n) {}

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G_r[b].emplace_back(a);
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
        sz.resize(k);
        for (int i = 0; i < n; ++i) {
            for (auto &&j : G[i]) {
                if(cmp[i] != cmp[j]){
                    G_out[cmp[i]].emplace_back(cmp[j]);
                }
            }
        }
        for (auto &&l : G_out) {
            sort(l.begin(), l.end());
            l.erase(unique(l.begin(), l.end()), l.end());
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/SCC.cpp"
class SCC {
    void dfs(int v){
        used[v] = 1;
        for (auto &&u : G[v]) if(!used[u]) dfs(u);
        vs.emplace_back(v);
    }

    void dfs_r(int v, int k){
        used[v] = 1;
        cmp[v] = k;
        sz[k]++;
        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);
    }
public:
    vector<vector<int>> G, G_r, G_out;
    vector<int> vs, used, cmp, sz;
    SCC() = default;
    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n), cmp(n), sz(n) {}

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G_r[b].emplace_back(a);
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
        sz.resize(k);
        for (int i = 0; i < n; ++i) {
            for (auto &&j : G[i]) {
                if(cmp[i] != cmp[j]){
                    G_out[cmp[i]].emplace_back(cmp[j]);
                }
            }
        }
        for (auto &&l : G_out) {
            sort(l.begin(), l.end());
            l.erase(unique(l.begin(), l.end()), l.end());
        }
        return k;
    }

    int operator[](int k) const { return cmp[k]; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

