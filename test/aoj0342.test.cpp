#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0342"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <numeric>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

static const int MOD = 1000000007;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#define ERROR "1e-4"
#include <charconv>
#include "../util/fastio.cpp"
#include "../geometry/geometry.cpp"
#include "../datastructure/unionfind.cpp"
template <typename T>
struct edge {
    int from, to;
    T cost;

    edge(int to, T cost) : from(-1), to(to), cost(cost) {}
    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}

    explicit operator int() const {return to;}
};

int main() {
    Scanner sc;
    Printer pr;
    int n, m;
    sc.read(n, m);
    vector<Point> v(n);
    map<Point, int> M;
    UnionFind uf(n);
    for (int i = 0; i < n; ++i) {
        sc.read(v[i].x, v[i].y);
        M[v[i]] = i;
    }
    double ans = 0;
    auto C = convex_hull(v);
    for (int i = 0; i < C.size(); ++i) {
        ans += abs(C[i]-C[(i+1)%C.size()]);
        uf.unite(M[C[i]], M[C[(i+1)%C.size()]]);
    }
    vector<edge<double>> G;
    for (int i = 0; i < m; ++i) {
        int a, b;
        sc.read(a, b);
        a--; b--;
        G.emplace_back(a, b, abs(v[a]-v[b]));
    }
    sort(begin(G), end(G), [](const edge<double> &a, const edge<double> &b) { return a.cost < b.cost; });
    for(auto &e : G) if(uf.unite(e.from, e.to)) ans += e.cost;
    pr.println_fixed(ans, 8);
    return 0;
}
