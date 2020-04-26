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


# :warning: datastructure/binarytrie.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/binarytrie.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Node {
    int val;
    Node *nxt[2];
    Node() : val(0), nxt{nullptr, nullptr} {}
    static int cnt;
    void *operator new(size_t){
        static Node pool[3000000];
        return pool + cnt++;
    }
};
int Node::cnt = 0;

template<class T, size_t X>
struct Binarytrie {
    Node *root;
    Binarytrie() { root = new Node; }

    void add(const T b, T x = 1){
        Node *p = root;
        for (int i = X-1; i >= 0; --i) {
            bool f = (b >> i) & 1;
            if(!p->nxt[f]) p->nxt[f] = new Node;
            p = p->nxt[f];
        }
        p->val += x;
    }

    T xor_min(Node* t, const T &x, int dep = X-1){
        if(dep < 0) return 0;
        T f = (x >> dep) & 1U; f ^= !t->nxt[f];
        return xor_min(t->nxt[f], x, dep-1) | (f << dep);
    }
    T max_element(T x = 0) {
        return xor_min(root, ~x);
    }
    T min_element(T x = 0){
        return xor_min(root, x);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/binarytrie.cpp"
struct Node {
    int val;
    Node *nxt[2];
    Node() : val(0), nxt{nullptr, nullptr} {}
    static int cnt;
    void *operator new(size_t){
        static Node pool[3000000];
        return pool + cnt++;
    }
};
int Node::cnt = 0;

template<class T, size_t X>
struct Binarytrie {
    Node *root;
    Binarytrie() { root = new Node; }

    void add(const T b, T x = 1){
        Node *p = root;
        for (int i = X-1; i >= 0; --i) {
            bool f = (b >> i) & 1;
            if(!p->nxt[f]) p->nxt[f] = new Node;
            p = p->nxt[f];
        }
        p->val += x;
    }

    T xor_min(Node* t, const T &x, int dep = X-1){
        if(dep < 0) return 0;
        T f = (x >> dep) & 1U; f ^= !t->nxt[f];
        return xor_min(t->nxt[f], x, dep-1) | (f << dep);
    }
    T max_element(T x = 0) {
        return xor_min(root, ~x);
    }
    T min_element(T x = 0){
        return xor_min(root, x);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

