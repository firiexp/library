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


# :heavy_check_mark: UnionFind(素集合データ構造) <small>(datastructure/unionfind.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/unionfind.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-28 23:17:17+09:00




## 説明
頂点の併合、代表元の取得が$O(\alpha (n))$でできるデータ構造。

## 操作
- $\mathrm{root}(a)$ : 頂点$a$の代表元を取得。　
- $\mathrm{unite}(a, b)$ : 頂点$a$と$b$の属する集合を併合する。　
- $\mathrm{size}()$ : 集合の数を取得する。
- $\mathrm{size}(i)$ : $i$の属する集合の大きさを取得する。
- $\mathrm{same}(a, b)$ : $a$と$b$が同じ集合に属するかどうかを判定する。


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj0342.test.cpp.html">test/aoj0342.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

