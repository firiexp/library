#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../math/stern_brocot_tree.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        ll n, x, y;
        sc.read(n, x, y);
        auto [left, right] = SternBrocotTree::binary_search(n, n, [&](ll p, ll q) {
            return p * y <= q * x;
        });
        if (left.first * y == left.second * x) right = left;
        pr.println(left.first, left.second, right.first, right.second);
    }
}
