#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_B"
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
    Polygon polygon(n);
    for (auto &p : polygon) in.read(p.x, p.y);
    out.println_fixed(diameter(polygon), 12);
}
