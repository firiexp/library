#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0452"
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/centroid_decomposition.cpp"

#include "../math/ntt.cpp"
#include "../math/factorial.cpp"


int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    CentroidDecomposition G(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        sc.read(u, v);
        u--; v--;
        G.add_edge(u, v);
    }
    int root = G.get(0);
    vector<int> bad(n);
    poly val;
    auto dfs = [&](int centroid, auto &&f) -> void {
        bad[centroid] = 1;
        poly all(1);
        all[0] = 1;
        for (auto &&i : G.G[centroid]) {
            if(bad[i]) continue;
            poly a;
            queue<tuple<int, int, int>> Q;
            Q.emplace(i, centroid, 1);
            while(!Q.empty()){
                auto [x, par, dep] = Q.front(); Q.pop();
                while(a.size() <= dep) a.v.emplace_back();
                while(all.size() <= dep) all.v.emplace_back();
                a[dep]++; all[dep]++;
                for (auto &&y : G.G[x]) {
                    if(y != par && !bad[y]) Q.emplace(y, x, dep+1);
                }
            }
            val -= a * a;
        }
        val += all * all;
        for (auto &&i : G.out[centroid]) f(i, f);
    };
    dfs(root, dfs);
    Factorial<mint> f(n);
    for (int i = 1; i < val.size(); ++i) {
        val[i-1] = val[i]*mint(499122177)*f[i-1];
    }
    val.v.pop_back();
    poly fact(n);
    for (int i = 0; i < n; ++i) {
        fact[i] = f[-(n-1-i)];
    }
    val *= fact;
    for (int i = 0; i < n-1; ++i) {
        if (n + i < (int)val.size() + 1) pr.println((val[n - 1 + i] * f[-i]).val);
        else pr.println(0);
    }
    return 0;
}
