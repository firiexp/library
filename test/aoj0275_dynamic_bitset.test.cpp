#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0275"

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;

template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../graph/dijkstra.cpp"
#include "../datastructure/dynamic_bitset.cpp"

int main() {
    Scanner in;
    Printer out;

    int n, m;
    in.read(n, m);
    vector<vector<edge<ll>>> g(n);
    vector<int> u(m), v(m), c(m);
    for (int i = 0; i < m; ++i) {
        in.read(u[i], v[i], c[i]);
        --u[i], --v[i];
        g[u[i]].emplace_back(v[i], c[i]);
        g[v[i]].emplace_back(u[i], c[i]);
    }

    int s, t, q;
    in.read(s, t, q);
    --s, --t;

    auto ds = dijkstra(s, g);
    auto dt = dijkstra(t, g);
    ll best = ds[t];

    vector<int> active_id(n, -1);
    vector<int> active_vertices;
    active_vertices.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (ds[i] != INF<ll> && dt[i] != INF<ll> && ds[i] + dt[i] == best) {
            active_id[i] = (int)active_vertices.size();
            active_vertices.push_back(i);
        }
    }

    int k = active_vertices.size();
    vector<vector<int>> dag(k);
    vector<int> indeg(k, 0);
    for (int i = 0; i < m; ++i) {
        int a = active_id[u[i]];
        int b = active_id[v[i]];
        if (a != -1 && b != -1 && ds[u[i]] + c[i] == ds[v[i]]) {
            dag[a].push_back(b);
            ++indeg[b];
        }
        if (a != -1 && b != -1 && ds[v[i]] + c[i] == ds[u[i]]) {
            dag[b].push_back(a);
            ++indeg[a];
        }
    }

    vector<int> ord;
    ord.reserve(k);
    queue<int> que;
    for (int i = 0; i < k; ++i) if (indeg[i] == 0) que.push(i);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        ord.push_back(x);
        for (int to : dag[x]) {
            if (--indeg[to] == 0) que.push(to);
        }
    }

    vector<pair<int, int>> qs(q);
    for (auto &[a, b] : qs) {
        in.read(a, b);
        --a, --b;
    }

    constexpr int BLOCK = 2048;
    vector<DynamicBitset> dp(k, DynamicBitset(BLOCK));
    vector<unsigned char> active(k, 0);
    for (int l = 0; l < q; l += BLOCK) {
        int r = min(q, l + BLOCK);
        for (auto &bs : dp) bs.reset();
        fill(active.begin(), active.end(), 0);
        for (int i = l; i < r; ++i) {
            int a = active_id[qs[i].first];
            if (a != -1) {
                dp[a].set(i - l);
                active[a] = 1;
            }
        }
        for (int vtx : ord) {
            if (!active[vtx]) continue;
            for (int to : dag[vtx]) {
                dp[to] |= dp[vtx];
                active[to] = 1;
            }
        }
        for (int i = l; i < r; ++i) {
            int b = active_id[qs[i].second];
            out.println(b != -1 && dp[b].test(i - l) ? "Yes" : "No");
        }
    }
    return 0;
}
