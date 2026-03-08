#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;
template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;

#include "../util/fastio.cpp"
#include "../flow/costscalingdinic.cpp"

int main() {
    Scanner sc;
    Printer pr;

    int n, m;
    sc.read(n, m);
    CostScalingDinic<int, true> mf(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        sc.read(u, v, c);
        mf.add_edge(u, v, c);
    }
    pr.writeln(mf.flow(0, n - 1));
    return 0;
}
