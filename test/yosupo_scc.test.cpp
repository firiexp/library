#define PROBLEM "https://judge.yosupo.jp/problem/scc"
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
using uint = unsigned;
using ull = unsigned long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include "../graph/SCC.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    SCC G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    printf("%d\n", G.build());
    vector<vector<int>> res(G.sz.size());
    for (int i = 0; i < n; ++i) {
        res[G[i]].emplace_back(i);
    }
    for (int i = 0; i < G.sz.size(); ++i) {
        printf("%d", G.sz[i]);
        for (auto &&j : res[i]) {
            printf(" %d", j);
        }
        puts("");
    }
    return 0;
}