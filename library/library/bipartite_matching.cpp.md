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


# :warning: library/bipartite_matching.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/bipartite_matching.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class Bipartite_Matching {
    vector<vector<int>> G;
    vector<int> used, alive;
    int t;
public:
    vector<int> match;
    explicit Bipartite_Matching(int n): t(0), G(n), used(n, 0), alive(n, -1), match(n, -1) {};

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    bool dfs(int x){
        used[x] = t;
        for (auto &&i : G[x]) {
            int w = match[i];
            if(alive[i] == 0) continue;
            if(w == -1 || (used[w] != t && dfs(w))){
                match[x] = i;
                match[i] = x;
                return true;
            }
        }
        return false;
    }

    int matching() {
        int ans = 0;
        for (int i = 0; i < G.size(); ++i) {
            if(alive[i] == 0) continue;
            if(match[i] == -1) {
                ++t;
                ans += dfs(i);
            }
        }
        return ans;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/bipartite_matching.cpp"
class Bipartite_Matching {
    vector<vector<int>> G;
    vector<int> used, alive;
    int t;
public:
    vector<int> match;
    explicit Bipartite_Matching(int n): t(0), G(n), used(n, 0), alive(n, -1), match(n, -1) {};

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    bool dfs(int x){
        used[x] = t;
        for (auto &&i : G[x]) {
            int w = match[i];
            if(alive[i] == 0) continue;
            if(w == -1 || (used[w] != t && dfs(w))){
                match[x] = i;
                match[i] = x;
                return true;
            }
        }
        return false;
    }

    int matching() {
        int ans = 0;
        for (int i = 0; i < G.size(); ++i) {
            if(alive[i] == 0) continue;
            if(match[i] == -1) {
                ++t;
                ans += dfs(i);
            }
        }
        return ans;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

