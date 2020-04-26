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


# :warning: tree/treedfs.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c0af77cf8294ff93a5cdb2963ca9f038">tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/tree/treedfs.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
deque<int> Q;
stack<int> s;
int cnt = 0;
vector<int> visited(n, 0), num(n);
s.emplace(0);
while(!s.empty()){
    int a = s.top(); s.pop();
    visited[a]++;
    num[a] = cnt++;
    Q.emplace_front(a);
    for (auto &&i : v[a]) {
        if(!visited[i]) s.emplace(i);
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "tree/treedfs.cpp"
deque<int> Q;
stack<int> s;
int cnt = 0;
vector<int> visited(n, 0), num(n);
s.emplace(0);
while(!s.empty()){
    int a = s.top(); s.pop();
    visited[a]++;
    num[a] = cnt++;
    Q.emplace_front(a);
    for (auto &&i : v[a]) {
        if(!visited[i]) s.emplace(i);
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

