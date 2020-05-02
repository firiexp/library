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


# :heavy_check_mark: test/yosupo_shortest_path.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo_shortest_path.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-02 12:42:39+09:00


* see: <a href="https://judge.yosupo.jp/problem/shortest_path">https://judge.yosupo.jp/problem/shortest_path</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/dijkstra.cpp.html">graph/dijkstra.cpp</a>


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

#include "../graph/dijkstra.cpp"

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
#line 1 "test/yosupo_shortest_path.test.cpp"
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

#line 1 "graph/dijkstra.cpp"
template <typename T>
struct edge {
    int from, to; T cost;
    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
};

template <typename T>
vector<T> dijkstra(int s,vector<vector<edge<T>>> &G){
    auto n = G.size();
    vector<T> d(n, INF<T>);
    priority_queue<pair<T, int>,vector<pair<T, int>>,greater<>> Q;
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
#line 22 "test/yosupo_shortest_path.test.cpp"

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

