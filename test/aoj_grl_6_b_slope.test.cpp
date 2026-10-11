#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"

#include <bits/stdc++.h>
using namespace std;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
#include "../util/fastio.cpp"
#include "../flow/primaldual.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, m, amount;
    sc.read(n, m, amount);
    PrimalDual<int, long long> mf(n);
    for (int i = 0; i < m; ++i) {
        int u, v, cap, cost;
        sc.read(u, v, cap, cost);
        mf.add_edge(u, v, cap, cost);
    }
    auto curve = mf.slope(0, n - 1, amount);
    pr.println(curve.back().first == amount ? curve.back().second : -1);
}
