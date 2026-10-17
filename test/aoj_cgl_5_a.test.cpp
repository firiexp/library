#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_5_A"
#define ERROR "1e-8"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../geometry/geometry.cpp"

int main() {
    Scanner in;
    Printer out;
    int n;
    in.read(n);
    Polygon points(n);
    for (auto &p : points) in.read(p.x, p.y);
    out.println_fixed(closest_pair(points), 12);
}
