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


# :x: test/aoj_dsl_2_b.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_dsl_2_b.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 23:45:54+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B</a>


## Depends on

* :x: <a href="../../library/datastructure/binaryindexedtree.cpp.html">datastructure/binaryindexedtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = uint32_t;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../datastructure/binaryindexedtree.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    BIT<int> s(n);
    for (int i = 0; i < q; ++i) {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        x--;
        if(c == 0) s.add(x, y);
        else printf("%d\n", s.sum(y) - s.sum(x));
    }
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_dsl_2_b.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>

static const int MOD = 1000000007;
using ll = long long;
using u32 = uint32_t;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#line 1 "datastructure/binaryindexedtree.cpp"
template<class T>
class BIT {
    vector<T> bit;
    int n, m;
public:
    BIT(int n): n(n), bit(n){
        m = 1;
        while(m < n) m <<= 1;
    }

    T sum(int k){
        T ret = 0;
        for (; k > 0; k -= (k & -k)) ret += bit[k-1];
        return ret;
    }

    void add(int k, T x){
        for (++k; k < bit.size(); k  += (k & -k)) bit[k-1] += x;
    }

    T lower_bound(T x){
        int i = 0;
        for (int j = m; j > 0; j >>= 1) {
            if(i+j-1 < bit.size() && bit[i+j-1] < x) {
                x -= bit[i+j-1];
                i += j;
            }
        }
        return i;
    }
};
#line 21 "test/aoj_dsl_2_b.test.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    BIT<int> s(n);
    for (int i = 0; i < q; ++i) {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        x--;
        if(c == 0) s.add(x, y);
        else printf("%d\n", s.sum(y) - s.sum(x));
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

