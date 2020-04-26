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


# :warning: library/weightedunionfind.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/weightedunionfind.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T>
class WeightedUnionFind {
    vector<int> uni;
    vector<T> weights;
    int n;
public:
    explicit WeightedUnionFind(int n, T SUM_UNITY = 0) :
    uni(static_cast<u32>(n), -1) , n(n), weights(n,  SUM_UNITY){};

    int root(int a) {
        if (uni[a] < 0) return a;
        else {
            int r = root(uni[a]);
            weights[a] += weights[uni[a]];
            return (uni[a] = r);
        }
    }

    bool unite(int a, int b, T w) {
        w += weight(a); w -= weight(b);
        a = root(a);
        b = root(b);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b), w = -w;
        uni[a] += uni[b];
        uni[b] = a;
        weights[b] = w;
        return true;
    }

    int size(int a){
        return -uni[root(a)];
    }

    T weight(T a){
        root(a);
        return weights[a];
    }
    int diff(int x, int y){
        return weight(y) - weight(x);
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/weightedunionfind.cpp"
template <class T>
class WeightedUnionFind {
    vector<int> uni;
    vector<T> weights;
    int n;
public:
    explicit WeightedUnionFind(int n, T SUM_UNITY = 0) :
    uni(static_cast<u32>(n), -1) , n(n), weights(n,  SUM_UNITY){};

    int root(int a) {
        if (uni[a] < 0) return a;
        else {
            int r = root(uni[a]);
            weights[a] += weights[uni[a]];
            return (uni[a] = r);
        }
    }

    bool unite(int a, int b, T w) {
        w += weight(a); w -= weight(b);
        a = root(a);
        b = root(b);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b), w = -w;
        uni[a] += uni[b];
        uni[b] = a;
        weights[b] = w;
        return true;
    }

    int size(int a){
        return -uni[root(a)];
    }

    T weight(T a){
        root(a);
        return weights[a];
    }
    int diff(int x, int y){
        return weight(y) - weight(x);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

