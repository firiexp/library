#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"

#include "../util/modint.cpp"
#include "../math/ntt.cpp"

#include "../datastructure/point_add_rectangle_sum.cpp"
#include "../datastructure/static_rectangle_sum.cpp"

#include "../graph/dijkstra.cpp"
#include "../graph/dijkstra_restore.cpp"

#include "../math/prime/get_min_factor.cpp"
#include "../math/prime/get_prime.cpp"

#include "../geometry/dualgraph.cpp"
#include "../geometry/half_plane_intersection.cpp"

#include "../tree/LCA.cpp"
#include "../tree/auxtree.cpp"

int main() {
    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
