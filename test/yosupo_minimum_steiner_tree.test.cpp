#define PROBLEM "https://judge.yosupo.jp/problem/minimum_steiner_tree"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../graph/minimum_steiner_tree.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    MinimumSteinerTree<ll> st(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        in.read(u, v, w);
        st.add_edge(u, v, w);
    }
    int k;
    in.read(k);
    vector<int> terminals(k);
    in.read(terminals);
    st.build(terminals);
    auto ids = st.restore(terminals[0]);
    out.println(st.cost(terminals[0]), (int)ids.size());
    out.println(ids);
}
