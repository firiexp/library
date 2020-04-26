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


# :warning: library/quickfind.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/quickfind.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct QuickFind {
    int n;
    vector<int> roots;
    vector<vector<int>> v;
    explicit QuickFind(int n) : n(n) {
        v.resize(n);
        for (int i = 0; i < n; ++i) v[i].emplace_back(i);
        roots.resize(n);
        iota(roots.begin(),roots.end(), 0);
    }
 
    int root(int a){ return roots[a]; }
    size_t size(int a){ return v[a].size(); }
    bool unite(int a, int b){
        if(same(a, b)) return false;
        a = roots[a], b = roots[b];
        if(size(a) < size(b)) swap(a, b);
        for (auto &&i : v[b]) {
            v[a].emplace_back(i);
            roots[i] = a;
        }
        dp[a] += dp[b];
        v[b].clear();
        v[b].shrink_to_fit();
        return true;
    }
    bool same(int a, int b){ return roots[a] == roots[b]; }
    const vector<int>& components(int x){ return v[roots[x]];}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/quickfind.cpp"
struct QuickFind {
    int n;
    vector<int> roots;
    vector<vector<int>> v;
    explicit QuickFind(int n) : n(n) {
        v.resize(n);
        for (int i = 0; i < n; ++i) v[i].emplace_back(i);
        roots.resize(n);
        iota(roots.begin(),roots.end(), 0);
    }
 
    int root(int a){ return roots[a]; }
    size_t size(int a){ return v[a].size(); }
    bool unite(int a, int b){
        if(same(a, b)) return false;
        a = roots[a], b = roots[b];
        if(size(a) < size(b)) swap(a, b);
        for (auto &&i : v[b]) {
            v[a].emplace_back(i);
            roots[i] = a;
        }
        dp[a] += dp[b];
        v[b].clear();
        v[b].shrink_to_fit();
        return true;
    }
    bool same(int a, int b){ return roots[a] == roots[b]; }
    const vector<int>& components(int x){ return v[roots[x]];}
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

