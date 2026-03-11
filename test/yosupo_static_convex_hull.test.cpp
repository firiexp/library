#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include <algorithm>
#include <random>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../geometry/convex_hull.cpp"


int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        int n;
        sc.read(n);
        vector<IntPoint> ps(n);
        for (int i = 0; i < n; ++i) {
            sc.read(ps[i].first, ps[i].second);
        }
        auto ch = convex_hull(ps);
        pr.writeln((int)ch.size());
        for (auto [x, y] : ch) pr.writeln(x, y);
    }
    return 0;
}
