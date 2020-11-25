#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0452"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../tree/centroid_decomposition.cpp"

#include "../math/ntt.cpp"

class Factorial {
    vector<mint> facts, factinv;
public:
    explicit Factorial(int n) : facts(n+1), factinv(n+1) {
        facts[0] = 1;
        for (int i = 1; i < n+1; ++i) facts[i] = facts[i-1] * mint(i);
        factinv[n] = facts[n].inv();
        for (int i = n-1; i >= 0; --i) factinv[i] = factinv[i+1] * mint(i+1);
    }
    mint fact(int k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint operator[](const int &k) const {
        if(k >= 0) return facts[k]; else return factinv[-k];
    }
    mint C(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[q] * factinv[p-q];
    }
    mint P(int p, int q) const {
        if(q < 0 || p < q) return 0;
        return facts[p] * factinv[p-q];
    }
    mint H(int p, int q) const {
        if(p < 0 || q < 0) return 0;
        return q == 0 ? 1 : C(p+q-1, q);
    }
};


int main() {
    int n;
    cin >> n;
    CentroidDecomposition G(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
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
    Factorial f(n);
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
        if(n+i < val.size()+1) printf("%d\n", (val[n-1+i]*f[-i]).val);
        else printf("%d\n", 0);
    }
    return 0;
}