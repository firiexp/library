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


# :heavy_check_mark: test/yosupo_dominator_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_dominator_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-10 18:46:05+09:00


* see: <a href="https://judge.yosupo.jp/problem/dominatortree">https://judge.yosupo.jp/problem/dominatortree</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/dominatortree.cpp.html">Dominator Tree <small>(graph/dominatortree.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../graph/dominatortree.cpp"

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    DominatorTree G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    G.build(s);
    for (int i = 0; i < n; ++i) {
        if(i) printf(" ");
        printf("%d", (i == s ? s : G.idom[i]));
    }
    puts("");
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_dominator_tree.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#line 1 "graph/dominatortree.cpp"
class DominatorTree {
    int n;
    void unite(int x, int y){
        uf_par[y] = x;
    }

    int compress(int x){
        if(uf_par[x] == x) return x;
        int r = compress(uf_par[x]);
        if(semi[m[x]] > semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];
        return uf_par[x] = r;
    }

    int eval(int x){
        compress(x);
        return m[x];
    }


    void dfs(int x, int &cur){
        semi[x] = cur;
        ord[cur++] = x;
        for (auto &&i : G[x]) {
            if(!~semi[i]){
                par[i] = x;
                dfs(i, cur);
            }
        }
    }
public:
    DominatorTree(int n) : n(n), G(n), Grev(n), idom(n), semi(n), ord(n), par(n), uf_par(n), m(n), tmp(n), U(n) {}

    vector<vector<int>> G, Grev, tmp;
    vector<int> semi, ord, par, uf_par, m, U, idom;

    void add_edge(int a, int b){
        G[a].emplace_back(b);
        Grev[b].emplace_back(a);
    }
    void build(int root){
        for (int i = 0; i < n; ++i) uf_par[i] = i, m[i] = i, semi[i] = -1, idom[i] = -1;
        int cur = 0;
        dfs(root, cur);
        for (int i = cur-1; i >= 0; --i) {
            int a = ord[i];
            for (auto &&b : Grev[a]) {
                if(~semi[b]){
                    int c = eval(b);
                    semi[a] = min(semi[a], semi[c]);
                }
            }
            tmp[ord[semi[a]]].emplace_back(a);
            for (auto &&b : tmp[par[a]]) U[b] = eval(b);
            tmp[par[a]].clear();
            unite(par[a], a);
        }
        for (int i = 1; i < cur; ++i) {
            int a = ord[i], b = U[a];
            if(semi[a] == semi[b]) idom[a] = semi[a];
            else idom[a] = idom[b];
        }
        for (int i = 1; i < cur; ++i) {
            int a = ord[i];
            idom[a] = ord[idom[a]];
        }
        idom[root] = -1;
    }

};


/**
 * @brief Dominator Tree
 * @docs _md/dominatortree.md
 */
#line 22 "test/yosupo_dominator_tree.test.cpp"

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    DominatorTree G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    G.build(s);
    for (int i = 0; i < n; ++i) {
        if(i) printf(" ");
        printf("%d", (i == s ? s : G.idom[i]));
    }
    puts("");
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

