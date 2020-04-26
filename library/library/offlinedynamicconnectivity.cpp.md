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


# :warning: library/offlinedynamicconnectivity.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/offlinedynamicconnectivity.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class UndoableUnionFind {
    stack<pair<int, int>> hist;
    int forest_size;
public:
    vector<int> uni;
    explicit UndoableUnionFind(int sz) : uni(sz, -1), forest_size(sz) {}

    int root(int a){
        if(uni[a] < 0) return a;
        return root(uni[a]);
    }

    bool unite(int a, int b){
        a = root(a), b = root(b);
        hist.emplace(a, uni[a]);
        hist.emplace(b, uni[b]);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }

    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }

    void undo(){
        uni[hist.top().first] = hist.top().second;
        hist.pop();
        uni[hist.top().first] = hist.top().second;
        hist.pop();
    }

    void snapshot(){ while(!hist.empty()) hist.pop(); }
    void rollback(){ while(!hist.empty()) undo(); }
};

class OfflineDynamicConnectivity {
    UndoableUnionFind uf;
    int n;
    vector<vector<pair<int, int>>> seg;
    vector<pair<pair<int, int>, pair<int, int>>> pend;
    map<pair<int, int>, int> cnt, appear;
    void add(int a, int b, const pair<int ,int> &e){
        for (int l = a+sz, r = b+sz; l < r; l >>= 1, r >>= 1) {
            if(l&1) seg[l++].emplace_back(e);
            if(r&1) seg[--r].emplace_back(e);
        }
    }
public:
    int sz;
    OfflineDynamicConnectivity(int n, int q) : uf(n), n(n){
        sz = 1;
        while(sz < q) sz <<= 1;
        seg.resize(2*sz);
    }

    void insert(int t, int a, int b){
        auto e = minmax(a, b);
        if(cnt[e]++ == 0) appear[e] = t;
    }

    void erase(int t, int a, int b){
        auto e = minmax(a, b);
        if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], t), e)
    }

    void build(){
        for (auto &&i : cnt) {
            if(!i.second) continue;
            pend.emplace_back(make_pair(appear[i.first], q), i.first);
        }
        for (auto &&i : pend) {
            add(i.first.first, i.first.second, i.second);
        }
    }

    template<typename F>
    void run(const F &f, int k = 1){
        for (auto &&i : seg[k]) uf.unite(i.first, i.second);
        if(k < sz){
            run(f, (k << 1) | 0);
            run(f, (k << 1) | 1);
        }else f(k-sz);
        for (auto &&i : seg[k]) uf.undo();
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/offlinedynamicconnectivity.cpp"
class UndoableUnionFind {
    stack<pair<int, int>> hist;
    int forest_size;
public:
    vector<int> uni;
    explicit UndoableUnionFind(int sz) : uni(sz, -1), forest_size(sz) {}

    int root(int a){
        if(uni[a] < 0) return a;
        return root(uni[a]);
    }

    bool unite(int a, int b){
        a = root(a), b = root(b);
        hist.emplace(a, uni[a]);
        hist.emplace(b, uni[b]);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a, b);
        uni[a] += uni[b];
        uni[b] = a;
        forest_size--;
        return true;
    }

    int size(){ return forest_size; }
    int size(int i){ return -uni[root(i)]; }

    void undo(){
        uni[hist.top().first] = hist.top().second;
        hist.pop();
        uni[hist.top().first] = hist.top().second;
        hist.pop();
    }

    void snapshot(){ while(!hist.empty()) hist.pop(); }
    void rollback(){ while(!hist.empty()) undo(); }
};

class OfflineDynamicConnectivity {
    UndoableUnionFind uf;
    int n;
    vector<vector<pair<int, int>>> seg;
    vector<pair<pair<int, int>, pair<int, int>>> pend;
    map<pair<int, int>, int> cnt, appear;
    void add(int a, int b, const pair<int ,int> &e){
        for (int l = a+sz, r = b+sz; l < r; l >>= 1, r >>= 1) {
            if(l&1) seg[l++].emplace_back(e);
            if(r&1) seg[--r].emplace_back(e);
        }
    }
public:
    int sz;
    OfflineDynamicConnectivity(int n, int q) : uf(n), n(n){
        sz = 1;
        while(sz < q) sz <<= 1;
        seg.resize(2*sz);
    }

    void insert(int t, int a, int b){
        auto e = minmax(a, b);
        if(cnt[e]++ == 0) appear[e] = t;
    }

    void erase(int t, int a, int b){
        auto e = minmax(a, b);
        if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], t), e)
    }

    void build(){
        for (auto &&i : cnt) {
            if(!i.second) continue;
            pend.emplace_back(make_pair(appear[i.first], q), i.first);
        }
        for (auto &&i : pend) {
            add(i.first.first, i.first.second, i.second);
        }
    }

    template<typename F>
    void run(const F &f, int k = 1){
        for (auto &&i : seg[k]) uf.unite(i.first, i.second);
        if(k < sz){
            run(f, (k << 1) | 0);
            run(f, (k << 1) | 1);
        }else f(k-sz);
        for (auto &&i : seg[k]) uf.undo();
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
