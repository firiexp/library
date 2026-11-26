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

#include "../graph/connectivity/SCC.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    SCC G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    printf("%d\n", G.build(false));
    for (const auto &group : G.groups()) {
        printf("%zu", group.size());
        for (int v : group) {
            printf(" %d", v);
        }
        puts("");
    }
    return 0;
}
