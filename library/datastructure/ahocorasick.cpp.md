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


# :warning: Aho-Corasick法 <small>(datastructure/ahocorasick.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/ahocorasick.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 18:02:42+09:00




## 説明
Trie木に対応するパターンマッチングオートマトンを構築する。

## 操作
- $\mathrm{add}(s, cur))$ : Trie木の位置$cur$に文字列$s$を追加し、そのノードを返す。
- $\mathrm{build}()$ : パターンマッチングオートマトンを構築する。

## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<int W, int start>
class AhoCorasick {
public:
    struct Node {
        array<int, W> to;
        int fail;
        int val;
    };
    explicit AhoCorasick() : v(1) {}
    vector<Node> v;
    vector<int> ord;
    int add(string &s, int cur = 0){
        for (auto &&i : s) {
            if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();
            cur = v[cur].to[i-start];
        }
        return cur;
    }

    void build() {
        v[0].fail = -1;
        int l = 0, r = 1;
        ord.clear();
        ord.reserve(v.size());
        ord.emplace_back(0);
        while(l < r){
            int i = ord[l]; l++;
            for (int c = 0; c < W; ++c) {
                if(!v[i].to[c]) continue;
                int to = v[i].to[c];
                v[to].fail = (v[i].fail == -1 ? 0 : v[v[i].fail].to[c]);
                ord.emplace_back(to);
                r++;
            }
            if(i != 0){
                for (int c = 0; c < W; ++c) {
                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];
                }
            }
        }
    }
    inline int next(int x, char c){ return v[x].to[c-start]; }
};
/**
 * @brief Aho-Corasick法
 * @docs _md/ahocorasick.md
 */
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/ahocorasick.cpp"
template<int W, int start>
class AhoCorasick {
public:
    struct Node {
        array<int, W> to;
        int fail;
        int val;
    };
    explicit AhoCorasick() : v(1) {}
    vector<Node> v;
    vector<int> ord;
    int add(string &s, int cur = 0){
        for (auto &&i : s) {
            if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();
            cur = v[cur].to[i-start];
        }
        return cur;
    }

    void build() {
        v[0].fail = -1;
        int l = 0, r = 1;
        ord.clear();
        ord.reserve(v.size());
        ord.emplace_back(0);
        while(l < r){
            int i = ord[l]; l++;
            for (int c = 0; c < W; ++c) {
                if(!v[i].to[c]) continue;
                int to = v[i].to[c];
                v[to].fail = (v[i].fail == -1 ? 0 : v[v[i].fail].to[c]);
                ord.emplace_back(to);
                r++;
            }
            if(i != 0){
                for (int c = 0; c < W; ++c) {
                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];
                }
            }
        }
    }
    inline int next(int x, char c){ return v[x].to[c-start]; }
};
/**
 * @brief Aho-Corasick法
 * @docs _md/ahocorasick.md
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

