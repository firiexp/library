#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"
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

#include "../graph/lowlink.cpp"

int main() {
    int n, m;
    cin >> n >> m;
    LowLink G(n);
    for (int i = 0; i < m; ++i) {
        int s, t;
        scanf("%d %d", &s, &t);
        G.add_edge(s, t);
    }
    G.build();
    for (auto &&e : G.bridge) {
        printf("%d %d\n", e.first, e.second);
    }
    return 0;
}
