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


# :heavy_check_mark: test/yosupo_sum_of_floor_of_linear.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_sum_of_floor_of_linear.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-10 21:23:43+09:00


* see: <a href="https://judge.yosupo.jp/problem/sum_of_floor_of_linear">https://judge.yosupo.jp/problem/sum_of_floor_of_linear</a>


## Depends on

* :heavy_check_mark: <a href="../../library/math/floor_sum.cpp.html">math/floor_sum.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
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

#include "../math/floor_sum.cpp"

int main() {
    int t;
    cin >> t;
    while(t--) {
        ll n, m, a, b;
        scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
        printf("%lld\n", floor_sum(n, m, a, b));
    }
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_sum_of_floor_of_linear.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"
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

#line 1 "math/floor_sum.cpp"
ll floor_sum(ll n, ll m, ll a, ll b){
    ll ans = 0;
    if(a >= m) {
        ans += (n-1)*n/2*(a/m);
        a %= m;
    }
    if (b >= m){
        ans += n*(b/m);
        b %= m;
    }
    ll y = (a*n+b)/m, x = (y*m - b);
    if(!y) return ans;
    ans += (n-(x+a-1)/a)*y;
    ans += floor_sum(y, a, m, (a - x%a)%a);
    return ans;
}
#line 21 "test/yosupo_sum_of_floor_of_linear.test.cpp"

int main() {
    int t;
    cin >> t;
    while(t--) {
        ll n, m, a, b;
        scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
        printf("%lld\n", floor_sum(n, m, a, b));
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

