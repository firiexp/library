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


# :heavy_check_mark: BinaryIndexedTree (BIT) <small>(datastructure/binaryindexedtree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/binaryindexedtree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 18:02:42+09:00




## 説明
可換群(逆元が存在する群)について、区間和を$O(\log N)$で求め、更新を$O(\log N)$で行う。<br>
可換でなくても$[0, x)$について演算した結果だけを求めたいのであれば、使うことができる。(例: LIS)

## 操作
- $\mathrm{add}(k, x)$ : $k$番目の要素に$x$を加算する。
- $\mathrm{sum}(k)$ : 閉区間$[0, k]$の和を求める。
- $\mathrm{lower\_bound}(x)$ : $\mathrm{sum}(k)$が$x$以上になる最小の$k$を求める。

## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_dsl_2_b.test.cpp.html">test/aoj_dsl_2_b.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
class BIT {
    vector<T> bit;
    int m;
public:
    BIT(int n): bit(vector<T>(n+1, 0)){
        m = 1;
        while(m < n) m <<= 1;
    }

    T sum(int k){
        T ret = 0;
        for (++k; k > 0; k -= (k & -k)) ret += bit[k];
        return ret;
    }

    void add(int k, T x){
        for (++k; k < bit.size(); k  += (k & -k)) bit[k] += x;
    }
    
    T lower_bound(T x){
        int i = 0;
        for (int j = m; j > 0; j >>= 1) {
            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];
        }
        return i;
    }
};
/**
 * @brief BinaryIndexedTree (BIT)
 * @docs _md/binaryindexedtree.md
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/binaryindexedtree.cpp"
template<class T>
class BIT {
    vector<T> bit;
    int m;
public:
    BIT(int n): bit(vector<T>(n+1, 0)){
        m = 1;
        while(m < n) m <<= 1;
    }

    T sum(int k){
        T ret = 0;
        for (++k; k > 0; k -= (k & -k)) ret += bit[k];
        return ret;
    }

    void add(int k, T x){
        for (++k; k < bit.size(); k  += (k & -k)) bit[k] += x;
    }
    
    T lower_bound(T x){
        int i = 0;
        for (int j = m; j > 0; j >>= 1) {
            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];
        }
        return i;
    }
};
/**
 * @brief BinaryIndexedTree (BIT)
 * @docs _md/binaryindexedtree.md
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

