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


# :heavy_check_mark: test/aoj_dpl_5_a.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_dpl_5_a.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-10 16:12:25+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/util/modint.cpp.html">modint(固定MOD) <small>(util/modint.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../util/modint.cpp"
int main() {
    int n, k;
    cin >> n >> k;
    cout << mint(k).pow(n).val << "\n";
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_dpl_5_a.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#line 1 "util/modint.cpp"
template <u32 M>
struct modint {
    u32 val;
public:
    static modint raw(int v) { modint x; x.val = v; return x; }
    modint() : val(0) {}
    template <class T>
    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = u32(x); }
    modint(bool v) { val = ((unsigned int)(v) % M); }
    modint& operator++() { val++; if (val == M) val = 0; return *this; }
    modint& operator--() { if (val == 0) val = M; val--; return *this; }
    modint operator++(int) { modint result = *this; ++*this; return result; }
    modint operator--(int) { modint result = *this; --*this; return result; }
    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -= M; return *this; }
    modint& operator-=(const modint& b) { val -= b.val; if (val >= M) val += M; return *this; }
    modint& operator*=(const modint& b) { u64 z = val; z *= b.val; val = (u32)(z % M); return *this; }
    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(M-2); }
    friend modint operator+(const modint& a, const modint& b) { return modint(a) += b; }
    friend modint operator-(const modint& a, const modint& b) { return modint(a) -= b; }
    friend modint operator*(const modint& a, const modint& b) { return modint(a) *= b; }
    friend modint operator/(const modint& a, const modint& b) { return modint(a) /= b; }
    friend bool operator==(const modint& a, const modint& b) { return a.val == b.val; }
    friend bool operator!=(const modint& a, const modint& b) { return a.val != b.val; }
};
using mint = modint<MOD>;

/**
 * @brief modint(固定MOD)
 * @docs _md/modint.md
 */
#line 21 "test/aoj_dpl_5_a.test.cpp"
int main() {
    int n, k;
    cin >> n >> k;
    cout << mint(k).pow(n).val << "\n";
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

