#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <charconv>
#include "../util/fastio.cpp"

#include "../util/modint.cpp"
#include "../math/ntt.cpp"

#include "../datastructure/point_add_rectangle_sum.cpp"
#include "../datastructure/static_rectangle_sum.cpp"

#include "../graph/dijkstra.cpp"
#include "../graph/dijkstra_restore.cpp"
#include "../graph/bfs01.cpp"
#include "../graph/bellman_ford.cpp"

#include "../graph/SCC.cpp"
#include "../graph/twosat.cpp"

#include "../graph/biconnected_components.cpp"
#include "../graph/block_cut_tree.cpp"

#include "../math/prime/get_min_factor.cpp"
#include "../math/prime/get_prime.cpp"
#include "../math/prime/get_prime_wheel.cpp"

#include "../geometry/dualgraph.cpp"
#include "../geometry/half_plane_intersection.cpp"

#include "../tree/LCA.cpp"
#include "../tree/auxtree.cpp"
#include "../tree/virtual_tree_helper.cpp"
#include "../tree/hld.cpp"
#include "../tree/hld_edge.cpp"

void check_composed_libraries() {
    edge<ll> adjacent(1, 0), directed(1, 2, 1);
    assert(adjacent.from == -1 && adjacent.to == 1 && adjacent.cost == 0);
    assert(directed.from == 1 && int(directed) == 2 && directed.cost == 1);
    vector<vector<edge<ll>>> g(3);
    g[0].push_back(adjacent);
    g[1].push_back(directed);
    vector<edge<ll>> es = {{0, 1, 0}, directed};
    vector<ll> expected = {0, 0, 1};
    assert(dijkstra(0, g) == expected);
    assert(dijkstra_restore(0, g).dist == expected);
    assert(bfs01(0, g) == expected);
    assert(bellman_ford(0, 3, es) == expected);

    SCC scc(3);
    scc.add_edge(0, 1);
    scc.add_edge(1, 0);
    scc.add_edge(1, 2);
    assert(scc.build() == 2);
    assert(scc[0] == scc[1] && scc[1] < scc[2]);
    assert(scc.G_out[scc[0]] == vector<int>{scc[2]});
    TwoSAT sat(2);
    sat.add_or(0, 0);
    sat.add_if(0, 1);
    assert(sat.build() == vector<int>({1, 1}));
    sat.add_or(sat.negate(1), sat.negate(1));
    assert(sat.build().empty());

    HeavyLightDecomposition hld(3);
    HeavyLightDecompositionEdge hld_edge(3);
    BiconnectedComponents bcc(3);
    BlockCutTree bct(3);
    AuxTree aux(3);
    VirtualTreeHelper virtual_tree(3);
    for (int v = 1; v < 3; ++v) {
        hld.add_edge(0, v);
        hld_edge.add_edge(0, v);
        bcc.add_edge(0, v);
        bct.add_edge(0, v);
        aux.add_edge(0, v);
        virtual_tree.add_edge(0, v);
    }
    hld.build();
    hld_edge.build();
    assert(hld.lca(1, 2) == 0 && hld_edge.lca(1, 2) == 0);
    assert(hld.subtree(0) == make_pair(0, 3));
    assert(hld_edge.subtree(0) == make_pair(1, 3));
    assert(bcc.build() == 2);
    assert(bct.build() == 3 && bct.is_articulation[0]);
    aux.buildLCA();
    virtual_tree.build();
    assert(aux.LCA(1, 2) == 0 && virtual_tree.lca(1, 2) == 0);
    auto tree = virtual_tree.make({1, 2});
    assert(tree.root == 0);
    sort(tree.vertices.begin(), tree.vertices.end());
    assert(tree.vertices == vector<int>({0, 1, 2}));
}

int main() {
    check_composed_libraries();
    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
