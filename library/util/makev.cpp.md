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


# :heavy_check_mark: make_v, chmin, chmax <small>(util/makev.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05c7e24700502a079cdd88012b5a76d3">util</a>
* <a href="{{ site.github.repository_url }}/blob/master/util/makev.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-28 18:50:16+09:00




## 説明
vector<vector\<int\>>とか書かなくていいようにするやつ。

## できること
- make_v : 多次元vectorの作成
- chmin(x, y) : x = min(x, y)
- chmax(x, y) : x = max(x, y) 

## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj0274.test.cpp.html">test/aoj0274.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj0335.test.cpp.html">test/aoj0335.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T, class U>
vector<T> make_v(U size, const T& init){ return vector<T>(static_cast<size_t>(size), init); }

template<class... Ts, class U>
auto make_v(U size, Ts... rest) { return vector<decltype(make_v(rest...))>(static_cast<size_t>(size), make_v(rest...)); }

template<class T> void chmin(T &a, const T &b){ a = (a < b ? a : b); }
template<class T> void chmax(T &a, const T &b){ a = (a > b ? a : b); }

/**
 * @brief make_v, chmin, chmax
 * @docs _md/makev.md
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "util/makev.cpp"
template <class T, class U>
vector<T> make_v(U size, const T& init){ return vector<T>(static_cast<size_t>(size), init); }

template<class... Ts, class U>
auto make_v(U size, Ts... rest) { return vector<decltype(make_v(rest...))>(static_cast<size_t>(size), make_v(rest...)); }

template<class T> void chmin(T &a, const T &b){ a = (a < b ? a : b); }
template<class T> void chmax(T &a, const T &b){ a = (a > b ? a : b); }

/**
 * @brief make_v, chmin, chmax
 * @docs _md/makev.md
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

