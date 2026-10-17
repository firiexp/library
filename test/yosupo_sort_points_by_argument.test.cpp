#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../geometry/argsort.cpp"

int main() {
    Scanner in;
    Printer out;
    int n;
    in.read(n);
    vector<IntPoint> points(n);
    for (auto &p : points) in.read(p.x, p.y);
    for (int i : arg_sort_indices(points)) out.println(points[i].x, points[i].y);
}
