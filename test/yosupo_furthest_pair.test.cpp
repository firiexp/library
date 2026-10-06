#define PROBLEM "https://judge.yosupo.jp/problem/furthest_pair"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../util/fastio.cpp"
#include "../geometry/furthest_pair.cpp"

int main() {
    Scanner in;
    Printer out;
    int t;
    in.read(t);
    while (t--) {
        int n;
        in.read(n);
        vector<pair<ll, ll>> points(n);
        for (auto &[x, y] : points) in.read(x, y);
        auto [i, j] = furthest_pair(points);
        out.println(i, j);
    }
}
