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


# :warning: string/rolling_hash_u64.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/rolling_hash_u64.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 17:42:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
using u64 = unsigned long long;

constexpr u64 M = (1UL << 61) - 1;
constexpr u64 POSITIVISER = M * 3;
constexpr u64 MASK30 = (1UL << 30) - 1;
constexpr u64 MASK31 = (1UL << 31) - 1;

class rolling_hash_u64 {
    static u64 get_base(){
        u64 z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1)))+0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z;
    }

    static u64 &B() {
        static u64 B_ = (get_base())%(M-2)+2;
        return B_;
    }
    static vector<u64> &p() {
        static vector<u64> p_{1, B()};
        return p_;
    }

    static inline u64 mul(u64 x, u64 y){
        u64 a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e = b*c+a*d;
        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);
    }

    static inline u64 calc_mod(u64 val){
        val = (val & M) + (val >> 61);
        if(val > M) val -= M;
        return val;
    }
public:
    vector<u64> hash;
    explicit rolling_hash_u64(const string &s) {
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = calc_mod(mul(p()[i-1], p()[1]));
            }
        }
        hash.resize(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            hash[i+1] = calc_mod(mul(hash[i],B()) + s[i]);
        }
    };

    u64 get(int l, int r){
        return calc_mod(hash[r] + POSITIVISER - mul(hash[l], p()[r-l]));
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/rolling_hash_u64.cpp"
using u64 = unsigned long long;

constexpr u64 M = (1UL << 61) - 1;
constexpr u64 POSITIVISER = M * 3;
constexpr u64 MASK30 = (1UL << 30) - 1;
constexpr u64 MASK31 = (1UL << 31) - 1;

class rolling_hash_u64 {
    static u64 get_base(){
        u64 z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1)))+0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z;
    }

    static u64 &B() {
        static u64 B_ = (get_base())%(M-2)+2;
        return B_;
    }
    static vector<u64> &p() {
        static vector<u64> p_{1, B()};
        return p_;
    }

    static inline u64 mul(u64 x, u64 y){
        u64 a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e = b*c+a*d;
        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);
    }

    static inline u64 calc_mod(u64 val){
        val = (val & M) + (val >> 61);
        if(val > M) val -= M;
        return val;
    }
public:
    vector<u64> hash;
    explicit rolling_hash_u64(const string &s) {
        if(p().size() <= s.size()){
            int l = p().size();
            p().resize(s.size()+1);
            for (int i = l; i < p().size(); ++i) {
                p()[i] = calc_mod(mul(p()[i-1], p()[1]));
            }
        }
        hash.resize(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            hash[i+1] = calc_mod(mul(hash[i],B()) + s[i]);
        }
    };

    u64 get(int l, int r){
        return calc_mod(hash[r] + POSITIVISER - mul(hash[l], p()[r-l]));
    }
};


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

