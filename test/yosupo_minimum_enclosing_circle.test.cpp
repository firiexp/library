#define PROBLEM "https://judge.yosupo.jp/problem/minimum_enclosing_circle"
#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../geometry/minimum_enclosing_circle.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    vector<IntPoint> points(n);
    for (auto &p : points) sc.read(p.x, p.y);
    auto circle = minimum_enclosing_circle(points);
    string answer(n, '0');
    for (int i : circle->boundary_indices) answer[i] = '1';
    pr.println(answer);
}
