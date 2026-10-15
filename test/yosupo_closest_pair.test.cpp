#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include <bits/stdc++.h>

using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../geometry/closest_pair.cpp"

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
            sc.read(ps[i].x, ps[i].y);
        }
        auto [a, b] = closest_pair(ps);
        pr.println(a, b);
    }
    return 0;
}
