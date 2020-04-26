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


# :heavy_check_mark: test/aoj_dsl_2_b.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_dsl_2_b.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 18:40:25+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/datastructure/binaryindexedtree.cpp.html">BinaryIndexedTree (BIT) <small>(datastructure/binaryindexedtree.cpp)</small></a>


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
        if(c == 0) s.add(x-1, y);
        else printf("%d\n", s.sum(y-1) - s.sum(x-2));
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
    int m;
public:
    BIT(int n): bit(vector<T>(n+1, 0)){
        m = 1;
        while(m < n) m <<= 1;
    }

    T sum(int k){
        T ret = 0;
        for (++k; k > 0; k -= (k & -k)) ret += bit[k];
        return ret;
    }

    void add(int k, T x){
        for (++k; k < bit.size(); k  += (k & -k)) bit[k] += x;
    }
    
    T lower_bound(T x){
        int i = 0;
        for (int j = m; j > 0; j >>= 1) {
            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];
        }
        return i;
    }
};
/**
 * @brief BinaryIndexedTree (BIT)
 * @docs _md/binaryindexedtree.md
 */
#line 21 "test/aoj_dsl_2_b.test.cpp"

int main() {
    int n, q;
    cin >> n >> q;
    BIT<int> s(n);
    for (int i = 0; i < q; ++i) {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        if(c == 0) s.add(x-1, y);
        else printf("%d\n", s.sum(y-1) - s.sum(x-2));
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

