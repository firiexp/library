#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
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

#include "../graph/biconnected_components.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    BiconnectedComponents G(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        G.add_edge(a, b);
    }
    G.build();
    auto res = G.bcc_vertices;
    for (auto &&v : res) sort(v.begin(), v.end());
    sort(res.begin(), res.end());
    cout << res.size() << "\n";
    for (auto &&v : res) {
        cout << v.size();
        for (auto &&x : v) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
