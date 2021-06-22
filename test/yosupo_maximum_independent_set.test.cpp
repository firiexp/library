#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
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

template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../graph/independentset.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    IndependentSet G(n);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        G.add_edge(l, r);
    }
    auto res = G.maximum_independent_set();
    cout << res.first << "\n";
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if(res.second & (1ull << i)){
            if(cur++) printf(" ");
            printf("%d", i);
        }
    }
    puts("");
    return 0;
}