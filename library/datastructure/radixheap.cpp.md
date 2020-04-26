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


# :warning: datastructure/radixheap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/radixheap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class K, class V>
class RadixHeap {
    static constexpr int bit_length = sizeof(K)*8;
    K last;
    size_t sz, cnt;
    
    array<vector<pair<K, V>>, bit_length> v;
    static inline int bsr(int x){
        return x ? bit_length-__builtin_clz(x) : 0;
    }
    static inline int bsr(ll x){
        return x ? bit_length-__builtin_clzll(x) : 0;
    }

    void pull() {
        if(cnt < v[0].size()) return;;
        int i = 1;
        while(v[i].empty()) i++;
        last = min_element(v[i].begin(),v[i].end())->first;
        for (auto &&x : v[i]) v[bsr(x.first ^ last)].push_back(x);
        v[i].clear();
    }
public:
    RadixHeap() : last(0), sz(0), cnt(0) {}
    void emplace(K x, V val){
        sz++;
        v[bsr(x^last)].emplace_back(x, val);
    }

    pair<K, V> top() {
        pull();
        return v[0][cnt];
    }

    void pop() {
        pull();
        sz--;
        cnt++;
    }

    size_t size() const { return sz; }
    bool empty() const { return !sz; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/radixheap.cpp"
template <class K, class V>
class RadixHeap {
    static constexpr int bit_length = sizeof(K)*8;
    K last;
    size_t sz, cnt;
    
    array<vector<pair<K, V>>, bit_length> v;
    static inline int bsr(int x){
        return x ? bit_length-__builtin_clz(x) : 0;
    }
    static inline int bsr(ll x){
        return x ? bit_length-__builtin_clzll(x) : 0;
    }

    void pull() {
        if(cnt < v[0].size()) return;;
        int i = 1;
        while(v[i].empty()) i++;
        last = min_element(v[i].begin(),v[i].end())->first;
        for (auto &&x : v[i]) v[bsr(x.first ^ last)].push_back(x);
        v[i].clear();
    }
public:
    RadixHeap() : last(0), sz(0), cnt(0) {}
    void emplace(K x, V val){
        sz++;
        v[bsr(x^last)].emplace_back(x, val);
    }

    pair<K, V> top() {
        pull();
        return v[0][cnt];
    }

    void pop() {
        pull();
        sz--;
        cnt++;
    }

    size_t size() const { return sz; }
    bool empty() const { return !sz; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

