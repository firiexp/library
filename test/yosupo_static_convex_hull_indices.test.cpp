#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include <bits/stdc++.h>
using namespace std;
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
        vector<IntPoint> points(n);
        for (auto &p : points) sc.read(p.x, p.y);
        auto ids = convex_hull_indices(points);
        pr.println(int(ids.size()));
        for (int id : ids) pr.println(points[id].x, points[id].y);
    }
}
