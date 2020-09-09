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


# :heavy_check_mark: test/yosupo_unionfind.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 23:04:12+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/datastructure/unionfind.cpp.html">UnionFind(素集合データ構造) <small>(datastructure/unionfind.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = uint32_t;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../datastructure/unionfind.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        scanf("%d %d %d", &t, &u, &v);
        if(t) printf("%d\n", uf.same(u, v));
        else uf.unite(u, v);
    }
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_unionfind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = uint32_t;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#line 1 "datastructure/unionfind.cpp"
class UnionFind {
    int n;
    vector<int> uni;
    int forest_size;
public:
    explicit UnionFind(int n) : n(n), uni(static_cast<u32>(n), -1), forest_size(n) {};

    int root(int a){
        if (uni[a] < 0) return a;
        else return (uni[a] = root(uni[a]));
    }

    bool unite(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }
    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }
    bool same(int a, int b) { return root(a) == root(b); }
};

/**
 * @brief UnionFind(素集合データ構造)
 * @docs _md/unionfind.md
 */
#line 22 "test/yosupo_unionfind.test.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        scanf("%d %d %d", &t, &u, &v);
        if(t) printf("%d\n", uf.same(u, v));
        else uf.unite(u, v);
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

