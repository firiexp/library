#define PROBLEM "https://yukicoder.me/problems/no/957"

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;
template<class T>
constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../flow/dinic.cpp"

int main() {
    Scanner in;
    Printer out;
    int h, w;
    in.read(h, w);

    vector<vector<ll>> g(h, vector<ll>(w));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            in.read(g[i][j]);
        }
    }
    vector<ll> row(h), col(w);
    for (int i = 0; i < h; ++i) in.read(row[i]);
    for (int j = 0; j < w; ++j) in.read(col[j]);

    int s = h + w;
    int t = s + 1;
    Dinic<ll, true> mf(h + w + 2);
    ll base = 0;
    auto add_cost_if_true = [&](int v, ll cost) {
        if (cost >= 0) mf.add_edge(s, v, cost);
        else {
            base += cost;
            mf.add_edge(v, t, -cost);
        }
    };

    for (int i = 0; i < h; ++i) {
        ll cost = -row[i];
        for (int j = 0; j < w; ++j) cost += g[i][j];
        add_cost_if_true(i, cost);
    }
    for (int j = 0; j < w; ++j) {
        add_cost_if_true(h + j, -col[j]);
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            mf.add_edge(i, h + j, g[i][j]);
        }
    }

    ll min_cost = base + mf.flow(s, t);
    out.println(-min_cost);
    return 0;
}
