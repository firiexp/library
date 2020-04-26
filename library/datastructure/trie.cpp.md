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


# :warning: datastructure/trie.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/trie.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<int W, class F> // W -> word size
struct Trie {
    struct Node {
        char c;
        array<int, W> nxt;
        vector<int> idxs;
        int id;
        explicit Node(char c): c(c), id(-1){
            fill(nxt.begin(),nxt.end(), -1);
        }
    };
    vector<Node> v;
    F f;
    explicit Trie(F f, char c = '$') : f(f) {
        v.emplace_back(c);
    }
    void add(const string &s, int x){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(~v[cur].nxt[k]){
                cur = v[cur].nxt[k];
                continue;
            }
            int npos = v.size();
            v[cur].nxt[k] = npos;
            v.emplace_back(i);
            cur = npos;
        }
        v[cur].id = x;
        v[cur].idxs.emplace_back(x);
    }

    int find(const string &s){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(v[cur].nxt[k] < 0) return -1;
            cur = v[cur].nxt[k];
        }
        return cur;
    }
    int find(int cur, char c) {return v[cur].nxt[f(c)]; }
    int id(int cur) { return cur < 0 ? -1 : v[cur].id;}

    vector<int> idxs(int cur) { return cur < 0 ? vector<int>() : v[cur].idxs; }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/trie.cpp"
template<int W, class F> // W -> word size
struct Trie {
    struct Node {
        char c;
        array<int, W> nxt;
        vector<int> idxs;
        int id;
        explicit Node(char c): c(c), id(-1){
            fill(nxt.begin(),nxt.end(), -1);
        }
    };
    vector<Node> v;
    F f;
    explicit Trie(F f, char c = '$') : f(f) {
        v.emplace_back(c);
    }
    void add(const string &s, int x){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(~v[cur].nxt[k]){
                cur = v[cur].nxt[k];
                continue;
            }
            int npos = v.size();
            v[cur].nxt[k] = npos;
            v.emplace_back(i);
            cur = npos;
        }
        v[cur].id = x;
        v[cur].idxs.emplace_back(x);
    }

    int find(const string &s){
        int cur = 0;
        for (auto &&i : s) {
            int k = f(i);
            if(v[cur].nxt[k] < 0) return -1;
            cur = v[cur].nxt[k];
        }
        return cur;
    }
    int find(int cur, char c) {return v[cur].nxt[f(c)]; }
    int id(int cur) { return cur < 0 ? -1 : v[cur].id;}

    vector<int> idxs(int cur) { return cur < 0 ? vector<int>() : v[cur].idxs; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

