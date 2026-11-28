#define PROBLEM "https://judge.yosupo.jp/problem/two_square_sum"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../math/prime/two_square_sum.cpp"

int main() {
    Scanner in;
    Printer out;
    int q;
    in.read(q);
    while (q--) {
        long long n;
        in.read(n);
        auto pairs = two_square_sum(n);
        out.println(pairs.size());
        for (auto [x, y] : pairs) out.println(x, y);
    }
}
