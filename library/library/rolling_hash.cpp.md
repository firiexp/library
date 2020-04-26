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


# :warning: library/rolling_hash.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/rolling_hash.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class xor_shift {
    uint32_t x, y, z, w;
public:
    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1))),
    y(1068246329), z(321908594), w(1234567890) {};

    uint32_t urand(){
        uint32_t t;
        t = x ^ (x << 11);
        x = y; y = z; z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    };

    int rand(int n){
        if(n < 0) return -rand(-n);
        uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);
        uint32_t e = urand();
        while(e >= t) e = urand();
        return static_cast<int>(e%(n+1));
    }

    int rand(int a, int b){
        if(a > b) swap(a, b);
        return a+rand(b-a);
    }
};


xor_shift rd;

template<int M>
class rolling_hash {

    static ll &B() {
        static ll B_ = rd.rand(2, M-1);
        return B_;
    }
    static vector<ll> &p() {
        static vector<ll> p_{1, B()};
        return p_;
    }
public:
    vector<ll> hash;
    explicit rolling_hash(const string &s) {
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = (p()[i-1]*p()[1])%M;
            }
        }
        hash.resize(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            hash[i+1] = (hash[i]*B() + s[i]) % M;
        }
    };

    ll get(int l, int r){
        ll res = hash[r]+M-hash[l]*p()[r-l]%M;
        return res >= M ? res-M : res;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/rolling_hash.cpp"
class xor_shift {
    uint32_t x, y, z, w;
public:
    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1))),
    y(1068246329), z(321908594), w(1234567890) {};

    uint32_t urand(){
        uint32_t t;
        t = x ^ (x << 11);
        x = y; y = z; z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    };

    int rand(int n){
        if(n < 0) return -rand(-n);
        uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);
        uint32_t e = urand();
        while(e >= t) e = urand();
        return static_cast<int>(e%(n+1));
    }

    int rand(int a, int b){
        if(a > b) swap(a, b);
        return a+rand(b-a);
    }
};


xor_shift rd;

template<int M>
class rolling_hash {

    static ll &B() {
        static ll B_ = rd.rand(2, M-1);
        return B_;
    }
    static vector<ll> &p() {
        static vector<ll> p_{1, B()};
        return p_;
    }
public:
    vector<ll> hash;
    explicit rolling_hash(const string &s) {
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = (p()[i-1]*p()[1])%M;
            }
        }
        hash.resize(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            hash[i+1] = (hash[i]*B() + s[i]) % M;
        }
    };

    ll get(int l, int r){
        ll res = hash[r]+M-hash[l]*p()[r-l]%M;
        return res >= M ? res-M : res;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

