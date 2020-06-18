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


# :heavy_check_mark: graph/bipartite_matching_lexmin.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/bipartite_matching_lexmin.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-18 18:17:52+09:00




## Depends on

* :heavy_check_mark: <a href="bipartite_matching.cpp.html">graph/bipartite_matching.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj0334.test.cpp.html">test/aoj0334.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "./bipartite_matching.cpp"
class Bipartite_Matching_LexMin : public Bipartite_Matching {
public:
    using Bipartite_Matching::Bipartite_Matching;

    int solve_LexMin() { // check sorted edge no
        int res = matching();
        for (int i = 0; i < l; ++i) {
            if(!~match[i]) continue;
            match[match[i]] = -1;
            match[i] = -1;
            ++t;
            dfs(i);
            alive[match[i]] = 0;
            alive[i] = 0;
        }
        return res;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/bipartite_matching.cpp"
class Bipartite_Matching {
protected:
    vector<vector<int>> G;
    vector<int> used, alive;
    int t;
    int l, r;
public:
    vector<int> match;
    explicit Bipartite_Matching(int l, int r): l(l), r(r), t(0), G(l+r), used(l+r, 0), alive(l+r, -1), match(l+r, -1) {};

    void add_edge(int a, int b){
        G[a].emplace_back(b+l);
        G[b+l].emplace_back(a);
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
#line 2 "graph/bipartite_matching_lexmin.cpp"
class Bipartite_Matching_LexMin : public Bipartite_Matching {
public:
    using Bipartite_Matching::Bipartite_Matching;

    int solve_LexMin() { // check sorted edge no
        int res = matching();
        for (int i = 0; i < l; ++i) {
            if(!~match[i]) continue;
            match[match[i]] = -1;
            match[i] = -1;
            ++t;
            dfs(i);
            alive[match[i]] = 0;
            alive[i] = 0;
        }
        return res;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

