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


# :heavy_check_mark: test/yosupo_shortest_path_radix_heap.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_shortest_path_radix_heap.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-02 12:50:18+09:00


* see: <a href="https://judge.yosupo.jp/problem/shortest_path">https://judge.yosupo.jp/problem/shortest_path</a>


## Depends on

* :heavy_check_mark: <a href="../../library/datastructure/radixheap.cpp.html">datastructure/radixheap.cpp</a>
* :heavy_check_mark: <a href="../../library/graph/dijkstra_radix_heap.cpp.html">Dijkstra法(Radix Heap) <small>(graph/dijkstra_radix_heap.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

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

#include "../graph/dijkstra_radix_heap.cpp"

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<edge<ll>>> G(n), Ginv(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G[a].emplace_back(b, c);
        Ginv[b].emplace_back(a, c);
    }
    auto d = dijkstra(s, G);
    if(d[t] == INF<ll>){
        puts("-1");
        return 0;
    }
    vector<int> ans{t};
    vector<int> visited(n);
    visited[t] = 1;
    while(ans.back() != s){
        for (auto &&i : Ginv[ans.back()]) {
            if(d[i.to]+i.cost == d[ans.back()] && !visited[i.to]){
                ans.emplace_back(i.to);
                visited[i.to] = 1;
                break;
            }
        }
    }
    printf("%lld %lu\n", d[t], ans.size()-1);
    for (int i = (int)ans.size()-1; i > 0; --i) {
        printf("%d %d\n", ans[i], ans[i-1]);
    }
    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo_shortest_path_radix_heap.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

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

#line 1 "graph/dijkstra_radix_heap.cpp"
template <typename T>
struct edge {
    int from, to; T cost;
    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
};

#line 1 "datastructure/radixheap.cpp"
template <class K, class V>
class RadixHeap {
    static constexpr int bit_length = sizeof(K)*8;
    K last;
    size_t sz, cnt;
    
    array<vector<pair<K, V>>, bit_length> v;
    static inline int bsr(int x){
        return x ? bit_length-__builtin_clz(x) : 0;
    }
    static inline int bsr(ll x){
        return x ? bit_length-__builtin_clzll(x) : 0;
    }

    void pull() {
        if(cnt < v[0].size()) return;;
        int i = 1;
        while(v[i].empty()) i++;
        last = min_element(v[i].begin(),v[i].end())->first;
        for (auto &&x : v[i]) v[bsr(x.first ^ last)].push_back(x);
        v[i].clear();
    }
public:
    RadixHeap() : last(0), sz(0), cnt(0) {}
    void emplace(K x, V val){
        sz++;
        v[bsr(x^last)].emplace_back(x, val);
    }

    pair<K, V> top() {
        pull();
        return v[0][cnt];
    }

    void pop() {
        pull();
        sz--;
        cnt++;
    }

    size_t size() const { return sz; }
    bool empty() const { return !sz; }
};
#line 9 "graph/dijkstra_radix_heap.cpp"

template <typename T>
vector<T> dijkstra(int s,vector<vector<edge<T>>> &G){
    auto n = G.size();
    vector<T> d(n, INF<T>);
    RadixHeap<ll, int> Q;
    d[s] = 0;
    Q.emplace(0, s);
    while(!Q.empty()){
        T cost; int i;
        tie(cost, i) = Q.top(); Q.pop();
        if(d[i] < cost) continue;
        for (auto &&e : G[i]) {
            auto cost2 = cost + e.cost;
            if(d[e.to] <= cost2) continue;
            d[e.to] = cost2;
            Q.emplace(d[e.to], e.to);
        }
    }
    return d;
}

/**
 * @brief Dijkstra法(Radix Heap)
 * @docs _md/dijkstra.md
 */
#line 22 "test/yosupo_shortest_path_radix_heap.test.cpp"

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<edge<ll>>> G(n), Ginv(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G[a].emplace_back(b, c);
        Ginv[b].emplace_back(a, c);
    }
    auto d = dijkstra(s, G);
    if(d[t] == INF<ll>){
        puts("-1");
        return 0;
    }
    vector<int> ans{t};
    vector<int> visited(n);
    visited[t] = 1;
    while(ans.back() != s){
        for (auto &&i : Ginv[ans.back()]) {
            if(d[i.to]+i.cost == d[ans.back()] && !visited[i.to]){
                ans.emplace_back(i.to);
                visited[i.to] = 1;
                break;
            }
        }
    }
    printf("%lld %lu\n", d[t], ans.size()-1);
    for (int i = (int)ans.size()-1; i > 0; --i) {
        printf("%d %d\n", ans[i], ans[i-1]);
    }
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

