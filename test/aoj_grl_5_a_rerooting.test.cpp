#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_A"

#include <algorithm>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../tree/rerooting.cpp"

struct Monoid {
    using T = long long;
    using U = long long;

    static T f(T a, T b) { return max(a, b); }
    static T g(T a, U b) { return a + b; }
    static T e() { return 0; }
};

int main() {
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    ReRooting<Monoid> rr(n);
    for (int i = 0; i < n - 1; ++i) {
        int s, t, w;
        sc.read(s, t, w);
        rr.add_edge(s, t, (long long)w);
    }

    auto dp = rr.solve();
    pr.println(*max_element(dp.begin(), dp.end()));
    return 0;
}
