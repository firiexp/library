#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"

#include <algorithm>
#include <vector>

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../geometry/area_of_union_of_rectangles.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);

    AreaOfUnionOfRectangles<long long> solver;
    for (int i = 0; i < n; ++i) {
        long long l, d, r, u;
        sc.read(l, d, r, u);
        solver.add_rectangle(l, d, r, u);
    }
    pr.println(solver.solve());
    return 0;
}
