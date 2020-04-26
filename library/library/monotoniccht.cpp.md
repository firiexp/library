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


# :warning: library/monotoniccht.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/monotoniccht.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, bool get_max>
class CHT {
    using P = pair<T, T>;
    deque<P> lines;
public:
    CHT() = default;
    int sgn(T x) { return x == 0 ? 0 : (x > 0 ? 1 : -1); }
    bool check(P l1, P l2, P l3){
        if(l1.second == l2.second || l2.second == l3.second){
            return sgn(l1.first - l2.first)*sgn(l2.second - l3.second)
                >= sgn(l2.first - l3.first)*sgn(l1.second - l2.second);
        }else {
            return (l1.first - l2.first)*sgn(l2.second - l3.second)/ static_cast<long double>(abs(l1.second - l2.second))
                   >= (l2.first - l3.first)*sgn(l1.second - l2.second)/ static_cast<long double>(abs(l2.second - l3.second));
        }
    }

    void add_line(T a, T b) { // add ax + b
        if(get_max) a = -a, b = -b;
        P L(a, b);
        if(lines.empty()){
            lines.emplace_back(L);
            return;
        }
        if(lines.front().first <= a){
            if(lines.front().first == a){
                if(lines.front().second <= b) return;
                else lines.pop_front();
            }
            while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();
            lines.emplace_front(L);
        }else {
            if(lines.back().first == a){
                if(lines.back().second <= b) return;
                else lines.pop_back();
            }
            while(lines.size() >= 2 && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();
            lines.emplace_back(L);
        }
    }

    T val(const P &L, const T &x) { return L.first * x + L.second; }
    T query(T x){
        int l = -1, r = lines.size() - 1;
        while(r - l > 1){
            int mid = (l+r) >> 1;
            if(val(lines[mid], x) >= val(lines[mid+1], x)) l = mid;
            else r = mid;
        }
        return get_max ? -val(lines[r], x) : val(lines[r], x);
    }

    T query_increase(T x){
        while(lines.size() >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();
        return get_max ? -val(lines.front(), x) : val(lines.front(), x);
    }

    T query_decrease(T x){
        while(lines.size() >= 2 && val(lines.back(), x) >= val(lines[lines.size() - 2], x)) lines.pop_back();
        return get_max ? -val(lines.back(), x) : val(lines.back(), x);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/monotoniccht.cpp"
template<class T, bool get_max>
class CHT {
    using P = pair<T, T>;
    deque<P> lines;
public:
    CHT() = default;
    int sgn(T x) { return x == 0 ? 0 : (x > 0 ? 1 : -1); }
    bool check(P l1, P l2, P l3){
        if(l1.second == l2.second || l2.second == l3.second){
            return sgn(l1.first - l2.first)*sgn(l2.second - l3.second)
                >= sgn(l2.first - l3.first)*sgn(l1.second - l2.second);
        }else {
            return (l1.first - l2.first)*sgn(l2.second - l3.second)/ static_cast<long double>(abs(l1.second - l2.second))
                   >= (l2.first - l3.first)*sgn(l1.second - l2.second)/ static_cast<long double>(abs(l2.second - l3.second));
        }
    }

    void add_line(T a, T b) { // add ax + b
        if(get_max) a = -a, b = -b;
        P L(a, b);
        if(lines.empty()){
            lines.emplace_back(L);
            return;
        }
        if(lines.front().first <= a){
            if(lines.front().first == a){
                if(lines.front().second <= b) return;
                else lines.pop_front();
            }
            while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();
            lines.emplace_front(L);
        }else {
            if(lines.back().first == a){
                if(lines.back().second <= b) return;
                else lines.pop_back();
            }
            while(lines.size() >= 2 && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();
            lines.emplace_back(L);
        }
    }

    T val(const P &L, const T &x) { return L.first * x + L.second; }
    T query(T x){
        int l = -1, r = lines.size() - 1;
        while(r - l > 1){
            int mid = (l+r) >> 1;
            if(val(lines[mid], x) >= val(lines[mid+1], x)) l = mid;
            else r = mid;
        }
        return get_max ? -val(lines[r], x) : val(lines[r], x);
    }

    T query_increase(T x){
        while(lines.size() >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();
        return get_max ? -val(lines.front(), x) : val(lines.front(), x);
    }

    T query_decrease(T x){
        while(lines.size() >= 2 && val(lines.back(), x) >= val(lines[lines.size() - 2], x)) lines.pop_back();
        return get_max ? -val(lines.back(), x) : val(lines.back(), x);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

